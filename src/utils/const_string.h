/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief A constexpr string.
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace ristra {
namespace utils {

////////////////////////////////////////////////////////////////////////////////
//! \brief A constexpr string.
////////////////////////////////////////////////////////////////////////////////
class const_string {

public:

  using size_type = std::size_t;
  using hash_type = size_type;

  //! \brief Construct a const_string from a static char array.
  //! \param [in] a  The input character array.
  //! \tparam N The length of the string.
  template< size_type N >
  constexpr const_string( const char (&a)[N] ) : p_(a), sz_(N-1) {}

  //! \brief return the value at a specific position `n`
  constexpr char operator[] ( size_type n )
  { return n < sz_ ? p_[n] : throw std::out_of_range(""); }

  //! \brief Return the size of the string.
  constexpr size_type size() { return sz_; }

  //! \brief Return a pointer to a c-string.
  constexpr const char* c_str() const { return p_; }

private:

  const char* const p_;
  const size_type sz_;

};

} // namspeace
} // namspeace
