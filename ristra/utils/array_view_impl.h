/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief A reference array to avoid a million overloads.
////////////////////////////////////////////////////////////////////////////////

#pragma once

// user includes
#include "ristra/utils/type_traits.h"
#include "ristra/exception/errors.h"
#include "ristra/utils/template_helpers.h"

namespace ristra {
namespace utils {



namespace detail {

////////////////////////////////////////////////////////////////////////////////    
//! \brief a searchable way to do narrowing casts of values
////////////////////////////////////////////////////////////////////////////////    
template<class T, class U>
inline constexpr T narrow_cast(U u) noexcept
{ return static_cast<T>(u); }



////////////////////////////////////////////////////////////////////////////////    
/// \brief A Helper to make strides
////////////////////////////////////////////////////////////////////////////////    
template< typename IndexType >
class make_strides {

  using size_type = typename IndexType::size_type;
  using value_type = typename IndexType::value_type;

  constexpr value_type stride(const value_type * ids, const size_type & N )
  {
    if ( N > 0 )
      return ids[1] * stride( &ids[1], N-1 );
    else 
      return 1;
  }
  
  template< 
    typename ArrayType,
    size_type... I,
    size_type N = sizeof...(I)
  >
  constexpr std::array<value_type, N> 
  ordering_helper( ArrayType && ids, std::index_sequence<I...> ) 
  {
    return {{ stride( &std::forward<ArrayType>(ids)[I], N-I-1 )... }};
  }

public:
  
  template< 
    size_type N,
    typename = std::enable_if_t< N == IndexType::rank >
  >
  constexpr auto operator()( const value_type (&ids)[N] )    
  {
    return ordering_helper( ids, std::make_index_sequence<N>{} );
  }

  template< 
    size_type N,
    typename = std::enable_if_t< N == IndexType::rank >
  >
  constexpr auto operator()( const std::array<value_type, N> ids )    
  {
    return ordering_helper( ids, std::make_index_sequence<N>{} );
  }

  template<
    typename... Args,
    int N = sizeof...(Args),
    std::enable_if_t< (N == IndexType::rank && are_integral_v<Args...>) >* = nullptr
  >
  constexpr auto operator()(Args... args) noexcept
  {
    value_type exts[N] = { detail::narrow_cast<value_type>( std::forward<Args>(args) )... };
    return ordering_helper( exts, std::make_index_sequence<N>{} );
  }
  
};



} // namespace detail


////////////////////////////////////////////////////////////////////////////////    
/// \brief the index represenation
/// An N-dimensional vector identifying a point in N-dimensional space
////////////////////////////////////////////////////////////////////////////////    
template <int Rank>
class index_t final {

  //! \brief declare other variations of index_t as a friend
  template< int R >
  friend class index_t;

public:

  //============================================================================
  /// \name types
  //============================================================================
  /// @{
  //! \brief the number of dimensions in the rectangle
  static constexpr auto rank = Rank;
  //! \brief the type of index, which is ptrdiff_t
  //! This allows the index to both address every byte in the largest allocation 
  //! and express any offset in the same
  using value_type = std::ptrdiff_t;
  //! \brief the reference to a value
  using reference = value_type &;
  //! \brief the constant reference to a value
  using const_reference = const value_type &;
  //! \brief the reference to a value
  using pointer = value_type *;
  //! \brief the constant reference to a value
  using const_pointer = const value_type *;
  //! \brief the size type used 
  using size_type = std::size_t;
  //! \brief the iterator types
  using iterator = pointer;
  //! \brief the constant interator
  using const_iterator = const_pointer;

  //! a slice type
  using sliced_type = std::conditional_t<rank != 0, index_t<rank - 1>, void>;
  /// @}

  //============================================================================
  /// \name construct/copy
  //============================================================================
  /// @{
  
  //! \brief the default constructor
  constexpr index_t() noexcept = default;
  //! \brief the default copy constructor
  constexpr index_t(const index_t &) noexcept = default;
  //! \brief the default move constructor
  constexpr index_t(index_t &&) noexcept = default;
  //! \brief the default assignment operator
  constexpr index_t& operator=(const index_t &) noexcept = default;
  //! \brief the default move assignment operator
  constexpr index_t& operator=(index_t &&) noexcept = default;


  //! \brief constructor with values, must be the same number as rank
  template <
    typename... Ts,
    typename = std::enable_if_t< (sizeof...(Ts) == Rank) && are_integral_v<Ts...> >
  > 
  constexpr index_t(Ts... ts) noexcept : 
    index_{ detail::narrow_cast<value_type>( std::forward<Ts>(ts) )...} 
  {};


  //! \brief constructor with values, must be the same number as rank
  template< 
    std::size_t N,
    std::enable_if_t< (N == Rank) >* = nullptr 
  >
  constexpr explicit index_t( const std::array<value_type,N> & arr ) noexcept : 
    index_{ arr } 
  {};

  //! \brief constructor with static array, must be the same size as rank\
  //! \tparam N the rank of the array, must equal Rank
  //! \param [in] vals  the values to set
  template< 
    std::size_t N,
    std::enable_if_t< (N == Rank) >* = nullptr 
  >
  constexpr index_t(const value_type (&vals)[N]) noexcept
  {
    std::copy( vals, vals+rank, index_.begin() );
  };
  /// @}
  

  //============================================================================
  /// \name Access components
  //============================================================================
  /// @{

  //! \brief return the extent of the array
  //! \tparam Dim the dimension to query
  template< size_type Dim = 0 >
  constexpr size_type get() const noexcept
  {
    static_assert(
      Dim < rank, 
      "dimension should be less than Rank (dimension count starts from 0)" 
    );
    return std::get<Dim>( index_ );
  }

  //! \brief access the individual bounds for a specific dimension
  //! \param [in] component_idx the component to return
  //! \return the index
  constexpr reference operator[](size_type component_idx) noexcept 
  { return index_[component_idx]; };

  //! \brief access the individual bounds for a specific dimension
  //! \param [in] component_idx the component to return
  //! \return the index
  constexpr const_reference operator[](size_type component_idx) const noexcept 
  { return index_[component_idx]; };

  //! \brief access the individual bounds for a specific dimension
  //! \remark this version has bounds checking
  //! \param [in] component_idx the component to return
  //! \return the index
  constexpr reference at(size_type component_idx)
  { 
    if ( component_idx < rank )
      return index_[component_idx];
    else
      throw std::out_of_range("at() argument out of range");
  };

  //! \brief access the individual bounds for a specific dimension
  //! \remark this version has bounds checking
  //! \param [in] component_idx the component to return
  //! \return the index
  constexpr const_reference at(size_type component_idx) const
  { 
    return  component_idx < rank ? index_[component_idx] : 
      throw std::out_of_range("at() argument out of range");
  };

  //! \brief shift the indices to the left
  constexpr sliced_type shift_left() const noexcept
  {
    sliced_type idx;
    for ( size_type i=1; i<rank; i++ )
      idx.index_[i-1] = index_[i];
    return idx;
  }

  //! \brief return the begining iterator {0} 
  //! \return an iterator to the first index
  constexpr const auto & as_array() const noexcept 
  { return index_; };

  //! \brief return the begining iterator {0} 
  //! \return an iterator to the first index
  const_pointer begin() const noexcept 
  { return index_.begin(); };

  //! \brief return the end iterator which is just past the bounds
  //! \return an iterator past the bounds
  const_pointer end() const noexcept
  { return index_.end(); }
  /// @}

  /// @}

  //============================================================================
  /// \name Comparison operators
  //============================================================================
  /// @{
  //! \brief test for equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if equal
  constexpr bool operator==(const index_t & rhs) const noexcept 
  {  
    return std::equal( index_.begin(), index_.end(), rhs.index_.begin() ); 
  };

  //! \brief test for non-equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if not equal
  constexpr bool operator!=(const index_t & rhs) const noexcept
  {
    return !( *this == rhs );
  };


  //! \brief check if one index is less than the other, i.e. one < other
  //! \param [in] rhs   the multidimensional index on the lhs
  //! \return true if lhs < rhs
  constexpr bool operator<(const index_t& rhs) const noexcept
  {
    for (size_type i = 0; i < rank; ++i) {
      if (index_[i] < rhs.index_[i]) return true;
    }
    return false;
  }

  //! \brief test <=
  //! \param [in] rhs the object on the right hand side of the operator
  constexpr bool operator<=(const index_t& rhs) const noexcept 
  { return !(rhs < *this); }

  //! \brief test >
  //! \param [in] rhs the object on the right hand side of the operator
  constexpr bool operator>(const index_t& rhs) const noexcept 
  { return rhs < *this; }

  //! \brief test >=
  //! \param [in] rhs the object on the right hand side of the operator
  constexpr bool operator>=(const index_t& rhs) const noexcept 
  { return !(rhs > *this); }

  //! \brief swap two indexes
  void swap(index_t& rhs) noexcept
  {
    std::swap(index_, rhs.index_);
  }

  /// @}

  //============================================================================
  /// \name Arithmatic operators
  //============================================================================
  /// @{

  //! \brief addition operator
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return return the result of the operation
  constexpr index_t operator+(const index_t<rank>& rhs) const noexcept
  { 
    auto tmp = *this;
    tmp += rhs;
    return tmp;
  };

  //! \brief minus operator
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return return the result of the operation
  constexpr index_t operator-(const index_t<rank>& rhs) const noexcept
  { 
    auto tmp = *this;
    tmp -= rhs;
    return tmp;
  };

  //! \brief in-place addition operator
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return a reference to this object
  constexpr index_t& operator+=(const index_t<rank>& rhs) noexcept
  { 
    std::transform( 
      index_.begin(), index_.end(), 
      rhs.index_.begin(), index_.begin(), 
      std::plus<value_type>{}
    );
    return *this;
  };

  //! \brief in-place minus operator
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return a reference to this object
  constexpr index_t& operator-=(const index_t<rank>& rhs) noexcept
  { 
    std::transform( 
      index_.begin(), index_.end(), 
      rhs.index_.begin(), index_.begin(), 
      std::minus<value_type>{}
    );
    return *this;
  };

  //! \brief multiply operator for arithmetic types only
  //! \tparam T must be an arithmetic type
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return return the result of the operation
  template< typename T >
  constexpr
  std::enable_if_t<std::is_arithmetic<T>::value, index_t> 
  operator*(T v) const noexcept
  { 
    auto tmp = *this;
    tmp *= v;
    return tmp;
  };
  
  //! \brief division operator for arithmetic types only
  //! \tparam T must be an arithmetic type
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return return the result of the operation
  template< typename T >
  constexpr
  std::enable_if_t<std::is_arithmetic<T>::value, index_t> 
  operator/(T v) const noexcept
  { 
    auto tmp = *this;
    tmp /= v;
    return tmp;
  };


  //! \brief namespace multiplication operator
  //! \tparam R the rank of the bounds object
  //! \param [in] lhs the object on the left hand side of the operator
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return the result of the operation
  template< typename T > 
  friend constexpr auto operator*( T lhs, const index_t & rhs ) noexcept
  {
    return rhs * lhs;
  }
  

  //! \brief in-place multiply operator for arithmetic types only
  //! \tparam T must be an arithmetic type
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return a reference to this object
  template< typename T >
  constexpr 
  std::enable_if_t<std::is_arithmetic<T>::value, index_t&> 
  operator*=(T v) noexcept
  { 
    std::transform( 
      index_.begin(), index_.end(), index_.begin(),
      [v](auto x) { return std::multiplies<value_type>{}(x, v); }
    );
    return *this;
  };

  //! \brief in-place division operator for arithmetic types only
  //! \tparam T must be an arithmetic type
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return a reference to this object
  template< typename T >
  constexpr 
  std::enable_if_t<std::is_arithmetic<T>::value, index_t&> 
  operator/=(T v) noexcept
  { 
    std::transform(
      index_.begin(), index_.end(), index_.begin(),
      [v](auto x) { return std::divides<value_type>{}(x, v); }
    );
    return *this;
  };

  /// @}

  //============================================================================
  /// \name Unary operators
  //============================================================================
  /// @{

  //! \brief unary + operator
  //! \return a copy of this object
  constexpr auto operator+() const noexcept
  { return *this; }

  //! \brief unary - operator
  //! \return a copy of this object negated
  constexpr auto operator-() const noexcept
  {
    index_t tmp;
    std::transform( 
      index_.begin(), index_.end(), tmp.index_.begin(), 
      std::negate<value_type>{}
    );
    return tmp;
  }

  //! \brief prefix increement
  //! \remark only valid for Rank=1
  //! \tparam R the rank
  //! \return a reference to the incremented object
  template< int R = rank >
  constexpr 
  std::enable_if_t< (R==1), index_t& > operator++() noexcept
  { 
    ++index_[0]; 
    return *this;
  }

  //! \brief prefix decrement
  //! \remark only valid for Rank=1
  //! \tparam R the rank
  //! \return a reference to the decremented object
  template< int R = rank >
  constexpr 
  std::enable_if_t< (R==1), index_t& > operator--() noexcept
  { 
    --index_[0]; 
    return *this;
  }

  //! \brief postfix increement
  //! \remark only valid for Rank=1
  //! \tparam R the rank
  //! \return a copy of the incremented object
  template< int R = rank >
  constexpr 
  std::enable_if_t< (R==1), index_t > operator++(int) noexcept
  { 
    auto tmp = *this;
    ++(*this); 
    return tmp;
  }

  //! \brief postfix decrement
  //! \remark only valid for Rank=1
  //! \tparam R the rank
  //! \return a copy of the decremented object
  template< int R = rank >
  constexpr 
  std::enable_if_t< (R==1), index_t > operator--(int) noexcept
  { 
    auto tmp = *this;
    --(*this); 
    return tmp;
  }
  /// @}

protected:

  //============================================================================
  /// \name private data
  //============================================================================
  /// @{  
  std::array<value_type, rank> index_ = {};
  /// @}

};

////////////////////////////////////////////////////////////////////////////////    
//! forward declarations
////////////////////////////////////////////////////////////////////////////////    
template <typename IndexType>
class bounds_iterator;

////////////////////////////////////////////////////////////////////////////////    
/// \brief the bounds represenation
///
/// This is an N-dimensional axis aligned rectangle with the minimum point at 0
////////////////////////////////////////////////////////////////////////////////    
template <int Rank>
class strided_bounds {

  //! \brief declare other variations of bound_t as a friend
  template< int R >
  friend class strided_bounds;

public:

  //============================================================================
  /// \name types
  //============================================================================
  /// @{
  //! \brief the number of dimensions in the rectangle
  static constexpr auto rank = Rank;
  //! \brief the index type
  using index_type = index_t<Rank>;
  using const_index_type = std::add_const_t<index_type>;
  //! \brief the type of index, which is ptrdiff_t
  //! This allows the index to both address every byte in the largest allocation 
  //! and express any offset in the same
  using value_type = typename index_type::value_type;
  //! \brief the reference to a value
  using reference = value_type &;
  using const_reference = const value_type &;
  //! \brief the size type used 
  using size_type = std::size_t;
  //! \brief the iterator type
  using iterator = bounds_iterator<const_index_type>;
  using const_iterator = bounds_iterator<const_index_type>;

  //! a slice type
  using sliced_type = std::conditional_t<rank != 0, strided_bounds<rank - 1>, void>;
  /// @}

  //============================================================================
  /// \name construct/copy
  //============================================================================
  /// @{
  
  //! \brief the default constructor
  constexpr strided_bounds() noexcept = default;
  //! \brief the default copy constructor
  constexpr strided_bounds(const strided_bounds &) noexcept = default;
  //! \brief the default move constructor
  constexpr strided_bounds(strided_bounds &&) noexcept = default;
  //! \brief the default assignment operator
  strided_bounds& operator=(const strided_bounds &) noexcept = default;
  //! \brief the default move assignment operator
  strided_bounds& operator=(strided_bounds &&) noexcept = default;

  //! \brief constructor with values, must be the same number as rank
  template <
    typename... T,
    typename = typename std::enable_if_t< (sizeof...(T) == Rank) >
  > 
  constexpr strided_bounds(T... ts) noexcept : 
    bounds_{ std::forward<T>(ts)... }, 
    strides_( detail::make_strides<index_type>{}( std::forward<T>(ts)... ) )
  {
  };

  //! \brief single parameter array constructor
  //! \remark The array bounds are derived from the extents
  //! \param [in] arr  the container to set the bounds to
  template<
    typename ArrayType,
    typename = std::enable_if_t< std::rank<ArrayType>::value == rank  >
  >
  constexpr explicit strided_bounds(ArrayType & arr) noexcept :
    strided_bounds( arr, std::make_index_sequence< std::rank<ArrayType>::value >{} )
  {   }

  //! \brief constructor with static array, must be the same size as rank\
  //! \tparam N the rank of the array, must equal Rank
  //! \param [in] vals  the values to set
  constexpr strided_bounds(const value_type (&vals)[rank]) noexcept :
    bounds_(vals),
    strides_( detail::make_strides<index_type>{}( vals ) )
  {  };

  //! \brief constructor with static array, must be the same size as rank\
  //! \tparam N the rank of the array, must equal Rank
  //! \param [in] vals  the values to set
  constexpr strided_bounds(const value_type (&vals)[rank], index_type strides) noexcept :
    bounds_(vals), strides_( std::move(strides) )
  {};

  //! \brief constructor with index_type and strides
  //! \param [in] bounds  the bounds to set
  //! \param [in] stride  the strides to set
  constexpr strided_bounds(const index_type & bounds, const index_type & strides) noexcept :
    bounds_(bounds), strides_(strides)
  { };

  /// @}

  //============================================================================
  /// \name Accessors
  //============================================================================
  /// @{

  //! \brief access the individual bounds for a specific dimension
  //! \param [in] component_idx the component to return
  //! \return the bounds
  constexpr const_reference operator[](size_type component_idx) const noexcept 
  { return bounds_[component_idx]; };

  //! \brief return the extent of the array
  //! \tparam Dim the dimension to query
  template< size_type Dim = 0 >
  constexpr size_type extent() const noexcept
  {
    static_assert(
      Dim < rank, 
      "dimension should be less than Rank (dimension count starts from 0)" 
    );
    return bounds_.template get<Dim>();
  }

  /// @}

  //============================================================================
  /// \name strided_bounds functions
  //============================================================================
  /// @{

  //! \brief the volume of the domain
  //! \return the product of all dimensions
  constexpr auto size() const noexcept
  { 
    size_type ret = 1;
    for (size_t i = 0; i < rank; ++i) 
      ret *= bounds_[i];
    return ret;
  }

  //! \brief the total volume of the contiguous chunk
  constexpr auto total_size() const noexcept
  { 
    size_type ret = 1;
    for (size_t i = 0; i < rank; ++i) 
      ret += (bounds_[i] - 1) * strides_[i];
    return ret;
  }

  //! \brief is particular index inside the domain bounds
  //! \param [in] idx the index to check against the bounds
  //! \return true if idx is within the bounds
  constexpr bool contains(const index_type & idx) const noexcept
  {
    for ( size_type i=0; i<rank; i++ )
      if ( idx[i] < 0 || idx[i] >= bounds_[i] )
        return false;
    return true;
  }

  //! \brief return the stride of the array
  constexpr const index_type & strides() const noexcept
  { return strides_; }

  constexpr const value_type & stride() const noexcept
  { return strides_[0]; }

  //! \brief return the stride of the array
  constexpr const index_type & as_index() const noexcept
  { return bounds_; }

  //! \brief comnpute a 1d index from a multidimensional one
  //! \param [in] idx the index to linearize
  constexpr auto linearize( const index_type & idx ) const noexcept {
    auto offset = idx[0] * strides_[0];
    for ( size_type i=1; i<rank; i++ ) offset += idx[i] * strides_[i];
    return offset; 
  }

  //! \brief slice the bounds, i.e. fix the major dimension
  template< bool Enabled = (Rank > 1), typename Ret = std::enable_if_t<Enabled, sliced_type> >
  constexpr Ret slice() const noexcept 
  {
    return  { bounds_.shift_left(), strides_.shift_left() };
  }

  //! \brief return the begining iterator {0} 
  //! \return an iterator to the first index
  constexpr auto begin() const noexcept 
  { return const_iterator( *this, index_type{} ); };

  //! \brief return the end iterator which is just past the bounds
  //! \return an iterator past the bounds
  constexpr auto end() const noexcept
  { return const_iterator( *this, bounds_ ); }
  /// @}


  //============================================================================
  /// \name Comparison operators
  //============================================================================
  /// @{
  //! \brief test for equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if equal
  constexpr bool operator==(const strided_bounds & rhs) const noexcept 
  {  
    return ( bounds_ == rhs.bounds_ );
  };

  //! \brief test for non-equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if not equal
  constexpr bool operator!=(const strided_bounds & rhs) const noexcept
  {
    return ( bounds_ != rhs.bounds_ );
  };
  /// @}


protected:

  //============================================================================
  /// \name private utilities
  //============================================================================
  /// @{


  //! \brief constructor with static array, must be the same size as rank
  //! \tparam N the rank of the array, must equal Rank
  //! \param [in] vals  the values to set
  template < typename ArrayType, std::size_t... I > 
  constexpr strided_bounds( 
    ArrayType &, std::index_sequence<I...> ) noexcept : 
    bounds_( std::extent<ArrayType, I>::value... ),
    strides_( detail::make_strides<index_type>{}( std::extent<ArrayType, I>::value... ) )

  { };  


  /// @}

  //============================================================================
  /// \name private data
  //============================================================================
  /// @{  
  index_type bounds_;
  //! \brief the strides of the data
  index_type strides_;

  /// @}
  
};

////////////////////////////////////////////////////////////////////////////////    
/// \brief the bounds represenation
///
/// This is an N-dimensional axis aligned rectangle with the minimum point at 0
////////////////////////////////////////////////////////////////////////////////    
template <int Rank>
class contiguous_bounds {

  //! \brief declare other variations of bound_t as a friend
  template< int R >
  friend class contiguous_bounds;

public:

  //============================================================================
  /// \name types
  //============================================================================
  /// @{
  //! \brief the number of dimensions in the rectangle
  static constexpr auto rank = Rank;
  //! \brief the index type
  using index_type = index_t<Rank>;
  using const_index_type = std::add_const_t<index_type>;
  //! \brief the type of index, which is ptrdiff_t
  //! This allows the index to both address every byte in the largest allocation 
  //! and express any offset in the same
  using value_type = typename index_type::value_type;
  //! \brief the reference to a value
  using reference = value_type &;
  using const_reference = const value_type &;
  //! \brief the size type used 
  using size_type = std::size_t;
  //! \brief the iterator type
  using iterator = bounds_iterator<const_index_type>;
  using const_iterator = bounds_iterator<const_index_type>;

  //! a slice type
  using sliced_type = std::conditional_t<rank != 0, contiguous_bounds<rank - 1>, void>;
  /// @}

  //============================================================================
  /// \name construct/copy
  //============================================================================
  /// @{
  
  //! \brief the default constructor
  constexpr contiguous_bounds() noexcept = default;
  //! \brief the default copy constructor
  constexpr contiguous_bounds(const contiguous_bounds &) noexcept = default;
  //! \brief the default move constructor
  constexpr contiguous_bounds(contiguous_bounds &&) noexcept = default;
  //! \brief the default assignment operator
  contiguous_bounds& operator=(const contiguous_bounds &) noexcept = default;
  //! \brief the default move assignment operator
  contiguous_bounds& operator=(contiguous_bounds &&) noexcept = default;

  //! \brief constructor with values, must be the same number as rank
  template <
    typename... T,
    typename = typename std::enable_if_t< (sizeof...(T) == Rank) >
  > 
  constexpr contiguous_bounds(T... ts) noexcept : 
    bounds_{ std::forward<T>(ts)...},
    strides_( detail::make_strides<index_type>{}( std::forward<T>(ts)... ) )
  {  };

  //! \brief single parameter array constructor
  //! \remark The array bounds are derived from the extents
  //! \param [in] arr  the container to set the bounds to
  template<
    typename ArrayType,
    typename = std::enable_if_t< std::rank<ArrayType>::value == rank  >
  >
  constexpr explicit contiguous_bounds(ArrayType & arr) noexcept :
    contiguous_bounds( arr, std::make_index_sequence< std::rank<ArrayType>::value >{} )
  {  };

  //! \brief constructor with static array, must be the same size as rank \
  //! \tparam N the rank of the array, must equal Rank
  //! \param [in] vals  the values to set
  constexpr contiguous_bounds(const value_type (&vals)[rank]) noexcept :
    bounds_(vals),
    strides_( detail::make_strides<index_type>{}( vals ) )
  {  };

  //! \brief constructor with index_type and strides
  //! \param [in] bounds  the bounds to set
  constexpr explicit contiguous_bounds(const index_type & bounds) noexcept :
    bounds_(bounds), strides_( detail::make_strides<index_type>{}( bounds.as_array() ) )
  { };

  /// @}

  //============================================================================
  /// \name Accessors
  //============================================================================
  /// @{
  //! \brief access the individual bounds for a specific dimension
  //! \param [in] component_idx the component to return
  //! \return the bounds
  constexpr reference operator[](size_type component_idx) noexcept 
  { return bounds_[component_idx]; };

  //! \brief access the individual bounds for a specific dimension
  //! \param [in] component_idx the component to return
  //! \return the bounds
  constexpr const_reference operator[](size_type component_idx) const noexcept 
  { return bounds_[component_idx]; };
  /// @}


  //! \brief return the extent of the array
  //! \tparam Dim the dimension to query
  template< size_type Dim = 0 >
  constexpr size_type extent() const noexcept
  {
    static_assert(
      Dim < rank, 
      "dimension should be less than Rank (dimension count starts from 0)" 
    );
    return bounds_.template get<Dim>();
  }

  //============================================================================
  /// \name bounds functions
  //============================================================================
  /// @{
  
  //! \brief the volume of the domain
  //! \return the product of all dimensions
  constexpr auto size() const noexcept
  { 
    size_type ret = 1;
    for (size_t i = 0; i < rank; ++i) 
      ret *= bounds_[i];
    return ret;
  }
  
  //! \brief the total volume of the contiguous chunk
  constexpr auto total_size() const noexcept
  { 
    return size();
  }
  
  //! \brief is particular index inside the domain bounds
  //! \param [in] idx the index to check against the bounds
  //! \return true if idx is within the bounds
  constexpr bool contains(const index_type & idx) const noexcept
  {
    for ( size_type i=0; i<rank; i++ )
      if ( idx[i] < 0 || idx[i] >= bounds_[i] )
        return false;
    return true;
  }

  //! \brief return the stride of the array
  constexpr const index_type & strides() const noexcept
  { 
    return strides_;
  }

  constexpr const value_type & stride() const noexcept
  { 
    return strides_[0];
  }

  //! \brief return the stride of the array
  constexpr const index_type & as_index() const noexcept
  { return bounds_; }

  //! \brief comnpute a 1d index from a multidimensional one
  //! \param [in] idx the index to linearize
  constexpr auto linearize( const index_type & idx ) const noexcept 
  {
    auto offset = idx[0] * strides_[0];
    for ( size_type i=1; i<rank; i++ ) offset += idx[i] * strides_[i];
    return offset; 
  }

  //! \brief slice the bounds, i.e. fix the major dimension
  template< bool Enabled = (Rank > 1), typename Ret = std::enable_if_t<Enabled, sliced_type> >
  constexpr Ret  slice() const noexcept 
  {
    return  sliced_type( bounds_.shift_left() );
  }

  //! \brief return the begining iterator {0} 
  //! \return an iterator to the first index
  constexpr auto begin() const noexcept 
  { return const_iterator( *this, index_type{} ); };

  //! \brief return the end iterator which is just past the bounds
  //! \return an iterator past the bounds
  constexpr auto end() const noexcept
  { return const_iterator( *this, bounds_ ); }
  /// @}


  //============================================================================
  /// \name Comparison operators
  //============================================================================
  /// @{
  //! \brief test for equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if equal
  constexpr bool operator==(const contiguous_bounds & rhs) const noexcept 
  {  
    return ( bounds_ == rhs.bounds_ );
  };

  //! \brief test for non-equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if not equal
  constexpr bool operator!=(const contiguous_bounds & rhs) const noexcept
  {
    return ( bounds_ != rhs.bounds_ );
  };
  /// @}

protected:

  //============================================================================
  /// \name private utilities
  //============================================================================
  /// @{


  //! \brief constructor with static array, must be the same size as rank
  //! \tparam N the rank of the array, must equal Rank
  //! \param [in] vals  the values to set
  template < typename ArrayType, std::size_t... I > 
  constexpr contiguous_bounds( 
    ArrayType &, std::index_sequence<I...> ) noexcept : 
    bounds_( std::extent<ArrayType, I>::value... ),
    strides_( std::extent<ArrayType, I>::value... )
  { };  

  /// @}

  //============================================================================
  /// \name private data
  //============================================================================
  /// @{  

  //! \brief the bounds
  index_type bounds_;

  //! \brief the strides
  index_type strides_;
  /// @}
  
};


////////////////////////////////////////////////////////////////////////////////    
/// \brief the bounds represenation
///
/// This is an N-dimensional axis aligned rectangle with the minimum point at 0
////////////////////////////////////////////////////////////////////////////////    
template< std::ptrdiff_t FirstRange, std::ptrdiff_t... RestRanges >
class static_bounds {


  //! \brief declare other variations of bound_t as a friend
  template< std::ptrdiff_t First, std::ptrdiff_t... Rest >
  friend class static_bounds;


  //! \brief add a level of indirection to selecting the slice
  //! This is necessary because static_bounds<Args...> is 
  //! ill formed if rank==1
  template <bool, typename T, std::ptrdiff_t ...Args>
  struct slice_chooser
  {
    using type = static_bounds<Args...>;
  };

  template <typename T, std::ptrdiff_t ...Args>
  struct slice_chooser<true, T, Args...>
  {
    using type = T;
  };

public:

  //============================================================================
  /// \name types
  //============================================================================
  /// @{
  //! \brief the number of dimensions in the rectangle
  static constexpr auto rank = 1 + sizeof...(RestRanges);
  //! \brief the index type
  using index_type = index_t<rank>;
  using const_index_type = std::add_const_t<index_type>;
  //! \brief the type of index, which is ptrdiff_t
  //! This allows the index to both address every byte in the largest allocation 
  //! and express any offset in the same
  using value_type = typename index_type::value_type;
  //! \brief the reference to a value
  using reference = value_type &;
  using const_reference = const value_type &;
  //! \brief the size type used 
  using size_type = std::size_t;
  //! \brief the iterator type
  using iterator = bounds_iterator<const_index_type>;
  using const_iterator = bounds_iterator<const_index_type>;


  //! a slice type
  using sliced_type = typename slice_chooser< (rank == 1), value_type, RestRanges... >::type;

  /// @}

  //============================================================================
  /// \name construct/copy
  //============================================================================
  /// @{

  /// @}

  //============================================================================
  /// \name Accessors
  //============================================================================
  /// @{

  //! \brief access the individual bounds for a specific dimension
  //! \param [in] component_idx the component to return
  //! \return the bounds
  constexpr value_type operator[]( size_type component_idx ) noexcept 
  { return bounds_[component_idx]; };
  /// @}

  //! \brief return the extent of the array
  //! \tparam Dim the dimension to query
  template< size_type Dim = 0 >
  static constexpr size_type extent() noexcept
  {
    static_assert(
      Dim < rank, 
      "dimension should be less than Rank (dimension count starts from 0)" 
    );
    return bounds_.template get<Dim>();
  }

  /// @}

  //============================================================================
  /// \name bounds functions
  //============================================================================
  /// @{
  
  //! \brief the volume of the domain
  //! \return the product of all dimensions
  static constexpr auto size() noexcept
  { return size_; }

  
  //! \brief the total volume of the contiguous chunk
  static constexpr auto total_size() noexcept
  { 
    return size();
  }
  
  //! \brief is particular index inside the domain bounds
  //! \param [in] idx the index to check against the bounds
  //! \return true if idx is within the bounds
  static constexpr bool contains(const index_type & idx) noexcept
  {
    for ( size_type i=0; i<rank; i++ )
      if ( idx[i] < 0 || idx[i] >= bounds_[i] )
        return false;
    return true;
  }

  //! \brief return the stride of the array
  static constexpr index_type strides() noexcept
  { 
    return strides_;
  }

  static constexpr value_type stride() noexcept
  { 
    return rank > 1 ? strides_[0] : 1;
  }

  //! \brief return the stride of the array
  static constexpr index_type as_index() noexcept
  { return bounds_; }

  //! \brief comnpute a 1d index from a multidimensional one
  //! \param [in] idx the index to linearize
  static constexpr auto linearize( const index_type & idx) noexcept
  {
    value_type res = 0;
    for (size_type i=0; i < rank; i++) 
      res += idx[i] * strides_[i];
    return res;
  }


  //! \brief slice the bounds, i.e. fix the major dimension
  template< 
    bool Enabled = (rank > 1), 
    typename Ret = std::enable_if_t<Enabled, sliced_type> 
  >
  static constexpr Ret  slice() noexcept 
  {
    return  {};
  }

  //! \brief return the begining iterator {0} 
  //! \return an iterator to the first index
  constexpr auto begin() const noexcept 
  { return const_iterator( *this, index_type{} ); };

  //! \brief return the end iterator which is just past the bounds
  //! \return an iterator past the bounds
  constexpr auto end() const noexcept
  { return const_iterator( *this, bounds_ ); }
  /// @}


  //============================================================================
  /// \name Comparison operators
  //============================================================================
  /// @{
  //! \brief test for equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if equal
  constexpr bool operator==(const static_bounds & rhs) const noexcept 
  {  
    return ( bounds_ == rhs.bounds_ );
  };

  //! \brief test for non-equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if not equal
  constexpr bool operator!=(const static_bounds & rhs) const noexcept
  {
    return ( bounds_ != rhs.bounds_ );
  };
  /// @}

private:
  //============================================================================
  /// \name private data
  //============================================================================
  /// @{

  //! \brief computed size
  static constexpr auto size_ = multiply( FirstRange, RestRanges... );
  //! \brief computed bounds
  static constexpr index_type bounds_ = { FirstRange, RestRanges... };
  //! \brief computed strides
  static constexpr index_type strides_ = 
    index_type(detail::template make_strides<index_type>{}( FirstRange, RestRanges... ));

  /// @}
};


//==============================================================================
/// \brief static types
//==============================================================================

//! \brief the bounds_ data
template< std::ptrdiff_t FirstRange, std::ptrdiff_t... RestRanges >
constexpr typename static_bounds<FirstRange,RestRanges...>::index_type 
static_bounds<FirstRange,RestRanges...>::bounds_;

//! \brief the stride_ data
template< std::ptrdiff_t FirstRange, std::ptrdiff_t... RestRanges >
constexpr typename static_bounds<FirstRange,RestRanges...>::index_type 
static_bounds<FirstRange,RestRanges...>::strides_;

  
////////////////////////////////////////////////////////////////////////////////    
/// \brief the bounds represenation
////////////////////////////////////////////////////////////////////////////////    
template <typename IndexType>
class bounds_iterator : 
    public std::iterator<std::random_access_iterator_tag, IndexType> 
{

private:
  using base = std::iterator<std::random_access_iterator_tag, IndexType>;

public:

  //============================================================================
  /// \name types
  //============================================================================
  /// @{

  //! \breif get the rank
  static constexpr auto rank = IndexType::rank;

  //! \brief the value type is an index
  using typename base::value_type;
  //! \brief the standard different type
  using typename base::difference_type;
  //! \brief a pointer to the index
  using typename base::pointer;
  //! \brief a reference to the index type
  using typename base::reference;


  //! \brief an alias for the index type
  using index_type = IndexType;
  //! \brief the size_type of the index type
  using index_value_type = typename IndexType::value_type;
  //! \brief the size type
  using size_type = typename IndexType::size_type;
  /// @}

  //============================================================================
  /// \name construct/copy
  //============================================================================
  /// @{

  //! \brief an explcit constructor to create a new iterator
  //! \param [in] bnd the bounds the iterator covers
  //! \param [in] curr the current value the iterator points to
  template< typename BoundsType >
  explicit bounds_iterator(
    const BoundsType & bnd, value_type curr ) noexcept : 
    bounds_( bnd.as_index() ), current_( std::move(curr) ) 
  {};

  //! \brief default copy constructor
  bounds_iterator(const bounds_iterator& rhs) = default;
  //! \brief default move constructor
  bounds_iterator(bounds_iterator&& rhs) = default;
  //! \brief default assignement operator
  bounds_iterator& operator=(const bounds_iterator& rhs) = default;

  /// @}

  //============================================================================
  /// \name Iterator operators
  //============================================================================
  
  //! \brief return the current value
  constexpr reference operator*() const noexcept { return current_; }

  //! \brief return a pointer to the current value
  constexpr pointer operator->() const noexcept { return &current_; }

  //! \brief prefix increment opeator
  constexpr bounds_iterator& operator++() noexcept
  {
    for (size_type i = rank; i-- > 0;) {
      if (current_[i] < bounds_[i] - 1) {
        current_[i]++;
        return *this;
      }
      current_[i] = 0;
    }
    // If we're here we've wrapped over - set to past-the-end.
    current_ = bounds_;
    return *this;
  }

  //! \brief postfix increment operator
  constexpr bounds_iterator operator++(int) noexcept
  {
    auto ret = *this;
    ++(*this);
    return ret;
  }

  //! \brief prefix decrement operator
  constexpr bounds_iterator& operator--() noexcept
  {
    if ( current_ >= bounds_ ) {
      // if at the past-the-end, set to last element
      for (size_type i = 0; i < rank; ++i) {
        current_[i] = bounds_[i] - 1;
      }
      return *this;
    }
    for (size_type i = rank; i-- > 0;) {
      if (current_[i] >= 1) {
        current_[i]--;
        return *this;
      }
      current_[i] = bounds_[i] - 1;
    }
    // If we're here the preconditions were violated
    // "pre: there exists s such that r == ++s"
    THROW_RUNTIME_ERROR( "index out of range" );
    return *this;
  }

  //! \brief the postfix decrement operator
  constexpr bounds_iterator operator--(int) noexcept
  {
    auto ret = *this;
    --(*this);
    return ret;
  }

  //! \brief offet the iterator
  //! \param [in] n  the offset to set
  constexpr bounds_iterator operator+(difference_type n) const noexcept
  {
    bounds_iterator ret{*this};
    return ret += n;
  }

  //! \brief offet the iterator
  //! \param [in] n  the offset to set
  //! \param [in] rhs  the value to offset
  friend constexpr bounds_iterator operator+(difference_type n, const bounds_iterator& rhs) noexcept
  {
    return rhs + n;
  }

  //! \brief offet the iterator
  //! \param [in] n  the offset to set
  constexpr bounds_iterator& operator+=(difference_type n) noexcept
  {
    auto linear_idx = linearize(current_) + n;
    std::remove_const_t<value_type> stride = 0;
    stride[rank - 1] = 1;
    for (size_type i = rank - 1; i-- > 0;) {
      stride[i] = stride[i + 1] * bounds_[i + 1];
    }
    for (size_type i = 0; i < rank; ++i) {
      current_[i] = linear_idx / stride[i];
      linear_idx = linear_idx % stride[i];
    }
    // index is out of bounds of the array
    assert( (current_ >= index_type{}) && (bounds_ >= current_) );
    return *this;
  }

  //! \brief offet the iterator
  //! \param [in] n  the offset to set
  constexpr bounds_iterator operator-(difference_type n) const noexcept
  {
    bounds_iterator ret{*this};
    return ret -= n;
  }

  //! \brief offet the iterator
  //! \param [in] n  the offset to set
  constexpr bounds_iterator& operator-=(difference_type n) noexcept 
  { return * this += -n; }

  //! \brief determine the distanec between two iterators
  constexpr difference_type operator-(const bounds_iterator& rhs) const noexcept
  {
    return linearize(current_) - linearize(rhs.current_);
  }
  
  //! \brief access an offset of the iterator
  constexpr value_type operator[](difference_type n) const noexcept 
  { return *(*this + n); }

  //============================================================================
  /// \name Comparison operators
  //============================================================================

  /// @{
  //! \brief test for equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if equal
  constexpr bool operator==(const bounds_iterator& rhs) const noexcept
  { return current_ == rhs.current_; }

  //! \brief test for non-equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if not equal
  constexpr bool operator!=(const bounds_iterator& rhs) const noexcept 
  { 
    return !(*this == rhs); 
  }

  //! \brief test less-than
  //! \param [in] rhs the object on the right hand side of the operator
  constexpr bool operator<(const bounds_iterator& rhs) const noexcept
  { return (current_ < rhs.current_); }

  //! \brief test <=
  //! \param [in] rhs the object on the right hand side of the operator
  constexpr bool operator<=(const bounds_iterator& rhs) const noexcept 
  { return !(rhs < *this); }

  //! \brief test >
  //! \param [in] rhs the object on the right hand side of the operator
  constexpr bool operator>(const bounds_iterator& rhs) const noexcept 
  { return rhs < *this; }

  //! \brief test >=
  //! \param [in] rhs the object on the right hand side of the operator
  constexpr bool operator>=(const bounds_iterator& rhs) const noexcept 
  { return !(rhs > *this); }

  //! \brief swap two iterators
  void swap(bounds_iterator& rhs) noexcept
  {
    std::swap(bounds_, rhs.bounds_);
    std::swap(current_, rhs.current_);
  }

  /// @}

private:

  //============================================================================
  /// \name private utilities
  //============================================================================
  /// @{

  //! \brief compute a linearized 1d index
  //! \param [in] idx   the multidimensional index
  constexpr index_value_type linearize(const value_type& idx) const noexcept
  {
    // TODO: Smarter impl.
    index_value_type multiplier = 1;
    index_value_type res = 0;
    // Check if past-the-end
    if (idx >= bounds_) {
      res = 1;
      for (size_type i = rank; i-- > 0;) {
        res += (idx[i] - 1) * multiplier;
        multiplier *= bounds_[i];
      }
    }
    // not past the end
    else
    {
      for (size_type i = rank; i-- > 0;) {
        res += idx[i] * multiplier;
        multiplier *= bounds_[i];
      }
    }
    return res;
  }
  /// @}

  //============================================================================
  /// \name private data
  //============================================================================
  /// @{

  //! \brief storage for the bounds
  value_type bounds_;
  //! \brief storage for the current index
  std::remove_const_t<value_type> current_;

  /// @}

};


////////////////////////////////////////////////////////////////////////////////    
/// \brief The iterator type for the strided array view
////////////////////////////////////////////////////////////////////////////////    
template <typename ArrayView>
class strided_iterator
  : public std::iterator<std::random_access_iterator_tag, typename ArrayView::value_type>
{

  //! \brief the base type
  using base = std::iterator<std::random_access_iterator_tag, typename ArrayView::value_type>;

public:

  //============================================================================
  /// \name types
  //============================================================================
  /// @{

  //! \brief the types extracted from the base class
  using typename base::reference;
  using typename base::pointer;
  using typename base::difference_type;
  using typename base::value_type;

  /// @}


  //============================================================================
  /// \name constructors
  //============================================================================
  /// @{

  //! \brief the main constructor
  //! \param [in] container   a pointer to the container object
  //! \param [in] is_begin    true if this is the beginngin, false if starts at end
  strided_iterator(const ArrayView* container, bool is_begin)
    : container_(container), 
      it_( is_begin ? container->bounds().begin() : container->bounds().end() )
  {  }

  /// @}

  //============================================================================
  /// \name Dereferenceing operators
  //============================================================================
  /// @{

  //! \brief dereferencing operators
  reference operator*() noexcept { return  (*container_)[*it_]; }
  pointer  operator->() noexcept { return &(*container_)[*it_]; }

  /// @}

  //============================================================================
  /// \name Incrementing / decrementing operators
  //============================================================================
  /// @{

  //! \brief prefix increment operator
  strided_iterator& operator++() noexcept
  {
    ++it_;
    return *this;
  }

  //! \brief postfix increment operator
  strided_iterator operator++(int) noexcept
  {
    auto ret = *this;
    ++(*this);
    return ret;
  }

  //! \brief prefix decrement operator
  strided_iterator& operator--() noexcept
  {
    --it_;
    return *this;
  }

  //! \brief postfix decrement operator
  strided_iterator operator--(int) noexcept
  {
    auto ret = *this;
    --(*this);
    return ret;
  }

  //! \brief increment by set value
  //! \param [in]  n   the value to increment by
  strided_iterator operator+(difference_type n) const noexcept
  {
    strided_iterator ret{*this};
    return ret += n;
  }

  //! \brief namespace increment by set value
  //! \param [in]  n  the value to increment by
  //! \param [in]  rhs  the value to increment
  friend strided_iterator 
  operator+(difference_type n, const strided_iterator & rhs) noexcept
  {
    return rhs + n;
  }

  //! \brief in place increment by set value
  //! \param [in]  n   the value to increment by
  strided_iterator& operator+=(difference_type n) noexcept
  {
    it_ += n;
    return *this;
  }

  //! \brief decrement by set value
  //! \param [in]  n   the value to decrement by
  strided_iterator operator-(difference_type n) const noexcept
  {
    strided_iterator ret{*this};
    return ret -= n;
  }

  //! \brief in place decrement by set value
  //! \param [in]  n   the value to decrement by
  strided_iterator& operator-=(difference_type n) noexcept 
  { 
    return * this += -n; 
  }

  //! \brief decrement by iterator
  //! \param [in]  rhs  the iterator to decrement by
  difference_type operator-(const strided_iterator& rhs) const noexcept
  {
    assert(container_ == rhs.container_);
    return it_ - rhs.it_;
  }

  //! \brief brackets iterator offset 
  //! \param [in]  n   the value to increment by
  value_type operator[](difference_type n) const noexcept
  {
    return (*container_)[it_[n]];
    ;
  }

  /// @}

  //============================================================================
  /// \name Comparison operators
  //============================================================================
  /// @{

  bool operator==(const strided_iterator& rhs) const noexcept
  {
    assert(container_ == rhs.container_);
    return it_ == rhs.it_;
  }
  bool operator!=(const strided_iterator& rhs) const noexcept 
  { 
    return !(*this == rhs); 
  }
  bool operator<(const strided_iterator& rhs) const noexcept
  {
    assert(container_ == rhs.container_);
    return it_ < rhs.it_;
  }
  bool operator<=(const strided_iterator& rhs) const noexcept 
  { 
    return !(rhs < *this); 
  }
  bool operator>(const strided_iterator& rhs) const noexcept 
  { 
    return rhs < *this; 
  }
  bool operator>=(const strided_iterator& rhs) const noexcept { 
    return !(rhs > *this); 
  }

  //! \brief swap two iterators
  //! \param [in]  rhs  the iterator to swap with
  void swap(strided_iterator& rhs) noexcept
  {
    std::swap(it_, rhs.it_);
    std::swap(container_, rhs.container_);
  }

  /// @}

private:

  //============================================================================
  /// \name Private data
  //============================================================================
  /// @{

  //! \brief a pointer to the data object
  const ArrayView * container_;

  //! \brief storage for the iterator
  typename ArrayView::bounds_type::iterator it_;

  /// @}
};

////////////////////////////////////////////////////////////////////////////////    
/// \brief The iterator type for the strided array view
////////////////////////////////////////////////////////////////////////////////    
template <typename ArrayView>
class contiguous_iterator
  : public std::iterator<std::random_access_iterator_tag, typename ArrayView::value_type>
{

  //! \brief the base type
  using base = std::iterator<std::random_access_iterator_tag, typename ArrayView::value_type>;

public:

  //============================================================================
  /// \name types
  //============================================================================
  /// @{

  //! \brief the types extracted from the base class
  using typename base::reference;
  using typename base::pointer;
  using typename base::difference_type;
  using typename base::value_type;

  /// @}


  //============================================================================
  /// \name constructors
  //============================================================================
  /// @{

  //! \brief the main constructor
  //! \param [in] container   a pointer to the container object
  //! \param [in] is_begin    true if this is the beginngin, false if starts at end
  contiguous_iterator(const ArrayView* container, bool is_begin)
    : container_(container), 
      it_( is_begin ? container->data() : container->data() + container->size() )
  {  }

  /// @}

  //============================================================================
  /// \name Dereferenceing operators
  //============================================================================
  /// @{

  //! \brief dereferencing operators
  reference operator*() noexcept { return *it_; }
  pointer  operator->() noexcept { return  it_; }

  /// @}

  //============================================================================
  /// \name Incrementing / decrementing operators
  //============================================================================
  /// @{

  //! \brief prefix increment operator
  contiguous_iterator& operator++() noexcept
  {
    ++it_;
    return *this;
  }

  //! \brief postfix increment operator
  contiguous_iterator operator++(int) noexcept
  {
    auto ret = *this;
    ++(*this);
    return ret;
  }

  //! \brief prefix decrement operator
  contiguous_iterator& operator--() noexcept
  {
    --it_;
    return *this;
  }

  //! \brief postfix decrement operator
  contiguous_iterator operator--(int) noexcept
  {
    auto ret = *this;
    --(*this);
    return ret;
  }

  //! \brief increment by set value
  //! \param [in]  n   the value to increment by
  contiguous_iterator operator+(difference_type n) const noexcept
  {
    contiguous_iterator ret{*this};
    return ret += n;
  }

  //! \brief namespace increment by set value
  //! \param [in]  n  the value to increment by
  //! \param [in]  rhs  the value to increment
  friend contiguous_iterator 
  operator+(difference_type n, const contiguous_iterator & rhs) noexcept
  {
    return rhs + n;
  }

  //! \brief in place increment by set value
  //! \param [in]  n   the value to increment by
  contiguous_iterator& operator+=(difference_type n) noexcept
  {
    it_ += n;
    return *this;
  }

  //! \brief decrement by set value
  //! \param [in]  n   the value to decrement by
  contiguous_iterator operator-(difference_type n) const noexcept
  {
    contiguous_iterator ret{*this};
    return ret -= n;
  }

  //! \brief in place decrement by set value
  //! \param [in]  n   the value to decrement by
  contiguous_iterator& operator-=(difference_type n) noexcept 
  { 
    return * this += -n; 
  }

  //! \brief decrement by iterator
  //! \param [in]  rhs  the iterator to decrement by
  difference_type operator-(const contiguous_iterator& rhs) const noexcept
  {
    assert(container_ == rhs.container_);
    return it_ - rhs.it_;
  }

  //! \brief brackets iterator offset 
  //! \param [in]  n   the value to increment by
  value_type operator[](difference_type n) const noexcept
  {
    return *(*this + n);
  }

  /// @}

  //============================================================================
  /// \name Comparison operators
  //============================================================================
  /// @{

  bool operator==(const contiguous_iterator& rhs) const noexcept
  {
    assert(container_ == rhs.container_);
    return it_ == rhs.it_;
  }
  bool operator!=(const contiguous_iterator& rhs) const noexcept 
  { 
    return !(*this == rhs); 
  }
  bool operator<(const contiguous_iterator& rhs) const noexcept
  {
    assert(container_ == rhs.container_);
    return it_ < rhs.it_;
  }
  bool operator<=(const contiguous_iterator& rhs) const noexcept 
  { 
    return !(rhs < *this); 
  }
  bool operator>(const contiguous_iterator& rhs) const noexcept 
  { 
    return rhs < *this; 
  }
  bool operator>=(const contiguous_iterator& rhs) const noexcept { 
    return !(rhs > *this); 
  }

  //! \brief swap two iterators
  //! \param [in]  rhs  the iterator to swap with
  void swap(contiguous_iterator& rhs) noexcept
  {
    std::swap(it_, rhs.it_);
    std::swap(container_, rhs.container_);
  }

  /// @}

private:

  //============================================================================
  /// \name Private data
  //============================================================================
  /// @{

  //! \brief a pointer to the data object
  const ArrayView * container_;

  //! \brief storage for the iterator
  pointer it_;

  /// @}
};


////////////////////////////////////////////////////////////////////////////////    
// forward declaration
////////////////////////////////////////////////////////////////////////////////    
template < typename ValueType, std::ptrdiff_t Rank >
class array_view;

template < 
  typename ValueType, 
  std::ptrdiff_t FirstDim, 
  std::ptrdiff_t... RestDims 
>
class static_array_view;

////////////////////////////////////////////////////////////////////////////////    
/// \brief represent multidimensional views onto regular collections of 
/// objects of a uniform type.
/// 
/// The view semantics convey that objects of these types do not store the 
/// actual data, but instead enables patterns congruent to that of random 
/// access iterators or pointers. 
////////////////////////////////////////////////////////////////////////////////    
template < typename ValueType, std::ptrdiff_t Rank = 1 >
class strided_array_view {


  //! \brief declare other variations of strided_array_view as a friend
  template< typename U,  std::ptrdiff_t R >
  friend class strided_array_view;

public:

  //============================================================================
  /// \name types
  //============================================================================

  /// @{
  //! \brief the bounds type
  using bounds_type = strided_bounds<Rank>;
  //! \brief the size type
  using size_type = typename bounds_type::size_type;
  //! \brief the index type
  using index_type = typename bounds_type::index_type;

  //! \brief the value type
  using value_type = ValueType;
  using const_value_type = std::add_const_t<value_type>;
  //! \brief a pointer to the data type
  using pointer = std::add_pointer_t<value_type>;
  //! \brief a reference to the data type
  using reference = std::add_lvalue_reference_t<value_type>;

  //! \brief a constant version of the same strided view
  using const_strided_array_view = strided_array_view<const_value_type, Rank>;

  //! \brief the iterators
  using iterator = strided_iterator<strided_array_view>;
  using const_iterator = strided_iterator<const_strided_array_view>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  //! a sliced type
  using sliced_type =
    std::conditional_t<Rank == 1, value_type, strided_array_view<value_type, Rank - 1>>;

  /// @}
        
  //============================================================================
  /// \name construct/copy
  //============================================================================
  /// @{

  //! \brief default constructor
  constexpr strided_array_view() noexcept = default;
  //! \brief default copy constructor
  constexpr strided_array_view(const strided_array_view&) noexcept = default; 
  //! \brief default move constructor
  constexpr strided_array_view(strided_array_view&&) noexcept = default;
  //! \brief default assignement operator
  strided_array_view& operator=(const strided_array_view&) noexcept = default;
  //! \brief default move assignement operator
  strided_array_view& operator=(strided_array_view&&) noexcept = default;


  //! \brief single parameter strided_array_view constructor
  //! \remark Data must be convertible to pointer
  //! \remark This serves a copy constructor but also as an implicit conversion
  //!         between related strided_array_view types, .e.g. converting non-const 
  //!         to const data
  //! \param [in] rhs  the array_vew to set the new view to
  template<typename ViewValueType>
  constexpr strided_array_view( 
    const strided_array_view<ViewValueType, Rank>& rhs,
    std::enable_if_t< std::is_convertible< std::add_pointer_t<ViewValueType>, pointer>::value >* = nullptr
  ) noexcept :
    data_( rhs.data() ), bounds_( rhs.bounds() )
  {  };

  //! \brief single parameter from array_view constructor
  //! \remark Data must be convertible to pointer
  //! \remark This serves as an implicit conversion
  //!         between related array_view types, .e.g. converting non-const 
  //!         to const data
  //! \param [in] rhs  the array_vew to set the new view to
  template<
    typename ViewValueType, 
    int ViewRank,
    bool Enabled1 = std::is_convertible< std::add_pointer_t<ViewValueType>, pointer>::value,
    bool Enabled2 = (ViewRank == Rank),
    std::enable_if_t< Enabled1 && Enabled2 >* = nullptr
  >
  constexpr strided_array_view( 
    const array_view<ViewValueType, ViewRank>& rhs  ) noexcept :
    data_( rhs.data() ), bounds_( rhs.bounds().as_index(), rhs.bounds().strides() )
  {  };


  //! \brief single parameter from static_array_view constructor
  //! \remark Data must be convertible to pointer
  //! \remark This serves as an implicit conversion
  //!         between related array_view types, .e.g. converting non-const 
  //!         to const data
  //! \param [in] rhs  the array_vew to set the new view to
  template<
    typename ViewValueType, 
    std::ptrdiff_t... Dimensions,
    bool Enabled1 = std::is_convertible< std::add_pointer_t<ViewValueType>, pointer>::value,
    bool Enabled2 = (sizeof...(Dimensions) == Rank),
    typename = std::enable_if_t< Enabled1 && Enabled2 >
  >
  constexpr strided_array_view( 
    const static_array_view<ViewValueType, Dimensions...>& rhs  ) noexcept :
    data_( rhs.data() ), bounds_( rhs.bounds().as_index(), rhs.bounds().strides() )
  {  };


  //! \brief strided_array_view copy assignemnt operator
  //! \remark Data must be convertible to pointer
  //! \remark This serves a copy constructor but also as an implicit conversion
  //!         between related strided_array_view types, .e.g. converting non-const 
  //!         to const data
  //! \param [in] rhs  the array_vew to set the new view to
  template<typename ViewValueType>
  std::enable_if_t< 
    std::is_convertible< std::add_pointer_t<ViewValueType>, pointer>::value, 
    strided_array_view&  
  >
  operator=(const strided_array_view<ViewValueType, Rank>& rhs) noexcept
  {
    data_ = rhs.data();
    bounds_ = rhs.bounds();
    return *this;
  }

  //! \brief single parameter container
  //! \remark only allowed for rank = 1
  //! \remark Note this constructor also allows for converting strided_array_views with 
  //!         rank>1 to strided_array_views with rank=  1, i.e. flattening
  //! \remark only for stl-like containers
  //! \param [in] cont  the container to set the view to
  template<
    typename Container,
    typename = typename std::enable_if_t< 
      is_minimal_container_v<Container> && (Rank == 1)
    >
  >
  constexpr explicit strided_array_view(Container & cont) noexcept :
    data_( cont.data() ), 
    bounds_( cont.size() )
  {  }


  //! \brief two parameter constructor with bounds and container
  //! \remark 
  //! \remark only for stl-like containers
  //! \param [in] bounds  the bounds of the view to set
  //! \param [in] cont  the container to set the view to
  template<
    typename Container,
    typename = typename std::enable_if_t< 
      is_minimal_container_v<Container>
    >
  >
  constexpr strided_array_view(Container& cont, bounds_type bounds) noexcept :
    data_( cont.data() ), 
    bounds_( bounds )
  {
    // the container size() must be greater than or equal to the bounds size
    assert( cont.size() >= bounds.size() && "container size is smaller than bounds" );
  }

  //! \brief single parameter array constructor
  //! \remark The array bounds are derived from the extents
  //! \remark only for arrays that can be converted to pointer with rank<> == rank
  //! \param [in] arr  the container to set the view to
  template<
    typename ArrayType,
    typename std::enable_if_t< 
      // can convert pointers
      std::is_convertible< std::add_pointer_t< std::remove_all_extents_t<ArrayType> >, pointer >::value
      // has same rank
      && std::rank<ArrayType>::value == Rank 
      // has same type
      &&  std::is_same_v< std::remove_all_extents_t<ArrayType>, value_type >
    >* = nullptr
  >
  constexpr explicit strided_array_view(ArrayType & arr) noexcept :
    strided_array_view( arr, std::make_index_sequence< std::rank<ArrayType>::value >{} )
  {  }


  //! \brief two parameter constructor with bounds and pointer
  //! \remark  pointed to storage contains at least as many adjacent objects 
  //!          as the bounds size()
  //! \remark only for arrays that can be converted to pointer with rank<> == rank
  //! \param [in] bounds  the bounds of the view to set
  //! \param [in] data  the data to set the view to
  constexpr strided_array_view(pointer data, bounds_type bounds) noexcept :
    data_( data ), bounds_( bounds )
  {  }

  //! \brief two parameter constructor with bounds and pointer
  //! \remark  pointed to storage contains at least as many adjacent objects 
  //!          as the bounds size()
  //! \remark only for arrays that can be converted to pointer with rank<> == rank
  //! \param [in] bounds  the bounds of the view to set
  //! \param [in] stride  the stride of the view to set
  //! \param [in] data  the data to set the view to
  constexpr strided_array_view(pointer data, index_type bounds, index_type stride) noexcept :
    data_( data ), bounds_( bounds, stride )
  {  }
        
  /// @}
        
        
  //============================================================================
  /// \name observers
  //============================================================================
  /// @{

  //! \brief return the total size of the array
  constexpr size_type size() const { return bounds().size(); }

  //! \brief return true if empty
  constexpr bool empty() const { return data_ != nullptr; }

  //! \brief return the bounds of the array
  constexpr const auto & bounds() const noexcept
  { return bounds_; }

  //! \brief return the stride of the array
  constexpr const auto & strides() const noexcept
  { return bounds_.strides(); }
 
  constexpr const auto & stride() const noexcept
  { return bounds_.stride(); }


  //! \brief return the rank
  static constexpr auto rank() { return Rank; }

  //! \brief return the extent of the array
  //! \tparam Dim the dimension to query
  template <size_type Dim = 0>
  constexpr size_type extent() const noexcept
  {
    static_assert(
      Dim < Rank, 
      "dimension should be less than Rank (dimension count starts from 0)" 
    );
    return bounds_.template extent<Dim>();
  }

  //! convert to a boolean
  //! \return true if empty
  constexpr explicit operator bool() const noexcept { return data_ != nullptr; }

  /// @}
        
  //============================================================================
  /// \name element access
  //============================================================================
  /// @{

  //! \brief access the element at a specified index
  //! \remark this version has no bounds checking
  //! \param [in] idx the index
  //! \return a reference to the indexed location
  constexpr reference operator[](const index_type &idx) const noexcept
  { 
    return data_[ bounds_.linearize(idx) ]; 
  }

  //! \brief access the element at a specified index
  //! \remark this version has bounds checking
  //! \param [in] idx the index
  //! \return a reference to the indexed location
  constexpr reference at(const index_type &idx) const noexcept 
  {
    // This makes at() constexpr as long as the argument is within the
    // bounds of the strided_array_view.    
    return bounds().contains(idx) ? this->operator[](idx) : 
      throw std::out_of_range("at() argument out of range");
  }

  template <
    typename... Indices,
    typename = std::enable_if_t< sizeof...(Indices) == Rank >
  >
  constexpr reference operator()(Indices... indices) const noexcept
  {
    index_type idx{indices...};
    return this->operator[](idx);
  }        
  /// \returns A pointer such that [<code>data()</code>,<code>data() +
  /// size()</code>) is a valid range. For a non-empty strided_array_view,
  /// <code>data() == &front()</code>.
  constexpr pointer data() const noexcept { return data_; }
                                                                 
  //! \brief slice an array, i.e. fix the most significant dimension
  //! \remark this version has no bounds checking
  //! \param [in] idx the index to slice at
  //! \return a reference to the indexed location
  template< bool Enabled = (Rank > 1), typename Ret = std::enable_if_t<Enabled, sliced_type> >
  constexpr Ret operator[]( size_type idx ) const noexcept
  { 
    const auto ridx = idx * bounds_.stride();
    return { data_+ridx, bounds_.slice() };
  }

  //! \brief slice an array, i.e. fix the most significant dimension
  //! \remark this version has bounds checking
  //! \param [in] slice the index
  //! \return a reference to the indexed location
  template< bool Enabled = (Rank > 1), typename Ret = std::enable_if_t<Enabled, sliced_type> >
  constexpr Ret slice( size_type idx ) const
  { 
    // This makes at() constexpr as long as the argument is within the
    // bounds of the strided_array_view.    
    return (idx >= bounds_[0] ) ? 
      throw std::out_of_range("at() argument out of range") :
      this->operator[](idx);
  }

                                                                 
  //! \brief section an array, i.e. create a sub-view
  //! \param [in] origin   the index, if non specified, use {0} origin
  //! \param [in] bnds     the new bounds, if non is specified, keep old bounds
  //! \return a the new view
  constexpr strided_array_view section() const noexcept
  { return *this; }

  constexpr strided_array_view section( const index_type & origin ) const noexcept
  { 
    assert( bounds().contains(origin) );
    auto bnds = bounds_.as_index() - origin;
    return strided_array_view( &this->operator[](origin), bnds, bounds_.strides() );
  }

  constexpr strided_array_view section( 
    const index_type & origin, 
    const index_type & bnds ) const noexcept
  { 
    assert( bounds_.contains(origin) );
    assert( origin + bnds <= bounds_.as_index() );    
    return strided_array_view( &this->operator[](origin), bnds, bounds_.strides() );
  }

  
  /// @}

  //============================================================================
  /// \name mutators
  //============================================================================
  /// @{
        
  /// Resets *this to its default-constructed state.
  void clear() { *this = strided_array_view(); }

  /// @}

  //============================================================================
  /// \name mutators
  //============================================================================
  /// @{

  //! \brief non-const iterators
  //! \return the desired iterator position
  constexpr iterator begin() const 
  { 
    return iterator{this, true}; 
  }
  constexpr iterator end() const 
  { 
    return iterator{this, false}; 
  }

  //! \brief const iterators
  //! \return the desired iterator position
  constexpr const_iterator cbegin() const
  {
    return const_iterator{reinterpret_cast<const const_strided_array_view*>(this), true};
  }
  constexpr const_iterator cend() const
  {
    return const_iterator{reinterpret_cast<const const_strided_array_view*>(this), false};
  }

  //! \brief non-const reverse iterators
  //! \return the desired iterator position
  constexpr reverse_iterator rbegin() const 
  { 
    return reverse_iterator{end()}; 
  }

  constexpr reverse_iterator rend() const 
  { 
    return reverse_iterator{begin()}; 
  }

  //! \brief const reverse iterators
  //! \return the desired iterator position
  constexpr const_reverse_iterator crbegin() const 
  { 
    return const_reverse_iterator{cend()}; 
  }

  constexpr const_reverse_iterator crend() const { 
    return const_reverse_iterator{cbegin()}; 
  }

  /// @}

  //============================================================================
  /// \name Comparison operators
  //============================================================================
  /// @{

  template <
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t< 
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> >
    >
  >
  constexpr bool operator==(const strided_array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return bounds_.size() == other.bounds_.size() &&
      (data_ == other.data_ || std::equal(this->begin(), this->end(), other.begin()));
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> >
    >
  >
  constexpr bool operator!=(const strided_array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return !(*this == other);
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator<(const strided_array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end());
  }

  template < 
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator<=(const strided_array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return !(other < *this);
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator>(const strided_array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return (other < *this);
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator>=(const strided_array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return !(*this < other);
  }


  //! swap two array views
  void swap(strided_array_view& rhs) noexcept
  {
    std::swap(data_, rhs.data_);
    std::swap(bounds_, rhs.bounds_);
  }

  /// @}


protected:


  //============================================================================
  /// \name private helpers
  //============================================================================

  //! \brief constructor with static array, must be the same size as rank
  //! \tparam N the rank of the array, must equal Rank
  //! \param [in] vals  the values to set
  template < typename ArrayType, std::size_t... I > 
  constexpr strided_array_view( 
    ArrayType & arr, std::index_sequence<I...> ) noexcept : 

    data_( reinterpret_cast<pointer>(arr) ),
    bounds_( std::extent<ArrayType, I>::value... )
  { };  

  

  //============================================================================
  /// \name private data
  //============================================================================

  //! \brief a pointer to the data
  pointer data_ = nullptr;
  //! \brief the bounds of the array in multidimensional space
  bounds_type bounds_;
  
        
};


////////////////////////////////////////////////////////////////////////////////    
/// \brief represent multidimensional views onto regular collections of 
/// objects of a uniform type.
/// 
/// The view semantics convey that objects of these types do not store the 
/// actual data, but instead enables patterns congruent to that of random 
/// access iterators or pointers.
///
/// This container assumes the data is contiguous 
////////////////////////////////////////////////////////////////////////////////    
template < typename ValueType, std::ptrdiff_t Rank = 1 >
class array_view {


  //! \brief declare other variations of array_view as a friend
  template< typename U,  std::ptrdiff_t R >
  friend class array_view;

public:

  //============================================================================
  /// \name types
  //============================================================================

  /// @{
  //! \brief the bounds type
  using bounds_type = contiguous_bounds<Rank>;
  //! \brief the size type
  using size_type = typename bounds_type::size_type;
  //! \brief the index type
  using index_type = typename bounds_type::index_type;

  //! \brief the value type
  using value_type = ValueType;
  using const_value_type = std::add_const_t<value_type>;
  //! \brief a pointer to the data type
  using pointer = std::add_pointer_t<value_type>;
  //! \brief a reference to the data type
  using reference = std::add_lvalue_reference_t<value_type>;

  //! \brief a constant version of the same view
  using const_array_view = array_view<const_value_type, Rank>;

  //! \brief a strided version of the same view
  using strided_view = strided_array_view<value_type, Rank>;

  //! \brief the iterators
  using iterator = contiguous_iterator<array_view>;
  using const_iterator = contiguous_iterator<const_array_view>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  //! a sliced type
  using sliced_type =
    std::conditional_t<Rank == 1, value_type, array_view<value_type, Rank - 1>>;

  /// @}
        
  //============================================================================
  /// \name construct/copy
  //============================================================================
  /// @{

  //! \brief default constructor
  constexpr array_view() noexcept = default;
  //! \brief default copy constructor
  constexpr array_view(const array_view&) noexcept = default; 
  //! \brief default move constructor
  constexpr array_view(array_view&&) noexcept = default;
  //! \brief default assignement operator
  array_view& operator=(const array_view&) noexcept = default;
  //! \brief default move assignement operator
  array_view& operator=(array_view&&) noexcept = default;


  //! \brief single parameter array_view constructor
  //! \remark Data must be convertible to pointer
  //! \remark This serves a copy constructor but also as an implicit conversion
  //!         between related array_view types, .e.g. converting non-const 
  //!         to const data
  //! \param [in] rhs  the array_vew to set the new view to
  template<typename ViewValueType>
  constexpr array_view( 
    const array_view<ViewValueType, Rank>& rhs,
    std::enable_if_t< std::is_convertible< std::add_pointer_t<ViewValueType>, pointer>::value >* = nullptr
  ) noexcept :
    data_( rhs.data() ), bounds_( rhs.bounds() )
  {  };

  //! \brief single parameter from static_array_view constructor
  //! \remark Data must be convertible to pointer
  //! \remark This serves as an implicit conversion
  //!         between related array_view types, .e.g. converting non-const 
  //!         to const data
  //! \param [in] rhs  the array_vew to set the new view to
  template<
    typename ViewValueType, 
    std::ptrdiff_t... Dimensions,
    bool Enabled1 = std::is_convertible< std::add_pointer_t<ViewValueType>, pointer>::value,
    bool Enabled2 = (sizeof...(Dimensions) == Rank),
    typename = std::enable_if_t< Enabled1 && Enabled2 >
  >
  constexpr array_view( 
    const static_array_view<ViewValueType, Dimensions...>& rhs  ) noexcept :
    data_( rhs.data() ), bounds_( rhs.bounds().as_index() )
  {  };

  //! \brief array_view copy assignemnt operator
  //! \remark Data must be convertible to pointer
  //! \remark This serves a copy constructor but also as an implicit conversion
  //!         between related array_view types, .e.g. converting non-const 
  //!         to const data
  //! \param [in] rhs  the array_vew to set the new view to
  template<typename ViewValueType>
  std::enable_if_t< 
    std::is_convertible< std::add_pointer_t<ViewValueType>, pointer>::value, 
    array_view&  
  >
  operator=(const array_view<ViewValueType, Rank>& rhs) noexcept
  {
    data_ = rhs.data();
    bounds_ = rhs.bounds();
    return *this;
  }

  //! \brief single parameter container
  //! \remark only allowed for rank = 1
  //! \remark Note this constructor also allows for converting array_views with 
  //!         rank>1 to array_views with rank=  1, i.e. flattening
  //! \remark only for stl-like containers
  //! \param [in] cont  the container to set the view to
  template<
    typename Container,
    typename = typename std::enable_if_t< 
      is_minimal_container_v<Container> && (Rank == 1)
    >
  >
  constexpr explicit array_view(Container & cont) noexcept :
    data_( cont.data() ), 
    bounds_( cont.size() )
  {  }


  //! \brief two parameter constructor with bounds and container
  //! \remark 
  //! \remark only for stl-like containers
  //! \param [in] bounds  the bounds of the view to set
  //! \param [in] cont  the container to set the view to
  template<
    typename Container,
    typename = typename std::enable_if_t< 
      is_minimal_container_v<Container>
    >
  >
  constexpr array_view(Container& cont, bounds_type bounds) noexcept :
    data_( cont.data() ), 
    bounds_( bounds )
  {
    // the container size() must be greater than or equal to the bounds size
    assert( cont.size() >= bounds.size() && "container size is smaller than bounds" );
  }

  //! \brief single parameter array constructor
  //! \remark The array bounds are derived from the extents
  //! \remark only for arrays that can be converted to pointer with rank<> == rank
  //! \param [in] arr  the container to set the view to
  template<
    typename ArrayType,
    typename std::enable_if_t< 
      // can convert pointers
      std::is_convertible< std::add_pointer_t< std::remove_all_extents_t<ArrayType> >, pointer >::value
      // has same rank
      && std::rank<ArrayType>::value == Rank 
      // has same type
      &&  std::is_same_v< std::remove_all_extents_t<ArrayType>, value_type >
    >* = nullptr
  >
  constexpr explicit array_view(ArrayType & arr) noexcept :
    array_view( arr, std::make_index_sequence< std::rank<ArrayType>::value >{} )
  {  }


  //! \brief two parameter constructor with bounds and pointer
  //! \remark  pointed to storage contains at least as many adjacent objects 
  //!          as the bounds size()
  //! \remark only for arrays that can be converted to pointer with rank<> == rank
  //! \param [in] bounds  the bounds of the view to set
  //! \param [in] data  the data to set the view to
  constexpr array_view(pointer data, bounds_type bounds) noexcept :
    data_( data ), bounds_( bounds )
  {  }
  /// @}
        
        
  //============================================================================
  /// \name observers
  //============================================================================
  /// @{

  //! \brief return the total size of the array
  constexpr size_type size() const { return bounds().size(); }

  //! \brief return true if empty
  constexpr bool empty() const { return data_ != nullptr; }

  //! \brief return the bounds of the array
  constexpr const auto & bounds() const noexcept
  { return bounds_; }

  //! \brief return the stride of the array
  constexpr const auto & strides() const noexcept
  { return bounds_.strides(); }
 
  constexpr const auto & stride() const noexcept
  { return bounds_.stride(); }

  //! \brief return the rank
  static constexpr auto rank() { return Rank; }

  //! \brief return the extent of the array
  //! \tparam Dim the dimension to query
  template <size_t Dim = 0>
  constexpr size_type extent() const noexcept
  {
    static_assert(
      Dim < Rank, 
      "dimension should be less than Rank (dimension count starts from 0)" 
    );
    return bounds_.template extent<Dim>();
  }

  //! convert to a boolean
  //! \return true if empty
  constexpr explicit operator bool() const noexcept { return data_ != nullptr; }

  /// @}
        
  //============================================================================
  /// \name element access
  //============================================================================
  /// @{

  //! \brief access the element at a specified index
  //! \remark this version has no bounds checking
  //! \param [in] idx the index
  //! \return a reference to the indexed location
  constexpr reference operator[](const index_type &idx) const noexcept
  { 
    return data_[ bounds_.linearize(idx) ]; 
  }

  //! \brief access the element at a specified index
  //! \remark this version has bounds checking
  //! \param [in] idx the index
  //! \return a reference to the indexed location
  constexpr reference at(const index_type &idx) const noexcept 
  {
    // This makes at() constexpr as long as the argument is within the
    // bounds of the array_view.    
    return bounds().contains(idx) ? this->operator[](idx) : 
      throw std::out_of_range("at() argument out of range");
  }

  template <
    typename... Indices,
    typename = std::enable_if_t< sizeof...(Indices) == Rank >
  >
  constexpr reference operator()(Indices... indices) const noexcept
  {
    index_type idx{indices...};
    return this->operator[](idx);
  }        
  /// \returns A pointer such that [<code>data()</code>,<code>data() +
  /// size()</code>) is a valid range. For a non-empty array_view,
  /// <code>data() == &front()</code>.
  constexpr pointer data() const noexcept { return data_; }
                                                                 
  //! \brief slice an array, i.e. fix the most significant dimension
  //! \remark this version has no bounds checking
  //! \param [in] idx the index to slice at
  //! \return a reference to the indexed location
  template< bool Enabled = (Rank > 1), typename Ret = std::enable_if_t<Enabled, sliced_type> >
  constexpr Ret operator[]( size_type idx ) const noexcept
  { 
    const auto ridx = idx * bounds_.stride();
    return { data_+ridx, bounds_.slice() };
  }

  //! \brief slice an array, i.e. fix the most significant dimension
  //! \remark this version has bounds checking
  //! \param [in] slice the index
  //! \return a reference to the indexed location
  template< bool Enabled = (Rank > 1), typename Ret = std::enable_if_t<Enabled, sliced_type> >
  constexpr Ret slice( size_type idx ) const
  { 
    // This makes at() constexpr as long as the argument is within the
    // bounds of the array_view.    
    return (idx >= bounds_[0] ) ? 
      throw std::out_of_range("at() argument out of range") :
      this->operator[](idx);
  }

                                                                 
  //! \brief section an array, i.e. create a sub-view
  //! \param [in] origin   the index, if non specified, use {0} origin
  //! \param [in] bnds     the new bounds, if non is specified, keep old bounds
  //! \return a the new view
  constexpr strided_view section() const noexcept
  { return *this; }

  constexpr strided_view section( const index_type & origin ) const noexcept
  { 
    assert( bounds().contains(origin) );
    auto bnds = bounds_.as_index() - origin;
    return strided_view( &this->operator[](origin), bnds, bounds_.strides() );
  }

  constexpr strided_view section( 
    const index_type & origin, 
    const index_type & bnds ) const noexcept
  { 
    assert( bounds_.contains(origin) );
    assert( origin + bnds <= bounds_.as_index() );    
    return strided_view( &this->operator[](origin), bnds, bounds_.strides() );
  }

  //! \brief conversion operator
  //! \return a strided version of the same view
  explicit operator strided_view() const 
  {
    return strided_view( data(), bounds_.as_index(), bounds_.strides() );
  }
  
  /// @}

  //============================================================================
  /// \name mutators
  //============================================================================
  /// @{
        
  /// Resets *this to its default-constructed state.
  void clear() { *this = array_view(); }

  /// @}

  //============================================================================
  /// \name mutators
  //============================================================================
  /// @{

  //! \brief non-const iterators
  //! \return the desired iterator position
  constexpr iterator begin() const 
  { 
    return iterator{this, true}; 
  }
  constexpr iterator end() const 
  { 
    return iterator{this, false}; 
  }

  //! \brief const iterators
  //! \return the desired iterator position
  constexpr const_iterator cbegin() const
  {
    return const_iterator{reinterpret_cast<const const_array_view*>(this), true};
  }
  constexpr const_iterator cend() const
  {
    return const_iterator{reinterpret_cast<const const_array_view*>(this), false};
  }

  //! \brief non-const reverse iterators
  //! \return the desired iterator position
  constexpr reverse_iterator rbegin() const 
  { 
    return reverse_iterator{end()}; 
  }

  constexpr reverse_iterator rend() const 
  { 
    return reverse_iterator{begin()}; 
  }

  //! \brief const reverse iterators
  //! \return the desired iterator position
  constexpr const_reverse_iterator crbegin() const 
  { 
    return const_reverse_iterator{cend()}; 
  }

  constexpr const_reverse_iterator crend() const { 
    return const_reverse_iterator{cbegin()}; 
  }

  /// @}

  //============================================================================
  /// \name Comparison operators
  //============================================================================
  /// @{

  template <
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t< 
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> >
    >
  >
  constexpr bool operator==(const array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return bounds_.size() == other.bounds_.size() &&
      (data_ == other.data_ || std::equal(this->begin(), this->end(), other.begin()));
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> >
    >
  >
  constexpr bool operator!=(const array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return !(*this == other);
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator<(const array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end());
  }

  template < 
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator<=(const array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return !(other < *this);
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator>(const array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return (other < *this);
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherRank,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator>=(const array_view<OtherValueType, OtherRank>& other) const noexcept
  {
    return !(*this < other);
  }


  //! swap two array views
  void swap(array_view& rhs) noexcept
  {
    std::swap(data_, rhs.data_);
    std::swap(bounds_, rhs.bounds_);
  }

  /// @}


protected:


  //============================================================================
  /// \name private helpers
  //============================================================================

  //! \brief constructor with static array, must be the same size as rank
  //! \tparam N the rank of the array, must equal Rank
  //! \param [in] vals  the values to set
  template < typename ArrayType, std::size_t... I > 
  constexpr array_view( 
    ArrayType & arr, std::index_sequence<I...> ) noexcept : 

    data_( reinterpret_cast<pointer>(arr) ),
    bounds_( std::extent<ArrayType, I>::value... )
  { };  

  

  //============================================================================
  /// \name private data
  //============================================================================

  //! \brief a pointer to the data
  pointer data_ = nullptr;
  //! \brief the bounds of the array in multidimensional space
  bounds_type bounds_;
  
        
};




////////////////////////////////////////////////////////////////////////////////    
/// \brief represent multidimensional views onto regular collections of 
/// objects of a uniform type.
/// 
/// The view semantics convey that objects of these types do not store the 
/// actual data, but instead enables patterns congruent to that of random 
/// access iterators or pointers.
///
/// This container assumes the data is contiguous 
////////////////////////////////////////////////////////////////////////////////    
template < 
  typename ValueType, 
  std::ptrdiff_t FirstDim, 
  std::ptrdiff_t... RestDims 
>
class static_array_view {


  //! \brief declare other variations of array_view as a friend
  template< typename U, std::ptrdiff_t FirstRange, std::ptrdiff_t... RestRanges >
  friend class static_array_view;

  //! \brief add a level of indirection to selecting the slice
  //! This is necessary because static_bounds<Args...> is 
  //! ill formed if rank==1
  template <bool, typename T, std::ptrdiff_t ...Args>
  struct slice_chooser
  {
    using type = static_array_view<T, Args...>;
  };

  template <typename T, std::ptrdiff_t ...Args>
  struct slice_chooser<true, T, Args...>
  {
    using type = T;
  };

public:

  //============================================================================
  /// \name types
  //============================================================================

  /// @{
  //! \brief the rank of the array view
  static constexpr auto Rank = sizeof...(RestDims) + 1;
  //! \brief the bounds type
  using bounds_type = static_bounds< FirstDim, RestDims... >;
  //! \brief the size type
  using size_type = typename bounds_type::size_type;
  //! \brief the index type
  using index_type = typename bounds_type::index_type;

  //! \brief the value type
  using value_type = ValueType;
  using const_value_type = std::add_const_t<value_type>;
  //! \brief a pointer to the data type
  using pointer = std::add_pointer_t<value_type>;
  //! \brief a reference to the data type
  using reference = std::add_lvalue_reference_t<value_type>;

  //! \brief a constant version of the same view
  using const_static_array_view = static_array_view<const_value_type, Rank>;

  //! \brief a strided version of the same view
  using strided_view = strided_array_view<value_type, Rank>;
  //! \brief a dynamic version of the same contiguous view
  using dynamic_view = array_view<value_type, Rank>;

  //! \brief the iterators
  using iterator = contiguous_iterator<static_array_view>;
  using const_iterator = contiguous_iterator<const_static_array_view>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;


  //! a sliced type
  using sliced_type = slice_chooser< (Rank == 1),  value_type, RestDims... >;

  /// @}
        
  //============================================================================
  /// \name construct/copy
  //============================================================================
  /// @{

  //! \brief default constructor
  constexpr static_array_view() noexcept = default;
  //! \brief default copy constructor
  constexpr static_array_view(const static_array_view&) noexcept = default; 
  //! \brief default move constructor
  constexpr static_array_view(static_array_view&&) noexcept = default;
  //! \brief default assignement operator
  static_array_view& operator=(const static_array_view&) noexcept = default;
  //! \brief default move assignement operator
  static_array_view& operator=(static_array_view&&) noexcept = default;


  //! \brief two parameter constructor that throws away the bounds if provided
  //! \remark  this is to enable interoperability between array_view and static_array_view
  //! \param [in] cont  the container to set the view to
  template< typename Container >
  constexpr static_array_view(Container && cont, bounds_type ) noexcept :
    static_array_view( std::forward<Container>(cont) )
  {  }


  //! \brief single parameter array_view constructor
  //! \remark Data must be convertible to pointer
  //! \remark This serves a copy constructor but also as an implicit conversion
  //!         between related array_view types, .e.g. converting non-const 
  //!         to const data
  //! \param [in] rhs  the array_vew to set the new view to
  template<typename ViewValueType  >
  constexpr static_array_view( 
    const static_array_view<ViewValueType, FirstDim, RestDims...>& rhs,
    std::enable_if_t< std::is_convertible< std::add_pointer_t<ViewValueType>, pointer>::value >* = nullptr 
  ) noexcept : data_( rhs.data() )
  {  };

  //! \brief array_view copy assignemnt operator
  //! \remark Data must be convertible to pointer
  //! \remark This serves a copy constructor but also as an implicit conversion
  //!         between related array_view types, .e.g. converting non-const 
  //!         to const data
  //! \param [in] rhs  the array_vew to set the new view to
  template<typename ViewValueType>
  std::enable_if_t< 
    std::is_convertible< std::add_pointer_t<ViewValueType>, pointer>::value, 
    static_array_view&  
  >
  operator=(const static_array_view<ViewValueType, FirstDim, RestDims...>& rhs) noexcept
  {
    data_ = rhs.data();
  }

  //! \brief single parameter container
  //! \remark only for stl-like containers
  //! \param [in] cont  the container to set the view to
  template<
    typename Container,
    typename = typename std::enable_if_t< 
      is_minimal_container_v<Container>
    >
  >
  constexpr explicit static_array_view(Container & cont) noexcept :
    data_( cont.data() )
  {
    // the container size() must be greater than or equal to the bounds size
    assert( cont.size() >= bounds_.size() && "container size is smaller than bounds" );
  }


  //! \brief single parameter array constructor
  //! \remark The array bounds are derived from the extents
  //! \remark only for arrays that can be converted to pointer with rank<> == rank
  //! \param [in] arr  the container to set the view to
  template<
    typename ArrayType,
    typename std::enable_if_t< 
      // can convert pointers
      std::is_convertible< std::add_pointer_t< std::remove_all_extents_t<ArrayType> >, pointer >::value
      // has same rank
      && std::rank<ArrayType>::value == Rank 
      // has same type
      &&  std::is_same_v< std::remove_all_extents_t<ArrayType>, value_type >
    >* = nullptr
  >
  constexpr explicit static_array_view(ArrayType & arr) noexcept :
    static_array_view( arr, std::make_index_sequence< std::rank<ArrayType>::value >{} )
  {  }


  //! \brief single parameter constructor with  pointer
  //! \remark  pointed to storage contains at least as many adjacent objects 
  //!          as the bounds size()
  //! \remark only for arrays that can be converted to pointer with rank<> == rank
  //! \param [in] data  the data to set the view to
  constexpr static_array_view(pointer data) noexcept : data_( data )
  {  }
        

  /// @}
        
        
  //============================================================================
  /// \name observers
  //============================================================================
  /// @{

  //! \brief return the total size of the array
  constexpr size_type size() const { return bounds().size(); }

  //! \brief return true if empty
  constexpr bool empty() const { return data_ != nullptr; }

  //! \brief return the bounds of the array
  constexpr const auto & bounds() const noexcept
  { return bounds_; }

  //! \brief return the stride of the array
  constexpr const auto & strides() const noexcept
  { return bounds_.strides(); }
 
  constexpr const auto & stride() const noexcept
  { return bounds_.stride(); }


  //! \brief return the extent of the array
  //! \tparam Dim the dimension to query
  template <size_t Dim = 0>
  constexpr size_type extent() const noexcept
  {
    static_assert(
      Dim < Rank, 
      "dimension should be less than Rank (dimension count starts from 0)" 
    );
    return bounds_.template extent<Dim>();
  }

  //! \brief return the rank
  static constexpr auto rank() { return Rank; }

  //! convert to a boolean
  //! \return true if empty
  constexpr explicit operator bool() const noexcept { return data_ != nullptr; }

  /// @}
        
  //============================================================================
  /// \name element access
  //============================================================================
  /// @{

  //! \brief access the element at a specified index
  //! \remark this version has no bounds checking
  //! \param [in] idx the index
  //! \return a reference to the indexed location
  constexpr reference operator[](const index_type &idx) const noexcept
  { 
    return data_[ bounds_.linearize(idx) ]; 
  }

  //! \brief access the element at a specified index
  //! \remark this version has bounds checking
  //! \param [in] idx the index
  //! \return a reference to the indexed location
  constexpr reference at(const index_type &idx) const noexcept 
  {
    // This makes at() constexpr as long as the argument is within the
    // bounds of the array_view.    
    return bounds().contains(idx) ? this->operator[](idx) : 
      throw std::out_of_range("at() argument out of range");
  }

  template <
    typename... Indices,
    typename = std::enable_if_t< sizeof...(Indices) == Rank >
  >
  constexpr reference operator()(Indices... indices) const noexcept
  {
    index_type idx{indices...};
    return this->operator[](idx);
  }        
  /// \returns A pointer such that [<code>data()</code>,<code>data() +
  /// size()</code>) is a valid range. For a non-empty array_view,
  /// <code>data() == &front()</code>.
  constexpr pointer data() const noexcept { return data_; }
                                                                 
  //! \brief slice an array, i.e. fix the most significant dimension
  //! \remark this version has no bounds checking
  //! \param [in] idx the index to slice at
  //! \return a reference to the indexed location
  template< 
    bool Enabled = (Rank > 1), 
    typename Ret = std::enable_if_t<Enabled, sliced_type> 
  >
  constexpr Ret operator[]( size_type idx ) const noexcept
  { 
    const auto ridx = idx * bounds_.stride();
    return { bounds_.slice(), data_+ridx };
  }

  //! \brief slice an array, i.e. fix the most significant dimension
  //! \remark this version has bounds checking
  //! \param [in] slice the index
  //! \return a reference to the indexed location
  constexpr auto slice( size_type idx ) const noexcept
  { 
    // This makes at() constexpr as long as the argument is within the
    // bounds of the array_view.    
    return (idx >= bounds_[0] ) ? 
      throw std::out_of_range("at() argument out of range") :
      this->operator[](idx);
  }


                                                                 
  //! \brief section an array, i.e. create a sub-view
  //! \param [in] origin   the index, if non specified, use {0} origin
  //! \param [in] bnds     the new bounds, if non is specified, keep old bounds
  //! \return a the new view
  constexpr strided_view section() const noexcept
  { return *this; }

  constexpr strided_view section( const index_type & origin ) const noexcept
  { 
    assert( bounds().contains(origin) );
    auto bnds = bounds_.as_index() - origin;
    return strided_view( bnds, bounds_.strides(), &this->operator[](origin) );
  }

  constexpr strided_view section( 
    const index_type & origin, 
    const index_type & bnds ) const noexcept
  { 
    assert( bounds_.contains(origin) );
    assert( origin + bnds <= bounds_.as_index() );    
    return strided_view( bnds, bounds_.strides(), &this->operator[](origin) );
  }

  //! \brief conversion operator
  //! \return a strided version of the same view
  explicit operator strided_view() const 
  {
    return strided_view( bounds_.as_index(), bounds_.strides(), data() );
  }

  //! \brief conversion operator
  //! \return a strided version of the same view
  explicit operator dynamic_view() const 
  {
    return dynamic_view( bounds_.as_index(), data() );
  }
  
  /// @}

  //============================================================================
  /// \name mutators
  //============================================================================
  /// @{
        
  /// Resets *this to its default-constructed state.
  void clear() { *this = static_array_view(); }

  /// @}

  //============================================================================
  /// \name mutators
  //============================================================================
  /// @{

  //! \brief non-const iterators
  //! \return the desired iterator position
  constexpr iterator begin() const 
  { 
    return iterator{this, true}; 
  }
  constexpr iterator end() const 
  { 
    return iterator{this, false}; 
  }

  //! \brief const iterators
  //! \return the desired iterator position
  constexpr const_iterator cbegin() const
  {
    return const_iterator{reinterpret_cast<const const_static_array_view*>(this), true};
  }
  constexpr const_iterator cend() const
  {
    return const_iterator{reinterpret_cast<const const_static_array_view*>(this), false};
  }

  //! \brief non-const reverse iterators
  //! \return the desired iterator position
  constexpr reverse_iterator rbegin() const 
  { 
    return reverse_iterator{end()}; 
  }

  constexpr reverse_iterator rend() const 
  { 
    return reverse_iterator{begin()}; 
  }

  //! \brief const reverse iterators
  //! \return the desired iterator position
  constexpr const_reverse_iterator crbegin() const 
  { 
    return const_reverse_iterator{cend()}; 
  }

  constexpr const_reverse_iterator crend() const { 
    return const_reverse_iterator{cbegin()}; 
  }

  /// @}

  //============================================================================
  /// \name Comparison operators
  //============================================================================
  /// @{

  template <
    typename OtherValueType, std::ptrdiff_t OtherFirstDim, std::ptrdiff_t... OtherRestDims,
    typename Dummy = std::enable_if_t< 
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> >
    >
  >
  constexpr bool operator==(
    const static_array_view<OtherValueType, OtherFirstDim, OtherRestDims...>& other ) const noexcept
  {
    return bounds_.size() == other.bounds_.size() &&
      (data_ == other.data_ || std::equal(this->begin(), this->end(), other.begin()));
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherFirstDim, std::ptrdiff_t... OtherRestDims,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> >
    >
  >
  constexpr bool operator!=(
    const static_array_view<OtherValueType, OtherFirstDim, OtherRestDims...>& other) const noexcept
  {
    return !(*this == other);
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherFirstDim, std::ptrdiff_t... OtherRestDims,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator<(
    const static_array_view<OtherValueType, OtherFirstDim, OtherRestDims...>& other) const noexcept
  {
    return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end());
  }

  template < 
    typename OtherValueType, std::ptrdiff_t OtherFirstDim, std::ptrdiff_t... OtherRestDims,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator<=(
    const static_array_view<OtherValueType, OtherFirstDim, OtherRestDims...>& other) const noexcept
  {
    return !(other < *this);
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherFirstDim, std::ptrdiff_t... OtherRestDims,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator>(
    const static_array_view<OtherValueType, OtherFirstDim, OtherRestDims...>& other) const noexcept
  {
    return (other < *this);
  }

  template <
    typename OtherValueType, std::ptrdiff_t OtherFirstDim, std::ptrdiff_t... OtherRestDims,
    typename Dummy = std::enable_if_t<
      std::is_same_v< std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType> > 
    >
  >
  constexpr bool operator>=(
    const static_array_view<OtherValueType, OtherFirstDim, OtherRestDims...>& other) const noexcept
  {
    return !(*this < other);
  }


  //! swap two array views
  void swap(static_array_view& rhs) noexcept
  {
    std::swap(data_, rhs.data_);
    std::swap(bounds_, rhs.bounds_);
  }

  /// @}


protected:


  //============================================================================
  /// \name private helpers
  //============================================================================

  //! \brief constructor with static array, must be the same size as rank
  //! \tparam N the rank of the array, must equal Rank
  //! \param [in] vals  the values to set
  template < typename ArrayType, std::size_t... I > 
  constexpr static_array_view( 
    ArrayType & arr, std::index_sequence<I...> ) noexcept : 
    data_( reinterpret_cast<pointer>(arr) )
  { 
    static_assert( 
      multiply( std::extent<ArrayType, I>:: value... ) >= bounds_.size(), 
      "container size is smaller than bounds"  );
  };  

  

  //============================================================================
  /// \name private data
  //============================================================================

  //! \brief a pointer to the data
  pointer data_ = nullptr;
  //! \brief the bounds of the array in multidimensional space
  static bounds_type bounds_;
  
        
};


//==============================================================================
/// \brief static types
//==============================================================================

//! \brief the bounds_ data
template < 
  typename ValueType, 
  std::ptrdiff_t FirstDim, 
  std::ptrdiff_t... RestDims 
>
typename static_array_view<ValueType,FirstDim,RestDims...>::bounds_type 
static_array_view<ValueType,FirstDim,RestDims...>::bounds_;



////////////////////////////////////////////////////////////////////////////////    
/// \name deducing constructor wrappers
///
/// These functions do the same thing as the constructor with the same
/// signature. They just allow users to avoid writing the types/bounds.
////////////////////////////////////////////////////////////////////////////////    


namespace detail {

template < typename ArrayType, std::size_t... I > 
auto make_static_array_view( ArrayType & arr, std::index_sequence<I...> ) 
{
  using value_type = std::remove_all_extents_t<ArrayType>;
  return static_array_view< value_type, std::extent<ArrayType, I>:: value... >( arr );
}

}


//! \brief general type deduction with no dimensions
//! \param [in] cont the array container
//! \return the array view
template< typename ContainerType >
auto make_array_view( ContainerType && cont) noexcept
{
  using value_type = typename std::decay_t<ContainerType>::value_type;
  return array_view<value_type>( std::forward<ContainerType>(cont) );
}


//! \brief general type deduction with dimensions passed
//! \param [in] cont the array container
//! \param [in] dims the dimensions of the array
//! \return the array view
template< 
  typename ContainerType,
  typename... Dims,
  int N = sizeof...(Dims)
>
auto make_array_view( ContainerType && rhs, Dims...dims ) noexcept
{
  using value_type = typename std::decay_t< decltype( std::declval<ContainerType>()[0] ) >;
  return array_view< value_type, N >( 
    std::forward<ContainerType>(rhs), {dims...}
  );
}



//! \brief general type deduction with dimensions passed
//! \tparam FirstDim the first dimension of the array
//! \tparam RestDims the rest of the dimensions
//! \param [in] cont the array container
//! \return the static array view
template< 
  std::ptrdiff_t FirstDim,
  std::ptrdiff_t... RestDims,
  typename ContainerType
>
auto make_static_array_view( ContainerType && cont ) noexcept
{
  using value_type = typename std::decay_t< decltype( std::declval<ContainerType>()[0] ) >;
  return static_array_view< value_type, FirstDim, RestDims... >( 
    std::forward<ContainerType>(cont)
  );
}


//! \brief special deduction for arrays with derived extents
//! \param [in] arr the array container
//! \return the array view
//! \remark this one returns a dynamic view
template<
  typename ArrayType,
  int N = std::rank<ArrayType>::value,
  typename = std::enable_if_t< std::is_array< ArrayType >::value >
>
auto make_array_view( ArrayType & arr ) noexcept
{
  using value_type = typename std::remove_all_extents<ArrayType>::type;
  return array_view< value_type, N >( arr );
}

//! \brief special deduction for arrays with derived extents
//! \param [in] arr the array 
//! \return the static array view
//! \remark this one returns a static view
template<
  typename ArrayType,
  typename = std::enable_if_t< std::is_array< ArrayType >::value >
>
auto make_static_array_view( ArrayType & arr ) noexcept
{
  using Indices = std::make_index_sequence< std::rank<ArrayType>::value >;
  return detail::make_static_array_view( arr, Indices{} );
}
    
/// @}

    
}      // End namespace
}      // End namespace
