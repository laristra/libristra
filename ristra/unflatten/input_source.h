// input_source.h
// T. M. Kelley
// May 08, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#pragma once

#include <array>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "ristra/detail/inputs_impl.h"
#include "ristra/lua_access.h"

namespace ristra
{
/**\TODO: review design. The registry idea is getting replicated in
 * several places. This can likely be cleaned up, perhaps with CRTP.
 */

/**\brief Interface for a source of input information. Goal is to permit
 * a container of sources. */
template <typename input_source_impl, typename real_ty = double,
  typename string_ty = std::string>
class input_source
{
 public:
  using string_t = string_ty;
  using str_cr_t = string_t const &;
  using real_t = real_ty;
  /**\TODO Need to clean up the function interfaces so that composite types
   * (like vectors) can be carried by the thing that parses/wraps functions. */
  template <uint32_t d>
  using vec = std::array<real_t, d>;
  template <uint32_t d>
  using ics_return_t = std::tuple<real_t, vec<d>, real_t>;
  template <uint32_t d>
  using ics_function_t =
    std::function<ics_return_t<d>(const vec<d> & x, const real_t & t)>;

 protected:
  // Hmmm...might be worth a base class:
  template <class T>
  struct data_registry {
    using registry = std::map<string_t, T>;
    data_registry() {}
    data_registry(data_registry &) = delete;
    data_registry(data_registry &&) = delete;
    void clear() { m_reg.clear(); }
    static data_registry & instance()
    {
      static data_registry m;
      return m;
    }
    registry & get_registry() { return m_reg; }
    registry m_reg;
  }; // data_registry

  /**\brief get value corr. to key
   * \return true if successfully found key.
   * \param[in] k: the key to look for
   * \param[out] t: reference to which value should be written */
  template <class T>
  bool get_value(str_cr_t k, T & t)
  {
    return static_cast<input_source_impl>(*this).get_value(k, t);
  }

  apply_void_f_by_tuple(clear_registry_);

  template <typename Tuple_T>
  void clear_registry()
  {
    clear_registry__by_tuple<Tuple_T>();
  }

  template <typename T, size_t I>
  void clear_registry_()
  {
    data_registry<T>::instance().clear();
  }

  virtual ~input_source() {}
}; // input_source

class hard_coded_source_t : public input_source<hard_coded_source_t>
{
  using base = input_source<hard_coded_source_t>;

 public:
  template <typename reg_t>
  using registry = std::map<string_t, reg_t>;
  template <class T>
  struct type_t {
  };

  template <class T>
  bool get_value(str_cr_t k, T & t)
  {
    auto & reg(get_registry<T>());
    auto it = reg.find(k);
    bool found(false);
    if (reg.end() != it) {
      t = std::move(it->second);
      found = true;
    }
    return found;
  } // get_value

  template <class T>
  void set_registry(registry<T> const & reg)
  {
    auto & this_reg(get_registry<T>());
    for (auto & v : reg) {
      this_reg[v.first] = v.second;
    }
  } // set_registry

  template <class T>
  registry<T> & get_registry()
  {
    return data_registry<T>::instance().get_registry();
  }

  template <class Tuple_T>
  void clear_registry()
  {
    base::clear_registry<Tuple_T>();
  }

}; // class hard_coded_source_t

using hard_coded_source_ptr_t = std::unique_ptr<hard_coded_source_t>;

inline hard_coded_source_ptr_t mk_hard_coded_source()
{
  return std::make_unique<hard_coded_source_t>();
} // mk_hard_coded_source

/**\brief Use a Lua file as input source.
 *
 Right now the Lua file structure is hard-coded here. Eventually we
 want to get the structure from some sort of description.

 The structure is maintained in several maps. Table map lists the entity
 in which each key is stored, whether it's a table or other data item.

 m_tables maintains the pointers to the actual tables.

 The base state of the lua file is a different type, so it's stored on its
 own. This offers a bit of complication in load_table.

 Finally, the lua tables act as namespaces, so there can be overlaps in the
 Lua names. We deal with this by optionally setting a key in the lua_keys
 map. If a C++ key is a key in the lua_keys map, then the corresponding value
 is used to query Lua. If not, then the C++ key is also the Lua key.
 */
class lua_source_t : public input_source<lua_source_t>
{
 public:
#ifdef HAVE_LUA
  using table_map_t = std::map<string_t, string_t>;
  using lua_keys_t = std::map<string_t, string_t>;
  using tables_t = std::map<string_t, lua_result_t>;

  explicit lua_source_t(str_cr_t filename) : m_lua_state(), m_filename(filename)
  {
    /* TODO Want this configuration to come from elsewhere. Maybe a traits
     * class, maybe generated from a description file. Not hard coded here. */
    m_lua_state.loadfile(filename);
    // where are tables located?
    m_table_map["hydro"] = "base_state";
    m_table_map["mesh"] = "hydro";
    load_table("hydro");
    load_table("mesh");

    // where are values located?
    m_table_map["prefix"] = "hydro";
    m_table_map["suffix"] = "hydro";
    m_lua_key["suffix"] = "postfix";
    m_table_map["output_freq"] = "hydro";
    m_table_map["CFL"] = "hydro";
    m_table_map["final_time"] = "hydro";
    m_table_map["max_steps"] = "hydro";

    m_table_map["mesh_type"] = "mesh";
    m_lua_key["mesh_type"] = "type";
    m_table_map["dimensions"] = "mesh";
    m_table_map["xmin"] = "mesh";
    m_table_map["xmax"] = "mesh";
    m_table_map["file"] = "mesh";

    m_lua_key["ics_func"] = "ics";
    m_table_map["ics_func"] = "hydro";
    return;
  } // ctor

  /**\brief Associate a key with a table.
   *
   * \param key: the key
   * \param p_name: parent table name (default: base_state)
   * \param lua_key: optional: different key to use in Lua files.
   *
   * \return: whether this registration displaced a previous definition
   */
  bool register_value(str_cr_t key, str_cr_t t_name, str_cr_t lua_key = "")
  {
    bool const will_replace = 0 < m_table_map.count(key);
    // if(will_replace){
    //   printf("%s:%i will replace %s in table map\n", __FUNCTION__, __LINE__,
    //     key.c_str());
    //   fflush(stdout);
    // }
    m_table_map[key] = t_name;
    if (!lua_key.empty()) {
      m_lua_key[key] = lua_key;
    }
    return will_replace;
  }

  /**\brief register a table with the lua_input, and load it.
   *
   * \param t_name: table name
   * \param p_name: parent table name (default: base_state)
   * \param lua_key: (optional) different key to use in Lua files.
   *
   * \return: whether this registration displaced a previous definition
   */
  bool register_table(
    str_cr_t t_name, str_cr_t p_name = "base_state", str_cr_t l_key = "")
  {
    bool const will_replace = register_value(t_name, p_name, l_key);
    load_table(t_name);
    return will_replace;
  } // register_table

  /**\brief get the length of the item associated with the key.
   *
   * \param key: the key to look up
   * Note: throws exception if key is not found */
  size_t get_size(str_cr_t key){
    size_t sz;
    str_cr_t l_key(1 == m_lua_key.count(key) ? m_lua_key[key] : key);
    bool found = true;
    // now recover the table to look in
    try {
      str_cr_t from_name = m_table_map.at(key);
      try {
        auto & from_table = m_tables.at(from_name);
        // use lua key (not arg key) in table
        auto lua_val = from_table[l_key];
        sz = lua_val.size();
      }  catch (std::exception & x) {
        printf("%s:%i Failed to find the table '%s' for the key '%s'\n",
          __PRETTY_FUNCTION__, __LINE__, from_name.c_str(),key.c_str());
        throw x;
      }
    } catch (std::exception & x) {
      printf("%s:%i Failed to find any table associated with key '%s'\n",
        __PRETTY_FUNCTION__, __LINE__, key.c_str());
      throw x;
    }
    return sz;
  } // get_size

  /**\brief Templated functor (thus specializable) to get values from Lua. */
  template <typename T>
  struct value_getter {
    bool get_value(str_cr_t k, T & t, lua_source_t & ls)
    {
      // check if there is a Lua key distinct from k
      str_cr_t l_key(1 == ls.m_lua_key.count(k) ? ls.m_lua_key[k] : k);
      bool found = true;
      // now recover the table to look in
      try {
        str_cr_t from_name = ls.m_table_map.at(k);
        try {
          auto & from_table = ls.m_tables.at(from_name);
          // use lua key (not arg key) in table
          auto lua_val = from_table[l_key];
          if (lua_val.empty()) {
            found = false;
          }
          if (found) {
            t = lua_val.as<T>();
          }
        } catch (std::exception & x) {
          printf("%s:%i Failed to find table '%s'\n", __PRETTY_FUNCTION__,
            __LINE__, from_name.c_str());
          throw x;
        }
      } catch (std::exception & x) {
        printf("%s:%i Failed to find table associated with key '%s'\n",
          __PRETTY_FUNCTION__, __LINE__, k.c_str());
        throw x;
      }
      return found;
    }
  }; // struct value_getter

  // see below for specialization returning lua_result_t...
  template <typename T>
  bool get_value(str_cr_t f, T & t)
  {
    value_getter<T> g;
    return g.get_value(f, t, *this);
  }

  /**\brief Get direct access to a Lua table. */
  lua_result_t &get_table(str_cr_t table_name){
    // Two steps to lookup: first get the name of the
    try {
      lua_result_t & from_table = m_tables.at(table_name);
      return from_table;
    } catch (std::exception & x) {
      printf("%s:%i Failed to find table named '%s'\n",
        __PRETTY_FUNCTION__, __LINE__, table_name.c_str());
      throw x;
    }
  } // get_table

  /**\brief Get a raw lua_result_t. */
  std::pair<bool, lua_result_t> get_lua_result_raw(str_cr_t k)
  {
    // check if there is a Lua key distinct from k
    str_cr_t l_key(1 == m_lua_key.count(k) ? m_lua_key[k] : k);
    // now recover the table to look in
    str_cr_t from_name = m_table_map.at(k);
    auto & from_table = m_tables.at(from_name);
    // use lua key in table
    bool found = true;
    lua_result_t lua_result = from_table[l_key];
    if (lua_result.empty()) {
      found = false;
    }
    return std::make_pair(found, lua_result);
  } // get_lua_result_raw

 private:
  void load_table(str_cr_t load_name)
  {
    str_cr_t from_name = m_table_map[load_name];
    if ("base_state" == from_name) {
      m_tables.emplace(load_name, lua_try_access(m_lua_state, load_name));
    } else {
      lua_result_t & from_state = m_tables.at(from_name);
      m_tables.emplace(load_name, lua_try_access(from_state, load_name));
    }
    // printf("%s:%i Loaded table
    // '%s'\n",__FUNCTION__,__LINE__,load_name.c_str());
    return;
  }

  lua_t m_lua_state;
  string_t m_filename;
  table_map_t m_table_map;
  tables_t m_tables;
  lua_keys_t m_lua_key;

#else // no lua
  explicit lua_source_t(str_cr_t) {}

  template <class T>
  bool get_value(str_cr_t /*k*/, T & /*t*/)
  {
    return false;
  }
#endif // HAVE_LUA
}; // lua_source_t

// specialization for lua_result_t (i.e. Lua function ptr): convert
// lua_result_t value to a unique_ptr
template <>
struct lua_source_t::value_getter<lua_result_uptr_t> {
  bool get_value(str_cr_t k, lua_result_uptr_t & t, lua_source_t & ls)
  {
    // check if there is a Lua key distinct from k
    str_cr_t l_key(1 == ls.m_lua_key.count(k) ? ls.m_lua_key[k] : k);
    // now recover the table to look in
    str_cr_t from_name = ls.m_table_map.at(k);
    auto & from_table = ls.m_tables.at(from_name);
    // use lua key in table
    bool found = true;
    auto lua_val = from_table[l_key];
    if (lua_val.empty()) {
      found = false;
    }
    if (found) {
      t = std::make_unique<lua_result_t>(lua_val);
    }
    return found;
  }
};

using lua_source_ptr_t = std::unique_ptr<lua_source_t>;

/**\brief */
inline lua_source_ptr_t mk_lua(lua_source_t::str_cr_t filename)
{
  return std::make_unique<lua_source_t>(filename);
}

} // ristra::

// End of file
