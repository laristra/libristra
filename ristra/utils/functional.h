/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file 
/// \brief Extends some functionality of the Functional library.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// system includes
#include <functional>

namespace ristra {
namespace utils {

////////////////////////////////////////////////////////////////////////////////
// Allow functional operators to work for two different argument types.  In
// the standard, the types of the left and right hand side objects have to be
// the same.
////////////////////////////////////////////////////////////////////////////////

//! \brief Addition operator.
//! \param [in] lhs,rhs   The objects on the left and right side of the 
//!                       operator
//! \return The result of `lhs + rhs`
template< class T, class U >
constexpr auto plus( T && lhs, U && rhs )
{ return std::forward<T>(lhs) + std::forward<U>(rhs); }

//! \brief Minus operator.
//! \param [in] lhs,rhs   The objects on the left and right side of the 
//!                       operator
//! \return The result of `lhs - rhs`
template< class T, class U >
constexpr auto minus( T && lhs, U && rhs )
{ return std::forward<T>(lhs) - std::forward<U>(rhs); }
 
//! \brief Multiplication operator.
//! \param [in] lhs,rhs   The objects on the left and right side of the 
//!                       operator
//! \return The result of `lhs * rhs`
template< class T, class U >
constexpr auto multiplies( T && lhs, U && rhs )
{ return std::forward<T>(lhs) * std::forward<U>(rhs); }

//! \brief Division operator.
//! \param [in] lhs,rhs   The objects on the left and right side of the 
//!                       operator
//! \return The result of `lhs / rhs`
template< class T, class U >
constexpr auto divides( T && lhs, U && rhs )
{ return std::forward<T>(lhs) / std::forward<U>(rhs); }


} // namespace
} //
