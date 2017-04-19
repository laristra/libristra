/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Provides a dimensioned array which functions as a vector.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "../utils/type_traits.h"
#include "../utils/template_helpers.h"
#include "../utils/tuple_visit.h"

// system includes
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>

namespace flecsi {
namespace sp {
namespace math {

////////////////////////////////////////////////////////////////////////////////
//!  \brief The dimensioned_array type provides a general base for defining
//!  contiguous array types that have a specific dimension.
//!
//!  \tparam T The type of the array, e.g., P.O.D. type.
//!  \tparam N The dimension of the array, i.e., the number of elements
//!    to be stored in the array.
////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N> 
class array {

public:

  //===========================================================================
  //! \brief Typedefs
  //===========================================================================
  // @{
  using value_type      = T;
  using reference       = T &;
  using pointer         = T *;
  using const_reference = const T &;
  using const_pointer   = const T *;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;
  using counter_type    = utils::select_counter_t<N>;
  
  //! \brief For iterator support.
  //! @{
  using iterator        = pointer;
  using const_iterator  = const_pointer;
  //! @}

  //! \brief For reverse iterator support.
  //! @{
  using reverse_iterator       = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  //! @}

  //! \brief The array size.
  static constexpr size_type length  = N;
  //! @}

private:

  //===========================================================================
  //! \brief Private Data
  //===========================================================================
  //! @{

  //! \brief The main data container, which is just a std::array.
  T elems_[length];

  //! @}

public:

  //===========================================================================
  //! \brief Constructors / Destructors
  //===========================================================================
  //! @{

  //! \brief Force the default constructor.
  constexpr array() noexcept = default;

  //! \brief force the default copy constructor
  array(const array &) = default;


  //! \brief fancier copy constructor
  template <typename T2>
  constexpr array(const array<T2,N> &rhs) noexcept
  {
    for ( counter_type i=0; i<N; ++i )
      elems_[i] = rhs.elems_[i]; 
  }

  //! \brief Constructor with variadic arguments.
  //! \param[in] args The individual array values.
  template <
    typename... Args,
    typename = std::enable_if_t< 
      ( sizeof...(Args) == N && sizeof...(Args) >= 2 )
    >
  >
  constexpr array(Args&&... args) noexcept : 
    elems_{ static_cast<T>( std::forward<Args>(args) )... }
  { 
    //std::cout << "array (variadic constructor)\n";
  }
 
  //! \brief Constructor with one value.
  //! \param[in] val The value to set the array to.
  template < typename T2 >
  constexpr array(const T2 & val)  noexcept 
  //elems_( utils::fill<length>::apply( static_cast<T>(val) ) )
  //elems_( utils::make_array<value_type,length>( static_cast<T>(val) ) )
  { 
    //std::cout << "array (single value constructor)\n";
    fill( val );
  }

  // @}
   
  //===========================================================================
  //! \brief Iterators.
  //===========================================================================
  // @{

  //! \brief return an iterator to the beginning of the array
  //! @{
                  iterator  begin()       { return elems_; }
  constexpr const_iterator  begin() const { return elems_; }
  constexpr const_iterator cbegin() const { return begin(); }
  //! @}
        
  //! \brief return an iterator to the end of the array
  //! @{
                  iterator  end()       { return elems_+length; }
  constexpr const_iterator  end() const { return elems_+length; }
  constexpr const_iterator cend() const { return end(); }


  //! \brief return a reverse iterator to the beginning of the aray
  //! @{
  reverse_iterator rbegin() 
  { return reverse_iterator(end()); }
  
  const_reverse_iterator rbegin() const 
  { return const_reverse_iterator(end()); }
  
  const_reverse_iterator crbegin() const 
  { return const_reverse_iterator(end()); }
  //! @}

  //! \brief return a reverse iterator to the end of the aray
  //! @{
  reverse_iterator rend() 
  { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const 
  { return const_reverse_iterator(begin()); }
  
  const_reverse_iterator crend() const 
  { return const_reverse_iterator(begin()); }
  //! @}
 
  //! @}

  //===========================================================================
  // Element Access
  //===========================================================================

  //! \brief Return the `i`th element.
  //! \param [in] i  The element to access.
  //! @{
  reference operator[](size_type i) 
  { 
    assert( i < size() && "out of range" );
    return elems_[i];
  }
        
  const_reference operator[](size_type i) const 
  {     
    assert( i < size() && "out of range" );
    return elems_[i]; 
  }

  reference operator()(size_type i) 
  { 
    assert( i < size() && "out of range" );
    return elems_[i];
  }

  const_reference operator()(size_type i) const
  { 
    assert( i < size() && "out of range" );
    return elems_[i];
  }
  //! @}

  //! \brief Return the `i`th element with a range check.
  //! \param [in] i  The element to access.
  //! @{
  reference at(size_type i) 
  { 
    return i >= size() ? 
      throw std::out_of_range("array<>: index out of range") : 
      elems_[i];
  }

  const_reference at(size_type i) const
  { 
    return i >= size() ? 
      throw std::out_of_range("array<>: index out of range") : 
      elems_[i];
  }
  //! @}

  //! \brief return the first element
  //! @{
  reference front() 
  { return elems_[0]; }
        
  const_reference front() const 
  { return elems_[0]; }
  //! @}
        
  //! \brief return the last element
  //! @{
  reference back() 
  { return elems_[size()-1]; }
        
  const_reference back() const 
  {  return elems_[size()-1]; }
  //! @}


  //  \brief direct access to data (read-only)
  //! @{
  const T* data() const { return elems_; }
  T* data() { return elems_.data(); }
  //! @}

  // use array as C array (direct read/write access to data)
  T* c_array() { return elems_.data(); }

  //===========================================================================
  //! \brief Capacity
  //===========================================================================
  //! @{

  //! \brief return the size
  static constexpr size_type     size() { return length; }
  static constexpr size_type capacity() { return size(); }

  //! \brief checks whether container is empty
  static constexpr bool empty() { return false; }
  
  //! \brief returns the maximum possible number of elements
  static constexpr size_type max_size() { return size(); }
  //! @}


  //===========================================================================
  //! \brief Modifiers
  //===========================================================================
  //! @{

  //  \brief swap contents (note: linear complexity)
  void swap (array& y) 
  {
    for ( counter_type i=0; i<N; i++ ) std::swap(elems_[i], y.elems_[i]);    
  }

  //! \brief assign one value to all elements
  void fill(const T& value)
  {
    for ( counter_type i=0; i<N; i++ ) elems_[i] = value;    

  }

  //! \brief Replaces the contents of the container. 
  //! \tparam InputIt  The input iterator type
  //! \param [in] first  the start of the range to copy the elements from
  //! \param [in] last   the end of the range to copy the elements from
  template < class InputIt >
  void assign(InputIt first, InputIt last) 
  { 
    std::copy( first, last, begin() );
  }

  void assign( std::initializer_list<T> list ) 
  { 
    assert( list.size() == size() && "input list size mismatch" );
    assign( list.begin(), list.end() );
  }
  //! @}

  //===========================================================================
  //! \brief Operators
  //===========================================================================
  //! @{

  // use std::move
  // http://stackoverflow.com/questions/11726171/numeric-vector-operator-overload-rvalue-reference-parameter

  //!\brief  assignment with type conversion
  template <typename T2>
  auto & operator= (const array<T2,N>& rhs) {
    for ( counter_type i=0; i<N; i++ ) elems_[i] = rhs.elems_[i];    
    return *this;
  }

  //! \brief assignement to constant value.
  //! \param[in] val The constant on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator= (const T2 & val) {
    fill(val);
    return *this;
  }


  //! \brief Addition binary operator involving another array.
  //! \param[in] rhs The array on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator+=(const array<T2,N> & rhs) {
    for ( counter_type i=0; i<N; i++ ) elems_[i] += rhs.elems_[i];    
    return *this;
  }

  //! \brief Addiition binary operator involving a constant.
  //! \param[in] val The constant on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator+=(const T2 & val) {
    for ( counter_type i=0; i<N; i++ ) elems_[i] += val;    
    return *this;
  }

  //! \brief Subtraction binary operator involving another array.
  //! \param[in] rhs The array on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator-=(const array<T2,N> & rhs) {
    for ( counter_type i=0; i<N; i++ ) elems_[i] -= rhs.elems_[i];    
    return *this;
  }

  //! \brief Subtraction binary operator involving a constant.
  //! \param[in] val The constant on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator-=(const T2 & val) {
    for ( counter_type i=0; i<N; i++ ) elems_[i] -= val;    
    return *this;
  }


  //! \brief Multiplication binary operator involving another array.
  //! \param[in] rhs The array on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2> 
  auto & operator*=(const array<T2,N> & rhs) {
    for ( counter_type i=0; i<N; i++ ) elems_[i] *= rhs.elems_[i];    
    return *this;
  }

  //! \brief Multiplication binary operator involving a constant.
  //! \param[in] val The constant on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator*=(const T2 & val) {
    for ( counter_type i=0; i<N; i++ ) elems_[i] *= val;    
    return *this;
  }

  //! \brief Division binary operator involving another array.
  //! \param[in] rhs The array on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator/=(const array<T2,N> & rhs) {
    for ( counter_type i=0; i<N; i++ ) elems_[i] /= rhs.elems_[i];    
    return *this;
  }

  //! \brief Division operator involving a constant.
  //! \param[in] val The constant on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator/=(const T2 & val) {
    auto inv = static_cast<T>(1) / val;
    for ( counter_type i=0; i<N; i++ ) elems_[i] *= inv;
    return *this;
  }

  //! \brief Unary - operator.
  //! \param[in] rhs The array on the right hand side of the operator.
  //! \return A reference to the current object.
  auto operator-() const {
    array tmp;
    for ( counter_type i=0; i<N; i++ ) tmp[i] = -elems_[i];
    return tmp;
  }

  //! @}

};


////////////////////////////////////////////////////////////////////////////////
// Friend functions
////////////////////////////////////////////////////////////////////////////////


//! \brief lexicographically compares the values in the array 
//! \param[in] lhs The quantity on the lhs.
//! \param[in] rhs The quantity on the rhs.
template<typename T, std::size_t N>
bool operator==(const array<T,N>& lhs, const array<T,N>& rhs)
{
  for ( typename array<T,N>::counter_type i=0; i<N; i++ )
    if ( lhs[i] != rhs[i] ) 
      return false;
  return true;
}

template<typename T, typename U, std::size_t N>
bool operator==(const array<T,N>& lhs, const U& rhs)
{
  for ( typename array<T,N>::counter_type i=0; i<N; i++ )
    if ( lhs[i] != rhs ) 
      return false;
  return true;
}

template<typename T, std::size_t N>
bool operator< (const array<T,N>& x, const array<T,N>& y) {
  return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}

template<typename T, std::size_t N>
bool operator!= (const array<T,N>& x, const array<T,N>& y) {
  return !(x==y);
}

template<typename T, std::size_t N>
bool operator> (const array<T,N>& x, const array<T,N>& y) {
  return y<x;
}
template<typename T, std::size_t N>
bool operator<= (const array<T,N>& x, const array<T,N>& y) {
  return !(y<x);
}
template<typename T, std::size_t N>
bool operator>= (const array<T,N>& x, const array<T,N>& y) {
  return !(x<y);
}

//! \brief  global swap(), specializes the std::swap algorithm 
template<typename T, std::size_t N>
inline void swap (array<T,N>& x, array<T,N>& y) {
  x.swap(y);
}


  
//! \brief Addition operator involving two arrays.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The array on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, std::size_t N>
auto operator+( const array<T,N>& lhs, 
                const array<T,N>& rhs )
{
  array<T,N> tmp;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs[i] + rhs[i];    
  return tmp;
}

//! \brief Addition operator involving one array and a scalar.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The scalar on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, typename U, std::size_t N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, array<T,N> >
operator+( const array<T,N>& lhs, 
           const U& rhs )
{
  array<T,N> tmp;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs[i] + rhs;
  return tmp;
}

template <typename T, typename U, std::size_t N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, array<T,N> >
operator+( const U& lhs, 
           const array<T,N>& rhs )
{
  array<T,N> tmp;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs + rhs[i];
  return tmp;
}

//! \brief Subtraction operator involving two arrays.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The array on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, std::size_t N>
auto operator-( const array<T,N>& lhs, 
                const array<T,N>& rhs )
{
  array<T,N> tmp;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs[i] - rhs[i];    
  return tmp;
}

//! \brief Subtraction operator involving one array and a scalar.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The scalar on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, typename U, std::size_t N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, array<T,N> >
operator-( const array<T,N>& lhs, 
           const U& rhs )
{
  array<T,N> tmp;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs[i] - rhs;
  return tmp;
}

template <typename T, typename U, std::size_t N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, array<T,N> >
operator-( const U& lhs, 
           const array<T,N>& rhs )
{
  array<T,N> tmp;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs - rhs[i];
  return tmp;
}

//! \brief Multiplication operator involving two arrays.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The array on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, std::size_t N>
auto operator*( const array<T,N>& lhs, 
                const array<T,N>& rhs )
{
  array<T,N> tmp;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs[i] * rhs[i];    
  return tmp;
}


//! \brief Multiplication operator involving one array and a scalar.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The scalar on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, typename U, std::size_t N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, array<T,N> >
operator*( const array<T,N>& lhs, 
           const U& rhs )
{
  array<T,N> tmp;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs[i] * rhs;
  return tmp;
}

template <typename T, typename U, std::size_t N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, array<T,N> >
operator*( const U & lhs,
           const array<T,N>& rhs )
{
  array<T,N> tmp;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs * rhs[i];
  return tmp;
}

//! \brief Division operator involving two arrays.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The array on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, std::size_t N>
auto operator/( const array<T,N>& lhs, 
                const array<T,N>& rhs )
{
  array<T,N> tmp;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs[i] / rhs[i];    
  return tmp;
}



//! \brief Division operator involving one array and a scalar.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The scalar on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, typename U, std::size_t N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, array<T,N> >
operator/( const array<T,N>& lhs, 
           const U& rhs )
{
  array<T,N> tmp;
  auto inv = static_cast<T>(1) / rhs;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs[i] * inv;
  return tmp;
}

template <typename T, typename U, std::size_t N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, array<T,N> >
operator/( const U& lhs, 
           const array<T,N>& rhs )
{
  array<T,N> tmp;
  for ( typename array<T,N>::counter_type i=0; i<N; i++ ) 
    tmp[i] = lhs / rhs[i];
  return tmp;
}

//! \brief Output operator for array.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in,out] os  The ostream to dump output to.
//! \param[in]     rhs The array on the right hand side of the operator.
//! \return A reference to the current ostream.
template <typename T, std::size_t N>
auto & operator<<(std::ostream& os, const array<T,N>& a)
{
  os << "(";
  for ( auto i : a ) os << " " << i;
  os << " )";
  return os;
}


} // namespace
} // namespace
} // namespace
