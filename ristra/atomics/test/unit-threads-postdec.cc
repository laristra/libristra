
const int MAXNTHREAD = 4;
const int MAXNITER = 500;

#define ATOMICS_TEST_UNARY
#include "unit-threads.h"

// -----------------------------------------------------------------------------
// main
// -----------------------------------------------------------------------------

// op
// RHS unused; we're testing a unary operator
template<class T_OR_ATOMIC, class RHS>
void op(T_OR_ATOMIC &value, const std::size_t niter, const RHS)
{
   for (std::size_t iiter = 0;  iiter < niter;  ++iiter)
      value--;
}

// main
int main()
{
   {
      using T = int;
      const T initial[] = { T(-2), T(-1), T( 0), T(1), T(2) };
      const T rhs    [] = { T(0) };
      type<T>(initial, rhs);
   } {
      using T = unsigned;
      const T initial[] = { T(0), T(1), T(2), T(3), T(4) };
      const T rhs    [] = { T(0) };
      type<T>(initial, rhs);
   } {
      using T = int*;
      int i, j, k, l, m;
      const T initial[] = { &i, &j, &k, &l, &m };
      const T rhs    [] = { T(0) };
      type<T>(initial, rhs);
   } {
      using T = float*;
      float i, j, k, l, m;
      const T initial[] = { &i, &j, &k, &l, &m };
      const T rhs    [] = { T(0) };
      type<T>(initial, rhs);
   } {
      using T = double*;
      double i, j, k, l, m;
      const T initial[] = { &i, &j, &k, &l, &m };
      const T rhs    [] = { T(0) };
      type<T>(initial, rhs);
   } {
      using T = float;
      const T initial[] = { T(0.1), T(1.2), T(2.3), T(3.4), T(4.5) };
      const T rhs    [] = { T(0) };
      type<T>(initial, rhs);
   } {
      using T = double;
      const T initial[] = { T(0.1), T(1.2), T(2.3), T(3.4), T(4.5) };
      const T rhs    [] = { T(0) };
      type<T>(initial, rhs);
   }
}
