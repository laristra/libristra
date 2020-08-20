// inputs.h
// May 08, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#pragma once

#include<ristra/ristra-config.h>

#include "ristra/assertions/dbc.h"
#include "ristra/embedded/embed_lua.h"
#include "ristra/initialization/inputs_impl.h"
#include "ristra/initialization/input_source.h"
#include "ristra/utils/type_traits.h"

#include <algorithm> // all_of
#include <array>
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric> // accumulate
#include <set>
#include <sstream>
#include <string>
#include <typeinfo>
#include "unistd.h"

namespace ristra
{
/**\brief Class to register and resolve application inputs (no RTTI required).
 *
 * \tparam input_traits: structure that defines a number of types, including
 * mesh, ics_return_t (return type of initial conditions function),
 * ics_function_t (initial condition function type), a callable wrapper to
 * ics_function_t (marshalls data to/from the initial condition function),
 *
 * input_engine_t is defined with a virtual destructor; this enables clients to
 * inherit from it and change the accessibility of various functionality. That
 * is useful for testing, if nothing else.
 *
 * A key enabler of inputs_t is the input_registry<T> class. This allows
 * the class to have a typed key-value store without type erasure. No RTTI
 * is used to do this. While input_engine_t is not a singleton, its registries
 * are singletons. Keeping most of the registry data in singletons is first
 * and foremost a syntactic enabler: it lets clients register arbitrary data
 * types. A further benefit is that different clients can basically act as if
 * input_engine_t were a singleton: you do not need to pass an input_engine_t
 * to every user of init_value_t, for example. The one respect in which
 * input_engine_t is NOT a singleton is registering input_sources and calling
 * resolve_inputs(). That needs to be done by the calling process.
 *
 * To operate the class, one registers targets and one or more input sources.
 * Targets are strings that will be resolved from the input source(s).
 * Currently,
 * there is support for a Lua source and a hard-coded C++ source. In the future,
 * we expect this to increase to Python, SQL, and (perhaps) multiple sources of
 * any given type.
 *
 * Note that inputs are distinguished by name and type. That is, an int32_t
 * target named "foo" is considered different from a uint32_t named "foo".
 *
 * The current resolution priority is Lua file, then hard-coded source. The
 * hard-coded source thus acts as a default file.
 */
template <class input_traits>
class input_engine_t
{
 public:
  using traits_t = input_traits;
  using type_tuple = typename input_traits::types;

  using string_t = std::string;
  using str_cr_t = string_t const &;
  using target_set_t = std::set<string_t>;
  using failed_set_t = std::set<string_t>;
  using deq_bool = std::deque<bool>;
  template <class reg_t>
  using registry = std::map<string_t, reg_t>;

  /**\brief Used only for type-switching in explicit specializations. */
  template <typename T>
  struct type_t {
  };

  static constexpr size_t tsize = std::tuple_size<type_tuple>::value;

 protected:
  /**\brief A class for registering targets, associating resolved data and
   * targets, and recording failures associated with a given type.
   *
   * \tparam T: The type of the target data
   */
  template <class T>
  struct input_registry {
    using key_t = std::string;
    using data_t = std::map<key_t, T>;
    using target_set_t = std::set<key_t>;
    using failed_set_t = std::set<key_t>;

    registry<T> & get_data_registry() { return m_reg; }

    target_set_t & get_target_set() { return m_targets; }

    failed_set_t & get_failed_set() { return m_failures; }

    registry<T> m_reg;
    target_set_t m_targets;
    failed_set_t m_failures;

    void clear()
    {
      m_reg.clear();
      m_targets.clear();
      m_failures.clear();
    }

    // singleton for each type
    static input_registry & instance()
    {
      static input_registry ir;
      return ir;
    }

    void set_all_resolved() { m_all_resolved = true; }

    bool get_all_resolved() const { return m_all_resolved; }

    void set_resolve_called() { m_resolve_called = true; }

    bool get_resolve_called() const { return m_resolve_called; }

   private:
    bool m_resolve_called = false;
    bool m_all_resolved = false;
    input_registry() {}
    ~input_registry() {}
    input_registry(input_registry &) = delete;
    input_registry(input_registry &&) = delete;
  }; // registry

 public:
  input_engine_t() {}

  virtual ~input_engine_t() {}

 private:
  input_engine_t(input_engine_t &) = delete;

  input_engine_t & operator=(input_engine_t &) = delete;

 private:
  // generate calls to each function for all types via std::tuple.
  apply_op_f_by_tuple(resolve_inputs_);
  apply_void_f_by_tuple(clear_registry_);
  apply_void_f_by_tuple(print_unresolved_types_);
  apply_void_f_by_tuple(print_registered_type_);

 public:
  // Principal interface

  /**\brief Clear all registered targets on all types. */
  void clear_registry() { clear_registry__by_tuple<type_tuple>(); }

  /**\\brief For each target, look through input sources and attempt
   * to resolve each target.
   *
   * \return whether all inputs for all types were successfully resolved.
   *
   * Always tries to find something in an external input file, then looks
   * in the hard-coded source. This makes the hard-coded source the
   * default.
   **/
  bool resolve_inputs()
  {
    deq_bool resolutions(resolve_inputs__by_tuple<type_tuple>(
      *this, m_lua_source, m_hard_coded_source));
    bool all_resolved = std::accumulate(resolutions.begin(), resolutions.end(),
      true, [](bool b1, bool b2) { return b1 && b2; });
    if (!all_resolved) {
      print_unresolved_types__by_tuple<type_tuple>(resolutions);
    }
    return all_resolved;
  } // resolve_inputs

  /**\brief Register a Lua input source. This class will delete by default.
   *
   * \param lua_source Pointer to lua_source_t
   */
  void register_lua_source(lua_source_t * lua_source)
  {
    m_lua_source.reset(lua_source);
    return;
  }

  /**\brief Register a hard coded input source. This class will delete
   * the source.
   *
   * \param hard_coded_source the hard_coded_source object
   */
  void register_hard_coded_source(hard_coded_source_t * hard_coded_source)
  {
    m_hard_coded_source.reset(hard_coded_source);
  }

  /**\brief Check whether input_engine has a Lua input source. */
  bool has_lua_source() const {
    return static_cast<bool>(m_lua_source);
  }

  /**\brief Check whether input_engine has a hard-coded input source. */
  bool has_hard_coded_source() const {
    return static_cast<bool>(m_hard_coded_source);
  }

  /**\brief Get reference to Lua input source.
   *
   * Throws exception if no Lua source registered.*/
  lua_source_t &get_lua_source() const {
    Require( has_lua_source(),"Cannot get reference to non-existent source!");
    return *m_lua_source;
  }

  /**\brief Get reference to hard-coded input source.
   *
   * Throws exception if no hard-coded source registered.*/
  hard_coded_source_t &get_hard_coded_source() const {
    Require(
      has_hard_coded_source(), "Cannot get reference to non-existent source!");
    return *m_hard_coded_source;
  }

  /**\brief Register a target for any non-function type.
   *
   * A separate sub-registry is maintained for each type.
   */
  template <class T>
  void register_target(str_cr_t name)
  {
    target_set_t & target_set = get_target_set<T>();
    // TODO could have some error checking here: what if something gets
    // registered more than once, for example?
    auto p = target_set.insert(name);
    if (!p.second) {
      printf("%s:%i failed to insert target '%s'\n", __FUNCTION__, __LINE__,
        name.c_str());
    }
    return;
  } // register_target

  template <class T> // TODO add validators, defaults, etc.
  void register_targets(target_set_t & names)
  {
    for (auto & n : names) {
      register_target<T>(n);
    }
    return;
  } // register_target

  /**\brief Method to get an initialization value.
   *
   * \return: non-callable types: reference to T; std::function: a copy of the
   * std::function object
   *
   * \tparam T: the type of thing you're retrieving
   * \tparam ret_t: Return type. You almost certainly want the default.
   */
  template <class T,
    typename ret_t =
      typename std::conditional<utils::is_callable<T>::value, T, T &>::type>
  ret_t get_value(str_cr_t target_name)
  {
    value_getter<T> g;
    return g(target_name, *this);
  } // get_value

  /**\brief indicate whether a target was resolved */
  template <class T>
  bool resolved(str_cr_t target) const
  {
    input_registry<T> const & i_reg(input_registry<T>::instance());
    registry<T> const & el_reg(get_registry<T>());
    bool res_called = i_reg.get_resolve_called();
    bool in_reg = 1 == el_reg.count(target);
    if (!res_called) {
      printf("%s:%i resolve not called for type '%s'\n", __FUNCTION__, __LINE__,
        typeid(T).name());
    }
    return res_called && in_reg;
  }

  void print_registered_types()
  {
    printf("%s:%i \n", __FUNCTION__, __LINE__);
    print_registered_type__by_tuple<type_tuple>();
  }

  /**\brief Get a value outside of the usual registry path.
   *
   * Use this to get a value on the spur of the moment: it will resolve
   * the key, and if successful, return the corresponding value. If resolution
   * fails, it will throw a std::runtime_error.
   *
   * \todo Need to decide between these different paths/approaches.
   */
  template <class T,
    typename ret_t =
      typename std::conditional<utils::is_callable<T>::value, T, T &>::type>
  ret_t get_instant_value(str_cr_t target_name)
  {
    resolve_input_<T> r;
    bool resolved = r(target_name, *this, m_lua_source, m_hard_coded_source);
    if(!resolved){
      string_t err = "get_instant_value: Could not resolve key '" +
        target_name + "' using type '" + typeid(T).name() + "'";
      Insist(false,err);
    }
    return get_value<T>(target_name);
  } // get_instant_value

 protected:
  template <class T>
  registry<T> & get_registry()
  {
    return input_registry<T>::instance().get_data_registry();
  }

  template <class T>
  registry<T> const & get_registry() const
  {
    return input_registry<T>::instance().get_data_registry();
  }

  template <class T>
  target_set_t & get_target_set()
  {
    return input_registry<T>::instance().get_target_set();
  }

  template <class T>
  target_set_t & get_failed_target_set()
  {
    return input_registry<T>::instance().get_failed_set();
  }

  /**\brief Clear all registered targets on type T. */
  template <typename T, size_t I>
  void clear_registry_()
  {
    input_registry<T>::instance().clear();
  }

  /**\brief If resolution failed for this type (at index I), print out some
   * information about that.
   */
  template <class T, size_t I>
  void print_unresolved_types_(deq_bool const & resolutions)
  {
    bool const resolved(resolutions[I]);
    failed_set_t const & failures(get_failed_target_set<T>());
    if (!resolved) {
      std::cout << "Did not resolve all targets for type "
                << typeid(T).name() // m_type_names[I]
                << ". Unresolved targets: ";
      std::copy(failures.begin(), failures.end(),
        std::ostream_iterator<string_t>(std::cout, ","));
      std::cout << std::endl;
    }
    return;
  } // print_unresolved_types_

  /**\brief Print registered types */
  template <class T, size_t I>
  void print_registered_type_()
  {
    std::cout << "\t" << typeid(T).name() << "\n";
    return;
  }

  /**\brief Functor that gets values for non-callable types. */
  template <typename T /*,
    typename std::enable_if<!ristra::is_callable<T>::value,int>::type = 0*/>
  struct value_getter {
    T & operator()(str_cr_t target_name, input_engine_t & inp)
    {
      registry<T> & reg(inp.get_registry<T>());
      typename registry<T>::iterator pv(reg.find(target_name));
      if (pv == reg.end()) {
        // TODO figure out what to do if lookup fails
        std::stringstream errstr;
        errstr << "input_engine_t::get_value: invalid key " << target_name
               << "; type = " << typeid(T).name();
        throw std::domain_error(errstr.str());
      }
      return pv->second;
    } // operator()
  }; // struct value_getter

  /**\brief Functor that gets value for std::function objects. */
  template <class Ret, class... Args>
  struct value_getter<std::function<Ret(Args...)>> {
    using func_t = std::function<Ret(Args...)>;

    func_t operator()(str_cr_t target_name, input_engine_t & inp)
    {
      registry<func_t> & hc_registry(inp.get_registry<func_t>());
      typename registry<func_t>::iterator pv(hc_registry.find(target_name));
      if (pv == hc_registry.end()) {
        // TODO figure out what to do if lookup fails
        std::stringstream errstr;
        errstr << "input_engine_t::get_value: invalid key " << target_name;
        throw std::domain_error(errstr.str());
      }
      return pv->second;
    } // get_value<std::function>
  }; // struct value_getter<std::function>

  /**\brief Resolve the targets for any one particular type.
   *
   * Written as a struct to enable us to partially specialize.
   * \return true if all targets for T resolved.
   */
  template <class T, size_t /*I*/>
  struct resolve_inputs_ {
    bool operator()(input_engine_t & inp, lua_source_ptr_t & lua_source,
      hard_coded_source_ptr_t & hard_coded_source)
    {
      // temp:
      target_set_t & targets(inp.get_target_set<T>());
      registry<T> & the_registry(inp.get_registry<T>());
      failed_set_t & failures(inp.get_failed_target_set<T>());
      bool missed_any(false);
      for (auto target : targets) {
        bool found_target(false);
        T tval = T();
        // try to find in the Lua source, if there is one
        if (lua_source) {
          found_target = lua_source->get_value(target, tval);
          if (found_target) {
            the_registry[target] = std::move(tval);
            continue;
          }
        }
        // not there? no Lua file? Default to hard coded source
        if (hard_coded_source) {
          found_target = hard_coded_source->get_value(target, tval);
          if (found_target) {
            the_registry[target] = std::move(tval);
            continue;
          }
        }
        missed_any = true;
        failures.insert(target);
      } // for(target : targets)
      bool found_all = !missed_any;
      if (found_all) {
        input_registry<T>::instance().set_all_resolved();
      }
      input_registry<T>::instance().set_resolve_called();
      return found_all;
    } // resolve
  }; // struct resolve_inputs_

  static string_t mk_lua_func_name(string_t const & t) { return "lua_f_" + t; }

  /*\\brief Specialization for std::function
   *
   * How Lua functions are kept in the registry: the lua_source_t class returns
   * a unique_ptr to a lua_result_t. The latter is the lowest level Ristra
   * representation of the Lua function. resolve_inputs_ wraps the lua_result_t
   * in a Lua_Func_Wrapper object, converting the unique_ptr to a shared_ptr
   * to enable copying. The Lua_Func_Wrapper makes sure that the lua_result_t
   * has the appropriate lifetime. Finally, resolve_inputs_ hands the
   * Lua_Func_Wrapper instance to a std::function object, ensuring type
   * uniformity with functions from other languages.
   */
  template <typename Ret_T, typename... Args, size_t I>
  struct resolve_inputs_<std::function<Ret_T(Args...)>, I> {
    using func_t = std::function<Ret_T(Args...)>;

    bool operator()(input_engine_t & inp, lua_source_ptr_t & lua_source,
      hard_coded_source_ptr_t & hard_coded_source)
    {
      target_set_t & targets(inp.get_target_set<func_t>());
      registry<func_t> & hc_registry(inp.get_registry<func_t>());
      failed_set_t & failures(inp.get_failed_target_set<func_t>());
      bool missed_any(false);
      for (auto target : targets) {
        bool found_target(false);
#ifdef RISTRA_ENABLE_LUA
        if (lua_source) {
          embedded::lua_result_uptr_t tval;
          found_target = lua_source->get_value(target, tval);
          if (found_target) {
            embedded::Lua_Func_Wrapper<func_t> lua_f(std::move(tval));
            func_t cpp_f(lua_f);
            hc_registry[target] = cpp_f;
            continue;
          } // if lua found
        } // if lua
#endif // RISTRA_ENABLE_LUA
        // next try hard-coded (default) case
        if (hard_coded_source) {
          func_t f;
          found_target = hard_coded_source->get_value(target, f);
          if (found_target) {
            // auto ins_pr =
            hc_registry.insert(std::make_pair(target, f));
            // bool inserted = ins_pr.second;
            // Could have some error checking on whether the thing was
            // inserted: if it weren't, that might mean this key is already
            // inhabited, and that would be unexpected.
            continue;
          }
        }
        missed_any = true;
        failures.insert(target);
      } // for target in targets
      bool found_all = !missed_any;
      if (found_all) {
        input_registry<func_t>::instance().set_all_resolved();
      }
      input_registry<func_t>::instance().set_resolve_called();
      return found_all;
    }
  }; // resolve_inputs for std::function

  /**\brief Resolve one target for given particular type.
   *
   * Written as a struct to enable us to partially specialize.
   * \return true if target resolved.
   */
  template <class T>
  struct resolve_input_ {
    bool operator()(string_t const & target, input_engine_t & inp,
      lua_source_ptr_t & lua_source,
      hard_coded_source_ptr_t & hard_coded_source)
    {
      registry<T> & the_registry(inp.get_registry<T>());
      bool found_target(false);
      T tval = T();
      // try to find in the Lua source, if there is one
      if (lua_source) {
        found_target = lua_source->get_value(target, tval);
        if (found_target) {
          the_registry[target] = std::move(tval);
        }
      }
      // not there? no Lua file? Default to hard coded source
      if (!found_target && hard_coded_source) {
        found_target = hard_coded_source->get_value(target, tval);
        if (found_target) {
          the_registry[target] = std::move(tval);
        }
      }
      return found_target;
    } // operator()
  }; // struct resolve_input_

  /*\\brief Specialization for std::function
   *
   * How Lua functions are kept in the registry: the lua_source_t class returns
   * a unique_ptr to a lua_result_t. The latter is the lowest level Ristra
   * representation of the Lua function. resolve_input_ wraps the lua_result_t
   * in a Lua_Func_Wrapper object, converting the unique_ptr to a shared_ptr
   * to enable copying. The Lua_Func_Wrapper makes sure that the lua_result_t
   * has the appropriate lifetime. Finally, resolve_input_ hands the
   * Lua_Func_Wrapper instance to a std::function object, ensuring type
   * uniformity with functions from other languages.
   */
  template <typename Ret_T, typename... Args>
  struct resolve_input_<std::function<Ret_T(Args...)>> {
    using func_t = std::function<Ret_T(Args...)>;

    bool operator()(str_cr_t target, input_engine_t & inp,
      lua_source_ptr_t & lua_source,
      hard_coded_source_ptr_t & hard_coded_source)
    {
      registry<func_t> & hc_registry(inp.get_registry<func_t>());
      bool found_target(false);
#ifdef RISTRA_ENABLE_LUA
      if (lua_source) {
        embedded::lua_result_uptr_t tval;
        found_target = lua_source->get_value(target, tval);
        if (found_target) {
          embedded::Lua_Func_Wrapper<func_t> lua_f(std::move(tval));
          func_t cpp_f(lua_f);
          hc_registry[target] = cpp_f;
        } // if lua found
      } // if lua
#endif
      // if not there, or no there there, next try hard-coded (default) case
      if (!found_target && hard_coded_source) {
        func_t f;
        found_target = hard_coded_source->get_value(target, f);
        if (found_target) {
          hc_registry.insert(std::make_pair(target, f));
        }
      }
      return found_target;
    } // operator()
  }; // resolve_input_ for std::function


 private:
  // state
  lua_source_ptr_t m_lua_source;
  hard_coded_source_ptr_t m_hard_coded_source;
}; // class inputs_t

} // ristra::

// End of file
