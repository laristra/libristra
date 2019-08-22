/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////    
/// \file
/// \brief a general purpose filtering iterator.
////////////////////////////////////////////////////////////////////////////////    
#pragma once

// user includes

namespace ristra {
namespace utils {


////////////////////////////////////////////////////////////////////////////////    
/// \brief the bounds represenation
////////////////////////////////////////////////////////////////////////////////    
template <class Predicate, class Iterator>
class filter_iterator
{

public:

  //============================================================================
  /// \name types
  //============================================================================
  /// @{

  //! \brief the stl iterator types
  using value_type = typename std::iterator_traits<Iterator>::value_type;
  using difference_type = typename std::iterator_traits<Iterator>::difference_type;
  using pointer = typename std::iterator_traits<Iterator>::pointer;
  using reference = typename std::iterator_traits<Iterator>::reference;
  using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;

  //! \brief the size type
  using size_type = std::size_t;
  /// @}

  //============================================================================
  /// \name construct/copy
  //============================================================================
  /// @{

  //! \brief the default constructor is deleted since lambda functions have 
  //!        no default constructor either
  constexpr filter_iterator( ) noexcept = delete;

  //! \brief the default constructor is deleted since lambda functions have 
  //!        no default constructor either
  constexpr filter_iterator( 
    Predicate pred, Iterator first, Iterator last = Iterator() ) noexcept
    : pred_( pred ), iter_(first), end_(last) {}

  template<
    class OtherIterator,
    typename = 
      std::enable_if_t< std::is_convertible<OtherIterator, Iterator>::value >
  >
  filter_iterator( 
    filter_iterator<Predicate, OtherIterator> const& other ) noexcept
    : pred_( other.predicate() ), iter_( *other ), end_( end() )
  {}

  //! \brief default copy constructor
  filter_iterator(const filter_iterator&) = default;
  //! \brief default move constructor
  filter_iterator(filter_iterator&&) = default;
  //! \brief default assignement operator
  filter_iterator& operator=(const filter_iterator&) = default;
  //! \brief default move assignement operator
  filter_iterator& operator=(filter_iterator&&) = default;

  /// @}


  //============================================================================
  /// \name Access members
  //============================================================================

  //! \brief return the predicate
  constexpr auto predicate() const noexcept 
  { return pred_; }


  //! \brief return the end location
  constexpr auto begin() const noexcept 
  { return iter_; }

  //! \brief return the end location
  constexpr auto end() const noexcept 
  { return end_; }

  //============================================================================
  /// \name Iterator operators
  //============================================================================
  
  //! \brief return the current value
  constexpr reference operator*() const noexcept { return iter_; }

  //! \brief return a pointer to the current value
  constexpr pointer operator->() const noexcept { return &iter_; }

  //! \brief prefix increment opeator
  constexpr filter_iterator& operator++() noexcept
  {
    for (; iter_ != end_ ; ++iter_) {
      if ( pred_(*iter_) )
        return *this;
    }
    return *this;
  }

  //! \brief postfix increment operator
  constexpr filter_iterator operator++(int) noexcept
  {
    auto ret = *this;
    ++(*this);
    return ret;
  }


  //============================================================================
  /// \name Comparison operators
  //============================================================================

  /// @{
  //! \brief test for equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if equal
  constexpr bool operator==(const filter_iterator& rhs) const noexcept
  { return iter_ == rhs.iter_; }

  //! \brief test for non-equivalency
  //! \param [in] rhs the object on the right hand side of the operator
  //! \return true if not equal
  constexpr bool operator!=(const filter_iterator& rhs) const noexcept 
  { 
    return !(*this == rhs); 
  }

  //! \brief swap two iterators
  //! \param [in] rhs the other iterator to swap with
  void swap(filter_iterator& rhs) noexcept
  {
    std::swap(iter_, rhs.iter_);
    std::swap(end_, rhs.end_);
  }

  /// @}

private:

  //============================================================================
  /// \name private data
  //============================================================================
  /// @{

  //! \brief the predicate
  Predicate pred_;

  //! \brief storage for the current index
  std::remove_const_t<Iterator> iter_;
  //! \brief storage for the endindex
  Iterator end_;

  /// @}

};


////////////////////////////////////////////////////////////////////////////////    
/// \brief template helper for type deduction
////////////////////////////////////////////////////////////////////////////////    

template <class Predicate, class Iterator>
auto make_filter_iterator( Iterator && first, Iterator && last, Predicate && pred ) 
{
  return filter_iterator<Predicate, Iterator>( 
    std::forward<Predicate>(pred), 
    std::forward<Iterator>(first), 
    std::forward<Iterator>(last)
  );
}

} // namespace
} // namespace
