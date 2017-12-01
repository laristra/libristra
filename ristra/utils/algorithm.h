/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Extensions to C++11 that are part of C++14.
////////////////////////////////////////////////////////////////////////////////

#pragma once

// system includes
#include <algorithm>

namespace ristra {
namespace utils {

////////////////////////////////////////////////////////////////////////////////
// Stuff not in C++ stds library
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
//! \brief Perform a set intersection, but this one sorts first.
//! \param [in] first1,last1  The first range of elements to examine.
//! \param [in] first2,last2  The second range of elements to examine.
//! \param [in,out] d_first  Iterator past the constructed range.
//! \return Iterator past the constructed range.
//==============================================================================
template<class InputIt1, class InputIt2, class OutputIt>
OutputIt unsorted_set_intersection( InputIt1 first1, InputIt1 last1,
                                    InputIt2 first2, InputIt2 last2,
                                    OutputIt d_first )
{
  using value_type1 = typename std::iterator_traits<InputIt1>::value_type;
  using value_type2 = typename std::iterator_traits<InputIt2>::value_type;
  
  std::vector< value_type1 > sorted1( first1, last1 );
  std::vector< value_type2 > sorted2( first2, last2 );
  
  std::sort( sorted1.begin(), sorted1.end() );
  std::sort( sorted2.begin(), sorted2.end() );

  return std::set_intersection( sorted1.begin(), sorted1.end(), 
                                sorted2.begin(), sorted2.end(),
                                d_first );
}

//==============================================================================
//! \brief Remove unique items from a container.
//! \param [in,out] cont  The container to modify.
//==============================================================================
template<class Container>
void remove_duplicates( Container && cont )
{
  auto end = std::forward<Container>(cont).end();
  auto last = std::unique( std::forward<Container>(cont).begin(), end );
  std::forward<Container>(cont).erase( last, end );
}

} // namespace
} // namespace
