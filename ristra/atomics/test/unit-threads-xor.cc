
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
      value ^= rhs;
}

// main
int main()
{
   {
      using T = int;
      const T initial[] = { T(0), T(100000), T(200000), T(300000), T(400000) };
      const T rhs    [] = { T(123000), T(456000), T(789000) };
      type<T>(initial, rhs);
   } {
      using T = unsigned;
      const T initial[] = { T(0), T(100000), T(200000), T(300000), T(400000) };
      const T rhs    [] = { T(123000), T(456000), T(789000) };
      type<T>(initial, rhs);
   }
}
