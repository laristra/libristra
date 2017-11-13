/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2017 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// 
/// \brief A serialized vector.  It acts like a vector but has a fixed internal
///        storage size.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "flecsi-sp/utils/type_traits.h"
#include "flecsi-sp/utils/template_helpers.h"

// system includes
#include <algorithm>
#include <array>
#include <cassert>

namespace flecsi {
namespace sp {
namespace utils {
    
////////////////////////////////////////////////////////////////////////////////
//! \brief the fixed size vector container class
////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N>
class fixed_vector {

public:

  //============================================================================
  // public typedefs
  //============================================================================
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        
  //============================================================================
  // Construct / copy
  //============================================================================
  constexpr fixed_vector() : length_(0) { }

  constexpr fixed_vector(const fixed_vector& o) 
    : length_( o.length_ )
  {
    std::copy_n( o.begin(), length_, begin() );
  }

  constexpr fixed_vector(fixed_vector &&) = default;

  fixed_vector& operator=(const fixed_vector&) = default;
  fixed_vector& operator=(fixed_vector&&) = default;
        
  explicit fixed_vector( size_type count, const T& value )
  {
    assign( count, value );
  }

  explicit fixed_vector( size_type count ) :
    length_( count )
  {
    assert( size() <= capacity() );
  }

  template< 
    class InputIt,
    typename = typename std::enable_if_t< is_iterator_v<InputIt> >
  >
  fixed_vector( InputIt first, InputIt last )
  {
    assign( first, last );
  }

  fixed_vector( std::initializer_list<T> init )
  {
    assign( init );
  }
  

  void assign( size_type count, const T& value )
  {
    length_ = count;
    assert( size() <= capacity() );
    std::fill_n( begin(), count, value );
  }

  template< class InputIt >
  void assign( InputIt first, InputIt last )
  {
    length_ = std::distance( first, last );
    assert( size() <= capacity() );
    std::copy( first, last, begin() );    
  }

  void assign( std::initializer_list<T> ilist )
  {
    length_ = ilist.size();
    assert( size() <= capacity() );
    std::copy( ilist.begin(), ilist.end(), begin() );    
  }

  //============================================================================
  // element access
  //============================================================================
  constexpr const_reference operator[](size_type i) const { return data_[i]; }
  constexpr reference operator[](size_type i) { return data_[i]; }

  constexpr const_reference at(size_type i) const 
  {
    // This makes at() constexpr as long as the argument is within the bounds.
    return i >= size() ? throw std::out_of_range("at() argument out of range")
      : data_[i];
  }
  constexpr reference at(size_type i)
  {
    // This makes at() constexpr as long as the argument is within the bounds.
    return i >= size() ? throw std::out_of_range("at() argument out of range")
      : data_[i];
  }
      
  constexpr const_reference front() const { return data_[0]; }
  constexpr const_reference back()  const { return data_[size()-1]; }

  constexpr reference front() { return data_[0]; }
  constexpr reference back()  { return data_[size()-1]; }
        
  constexpr const_pointer data() const { return data_; }
  constexpr pointer data() { return data_; }
        

  //============================================================================
  // Iterators
  //============================================================================

  constexpr iterator begin() { return data_.begin(); }
  constexpr iterator end() { return std::next(data_.begin(), length_); }
  constexpr const_iterator begin() const { return data_.begin(); }
  constexpr const_iterator end() const { return std::next(data_.begin(), length_); }
  constexpr const_iterator cbegin() const { return begin(); }
  constexpr const_iterator cend() const { return end(); }
  reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  const_reverse_iterator crbegin() const { return rbegin(); }
  const_reverse_iterator crend() const { return rend(); }

        

  //============================================================================
  // Capacity
  //============================================================================

  constexpr size_type size() const { return length_; }
  constexpr size_type max_size() const { return N; }
  constexpr size_type capacity() const { return N; }
  constexpr bool empty() const { return length_ == 0; }
        
  //============================================================================
  // Modifiers
  //============================================================================

  void clear() { length_ = 0; }  
  
  iterator insert( const_iterator pos, const T& value )
  {
    assert( size() < capacity() );
    // convert to a non-const iterator
    auto d_first = _validate_iterator( pos );
    // shift data to the right
    auto d_last = std::next(d_first);
    std::copy(d_first, end(), d_last );
    // assign value
    *d_first = value;
    // increment counter
    length_++;
    // return an iterator to the inserted value
    return d_first;
  }

  iterator insert( const_iterator pos, T&& value ) 
  {
    assert( size() < capacity() );
    // convert to a non-const iterator
    auto d_first = _validate_iterator( pos );
    // shift data to the right
    auto d_last = std::next(d_first);
    std::move(d_first, end(), d_last );
    // assign value
    *d_first = std::move( value );
    // increment counter
    length_++;
    // return an iterator to the inserted value
    return d_first;
  }

  iterator insert( const_iterator pos, size_type count, const T& value ) 
  {
    assert( size()+count <= capacity() );
    // convert to a non-const iterator
    auto d_first = _validate_iterator( pos );
    // if zero size is inserted, return pos
    if ( count == 0 ) return d_first;
    // otherwise, shift data to the right
    auto d_last = std::next(d_first, count);
    std::copy(d_first, end(), d_last );
    // assign value
    std::fill_n( d_first, count, value );
    // increment counter
    length_ += count;
    // return an iterator to the inserted value
    return d_first;
  }

  template< 
    class InputIt,
    typename = typename std::enable_if_t< is_iterator_v<InputIt> >
  >
  iterator insert( const_iterator pos, InputIt first, InputIt last )
  {
    // figure out the added size
    auto count = std::distance( first, last );
    assert( size()+count <= capacity() );
    // convert to a non-const iterator
    auto d_first = _validate_iterator( pos );
    // if zero size is inserted, return pos
    if ( count == 0 ) return d_first;
    // otherwise, shift data to the right
    auto d_last = std::next(d_first, count);
    std::move(d_first, end(), d_last );
    // assign values
    std::copy( first, last, d_first );
    // increment counter
    length_ += count;
    // return an iterator to the inserted value
    return d_first;
  }

  iterator insert( const_iterator pos, std::initializer_list<T> ilist )
  {
    // figure out the added size
    auto count = ilist.size();
    assert( size()+count <= capacity() );
    // convert to a non-const iterator
    auto start = std::next(begin(), std::distance(cbegin(), pos));
    // if zero size is inserted, return pos
    if ( count == 0 ) return start;
    // otherwise, shift data to the right
    auto next = std::next(start, count);
    std::move(start, end(), next );
    // assign values
    std::copy( ilist.begin(), ilist.end(), start );
    // increment counter
    length_ += count;
    // return an iterator to the inserted value
    return start;
  }
  


  iterator erase( const_iterator pos )
  {
    // empty, nothing to do
    if ( empty() ) return end();
    // convert to a non-const iterator
    auto d_first = _validate_iterator( pos );
    // get next position
    auto d_last = std::next(d_first);
    // if this is not last element, shift the values left
    if ( d_last != end() )
      std::move( d_last, end(), d_first );
    // decrement counter
    length_--;
    // return the iterator following the last removed element
    return d_first;
  }

  iterator erase( const_iterator first, const_iterator last )
  {
    // if empty, nothing to do    
    if ( empty() ) return end();
    // if first == last, nothring to do
    if ( first == last ) return begin();
    // get the number of deleted elements
    auto count = std::distance( first, last );
    // convert to a non-const iterator
    auto d_first = _validate_iterator( first );
    auto d_last = _validate_iterator( last );
    // if we are deleting from the middle, shift values left
    if ( last != end() ) 
      std::move( d_last, end(), d_first );
    // the new length
    length_ -= count;
    // return the iterator following the last removed element
    return d_first;
  }

  void push_back( const T& value )
  {
    assert( size() < capacity() );
    data_[length_++] = value;
  }

  void push_back( T&& value )
  {
    assert( size() < capacity() );
    data_[length_++] = std::move( value );
  }

  template< class... Args >
  void emplace_back( Args&&... args )
  {
    assert( size() < capacity() );
    data_[length_++] = value_type( std::forward<Args>(args)... );
  }

  void pop_back() 
  {
    if ( empty() ) return;
    length_--;
  }

  void resize( size_type count ) 
  {
    length_ = count;
    assert( size() <= capacity() );
  }
  void resize( size_type count, const value_type& value )
  {
    assert( count <= capacity() );
    for ( utils::select_counter_t<N> i=length_; i<count; i++ )
      data_[i] = value;
    length_ = count;
  }

  void swap( fixed_vector& other ) 
  {
    std::swap( length_, other.length_ );
    std::swap( data_, other.data_ );
  }

private:

  //============================================================================
  // private members
  //============================================================================

  iterator _validate_iterator( const_iterator pos )
  {
    auto n = std::distance(cbegin(), pos);
    assert( n >= 0 && n <= length_ );
    return std::next(begin(), n);
  }

  //============================================================================
  // private data
  //============================================================================

  //! \brief the actual data is stored in an array of fixed size
  std::array<value_type, N> data_;
  //! the length of the array that is actually used
  size_type  length_;
        
};


////////////////////////////////////////////////////////////////////////////////
//! \brief non member functions
////////////////////////////////////////////////////////////////////////////////
template< class T, std::size_t N >
bool operator==( const fixed_vector<T,N>& lhs,
                 const fixed_vector<T,N>& rhs )
{
  return std::equal( lhs.begin(), lhs.end(), rhs.begin() );
}
    
}      // End namespace
}      // End namespace
}      // End namespace
