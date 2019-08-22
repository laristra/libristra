
const int MAXNTHREAD = 4;
const int MAXNITER = 10;

#define ATOMICS_NO_CPP
#include "unit-threads.h"

// -----------------------------------------------------------------------------
// main
// -----------------------------------------------------------------------------

// op
template<class T_OR_ATOMIC, class RHS>
void op(T_OR_ATOMIC &value, const std::size_t niter, const RHS rhs)
{
   for (std::size_t iiter = 0;  iiter < niter;  ++iiter)
      value /= rhs;
}

// main
int main()
{
   {
      using T = int;
      const T initial[] = { T(0), T(100000), T(200000), T(300000), T(400000) };
      const T rhs    [] = { T(1), T(2), T(3) };
      type<T>(initial, rhs);
   } {
      using T = unsigned;
      const T initial[] = { T(0), T(100000), T(200000), T(300000), T(400000) };
      const T rhs    [] = { T(1), T(2), T(3) };
      type<T>(initial, rhs);
   } {
      using T = float;
      const T initial[] = { T(0.1), T(1.2), T(2.3), T(3.4), T(4.5) };
      const T rhs    [] = { T(1.2), T(2.3), T(3.4), T(4.5) };
      type<T>(initial, rhs);
   } {
      using T = double;
      const T initial[] = { T(0.1), T(1.2), T(2.3), T(3.4), T(4.5) };
      const T rhs    [] = { T(1.2), T(2.3), T(3.4), T(4.5) };
      type<T>(initial, rhs);
   } {
      using T = std::complex<float>;
      const T initial[] = { T(0.1), T(1.2), T(2.3), T(3.4), T(4.5) };
      const T rhs    [] = { T(1.2), T(2.3), T(3.4), T(4.5) };
      type<T>(initial, rhs);
   } {
      using T = std::complex<double>;
      const T initial[] = { T(0.1), T(1.2), T(2.3), T(3.4), T(4.5) };
      const T rhs    [] = { T(1.2), T(2.3), T(3.4), T(4.5) };
      type<T>(initial, rhs);
   }
}
