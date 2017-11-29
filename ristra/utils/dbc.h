// dbc.hh
// Header for design by contract assertions
// (c) Copyright 2011-7 LANSLLC all rights reserved.

#pragma once

#define IM_OK_TO_INCLUDE_DBC_IMPL
#include "ristra/utils/detail/dbc_impl.h"
#undef IM_OK_TO_INCLUDE_DBC_IMPL
#include <functional>
#include <sstream>
#include <string>

/**\file
 *
 * \brief Design By Contract (DBC) assertions.
 *
 *  Derived from the Draco DBC system.
 *
 *  This header provides several generic design-by-contract macros:
 *  * Require: Assert precondition is true.
 *  * Check: Invariant within function call
 *  * Ensure: Assert postcondition
 *  * Insist: Always on macro assertion
 *
 *  Additional useful assertions are supplied:
 *  *    Equal(x,y): (x == y)
 *  *    InOpenRange(x,min,max): x > min && x < max
 *  *    GreaterThan(x,min): x > min
 *  *    GreaterEqual(x,min): x >= min
 *  *    LessThan(x,max): x < max
 *
 *  The behavior of failing any of these assertions can be tuned to
 *  * throw an exception,
 *  * write a message to std::err, or
 *  * return a bool
 *
 *  Behavior is contolled by RISTRA_DBC_ACTION and RISTRA_REQUIRE_ON
 *  in the build system.
 *
 *  Set RISTRA_DBC_ACTION={throw, notify, nothing} to set the
 *  DBC action.
 *
 *  Set RISTRA_REQUIRE_ON=1 to enable Require, Check, and Ensure.
 *
 *  Note that Insist is always on. Probably not good in inner loops, etc. It's
 *  for the things that absolutely must always be true.
 */

namespace ristra
{
namespace dbc
{
// Possible DBC actions
inline void throw_exception(std::string const & cond, const char * file_name,
  const char * func_name, int line)
{
  std::string msg(build_message(cond, file_name, func_name, line));
  throw std::logic_error(msg);
} // throw_exception

inline void notify(std::string const & cond, const char * file_name,
  const char * func_name, int line)
{
  std::ostream & s(*p_str);
  s << build_message(cond, file_name, func_name, line);
  return;
} // notify

inline void do_nothing(std::string const &, const char *, const char *, int)
{
  // printf("%s:%i \n",__FUNCTION__,__LINE__);
}


namespace
{
#ifdef RISTRA_DBC_THROW
action_t dbc_action(throw_exception);
#elif defined RISTRA_DBC_NOTIFY
action_t dbc_action(notify);
#else
action_t dbc_action(do_nothing);
#endif // RISTRA_DBC_THROW
} // anonymous::

/**\brief assert that a == b. Give names for a and b. */
template <class eq_t>
inline bool equal_func(eq_t const & a, eq_t const & b, char const * a_name_cstr,
  char const * b_name_cstr, const char * file_name, const char * func_name,
  int line)
{
  auto gen = [&]() {
    std::string const a_name(a_name_cstr);
    std::string const b_name(b_name_cstr);
    std::string const errstr(a_name + " != " + b_name);
    return errstr;
  };
  bool cond = a == b;
  assertf_l(cond, gen, file_name, func_name, line, dbc_action);
  return cond;
} // equal_func

/**\brief min < x < max */
template <typename comp_t>
inline bool in_open_range_func(comp_t const & x, comp_t const & min,
  comp_t const & max, char const * const name, const char * file_name,
  const char * func_name, int line)
{
  auto gen = [&]() {
    std::stringstream errstr;
    errstr << name << " (" << x << ") was not in range (" << min << "," << max
           << ")";
    return errstr.str();
  };
  bool cond = x > min && x < max;
  assertf_l(cond, gen, file_name, func_name, line, dbc_action);
  return cond;
} // InOpenRange

template <typename gt_t>
inline bool greater_than_func(gt_t const & x, gt_t const & min,
  char const * name, const char * file_name, const char * func_name, int line)
{
  bool cond = x > min;
  auto gen = [&]() {
    std::stringstream errstr;
    errstr << name << " (" << x << ") <= " << min;
    return errstr.str();
  };
  assertf_l(cond, gen, file_name, func_name, line, dbc_action);
  return cond;
} // GreaterThan

template <typename gt_t>
inline bool greater_equal_func(gt_t const & x, gt_t const & min,
  char const * name, const char * file_name, const char * func_name, int line)
{
  bool cond = x >= min;
  auto gen = [&]() {
    std::stringstream errstr;
    errstr << name << " (" << x << ") < " << min;
    return errstr.str();
  };
  assertf_l(cond, gen, file_name, func_name, line, dbc_action);
  return cond;
} // GreaterEqual

template <typename gt_t>
inline bool less_than_func(gt_t const & x, gt_t const & min, char const * name,
  const char * file_name, const char * func_name, int line)
{
  bool cond = x < min;
  auto gen = [&]() {
    std::stringstream errstr;
    errstr << name << " (" << x << ") >= " << min;
    return errstr.str();
  };
  assertf_l(cond, gen, file_name, func_name, line, dbc_action);
  return cond;
} // GreaterThan

} // dbc::
} // ristra::

#define Insist(c, cs)     \
  ::ristra::dbc::assertf( \
    c, cs, __FILE__, __FUNCTION__, __LINE__, ristra::dbc::dbc_action);

#ifdef RISTRA_REQUIRE_ON
/*! \def Require(condition,descriptive_string): Precondition assertion. */
#define Require(c, cs)    \
  ::ristra::dbc::assertf( \
    c, cs, __FILE__, __FUNCTION__, __LINE__, ristra::dbc::dbc_action);
/*! \def Check(condition,descriptive_string): Invariant assertion. */
#define Check(c, cs)      \
  ::ristra::dbc::assertf( \
    c, cs, __FILE__, __FUNCTION__, __LINE__, ristra::dbc::dbc_action);
/*! \def Ensure(condition,descriptive_string): Postcondition assertion. */
#define Ensure(c, cs)     \
  ::ristra::dbc::assertf( \
    c, cs, __FILE__, __FUNCTION__, __LINE__, ristra::dbc::dbc_action);
/*! \def Equal(x,y): Assert x == y */
#define Equal(a, b) \
  ::ristra::dbc::equal_func(a, b, #a, #b, __FILE__, __FUNCTION__, __LINE__);
/*! \def InOpenRange(x,min,max): Assert x > min && x < max */
#define InOpenRange(x, mn, mx)       \
  ::ristra::dbc::in_open_range_func( \
    x, mn, mx, #x, __FILE__, __FUNCTION__, __LINE__);
/*! \def GreaterThan(x,min): Assert x > min */
#define GreaterThan(x, mn) \
  ::ristra::dbc::greater_than_func(x, mn, #x, __FILE__, __FUNCTION__, __LINE__);
/*! \def GreaterEqual(x,min): Assert x >= min */
#define GreaterEqual(x, mn)          \
  ::ristra::dbc::greater_equal_func( \
    x, mn, #x, __FILE__, __FUNCTION__, __LINE__);
/*! \def LessThan(x,max): Assert x < max */
#define LessThan(x, mx) \
  ::ristra::dbc::less_than_func(x, mx, #x, __FILE__, __FUNCTION__, __LINE__);

#else // REQUIRE_ON

#define Require(c, cs)
#define Check(c, cs)
#define Ensure(c, cs)
#define Equal(a, b) ((a) == (b))
#define InOpenRange(x, mn, mx) ((x) > (mn) && (x) < (mx))
#define GreaterThan(x, mn) ((x) > (mn))
#define GreaterEqual(x, mn) ((x) >= (mn))
#define LessThan(x, mn) ((x) < (mn))

#endif // REQUIRE_ON

// End of file
