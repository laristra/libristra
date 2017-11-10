/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2017 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Provides a multi-dimensioned array which functions as a vector.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "flecsi-sp/utils/type_traits.h"
#include "flecsi-sp/utils/template_helpers.h"
#include "flecsi-sp/utils/tuple_visit.h"

// system includes
#include <algorithm>
#include <array>
#include <cassert>

namespace flecsi {
namespace sp {
namespace math {



////////////////////////////////////////////////////////////////////////////////
/// \brief A helper struct to statically generate strides at compile time
///        for row major matrices.
////////////////////////////////////////////////////////////////////////////////
class row_major_ordering {

  //! \brief The size type is just a size_t.
  using size_type = std::size_t;

  //! \brief Compute the stride at position `N` recursively.
  //! \param [in] ids The array of dimensions of the matrix.
  //! \param [in] N   The dimension of the stride to compute.
  //! \return The strid at position `N`.
  constexpr size_type stride(const size_type * ids, const size_type & N )
  {
    if ( N > 0 )
      return ids[1] * stride( &ids[1], N-1 );
    else 
      return 1;
  }
  
  //! \brief Main helper function to compute the strides.
  //! \param [in] ids The array of dimensions of the matrix.
  //! \tparam N The number of dimensions.
  //! \tparam I The an index sequence from `0` to `N`
  //! \return The array of strides.
  template< size_type N, size_type... I >
  constexpr std::array<size_type, N> ordering_helper( const size_type (&ids)[N], std::index_sequence<I...> ) 
  {
    return {{ stride( &ids[I], N-I-1 )... }};
  }

public:
  
  //! \brief Main calling function to compute the strides.
  //! \param [in] ids The array of dimensions of the matrix.
  //! \tparam N The number of dimensions.
  //! \return The array of strides.
  template< size_type N >
  constexpr auto operator()( const size_type (&ids)[N] )    
  {
    return ordering_helper( ids, std::make_index_sequence<N>{} );
  }
  
};

////////////////////////////////////////////////////////////////////////////////
/// \brief A helper struct to statically generate strides at compile time
///        for column major matrices.
////////////////////////////////////////////////////////////////////////////////
class col_major_ordering {

  //! \brief The size type is just a size_t.
  using size_type = std::size_t;

  //! \brief Compute the stride at position `N` recursively.
  //! \param [in] ids The array of dimensions of the matrix.
  //! \param [in] N   The dimension of the stride to compute.
  //! \return The stride at position `N`.
  constexpr size_type stride(const size_type * ids, const size_type & N )
  {
    if ( N > 0 )
      return ids[1] * stride( &ids[1], N-1 );
    else 
      return 1;
  }
  
  //! \brief Main helper function to compute the strides.
  //! \param [in] ids The array of dimensions of the matrix.
  //! \tparam N The number of dimensions.
  //! \tparam I The an index sequence from `0` to `N`
  //! \return The array of strides.
  template< size_type N, size_type... I >
  constexpr std::array<size_type, N> ordering_helper( const size_type (&ids)[N], std::index_sequence<I...> ) 
  {
    return {{ stride( &ids[N-I-1], I )... }};
  }
  
public:

  //! \brief Main calling function to compute the strides.
  //! \param [in] ids The array of dimensions of the matrix.
  //! \tparam N The number of dimensions.
  //! \return The array of strides.
  template< size_type N >
  constexpr auto operator()( const size_type (&ids)[N] )    
  {
    return ordering_helper( ids, std::make_index_sequence<N>{} );
  }
  
};

////////////////////////////////////////////////////////////////////////////////
//!  \brief The dimensioned_array type provides a general base for defining
//!  contiguous array types that have a specific dimension.
//!
//!  \tparam T The type of the array, e.g., P.O.D. type.
//!  \tparam N The dimensions of the array.
////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t... N> 
class multi_array {

public:

  //===========================================================================
  // Typedefs
  //===========================================================================

  using value_type      = T;
  using reference       = T &;
  using pointer         = T *;
  using const_reference = const T &;
  using const_pointer   = const T *;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;

  //! \brief For terator support.
  //! @{
  using iterator        = pointer;
  using const_iterator  = const_pointer;
  //! @}

  //! \brief For reverse iterator support.
  //! @{
  using reverse_iterator       = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  //! @}

  //! \brief The number of dimensions.
  static constexpr size_type dimensions  = sizeof...(N);
  //! \brief The total length of storage.
  static constexpr size_type elements = utils::multiply(N...);

  //! \brief A counter type
  using counter_type = utils::select_counter_t<elements>;

private:

  //===========================================================================
  // Private Data
  //===========================================================================

  //! \brief The main data container, which is just a std::array.
  T elems_[ elements ];

  //! \brief The individual dimensions.
  static constexpr size_type dims_[ dimensions ] = {N...};

  //! \brief The individual strides.
  static constexpr std::array<size_type, sizeof...(N)> strides_ = row_major_ordering{}( dims_ );

public:

  //===========================================================================
  // Constructors / Destructors
  //===========================================================================

  //! \brief Force the default constructor.
  multi_array() = default;

  //! \brief Force the default copy constructor.
  multi_array(const multi_array &) = default;

  //!\brief A fancy copy constructor with type conversion.
  template <typename T2>
  multi_array(const multi_array<T2,N...>& oth) 
  {
    std::copy(oth.begin(),oth.end(), begin());    
  }

  //! \brief Constructor with one value.
  //! \param[in] val The value to set the multi_array to.
  template < typename T2 >
  multi_array(const T2 & val)
  { 
    //std::cout << "multi_array (single value constructor)\n";
    fill( val ); 
  }

  //! \brief Constructor with initializer list.
  //! Initializer list is ALWAYS provided in row-major format.
  //! \param[in] list The initializer list of values.
  multi_array( std::initializer_list<T> list) 
  { 
    //std::cout << "multi_array (variadic constructor)\n";
    if ( list.size() == 1 ) 
      fill( *list.begin() );
    else
      assign(list);
  }
   
  //===========================================================================
  // Iterators
  //===========================================================================

  //! \brief Return an iterator to the beginning of the multi_array.
  //! @{
                  iterator  begin()       { return elems_; }
  constexpr const_iterator  begin() const { return elems_; }
  constexpr const_iterator cbegin() const { return begin(); }
  //! @}
        
  //! \brief Return an iterator to the end of the multi_array.
  //! @{
                  iterator  end()       { return elems_+elements; }
  constexpr const_iterator  end() const { return elems_+elements; }
  constexpr const_iterator cend() const { return end(); }
  //! @}

  //! \brief Return a reverse iterator to the beginning of the multi_array.
  //! @{
  reverse_iterator rbegin() 
  { return reverse_iterator(end()); }
  
  const_reverse_iterator rbegin() const 
  { return const_reverse_iterator(end()); }
  
  const_reverse_iterator crbegin() const 
  { return const_reverse_iterator(end()); }
  //! @}

  //! \brief Return a reverse iterator to the end of the multi_array.
  //! @{
  reverse_iterator rend() 
  { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const 
  { return const_reverse_iterator(begin()); }
  
  const_reverse_iterator crend() const 
  { return const_reverse_iterator(begin()); }
  //! @}
 


  //===========================================================================
  // Element Access
  //===========================================================================


  //! \brief Return the `i`th element ( uses 1d index only ).
  //! \param [in] i  The element to access.
  //! @{
  reference operator[](size_type i) 
  { 
    assert( i < elements && "out of range" );
    return elems_[i];
  }
        
  const_reference operator[](size_type i) const 
  {     
    assert( i < elements && "out of range" );
    return elems_[i]; 
  }
  //! @}

  //! \brief Return a specific element ( allows multiple dimensions ).
  //! \param [in] ids  The indices in each dimension in an array.
  //! \tparam D The lenngth of the dimension array.
  //! \remark Must match the number of dimensions of the multi_array.
  //! @{
  template< size_type D >
  std::enable_if_t< D == dimensions, reference >
  operator[](const size_type (&ids)[D]) 
  { 
    auto ind = element( ids );
    return elems_[ind];
  }
        
  template<size_type D>
  std::enable_if_t< D == dimensions, const_reference >
  operator[](const size_type (&ids)[D]) const 
  {     
    auto ind = element( ids );
    return elems_[ind]; 
  }
  //! @}

  //! \brief Return a specific element ( allows multiple dimensions ).
  //! \param [in] i  The indices in each dimension.
  //! \remark Number of arguments must match the number of dimensions of the 
  //!         multi_array.
  //! @{
  template <typename... Args>
  std::enable_if_t< sizeof...(Args) == sizeof...(N), reference >
  operator()(Args... i) 
  { 
    assert_ranges( std::forward<Args>(i)... );
    auto ind = this->element( std::forward<Args>(i)... );
    return elems_[ind];
  }


  template <typename... Args>
  std::enable_if_t< sizeof...(Args) == sizeof...(N), const_reference >
  operator()(Args... i) const
  { 
    assert_ranges( std::forward<Args>(i)... );
    auto ind = this->element( std::forward<Args>(i)... );
    return elems_[ind];
  }
  //! @}

  //! \brief Access a specific element with a range check
  //! \param [in] i  The indices in each dimension.
  //! \remark Number of arguments must match the number of dimensions of the 
  //!         multi_array.
  template< typename... Args >
  std::enable_if_t< sizeof...(Args) == sizeof...(N), reference >
  at(Args... i) { 
    check_ranges( std::forward<Args>(i)... ); 
    auto ind = element( std::forward<Args>(i)... );
    return elems_[ind];
  }

  template< typename... Args >
  std::enable_if_t< sizeof...(Args) == sizeof...(N), const_reference >
  at(Args... i) const 
  { 
    check_ranges( std::forward<Args>(i)... ); 
    auto ind = element( std::forward<Args>(i)... );
    return elems_[ind];
  }
    
  //! \brief Return the first element.
  //! @{
  reference front() 
  { return elems_[0]; }
        
  const_reference front() const 
  { return elems_[0]; }
  //! @}
        
  //! \brief Return the last element.
  //! @{
  reference back() 
  { return elems_[elements-1]; }
        
  const_reference back() const 
  {  return elems_[elements-1]; }
  //! @}

  //  \brief Direct access to data (read-only)
  //! @{
  const T* data() const { return elems_; }
  T* data() { return elems_; }
  //! @}

  // \brief use array as C array (direct read/write access to data)
  T* c_array() { return elems_; }

  //===========================================================================
  // Capacity
  //===========================================================================

  //! \brief return the size
  static constexpr size_type size() 
  { return elements; }

  //! \brief return the number of elements
  static constexpr size_type num_elements() 
  { return size(); }

  //! \brief return the number of dimensions
  static constexpr size_type num_dimensions() 
  { return dimensions; }

  //! \brief return the size in a particular dimension
  static constexpr const size_type * shape() 
  { return dims_; }

  //! \brief the stride associated with each array dimension
  static constexpr const size_type * strides() 
  { return strides_.data(); }


  //===========================================================================
  // operations
  //===========================================================================


  //! \brief Swap contents (note: linear complexity).
  //! \param [in] y  The array to swap with.
  void swap (multi_array& y) {
    for ( counter_type i=0; i<elements; i++ ) std::swap(elems_[i], y.elems_[i]);    
  }


  //! \brief Assign one value to all elements.
  //! \param [in] value   The value to set.
  void fill(const T& value)
  {
    for ( counter_type i=0; i<elements; i++ ) elems_[i] = value;    
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

  //! \brief Replaces the contents of the container. 
  //! \param [in] list  An initializer list to use in assignement.
  void assign( std::initializer_list<T> list ) 
  { 
    assert( list.size() == elements && "input list size mismatch" );
    assign( list.begin(), list.end() );
  }

  
  //===========================================================================
  //! \brief Operators
  //===========================================================================
  //! @{

  // use std::move
  // http://stackoverflow.com/questions/11726171/numeric-vector-operator-overload-rvalue-reference-parameter

  //!\brief  assignment with type conversion
  template <typename T2>
  auto & operator= (const multi_array<T2,N...>& rhs) {
    if ( this != &rhs )
      for ( counter_type i=0; i<elements; i++ ) elems_[i] = rhs.elems_[i];    
    return *this;
  }

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
  auto & operator+=(const multi_array<T2,N...> & rhs) {
    for ( counter_type i=0; i<elements; i++ ) elems_[i] += rhs.elems_[i];    
    return *this;
  }

  //! \brief Addiition binary operator involving a constant.
  //! \param[in] val The constant on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator+=(const T2 & val) {
    for ( counter_type i=0; i<elements; i++ ) elems_[i] += val;    
    return *this;
  }

  //! \brief Subtraction binary operator involving another array.
  //! \param[in] rhs The array on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator-=(const multi_array<T2,N...> & rhs) {
    for ( counter_type i=0; i<elements; i++ ) elems_[i] -= rhs.elems_[i];    
    return *this;
  }

  //! \brief Subtraction binary operator involving a constant.
  //! \param[in] val The constant on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator-=(const T2 & val) {
    for ( counter_type i=0; i<elements; i++ ) elems_[i] -= val;    
    return *this;
  }


  //! \brief Multiplication binary operator involving another array.
  //! \param[in] rhs The array on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2> 
  auto & operator*=(const multi_array<T2,N...> & rhs) {
    for ( counter_type i=0; i<elements; i++ ) elems_[i] *= rhs.elems_[i];    
    return *this;
  }

  //! \brief Multiplication binary operator involving a constant.
  //! \param[in] val The constant on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator*=(const T2 & val) {
    for ( counter_type i=0; i<elements; i++ ) elems_[i] *= val;    
    return *this;
  }

  //! \brief Division binary operator involving another array.
  //! \param[in] rhs The array on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator/=(const multi_array<T2,N...> & rhs) {
    for ( counter_type i=0; i<elements; i++ ) elems_[i] /= rhs.elems_[i];    
    return *this;
  }

  //! \brief Division operator involving a constant.
  //! \param[in] val The constant on the right hand side of the operator.
  //! \return A reference to the current object.
  template <typename T2>
  auto & operator/=(const T2 & val) {
    auto inv = static_cast<T>(1) / val;
    for ( counter_type i=0; i<elements; i++ ) elems_[i] *= inv;
    return *this;
  }

  //! \brief Unary - operator.
  //! \param[in] rhs The array on the right hand side of the operator.
  //! \return A reference to the current object.
  auto operator-() const {
    multi_array tmp;
    for ( counter_type i=0; i<elements; i++ ) tmp[i] = -elems_[i];
    return tmp;
  }

  //! @}

  //===========================================================================
  //! \brief Utitilities
  //===========================================================================
  //! @{
  
  //! \brief unpack an array of indices and get the element index
  //! \remark this version uses an array of indices
  template< 
    typename U, 
    size_type D,
    typename = typename std::enable_if_t< (D == dimensions) >
  >
  static constexpr
  auto element( const U (&ids)[D] )
  {
    size_type ind = 0;
    for ( auto i=0; i<dimensions; i++ ) ind += ids[i]*strides_[i];
    return ind;
    //return std::inner_product( std::begin(ids), std::end(ids), std::begin(strides_), 0);
  }

  //! \brief compute the 1d element index
  //! \remark this version uses the variadic arguments
  template< 
    typename... Args, 
    typename = typename std::enable_if_t< (sizeof...(Args) == dimensions && dimensions > 1) >
  >
  static constexpr
  auto element( Args&&... ids )
  {
    size_type idx[sizeof...(ids)] = {static_cast<size_type>(ids)...};
    return element( idx );
  }

  //! \brief compute the 1d element index
  //! \remark this version is only enabled for 1d arrays
  template< 
    size_type D = dimensions, 
    typename = typename std::enable_if_t< D == 1 >
  >
  static constexpr
  auto element( size_type id )
  {
    return id;
  }

  //! \brief Make sure indices are in the range, throwing an exception on failure.
  //! \param [in] is  The indices to check.
  template< typename... Args >
  static
  std::enable_if_t< sizeof...(Args) == sizeof...(N) >
  check_ranges (Args... is) {
    utils::tuple_visit( 
                       [](auto i, auto dim) { 
                         if ( i>= dim  )
                           throw std::out_of_range("multi_array<>: index out of range");
                       },
                       std::forward_as_tuple(is...), 
                       std::forward_as_tuple(N...) );
  }


  //! \brief Make sure indices are in the range, throwing an assertion on failure.
  //! \param [in] is  The indices to check.
  template< typename... Args >
  static
  std::enable_if_t< sizeof...(Args) == sizeof...(N) >
  assert_ranges ( Args... is ) 
  { 
    utils::tuple_visit( 
                       [](auto i, auto dim) { 
                         assert( i < dim && "out of range" );
                       },
                       std::forward_as_tuple(is...), 
                       std::forward_as_tuple(N...) );
  }

  //! @}

};

////////////////////////////////////////////////////////////////////////////////
// static members
////////////////////////////////////////////////////////////////////////////////

//! \brief The individual dimensions
template <typename T, std::size_t... N> 
constexpr typename multi_array<T,N...>::size_type 
multi_array<T,N...> :: dims_[ multi_array<T,N...>::dimensions ];

//! \brief The individual dimensions
template <typename T, std::size_t... N> 
constexpr std::array<std::size_t, sizeof...(N)> multi_array<T,N...> :: strides_;

////////////////////////////////////////////////////////////////////////////////
// Friend functions
////////////////////////////////////////////////////////////////////////////////


//! \brief lexicographically compares the values in the array 
//! \param[in] lhs The quantity on the lhs.
//! \param[in] rhs The quantity on the rhs.
template<typename T, std::size_t... N>
bool operator==(const multi_array<T,N...>& lhs, const multi_array<T,N...>& rhs)
{
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ )
    if ( lhs[i] != rhs[i] ) 
      return false;
  return true;
}

template<typename T, typename U, std::size_t... N>
bool operator==(const multi_array<T,N...>& lhs, const U& rhs)
{
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ )
    if ( lhs[i] != rhs ) 
      return false;
  return true;
}


template<typename T, std::size_t... N>
bool operator< (const multi_array<T,N...>& x, const multi_array<T,N...>& y) {
  return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}

template<typename T, std::size_t... N>
bool operator!= (const multi_array<T,N...>& x, const multi_array<T,N...>& y) {
  return !(x==y);
}

template<typename T, std::size_t... N>
bool operator> (const multi_array<T,N...>& x, const multi_array<T,N...>& y) {
  return y<x;
}
template<typename T, std::size_t... N>
bool operator<= (const multi_array<T,N...>& x, const multi_array<T,N...>& y) {
  return !(y<x);
}
template<typename T, std::size_t... N>
bool operator>= (const multi_array<T,N...>& x, const multi_array<T,N...>& y) {
  return !(x<y);
}

//! \brief  global swap(), specializes the std::swap algorithm 
template<typename T, std::size_t... N>
inline void swap (multi_array<T,N...>& x, multi_array<T,N...>& y) {
  x.swap(y);
}


  
//! \brief Addition operator involving two multi_arrays.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The array on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, size_t... N>
auto operator+( const multi_array<T,N...>& lhs, 
                const multi_array<T,N...>& rhs )
{
  multi_array<T,N...> tmp;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs[i] + rhs[i];    
  return tmp;
}

//! \brief Addition operator involving one array and a scalar.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The scalar on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, typename U, size_t... N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, multi_array<T,N...> >
operator+( const multi_array<T,N...>& lhs, 
           const U& rhs )
{
  multi_array<T,N...> tmp;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs[i] + rhs;
  return tmp;
}

template <typename T, typename U, size_t... N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, multi_array<T,N...> >
operator+( const U& lhs, 
           const multi_array<T,N...>& rhs )
{
  multi_array<T,N...> tmp;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs + rhs[i];    
  return tmp;
}

//! \brief Subtraction operator involving two arrays.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The array on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, size_t... N>
auto operator-( const multi_array<T,N...>& lhs, 
                const multi_array<T,N...>& rhs )
{
  multi_array<T,N...> tmp;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs[i] - rhs[i];    
  return tmp;
}

//! \brief Subtraction operator involving one array and a scalar.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The scalar on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, typename U, size_t... N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, multi_array<T,N...> >
operator-( const multi_array<T,N...>& lhs, 
           const U& rhs )
{
  multi_array<T,N...> tmp;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs[i] - rhs;
  return tmp;
}

template <typename T, typename U, size_t... N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, multi_array<T,N...> >
operator-( const U& lhs, 
           const multi_array<T,N...>& rhs )
{
  multi_array<T,N...> tmp;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs - rhs[i];    
  return tmp;
}

//! \brief Multiplication operator involving two arrays.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The array on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, size_t... N>
auto operator*( const multi_array<T,N...>& lhs, 
                const multi_array<T,N...>& rhs )
{
  multi_array<T,N...> tmp;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs[i] * rhs[i];    
  return tmp;
}


//! \brief Multiplication operator involving one array and a scalar.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The scalar on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, typename U, size_t... N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, multi_array<T,N...> >
operator*( const multi_array<T,N...>& lhs, 
           const U& rhs )
{
  multi_array<T,N...> tmp;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs[i] * rhs;    
  return tmp;
}

template <typename T, typename U, size_t... N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, multi_array<T,N...> >
operator*( const U& lhs,
           const multi_array<T,N...>& rhs )
{
  multi_array<T,N...> tmp;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs * rhs[i];    
  return tmp;
}

//! \brief Division operator involving two arrays.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The array on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, size_t... N>
auto operator/( const multi_array<T,N...>& lhs, 
                const multi_array<T,N...>& rhs )
{
  multi_array<T,N...> tmp;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs[i] / rhs[i];    
  return tmp;
}



//! \brief Division operator involving one array and a scalar.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] lhs The array on the left hand side of the operator.
//! \param[in] rhs The scalar on the right hand side of the operator.
//! \return A reference to the current object.
template <typename T, typename U, size_t... N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, multi_array<T,N...> >
operator/( const multi_array<T,N...>& lhs, 
           const U& rhs )
{
  multi_array<T,N...> tmp;
  auto inv = static_cast<T>(1) / rhs;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs[i] * inv;    
  return tmp;
}

template <typename T, typename U, size_t... N>
std::enable_if_t< utils::is_arithmetic_v< std::decay_t<U> >, multi_array<T,N...> >
operator/( const U& lhs, 
           const multi_array<T,N...>& rhs )
{
  multi_array<T,N...> tmp;
  using counter_type = typename multi_array<T,N...>::counter_type;
  for ( counter_type i=0; i<multi_array<T,N...>::elements; i++ ) 
    tmp[i] = lhs / rhs[i];    
  return tmp;
}

//! \brief Output operator for array.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in,out] os  The ostream to dump output to.
//! \param[in]     rhs The array on the right hand side of the operator.
//! \return A reference to the current ostream.
template <typename T, std::size_t D1, std::size_t D2>
auto & operator<<(std::ostream& os, const multi_array<T,D1,D2>& a)
{
  using counter_type = typename multi_array<T,D1,D2>::counter_type;
  for ( counter_type j = 0; j<D2; j++ ) { 
    os << "[";
    for ( counter_type i = 0; i<D1; i++ ) os << " " << a(i,j);
    os << " ]" << std::endl;
  }
  return os;
}


} // namespace
} // namespace
} // namespace
