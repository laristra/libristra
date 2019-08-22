
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
      value <<= rhs;
}

// main
int main()
{
   {
      using T = int;
      const T initial[] = { T(0), T(1), T(2), T(3), T(4) };
      const T rhs    [] = { T(0), T(1), T(2), T(3) };
      type<T>(initial, rhs);
   } {
      using T = unsigned;
      const T initial[] = { T(0), T(1), T(2), T(3), T(4) };
      const T rhs    [] = { T(0), T(1), T(2), T(3) };
      type<T>(initial, rhs);
   }
}
