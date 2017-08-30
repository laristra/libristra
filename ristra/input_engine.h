// inputs.h
// May 08, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#pragma once

#include "ristra/detail/inputs_impl.h"
#include "ristra/input_source.h"
#include "ristra/detail/type_utils.h"

#include <algorithm>  // all_of
#include <array>
#include <deque>
#include <iterator>
#include <map>
#include <memory>
#include <numeric> // accumulate
#include <set>
#include <sstream>
#include <string>
#include <typeinfo>
#include "unistd.h"

namespace ristra{

/**\brief Class to register and resolve application inputs (no RTTI required).
 *
 * \tparam input_traits: structure that defines a number of types, including
 * mesh, ics_return_t (return type of initial conditions function),
 * ics_function_t (initial condition function type), a callable wrapper to
 * ics_function_t (marshalls data to/from the initial condition function),
 *
 * inputs_t is defined with a virtual destructor; this enables clients to
 * inherit from it and change the accessibility of various functionality.
 *
 * A key enabler of inputs_t is the input_registry<T> class. This allows
 * the class to have a typed key-value store without type erasure. No RTTI
 * is used to do this. While input_t<traits> is not a singleton, its registries
 * are singletons.
 *
 * To operate the class, one registers targets and one or more input sources.
 * Targets are strings that will be resolved from the input source(s). Currently,
 * there is support for a Lua source and a hard-coded C++ source. In the future,
 * we expect this to increase to Python, SQL, and (perhaps) multiple sources of
 * any given type.
 *
 * Note that inputs are distinguished by name and type. That is, an int32_t
 * target named "foo" is considered different from a uint32_t named "foo".
 *
 * The current resolution priority is Lua file, then hard-coded source.
 */
template <class input_traits>
class input_engine_t {
public:
  using traits_t = input_traits;
  using type_tuple = typename input_traits::types;
  using real_t = typename input_traits::real_t;

  using vector_t = typename input_traits::vector_t;
  using string_t = std::string;
  using str_cr_t = string_t const &;
  using ics_return_t = typename input_traits::ics_return_t;
  using ics_function_t = typename input_traits::ics_function_t;
  using ics_wrapper_t = typename input_traits::Lua_ICS_Func_Wrapper;
  using ics_uptr_t = std::unique_ptr<ics_wrapper_t>;
  using target_set_t = std::set<string_t>;
  using failed_set_t = std::set<string_t>;
  using deq_bool = std::deque<bool>;
  template <class reg_t> using registry = std::map<string_t,reg_t>;

  /**\brief Used only for type-switching in explicit specializations. */
  template <typename T> struct type_t{};

  static constexpr size_t tsize = std::tuple_size<type_tuple>::value;

protected:
  /**\brief A class for registering targets, associating resolved data and
   * targets, and recording failures associated with a given type.
   *
   * \tparam T: The type of the target data
   */
  template <class T>
  struct input_registry{
    using key_t = std::string;
    using data_t = std::map<key_t,T>;
    using target_set_t = std::set<key_t>;
    using failed_set_t = std::set<key_t>;

    registry<T> & get_data_registry(){ return m_reg;}

    target_set_t & get_target_set() { return m_targets; }

    failed_set_t &get_failed_set(){return m_failures;}

    registry<T> m_reg;
    target_set_t m_targets;
    failed_set_t m_failures;

    void clear(){
      m_reg.clear();
      m_targets.clear();
      m_failures.clear();
    }

    // singleton for each type
    input_registry(){}
    input_registry(input_registry &) = delete;
    input_registry(input_registry&&) = delete;

  }; // registry

private:
  template <typename T>
  static input_registry<T>& instance(){
    static input_registry<T> m;
    return m;
  }

public:

// meta
  // generate calls to each function for all types via std::tuple.
  apply_op_f_by_tuple(resolve_inputs_);
  apply_void_f_by_tuple(clear_registry_);
  apply_void_f_by_tuple(print_unresolved_types_);
  apply_void_f_by_tuple(define_type_names_);

  input_engine_t(){
    define_type_names__by_tuple<type_tuple>();
  }

  virtual ~input_engine_t(){}

  /**\brief Clear all registered targets on all types. */
  void clear_registry(){
    clear_registry__by_tuple<type_tuple>();
  }

// interface
  /**\\brief For each target, look through input sources and attempt
   * to resolve each target.
   *
   * \return whether all inputs for all types were successfully resolved.
   *
   * Always tries to find something in an external input file, then looks
   * in the hard-coded source. This makes the hard-coded source the
   * default.
   **/
  bool resolve_inputs(){
    m_resolve_called = true;
    deq_bool resolutions(resolve_inputs__by_tuple<type_tuple>(
      *this,m_lua_source,m_hard_coded_source));
    bool all_resolved = std::accumulate(
        resolutions.begin(), resolutions.end(), true,
        [](bool b1,bool b2) {return b1 && b2; });
    if(!all_resolved){
      print_unresolved_types__by_tuple<type_tuple>(resolutions);
    }
    m_all_resolved = all_resolved;
    return all_resolved;
  } // resolve_inputs

  /**\brief Register a Lua input source. This class will delete by default.
   *
   * \param lua_source Pointer to lua_source_t
   */
  void register_lua_source( lua_source_t * lua_source){
    m_lua_source.reset(lua_source);
    return;
  }

  /**\brief Register a hard coded input source. This class will delete
   * the source.
   *
   * \param hard_coded_source the hard_coded_source object
   */
  void register_hard_coded_source(hard_coded_source_t * hard_coded_source){
    m_hard_coded_source.reset(hard_coded_source);
  }

  /* Idea: derived class should call register_target for each thing it expects
   * from the input. */
  template <class T> // TODO add validators, defaults, etc.
  void register_target(str_cr_t name){
    target_set_t & target_set = get_target_set<T>();
    // TODO could have some error checking here: what if something gets
    // registered more than once, for example?
    auto p = target_set.insert(name);
    if(!p.second){
      printf("%s:%i failed to insert target '%s'\n", __FUNCTION__, __LINE__,
        name.c_str());
    }
    return;
  } // register_target

  template <class T> // TODO add validators, defaults, etc.
  void register_targets(target_set_t &names){
    for(auto & n : names){
      register_target<T>(n);
    }
    return;
  } // register_target

  /**\brief Get the value from the input process. */
  template <class T>
  T& get_value(str_cr_t target_name){
    registry<T> & reg(this->get_registry<T>());
    typename registry<T>::iterator pv(reg.find(target_name));
    if(pv == reg.end()){
      // TODO figure out what to do if lookup fails
      std::stringstream errstr;
      errstr << "input_engine_t::get_value: invalid key " << target_name;
      throw std::domain_error(errstr.str());
    }
    return pv->second;
  } // get_value

  ics_function_t get_ics_function(str_cr_t target_name){
    registry<ics_function_t> &hc_registry(get_registry<ics_function_t>());
    registry<lua_result_uptr_t> &lua_registry(
        get_registry<lua_result_uptr_t>());
    // check whether the result is in the Lua items registry
    string_t lua_target(mk_lua_func_name(target_name));
    typename registry<lua_result_uptr_t>::iterator plua_val(
        lua_registry.find(lua_target));
    bool is_lua(plua_val != lua_registry.end());
    if(is_lua){
      // get the lua_func_wrapper object, return std::function to it
      lua_result_t & lfunc(*(plua_val->second));
      typename input_traits::Lua_ICS_Func_Wrapper w(lfunc);
      ics_function_t f(w);
      return std::move(f);
    }
    // If not, look for it in the hard-coded items registry
    typename registry<ics_function_t>::iterator pv(
        hc_registry.find(target_name));
    if(pv == hc_registry.end()){
      // TODO figure out what to do if lookup fails
      std::stringstream errstr;
      errstr << "input_engine_t::get_value: invalid key " << target_name;
      throw std::domain_error(errstr.str());
    }
    return pv->second;
  } // get_value

  /**\brief indicate whether a target was resolved */
  template <class T>
  bool resolved(str_cr_t target) const {
    if(!m_resolve_called){
      return false; // shd be error ?!?
    }
    // if the target is in the set of failures, then it was not resolved.
    registry<T> const & el_reg(get_registry<T>());
    return (1 == el_reg.count(target));
  }

protected:
  template <class T>
  registry<T> & get_registry(){
    return instance<T>().get_data_registry();
  }

  template <class T>
  registry<T> const & get_registry() const {
    return instance<T>().get_data_registry();
  }

  template <class T>
  target_set_t & get_target_set(){
    return instance<T>().get_target_set();
  }

  template <class T>
  target_set_t & get_failed_target_set(){
    return instance<T>().get_failed_set();
  }

  /**\brief Clear all registered targets on type T. */
  template <typename T, size_t I>
  void clear_registry_(){
    instance<T>().clear();
  }

  template <class T, size_t I>
  void define_type_names_(){
    m_type_names[I] = typeid(T).name();
  }

  /**\brief If resolution failed for this type (at index I), print out some
   * information about that.
   */
  template <class T, size_t I>
  void print_unresolved_types_(deq_bool const &resolutions){
    bool const resolved(resolutions[I]);
    failed_set_t const &failures(get_failed_target_set<T>());
    if(!resolved){
      std::cout << "Did not resolve all targets for type "
        << m_type_names[I]
        << ". Unresolved targets: ";
      std::copy(failures.begin(), failures.end(),
                std::ostream_iterator<string_t>(std::cout, ","));
      std::cout << std::endl;
    }
    return;
  } // print_unresolved_types_

  /**\brief Resolve the targets for any one particular type.
   *
   * \return true if all targets for T resolved. */
  template <class T, size_t I>
  struct resolve_inputs_{
    bool operator()(input_engine_t & inp, lua_source_ptr_t &lua_source,
      hard_coded_source_ptr_t & hard_coded_source){
      // temp:
      target_set_t &targets(inp.get_target_set<T>());
      registry<T> &registry(inp.get_registry<T>());
      failed_set_t &failures(inp.get_failed_target_set<T>());
      bool missed_any(false);
      for(auto target : targets){
        bool found_target(false);
        T tval = T();
        // try to find in the Lua source, if there is one
        if(lua_source){
            lua_source.get();
          found_target = lua_source->get_value(target,tval);
          if(found_target){
            registry[target] = std::move(tval);
            continue;
          }
        }
        // not there? no Lua file? Default to hard coded source
        if(hard_coded_source){
          found_target = hard_coded_source->get_value(target,tval);
          if(found_target){
            registry[target] = std::move(tval);
            continue;
          }
        }
        missed_any = true;
        failures.insert(target);
      } // for(target : targets)
      bool found_all = !missed_any;
      return found_all;
    } // resolve
  }; // struct resolve_inputs_

  static string_t mk_lua_func_name(string_t const &t){
    return "lua_f_" + t;
  }

  /* Specialization for initial conditions functions. */
  template <size_t I>
  struct resolve_inputs_<ics_function_t, I>{
    bool operator()(input_engine_t &inp, lua_source_ptr_t &lua_source,
               hard_coded_source_ptr_t &hard_coded_source) {

      // This is a bit more complex: we're going to store either
      // a std::function that wraps a hard-coded function, or a
      // lua wrapper object. So we will have multiple registries.

      target_set_t &targets(inp.get_target_set<ics_function_t>());
      registry<ics_function_t> &hc_registry(inp.get_registry<ics_function_t>());
      registry<lua_result_uptr_t> &lua_registry(
          inp.get_registry<lua_result_uptr_t>());
      failed_set_t &failures(inp.get_failed_target_set<ics_function_t>());

      bool missed_any(false);
      for(auto target : targets){
        bool found_target(false);
        if(lua_source){
          /* If the Lua module provides a function, put a unique_ptr to
           * the Lua result into a registry. get_ics_function will handle
           * wrapping that u_ptr in a callable object that marshals the data.*/
          lua_result_uptr_t tval;
          found_target = lua_source->get_value(target,tval);
          if(found_target){
            string_t lua_target(mk_lua_func_name(target));
            lua_registry[lua_target] = std::move(tval);
            continue;
          } // if lua found
        }// if lua
        // next try hard-coded case
        if(hard_coded_source){
          ics_function_t f;
          found_target = hard_coded_source->get_value(target,f);
          if(found_target){
            hc_registry[target] = f;
            continue;
          }
        }
        missed_any = true;
        failures.insert(target);
      } // for target in targets
      bool found_all = !missed_any;
      return found_all;
    }
  }; // resolve_inputs for ics_function

  // template <class R, class... Args, size_t I>
  // struct resolve_inputs_<std::function<R(Args...)>, I>{

  //   bool operator()(inputs_t &inp, lua_source_ptr_t &lua_source,
  //              hard_coded_source_ptr_t &hard_coded_source) {
  //     using Func_T = std::function<R(Args...)>;
  //     target_set_t &targets(inp.get_target_set<Func_T>());
  //     registry<Func_T> &registry(inp.get_registry<Func_T>());
  //     failed_set_t &failures(inp.get_failed_target_set<Func_T>());
  //     bool missed_any(false);
  //     /* alright, the trick here is to look in various places for
  //     * a function object, wrapping each in a std::function, along
  //     * with argument matching. shew.
  //     */
  //     for(auto target : targets){
  //       bool found_target(false);
  //       if(lua_source){
  //         lua_result_uptr_t tval;
  //         found_target = lua_source->get_value(target,tval);
  //       }
  //       if(found_target){
  //         // need to generate a wrapper to the Lua function. We'll
  //         // assume (HAH!) that the function type we were instantiated
  //         // with is a reasonable representation of the lua signature
  //         // expect that we'll expect arrays on the C++ side to be
  //         // unpacked to scalars on the Lua side. What could possibly go wrong?

  //       }
  //     } // for target in targets
  //     bool found_all = !missed_any;
  //     return found_all;
  //   }
  // }; // resolve_inputs for std::function

private:
  // state
  lua_source_ptr_t m_lua_source;
  hard_coded_source_ptr_t m_hard_coded_source;
  std::array<bool,tsize> m_registered;
  std::array<string_t,tsize> m_type_names;
  bool m_resolve_called = false;
  bool m_all_resolved = false;
}; // class inputs_t

//
//// specialization for initial conditions functions
//template <>
//template <class I> //, class F = typename I::ics_function_t>
//struct inputs_t<I>::value_getter<typename I::ics_function_t>{
//
//  ics_function_t &operator()(str_cr_t target_name){
//    registry<ics_function_t> &hc_registry(inp.get_registry<ics_function_t>());
//    registry<ics_uptr_t> &lua_registry(inp.get_registry<ics_uptr_t>());
//
//    string_t lua_target(mk_lua_func_name(target));
//    registry<ics_uptr_t>::iterator plua_val(lua_registry.find(lua_target));
//    bool is_lua(plua_val != lua_registry.end());
//    if(is_lua){
//      // get the lua_func_wrapper object, return std::function to it
//      ics_uptr_t &plua_wrapper(plua_val->second);
//      return ics_function_t(*plua_wrapper);
//    }
//    registry<ics_function_t>::iterator pv(hc_registry.find(target_name));
//    if(pv == reg.end()){
//      // TODO figure out what to do if lookup fails
//      std::stringstream errstr;
//      errstr << "inputs_t::get_value: invalid key " << target_name;
//      throw std::domain_error(errstr.str());
//    }
//    return pv->second;
//  } // get_value
//
//};


///*template <class input_user>
//class inputs_t {*/
//  template <class input_user>
//  bool inputs_t<input_user>::<class R, class ...Args> resolve_inputs_<std::function<R(Args...)>, size_t I>(){
//    // temp:
//    // target_set_t &targets(get_target_set<T>());
//    // registry<T> &registry(get_registry<T>());
//    // failed_set_t &failures(get_failed_target_set<T>());
//    // bool missed_any(false);
//    // for(auto target : targets){
//    //   bool found_target(false);
//    //   T tval = T();
//    //   // try to find in the Lua source, if there is one
//    //   if(m_lua_source){
//    //     found_target = m_lua_source->get_value(target,tval);
//    //   }
//    //   if(found_target){
//    //     registry[target] = std::move(tval);
//    //     continue;
//    //   }
//    //   // not there? no Lua file? Default to hard coded source
//    //   if(m_hard_coded_source){
//    //     found_target = m_hard_coded_source->get_value(target,tval);
//    //   }
//    //   if(found_target){
//    //     registry[target] = std::move(tval);
//    //   }
//    //   else{
//    //     missed_any = true;
//    //     failures.insert(target);
//    //   }
//    // } // for(target : targets)
//    // return !missed_any;
//    return false;
//  } // resolve_inputs_


} // ristra::

// End of file
