/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
///
/// \file
///
/// \brief Provide a zip-like iterator for range-based fors.
///
/// This lets us do something like: for (auto i : zip(a, b, c) )
///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ristra-config.h"

// uncomment to use boost's zip iterator
//#define USE_BOOST_ZIP

#ifdef USE_BOOST_ZIP

// system includes
#  include <boost/iterator/zip_iterator.hpp>
#  include <boost/range.hpp>

#else

// user includes
#include "zip_impl.h"
#include "ristra/utils/type_traits.h"

// system includes
#  include <cassert>
#  include <iterator>
#  include <tuple>
#  include <utility>

#endif


namespace ristra {
namespace utils {


//##############################################################################
//##############################################################################
#ifdef USE_BOOST_ZIP
//##############################################################################
//##############################################################################


////////////////////////////////////////////////////////////////////////////////
//! \brief put this get in the open
//!
//! If your using the boost zip iterator, you will need to use boost's get. 
//! 
//! \remark its still protected within this namespace though, so it won't clash
////////////////////////////////////////////////////////////////////////////////
using boost::get;

////////////////////////////////////////////////////////////////////////////////
//! \brief Combine iterators together using boost
//!
//! \tparam T   a variadic template parameter for the different container 
//!             types
//!
//! \param [in,out] containers  The different list containters to zip together.
//! \return An iterator range.
////////////////////////////////////////////////////////////////////////////////
template <typename... T>
decltype(auto) zip(T&&... containers)
{
  // get the number of arguments
  auto n = sizeof...(T);

  // check all the sizes
  size_t sizes[] = { containers.size()... };
  auto first_size = sizes[1];
#ifndef NDEBUG
  for ( int i=2; i<n; i++ )
    assert( first_size == sizes[i] && " size mismatch" ); 
#endif

  // do the zip
  auto zip_begin = boost::make_zip_iterator(boost::make_tuple(std::begin(containers)...));
  auto zip_end = boost::make_zip_iterator(boost::make_tuple(std::end(containers)...));
  return boost::make_iterator_range(zip_begin, zip_end);
}


// delete from scope
#undef USE_BOOST_ZIP

//##############################################################################
//##############################################################################
#else // USE_BOOST_ZIP
//##############################################################################
//##############################################################################

////////////////////////////////////////////////////////////////////////////////
//! \brief put this get in the open
//!
//! If your using this zip iterator, you will need to use std::get. 
//! 
//! \remark its still protected within this namespace though, so it won't clash
////////////////////////////////////////////////////////////////////////////////
using std::get;


////////////////////////////////////////////////////////////////////////////////
//! \brief Combine iterators together
//!
//! Got this from 
//! http://codereview.stackexchange.com/questions/30846/zip-like-functionality-with-c11s-range-based-for-loop
//!
//! \tparam Types   a variadic template parameter for the different container 
//!                 types
//!
//! \param [in,out] args  The different list containters to zip together
//! \return A new iterator.
////////////////////////////////////////////////////////////////////////////////
template <class... Types>
decltype(auto) zip(Types&&... args)
{
  // load the detail namespace
  using namespace detail;

  // get the number of arguments
  auto n = sizeof...(Types);

  // check all the sizes
  size_t sizes[] = { args.size()... };
  auto first_size = sizes[1];
  for ( int i=2; i<n; i++ )
    assert( first_size == sizes[i] && " size mismatch" ); 

  return zipper<special_decay_t<Types>...>(std::forward<Types>(args)...);
}

//##############################################################################
//##############################################################################
#endif // USE_BOOST_ZIP
//##############################################################################
//##############################################################################

} // namespace
} // namespace
