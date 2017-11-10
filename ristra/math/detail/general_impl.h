/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Provides a default operators for fundamental types.
////////////////////////////////////////////////////////////////////////////////

#pragma once

// system includes
#include <utility>

namespace flecsi {
namespace sp {
namespace math {
namespace detail {


////////////////////////////////////////////////////////////////////////////////
//! \brief Template helpers to compute averages.
////////////////////////////////////////////////////////////////////////////////
//@{

//! \brief The average operator.
//! \param [in,out] res The result of the average.
//! \tparam T  The type of the result.
//! \remark This is the last function called when all the arguments have been
//!         chopped off.
template< class T >
constexpr void average( T & res )
{ 
  // nothing left to do
}

//! \brief The average operator.
//! \param [in,out] res The result of the average.
//! \param [in] u,args The arguments to average.
//! \tparam T  The type of the result.
//! \tparam U  The type of one of the arguments.
//! \tparam Args  The remainder of the arguments.
//! \remark This is the main function called that adds the contribution
//!         of each argument recursively.
template< class T, class U, class ... Args >
constexpr void average( T & res, U && u, Args&&... args )
{ 
  res += u;
  average(res, std::forward<Args>(args)...); 
}

//@}

} // namespace detail
} // namespace math
} // namespace ale
} // namespace ale
