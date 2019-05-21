// init_value.h
// Aug 29, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#pragma once

#include "ristra/assertions/dbc.h"
#include "ristra/assertions/errors.h"
#include "ristra/utils/type_traits.h"
#include <string>

namespace ristra
{
/**\brief Status cues for initialization values */
enum class init_val_status_t : uint32_t {
  unregistered = 0, /*!< not registered with input_engine (??) */
  registered = 1, /*!< registered, not yet resolved */
  resolve_failed = 2, /*!< resolution failed, or not yet attempted */
  initialized = 3, /*!< resolution succeeded */
  invalid = 4, /*!< ^^ and was not valid */
  valid = 5 /*!< ^^ and value was valid */
};

inline std::string init_val_status_name(init_val_status_t const & s);

/**\class init_value_t: a value that needs to be supplied at the beginning of a
 * simulation
 *
 * This allows one to easily declare an initialization value, without
 * worrying about the input_engine. The init_value_t instance will delegate to
 * the input_engine.
 */
template <typename T, typename input_engine>
class init_value_t
{
 public:
  // types

  using validator = std::function<bool(T const &)>;
  using string_t = std::string;
  using str_cr_t = string_t const &;
  using status_t = init_val_status_t;
  using get_return_t =
    typename std::conditional<utils::is_callable<T>::value, T, T &>::type;

  // interface
  /**\brief get a reference to the value if that's possible.
   *
   * \return: non-callable type: T& , callable type: T&&
   *
   * If the init_value_t was resolve_failed by the input_engine, or if an
   * invalid
   * value was provided, an exception will be thrown.
   *
   * You can check whether the init_value_t was resolved without exception by
   * first invoking resolved().
   */
  get_return_t get()
  {
    // to do: if checks prove expensive, re-use possible earlier checks
    // by re-ordering the logic here.
    // e.g. if(m_status == status_t::valid) return ie.get_value<T>(fname); etc.
    input_engine ie;
    string_t fname(full_name());
    if (status_t::registered == m_status) {
      // still just at registered: check if it was resolved
      bool resolved = ie.template resolved<T>(fname);
      m_status = resolved ? status_t::initialized : status_t::resolve_failed;
      if (status_t::resolve_failed == m_status) {
        Insist(false,
          "Failed to resolve init_value " + m_name + " in namespace " +
            m_namespace);
      }
    }
    get_return_t t(ie.template get_value<T>(fname));
    bool valid(m_valid(t));
    if (!valid) {
      m_status = status_t::invalid;
      THROW_RUNTIME_ERROR("Invalid init_value " + fname);
    }
    m_status = status_t::valid;
    return t;
  }

  status_t const & status() const { return m_status; }

  /**\brief Has this init_value been resolved?
   * Does not throw.*/
  bool resolved()
  {
    Require(m_status > status_t::unregistered, "");
    input_engine ie;
    bool resolved = ie.template resolved<T>(full_name());
    if (resolved) {
      m_status = status_t::initialized;
    }
    return resolved;
  }

  /**\brief Was a valid */
  bool valid() const
  {
    if (status_t::valid == m_status) {
      return true;
    }
    if (status_t::invalid == m_status) {
      return false;
    }
    bool reslvd = resolved();
    if (!reslvd) {
      return false;
    }
    input_engine ie;
    T & t(ie.template get_value<T>(full_name()));
    bool valid = m_valid(t);
    m_status = valid ? status_t::valid : status_t::invalid;
    return valid;
  }

  // meta
  /**\brief Constructor
   * \param name: name
   * \param namespace: (optional) namespace for this parameter
   * \param validator: (optional) function to decide if the init value is valid
   *
   * Note: the validator is applied the first time get() is invoked.
   */
  init_value_t(str_cr_t name, validator val = [](T const &) { return true; },
    str_cr_t nmspace = "")
    : m_name(name),
      m_namespace(nmspace),
      m_valid(val),
      m_status(status_t::unregistered)
  {
    this->register_val();
  }

 private:
  // implementation
  void register_val()
  {
    input_engine ie;
    ie.template register_target<T>(full_name());
    m_status = status_t::registered;
    return;
  }

  string_t full_name() const
  {
    if (!m_namespace.empty()) {
      return m_namespace + ":" + m_name;
    }
    return m_name;
  }

  // state
  string_t m_name;
  string_t m_namespace;
  validator m_valid;
  status_t m_status;
}; // struct init_value_t

inline std::string init_val_status_name(init_val_status_t const & s)
{
  std::string str;
  using s_t = init_val_status_t;
  switch (s) {
    case s_t::unregistered:
      str = "unregistered";
      break;
    case s_t::registered:
      str = "registered";
      break;
    case s_t::resolve_failed:
      str = "resolve_failed";
      break;
    case s_t::initialized:
      str = "initialized";
      break;
    case s_t::invalid:
      str = "invalid";
      break;
    case s_t::valid:
      str = "valid";
      break;
    default:
      str = "unknown";
  };
  return str;
} // init_val_status_name

} // ristra::

// End of file
