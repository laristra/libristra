
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
   for (int i = 0;  i <= 100;  ++i) {
      {
         T value = T(i);
         ristra::atomics::atomic<T,SCHEME> atom(value);
         assert(--value == --atom);
         atomics_print_var(value);
      } {
         T value = T(i);
         ristra::atomics::atomic<T,SCHEME> atom(value);
         assert(--value == atom.dec());
         atomics_print_var(value);
      } {
         T value = T(i);
         ristra::atomics::atomic<T,SCHEME> atom(value);
         assert(--value == ristra::atomics::dec(atom));
         atomics_print_var(value);
      } {
         T value = T(i);
         ristra::atomics::atomic<T,SCHEME> atom(value);
         assert(--value == atom.predec());
         atomics_print_var(value);
      } {
         T value = T(i);
         ristra::atomics::atomic<T,SCHEME> atom(value);
         assert(--value == ristra::atomics::predec(atom));
         atomics_print_var(value);
      }
   }
}

// -----------------------------------------------------------------------------
// main()
// -----------------------------------------------------------------------------

int main()
{
   fun<int, ristra::atomics::cpp        >();
   fun<int, ristra::atomics::kokkos     >();
   fun<int, ristra::atomics::strong     >();
   fun<int, ristra::atomics::strong::pun>();
   fun<int, ristra::atomics::weak       >();
   fun<int, ristra::atomics::weak::pun  >();
   fun<int, ristra::atomics::lock       >();
   fun<int, ristra::atomics::serial     >();

   fun<unsigned, ristra::atomics::cpp        >();
   fun<unsigned, ristra::atomics::kokkos     >();
   fun<unsigned, ristra::atomics::strong     >();
   fun<unsigned, ristra::atomics::strong::pun>();
   fun<unsigned, ristra::atomics::weak       >();
   fun<unsigned, ristra::atomics::weak::pun  >();
   fun<unsigned, ristra::atomics::lock       >();
   fun<unsigned, ristra::atomics::serial     >();

// fun<float, ristra::atomics::cpp        >();
// fun<float, ristra::atomics::kokkos     >();
   fun<float, ristra::atomics::strong     >();
   fun<float, ristra::atomics::strong::pun>();
   fun<float, ristra::atomics::weak       >();
   fun<float, ristra::atomics::weak::pun  >();
   fun<float, ristra::atomics::lock       >();
   fun<float, ristra::atomics::serial     >();

// fun<double, ristra::atomics::cpp        >();
   fun<double, ristra::atomics::kokkos     >();
   fun<double, ristra::atomics::strong     >();
   fun<double, ristra::atomics::strong::pun>();
   fun<double, ristra::atomics::weak       >();
   fun<double, ristra::atomics::weak::pun  >();
   fun<double, ristra::atomics::lock       >();
   fun<double, ristra::atomics::serial     >();
}
