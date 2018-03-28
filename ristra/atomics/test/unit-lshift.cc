
#define ATOMICS_KOKKOS
#define ATOMICS_DEBUG
#define ATOMICS_PRINT

#include "atomics.h"
#include <cassert>
#include <iostream>

// -----------------------------------------------------------------------------
// fun()
// -----------------------------------------------------------------------------

template<class T, class SCHEME>
void fun()
{
   for (int i = 0;  i <= 10;  ++i) {
   for (int j = 0;  j <= 10;  ++j) {
      {
         T value = T(i);
         ristra::atomics::atomic<T,SCHEME> atom(value);
         assert((value <<= j) == (atom <<= j));
         atomics_print_var(value);
      } {
         T value = T(i);
         ristra::atomics::atomic<T,SCHEME> atom(value);
         assert((value <<= j) == (atom.lshift(j)));
         atomics_print_var(value);
      } {
         T value = T(i);
         ristra::atomics::atomic<T,SCHEME> atom(value);
         assert((value <<= j) == (ristra::atomics::lshift(atom,j)));
         atomics_print_var(value);
      }
   }
   }
}

// -----------------------------------------------------------------------------
// main()
// -----------------------------------------------------------------------------

int main()
{
// fun<int, ristra::atomics::cpp        >();
   fun<int, ristra::atomics::kokkos     >();
   fun<int, ristra::atomics::strong     >();
   fun<int, ristra::atomics::strong::pun>();
   fun<int, ristra::atomics::weak       >();
   fun<int, ristra::atomics::weak::pun  >();
   fun<int, ristra::atomics::lock       >();
   fun<int, ristra::atomics::serial     >();

// fun<unsigned, ristra::atomics::cpp        >();
   fun<unsigned, ristra::atomics::kokkos     >();
   fun<unsigned, ristra::atomics::strong     >();
   fun<unsigned, ristra::atomics::strong::pun>();
   fun<unsigned, ristra::atomics::weak       >();
   fun<unsigned, ristra::atomics::weak::pun  >();
   fun<unsigned, ristra::atomics::lock       >();
   fun<unsigned, ristra::atomics::serial     >();

   // no float or double <<=
}
