// static_warning.h
// T. M. Kelley
// Aug 25, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved


#pragma once

#include <type_traits>

// two steps give macros like __LINE__ a chance to be evaluated
#define RISTRA_CAT(x,y) RISTRA_CAT1(x,y)
#define RISTRA_CAT1(x,y) x##y
#define RISTRA_DECO(c,m) #c":"#m

/**\brief This is a klunky way of generating compile time messages.
 *
 * This can be useful in tracing the path through compile-time template
 * deduction and overload resolution. It should be useable at namespace
 * and function scope.
 *
 * It works by compile-time evaluating a condition: if the condition is false
 * then it invokes a deprecated method that does nothing. The deprecated
 * attribute is standard C++11/14; most compilers have a mechanism to print
 * out a warning.
 *
 * Use this sparingly: for example when actively debugging a template issue.
 */
#define static_warning(cond, msg)                \
  struct RISTRA_CAT(Static_warning,__LINE__) {                   \
    [[deprecated( (RISTRA_DECO(cond,msg)) )]] void warn(std::false_type const &) {}                \
    void warn(std::true_type const &) {}                  \
    RISTRA_CAT(Static_warning,__LINE__)() {                        \
      warn(std::integral_constant<bool, cond>::type{});     \
    }                                                     \
  }

// End of file
