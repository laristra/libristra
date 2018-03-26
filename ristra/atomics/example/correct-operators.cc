
#define ATOMICS_KOKKOS
#define ATOMICS_DEBUG
//#define ATOMICS_PRINT

#include "atomics.h"
#include <cassert>

using namespace ristra::atomics;



// -----------------------------------------------------------------------------
// fun()
// -----------------------------------------------------------------------------

template<class T>
void fun()
{
   const T c1 = 5;
   const T c2 = 7;

   atomic<T> a(0);

   // ++, --
   assert(T(a  ) == 0);
   assert(T(++a) == 1);
   assert(T(a++) == 1);
   assert(T(a  ) == 2);
   assert(T(--a) == 1);
   assert(T(a--) == 1);

   // preinc, postinc, predec, postdec
   assert(T(a  ) == 0);
   assert(T(a.preinc()) == 1);
   assert(T(a.postinc()) == 1);
   assert(T(a) == 2);
   assert(T(a.predec()) == 1);
   assert(T(a.postdec()) == 1);

   // inc, dec
   assert(T(a) == 0);
   assert(T(a.inc()) == 1);
   assert(T(a.dec()) == 0);

   // +=, *=, /=, -=
   assert(T(a) == 0);
   assert(T(a += c1) == c1);
   assert(T(a *= c2) == c1*c2);
   assert(T(a /= c2) == c1);
   assert(T(a -= c1) == 0);

   // add, mul, div, sub
   assert(T(a) == 0);
   assert(T(a.add(c1)) == c1);
   assert(T(a.mul(c2)) == c1*c2);
   assert(T(a.div(c2)) == c1);
   assert(T(a.sub(c1)) == 0);

   // %=, mod
   a = 13;
   assert(T(a %= 5) == 3);
   a = 13;
   assert(T(a.mod(4)) == 1);

   // <<=, >>=, lshift, rshift
   a = 3;
   assert(T(a <<= 1) == 6);
   assert(T(a >>= 1) == 3);
   assert(T(a.lshift(2)) == 12);
   assert(T(a.rshift(1)) == 6);

   // &=, |=, andeq, oreq
   a = 0b10110100;
   assert(T(a &= 0b10101010) == 0b10100000);
   assert(T(a |= 0b01010101) == 0b11110101);
   assert(T(a.andeq(0b01010101)) == 0b01010101);
   assert(T(a.oreq (0b10101010)) == 0b11111111);

   // ^=, xoreq
   a = 0b11110000;
   //    10101010
   //    01011010
   assert(T(a ^= 0b10101010) == 0b01011010);
   assert(T(a.xoreq(0b00001111)) == 0b01010101);
}



// -----------------------------------------------------------------------------
// main()
// -----------------------------------------------------------------------------

int main()
{
   fun<short>();
   fun<int>();
   fun<long>();
   fun<long long>();
}
