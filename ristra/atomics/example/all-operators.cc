
/*
We illustrate each of our operators, for each of our atomicizing schemes cpp,
kokkos (optional), strong, strong::pun, weak, weak::pun, lock, and serial, and
for each of the following underlying data types: int, unsigned long, double,
int*, std::complex<float>, and our user-defined class foo.

Note: we're writing things in operator form (e.g. +=), not function form (e.g.
member or namespace-scope add()). Also, for now, we're just illustrating all
these operators.
*/

#define ATOMICS_KOKKOS
#define ATOMICS_DEBUG

#include "atomics.h"
#include <complex>
#include <iostream>

// User-defined foo and bar classes
#include "foobar.h"

// main
int main()
{
   using namespace ristra::atomics;

   using ulong = unsigned long;
   using cmplx = std::complex<float>;

   int i(0); // for the int* cases
   const cmplx c(1.2,3.4);
   const bar b(2); // for the foo cases



   // --------------------------------------------------------------------------
   // non-volatile
   // --------------------------------------------------------------------------

   // ------------------------
   // int
   // ------------------------

   // cpp
   { atomic<int,cpp> a(0);  a +=  2; }
   { atomic<int,cpp> a(0);  a -=  2; }
// { atomic<int,cpp> a(0);  a *=  2; }  // std::atomic<int> has no *=
// { atomic<int,cpp> a(0);  a /=  2; }  // ...
// { atomic<int,cpp> a(0);  a %=  2; }  // ...
// { atomic<int,cpp> a(0);  a <<= 2; }  // ...
// { atomic<int,cpp> a(0);  a >>= 2; }  // ...
   { atomic<int,cpp> a(0);  a &=  2; }
   { atomic<int,cpp> a(0);  a |=  2; }
   { atomic<int,cpp> a(0);  a ^=  2; }
   { atomic<int,cpp> a(0);  ++a; }
   { atomic<int,cpp> a(0);  a++; }
   { atomic<int,cpp> a(0);  --a; }
   { atomic<int,cpp> a(0);  a--; }

   // kokkos
#if defined(ATOMICS_KOKKOS)
   { atomic<int,kokkos> a(0);  a +=  2; }
   { atomic<int,kokkos> a(0);  a -=  2; }
   { atomic<int,kokkos> a(0);  a *=  2; }
   { atomic<int,kokkos> a(0);  a /=  2; }
   { atomic<int,kokkos> a(0);  a %=  2; }
   { atomic<int,kokkos> a(0);  a <<= 2; }
   { atomic<int,kokkos> a(0);  a >>= 2; }
   { atomic<int,kokkos> a(0);  a &=  2; }
   { atomic<int,kokkos> a(0);  a |=  2; }
   { atomic<int,kokkos> a(0);  a ^=  2; }
   { atomic<int,kokkos> a(0);  ++a; }
   { atomic<int,kokkos> a(0);  a++; }
   { atomic<int,kokkos> a(0);  --a; }
   { atomic<int,kokkos> a(0);  a--; }
#endif

   // strong
   { atomic<int,strong> a(0);  a +=  2; }
   { atomic<int,strong> a(0);  a -=  2; }
   { atomic<int,strong> a(0);  a *=  2; }
   { atomic<int,strong> a(0);  a /=  2; }
   { atomic<int,strong> a(0);  a %=  2; }
   { atomic<int,strong> a(0);  a <<= 2; }
   { atomic<int,strong> a(0);  a >>= 2; }
   { atomic<int,strong> a(0);  a &=  2; }
   { atomic<int,strong> a(0);  a |=  2; }
   { atomic<int,strong> a(0);  a ^=  2; }
   { atomic<int,strong> a(0);  ++a; }
   { atomic<int,strong> a(0);  a++; }
   { atomic<int,strong> a(0);  --a; }
   { atomic<int,strong> a(0);  a--; }

   // strong::pun
   { atomic<int,strong::pun> a(0);  a +=  2; }
   { atomic<int,strong::pun> a(0);  a -=  2; }
   { atomic<int,strong::pun> a(0);  a *=  2; }
   { atomic<int,strong::pun> a(0);  a /=  2; }
   { atomic<int,strong::pun> a(0);  a %=  2; }
   { atomic<int,strong::pun> a(0);  a <<= 2; }
   { atomic<int,strong::pun> a(0);  a >>= 2; }
   { atomic<int,strong::pun> a(0);  a &=  2; }
   { atomic<int,strong::pun> a(0);  a |=  2; }
   { atomic<int,strong::pun> a(0);  a ^=  2; }
   { atomic<int,strong::pun> a(0);  ++a; }
   { atomic<int,strong::pun> a(0);  a++; }
   { atomic<int,strong::pun> a(0);  --a; }
   { atomic<int,strong::pun> a(0);  a--; }

   // weak
   { atomic<int,weak> a(0);  a +=  2; }
   { atomic<int,weak> a(0);  a -=  2; }
   { atomic<int,weak> a(0);  a *=  2; }
   { atomic<int,weak> a(0);  a /=  2; }
   { atomic<int,weak> a(0);  a %=  2; }
   { atomic<int,weak> a(0);  a <<= 2; }
   { atomic<int,weak> a(0);  a >>= 2; }
   { atomic<int,weak> a(0);  a &=  2; }
   { atomic<int,weak> a(0);  a |=  2; }
   { atomic<int,weak> a(0);  a ^=  2; }
   { atomic<int,weak> a(0);  ++a; }
   { atomic<int,weak> a(0);  a++; }
   { atomic<int,weak> a(0);  --a; }
   { atomic<int,weak> a(0);  a--; }

   // weak::pun
   { atomic<int,weak::pun> a(0);  a +=  2; }
   { atomic<int,weak::pun> a(0);  a -=  2; }
   { atomic<int,weak::pun> a(0);  a *=  2; }
   { atomic<int,weak::pun> a(0);  a /=  2; }
   { atomic<int,weak::pun> a(0);  a %=  2; }
   { atomic<int,weak::pun> a(0);  a <<= 2; }
   { atomic<int,weak::pun> a(0);  a >>= 2; }
   { atomic<int,weak::pun> a(0);  a &=  2; }
   { atomic<int,weak::pun> a(0);  a |=  2; }
   { atomic<int,weak::pun> a(0);  a ^=  2; }
   { atomic<int,weak::pun> a(0);  ++a; }
   { atomic<int,weak::pun> a(0);  a++; }
   { atomic<int,weak::pun> a(0);  --a; }
   { atomic<int,weak::pun> a(0);  a--; }

   // lock
   { atomic<int,lock> a(0);  a +=  2; }
   { atomic<int,lock> a(0);  a -=  2; }
   { atomic<int,lock> a(0);  a *=  2; }
   { atomic<int,lock> a(0);  a /=  2; }
   { atomic<int,lock> a(0);  a %=  2; }
   { atomic<int,lock> a(0);  a <<= 2; }
   { atomic<int,lock> a(0);  a >>= 2; }
   { atomic<int,lock> a(0);  a &=  2; }
   { atomic<int,lock> a(0);  a |=  2; }
   { atomic<int,lock> a(0);  a ^=  2; }
   { atomic<int,lock> a(0);  ++a; }
   { atomic<int,lock> a(0);  a++; }
   { atomic<int,lock> a(0);  --a; }
   { atomic<int,lock> a(0);  a--; }

   // serial
   { atomic<int,serial> a(0);  a +=  2; }
   { atomic<int,serial> a(0);  a -=  2; }
   { atomic<int,serial> a(0);  a *=  2; }
   { atomic<int,serial> a(0);  a /=  2; }
   { atomic<int,serial> a(0);  a %=  2; }
   { atomic<int,serial> a(0);  a <<= 2; }
   { atomic<int,serial> a(0);  a >>= 2; }
   { atomic<int,serial> a(0);  a &=  2; }
   { atomic<int,serial> a(0);  a |=  2; }
   { atomic<int,serial> a(0);  a ^=  2; }
   { atomic<int,serial> a(0);  ++a; }
   { atomic<int,serial> a(0);  a++; }
   { atomic<int,serial> a(0);  --a; }
   { atomic<int,serial> a(0);  a--; }



   // ------------------------
   // unsigned long
   // ------------------------

   // cpp
   { atomic<ulong,cpp> a(0);  a +=  2; }
   { atomic<ulong,cpp> a(0);  a -=  2; }
// { atomic<ulong,cpp> a(0);  a *=  2; }  // std::atomic<ulong> has no *=
// { atomic<ulong,cpp> a(0);  a /=  2; }  // ...
// { atomic<ulong,cpp> a(0);  a %=  2; }  // ...
// { atomic<ulong,cpp> a(0);  a <<= 2; }  // ...
// { atomic<ulong,cpp> a(0);  a >>= 2; }  // ...
   { atomic<ulong,cpp> a(0);  a &=  2; }
   { atomic<ulong,cpp> a(0);  a |=  2; }
   { atomic<ulong,cpp> a(0);  a ^=  2; }
   { atomic<ulong,cpp> a(0);  ++a; }
   { atomic<ulong,cpp> a(0);  a++; }
   { atomic<ulong,cpp> a(0);  --a; }
   { atomic<ulong,cpp> a(0);  a--; }

   // kokkos
#if defined(ATOMICS_KOKKOS)
   { atomic<ulong,kokkos> a(0);  a +=  2; }
   { atomic<ulong,kokkos> a(0);  a -=  2; }
   { atomic<ulong,kokkos> a(0);  a *=  2; }
   { atomic<ulong,kokkos> a(0);  a /=  2; }
   { atomic<ulong,kokkos> a(0);  a %=  2; }
   { atomic<ulong,kokkos> a(0);  a <<= 2; }
   { atomic<ulong,kokkos> a(0);  a >>= 2; }
   { atomic<ulong,kokkos> a(0);  a &=  2; }
   { atomic<ulong,kokkos> a(0);  a |=  2; }
   { atomic<ulong,kokkos> a(0);  a ^=  2; }
   { atomic<ulong,kokkos> a(0);  ++a; }
   { atomic<ulong,kokkos> a(0);  a++; }
   { atomic<ulong,kokkos> a(0);  --a; }
   { atomic<ulong,kokkos> a(0);  a--; }
#endif

   // strong
   { atomic<ulong,strong> a(0);  a +=  2; }
   { atomic<ulong,strong> a(0);  a -=  2; }
   { atomic<ulong,strong> a(0);  a *=  2; }
   { atomic<ulong,strong> a(0);  a /=  2; }
   { atomic<ulong,strong> a(0);  a %=  2; }
   { atomic<ulong,strong> a(0);  a <<= 2; }
   { atomic<ulong,strong> a(0);  a >>= 2; }
   { atomic<ulong,strong> a(0);  a &=  2; }
   { atomic<ulong,strong> a(0);  a |=  2; }
   { atomic<ulong,strong> a(0);  a ^=  2; }
   { atomic<ulong,strong> a(0);  ++a; }
   { atomic<ulong,strong> a(0);  a++; }
   { atomic<ulong,strong> a(0);  --a; }
   { atomic<ulong,strong> a(0);  a--; }

   // strong::pun
   { atomic<ulong,strong::pun> a(0);  a +=  2; }
   { atomic<ulong,strong::pun> a(0);  a -=  2; }
   { atomic<ulong,strong::pun> a(0);  a *=  2; }
   { atomic<ulong,strong::pun> a(0);  a /=  2; }
   { atomic<ulong,strong::pun> a(0);  a %=  2; }
   { atomic<ulong,strong::pun> a(0);  a <<= 2; }
   { atomic<ulong,strong::pun> a(0);  a >>= 2; }
   { atomic<ulong,strong::pun> a(0);  a &=  2; }
   { atomic<ulong,strong::pun> a(0);  a |=  2; }
   { atomic<ulong,strong::pun> a(0);  a ^=  2; }
   { atomic<ulong,strong::pun> a(0);  ++a; }
   { atomic<ulong,strong::pun> a(0);  a++; }
   { atomic<ulong,strong::pun> a(0);  --a; }
   { atomic<ulong,strong::pun> a(0);  a--; }

   // weak
   { atomic<ulong,weak> a(0);  a +=  2; }
   { atomic<ulong,weak> a(0);  a -=  2; }
   { atomic<ulong,weak> a(0);  a *=  2; }
   { atomic<ulong,weak> a(0);  a /=  2; }
   { atomic<ulong,weak> a(0);  a %=  2; }
   { atomic<ulong,weak> a(0);  a <<= 2; }
   { atomic<ulong,weak> a(0);  a >>= 2; }
   { atomic<ulong,weak> a(0);  a &=  2; }
   { atomic<ulong,weak> a(0);  a |=  2; }
   { atomic<ulong,weak> a(0);  a ^=  2; }
   { atomic<ulong,weak> a(0);  ++a; }
   { atomic<ulong,weak> a(0);  a++; }
   { atomic<ulong,weak> a(0);  --a; }
   { atomic<ulong,weak> a(0);  a--; }

   // weak::pun
   { atomic<ulong,weak::pun> a(0);  a +=  2; }
   { atomic<ulong,weak::pun> a(0);  a -=  2; }
   { atomic<ulong,weak::pun> a(0);  a *=  2; }
   { atomic<ulong,weak::pun> a(0);  a /=  2; }
   { atomic<ulong,weak::pun> a(0);  a %=  2; }
   { atomic<ulong,weak::pun> a(0);  a <<= 2; }
   { atomic<ulong,weak::pun> a(0);  a >>= 2; }
   { atomic<ulong,weak::pun> a(0);  a &=  2; }
   { atomic<ulong,weak::pun> a(0);  a |=  2; }
   { atomic<ulong,weak::pun> a(0);  a ^=  2; }
   { atomic<ulong,weak::pun> a(0);  ++a; }
   { atomic<ulong,weak::pun> a(0);  a++; }
   { atomic<ulong,weak::pun> a(0);  --a; }
   { atomic<ulong,weak::pun> a(0);  a--; }

   // lock
   { atomic<ulong,lock> a(0);  a +=  2; }
   { atomic<ulong,lock> a(0);  a -=  2; }
   { atomic<ulong,lock> a(0);  a *=  2; }
   { atomic<ulong,lock> a(0);  a /=  2; }
   { atomic<ulong,lock> a(0);  a %=  2; }
   { atomic<ulong,lock> a(0);  a <<= 2; }
   { atomic<ulong,lock> a(0);  a >>= 2; }
   { atomic<ulong,lock> a(0);  a &=  2; }
   { atomic<ulong,lock> a(0);  a |=  2; }
   { atomic<ulong,lock> a(0);  a ^=  2; }
   { atomic<ulong,lock> a(0);  ++a; }
   { atomic<ulong,lock> a(0);  a++; }
   { atomic<ulong,lock> a(0);  --a; }
   { atomic<ulong,lock> a(0);  a--; }

   // serial
   { atomic<ulong,serial> a(0);  a +=  2; }
   { atomic<ulong,serial> a(0);  a -=  2; }
   { atomic<ulong,serial> a(0);  a *=  2; }
   { atomic<ulong,serial> a(0);  a /=  2; }
   { atomic<ulong,serial> a(0);  a %=  2; }
   { atomic<ulong,serial> a(0);  a <<= 2; }
   { atomic<ulong,serial> a(0);  a >>= 2; }
   { atomic<ulong,serial> a(0);  a &=  2; }
   { atomic<ulong,serial> a(0);  a |=  2; }
   { atomic<ulong,serial> a(0);  a ^=  2; }
   { atomic<ulong,serial> a(0);  ++a; }
   { atomic<ulong,serial> a(0);  a++; }
   { atomic<ulong,serial> a(0);  --a; }
   { atomic<ulong,serial> a(0);  a--; }



   // ------------------------
   // double
   // ------------------------

   // cpp <== meaning C++ std::atomic<T> must have these
// { atomic<double,cpp> a(0);  a +=  2; }  // std::atomic<double> has no +=
// { atomic<double,cpp> a(0);  a -=  2; }  // ...
// { atomic<double,cpp> a(0);  a *=  2; }  // ...
// { atomic<double,cpp> a(0);  a /=  2; }  // ...
// { atomic<double,cpp> a(0);  a %=  2; }  // ...also no %= for plain double
// { atomic<double,cpp> a(0);  a <<= 2; }  // ...
// { atomic<double,cpp> a(0);  a >>= 2; }  // ...
// { atomic<double,cpp> a(0);  a &=  2; }  // ...
// { atomic<double,cpp> a(0);  a |=  2; }  // ...
// { atomic<double,cpp> a(0);  a ^=  2; }  // ...
// { atomic<double,cpp> a(0);  ++a; }  // ...Remember, the issue here again
// { atomic<double,cpp> a(0);  a++; }  // ...is that std::atomic for double
// { atomic<double,cpp> a(0);  --a; }  // ...doesn't support ++ and --, even
// { atomic<double,cpp> a(0);  a--; }  // ...though plain double has those.

   // kokkos
#if defined(ATOMICS_KOKKOS)
   { atomic<double,kokkos> a(0);  a +=  2; }
   { atomic<double,kokkos> a(0);  a -=  2; }
   { atomic<double,kokkos> a(0);  a *=  2; }
   { atomic<double,kokkos> a(0);  a /=  2; }
// { atomic<double,kokkos> a(0);  a %=  2; }  // C++ has no %= for double
// { atomic<double,kokkos> a(0);  a <<= 2; }  // ...
// { atomic<double,kokkos> a(0);  a >>= 2; }  // ...
// { atomic<double,kokkos> a(0);  a &=  2; }  // ...
// { atomic<double,kokkos> a(0);  a |=  2; }  // ...
// { atomic<double,kokkos> a(0);  a ^=  2; }  // ...
   { atomic<double,kokkos> a(0);  ++a; }
   { atomic<double,kokkos> a(0);  a++; }
   { atomic<double,kokkos> a(0);  --a; }
   { atomic<double,kokkos> a(0);  a--; }
#endif

   // strong
   { atomic<double,strong> a(0);  a +=  2; }
   { atomic<double,strong> a(0);  a -=  2; }
   { atomic<double,strong> a(0);  a *=  2; }
   { atomic<double,strong> a(0);  a /=  2; }
// { atomic<double,strong> a(0);  a %=  2; }  // C++ has no %= for double
// { atomic<double,strong> a(0);  a <<= 2; }  // ...
// { atomic<double,strong> a(0);  a >>= 2; }  // ...
// { atomic<double,strong> a(0);  a &=  2; }  // ...
// { atomic<double,strong> a(0);  a |=  2; }  // ...
// { atomic<double,strong> a(0);  a ^=  2; }  // ...
   { atomic<double,strong> a(0);  ++a; }
   { atomic<double,strong> a(0);  a++; }
   { atomic<double,strong> a(0);  --a; }
   { atomic<double,strong> a(0);  a--; }

   // strong::pun
   { atomic<double,strong::pun> a(0);  a +=  2; }
   { atomic<double,strong::pun> a(0);  a -=  2; }
   { atomic<double,strong::pun> a(0);  a *=  2; }
   { atomic<double,strong::pun> a(0);  a /=  2; }
// { atomic<double,strong::pun> a(0);  a %=  2; }  // C++ has no %= for double
// { atomic<double,strong::pun> a(0);  a <<= 2; }  // ...
// { atomic<double,strong::pun> a(0);  a >>= 2; }  // ...
// { atomic<double,strong::pun> a(0);  a &=  2; }  // ...
// { atomic<double,strong::pun> a(0);  a |=  2; }  // ...
// { atomic<double,strong::pun> a(0);  a ^=  2; }  // ...
   { atomic<double,strong::pun> a(0);  ++a; }
   { atomic<double,strong::pun> a(0);  a++; }
   { atomic<double,strong::pun> a(0);  --a; }
   { atomic<double,strong::pun> a(0);  a--; }

   // weak
   { atomic<double,weak> a(0);  a +=  2; }
   { atomic<double,weak> a(0);  a -=  2; }
   { atomic<double,weak> a(0);  a *=  2; }
   { atomic<double,weak> a(0);  a /=  2; }
// { atomic<double,weak> a(0);  a %=  2; }  // C++ has no %= for double
// { atomic<double,weak> a(0);  a <<= 2; }  // ...
// { atomic<double,weak> a(0);  a >>= 2; }  // ...
// { atomic<double,weak> a(0);  a &=  2; }  // ...
// { atomic<double,weak> a(0);  a |=  2; }  // ...
// { atomic<double,weak> a(0);  a ^=  2; }  // ...
   { atomic<double,weak> a(0);  ++a; }
   { atomic<double,weak> a(0);  a++; }
   { atomic<double,weak> a(0);  --a; }
   { atomic<double,weak> a(0);  a--; }

   // weak::pun
   { atomic<double,weak::pun> a(0);  a +=  2; }
   { atomic<double,weak::pun> a(0);  a -=  2; }
   { atomic<double,weak::pun> a(0);  a *=  2; }
   { atomic<double,weak::pun> a(0);  a /=  2; }
// { atomic<double,weak::pun> a(0);  a %=  2; }  // C++ has no %= for double
// { atomic<double,weak::pun> a(0);  a <<= 2; }  // ...
// { atomic<double,weak::pun> a(0);  a >>= 2; }  // ...
// { atomic<double,weak::pun> a(0);  a &=  2; }  // ...
// { atomic<double,weak::pun> a(0);  a |=  2; }  // ...
// { atomic<double,weak::pun> a(0);  a ^=  2; }  // ...
   { atomic<double,weak::pun> a(0);  ++a; }
   { atomic<double,weak::pun> a(0);  a++; }
   { atomic<double,weak::pun> a(0);  --a; }
   { atomic<double,weak::pun> a(0);  a--; }

   // lock
   { atomic<double,lock> a(0);  a +=  2; }
   { atomic<double,lock> a(0);  a -=  2; }
   { atomic<double,lock> a(0);  a *=  2; }
   { atomic<double,lock> a(0);  a /=  2; }
// { atomic<double,lock> a(0);  a %=  2; }  // C++ has no %= for double
// { atomic<double,lock> a(0);  a <<= 2; }  // ...
// { atomic<double,lock> a(0);  a >>= 2; }  // ...
// { atomic<double,lock> a(0);  a &=  2; }  // ...
// { atomic<double,lock> a(0);  a |=  2; }  // ...
// { atomic<double,lock> a(0);  a ^=  2; }  // ...
   { atomic<double,lock> a(0);  ++a; }
   { atomic<double,lock> a(0);  a++; }
   { atomic<double,lock> a(0);  --a; }
   { atomic<double,lock> a(0);  a--; }

   // serial
   { atomic<double,serial> a(0);  a +=  2; }
   { atomic<double,serial> a(0);  a -=  2; }
   { atomic<double,serial> a(0);  a *=  2; }
   { atomic<double,serial> a(0);  a /=  2; }
// { atomic<double,serial> a(0);  a %=  2; }  // C++ has no %= for double
// { atomic<double,serial> a(0);  a <<= 2; }  // ...
// { atomic<double,serial> a(0);  a >>= 2; }  // ...
// { atomic<double,serial> a(0);  a &=  2; }  // ...
// { atomic<double,serial> a(0);  a |=  2; }  // ...
// { atomic<double,serial> a(0);  a ^=  2; }  // ...
   { atomic<double,serial> a(0);  ++a; }
   { atomic<double,serial> a(0);  a++; }
   { atomic<double,serial> a(0);  --a; }
   { atomic<double,serial> a(0);  a--; }



   // ------------------------
   // int*
   // So: pointer arithmetic
   // ------------------------

   (void)i;
#if !defined(ATOMICS_TEST)
   // cpp
   { atomic<int*,cpp> a(&i);  a +=  2; }
   { atomic<int*,cpp> a(&i);  a -=  2; }
// { atomic<int*,cpp> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { atomic<int*,cpp> a(&i);  a /=  2; }  // ...
// { atomic<int*,cpp> a(&i);  a %=  2; }  // ...
// { atomic<int*,cpp> a(&i);  a <<= 2; }  // ...
// { atomic<int*,cpp> a(&i);  a >>= 2; }  // ...
// { atomic<int*,cpp> a(&i);  a &=  2; }  // ...
// { atomic<int*,cpp> a(&i);  a |=  2; }  // ...
// { atomic<int*,cpp> a(&i);  a ^=  2; }  // ...
   { atomic<int*,cpp> a(&i);  ++a; }
   { atomic<int*,cpp> a(&i);  a++; }
   { atomic<int*,cpp> a(&i);  --a; }
   { atomic<int*,cpp> a(&i);  a--; }

   // kokkos
#if defined(ATOMICS_KOKKOS)
// { atomic<int*,kokkos> a(&i);  a +=  2; }  // Kokkos has nothing for pointers
// { atomic<int*,kokkos> a(&i);  a -=  2; }  // ...
// { atomic<int*,kokkos> a(&i);  a *=  2; }  // ...
// { atomic<int*,kokkos> a(&i);  a /=  2; }  // ...
// { atomic<int*,kokkos> a(&i);  a %=  2; }  // ...
// { atomic<int*,kokkos> a(&i);  a <<= 2; }  // ...
// { atomic<int*,kokkos> a(&i);  a >>= 2; }  // ...
// { atomic<int*,kokkos> a(&i);  a &=  2; }  // ...
// { atomic<int*,kokkos> a(&i);  a |=  2; }  // ...
// { atomic<int*,kokkos> a(&i);  a ^=  2; }  // ...
// { atomic<int*,kokkos> a(&i);  ++a; }  // ...
// { atomic<int*,kokkos> a(&i);  a++; }  // ...
// { atomic<int*,kokkos> a(&i);  --a; }  // ...
// { atomic<int*,kokkos> a(&i);  a--; }  // ...
#endif

   // strong
   { atomic<int*,strong> a(&i);  a +=  2; }
   { atomic<int*,strong> a(&i);  a -=  2; }
// { atomic<int*,strong> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { atomic<int*,strong> a(&i);  a /=  2; }  // ...
// { atomic<int*,strong> a(&i);  a %=  2; }  // ...
// { atomic<int*,strong> a(&i);  a <<= 2; }  // ...
// { atomic<int*,strong> a(&i);  a >>= 2; }  // ...
// { atomic<int*,strong> a(&i);  a &=  2; }  // ...
// { atomic<int*,strong> a(&i);  a |=  2; }  // ...
// { atomic<int*,strong> a(&i);  a ^=  2; }  // ...
   { atomic<int*,strong> a(&i);  ++a; }
   { atomic<int*,strong> a(&i);  a++; }
   { atomic<int*,strong> a(&i);  --a; }
   { atomic<int*,strong> a(&i);  a--; }

   // strong::pun
   { atomic<int*,strong::pun> a(&i);  a +=  2; }
   { atomic<int*,strong::pun> a(&i);  a -=  2; }
// { atomic<int*,strong::pun> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { atomic<int*,strong::pun> a(&i);  a /=  2; }  // ...
// { atomic<int*,strong::pun> a(&i);  a %=  2; }  // ...
// { atomic<int*,strong::pun> a(&i);  a <<= 2; }  // ...
// { atomic<int*,strong::pun> a(&i);  a >>= 2; }  // ...
// { atomic<int*,strong::pun> a(&i);  a &=  2; }  // ...
// { atomic<int*,strong::pun> a(&i);  a |=  2; }  // ...
// { atomic<int*,strong::pun> a(&i);  a ^=  2; }  // ...
   { atomic<int*,strong::pun> a(&i);  ++a; }
   { atomic<int*,strong::pun> a(&i);  a++; }
   { atomic<int*,strong::pun> a(&i);  --a; }
   { atomic<int*,strong::pun> a(&i);  a--; }

   // weak
   { atomic<int*,weak> a(&i);  a +=  2; }
   { atomic<int*,weak> a(&i);  a -=  2; }
// { atomic<int*,weak> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { atomic<int*,weak> a(&i);  a /=  2; }  // ...
// { atomic<int*,weak> a(&i);  a %=  2; }  // ...
// { atomic<int*,weak> a(&i);  a <<= 2; }  // ...
// { atomic<int*,weak> a(&i);  a >>= 2; }  // ...
// { atomic<int*,weak> a(&i);  a &=  2; }  // ...
// { atomic<int*,weak> a(&i);  a |=  2; }  // ...
// { atomic<int*,weak> a(&i);  a ^=  2; }  // ...
   { atomic<int*,weak> a(&i);  ++a; }
   { atomic<int*,weak> a(&i);  a++; }
   { atomic<int*,weak> a(&i);  --a; }
   { atomic<int*,weak> a(&i);  a--; }

   // weak::pun
   { atomic<int*,weak::pun> a(&i);  a +=  2; }
   { atomic<int*,weak::pun> a(&i);  a -=  2; }
// { atomic<int*,weak::pun> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { atomic<int*,weak::pun> a(&i);  a /=  2; }  // ...
// { atomic<int*,weak::pun> a(&i);  a %=  2; }  // ...
// { atomic<int*,weak::pun> a(&i);  a <<= 2; }  // ...
// { atomic<int*,weak::pun> a(&i);  a >>= 2; }  // ...
// { atomic<int*,weak::pun> a(&i);  a &=  2; }  // ...
// { atomic<int*,weak::pun> a(&i);  a |=  2; }  // ...
// { atomic<int*,weak::pun> a(&i);  a ^=  2; }  // ...
   { atomic<int*,weak::pun> a(&i);  ++a; }
   { atomic<int*,weak::pun> a(&i);  a++; }
   { atomic<int*,weak::pun> a(&i);  --a; }
   { atomic<int*,weak::pun> a(&i);  a--; }

   // lock
   { atomic<int*,lock> a(&i);  a +=  2; }
   { atomic<int*,lock> a(&i);  a -=  2; }
// { atomic<int*,lock> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { atomic<int*,lock> a(&i);  a /=  2; }  // ...
// { atomic<int*,lock> a(&i);  a %=  2; }  // ...
// { atomic<int*,lock> a(&i);  a <<= 2; }  // ...
// { atomic<int*,lock> a(&i);  a >>= 2; }  // ...
// { atomic<int*,lock> a(&i);  a &=  2; }  // ...
// { atomic<int*,lock> a(&i);  a |=  2; }  // ...
// { atomic<int*,lock> a(&i);  a ^=  2; }  // ...
   { atomic<int*,lock> a(&i);  ++a; }
   { atomic<int*,lock> a(&i);  a++; }
   { atomic<int*,lock> a(&i);  --a; }
   { atomic<int*,lock> a(&i);  a--; }

   // serial
   { atomic<int*,serial> a(&i);  a +=  2; }
   { atomic<int*,serial> a(&i);  a -=  2; }
// { atomic<int*,serial> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { atomic<int*,serial> a(&i);  a /=  2; }  // ...
// { atomic<int*,serial> a(&i);  a %=  2; }  // ...
// { atomic<int*,serial> a(&i);  a <<= 2; }  // ...
// { atomic<int*,serial> a(&i);  a >>= 2; }  // ...
// { atomic<int*,serial> a(&i);  a &=  2; }  // ...
// { atomic<int*,serial> a(&i);  a |=  2; }  // ...
// { atomic<int*,serial> a(&i);  a ^=  2; }  // ...
   { atomic<int*,serial> a(&i);  ++a; }
   { atomic<int*,serial> a(&i);  a++; }
   { atomic<int*,serial> a(&i);  --a; }
   { atomic<int*,serial> a(&i);  a--; }
#endif



   // ------------------------
   // std::complex
   // ------------------------

   // cpp
// { atomic<cmplx,cpp> a(0);  a +=  c; } // C++ atomics don't support complex
// { atomic<cmplx,cpp> a(0);  a -=  c; } // ...
// { atomic<cmplx,cpp> a(0);  a *=  c; } // ...
// { atomic<cmplx,cpp> a(0);  a /=  c; } // ...
// { atomic<cmplx,cpp> a(0);  a %=  c; } // ...
// { atomic<cmplx,cpp> a(0);  a <<= c; } // ...
// { atomic<cmplx,cpp> a(0);  a >>= c; } // ...
// { atomic<cmplx,cpp> a(0);  a &=  c; } // ...
// { atomic<cmplx,cpp> a(0);  a |=  c; } // ...
// { atomic<cmplx,cpp> a(0);  a ^=  c; } // ...
// { atomic<cmplx,cpp> a(0);  ++a; } // ...
// { atomic<cmplx,cpp> a(0);  a++; } // ...
// { atomic<cmplx,cpp> a(0);  --a; } // ...
// { atomic<cmplx,cpp> a(0);  a--; } // ...

   // kokkos
#if defined(ATOMICS_KOKKOS)
// { atomic<cmplx,kokkos> a(0);  a +=  c; } // Kokkos atomics don't either
// { atomic<cmplx,kokkos> a(0);  a -=  c; } // ...
// { atomic<cmplx,kokkos> a(0);  a *=  c; } // ...
// { atomic<cmplx,kokkos> a(0);  a /=  c; } // ...
// { atomic<cmplx,kokkos> a(0);  a %=  c; } // ...
// { atomic<cmplx,kokkos> a(0);  a <<= c; } // ...
// { atomic<cmplx,kokkos> a(0);  a >>= c; } // ...
// { atomic<cmplx,kokkos> a(0);  a &=  c; } // ...
// { atomic<cmplx,kokkos> a(0);  a |=  c; } // ...
// { atomic<cmplx,kokkos> a(0);  a ^=  c; } // ...
// { atomic<cmplx,kokkos> a(0);  ++a; } // ...
// { atomic<cmplx,kokkos> a(0);  a++; } // ...
// { atomic<cmplx,kokkos> a(0);  --a; } // ...
// { atomic<cmplx,kokkos> a(0);  a--; } // ...
#endif

   // strong
   { atomic<cmplx,strong> a(0);  a +=  c; }
   { atomic<cmplx,strong> a(0);  a -=  c; }
   { atomic<cmplx,strong> a(0);  a *=  c; }
   { atomic<cmplx,strong> a(0);  a /=  c; }
// { atomic<cmplx,strong> a(0);  a %=  c; }  // no modulo for complex
// { atomic<cmplx,strong> a(0);  a <<= c; }  // no bitwise ops for complex
// { atomic<cmplx,strong> a(0);  a >>= c; } // ...
// { atomic<cmplx,strong> a(0);  a &=  c; } // ...
// { atomic<cmplx,strong> a(0);  a |=  c; } // ...
// { atomic<cmplx,strong> a(0);  a ^=  c; } // ...
// { atomic<cmplx,strong> a(0);  ++a; }  // no ++ or -- for complex
// { atomic<cmplx,strong> a(0);  a++; } // ...
// { atomic<cmplx,strong> a(0);  --a; } // ...
// { atomic<cmplx,strong> a(0);  a--; } // ...

   // strong::pun
   { atomic<cmplx,strong::pun> a(0);  a +=  c; }
   { atomic<cmplx,strong::pun> a(0);  a -=  c; }
   { atomic<cmplx,strong::pun> a(0);  a *=  c; }
   { atomic<cmplx,strong::pun> a(0);  a /=  c; }
// { atomic<cmplx,strong::pun> a(0);  a %=  c; } // as for strong
// { atomic<cmplx,strong::pun> a(0);  a <<= c; } // ...
// { atomic<cmplx,strong::pun> a(0);  a >>= c; } // ...
// { atomic<cmplx,strong::pun> a(0);  a &=  c; } // ...
// { atomic<cmplx,strong::pun> a(0);  a |=  c; } // ...
// { atomic<cmplx,strong::pun> a(0);  a ^=  c; } // ...
// { atomic<cmplx,strong::pun> a(0);  ++a; } // ...
// { atomic<cmplx,strong::pun> a(0);  a++; } // ...
// { atomic<cmplx,strong::pun> a(0);  --a; } // ...
// { atomic<cmplx,strong::pun> a(0);  a--; } // ...

   // weak
   { atomic<cmplx,weak> a(0);  a +=  c; }
   { atomic<cmplx,weak> a(0);  a -=  c; }
   { atomic<cmplx,weak> a(0);  a *=  c; }
   { atomic<cmplx,weak> a(0);  a /=  c; }
// { atomic<cmplx,weak> a(0);  a %=  c; } // as for strong
// { atomic<cmplx,weak> a(0);  a <<= c; } // ...
// { atomic<cmplx,weak> a(0);  a >>= c; } // ...
// { atomic<cmplx,weak> a(0);  a &=  c; } // ...
// { atomic<cmplx,weak> a(0);  a |=  c; } // ...
// { atomic<cmplx,weak> a(0);  a ^=  c; } // ...
// { atomic<cmplx,weak> a(0);  ++a; } // ...
// { atomic<cmplx,weak> a(0);  a++; } // ...
// { atomic<cmplx,weak> a(0);  --a; } // ...
// { atomic<cmplx,weak> a(0);  a--; } // ...

   // weak::pun
   { atomic<cmplx,weak::pun> a(0);  a +=  c; }
   { atomic<cmplx,weak::pun> a(0);  a -=  c; }
   { atomic<cmplx,weak::pun> a(0);  a *=  c; }
   { atomic<cmplx,weak::pun> a(0);  a /=  c; }
// { atomic<cmplx,weak::pun> a(0);  a %=  c; } // as for strong
// { atomic<cmplx,weak::pun> a(0);  a <<= c; } // ...
// { atomic<cmplx,weak::pun> a(0);  a >>= c; } // ...
// { atomic<cmplx,weak::pun> a(0);  a &=  c; } // ...
// { atomic<cmplx,weak::pun> a(0);  a |=  c; } // ...
// { atomic<cmplx,weak::pun> a(0);  a ^=  c; } // ...
// { atomic<cmplx,weak::pun> a(0);  ++a; } // ...
// { atomic<cmplx,weak::pun> a(0);  a++; } // ...
// { atomic<cmplx,weak::pun> a(0);  --a; } // ...
// { atomic<cmplx,weak::pun> a(0);  a--; } // ...

   // lock
   { atomic<cmplx,lock> a(0);  a +=  c; }
   { atomic<cmplx,lock> a(0);  a -=  c; }
   { atomic<cmplx,lock> a(0);  a *=  c; }
   { atomic<cmplx,lock> a(0);  a /=  c; }
// { atomic<cmplx,lock> a(0);  a %=  c; } // as for strong
// { atomic<cmplx,lock> a(0);  a <<= c; } // ...
// { atomic<cmplx,lock> a(0);  a >>= c; } // ...
// { atomic<cmplx,lock> a(0);  a &=  c; } // ...
// { atomic<cmplx,lock> a(0);  a |=  c; } // ...
// { atomic<cmplx,lock> a(0);  a ^=  c; } // ...
// { atomic<cmplx,lock> a(0);  ++a; } // ...
// { atomic<cmplx,lock> a(0);  a++; } // ...
// { atomic<cmplx,lock> a(0);  --a; } // ...
// { atomic<cmplx,lock> a(0);  a--; } // ...

   // serial
   { atomic<cmplx,serial> a(0);  a +=  c; }
   { atomic<cmplx,serial> a(0);  a -=  c; }
   { atomic<cmplx,serial> a(0);  a *=  c; }
   { atomic<cmplx,serial> a(0);  a /=  c; }
// { atomic<cmplx,serial> a(0);  a %=  c; } // as for strong
// { atomic<cmplx,serial> a(0);  a <<= c; } // ...
// { atomic<cmplx,serial> a(0);  a >>= c; } // ...
// { atomic<cmplx,serial> a(0);  a &=  c; } // ...
// { atomic<cmplx,serial> a(0);  a |=  c; } // ...
// { atomic<cmplx,serial> a(0);  a ^=  c; } // ...
// { atomic<cmplx,serial> a(0);  ++a; } // ...
// { atomic<cmplx,serial> a(0);  a++; } // ...
// { atomic<cmplx,serial> a(0);  --a; } // ...
// { atomic<cmplx,serial> a(0);  a--; } // ...



   // ------------------------
   // foo (our own class)
   // See definition earlier
   // ------------------------

   // cpp <== again, means "must be supported directly by std::atomic<T>"
// { atomic<foo,cpp> a(0);  a +=  b; }  // Nope, not with cpp
// { atomic<foo,cpp> a(0);  a -=  b; }
// { atomic<foo,cpp> a(0);  a *=  b; }
// { atomic<foo,cpp> a(0);  a /=  b; }
// { atomic<foo,cpp> a(0);  a %=  b; }
// { atomic<foo,cpp> a(0);  a <<= b; }
// { atomic<foo,cpp> a(0);  a >>= b; }
// { atomic<foo,cpp> a(0);  a &=  b; }
// { atomic<foo,cpp> a(0);  a |=  b; }
// { atomic<foo,cpp> a(0);  a ^=  b; }
// { atomic<foo,cpp> a(0);  ++a; }
// { atomic<foo,cpp> a(0);  a++; }
// { atomic<foo,cpp> a(0);  --a; }
// { atomic<foo,cpp> a(0);  a--; }

   // kokkos
#if defined(ATOMICS_KOKKOS)
   // Note: there's really more than one Kokkos issue here. Kokkos atomic
   // functions can take a general T, but the functions assume that the
   // right-hand side is also a T. That is, X += Y may work if Y is of the
   // same type as X, or is convertible thereto. Here, however, for this
   // test code, I defined foo += bar, etc. Not foo += foo, etc.; and bars
   // aren't convertible to foos. Moreover, it seems like Kokkos sometimes
   // tries to accomplish X += Y by assuming X = X+Y will do the trick;
   // similarly for some other operations. So, then, we'd need a foo+bar
   // function, which we don't have.
// { atomic<foo,kokkos> a(0);  a +=  b; }
// { atomic<foo,kokkos> a(0);  a -=  b; }
// { atomic<foo,kokkos> a(0);  a *=  b; }
// { atomic<foo,kokkos> a(0);  a /=  b; }
// { atomic<foo,kokkos> a(0);  a %=  b; }
// { atomic<foo,kokkos> a(0);  a <<= b; }
// { atomic<foo,kokkos> a(0);  a >>= b; }
// { atomic<foo,kokkos> a(0);  a &=  b; }
// { atomic<foo,kokkos> a(0);  a |=  b; }
// { atomic<foo,kokkos> a(0);  a ^=  b; }
// { atomic<foo,kokkos> a(0);  ++a; }
// { atomic<foo,kokkos> a(0);  a++; }
// { atomic<foo,kokkos> a(0);  --a; }
// { atomic<foo,kokkos> a(0);  a--; }
#endif

   // strong
   { atomic<foo,strong> a(0);  a +=  b; }
   { atomic<foo,strong> a(0);  a -=  b; }
   { atomic<foo,strong> a(0);  a *=  b; }
   { atomic<foo,strong> a(0);  a /=  b; }
   { atomic<foo,strong> a(0);  a %=  b; }
   { atomic<foo,strong> a(0);  a <<= b; }
   { atomic<foo,strong> a(0);  a >>= b; }
   { atomic<foo,strong> a(0);  a &=  b; }
   { atomic<foo,strong> a(0);  a |=  b; }
   { atomic<foo,strong> a(0);  a ^=  b; }
   { atomic<foo,strong> a(0);  ++a; }
   { atomic<foo,strong> a(0);  a++; }
   { atomic<foo,strong> a(0);  --a; }
   { atomic<foo,strong> a(0);  a--; }

   // strong::pun
   { atomic<foo,strong::pun> a(0);  a +=  b; }
   { atomic<foo,strong::pun> a(0);  a -=  b; }
   { atomic<foo,strong::pun> a(0);  a *=  b; }
   { atomic<foo,strong::pun> a(0);  a /=  b; }
   { atomic<foo,strong::pun> a(0);  a %=  b; }
   { atomic<foo,strong::pun> a(0);  a <<= b; }
   { atomic<foo,strong::pun> a(0);  a >>= b; }
   { atomic<foo,strong::pun> a(0);  a &=  b; }
   { atomic<foo,strong::pun> a(0);  a |=  b; }
   { atomic<foo,strong::pun> a(0);  a ^=  b; }
   { atomic<foo,strong::pun> a(0);  ++a; }
   { atomic<foo,strong::pun> a(0);  a++; }
   { atomic<foo,strong::pun> a(0);  --a; }
   { atomic<foo,strong::pun> a(0);  a--; }

   // weak
   { atomic<foo,weak> a(0);  a +=  b; }
   { atomic<foo,weak> a(0);  a -=  b; }
   { atomic<foo,weak> a(0);  a *=  b; }
   { atomic<foo,weak> a(0);  a /=  b; }
   { atomic<foo,weak> a(0);  a %=  b; }
   { atomic<foo,weak> a(0);  a <<= b; }
   { atomic<foo,weak> a(0);  a >>= b; }
   { atomic<foo,weak> a(0);  a &=  b; }
   { atomic<foo,weak> a(0);  a |=  b; }
   { atomic<foo,weak> a(0);  a ^=  b; }
   { atomic<foo,weak> a(0);  ++a; }
   { atomic<foo,weak> a(0);  a++; }
   { atomic<foo,weak> a(0);  --a; }
   { atomic<foo,weak> a(0);  a--; }

   // weak::pun
   { atomic<foo,weak::pun> a(0);  a +=  b; }
   { atomic<foo,weak::pun> a(0);  a -=  b; }
   { atomic<foo,weak::pun> a(0);  a *=  b; }
   { atomic<foo,weak::pun> a(0);  a /=  b; }
   { atomic<foo,weak::pun> a(0);  a %=  b; }
   { atomic<foo,weak::pun> a(0);  a <<= b; }
   { atomic<foo,weak::pun> a(0);  a >>= b; }
   { atomic<foo,weak::pun> a(0);  a &=  b; }
   { atomic<foo,weak::pun> a(0);  a |=  b; }
   { atomic<foo,weak::pun> a(0);  a ^=  b; }
   { atomic<foo,weak::pun> a(0);  ++a; }
   { atomic<foo,weak::pun> a(0);  a++; }
   { atomic<foo,weak::pun> a(0);  --a; }
   { atomic<foo,weak::pun> a(0);  a--; }

   // lock
   { atomic<foo,lock> a(0);  a +=  b; }
   { atomic<foo,lock> a(0);  a -=  b; }
   { atomic<foo,lock> a(0);  a *=  b; }
   { atomic<foo,lock> a(0);  a /=  b; }
   { atomic<foo,lock> a(0);  a %=  b; }
   { atomic<foo,lock> a(0);  a <<= b; }
   { atomic<foo,lock> a(0);  a >>= b; }
   { atomic<foo,lock> a(0);  a &=  b; }
   { atomic<foo,lock> a(0);  a |=  b; }
   { atomic<foo,lock> a(0);  a ^=  b; }
   { atomic<foo,lock> a(0);  ++a; }
   { atomic<foo,lock> a(0);  a++; }
   { atomic<foo,lock> a(0);  --a; }
   { atomic<foo,lock> a(0);  a--; }

   // serial
   { atomic<foo,serial> a(0);  a +=  b; }
   { atomic<foo,serial> a(0);  a -=  b; }
   { atomic<foo,serial> a(0);  a *=  b; }
   { atomic<foo,serial> a(0);  a /=  b; }
   { atomic<foo,serial> a(0);  a %=  b; }
   { atomic<foo,serial> a(0);  a <<= b; }
   { atomic<foo,serial> a(0);  a >>= b; }
   { atomic<foo,serial> a(0);  a &=  b; }
   { atomic<foo,serial> a(0);  a |=  b; }
   { atomic<foo,serial> a(0);  a ^=  b; }
   { atomic<foo,serial> a(0);  ++a; }
   { atomic<foo,serial> a(0);  a++; }
   { atomic<foo,serial> a(0);  --a; }
   { atomic<foo,serial> a(0);  a--; }



   // --------------------------------------------------------------------------
   // volatile
   // --------------------------------------------------------------------------

   // ------------------------
   // int
   // ------------------------

   // cpp
   { volatile atomic<int,cpp> a(0);  a +=  2; }
   { volatile atomic<int,cpp> a(0);  a -=  2; }
// { volatile atomic<int,cpp> a(0);  a *=  2; }  // std::atomic<int> has no *=
// { volatile atomic<int,cpp> a(0);  a /=  2; }  // ...
// { volatile atomic<int,cpp> a(0);  a %=  2; }  // ...
// { volatile atomic<int,cpp> a(0);  a <<= 2; }  // ...
// { volatile atomic<int,cpp> a(0);  a >>= 2; }  // ...
   { volatile atomic<int,cpp> a(0);  a &=  2; }
   { volatile atomic<int,cpp> a(0);  a |=  2; }
   { volatile atomic<int,cpp> a(0);  a ^=  2; }
   { volatile atomic<int,cpp> a(0);  ++a; }
   { volatile atomic<int,cpp> a(0);  a++; }
   { volatile atomic<int,cpp> a(0);  --a; }
   { volatile atomic<int,cpp> a(0);  a--; }

   // kokkos
#if defined(ATOMICS_KOKKOS)
   { volatile atomic<int,kokkos> a(0);  a +=  2; }
   { volatile atomic<int,kokkos> a(0);  a -=  2; }
   { volatile atomic<int,kokkos> a(0);  a *=  2; }
   { volatile atomic<int,kokkos> a(0);  a /=  2; }
   { volatile atomic<int,kokkos> a(0);  a %=  2; }
   { volatile atomic<int,kokkos> a(0);  a <<= 2; }
   { volatile atomic<int,kokkos> a(0);  a >>= 2; }
   { volatile atomic<int,kokkos> a(0);  a &=  2; }
   { volatile atomic<int,kokkos> a(0);  a |=  2; }
   { volatile atomic<int,kokkos> a(0);  a ^=  2; }
   { volatile atomic<int,kokkos> a(0);  ++a; }
   { volatile atomic<int,kokkos> a(0);  a++; }
   { volatile atomic<int,kokkos> a(0);  --a; }
   { volatile atomic<int,kokkos> a(0);  a--; }
#endif

   // strong
   { volatile atomic<int,strong> a(0);  a +=  2; }
   { volatile atomic<int,strong> a(0);  a -=  2; }
   { volatile atomic<int,strong> a(0);  a *=  2; }
   { volatile atomic<int,strong> a(0);  a /=  2; }
   { volatile atomic<int,strong> a(0);  a %=  2; }
   { volatile atomic<int,strong> a(0);  a <<= 2; }
   { volatile atomic<int,strong> a(0);  a >>= 2; }
   { volatile atomic<int,strong> a(0);  a &=  2; }
   { volatile atomic<int,strong> a(0);  a |=  2; }
   { volatile atomic<int,strong> a(0);  a ^=  2; }
   { volatile atomic<int,strong> a(0);  ++a; }
   { volatile atomic<int,strong> a(0);  a++; }
   { volatile atomic<int,strong> a(0);  --a; }
   { volatile atomic<int,strong> a(0);  a--; }

   // strong::pun
   { volatile atomic<int,strong::pun> a(0);  a +=  2; }
   { volatile atomic<int,strong::pun> a(0);  a -=  2; }
   { volatile atomic<int,strong::pun> a(0);  a *=  2; }
   { volatile atomic<int,strong::pun> a(0);  a /=  2; }
   { volatile atomic<int,strong::pun> a(0);  a %=  2; }
   { volatile atomic<int,strong::pun> a(0);  a <<= 2; }
   { volatile atomic<int,strong::pun> a(0);  a >>= 2; }
   { volatile atomic<int,strong::pun> a(0);  a &=  2; }
   { volatile atomic<int,strong::pun> a(0);  a |=  2; }
   { volatile atomic<int,strong::pun> a(0);  a ^=  2; }
   { volatile atomic<int,strong::pun> a(0);  ++a; }
   { volatile atomic<int,strong::pun> a(0);  a++; }
   { volatile atomic<int,strong::pun> a(0);  --a; }
   { volatile atomic<int,strong::pun> a(0);  a--; }

   // weak
   { volatile atomic<int,weak> a(0);  a +=  2; }
   { volatile atomic<int,weak> a(0);  a -=  2; }
   { volatile atomic<int,weak> a(0);  a *=  2; }
   { volatile atomic<int,weak> a(0);  a /=  2; }
   { volatile atomic<int,weak> a(0);  a %=  2; }
   { volatile atomic<int,weak> a(0);  a <<= 2; }
   { volatile atomic<int,weak> a(0);  a >>= 2; }
   { volatile atomic<int,weak> a(0);  a &=  2; }
   { volatile atomic<int,weak> a(0);  a |=  2; }
   { volatile atomic<int,weak> a(0);  a ^=  2; }
   { volatile atomic<int,weak> a(0);  ++a; }
   { volatile atomic<int,weak> a(0);  a++; }
   { volatile atomic<int,weak> a(0);  --a; }
   { volatile atomic<int,weak> a(0);  a--; }

   // weak::pun
   { volatile atomic<int,weak::pun> a(0);  a +=  2; }
   { volatile atomic<int,weak::pun> a(0);  a -=  2; }
   { volatile atomic<int,weak::pun> a(0);  a *=  2; }
   { volatile atomic<int,weak::pun> a(0);  a /=  2; }
   { volatile atomic<int,weak::pun> a(0);  a %=  2; }
   { volatile atomic<int,weak::pun> a(0);  a <<= 2; }
   { volatile atomic<int,weak::pun> a(0);  a >>= 2; }
   { volatile atomic<int,weak::pun> a(0);  a &=  2; }
   { volatile atomic<int,weak::pun> a(0);  a |=  2; }
   { volatile atomic<int,weak::pun> a(0);  a ^=  2; }
   { volatile atomic<int,weak::pun> a(0);  ++a; }
   { volatile atomic<int,weak::pun> a(0);  a++; }
   { volatile atomic<int,weak::pun> a(0);  --a; }
   { volatile atomic<int,weak::pun> a(0);  a--; }

   // lock
   { volatile atomic<int,lock> a(0);  a +=  2; }
   { volatile atomic<int,lock> a(0);  a -=  2; }
   { volatile atomic<int,lock> a(0);  a *=  2; }
   { volatile atomic<int,lock> a(0);  a /=  2; }
   { volatile atomic<int,lock> a(0);  a %=  2; }
   { volatile atomic<int,lock> a(0);  a <<= 2; }
   { volatile atomic<int,lock> a(0);  a >>= 2; }
   { volatile atomic<int,lock> a(0);  a &=  2; }
   { volatile atomic<int,lock> a(0);  a |=  2; }
   { volatile atomic<int,lock> a(0);  a ^=  2; }
   { volatile atomic<int,lock> a(0);  ++a; }
   { volatile atomic<int,lock> a(0);  a++; }
   { volatile atomic<int,lock> a(0);  --a; }
   { volatile atomic<int,lock> a(0);  a--; }

   // serial
   { volatile atomic<int,serial> a(0);  a +=  2; }
   { volatile atomic<int,serial> a(0);  a -=  2; }
   { volatile atomic<int,serial> a(0);  a *=  2; }
   { volatile atomic<int,serial> a(0);  a /=  2; }
   { volatile atomic<int,serial> a(0);  a %=  2; }
   { volatile atomic<int,serial> a(0);  a <<= 2; }
   { volatile atomic<int,serial> a(0);  a >>= 2; }
   { volatile atomic<int,serial> a(0);  a &=  2; }
   { volatile atomic<int,serial> a(0);  a |=  2; }
   { volatile atomic<int,serial> a(0);  a ^=  2; }
   { volatile atomic<int,serial> a(0);  ++a; }
   { volatile atomic<int,serial> a(0);  a++; }
   { volatile atomic<int,serial> a(0);  --a; }
   { volatile atomic<int,serial> a(0);  a--; }



   // ------------------------
   // unsigned long
   // ------------------------

   // cpp
   { volatile atomic<ulong,cpp> a(0);  a +=  2; }
   { volatile atomic<ulong,cpp> a(0);  a -=  2; }
// { volatile atomic<ulong,cpp> a(0);  a *=  2; }  // std::atomic<ulong> has no *=
// { volatile atomic<ulong,cpp> a(0);  a /=  2; }  // ...
// { volatile atomic<ulong,cpp> a(0);  a %=  2; }  // ...
// { volatile atomic<ulong,cpp> a(0);  a <<= 2; }  // ...
// { volatile atomic<ulong,cpp> a(0);  a >>= 2; }  // ...
   { volatile atomic<ulong,cpp> a(0);  a &=  2; }
   { volatile atomic<ulong,cpp> a(0);  a |=  2; }
   { volatile atomic<ulong,cpp> a(0);  a ^=  2; }
   { volatile atomic<ulong,cpp> a(0);  ++a; }
   { volatile atomic<ulong,cpp> a(0);  a++; }
   { volatile atomic<ulong,cpp> a(0);  --a; }
   { volatile atomic<ulong,cpp> a(0);  a--; }

   // kokkos
#if defined(ATOMICS_KOKKOS)
   { volatile atomic<ulong,kokkos> a(0);  a +=  2; }
   { volatile atomic<ulong,kokkos> a(0);  a -=  2; }
   { volatile atomic<ulong,kokkos> a(0);  a *=  2; }
   { volatile atomic<ulong,kokkos> a(0);  a /=  2; }
   { volatile atomic<ulong,kokkos> a(0);  a %=  2; }
   { volatile atomic<ulong,kokkos> a(0);  a <<= 2; }
   { volatile atomic<ulong,kokkos> a(0);  a >>= 2; }
   { volatile atomic<ulong,kokkos> a(0);  a &=  2; }
   { volatile atomic<ulong,kokkos> a(0);  a |=  2; }
   { volatile atomic<ulong,kokkos> a(0);  a ^=  2; }
   { volatile atomic<ulong,kokkos> a(0);  ++a; }
   { volatile atomic<ulong,kokkos> a(0);  a++; }
   { volatile atomic<ulong,kokkos> a(0);  --a; }
   { volatile atomic<ulong,kokkos> a(0);  a--; }
#endif

   // strong
   { volatile atomic<ulong,strong> a(0);  a +=  2; }
   { volatile atomic<ulong,strong> a(0);  a -=  2; }
   { volatile atomic<ulong,strong> a(0);  a *=  2; }
   { volatile atomic<ulong,strong> a(0);  a /=  2; }
   { volatile atomic<ulong,strong> a(0);  a %=  2; }
   { volatile atomic<ulong,strong> a(0);  a <<= 2; }
   { volatile atomic<ulong,strong> a(0);  a >>= 2; }
   { volatile atomic<ulong,strong> a(0);  a &=  2; }
   { volatile atomic<ulong,strong> a(0);  a |=  2; }
   { volatile atomic<ulong,strong> a(0);  a ^=  2; }
   { volatile atomic<ulong,strong> a(0);  ++a; }
   { volatile atomic<ulong,strong> a(0);  a++; }
   { volatile atomic<ulong,strong> a(0);  --a; }
   { volatile atomic<ulong,strong> a(0);  a--; }

   // strong::pun
   { volatile atomic<ulong,strong::pun> a(0);  a +=  2; }
   { volatile atomic<ulong,strong::pun> a(0);  a -=  2; }
   { volatile atomic<ulong,strong::pun> a(0);  a *=  2; }
   { volatile atomic<ulong,strong::pun> a(0);  a /=  2; }
   { volatile atomic<ulong,strong::pun> a(0);  a %=  2; }
   { volatile atomic<ulong,strong::pun> a(0);  a <<= 2; }
   { volatile atomic<ulong,strong::pun> a(0);  a >>= 2; }
   { volatile atomic<ulong,strong::pun> a(0);  a &=  2; }
   { volatile atomic<ulong,strong::pun> a(0);  a |=  2; }
   { volatile atomic<ulong,strong::pun> a(0);  a ^=  2; }
   { volatile atomic<ulong,strong::pun> a(0);  ++a; }
   { volatile atomic<ulong,strong::pun> a(0);  a++; }
   { volatile atomic<ulong,strong::pun> a(0);  --a; }
   { volatile atomic<ulong,strong::pun> a(0);  a--; }

   // weak
   { volatile atomic<ulong,weak> a(0);  a +=  2; }
   { volatile atomic<ulong,weak> a(0);  a -=  2; }
   { volatile atomic<ulong,weak> a(0);  a *=  2; }
   { volatile atomic<ulong,weak> a(0);  a /=  2; }
   { volatile atomic<ulong,weak> a(0);  a %=  2; }
   { volatile atomic<ulong,weak> a(0);  a <<= 2; }
   { volatile atomic<ulong,weak> a(0);  a >>= 2; }
   { volatile atomic<ulong,weak> a(0);  a &=  2; }
   { volatile atomic<ulong,weak> a(0);  a |=  2; }
   { volatile atomic<ulong,weak> a(0);  a ^=  2; }
   { volatile atomic<ulong,weak> a(0);  ++a; }
   { volatile atomic<ulong,weak> a(0);  a++; }
   { volatile atomic<ulong,weak> a(0);  --a; }
   { volatile atomic<ulong,weak> a(0);  a--; }

   // weak::pun
   { volatile atomic<ulong,weak::pun> a(0);  a +=  2; }
   { volatile atomic<ulong,weak::pun> a(0);  a -=  2; }
   { volatile atomic<ulong,weak::pun> a(0);  a *=  2; }
   { volatile atomic<ulong,weak::pun> a(0);  a /=  2; }
   { volatile atomic<ulong,weak::pun> a(0);  a %=  2; }
   { volatile atomic<ulong,weak::pun> a(0);  a <<= 2; }
   { volatile atomic<ulong,weak::pun> a(0);  a >>= 2; }
   { volatile atomic<ulong,weak::pun> a(0);  a &=  2; }
   { volatile atomic<ulong,weak::pun> a(0);  a |=  2; }
   { volatile atomic<ulong,weak::pun> a(0);  a ^=  2; }
   { volatile atomic<ulong,weak::pun> a(0);  ++a; }
   { volatile atomic<ulong,weak::pun> a(0);  a++; }
   { volatile atomic<ulong,weak::pun> a(0);  --a; }
   { volatile atomic<ulong,weak::pun> a(0);  a--; }

   // lock
   { volatile atomic<ulong,lock> a(0);  a +=  2; }
   { volatile atomic<ulong,lock> a(0);  a -=  2; }
   { volatile atomic<ulong,lock> a(0);  a *=  2; }
   { volatile atomic<ulong,lock> a(0);  a /=  2; }
   { volatile atomic<ulong,lock> a(0);  a %=  2; }
   { volatile atomic<ulong,lock> a(0);  a <<= 2; }
   { volatile atomic<ulong,lock> a(0);  a >>= 2; }
   { volatile atomic<ulong,lock> a(0);  a &=  2; }
   { volatile atomic<ulong,lock> a(0);  a |=  2; }
   { volatile atomic<ulong,lock> a(0);  a ^=  2; }
   { volatile atomic<ulong,lock> a(0);  ++a; }
   { volatile atomic<ulong,lock> a(0);  a++; }
   { volatile atomic<ulong,lock> a(0);  --a; }
   { volatile atomic<ulong,lock> a(0);  a--; }

   // serial
   { volatile atomic<ulong,serial> a(0);  a +=  2; }
   { volatile atomic<ulong,serial> a(0);  a -=  2; }
   { volatile atomic<ulong,serial> a(0);  a *=  2; }
   { volatile atomic<ulong,serial> a(0);  a /=  2; }
   { volatile atomic<ulong,serial> a(0);  a %=  2; }
   { volatile atomic<ulong,serial> a(0);  a <<= 2; }
   { volatile atomic<ulong,serial> a(0);  a >>= 2; }
   { volatile atomic<ulong,serial> a(0);  a &=  2; }
   { volatile atomic<ulong,serial> a(0);  a |=  2; }
   { volatile atomic<ulong,serial> a(0);  a ^=  2; }
   { volatile atomic<ulong,serial> a(0);  ++a; }
   { volatile atomic<ulong,serial> a(0);  a++; }
   { volatile atomic<ulong,serial> a(0);  --a; }
   { volatile atomic<ulong,serial> a(0);  a--; }



   // ------------------------
   // double
   // ------------------------

   // cpp <== meaning C++ std::atomic<T> must have these
// { volatile atomic<double,cpp> a(0);  a +=  2; }  // std::atomic<double> has no +=
// { volatile atomic<double,cpp> a(0);  a -=  2; }  // ...
// { volatile atomic<double,cpp> a(0);  a *=  2; }  // ...
// { volatile atomic<double,cpp> a(0);  a /=  2; }  // ...
// { volatile atomic<double,cpp> a(0);  a %=  2; }  // ...also no %= for plain double
// { volatile atomic<double,cpp> a(0);  a <<= 2; }  // ...
// { volatile atomic<double,cpp> a(0);  a >>= 2; }  // ...
// { volatile atomic<double,cpp> a(0);  a &=  2; }  // ...
// { volatile atomic<double,cpp> a(0);  a |=  2; }  // ...
// { volatile atomic<double,cpp> a(0);  a ^=  2; }  // ...
// { volatile atomic<double,cpp> a(0);  ++a; }  // ...Remember, the issue here again
// { volatile atomic<double,cpp> a(0);  a++; }  // ...is that std::atomic for double
// { volatile atomic<double,cpp> a(0);  --a; }  // ...doesn't support ++ and --, even
// { volatile atomic<double,cpp> a(0);  a--; }  // ...though plain double has those.

   // kokkos
#if defined(ATOMICS_KOKKOS)
   { volatile atomic<double,kokkos> a(0);  a +=  2; }
   { volatile atomic<double,kokkos> a(0);  a -=  2; }
   { volatile atomic<double,kokkos> a(0);  a *=  2; }
   { volatile atomic<double,kokkos> a(0);  a /=  2; }
// { volatile atomic<double,kokkos> a(0);  a %=  2; }  // C++ has no %= for double
// { volatile atomic<double,kokkos> a(0);  a <<= 2; }  // ...
// { volatile atomic<double,kokkos> a(0);  a >>= 2; }  // ...
// { volatile atomic<double,kokkos> a(0);  a &=  2; }  // ...
// { volatile atomic<double,kokkos> a(0);  a |=  2; }  // ...
// { volatile atomic<double,kokkos> a(0);  a ^=  2; }  // ...
   { volatile atomic<double,kokkos> a(0);  ++a; }
   { volatile atomic<double,kokkos> a(0);  a++; }
   { volatile atomic<double,kokkos> a(0);  --a; }
   { volatile atomic<double,kokkos> a(0);  a--; }
#endif

   // strong
   { volatile atomic<double,strong> a(0);  a +=  2; }
   { volatile atomic<double,strong> a(0);  a -=  2; }
   { volatile atomic<double,strong> a(0);  a *=  2; }
   { volatile atomic<double,strong> a(0);  a /=  2; }
// { volatile atomic<double,strong> a(0);  a %=  2; }  // C++ has no %= for double
// { volatile atomic<double,strong> a(0);  a <<= 2; }  // ...
// { volatile atomic<double,strong> a(0);  a >>= 2; }  // ...
// { volatile atomic<double,strong> a(0);  a &=  2; }  // ...
// { volatile atomic<double,strong> a(0);  a |=  2; }  // ...
// { volatile atomic<double,strong> a(0);  a ^=  2; }  // ...
   { volatile atomic<double,strong> a(0);  ++a; }
   { volatile atomic<double,strong> a(0);  a++; }
   { volatile atomic<double,strong> a(0);  --a; }
   { volatile atomic<double,strong> a(0);  a--; }

   // strong::pun
   { volatile atomic<double,strong::pun> a(0);  a +=  2; }
   { volatile atomic<double,strong::pun> a(0);  a -=  2; }
   { volatile atomic<double,strong::pun> a(0);  a *=  2; }
   { volatile atomic<double,strong::pun> a(0);  a /=  2; }
// { volatile atomic<double,strong::pun> a(0);  a %=  2; }  // C++ has no %= for double
// { volatile atomic<double,strong::pun> a(0);  a <<= 2; }  // ...
// { volatile atomic<double,strong::pun> a(0);  a >>= 2; }  // ...
// { volatile atomic<double,strong::pun> a(0);  a &=  2; }  // ...
// { volatile atomic<double,strong::pun> a(0);  a |=  2; }  // ...
// { volatile atomic<double,strong::pun> a(0);  a ^=  2; }  // ...
   { volatile atomic<double,strong::pun> a(0);  ++a; }
   { volatile atomic<double,strong::pun> a(0);  a++; }
   { volatile atomic<double,strong::pun> a(0);  --a; }
   { volatile atomic<double,strong::pun> a(0);  a--; }

   // weak
   { volatile atomic<double,weak> a(0);  a +=  2; }
   { volatile atomic<double,weak> a(0);  a -=  2; }
   { volatile atomic<double,weak> a(0);  a *=  2; }
   { volatile atomic<double,weak> a(0);  a /=  2; }
// { volatile atomic<double,weak> a(0);  a %=  2; }  // C++ has no %= for double
// { volatile atomic<double,weak> a(0);  a <<= 2; }  // ...
// { volatile atomic<double,weak> a(0);  a >>= 2; }  // ...
// { volatile atomic<double,weak> a(0);  a &=  2; }  // ...
// { volatile atomic<double,weak> a(0);  a |=  2; }  // ...
// { volatile atomic<double,weak> a(0);  a ^=  2; }  // ...
   { volatile atomic<double,weak> a(0);  ++a; }
   { volatile atomic<double,weak> a(0);  a++; }
   { volatile atomic<double,weak> a(0);  --a; }
   { volatile atomic<double,weak> a(0);  a--; }

   // weak::pun
   { volatile atomic<double,weak::pun> a(0);  a +=  2; }
   { volatile atomic<double,weak::pun> a(0);  a -=  2; }
   { volatile atomic<double,weak::pun> a(0);  a *=  2; }
   { volatile atomic<double,weak::pun> a(0);  a /=  2; }
// { volatile atomic<double,weak::pun> a(0);  a %=  2; }  // C++ has no %= for double
// { volatile atomic<double,weak::pun> a(0);  a <<= 2; }  // ...
// { volatile atomic<double,weak::pun> a(0);  a >>= 2; }  // ...
// { volatile atomic<double,weak::pun> a(0);  a &=  2; }  // ...
// { volatile atomic<double,weak::pun> a(0);  a |=  2; }  // ...
// { volatile atomic<double,weak::pun> a(0);  a ^=  2; }  // ...
   { volatile atomic<double,weak::pun> a(0);  ++a; }
   { volatile atomic<double,weak::pun> a(0);  a++; }
   { volatile atomic<double,weak::pun> a(0);  --a; }
   { volatile atomic<double,weak::pun> a(0);  a--; }

   // lock
   { volatile atomic<double,lock> a(0);  a +=  2; }
   { volatile atomic<double,lock> a(0);  a -=  2; }
   { volatile atomic<double,lock> a(0);  a *=  2; }
   { volatile atomic<double,lock> a(0);  a /=  2; }
// { volatile atomic<double,lock> a(0);  a %=  2; }  // C++ has no %= for double
// { volatile atomic<double,lock> a(0);  a <<= 2; }  // ...
// { volatile atomic<double,lock> a(0);  a >>= 2; }  // ...
// { volatile atomic<double,lock> a(0);  a &=  2; }  // ...
// { volatile atomic<double,lock> a(0);  a |=  2; }  // ...
// { volatile atomic<double,lock> a(0);  a ^=  2; }  // ...
   { volatile atomic<double,lock> a(0);  ++a; }
   { volatile atomic<double,lock> a(0);  a++; }
   { volatile atomic<double,lock> a(0);  --a; }
   { volatile atomic<double,lock> a(0);  a--; }

   // serial
   { volatile atomic<double,serial> a(0);  a +=  2; }
   { volatile atomic<double,serial> a(0);  a -=  2; }
   { volatile atomic<double,serial> a(0);  a *=  2; }
   { volatile atomic<double,serial> a(0);  a /=  2; }
// { volatile atomic<double,serial> a(0);  a %=  2; }  // C++ has no %= for double
// { volatile atomic<double,serial> a(0);  a <<= 2; }  // ...
// { volatile atomic<double,serial> a(0);  a >>= 2; }  // ...
// { volatile atomic<double,serial> a(0);  a &=  2; }  // ...
// { volatile atomic<double,serial> a(0);  a |=  2; }  // ...
// { volatile atomic<double,serial> a(0);  a ^=  2; }  // ...
   { volatile atomic<double,serial> a(0);  ++a; }
   { volatile atomic<double,serial> a(0);  a++; }
   { volatile atomic<double,serial> a(0);  --a; }
   { volatile atomic<double,serial> a(0);  a--; }



   // ------------------------
   // int*
   // So: pointer arithmetic
   // ------------------------

#if !defined(ATOMICS_TEST)
   // cpp
   { volatile atomic<int*,cpp> a(&i);  a +=  2; }
   { volatile atomic<int*,cpp> a(&i);  a -=  2; }
// { volatile atomic<int*,cpp> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { volatile atomic<int*,cpp> a(&i);  a /=  2; }  // ...
// { volatile atomic<int*,cpp> a(&i);  a %=  2; }  // ...
// { volatile atomic<int*,cpp> a(&i);  a <<= 2; }  // ...
// { volatile atomic<int*,cpp> a(&i);  a >>= 2; }  // ...
// { volatile atomic<int*,cpp> a(&i);  a &=  2; }  // ...
// { volatile atomic<int*,cpp> a(&i);  a |=  2; }  // ...
// { volatile atomic<int*,cpp> a(&i);  a ^=  2; }  // ...
   { volatile atomic<int*,cpp> a(&i);  ++a; }
   { volatile atomic<int*,cpp> a(&i);  a++; }
   { volatile atomic<int*,cpp> a(&i);  --a; }
   { volatile atomic<int*,cpp> a(&i);  a--; }

   // kokkos
#if defined(ATOMICS_KOKKOS)
// { volatile atomic<int*,kokkos> a(&i);  a +=  2; }  // Kokkos has nothing for pointers
// { volatile atomic<int*,kokkos> a(&i);  a -=  2; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  a *=  2; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  a /=  2; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  a %=  2; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  a <<= 2; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  a >>= 2; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  a &=  2; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  a |=  2; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  a ^=  2; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  ++a; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  a++; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  --a; }  // ...
// { volatile atomic<int*,kokkos> a(&i);  a--; }  // ...
#endif

   // strong
   { volatile atomic<int*,strong> a(&i);  a +=  2; }
   { volatile atomic<int*,strong> a(&i);  a -=  2; }
// { volatile atomic<int*,strong> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { volatile atomic<int*,strong> a(&i);  a /=  2; }  // ...
// { volatile atomic<int*,strong> a(&i);  a %=  2; }  // ...
// { volatile atomic<int*,strong> a(&i);  a <<= 2; }  // ...
// { volatile atomic<int*,strong> a(&i);  a >>= 2; }  // ...
// { volatile atomic<int*,strong> a(&i);  a &=  2; }  // ...
// { volatile atomic<int*,strong> a(&i);  a |=  2; }  // ...
// { volatile atomic<int*,strong> a(&i);  a ^=  2; }  // ...
   { volatile atomic<int*,strong> a(&i);  ++a; }
   { volatile atomic<int*,strong> a(&i);  a++; }
   { volatile atomic<int*,strong> a(&i);  --a; }
   { volatile atomic<int*,strong> a(&i);  a--; }

   // strong::pun
   { volatile atomic<int*,strong::pun> a(&i);  a +=  2; }
   { volatile atomic<int*,strong::pun> a(&i);  a -=  2; }
// { volatile atomic<int*,strong::pun> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { volatile atomic<int*,strong::pun> a(&i);  a /=  2; }  // ...
// { volatile atomic<int*,strong::pun> a(&i);  a %=  2; }  // ...
// { volatile atomic<int*,strong::pun> a(&i);  a <<= 2; }  // ...
// { volatile atomic<int*,strong::pun> a(&i);  a >>= 2; }  // ...
// { volatile atomic<int*,strong::pun> a(&i);  a &=  2; }  // ...
// { volatile atomic<int*,strong::pun> a(&i);  a |=  2; }  // ...
// { volatile atomic<int*,strong::pun> a(&i);  a ^=  2; }  // ...
   { volatile atomic<int*,strong::pun> a(&i);  ++a; }
   { volatile atomic<int*,strong::pun> a(&i);  a++; }
   { volatile atomic<int*,strong::pun> a(&i);  --a; }
   { volatile atomic<int*,strong::pun> a(&i);  a--; }

   // weak
   { volatile atomic<int*,weak> a(&i);  a +=  2; }
   { volatile atomic<int*,weak> a(&i);  a -=  2; }
// { volatile atomic<int*,weak> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { volatile atomic<int*,weak> a(&i);  a /=  2; }  // ...
// { volatile atomic<int*,weak> a(&i);  a %=  2; }  // ...
// { volatile atomic<int*,weak> a(&i);  a <<= 2; }  // ...
// { volatile atomic<int*,weak> a(&i);  a >>= 2; }  // ...
// { volatile atomic<int*,weak> a(&i);  a &=  2; }  // ...
// { volatile atomic<int*,weak> a(&i);  a |=  2; }  // ...
// { volatile atomic<int*,weak> a(&i);  a ^=  2; }  // ...
   { volatile atomic<int*,weak> a(&i);  ++a; }
   { volatile atomic<int*,weak> a(&i);  a++; }
   { volatile atomic<int*,weak> a(&i);  --a; }
   { volatile atomic<int*,weak> a(&i);  a--; }

   // weak::pun
   { volatile atomic<int*,weak::pun> a(&i);  a +=  2; }
   { volatile atomic<int*,weak::pun> a(&i);  a -=  2; }
// { volatile atomic<int*,weak::pun> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { volatile atomic<int*,weak::pun> a(&i);  a /=  2; }  // ...
// { volatile atomic<int*,weak::pun> a(&i);  a %=  2; }  // ...
// { volatile atomic<int*,weak::pun> a(&i);  a <<= 2; }  // ...
// { volatile atomic<int*,weak::pun> a(&i);  a >>= 2; }  // ...
// { volatile atomic<int*,weak::pun> a(&i);  a &=  2; }  // ...
// { volatile atomic<int*,weak::pun> a(&i);  a |=  2; }  // ...
// { volatile atomic<int*,weak::pun> a(&i);  a ^=  2; }  // ...
   { volatile atomic<int*,weak::pun> a(&i);  ++a; }
   { volatile atomic<int*,weak::pun> a(&i);  a++; }
   { volatile atomic<int*,weak::pun> a(&i);  --a; }
   { volatile atomic<int*,weak::pun> a(&i);  a--; }

   // lock
   { volatile atomic<int*,lock> a(&i);  a +=  2; }
   { volatile atomic<int*,lock> a(&i);  a -=  2; }
// { volatile atomic<int*,lock> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { volatile atomic<int*,lock> a(&i);  a /=  2; }  // ...
// { volatile atomic<int*,lock> a(&i);  a %=  2; }  // ...
// { volatile atomic<int*,lock> a(&i);  a <<= 2; }  // ...
// { volatile atomic<int*,lock> a(&i);  a >>= 2; }  // ...
// { volatile atomic<int*,lock> a(&i);  a &=  2; }  // ...
// { volatile atomic<int*,lock> a(&i);  a |=  2; }  // ...
// { volatile atomic<int*,lock> a(&i);  a ^=  2; }  // ...
   { volatile atomic<int*,lock> a(&i);  ++a; }
   { volatile atomic<int*,lock> a(&i);  a++; }
   { volatile atomic<int*,lock> a(&i);  --a; }
   { volatile atomic<int*,lock> a(&i);  a--; }

   // serial
   { volatile atomic<int*,serial> a(&i);  a +=  2; }
   { volatile atomic<int*,serial> a(&i);  a -=  2; }
// { volatile atomic<int*,serial> a(&i);  a *=  2; }  // C++ has no *= for pointer
// { volatile atomic<int*,serial> a(&i);  a /=  2; }  // ...
// { volatile atomic<int*,serial> a(&i);  a %=  2; }  // ...
// { volatile atomic<int*,serial> a(&i);  a <<= 2; }  // ...
// { volatile atomic<int*,serial> a(&i);  a >>= 2; }  // ...
// { volatile atomic<int*,serial> a(&i);  a &=  2; }  // ...
// { volatile atomic<int*,serial> a(&i);  a |=  2; }  // ...
// { volatile atomic<int*,serial> a(&i);  a ^=  2; }  // ...
   { volatile atomic<int*,serial> a(&i);  ++a; }
   { volatile atomic<int*,serial> a(&i);  a++; }
   { volatile atomic<int*,serial> a(&i);  --a; }
   { volatile atomic<int*,serial> a(&i);  a--; }
#endif



   // ------------------------
   // std::complex
   // ------------------------

   // cpp
// { volatile atomic<cmplx,cpp> a(0);  a +=  c; } // C++ atomics don't support complex
// { volatile atomic<cmplx,cpp> a(0);  a -=  c; } // ...
// { volatile atomic<cmplx,cpp> a(0);  a *=  c; } // ...
// { volatile atomic<cmplx,cpp> a(0);  a /=  c; } // ...
// { volatile atomic<cmplx,cpp> a(0);  a %=  c; } // ...
// { volatile atomic<cmplx,cpp> a(0);  a <<= c; } // ...
// { volatile atomic<cmplx,cpp> a(0);  a >>= c; } // ...
// { volatile atomic<cmplx,cpp> a(0);  a &=  c; } // ...
// { volatile atomic<cmplx,cpp> a(0);  a |=  c; } // ...
// { volatile atomic<cmplx,cpp> a(0);  a ^=  c; } // ...
// { volatile atomic<cmplx,cpp> a(0);  ++a; } // ...
// { volatile atomic<cmplx,cpp> a(0);  a++; } // ...
// { volatile atomic<cmplx,cpp> a(0);  --a; } // ...
// { volatile atomic<cmplx,cpp> a(0);  a--; } // ...

   // kokkos
#if defined(ATOMICS_KOKKOS)
// { volatile atomic<cmplx,kokkos> a(0);  a +=  c; } // Kokkos atomics don't either
// { volatile atomic<cmplx,kokkos> a(0);  a -=  c; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  a *=  c; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  a /=  c; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  a %=  c; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  a <<= c; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  a >>= c; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  a &=  c; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  a |=  c; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  a ^=  c; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  ++a; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  a++; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  --a; } // ...
// { volatile atomic<cmplx,kokkos> a(0);  a--; } // ...
#endif

   // strong
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong> a(0);  a +=  c; }
   { volatile atomic<cmplx,strong> a(0);  a -=  c; }
   { volatile atomic<cmplx,strong> a(0);  a *=  c; }
   { volatile atomic<cmplx,strong> a(0);  a /=  c; }
#endif
// { volatile atomic<cmplx,strong> a(0);  a %=  c; }  // no modulo for complex
// { volatile atomic<cmplx,strong> a(0);  a <<= c; }  // no bitwise ops for complex
// { volatile atomic<cmplx,strong> a(0);  a >>= c; } // ...
// { volatile atomic<cmplx,strong> a(0);  a &=  c; } // ...
// { volatile atomic<cmplx,strong> a(0);  a |=  c; } // ...
// { volatile atomic<cmplx,strong> a(0);  a ^=  c; } // ...
// { volatile atomic<cmplx,strong> a(0);  ++a; }  // no ++ or -- for complex
// { volatile atomic<cmplx,strong> a(0);  a++; } // ...
// { volatile atomic<cmplx,strong> a(0);  --a; } // ...
// { volatile atomic<cmplx,strong> a(0);  a--; } // ...

   // strong::pun
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong::pun> a(0);  a +=  c; }
   { volatile atomic<cmplx,strong::pun> a(0);  a -=  c; }
   { volatile atomic<cmplx,strong::pun> a(0);  a *=  c; }
   { volatile atomic<cmplx,strong::pun> a(0);  a /=  c; }
#endif
// { volatile atomic<cmplx,strong::pun> a(0);  a %=  c; } // as for strong
// { volatile atomic<cmplx,strong::pun> a(0);  a <<= c; } // ...
// { volatile atomic<cmplx,strong::pun> a(0);  a >>= c; } // ...
// { volatile atomic<cmplx,strong::pun> a(0);  a &=  c; } // ...
// { volatile atomic<cmplx,strong::pun> a(0);  a |=  c; } // ...
// { volatile atomic<cmplx,strong::pun> a(0);  a ^=  c; } // ...
// { volatile atomic<cmplx,strong::pun> a(0);  ++a; } // ...
// { volatile atomic<cmplx,strong::pun> a(0);  a++; } // ...
// { volatile atomic<cmplx,strong::pun> a(0);  --a; } // ...
// { volatile atomic<cmplx,strong::pun> a(0);  a--; } // ...

   // weak
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak> a(0);  a +=  c; }
   { volatile atomic<cmplx,weak> a(0);  a -=  c; }
   { volatile atomic<cmplx,weak> a(0);  a *=  c; }
   { volatile atomic<cmplx,weak> a(0);  a /=  c; }
#endif
// { volatile atomic<cmplx,weak> a(0);  a %=  c; } // as for strong
// { volatile atomic<cmplx,weak> a(0);  a <<= c; } // ...
// { volatile atomic<cmplx,weak> a(0);  a >>= c; } // ...
// { volatile atomic<cmplx,weak> a(0);  a &=  c; } // ...
// { volatile atomic<cmplx,weak> a(0);  a |=  c; } // ...
// { volatile atomic<cmplx,weak> a(0);  a ^=  c; } // ...
// { volatile atomic<cmplx,weak> a(0);  ++a; } // ...
// { volatile atomic<cmplx,weak> a(0);  a++; } // ...
// { volatile atomic<cmplx,weak> a(0);  --a; } // ...
// { volatile atomic<cmplx,weak> a(0);  a--; } // ...

   // weak::pun
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak::pun> a(0);  a +=  c; }
   { volatile atomic<cmplx,weak::pun> a(0);  a -=  c; }
   { volatile atomic<cmplx,weak::pun> a(0);  a *=  c; }
   { volatile atomic<cmplx,weak::pun> a(0);  a /=  c; }
#endif
// { volatile atomic<cmplx,weak::pun> a(0);  a %=  c; } // as for strong
// { volatile atomic<cmplx,weak::pun> a(0);  a <<= c; } // ...
// { volatile atomic<cmplx,weak::pun> a(0);  a >>= c; } // ...
// { volatile atomic<cmplx,weak::pun> a(0);  a &=  c; } // ...
// { volatile atomic<cmplx,weak::pun> a(0);  a |=  c; } // ...
// { volatile atomic<cmplx,weak::pun> a(0);  a ^=  c; } // ...
// { volatile atomic<cmplx,weak::pun> a(0);  ++a; } // ...
// { volatile atomic<cmplx,weak::pun> a(0);  a++; } // ...
// { volatile atomic<cmplx,weak::pun> a(0);  --a; } // ...
// { volatile atomic<cmplx,weak::pun> a(0);  a--; } // ...

   // lock
//v{ volatile atomic<cmplx,lock> a(0);  a +=  c; }
//v{ volatile atomic<cmplx,lock> a(0);  a -=  c; }
//v{ volatile atomic<cmplx,lock> a(0);  a *=  c; }
//v{ volatile atomic<cmplx,lock> a(0);  a /=  c; }
// { volatile atomic<cmplx,lock> a(0);  a %=  c; } // as for strong
// { volatile atomic<cmplx,lock> a(0);  a <<= c; } // ...
// { volatile atomic<cmplx,lock> a(0);  a >>= c; } // ...
// { volatile atomic<cmplx,lock> a(0);  a &=  c; } // ...
// { volatile atomic<cmplx,lock> a(0);  a |=  c; } // ...
// { volatile atomic<cmplx,lock> a(0);  a ^=  c; } // ...
// { volatile atomic<cmplx,lock> a(0);  ++a; } // ...
// { volatile atomic<cmplx,lock> a(0);  a++; } // ...
// { volatile atomic<cmplx,lock> a(0);  --a; } // ...
// { volatile atomic<cmplx,lock> a(0);  a--; } // ...

   // serial
//v{ volatile atomic<cmplx,serial> a(0);  a +=  c; }
//v{ volatile atomic<cmplx,serial> a(0);  a -=  c; }
//v{ volatile atomic<cmplx,serial> a(0);  a *=  c; }
//v{ volatile atomic<cmplx,serial> a(0);  a /=  c; }
// { volatile atomic<cmplx,serial> a(0);  a %=  c; } // as for strong
// { volatile atomic<cmplx,serial> a(0);  a <<= c; } // ...
// { volatile atomic<cmplx,serial> a(0);  a >>= c; } // ...
// { volatile atomic<cmplx,serial> a(0);  a &=  c; } // ...
// { volatile atomic<cmplx,serial> a(0);  a |=  c; } // ...
// { volatile atomic<cmplx,serial> a(0);  a ^=  c; } // ...
// { volatile atomic<cmplx,serial> a(0);  ++a; } // ...
// { volatile atomic<cmplx,serial> a(0);  a++; } // ...
// { volatile atomic<cmplx,serial> a(0);  --a; } // ...
// { volatile atomic<cmplx,serial> a(0);  a--; } // ...



   // ------------------------
   // foo (our own class)
   // See definition earlier
   // ------------------------

   // cpp <== again, means "must be supported directly by std::atomic<T>"
// { volatile atomic<foo,cpp> a(0);  a +=  b; }  // Nope, not with cpp
// { volatile atomic<foo,cpp> a(0);  a -=  b; }
// { volatile atomic<foo,cpp> a(0);  a *=  b; }
// { volatile atomic<foo,cpp> a(0);  a /=  b; }
// { volatile atomic<foo,cpp> a(0);  a %=  b; }
// { volatile atomic<foo,cpp> a(0);  a <<= b; }
// { volatile atomic<foo,cpp> a(0);  a >>= b; }
// { volatile atomic<foo,cpp> a(0);  a &=  b; }
// { volatile atomic<foo,cpp> a(0);  a |=  b; }
// { volatile atomic<foo,cpp> a(0);  a ^=  b; }
// { volatile atomic<foo,cpp> a(0);  ++a; }
// { volatile atomic<foo,cpp> a(0);  a++; }
// { volatile atomic<foo,cpp> a(0);  --a; }
// { volatile atomic<foo,cpp> a(0);  a--; }

   // kokkos
#if defined(ATOMICS_KOKKOS)
   // Note: there's really more than one Kokkos issue here. Kokkos atomic
   // functions can take a general T, but the functions assume that the
   // right-hand side is also a T. That is, X += Y may work if Y is of the
   // same type as X, or is convertible thereto. Here, however, for this
   // test code, I defined foo += bar, etc. Not foo += foo, etc.; and bars
   // aren't convertible to foos. Moreover, it seems like Kokkos sometimes
   // tries to accomplish X += Y by assuming X = X+Y will do the trick;
   // similarly for some other operations. So, then, we'd need a foo+bar
   // function, which we don't have.
// { volatile atomic<foo,kokkos> a(0);  a +=  b; }
// { volatile atomic<foo,kokkos> a(0);  a -=  b; }
// { volatile atomic<foo,kokkos> a(0);  a *=  b; }
// { volatile atomic<foo,kokkos> a(0);  a /=  b; }
// { volatile atomic<foo,kokkos> a(0);  a %=  b; }
// { volatile atomic<foo,kokkos> a(0);  a <<= b; }
// { volatile atomic<foo,kokkos> a(0);  a >>= b; }
// { volatile atomic<foo,kokkos> a(0);  a &=  b; }
// { volatile atomic<foo,kokkos> a(0);  a |=  b; }
// { volatile atomic<foo,kokkos> a(0);  a ^=  b; }
// { volatile atomic<foo,kokkos> a(0);  ++a; }
// { volatile atomic<foo,kokkos> a(0);  a++; }
// { volatile atomic<foo,kokkos> a(0);  --a; }
// { volatile atomic<foo,kokkos> a(0);  a--; }
#endif

   // strong
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,strong> a(0);  a +=  b; }
   { volatile atomic<foo,strong> a(0);  a -=  b; }
   { volatile atomic<foo,strong> a(0);  a *=  b; }
   { volatile atomic<foo,strong> a(0);  a /=  b; }
   { volatile atomic<foo,strong> a(0);  a %=  b; }
   { volatile atomic<foo,strong> a(0);  a <<= b; }
   { volatile atomic<foo,strong> a(0);  a >>= b; }
   { volatile atomic<foo,strong> a(0);  a &=  b; }
   { volatile atomic<foo,strong> a(0);  a |=  b; }
   { volatile atomic<foo,strong> a(0);  a ^=  b; }
   { volatile atomic<foo,strong> a(0);  ++a; }
   { volatile atomic<foo,strong> a(0);  a++; }
   { volatile atomic<foo,strong> a(0);  --a; }
   { volatile atomic<foo,strong> a(0);  a--; }
#endif

   // strong::pun
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,strong::pun> a(0);  a +=  b; }
   { volatile atomic<foo,strong::pun> a(0);  a -=  b; }
   { volatile atomic<foo,strong::pun> a(0);  a *=  b; }
   { volatile atomic<foo,strong::pun> a(0);  a /=  b; }
   { volatile atomic<foo,strong::pun> a(0);  a %=  b; }
   { volatile atomic<foo,strong::pun> a(0);  a <<= b; }
   { volatile atomic<foo,strong::pun> a(0);  a >>= b; }
   { volatile atomic<foo,strong::pun> a(0);  a &=  b; }
   { volatile atomic<foo,strong::pun> a(0);  a |=  b; }
   { volatile atomic<foo,strong::pun> a(0);  a ^=  b; }
   { volatile atomic<foo,strong::pun> a(0);  ++a; }
   { volatile atomic<foo,strong::pun> a(0);  a++; }
   { volatile atomic<foo,strong::pun> a(0);  --a; }
   { volatile atomic<foo,strong::pun> a(0);  a--; }
#endif

   // weak
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,weak> a(0);  a +=  b; }
   { volatile atomic<foo,weak> a(0);  a -=  b; }
   { volatile atomic<foo,weak> a(0);  a *=  b; }
   { volatile atomic<foo,weak> a(0);  a /=  b; }
   { volatile atomic<foo,weak> a(0);  a %=  b; }
   { volatile atomic<foo,weak> a(0);  a <<= b; }
   { volatile atomic<foo,weak> a(0);  a >>= b; }
   { volatile atomic<foo,weak> a(0);  a &=  b; }
   { volatile atomic<foo,weak> a(0);  a |=  b; }
   { volatile atomic<foo,weak> a(0);  a ^=  b; }
   { volatile atomic<foo,weak> a(0);  ++a; }
   { volatile atomic<foo,weak> a(0);  a++; }
   { volatile atomic<foo,weak> a(0);  --a; }
   { volatile atomic<foo,weak> a(0);  a--; }
#endif

   // weak::pun
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,weak::pun> a(0);  a +=  b; }
   { volatile atomic<foo,weak::pun> a(0);  a -=  b; }
   { volatile atomic<foo,weak::pun> a(0);  a *=  b; }
   { volatile atomic<foo,weak::pun> a(0);  a /=  b; }
   { volatile atomic<foo,weak::pun> a(0);  a %=  b; }
   { volatile atomic<foo,weak::pun> a(0);  a <<= b; }
   { volatile atomic<foo,weak::pun> a(0);  a >>= b; }
   { volatile atomic<foo,weak::pun> a(0);  a &=  b; }
   { volatile atomic<foo,weak::pun> a(0);  a |=  b; }
   { volatile atomic<foo,weak::pun> a(0);  a ^=  b; }
   { volatile atomic<foo,weak::pun> a(0);  ++a; }
   { volatile atomic<foo,weak::pun> a(0);  a++; }
   { volatile atomic<foo,weak::pun> a(0);  --a; }
   { volatile atomic<foo,weak::pun> a(0);  a--; }
#endif

   // lock
//v{ volatile atomic<foo,lock> a(0);  a +=  b; }
//v{ volatile atomic<foo,lock> a(0);  a -=  b; }
//v{ volatile atomic<foo,lock> a(0);  a *=  b; }
//v{ volatile atomic<foo,lock> a(0);  a /=  b; }
//v{ volatile atomic<foo,lock> a(0);  a %=  b; }
//v{ volatile atomic<foo,lock> a(0);  a <<= b; }
//v{ volatile atomic<foo,lock> a(0);  a >>= b; }
//v{ volatile atomic<foo,lock> a(0);  a &=  b; }
//v{ volatile atomic<foo,lock> a(0);  a |=  b; }
//v{ volatile atomic<foo,lock> a(0);  a ^=  b; }
//v{ volatile atomic<foo,lock> a(0);  ++a; }
//v{ volatile atomic<foo,lock> a(0);  a++; }
//v{ volatile atomic<foo,lock> a(0);  --a; }
//v{ volatile atomic<foo,lock> a(0);  a--; }

   // serial
//v{ volatile atomic<foo,serial> a(0);  a +=  b; }
//v{ volatile atomic<foo,serial> a(0);  a -=  b; }
//v{ volatile atomic<foo,serial> a(0);  a *=  b; }
//v{ volatile atomic<foo,serial> a(0);  a /=  b; }
//v{ volatile atomic<foo,serial> a(0);  a %=  b; }
//v{ volatile atomic<foo,serial> a(0);  a <<= b; }
//v{ volatile atomic<foo,serial> a(0);  a >>= b; }
//v{ volatile atomic<foo,serial> a(0);  a &=  b; }
//v{ volatile atomic<foo,serial> a(0);  a |=  b; }
//v{ volatile atomic<foo,serial> a(0);  a ^=  b; }
//v{ volatile atomic<foo,serial> a(0);  ++a; }
//v{ volatile atomic<foo,serial> a(0);  a++; }
//v{ volatile atomic<foo,serial> a(0);  --a; }
//v{ volatile atomic<foo,serial> a(0);  a--; }
}
