/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2017 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Provides a dimensioned array which functions as a matrix.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "flecsi-sp/math/multi_array.h"
#include "flecsi-sp/math/vector.h"

// system includes
 #include <cmath>

namespace flecsi {
namespace sp {
namespace math {


////////////////////////////////////////////////////////////////////////////////
//!  \brief A specialization of multi_array for two-dimensional arrays.
//!
//!  \tparam T The type of the array, e.g., P.O.D. type.
//!  \tparam D1,D2 The dimensions of the matrix.
////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t D1, std::size_t D2> 
using matrix = multi_array<T, D1, D2>;

////////////////////////////////////////////////////////////////////////////////
//! \brief Compute the outer product of two arrays.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] a  The first vector
//! \param[in] b  The other vector
//! \return The result of the operation is a matrix of dimension `D`.
////////////////////////////////////////////////////////////////////////////////
template < 
  typename T, std::size_t D,
  template<typename, std::size_t> class C
>
auto outer_product(
  const C<T, D> &a, const C<T, D> &b
) {
  using counter_t = utils::select_counter_t< D >;

  matrix<T,D,D> tmp;
  
  // the result is symmetric, so use the iterator to make sure we are always
  // looping in favorable order
  auto it = tmp.begin();
  
  // this order does not matter
  for ( counter_t i = 0; i<D; i++ )
    for ( counter_t j = 0; j<D; j++ )
      *it++ = a[i] * b[j];

  return tmp;
}



////////////////////////////////////////////////////////////////////////////////
//! \brief Compute the outer product of two arrays.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] a  The first vector
//! \param[in] b  The other vector
//! \param[in] fact  A multiplying factor
//! \return The result of the operation is a matrix of dimension `D`.
//! \remark This version modifies a matrix in place.
////////////////////////////////////////////////////////////////////////////////
template < 
  typename T, 
  typename U,
  std::size_t D,
  template<typename, std::size_t> class C
>
void outer_product(
  const C<T, D> &a, const C<T, D> &b, matrix<T,D,D> &c, const U & fact
) {
  using counter_t = utils::select_counter_t< D >;
  
  // the result is symmetric, so use the iterator to make sure we are always
  // looping in favorable order
  
  // this order does not matter
  for ( counter_t i = 0; i<D; i++ )
    for ( counter_t j = 0; j<D; j++ )
      c[ i*D + j ] += fact * a[i] * b[j];
}


////////////////////////////////////////////////////////////////////////////////
//! \brief Compute the cofactor of a square matrix
//! \tparam T  The base value type.
//! \tparam N  The matrix dimension.
//! \param[in] mat  The matrix to invert
//! \param[in] row,col  The matrix row and column to use.
//! \return The result of the operation is a matrix one size smaller in each 
//!         dimension.
////////////////////////////////////////////////////////////////////////////////
template < typename T, std::size_t N >
auto cofactor( const matrix<T, N, N> & mat, std::size_t row, std::size_t col )
{

  using counter_t = utils::select_counter_t< N >;

  matrix<T,N-1,N-1> tmp;

  // indicate which col and row is being copied to dest
  size_t col_cnt=0, row_cnt=0;
 
  for (counter_t i = 0; i < N; i++ ) {
    if ( i != row ) {
      col_cnt = 0;
      for( counter_t j = 0; j < N; j++ ) {
        // when j is not the element
        if ( j != col ) {
          tmp(row_cnt,col_cnt) = mat(i,j);
          col_cnt++;
        }
      }
      row_cnt++;
    }
  }
 
  return tmp;
}

////////////////////////////////////////////////////////////////////////////////
//! \brief Compute the determinant of a square matrix
//! \tparam T  The base value type.
//! \tparam N  The matrix dimension.
//! \param[in] mat  The matrix to invert
//! \return The result of the operation
////////////////////////////////////////////////////////////////////////////////
//! @{
template < typename T, std::size_t N >
auto determinant( const matrix<T, N, N> & mat )
{

  using counter_t = utils::select_counter_t< N >;

  // the determinant value
  T det = 0;
 
  for(counter_t i = 0; i < N; i++ )
  {
    // get minor of element (0,i)
    auto minor = cofactor( mat, 0, i);
    // the recusion is here!
    det += (i%2==1 ? -1:1) * mat(0,i) * determinant(minor);
  }
 
  return det;
}

template < typename T >
auto determinant( const matrix<T, 1, 1> & mat )
{
  return mat(0,0);
}
//! @}

////////////////////////////////////////////////////////////////////////////////
//! \brief Compute the inverse of a square matrix
//! \tparam T  The base value type.
//! \param[in] mat  The matrix to invert
//! \return The result of the operation
////////////////////////////////////////////////////////////////////////////////
//! @{
template < typename T >
auto inverse( const matrix<T, 2, 2> & mat )
{
  matrix<T,2,2> tmp;
  auto a = mat(0,0);
  auto b = mat(0,1);
  auto c = mat(1,0);
  auto d = mat(1,1);
  tmp(0,0) =  d;
  tmp(0,1) = -b;
  tmp(1,0) = -c;
  tmp(1,1) =  a;
  auto denom = a*d - b*c;
  assert( denom != T() );
  tmp /= denom;
  return tmp;
}

template < typename T >
auto inverse( const matrix<T, 3, 3> & mat )
{
  matrix<T,3,3> tmp;

  auto a11 = mat(0,0);
  auto a12 = mat(0,1);
  auto a13 = mat(0,2);

  auto a21 = mat(1,0);
  auto a22 = mat(1,1);
  auto a23 = mat(1,2);

  auto a31 = mat(2,0);
  auto a32 = mat(2,1);
  auto a33 = mat(2,2);

  tmp(0,0) = a22*a33 - a32*a23;
  tmp(0,1) = a13*a32 - a33*a12;
  tmp(0,2) = a12*a23 - a22*a13;

  tmp(1,0) = a23*a31 - a33*a21;
  tmp(1,1) = a11*a33 - a31*a13;
  tmp(1,2) = a13*a21 - a23*a11;

  tmp(2,0) = a21*a32 - a31*a22;
  tmp(2,1) = a12*a31 - a32*a11;
  tmp(2,2) = a11*a22 - a21*a12;

  auto denom = 
    a11*a22*a33 + a12*a23*a31 + a13*a21*a32 - 
    a31*a22*a13 - a32*a23*a11 - a33*a21*a12;

  assert( denom != T() );
  
  tmp /= denom;
  
  return tmp;
}


//! \tparam N  The matrix dimension.
template < typename T, std::size_t N >
auto inverse( const matrix<T, N, N> & mat )
{

  using counter_t = utils::select_counter_t< N >;

  matrix<T,N,N> tmp;

  // get the determinant of a
  auto det = determinant(mat);
  assert( std::abs(det) > 0 );
  auto inv_det = 1 / det;

  
  for(counter_t j=0;j<N; j++) {
    for(counter_t i=0; i<N; i++) {
      // get the co-factor (matrix) of A(j,i)
      auto minor = cofactor(mat,j,i);
      // compute the result
      auto val = inv_det * determinant(minor);
      if ( (i+j)%2 == 1 ) val = val;
      tmp(i,j) = val;
    }
  }
  
  return tmp;
}
//! @}

////////////////////////////////////////////////////////////////////////////////
//! \brief Compute the product of a matrix times a vector, i.e. y = Ax + y
//! \tparam T  The base value type.
//! \tparam D1,D2  The matrix/array dimensions.
//! \param[in] A  The matrix
//! \param[in] x  The first vector that gets right multiplied by `A`
//! \param[in,out] y  The second vector 
////////////////////////////////////////////////////////////////////////////////
//! @{

template < 
  typename T, std::size_t D1, std::size_t D2,
  template<typename, std::size_t> class C
>
void ax_plus_y( const matrix<T, D1, D2> & A, const C<T,D2> & x, C<T,D1> & y )
{
  for ( utils::select_counter_t<D1> i = 0; i<D1; i++ ) {
    for ( utils::select_counter_t<D2> j = 0; j<D2; j++ )
      y[i] += A(i,j) * x[j];
  }
}

template < 
  typename T, std::size_t D1, std::size_t D2,
  template<typename, std::size_t> class C
>
void matrix_vector( 
  const T & alpha, 
  const matrix<T, D1, D2> & A, 
  const C<T,D2> & x, 
  const T & beta,
  C<T,D1> & y )
{
  for ( utils::select_counter_t<D1> i = 0; i<D1; i++ ) {
    for ( utils::select_counter_t<D2>  j = 0; j<D2; j++ )
      y[i] = alpha * A(i,j) * x[j] + beta * y[i];
  }
}
//! @}

////////////////////////////////////////////////////////////////////////////////
//! \brief Compute the product of a matrix times a vector
//! \tparam T  The base value type.
//! \tparam D1,D2  The matrix/array dimensions.
//! \param[in] lhs  The matrix
//! \param[in] rhs  The vector
////////////////////////////////////////////////////////////////////////////////
template < 
  typename T, std::size_t D1, std::size_t D2,
  template<typename, std::size_t> class C
>
auto operator*( const matrix<T, D1, D2> & lhs, const C<T,D2> & rhs )
{
  C<T,D1> tmp;
  for ( utils::select_counter_t<D1> i = 0; i<D1; i++ ) {
    tmp[i] = 0;
    for ( utils::select_counter_t<D2> j = 0; j<D2; j++ )
      tmp[i] += lhs(i,j) * rhs[j];
  }
  return tmp;
}

////////////////////////////////////////////////////////////////////////////////
//! \brief Compute the product of a matrix times a matrix
//! \tparam T  The base value type.
//! \tparam D1,D2,D3  The matrix dimensions.
//! \param[in] A,B  The matrices that get multiplied together.
//! \param[in,out] C  The result matrix.
////////////////////////////////////////////////////////////////////////////////
//! @{

template < 
  typename T, std::size_t D1, std::size_t D2, std::size_t D3
>
void matrix_multiply( 
  const matrix<T, D1, D2> & A, 
  const matrix<T, D2, D3> & B,
  matrix<T, D1, D3> & C )
{
  for ( utils::select_counter_t<D1> i = 0; i < D1; i++ )
    for ( utils::select_counter_t<D3> j = 0; j < D3; j++) {
      T sum = 0;
      for ( utils::select_counter_t<D2> k = 0; k < D2; k++) 
        sum += A(i,k)*B(k,j);
      C(i,j) += sum;
    }
}

template < 
  typename T, std::size_t D1, std::size_t D2, std::size_t D3
>
auto matrix_multiply( 
  const matrix<T, D1, D2> & A, 
  const matrix<T, D2, D3> & B )
{
  matrix<T, D1, D3> C(0);
  for ( utils::select_counter_t<D1> i = 0; i < D1; i++ )
    for ( utils::select_counter_t<D3> j = 0; j < D3; j++) {
      T sum = 0;
      for ( utils::select_counter_t<D2> k = 0; k < D2; k++) 
        sum += A(i,k)*B(k,j);
      C(i,j) += sum;
    }
  return C;
}
//! @}

////////////////////////////////////////////////////////////////////////////////
//! \brief Solve a linear system A.x = b for x.
//! \tparam T  The base value type.
//! \tparam D  The matrix/array dimension.
//! \param[in] A  The matrix
//! \param[in] B  The right hand side vector
////////////////////////////////////////////////////////////////////////////////
template < 
  typename T, std::size_t D,
  template<typename, std::size_t> class C
>
auto solve( const matrix<T, D, D> & A, const C<T,D> & b )
{
  C<T,D> x(0);
  auto inv = inverse(A);
  ax_plus_y( inv, b, x );
  return x;
}


////////////////////////////////////////////////////////////////////////////////
//! \brief Compute the rotation matrix
//! \tparam T  The base value type.
//! \tparam D  The matrix dimension.
//! \param[in] radians  The number of radians to rotate.
////////////////////////////////////////////////////////////////////////////////
template < 
  typename T, std::size_t D,
  typename = typename std::enable_if_t< (D==2) >
>
auto rotation_matrix( const T & radians ) {

  // compute some angles
  auto cos = std::cos( radians );
  auto sin = std::sin( radians );

  // create a rotation matrix
  matrix< T, D, D > rot;

  for ( utils::select_counter_t<D> i=0; i<D; i++ ) rot(i, i) = 1;

  rot(0, 0) = cos;
  rot(0, 1) = -sin;
  rot(1, 0) = sin;
  rot(1, 1) = cos;

  return rot;
}

////////////////////////////////////////////////////////////////////////////////
//! \brief Compute the reflection matrix.
//! \tparam T  The base value type.
//! \tparam D  The matrix dimension.
//! \param [in] n  The normal of the plane to reflect arround.
////////////////////////////////////////////////////////////////////////////////
template < 
  typename T, std::size_t D,
  template<typename, std::size_t> class C
>
auto reflection_matrix( const C<T,D> & n ) {

  // create a rotation matrix
  auto mat = outer_product( n, n );
  mat = - 2*mat;
  for ( utils::select_counter_t<D> i=0; i<D; i++ ) mat(i, i) += 1;

  return mat;
}

////////////////////////////////////////////////////////////////////////////////
//! \brief Compute the projection matrix
//! \tparam T  The base value type.
//! \tparam D  The matrix dimension.
//! \param [in] n  The normal to project onto.
////////////////////////////////////////////////////////////////////////////////
template < 
  typename T, std::size_t D,
  template<typename, std::size_t> class C
>
auto projection_matrix( const C<T,D> & n ) {

  // create a rotation matrix
  auto mat = outer_product( n, n );
  mat = - mat;
  for ( utils::select_counter_t<D> i=0; i<D; i++ ) mat(i, i) += 1;

  return mat;
}

} // namespace
} // namespace
} // namespace
