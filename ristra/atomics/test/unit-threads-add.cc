
const int MAXNTHREAD = 4;
const int MAXNITER = 100;

#include "unit-threads.h"

// -----------------------------------------------------------------------------
// main
// -----------------------------------------------------------------------------

// op
template<class T_OR_ATOMIC, class RHS>
void op(T_OR_ATOMIC &value, const std::size_t niter, const RHS rhs)
{
   for (std::size_t iiter = 0;  iiter < niter;  ++iiter)
      value += rhs;
}

// main
int main()
{
   {
      using T = int;
      const T initial[] = { T(-2), T(-1), T( 0), T(1), T(2) };
      const T rhs    [] = { T(10), T(-10), T(11), T(-11) };
      type<T>(initial, rhs);
   } {
      using T = unsigned;
      const T initial[] = { T(0), T(1), T(2), T(3), T(4) };
      const T rhs    [] = { T(10), T(11), T(12), T(13), T(14) };
      type<T>(initial, rhs);
   } {
      using T = int*;
      int i, j, k, l, m;
      const T initial[] = { &i, &j, &k, &l, &m };
      const int   rhs[] = { 10, 11, 12, 13, 14 };
      type<T>(initial, rhs);
   } {
      using T = float*;
      float i, j, k, l, m;
      const T initial[] = { &i, &j, &k, &l, &m };
      const int   rhs[] = { 10, 11, 12, 13, 14 };
      type<T>(initial, rhs);
   } {
      using T = double*;
      double i, j, k, l, m;
      const T initial[] = { &i, &j, &k, &l, &m };
      const int   rhs[] = { 10, 11, 12, 13, 14 };
      type<T>(initial, rhs);
   } {
      using T = float;
      const T initial[] = { T(0.1), T(1.2), T(2.3), T(3.4), T(4.5) };
      const T rhs    [] = { T(-1.1), T(2.2), T(-3.3), T(4.4), T(-5.5) };
      type<T>(initial, rhs);
   } {
      using T = double;
      const T initial[] = { T(0.1), T(1.2), T(2.3), T(3.4), T(4.5) };
      const T rhs    [] = { T(-1.1), T(2.2), T(-3.3), T(4.4), T(-5.5) };
      type<T>(initial, rhs);
   } {
      using T = std::complex<float>;
      const T initial[] = { T(0.1,-0.2), T(-1.2,3.4), T(-4.5,-6.7) };
      const T rhs    [] = { T(1.1,-2.2), T(-2.1,1.3), T(-5.4,-7.6) };
      type<T>(initial, rhs);
   } {
      using T = std::complex<double>;
      const T initial[] = { T(1.1,-2.2), T(-2.1,1.3), T(-5.4,-7.6) };
      const T rhs    [] = { T(0.1,-0.2), T(-1.2,3.4), T(-4.5,-6.7) };
      type<T>(initial, rhs);
   }
}
