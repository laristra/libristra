
/*
In this file, we illustrate combinations of the following:

   - Data types:
        int
        unsigned long
        double
        int*
        std::complex<float>
        foo (a custom type; see foobar.h)

   - Atomicity schemes:
        cpp
        kokkos
        strong
        strong::pun
        weak
        weak::pun
        lock
        serial

   - Functions:
        add
        sub
        mul
        div
        mod
        lshift
        rshift
        andeq
        oreq
        xoreq
        min
        max
        inc
        preinc
        postinc
        dec
        predec
        postdec

   - Memory-order parameter(s):
        none
        sync
        success, failure

The point of this file is to illustrate every combination that works, and every
combination that doesn't work. The former are in working code, while the latter
are commented-out.

Each commented-out case - i.e., each case that doesn't work - is unavailable for
one or more of the following reasons:

   - C++ std::atomic<T> (used by the "cpp" scheme) doesn't support certain
     operations - in particular, *=, /=, %=, <<=, >>=, min, and max - even
     for integral T.

   - C++ std::atomic<T> has no ++ or -- that accepts a memory_order sync.

   - C++ std::atomic<T> has no operators that accept the success, failure
     memory_order combination. (The compare_exchange_*() functions accept
     those; but those functions are used by our various "strong" and "weak"
     [pun] schemes, not by our cpp scheme).

   - The kokkos, lock, and serial schemes don't accept any memory_order
     parameters (sync, or success and failure).

   - C++ std::atomic<T> has no operations for non-integral types (e.g, for
     floating-point, complex<>, or user-defined types).

   - In general, regardless of whatever atomicity scheme is stipulated,
     non-integral data types in the C++ language don't have modulo, left
     or right shift, or bitwise and, or, or xor.

   - Additionally, pointers in C++ don't have *= or /=.

   - Kokkos has no atomic operations for pointers (e.g. our int* case)
     or for complex<>.

   - C++ complex<> has no %=, <<=, >>=, &=, |=, ^=, min, max, ++, or --.

   - Neither Kokkos nor std::atomic<> (via cpp) knows anything about our
     custom "foo" class.

We think that this list covers all the reasons for something not working. :-)
Note, again, that a particular case may fail for multiple reasons.

At this time, if you try to use an invalid variant, the compiler may or may
not emit a particularly comprehensible error message. This is because our
functions - the ones that are called directly, below - generally pass their
arguments down through a series of lower-level functions, eventually reaching
a final destination (e.g. an actual += operator for some underlying data type,
or a member function of std::atomic<>) where the work is supposed to occur.
For the cases that don't work, a failure happens at some point in the process,
and this may mean a long, meandering series of error messages. We may be able
to improve this, perhaps by using SFINAE constructs in higher-level functions
that call the lower-level functions. At the moment, we don't do this.
*/

//#define ATOMICS_KOKKOS
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

   int i(0), j(0); // for the int* cases
   const cmplx c(1.2,3.4);
   const bar b(2); // for the foo cases

   const std::memory_order sync    = std::memory_order_seq_cst;
   const std::memory_order success = std::memory_order_seq_cst;
   const std::memory_order failure = std::memory_order_seq_cst;



   // --------------------------------------------------------------------------
   // non-volatile
   // --------------------------------------------------------------------------

   // ------------------------
   // int
   // ------------------------

   { atomic<int,cpp> a(0);  add    (a,2); }
   { atomic<int,cpp> a(0);  sub    (a,2); }
// { atomic<int,cpp> a(0);  mul    (a,2); }
// { atomic<int,cpp> a(0);  div    (a,2); }
// { atomic<int,cpp> a(0);  mod    (a,2); }
// { atomic<int,cpp> a(0);  lshift (a,2); }
// { atomic<int,cpp> a(0);  rshift (a,2); }
   { atomic<int,cpp> a(0);  andeq  (a,2); }
   { atomic<int,cpp> a(0);  oreq   (a,2); }
   { atomic<int,cpp> a(0);  xoreq  (a,2); }
// { atomic<int,cpp> a(0);  min    (a,2); }
// { atomic<int,cpp> a(0);  max    (a,2); }
   { atomic<int,cpp> a(0);  inc    (a); }
   { atomic<int,cpp> a(0);  preinc (a); }
   { atomic<int,cpp> a(0);  postinc(a); }
   { atomic<int,cpp> a(0);  dec    (a); }
   { atomic<int,cpp> a(0);  predec (a); }
   { atomic<int,cpp> a(0);  postdec(a); }
   { atomic<int,cpp> a(0);  add    (a,2,sync); }
   { atomic<int,cpp> a(0);  sub    (a,2,sync); }
// { atomic<int,cpp> a(0);  mul    (a,2,sync); }
// { atomic<int,cpp> a(0);  div    (a,2,sync); }
// { atomic<int,cpp> a(0);  mod    (a,2,sync); }
// { atomic<int,cpp> a(0);  lshift (a,2,sync); }
// { atomic<int,cpp> a(0);  rshift (a,2,sync); }
   { atomic<int,cpp> a(0);  andeq  (a,2,sync); }
   { atomic<int,cpp> a(0);  oreq   (a,2,sync); }
   { atomic<int,cpp> a(0);  xoreq  (a,2,sync); }
// { atomic<int,cpp> a(0);  min    (a,2,sync); }
// { atomic<int,cpp> a(0);  max    (a,2,sync); }
// { atomic<int,cpp> a(0);  inc    (a,  sync); }
// { atomic<int,cpp> a(0);  preinc (a,  sync); }
// { atomic<int,cpp> a(0);  postinc(a,  sync); }
// { atomic<int,cpp> a(0);  dec    (a,  sync); }
// { atomic<int,cpp> a(0);  predec (a,  sync); }
// { atomic<int,cpp> a(0);  postdec(a,  sync); }
// { atomic<int,cpp> a(0);  add    (a,2,success,failure); }
// { atomic<int,cpp> a(0);  sub    (a,2,success,failure); }
// { atomic<int,cpp> a(0);  mul    (a,2,success,failure); }
// { atomic<int,cpp> a(0);  div    (a,2,success,failure); }
// { atomic<int,cpp> a(0);  mod    (a,2,success,failure); }
// { atomic<int,cpp> a(0);  lshift (a,2,success,failure); }
// { atomic<int,cpp> a(0);  rshift (a,2,success,failure); }
// { atomic<int,cpp> a(0);  andeq  (a,2,success,failure); }
// { atomic<int,cpp> a(0);  oreq   (a,2,success,failure); }
// { atomic<int,cpp> a(0);  xoreq  (a,2,success,failure); }
// { atomic<int,cpp> a(0);  min    (a,2,success,failure); }
// { atomic<int,cpp> a(0);  max    (a,2,success,failure); }
// { atomic<int,cpp> a(0);  inc    (a,  success,failure); }
// { atomic<int,cpp> a(0);  preinc (a,  success,failure); }
// { atomic<int,cpp> a(0);  postinc(a,  success,failure); }
// { atomic<int,cpp> a(0);  dec    (a,  success,failure); }
// { atomic<int,cpp> a(0);  predec (a,  success,failure); }
// { atomic<int,cpp> a(0);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { atomic<int,kokkos> a(0);  add    (a,2); }
   { atomic<int,kokkos> a(0);  sub    (a,2); }
   { atomic<int,kokkos> a(0);  mul    (a,2); }
   { atomic<int,kokkos> a(0);  div    (a,2); }
   { atomic<int,kokkos> a(0);  mod    (a,2); }
   { atomic<int,kokkos> a(0);  lshift (a,2); }
   { atomic<int,kokkos> a(0);  rshift (a,2); }
   { atomic<int,kokkos> a(0);  andeq  (a,2); }
   { atomic<int,kokkos> a(0);  oreq   (a,2); }
   { atomic<int,kokkos> a(0);  xoreq  (a,2); }
   { atomic<int,kokkos> a(0);  min    (a,2); }
   { atomic<int,kokkos> a(0);  max    (a,2); }
   { atomic<int,kokkos> a(0);  inc    (a); }
   { atomic<int,kokkos> a(0);  preinc (a); }
   { atomic<int,kokkos> a(0);  postinc(a); }
   { atomic<int,kokkos> a(0);  dec    (a); }
   { atomic<int,kokkos> a(0);  predec (a); }
   { atomic<int,kokkos> a(0);  postdec(a); }
// { atomic<int,kokkos> a(0);  add    (a,2,sync); }
// { atomic<int,kokkos> a(0);  sub    (a,2,sync); }
// { atomic<int,kokkos> a(0);  mul    (a,2,sync); }
// { atomic<int,kokkos> a(0);  div    (a,2,sync); }
// { atomic<int,kokkos> a(0);  mod    (a,2,sync); }
// { atomic<int,kokkos> a(0);  lshift (a,2,sync); }
// { atomic<int,kokkos> a(0);  rshift (a,2,sync); }
// { atomic<int,kokkos> a(0);  andeq  (a,2,sync); }
// { atomic<int,kokkos> a(0);  oreq   (a,2,sync); }
// { atomic<int,kokkos> a(0);  xoreq  (a,2,sync); }
// { atomic<int,kokkos> a(0);  min    (a,2,sync); }
// { atomic<int,kokkos> a(0);  max    (a,2,sync); }
// { atomic<int,kokkos> a(0);  inc    (a,  sync); }
// { atomic<int,kokkos> a(0);  preinc (a,  sync); }
// { atomic<int,kokkos> a(0);  postinc(a,  sync); }
// { atomic<int,kokkos> a(0);  dec    (a,  sync); }
// { atomic<int,kokkos> a(0);  predec (a,  sync); }
// { atomic<int,kokkos> a(0);  postdec(a,  sync); }
// { atomic<int,kokkos> a(0);  add    (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  sub    (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  mul    (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  div    (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  mod    (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  lshift (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  rshift (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  andeq  (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  oreq   (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  xoreq  (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  min    (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  max    (a,2,success,failure); }
// { atomic<int,kokkos> a(0);  inc    (a,  success,failure); }
// { atomic<int,kokkos> a(0);  preinc (a,  success,failure); }
// { atomic<int,kokkos> a(0);  postinc(a,  success,failure); }
// { atomic<int,kokkos> a(0);  dec    (a,  success,failure); }
// { atomic<int,kokkos> a(0);  predec (a,  success,failure); }
// { atomic<int,kokkos> a(0);  postdec(a,  success,failure); }
#endif

   { atomic<int,strong> a(0);  add    (a,2); }
   { atomic<int,strong> a(0);  sub    (a,2); }
   { atomic<int,strong> a(0);  mul    (a,2); }
   { atomic<int,strong> a(0);  div    (a,2); }
   { atomic<int,strong> a(0);  mod    (a,2); }
   { atomic<int,strong> a(0);  lshift (a,2); }
   { atomic<int,strong> a(0);  rshift (a,2); }
   { atomic<int,strong> a(0);  andeq  (a,2); }
   { atomic<int,strong> a(0);  oreq   (a,2); }
   { atomic<int,strong> a(0);  xoreq  (a,2); }
   { atomic<int,strong> a(0);  min    (a,2); }
   { atomic<int,strong> a(0);  max    (a,2); }
   { atomic<int,strong> a(0);  inc    (a); }
   { atomic<int,strong> a(0);  preinc (a); }
   { atomic<int,strong> a(0);  postinc(a); }
   { atomic<int,strong> a(0);  dec    (a); }
   { atomic<int,strong> a(0);  predec (a); }
   { atomic<int,strong> a(0);  postdec(a); }
   { atomic<int,strong> a(0);  add    (a,2,sync); }
   { atomic<int,strong> a(0);  sub    (a,2,sync); }
   { atomic<int,strong> a(0);  mul    (a,2,sync); }
   { atomic<int,strong> a(0);  div    (a,2,sync); }
   { atomic<int,strong> a(0);  mod    (a,2,sync); }
   { atomic<int,strong> a(0);  lshift (a,2,sync); }
   { atomic<int,strong> a(0);  rshift (a,2,sync); }
   { atomic<int,strong> a(0);  andeq  (a,2,sync); }
   { atomic<int,strong> a(0);  oreq   (a,2,sync); }
   { atomic<int,strong> a(0);  xoreq  (a,2,sync); }
   { atomic<int,strong> a(0);  min    (a,2,sync); }
   { atomic<int,strong> a(0);  max    (a,2,sync); }
   { atomic<int,strong> a(0);  inc    (a,  sync); }
   { atomic<int,strong> a(0);  preinc (a,  sync); }
   { atomic<int,strong> a(0);  postinc(a,  sync); }
   { atomic<int,strong> a(0);  dec    (a,  sync); }
   { atomic<int,strong> a(0);  predec (a,  sync); }
   { atomic<int,strong> a(0);  postdec(a,  sync); }
   { atomic<int,strong> a(0);  add    (a,2,success,failure); }
   { atomic<int,strong> a(0);  sub    (a,2,success,failure); }
   { atomic<int,strong> a(0);  mul    (a,2,success,failure); }
   { atomic<int,strong> a(0);  div    (a,2,success,failure); }
   { atomic<int,strong> a(0);  mod    (a,2,success,failure); }
   { atomic<int,strong> a(0);  lshift (a,2,success,failure); }
   { atomic<int,strong> a(0);  rshift (a,2,success,failure); }
   { atomic<int,strong> a(0);  andeq  (a,2,success,failure); }
   { atomic<int,strong> a(0);  oreq   (a,2,success,failure); }
   { atomic<int,strong> a(0);  xoreq  (a,2,success,failure); }
   { atomic<int,strong> a(0);  min    (a,2,success,failure); }
   { atomic<int,strong> a(0);  max    (a,2,success,failure); }
   { atomic<int,strong> a(0);  inc    (a,  success,failure); }
   { atomic<int,strong> a(0);  preinc (a,  success,failure); }
   { atomic<int,strong> a(0);  postinc(a,  success,failure); }
   { atomic<int,strong> a(0);  dec    (a,  success,failure); }
   { atomic<int,strong> a(0);  predec (a,  success,failure); }
   { atomic<int,strong> a(0);  postdec(a,  success,failure); }

   { atomic<int,strong::pun> a(0);  add    (a,2); }
   { atomic<int,strong::pun> a(0);  sub    (a,2); }
   { atomic<int,strong::pun> a(0);  mul    (a,2); }
   { atomic<int,strong::pun> a(0);  div    (a,2); }
   { atomic<int,strong::pun> a(0);  mod    (a,2); }
   { atomic<int,strong::pun> a(0);  lshift (a,2); }
   { atomic<int,strong::pun> a(0);  rshift (a,2); }
   { atomic<int,strong::pun> a(0);  andeq  (a,2); }
   { atomic<int,strong::pun> a(0);  oreq   (a,2); }
   { atomic<int,strong::pun> a(0);  xoreq  (a,2); }
   { atomic<int,strong::pun> a(0);  min    (a,2); }
   { atomic<int,strong::pun> a(0);  max    (a,2); }
   { atomic<int,strong::pun> a(0);  inc    (a); }
   { atomic<int,strong::pun> a(0);  preinc (a); }
   { atomic<int,strong::pun> a(0);  postinc(a); }
   { atomic<int,strong::pun> a(0);  dec    (a); }
   { atomic<int,strong::pun> a(0);  predec (a); }
   { atomic<int,strong::pun> a(0);  postdec(a); }
   { atomic<int,strong::pun> a(0);  add    (a,2,sync); }
   { atomic<int,strong::pun> a(0);  sub    (a,2,sync); }
   { atomic<int,strong::pun> a(0);  mul    (a,2,sync); }
   { atomic<int,strong::pun> a(0);  div    (a,2,sync); }
   { atomic<int,strong::pun> a(0);  mod    (a,2,sync); }
   { atomic<int,strong::pun> a(0);  lshift (a,2,sync); }
   { atomic<int,strong::pun> a(0);  rshift (a,2,sync); }
   { atomic<int,strong::pun> a(0);  andeq  (a,2,sync); }
   { atomic<int,strong::pun> a(0);  oreq   (a,2,sync); }
   { atomic<int,strong::pun> a(0);  xoreq  (a,2,sync); }
   { atomic<int,strong::pun> a(0);  min    (a,2,sync); }
   { atomic<int,strong::pun> a(0);  max    (a,2,sync); }
   { atomic<int,strong::pun> a(0);  inc    (a,  sync); }
   { atomic<int,strong::pun> a(0);  preinc (a,  sync); }
   { atomic<int,strong::pun> a(0);  postinc(a,  sync); }
   { atomic<int,strong::pun> a(0);  dec    (a,  sync); }
   { atomic<int,strong::pun> a(0);  predec (a,  sync); }
   { atomic<int,strong::pun> a(0);  postdec(a,  sync); }
   { atomic<int,strong::pun> a(0);  add    (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  sub    (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  mul    (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  div    (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  mod    (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  lshift (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  rshift (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  andeq  (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  oreq   (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  xoreq  (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  min    (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  max    (a,2,success,failure); }
   { atomic<int,strong::pun> a(0);  inc    (a,  success,failure); }
   { atomic<int,strong::pun> a(0);  preinc (a,  success,failure); }
   { atomic<int,strong::pun> a(0);  postinc(a,  success,failure); }
   { atomic<int,strong::pun> a(0);  dec    (a,  success,failure); }
   { atomic<int,strong::pun> a(0);  predec (a,  success,failure); }
   { atomic<int,strong::pun> a(0);  postdec(a,  success,failure); }

   { atomic<int,weak> a(0);  add    (a,2); }
   { atomic<int,weak> a(0);  sub    (a,2); }
   { atomic<int,weak> a(0);  mul    (a,2); }
   { atomic<int,weak> a(0);  div    (a,2); }
   { atomic<int,weak> a(0);  mod    (a,2); }
   { atomic<int,weak> a(0);  lshift (a,2); }
   { atomic<int,weak> a(0);  rshift (a,2); }
   { atomic<int,weak> a(0);  andeq  (a,2); }
   { atomic<int,weak> a(0);  oreq   (a,2); }
   { atomic<int,weak> a(0);  xoreq  (a,2); }
   { atomic<int,weak> a(0);  min    (a,2); }
   { atomic<int,weak> a(0);  max    (a,2); }
   { atomic<int,weak> a(0);  inc    (a); }
   { atomic<int,weak> a(0);  preinc (a); }
   { atomic<int,weak> a(0);  postinc(a); }
   { atomic<int,weak> a(0);  dec    (a); }
   { atomic<int,weak> a(0);  predec (a); }
   { atomic<int,weak> a(0);  postdec(a); }
   { atomic<int,weak> a(0);  add    (a,2,sync); }
   { atomic<int,weak> a(0);  sub    (a,2,sync); }
   { atomic<int,weak> a(0);  mul    (a,2,sync); }
   { atomic<int,weak> a(0);  div    (a,2,sync); }
   { atomic<int,weak> a(0);  mod    (a,2,sync); }
   { atomic<int,weak> a(0);  lshift (a,2,sync); }
   { atomic<int,weak> a(0);  rshift (a,2,sync); }
   { atomic<int,weak> a(0);  andeq  (a,2,sync); }
   { atomic<int,weak> a(0);  oreq   (a,2,sync); }
   { atomic<int,weak> a(0);  xoreq  (a,2,sync); }
   { atomic<int,weak> a(0);  min    (a,2,sync); }
   { atomic<int,weak> a(0);  max    (a,2,sync); }
   { atomic<int,weak> a(0);  inc    (a,  sync); }
   { atomic<int,weak> a(0);  preinc (a,  sync); }
   { atomic<int,weak> a(0);  postinc(a,  sync); }
   { atomic<int,weak> a(0);  dec    (a,  sync); }
   { atomic<int,weak> a(0);  predec (a,  sync); }
   { atomic<int,weak> a(0);  postdec(a,  sync); }
   { atomic<int,weak> a(0);  add    (a,2,success,failure); }
   { atomic<int,weak> a(0);  sub    (a,2,success,failure); }
   { atomic<int,weak> a(0);  mul    (a,2,success,failure); }
   { atomic<int,weak> a(0);  div    (a,2,success,failure); }
   { atomic<int,weak> a(0);  mod    (a,2,success,failure); }
   { atomic<int,weak> a(0);  lshift (a,2,success,failure); }
   { atomic<int,weak> a(0);  rshift (a,2,success,failure); }
   { atomic<int,weak> a(0);  andeq  (a,2,success,failure); }
   { atomic<int,weak> a(0);  oreq   (a,2,success,failure); }
   { atomic<int,weak> a(0);  xoreq  (a,2,success,failure); }
   { atomic<int,weak> a(0);  min    (a,2,success,failure); }
   { atomic<int,weak> a(0);  max    (a,2,success,failure); }
   { atomic<int,weak> a(0);  inc    (a,  success,failure); }
   { atomic<int,weak> a(0);  preinc (a,  success,failure); }
   { atomic<int,weak> a(0);  postinc(a,  success,failure); }
   { atomic<int,weak> a(0);  dec    (a,  success,failure); }
   { atomic<int,weak> a(0);  predec (a,  success,failure); }
   { atomic<int,weak> a(0);  postdec(a,  success,failure); }

   { atomic<int,weak::pun> a(0);  add    (a,2); }
   { atomic<int,weak::pun> a(0);  sub    (a,2); }
   { atomic<int,weak::pun> a(0);  mul    (a,2); }
   { atomic<int,weak::pun> a(0);  div    (a,2); }
   { atomic<int,weak::pun> a(0);  mod    (a,2); }
   { atomic<int,weak::pun> a(0);  lshift (a,2); }
   { atomic<int,weak::pun> a(0);  rshift (a,2); }
   { atomic<int,weak::pun> a(0);  andeq  (a,2); }
   { atomic<int,weak::pun> a(0);  oreq   (a,2); }
   { atomic<int,weak::pun> a(0);  xoreq  (a,2); }
   { atomic<int,weak::pun> a(0);  min    (a,2); }
   { atomic<int,weak::pun> a(0);  max    (a,2); }
   { atomic<int,weak::pun> a(0);  inc    (a); }
   { atomic<int,weak::pun> a(0);  preinc (a); }
   { atomic<int,weak::pun> a(0);  postinc(a); }
   { atomic<int,weak::pun> a(0);  dec    (a); }
   { atomic<int,weak::pun> a(0);  predec (a); }
   { atomic<int,weak::pun> a(0);  postdec(a); }
   { atomic<int,weak::pun> a(0);  add    (a,2,sync); }
   { atomic<int,weak::pun> a(0);  sub    (a,2,sync); }
   { atomic<int,weak::pun> a(0);  mul    (a,2,sync); }
   { atomic<int,weak::pun> a(0);  div    (a,2,sync); }
   { atomic<int,weak::pun> a(0);  mod    (a,2,sync); }
   { atomic<int,weak::pun> a(0);  lshift (a,2,sync); }
   { atomic<int,weak::pun> a(0);  rshift (a,2,sync); }
   { atomic<int,weak::pun> a(0);  andeq  (a,2,sync); }
   { atomic<int,weak::pun> a(0);  oreq   (a,2,sync); }
   { atomic<int,weak::pun> a(0);  xoreq  (a,2,sync); }
   { atomic<int,weak::pun> a(0);  min    (a,2,sync); }
   { atomic<int,weak::pun> a(0);  max    (a,2,sync); }
   { atomic<int,weak::pun> a(0);  inc    (a,  sync); }
   { atomic<int,weak::pun> a(0);  preinc (a,  sync); }
   { atomic<int,weak::pun> a(0);  postinc(a,  sync); }
   { atomic<int,weak::pun> a(0);  dec    (a,  sync); }
   { atomic<int,weak::pun> a(0);  predec (a,  sync); }
   { atomic<int,weak::pun> a(0);  postdec(a,  sync); }
   { atomic<int,weak::pun> a(0);  add    (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  sub    (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  mul    (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  div    (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  mod    (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  lshift (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  rshift (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  andeq  (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  oreq   (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  xoreq  (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  min    (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  max    (a,2,success,failure); }
   { atomic<int,weak::pun> a(0);  inc    (a,  success,failure); }
   { atomic<int,weak::pun> a(0);  preinc (a,  success,failure); }
   { atomic<int,weak::pun> a(0);  postinc(a,  success,failure); }
   { atomic<int,weak::pun> a(0);  dec    (a,  success,failure); }
   { atomic<int,weak::pun> a(0);  predec (a,  success,failure); }
   { atomic<int,weak::pun> a(0);  postdec(a,  success,failure); }

   { atomic<int,lock> a(0);  add    (a,2); }
   { atomic<int,lock> a(0);  sub    (a,2); }
   { atomic<int,lock> a(0);  mul    (a,2); }
   { atomic<int,lock> a(0);  div    (a,2); }
   { atomic<int,lock> a(0);  mod    (a,2); }
   { atomic<int,lock> a(0);  lshift (a,2); }
   { atomic<int,lock> a(0);  rshift (a,2); }
   { atomic<int,lock> a(0);  andeq  (a,2); }
   { atomic<int,lock> a(0);  oreq   (a,2); }
   { atomic<int,lock> a(0);  xoreq  (a,2); }
   { atomic<int,lock> a(0);  min    (a,2); }
   { atomic<int,lock> a(0);  max    (a,2); }
   { atomic<int,lock> a(0);  inc    (a); }
   { atomic<int,lock> a(0);  preinc (a); }
   { atomic<int,lock> a(0);  postinc(a); }
   { atomic<int,lock> a(0);  dec    (a); }
   { atomic<int,lock> a(0);  predec (a); }
   { atomic<int,lock> a(0);  postdec(a); }
// { atomic<int,lock> a(0);  add    (a,2,sync); }
// { atomic<int,lock> a(0);  sub    (a,2,sync); }
// { atomic<int,lock> a(0);  mul    (a,2,sync); }
// { atomic<int,lock> a(0);  div    (a,2,sync); }
// { atomic<int,lock> a(0);  mod    (a,2,sync); }
// { atomic<int,lock> a(0);  lshift (a,2,sync); }
// { atomic<int,lock> a(0);  rshift (a,2,sync); }
// { atomic<int,lock> a(0);  andeq  (a,2,sync); }
// { atomic<int,lock> a(0);  oreq   (a,2,sync); }
// { atomic<int,lock> a(0);  xoreq  (a,2,sync); }
// { atomic<int,lock> a(0);  min    (a,2,sync); }
// { atomic<int,lock> a(0);  max    (a,2,sync); }
// { atomic<int,lock> a(0);  inc    (a,  sync); }
// { atomic<int,lock> a(0);  preinc (a,  sync); }
// { atomic<int,lock> a(0);  postinc(a,  sync); }
// { atomic<int,lock> a(0);  dec    (a,  sync); }
// { atomic<int,lock> a(0);  predec (a,  sync); }
// { atomic<int,lock> a(0);  postdec(a,  sync); }
// { atomic<int,lock> a(0);  add    (a,2,success,failure); }
// { atomic<int,lock> a(0);  sub    (a,2,success,failure); }
// { atomic<int,lock> a(0);  mul    (a,2,success,failure); }
// { atomic<int,lock> a(0);  div    (a,2,success,failure); }
// { atomic<int,lock> a(0);  mod    (a,2,success,failure); }
// { atomic<int,lock> a(0);  lshift (a,2,success,failure); }
// { atomic<int,lock> a(0);  rshift (a,2,success,failure); }
// { atomic<int,lock> a(0);  andeq  (a,2,success,failure); }
// { atomic<int,lock> a(0);  oreq   (a,2,success,failure); }
// { atomic<int,lock> a(0);  xoreq  (a,2,success,failure); }
// { atomic<int,lock> a(0);  min    (a,2,success,failure); }
// { atomic<int,lock> a(0);  max    (a,2,success,failure); }
// { atomic<int,lock> a(0);  inc    (a,  success,failure); }
// { atomic<int,lock> a(0);  preinc (a,  success,failure); }
// { atomic<int,lock> a(0);  postinc(a,  success,failure); }
// { atomic<int,lock> a(0);  dec    (a,  success,failure); }
// { atomic<int,lock> a(0);  predec (a,  success,failure); }
// { atomic<int,lock> a(0);  postdec(a,  success,failure); }

   { atomic<int,serial> a(0);  add    (a,2); }
   { atomic<int,serial> a(0);  sub    (a,2); }
   { atomic<int,serial> a(0);  mul    (a,2); }
   { atomic<int,serial> a(0);  div    (a,2); }
   { atomic<int,serial> a(0);  mod    (a,2); }
   { atomic<int,serial> a(0);  lshift (a,2); }
   { atomic<int,serial> a(0);  rshift (a,2); }
   { atomic<int,serial> a(0);  andeq  (a,2); }
   { atomic<int,serial> a(0);  oreq   (a,2); }
   { atomic<int,serial> a(0);  xoreq  (a,2); }
   { atomic<int,serial> a(0);  min    (a,2); }
   { atomic<int,serial> a(0);  max    (a,2); }
   { atomic<int,serial> a(0);  inc    (a); }
   { atomic<int,serial> a(0);  preinc (a); }
   { atomic<int,serial> a(0);  postinc(a); }
   { atomic<int,serial> a(0);  dec    (a); }
   { atomic<int,serial> a(0);  predec (a); }
   { atomic<int,serial> a(0);  postdec(a); }
// { atomic<int,serial> a(0);  add    (a,2,sync); }
// { atomic<int,serial> a(0);  sub    (a,2,sync); }
// { atomic<int,serial> a(0);  mul    (a,2,sync); }
// { atomic<int,serial> a(0);  div    (a,2,sync); }
// { atomic<int,serial> a(0);  mod    (a,2,sync); }
// { atomic<int,serial> a(0);  lshift (a,2,sync); }
// { atomic<int,serial> a(0);  rshift (a,2,sync); }
// { atomic<int,serial> a(0);  andeq  (a,2,sync); }
// { atomic<int,serial> a(0);  oreq   (a,2,sync); }
// { atomic<int,serial> a(0);  xoreq  (a,2,sync); }
// { atomic<int,serial> a(0);  min    (a,2,sync); }
// { atomic<int,serial> a(0);  max    (a,2,sync); }
// { atomic<int,serial> a(0);  inc    (a,  sync); }
// { atomic<int,serial> a(0);  preinc (a,  sync); }
// { atomic<int,serial> a(0);  postinc(a,  sync); }
// { atomic<int,serial> a(0);  dec    (a,  sync); }
// { atomic<int,serial> a(0);  predec (a,  sync); }
// { atomic<int,serial> a(0);  postdec(a,  sync); }
// { atomic<int,serial> a(0);  add    (a,2,success,failure); }
// { atomic<int,serial> a(0);  sub    (a,2,success,failure); }
// { atomic<int,serial> a(0);  mul    (a,2,success,failure); }
// { atomic<int,serial> a(0);  div    (a,2,success,failure); }
// { atomic<int,serial> a(0);  mod    (a,2,success,failure); }
// { atomic<int,serial> a(0);  lshift (a,2,success,failure); }
// { atomic<int,serial> a(0);  rshift (a,2,success,failure); }
// { atomic<int,serial> a(0);  andeq  (a,2,success,failure); }
// { atomic<int,serial> a(0);  oreq   (a,2,success,failure); }
// { atomic<int,serial> a(0);  xoreq  (a,2,success,failure); }
// { atomic<int,serial> a(0);  min    (a,2,success,failure); }
// { atomic<int,serial> a(0);  max    (a,2,success,failure); }
// { atomic<int,serial> a(0);  inc    (a,  success,failure); }
// { atomic<int,serial> a(0);  preinc (a,  success,failure); }
// { atomic<int,serial> a(0);  postinc(a,  success,failure); }
// { atomic<int,serial> a(0);  dec    (a,  success,failure); }
// { atomic<int,serial> a(0);  predec (a,  success,failure); }
// { atomic<int,serial> a(0);  postdec(a,  success,failure); }



   // ------------------------
   // ulong
   // ------------------------

   { atomic<ulong,cpp> a(0);  add    (a,2); }
   { atomic<ulong,cpp> a(0);  sub    (a,2); }
// { atomic<ulong,cpp> a(0);  mul    (a,2); }
// { atomic<ulong,cpp> a(0);  div    (a,2); }
// { atomic<ulong,cpp> a(0);  mod    (a,2); }
// { atomic<ulong,cpp> a(0);  lshift (a,2); }
// { atomic<ulong,cpp> a(0);  rshift (a,2); }
   { atomic<ulong,cpp> a(0);  andeq  (a,2); }
   { atomic<ulong,cpp> a(0);  oreq   (a,2); }
   { atomic<ulong,cpp> a(0);  xoreq  (a,2); }
// { atomic<ulong,cpp> a(0);  min    (a,2); }
// { atomic<ulong,cpp> a(0);  max    (a,2); }
   { atomic<ulong,cpp> a(0);  inc    (a); }
   { atomic<ulong,cpp> a(0);  preinc (a); }
   { atomic<ulong,cpp> a(0);  postinc(a); }
   { atomic<ulong,cpp> a(0);  dec    (a); }
   { atomic<ulong,cpp> a(0);  predec (a); }
   { atomic<ulong,cpp> a(0);  postdec(a); }
   { atomic<ulong,cpp> a(0);  add    (a,2,sync); }
   { atomic<ulong,cpp> a(0);  sub    (a,2,sync); }
// { atomic<ulong,cpp> a(0);  mul    (a,2,sync); }
// { atomic<ulong,cpp> a(0);  div    (a,2,sync); }
// { atomic<ulong,cpp> a(0);  mod    (a,2,sync); }
// { atomic<ulong,cpp> a(0);  lshift (a,2,sync); }
// { atomic<ulong,cpp> a(0);  rshift (a,2,sync); }
   { atomic<ulong,cpp> a(0);  andeq  (a,2,sync); }
   { atomic<ulong,cpp> a(0);  oreq   (a,2,sync); }
   { atomic<ulong,cpp> a(0);  xoreq  (a,2,sync); }
// { atomic<ulong,cpp> a(0);  min    (a,2,sync); }
// { atomic<ulong,cpp> a(0);  max    (a,2,sync); }
// { atomic<ulong,cpp> a(0);  inc    (a,  sync); }
// { atomic<ulong,cpp> a(0);  preinc (a,  sync); }
// { atomic<ulong,cpp> a(0);  postinc(a,  sync); }
// { atomic<ulong,cpp> a(0);  dec    (a,  sync); }
// { atomic<ulong,cpp> a(0);  predec (a,  sync); }
// { atomic<ulong,cpp> a(0);  postdec(a,  sync); }
// { atomic<ulong,cpp> a(0);  add    (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  sub    (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  mul    (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  div    (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  mod    (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  lshift (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  rshift (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  andeq  (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  oreq   (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  xoreq  (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  min    (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  max    (a,2,success,failure); }
// { atomic<ulong,cpp> a(0);  inc    (a,  success,failure); }
// { atomic<ulong,cpp> a(0);  preinc (a,  success,failure); }
// { atomic<ulong,cpp> a(0);  postinc(a,  success,failure); }
// { atomic<ulong,cpp> a(0);  dec    (a,  success,failure); }
// { atomic<ulong,cpp> a(0);  predec (a,  success,failure); }
// { atomic<ulong,cpp> a(0);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { atomic<ulong,kokkos> a(0);  add    (a,2); }
   { atomic<ulong,kokkos> a(0);  sub    (a,2); }
   { atomic<ulong,kokkos> a(0);  mul    (a,2); }
   { atomic<ulong,kokkos> a(0);  div    (a,2); }
   { atomic<ulong,kokkos> a(0);  mod    (a,2); }
   { atomic<ulong,kokkos> a(0);  lshift (a,2); }
   { atomic<ulong,kokkos> a(0);  rshift (a,2); }
   { atomic<ulong,kokkos> a(0);  andeq  (a,2); }
   { atomic<ulong,kokkos> a(0);  oreq   (a,2); }
   { atomic<ulong,kokkos> a(0);  xoreq  (a,2); }
   { atomic<ulong,kokkos> a(0);  min    (a,2); }
   { atomic<ulong,kokkos> a(0);  max    (a,2); }
   { atomic<ulong,kokkos> a(0);  inc    (a); }
   { atomic<ulong,kokkos> a(0);  preinc (a); }
   { atomic<ulong,kokkos> a(0);  postinc(a); }
   { atomic<ulong,kokkos> a(0);  dec    (a); }
   { atomic<ulong,kokkos> a(0);  predec (a); }
   { atomic<ulong,kokkos> a(0);  postdec(a); }
// { atomic<ulong,kokkos> a(0);  add    (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  sub    (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  mul    (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  div    (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  mod    (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  lshift (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  rshift (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  andeq  (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  oreq   (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  xoreq  (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  min    (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  max    (a,2,sync); }
// { atomic<ulong,kokkos> a(0);  inc    (a,  sync); }
// { atomic<ulong,kokkos> a(0);  preinc (a,  sync); }
// { atomic<ulong,kokkos> a(0);  postinc(a,  sync); }
// { atomic<ulong,kokkos> a(0);  dec    (a,  sync); }
// { atomic<ulong,kokkos> a(0);  predec (a,  sync); }
// { atomic<ulong,kokkos> a(0);  postdec(a,  sync); }
// { atomic<ulong,kokkos> a(0);  add    (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  sub    (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  mul    (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  div    (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  mod    (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  lshift (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  rshift (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  andeq  (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  oreq   (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  xoreq  (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  min    (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  max    (a,2,success,failure); }
// { atomic<ulong,kokkos> a(0);  inc    (a,  success,failure); }
// { atomic<ulong,kokkos> a(0);  preinc (a,  success,failure); }
// { atomic<ulong,kokkos> a(0);  postinc(a,  success,failure); }
// { atomic<ulong,kokkos> a(0);  dec    (a,  success,failure); }
// { atomic<ulong,kokkos> a(0);  predec (a,  success,failure); }
// { atomic<ulong,kokkos> a(0);  postdec(a,  success,failure); }
#endif

   { atomic<ulong,strong> a(0);  add    (a,2); }
   { atomic<ulong,strong> a(0);  sub    (a,2); }
   { atomic<ulong,strong> a(0);  mul    (a,2); }
   { atomic<ulong,strong> a(0);  div    (a,2); }
   { atomic<ulong,strong> a(0);  mod    (a,2); }
   { atomic<ulong,strong> a(0);  lshift (a,2); }
   { atomic<ulong,strong> a(0);  rshift (a,2); }
   { atomic<ulong,strong> a(0);  andeq  (a,2); }
   { atomic<ulong,strong> a(0);  oreq   (a,2); }
   { atomic<ulong,strong> a(0);  xoreq  (a,2); }
   { atomic<ulong,strong> a(0);  min    (a,2); }
   { atomic<ulong,strong> a(0);  max    (a,2); }
   { atomic<ulong,strong> a(0);  inc    (a); }
   { atomic<ulong,strong> a(0);  preinc (a); }
   { atomic<ulong,strong> a(0);  postinc(a); }
   { atomic<ulong,strong> a(0);  dec    (a); }
   { atomic<ulong,strong> a(0);  predec (a); }
   { atomic<ulong,strong> a(0);  postdec(a); }
   { atomic<ulong,strong> a(0);  add    (a,2,sync); }
   { atomic<ulong,strong> a(0);  sub    (a,2,sync); }
   { atomic<ulong,strong> a(0);  mul    (a,2,sync); }
   { atomic<ulong,strong> a(0);  div    (a,2,sync); }
   { atomic<ulong,strong> a(0);  mod    (a,2,sync); }
   { atomic<ulong,strong> a(0);  lshift (a,2,sync); }
   { atomic<ulong,strong> a(0);  rshift (a,2,sync); }
   { atomic<ulong,strong> a(0);  andeq  (a,2,sync); }
   { atomic<ulong,strong> a(0);  oreq   (a,2,sync); }
   { atomic<ulong,strong> a(0);  xoreq  (a,2,sync); }
   { atomic<ulong,strong> a(0);  min    (a,2,sync); }
   { atomic<ulong,strong> a(0);  max    (a,2,sync); }
   { atomic<ulong,strong> a(0);  inc    (a,  sync); }
   { atomic<ulong,strong> a(0);  preinc (a,  sync); }
   { atomic<ulong,strong> a(0);  postinc(a,  sync); }
   { atomic<ulong,strong> a(0);  dec    (a,  sync); }
   { atomic<ulong,strong> a(0);  predec (a,  sync); }
   { atomic<ulong,strong> a(0);  postdec(a,  sync); }
   { atomic<ulong,strong> a(0);  add    (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  sub    (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  mul    (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  div    (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  mod    (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  lshift (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  rshift (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  andeq  (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  oreq   (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  xoreq  (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  min    (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  max    (a,2,success,failure); }
   { atomic<ulong,strong> a(0);  inc    (a,  success,failure); }
   { atomic<ulong,strong> a(0);  preinc (a,  success,failure); }
   { atomic<ulong,strong> a(0);  postinc(a,  success,failure); }
   { atomic<ulong,strong> a(0);  dec    (a,  success,failure); }
   { atomic<ulong,strong> a(0);  predec (a,  success,failure); }
   { atomic<ulong,strong> a(0);  postdec(a,  success,failure); }

   { atomic<ulong,strong::pun> a(0);  add    (a,2); }
   { atomic<ulong,strong::pun> a(0);  sub    (a,2); }
   { atomic<ulong,strong::pun> a(0);  mul    (a,2); }
   { atomic<ulong,strong::pun> a(0);  div    (a,2); }
   { atomic<ulong,strong::pun> a(0);  mod    (a,2); }
   { atomic<ulong,strong::pun> a(0);  lshift (a,2); }
   { atomic<ulong,strong::pun> a(0);  rshift (a,2); }
   { atomic<ulong,strong::pun> a(0);  andeq  (a,2); }
   { atomic<ulong,strong::pun> a(0);  oreq   (a,2); }
   { atomic<ulong,strong::pun> a(0);  xoreq  (a,2); }
   { atomic<ulong,strong::pun> a(0);  min    (a,2); }
   { atomic<ulong,strong::pun> a(0);  max    (a,2); }
   { atomic<ulong,strong::pun> a(0);  inc    (a); }
   { atomic<ulong,strong::pun> a(0);  preinc (a); }
   { atomic<ulong,strong::pun> a(0);  postinc(a); }
   { atomic<ulong,strong::pun> a(0);  dec    (a); }
   { atomic<ulong,strong::pun> a(0);  predec (a); }
   { atomic<ulong,strong::pun> a(0);  postdec(a); }
   { atomic<ulong,strong::pun> a(0);  add    (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  sub    (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  mul    (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  div    (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  mod    (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  lshift (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  rshift (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  andeq  (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  oreq   (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  xoreq  (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  min    (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  max    (a,2,sync); }
   { atomic<ulong,strong::pun> a(0);  inc    (a,  sync); }
   { atomic<ulong,strong::pun> a(0);  preinc (a,  sync); }
   { atomic<ulong,strong::pun> a(0);  postinc(a,  sync); }
   { atomic<ulong,strong::pun> a(0);  dec    (a,  sync); }
   { atomic<ulong,strong::pun> a(0);  predec (a,  sync); }
   { atomic<ulong,strong::pun> a(0);  postdec(a,  sync); }
   { atomic<ulong,strong::pun> a(0);  add    (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  sub    (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  mul    (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  div    (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  mod    (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  lshift (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  rshift (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  andeq  (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  oreq   (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  xoreq  (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  min    (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  max    (a,2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  inc    (a,  success,failure); }
   { atomic<ulong,strong::pun> a(0);  preinc (a,  success,failure); }
   { atomic<ulong,strong::pun> a(0);  postinc(a,  success,failure); }
   { atomic<ulong,strong::pun> a(0);  dec    (a,  success,failure); }
   { atomic<ulong,strong::pun> a(0);  predec (a,  success,failure); }
   { atomic<ulong,strong::pun> a(0);  postdec(a,  success,failure); }

   { atomic<ulong,weak> a(0);  add    (a,2); }
   { atomic<ulong,weak> a(0);  sub    (a,2); }
   { atomic<ulong,weak> a(0);  mul    (a,2); }
   { atomic<ulong,weak> a(0);  div    (a,2); }
   { atomic<ulong,weak> a(0);  mod    (a,2); }
   { atomic<ulong,weak> a(0);  lshift (a,2); }
   { atomic<ulong,weak> a(0);  rshift (a,2); }
   { atomic<ulong,weak> a(0);  andeq  (a,2); }
   { atomic<ulong,weak> a(0);  oreq   (a,2); }
   { atomic<ulong,weak> a(0);  xoreq  (a,2); }
   { atomic<ulong,weak> a(0);  min    (a,2); }
   { atomic<ulong,weak> a(0);  max    (a,2); }
   { atomic<ulong,weak> a(0);  inc    (a); }
   { atomic<ulong,weak> a(0);  preinc (a); }
   { atomic<ulong,weak> a(0);  postinc(a); }
   { atomic<ulong,weak> a(0);  dec    (a); }
   { atomic<ulong,weak> a(0);  predec (a); }
   { atomic<ulong,weak> a(0);  postdec(a); }
   { atomic<ulong,weak> a(0);  add    (a,2,sync); }
   { atomic<ulong,weak> a(0);  sub    (a,2,sync); }
   { atomic<ulong,weak> a(0);  mul    (a,2,sync); }
   { atomic<ulong,weak> a(0);  div    (a,2,sync); }
   { atomic<ulong,weak> a(0);  mod    (a,2,sync); }
   { atomic<ulong,weak> a(0);  lshift (a,2,sync); }
   { atomic<ulong,weak> a(0);  rshift (a,2,sync); }
   { atomic<ulong,weak> a(0);  andeq  (a,2,sync); }
   { atomic<ulong,weak> a(0);  oreq   (a,2,sync); }
   { atomic<ulong,weak> a(0);  xoreq  (a,2,sync); }
   { atomic<ulong,weak> a(0);  min    (a,2,sync); }
   { atomic<ulong,weak> a(0);  max    (a,2,sync); }
   { atomic<ulong,weak> a(0);  inc    (a,  sync); }
   { atomic<ulong,weak> a(0);  preinc (a,  sync); }
   { atomic<ulong,weak> a(0);  postinc(a,  sync); }
   { atomic<ulong,weak> a(0);  dec    (a,  sync); }
   { atomic<ulong,weak> a(0);  predec (a,  sync); }
   { atomic<ulong,weak> a(0);  postdec(a,  sync); }
   { atomic<ulong,weak> a(0);  add    (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  sub    (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  mul    (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  div    (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  mod    (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  lshift (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  rshift (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  andeq  (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  oreq   (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  xoreq  (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  min    (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  max    (a,2,success,failure); }
   { atomic<ulong,weak> a(0);  inc    (a,  success,failure); }
   { atomic<ulong,weak> a(0);  preinc (a,  success,failure); }
   { atomic<ulong,weak> a(0);  postinc(a,  success,failure); }
   { atomic<ulong,weak> a(0);  dec    (a,  success,failure); }
   { atomic<ulong,weak> a(0);  predec (a,  success,failure); }
   { atomic<ulong,weak> a(0);  postdec(a,  success,failure); }

   { atomic<ulong,weak::pun> a(0);  add    (a,2); }
   { atomic<ulong,weak::pun> a(0);  sub    (a,2); }
   { atomic<ulong,weak::pun> a(0);  mul    (a,2); }
   { atomic<ulong,weak::pun> a(0);  div    (a,2); }
   { atomic<ulong,weak::pun> a(0);  mod    (a,2); }
   { atomic<ulong,weak::pun> a(0);  lshift (a,2); }
   { atomic<ulong,weak::pun> a(0);  rshift (a,2); }
   { atomic<ulong,weak::pun> a(0);  andeq  (a,2); }
   { atomic<ulong,weak::pun> a(0);  oreq   (a,2); }
   { atomic<ulong,weak::pun> a(0);  xoreq  (a,2); }
   { atomic<ulong,weak::pun> a(0);  min    (a,2); }
   { atomic<ulong,weak::pun> a(0);  max    (a,2); }
   { atomic<ulong,weak::pun> a(0);  inc    (a); }
   { atomic<ulong,weak::pun> a(0);  preinc (a); }
   { atomic<ulong,weak::pun> a(0);  postinc(a); }
   { atomic<ulong,weak::pun> a(0);  dec    (a); }
   { atomic<ulong,weak::pun> a(0);  predec (a); }
   { atomic<ulong,weak::pun> a(0);  postdec(a); }
   { atomic<ulong,weak::pun> a(0);  add    (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  sub    (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  mul    (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  div    (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  mod    (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  lshift (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  rshift (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  andeq  (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  oreq   (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  xoreq  (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  min    (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  max    (a,2,sync); }
   { atomic<ulong,weak::pun> a(0);  inc    (a,  sync); }
   { atomic<ulong,weak::pun> a(0);  preinc (a,  sync); }
   { atomic<ulong,weak::pun> a(0);  postinc(a,  sync); }
   { atomic<ulong,weak::pun> a(0);  dec    (a,  sync); }
   { atomic<ulong,weak::pun> a(0);  predec (a,  sync); }
   { atomic<ulong,weak::pun> a(0);  postdec(a,  sync); }
   { atomic<ulong,weak::pun> a(0);  add    (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  sub    (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  mul    (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  div    (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  mod    (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  lshift (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  rshift (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  andeq  (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  oreq   (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  xoreq  (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  min    (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  max    (a,2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  inc    (a,  success,failure); }
   { atomic<ulong,weak::pun> a(0);  preinc (a,  success,failure); }
   { atomic<ulong,weak::pun> a(0);  postinc(a,  success,failure); }
   { atomic<ulong,weak::pun> a(0);  dec    (a,  success,failure); }
   { atomic<ulong,weak::pun> a(0);  predec (a,  success,failure); }
   { atomic<ulong,weak::pun> a(0);  postdec(a,  success,failure); }

   { atomic<ulong,lock> a(0);  add    (a,2); }
   { atomic<ulong,lock> a(0);  sub    (a,2); }
   { atomic<ulong,lock> a(0);  mul    (a,2); }
   { atomic<ulong,lock> a(0);  div    (a,2); }
   { atomic<ulong,lock> a(0);  mod    (a,2); }
   { atomic<ulong,lock> a(0);  lshift (a,2); }
   { atomic<ulong,lock> a(0);  rshift (a,2); }
   { atomic<ulong,lock> a(0);  andeq  (a,2); }
   { atomic<ulong,lock> a(0);  oreq   (a,2); }
   { atomic<ulong,lock> a(0);  xoreq  (a,2); }
   { atomic<ulong,lock> a(0);  min    (a,2); }
   { atomic<ulong,lock> a(0);  max    (a,2); }
   { atomic<ulong,lock> a(0);  inc    (a); }
   { atomic<ulong,lock> a(0);  preinc (a); }
   { atomic<ulong,lock> a(0);  postinc(a); }
   { atomic<ulong,lock> a(0);  dec    (a); }
   { atomic<ulong,lock> a(0);  predec (a); }
   { atomic<ulong,lock> a(0);  postdec(a); }
// { atomic<ulong,lock> a(0);  add    (a,2,sync); }
// { atomic<ulong,lock> a(0);  sub    (a,2,sync); }
// { atomic<ulong,lock> a(0);  mul    (a,2,sync); }
// { atomic<ulong,lock> a(0);  div    (a,2,sync); }
// { atomic<ulong,lock> a(0);  mod    (a,2,sync); }
// { atomic<ulong,lock> a(0);  lshift (a,2,sync); }
// { atomic<ulong,lock> a(0);  rshift (a,2,sync); }
// { atomic<ulong,lock> a(0);  andeq  (a,2,sync); }
// { atomic<ulong,lock> a(0);  oreq   (a,2,sync); }
// { atomic<ulong,lock> a(0);  xoreq  (a,2,sync); }
// { atomic<ulong,lock> a(0);  min    (a,2,sync); }
// { atomic<ulong,lock> a(0);  max    (a,2,sync); }
// { atomic<ulong,lock> a(0);  inc    (a,  sync); }
// { atomic<ulong,lock> a(0);  preinc (a,  sync); }
// { atomic<ulong,lock> a(0);  postinc(a,  sync); }
// { atomic<ulong,lock> a(0);  dec    (a,  sync); }
// { atomic<ulong,lock> a(0);  predec (a,  sync); }
// { atomic<ulong,lock> a(0);  postdec(a,  sync); }
// { atomic<ulong,lock> a(0);  add    (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  sub    (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  mul    (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  div    (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  mod    (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  lshift (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  rshift (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  andeq  (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  oreq   (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  xoreq  (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  min    (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  max    (a,2,success,failure); }
// { atomic<ulong,lock> a(0);  inc    (a,  success,failure); }
// { atomic<ulong,lock> a(0);  preinc (a,  success,failure); }
// { atomic<ulong,lock> a(0);  postinc(a,  success,failure); }
// { atomic<ulong,lock> a(0);  dec    (a,  success,failure); }
// { atomic<ulong,lock> a(0);  predec (a,  success,failure); }
// { atomic<ulong,lock> a(0);  postdec(a,  success,failure); }

   { atomic<ulong,serial> a(0);  add    (a,2); }
   { atomic<ulong,serial> a(0);  sub    (a,2); }
   { atomic<ulong,serial> a(0);  mul    (a,2); }
   { atomic<ulong,serial> a(0);  div    (a,2); }
   { atomic<ulong,serial> a(0);  mod    (a,2); }
   { atomic<ulong,serial> a(0);  lshift (a,2); }
   { atomic<ulong,serial> a(0);  rshift (a,2); }
   { atomic<ulong,serial> a(0);  andeq  (a,2); }
   { atomic<ulong,serial> a(0);  oreq   (a,2); }
   { atomic<ulong,serial> a(0);  xoreq  (a,2); }
   { atomic<ulong,serial> a(0);  min    (a,2); }
   { atomic<ulong,serial> a(0);  max    (a,2); }
   { atomic<ulong,serial> a(0);  inc    (a); }
   { atomic<ulong,serial> a(0);  preinc (a); }
   { atomic<ulong,serial> a(0);  postinc(a); }
   { atomic<ulong,serial> a(0);  dec    (a); }
   { atomic<ulong,serial> a(0);  predec (a); }
   { atomic<ulong,serial> a(0);  postdec(a); }
// { atomic<ulong,serial> a(0);  add    (a,2,sync); }
// { atomic<ulong,serial> a(0);  sub    (a,2,sync); }
// { atomic<ulong,serial> a(0);  mul    (a,2,sync); }
// { atomic<ulong,serial> a(0);  div    (a,2,sync); }
// { atomic<ulong,serial> a(0);  mod    (a,2,sync); }
// { atomic<ulong,serial> a(0);  lshift (a,2,sync); }
// { atomic<ulong,serial> a(0);  rshift (a,2,sync); }
// { atomic<ulong,serial> a(0);  andeq  (a,2,sync); }
// { atomic<ulong,serial> a(0);  oreq   (a,2,sync); }
// { atomic<ulong,serial> a(0);  xoreq  (a,2,sync); }
// { atomic<ulong,serial> a(0);  min    (a,2,sync); }
// { atomic<ulong,serial> a(0);  max    (a,2,sync); }
// { atomic<ulong,serial> a(0);  inc    (a,  sync); }
// { atomic<ulong,serial> a(0);  preinc (a,  sync); }
// { atomic<ulong,serial> a(0);  postinc(a,  sync); }
// { atomic<ulong,serial> a(0);  dec    (a,  sync); }
// { atomic<ulong,serial> a(0);  predec (a,  sync); }
// { atomic<ulong,serial> a(0);  postdec(a,  sync); }
// { atomic<ulong,serial> a(0);  add    (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  sub    (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  mul    (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  div    (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  mod    (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  lshift (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  rshift (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  andeq  (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  oreq   (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  xoreq  (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  min    (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  max    (a,2,success,failure); }
// { atomic<ulong,serial> a(0);  inc    (a,  success,failure); }
// { atomic<ulong,serial> a(0);  preinc (a,  success,failure); }
// { atomic<ulong,serial> a(0);  postinc(a,  success,failure); }
// { atomic<ulong,serial> a(0);  dec    (a,  success,failure); }
// { atomic<ulong,serial> a(0);  predec (a,  success,failure); }
// { atomic<ulong,serial> a(0);  postdec(a,  success,failure); }



   // ------------------------
   // double
   // ------------------------

// { atomic<double,cpp> a(0);  add    (a,2); }
// { atomic<double,cpp> a(0);  sub    (a,2); }
// { atomic<double,cpp> a(0);  mul    (a,2); }
// { atomic<double,cpp> a(0);  div    (a,2); }
// { atomic<double,cpp> a(0);  mod    (a,2); }
// { atomic<double,cpp> a(0);  lshift (a,2); }
// { atomic<double,cpp> a(0);  rshift (a,2); }
// { atomic<double,cpp> a(0);  andeq  (a,2); }
// { atomic<double,cpp> a(0);  oreq   (a,2); }
// { atomic<double,cpp> a(0);  xoreq  (a,2); }
// { atomic<double,cpp> a(0);  min    (a,2); }
// { atomic<double,cpp> a(0);  max    (a,2); }
// { atomic<double,cpp> a(0);  inc    (a); }
// { atomic<double,cpp> a(0);  preinc (a); }
// { atomic<double,cpp> a(0);  postinc(a); }
// { atomic<double,cpp> a(0);  dec    (a); }
// { atomic<double,cpp> a(0);  predec (a); }
// { atomic<double,cpp> a(0);  postdec(a); }
// { atomic<double,cpp> a(0);  add    (a,2,sync); }
// { atomic<double,cpp> a(0);  sub    (a,2,sync); }
// { atomic<double,cpp> a(0);  mul    (a,2,sync); }
// { atomic<double,cpp> a(0);  div    (a,2,sync); }
// { atomic<double,cpp> a(0);  mod    (a,2,sync); }
// { atomic<double,cpp> a(0);  lshift (a,2,sync); }
// { atomic<double,cpp> a(0);  rshift (a,2,sync); }
// { atomic<double,cpp> a(0);  andeq  (a,2,sync); }
// { atomic<double,cpp> a(0);  oreq   (a,2,sync); }
// { atomic<double,cpp> a(0);  xoreq  (a,2,sync); }
// { atomic<double,cpp> a(0);  min    (a,2,sync); }
// { atomic<double,cpp> a(0);  max    (a,2,sync); }
// { atomic<double,cpp> a(0);  inc    (a,  sync); }
// { atomic<double,cpp> a(0);  preinc (a,  sync); }
// { atomic<double,cpp> a(0);  postinc(a,  sync); }
// { atomic<double,cpp> a(0);  dec    (a,  sync); }
// { atomic<double,cpp> a(0);  predec (a,  sync); }
// { atomic<double,cpp> a(0);  postdec(a,  sync); }
// { atomic<double,cpp> a(0);  add    (a,2,success,failure); }
// { atomic<double,cpp> a(0);  sub    (a,2,success,failure); }
// { atomic<double,cpp> a(0);  mul    (a,2,success,failure); }
// { atomic<double,cpp> a(0);  div    (a,2,success,failure); }
// { atomic<double,cpp> a(0);  mod    (a,2,success,failure); }
// { atomic<double,cpp> a(0);  lshift (a,2,success,failure); }
// { atomic<double,cpp> a(0);  rshift (a,2,success,failure); }
// { atomic<double,cpp> a(0);  andeq  (a,2,success,failure); }
// { atomic<double,cpp> a(0);  oreq   (a,2,success,failure); }
// { atomic<double,cpp> a(0);  xoreq  (a,2,success,failure); }
// { atomic<double,cpp> a(0);  min    (a,2,success,failure); }
// { atomic<double,cpp> a(0);  max    (a,2,success,failure); }
// { atomic<double,cpp> a(0);  inc    (a,  success,failure); }
// { atomic<double,cpp> a(0);  preinc (a,  success,failure); }
// { atomic<double,cpp> a(0);  postinc(a,  success,failure); }
// { atomic<double,cpp> a(0);  dec    (a,  success,failure); }
// { atomic<double,cpp> a(0);  predec (a,  success,failure); }
// { atomic<double,cpp> a(0);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { atomic<double,kokkos> a(0);  add    (a,2); }
   { atomic<double,kokkos> a(0);  sub    (a,2); }
   { atomic<double,kokkos> a(0);  mul    (a,2); }
   { atomic<double,kokkos> a(0);  div    (a,2); }
// { atomic<double,kokkos> a(0);  mod    (a,2); }
// { atomic<double,kokkos> a(0);  lshift (a,2); }
// { atomic<double,kokkos> a(0);  rshift (a,2); }
// { atomic<double,kokkos> a(0);  andeq  (a,2); }
// { atomic<double,kokkos> a(0);  oreq   (a,2); }
// { atomic<double,kokkos> a(0);  xoreq  (a,2); }
   { atomic<double,kokkos> a(0);  min    (a,2); }
   { atomic<double,kokkos> a(0);  max    (a,2); }
   { atomic<double,kokkos> a(0);  inc    (a); }
   { atomic<double,kokkos> a(0);  preinc (a); }
   { atomic<double,kokkos> a(0);  postinc(a); }
   { atomic<double,kokkos> a(0);  dec    (a); }
   { atomic<double,kokkos> a(0);  predec (a); }
   { atomic<double,kokkos> a(0);  postdec(a); }
// { atomic<double,kokkos> a(0);  add    (a,2,sync); }
// { atomic<double,kokkos> a(0);  sub    (a,2,sync); }
// { atomic<double,kokkos> a(0);  mul    (a,2,sync); }
// { atomic<double,kokkos> a(0);  div    (a,2,sync); }
// { atomic<double,kokkos> a(0);  mod    (a,2,sync); }
// { atomic<double,kokkos> a(0);  lshift (a,2,sync); }
// { atomic<double,kokkos> a(0);  rshift (a,2,sync); }
// { atomic<double,kokkos> a(0);  andeq  (a,2,sync); }
// { atomic<double,kokkos> a(0);  oreq   (a,2,sync); }
// { atomic<double,kokkos> a(0);  xoreq  (a,2,sync); }
// { atomic<double,kokkos> a(0);  min    (a,2,sync); }
// { atomic<double,kokkos> a(0);  max    (a,2,sync); }
// { atomic<double,kokkos> a(0);  inc    (a,  sync); }
// { atomic<double,kokkos> a(0);  preinc (a,  sync); }
// { atomic<double,kokkos> a(0);  postinc(a,  sync); }
// { atomic<double,kokkos> a(0);  dec    (a,  sync); }
// { atomic<double,kokkos> a(0);  predec (a,  sync); }
// { atomic<double,kokkos> a(0);  postdec(a,  sync); }
// { atomic<double,kokkos> a(0);  add    (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  sub    (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  mul    (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  div    (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  mod    (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  lshift (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  rshift (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  andeq  (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  oreq   (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  xoreq  (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  min    (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  max    (a,2,success,failure); }
// { atomic<double,kokkos> a(0);  inc    (a,  success,failure); }
// { atomic<double,kokkos> a(0);  preinc (a,  success,failure); }
// { atomic<double,kokkos> a(0);  postinc(a,  success,failure); }
// { atomic<double,kokkos> a(0);  dec    (a,  success,failure); }
// { atomic<double,kokkos> a(0);  predec (a,  success,failure); }
// { atomic<double,kokkos> a(0);  postdec(a,  success,failure); }
#endif

   { atomic<double,strong> a(0);  add    (a,2); }
   { atomic<double,strong> a(0);  sub    (a,2); }
   { atomic<double,strong> a(0);  mul    (a,2); }
   { atomic<double,strong> a(0);  div    (a,2); }
// { atomic<double,strong> a(0);  mod    (a,2); }
// { atomic<double,strong> a(0);  lshift (a,2); }
// { atomic<double,strong> a(0);  rshift (a,2); }
// { atomic<double,strong> a(0);  andeq  (a,2); }
// { atomic<double,strong> a(0);  oreq   (a,2); }
// { atomic<double,strong> a(0);  xoreq  (a,2); }
   { atomic<double,strong> a(0);  min    (a,2); }
   { atomic<double,strong> a(0);  max    (a,2); }
   { atomic<double,strong> a(0);  inc    (a); }
   { atomic<double,strong> a(0);  preinc (a); }
   { atomic<double,strong> a(0);  postinc(a); }
   { atomic<double,strong> a(0);  dec    (a); }
   { atomic<double,strong> a(0);  predec (a); }
   { atomic<double,strong> a(0);  postdec(a); }
   { atomic<double,strong> a(0);  add    (a,2,sync); }
   { atomic<double,strong> a(0);  sub    (a,2,sync); }
   { atomic<double,strong> a(0);  mul    (a,2,sync); }
   { atomic<double,strong> a(0);  div    (a,2,sync); }
// { atomic<double,strong> a(0);  mod    (a,2,sync); }
// { atomic<double,strong> a(0);  lshift (a,2,sync); }
// { atomic<double,strong> a(0);  rshift (a,2,sync); }
// { atomic<double,strong> a(0);  andeq  (a,2,sync); }
// { atomic<double,strong> a(0);  oreq   (a,2,sync); }
// { atomic<double,strong> a(0);  xoreq  (a,2,sync); }
   { atomic<double,strong> a(0);  min    (a,2,sync); }
   { atomic<double,strong> a(0);  max    (a,2,sync); }
   { atomic<double,strong> a(0);  inc    (a,  sync); }
   { atomic<double,strong> a(0);  preinc (a,  sync); }
   { atomic<double,strong> a(0);  postinc(a,  sync); }
   { atomic<double,strong> a(0);  dec    (a,  sync); }
   { atomic<double,strong> a(0);  predec (a,  sync); }
   { atomic<double,strong> a(0);  postdec(a,  sync); }
   { atomic<double,strong> a(0);  add    (a,2,success,failure); }
   { atomic<double,strong> a(0);  sub    (a,2,success,failure); }
   { atomic<double,strong> a(0);  mul    (a,2,success,failure); }
   { atomic<double,strong> a(0);  div    (a,2,success,failure); }
// { atomic<double,strong> a(0);  mod    (a,2,success,failure); }
// { atomic<double,strong> a(0);  lshift (a,2,success,failure); }
// { atomic<double,strong> a(0);  rshift (a,2,success,failure); }
// { atomic<double,strong> a(0);  andeq  (a,2,success,failure); }
// { atomic<double,strong> a(0);  oreq   (a,2,success,failure); }
// { atomic<double,strong> a(0);  xoreq  (a,2,success,failure); }
   { atomic<double,strong> a(0);  min    (a,2,success,failure); }
   { atomic<double,strong> a(0);  max    (a,2,success,failure); }
   { atomic<double,strong> a(0);  inc    (a,  success,failure); }
   { atomic<double,strong> a(0);  preinc (a,  success,failure); }
   { atomic<double,strong> a(0);  postinc(a,  success,failure); }
   { atomic<double,strong> a(0);  dec    (a,  success,failure); }
   { atomic<double,strong> a(0);  predec (a,  success,failure); }
   { atomic<double,strong> a(0);  postdec(a,  success,failure); }

   { atomic<double,strong::pun> a(0);  add    (a,2); }
   { atomic<double,strong::pun> a(0);  sub    (a,2); }
   { atomic<double,strong::pun> a(0);  mul    (a,2); }
   { atomic<double,strong::pun> a(0);  div    (a,2); }
// { atomic<double,strong::pun> a(0);  mod    (a,2); }
// { atomic<double,strong::pun> a(0);  lshift (a,2); }
// { atomic<double,strong::pun> a(0);  rshift (a,2); }
// { atomic<double,strong::pun> a(0);  andeq  (a,2); }
// { atomic<double,strong::pun> a(0);  oreq   (a,2); }
// { atomic<double,strong::pun> a(0);  xoreq  (a,2); }
   { atomic<double,strong::pun> a(0);  min    (a,2); }
   { atomic<double,strong::pun> a(0);  max    (a,2); }
   { atomic<double,strong::pun> a(0);  inc    (a); }
   { atomic<double,strong::pun> a(0);  preinc (a); }
   { atomic<double,strong::pun> a(0);  postinc(a); }
   { atomic<double,strong::pun> a(0);  dec    (a); }
   { atomic<double,strong::pun> a(0);  predec (a); }
   { atomic<double,strong::pun> a(0);  postdec(a); }
   { atomic<double,strong::pun> a(0);  add    (a,2,sync); }
   { atomic<double,strong::pun> a(0);  sub    (a,2,sync); }
   { atomic<double,strong::pun> a(0);  mul    (a,2,sync); }
   { atomic<double,strong::pun> a(0);  div    (a,2,sync); }
// { atomic<double,strong::pun> a(0);  mod    (a,2,sync); }
// { atomic<double,strong::pun> a(0);  lshift (a,2,sync); }
// { atomic<double,strong::pun> a(0);  rshift (a,2,sync); }
// { atomic<double,strong::pun> a(0);  andeq  (a,2,sync); }
// { atomic<double,strong::pun> a(0);  oreq   (a,2,sync); }
// { atomic<double,strong::pun> a(0);  xoreq  (a,2,sync); }
   { atomic<double,strong::pun> a(0);  min    (a,2,sync); }
   { atomic<double,strong::pun> a(0);  max    (a,2,sync); }
   { atomic<double,strong::pun> a(0);  inc    (a,  sync); }
   { atomic<double,strong::pun> a(0);  preinc (a,  sync); }
   { atomic<double,strong::pun> a(0);  postinc(a,  sync); }
   { atomic<double,strong::pun> a(0);  dec    (a,  sync); }
   { atomic<double,strong::pun> a(0);  predec (a,  sync); }
   { atomic<double,strong::pun> a(0);  postdec(a,  sync); }
   { atomic<double,strong::pun> a(0);  add    (a,2,success,failure); }
   { atomic<double,strong::pun> a(0);  sub    (a,2,success,failure); }
   { atomic<double,strong::pun> a(0);  mul    (a,2,success,failure); }
   { atomic<double,strong::pun> a(0);  div    (a,2,success,failure); }
// { atomic<double,strong::pun> a(0);  mod    (a,2,success,failure); }
// { atomic<double,strong::pun> a(0);  lshift (a,2,success,failure); }
// { atomic<double,strong::pun> a(0);  rshift (a,2,success,failure); }
// { atomic<double,strong::pun> a(0);  andeq  (a,2,success,failure); }
// { atomic<double,strong::pun> a(0);  oreq   (a,2,success,failure); }
// { atomic<double,strong::pun> a(0);  xoreq  (a,2,success,failure); }
   { atomic<double,strong::pun> a(0);  min    (a,2,success,failure); }
   { atomic<double,strong::pun> a(0);  max    (a,2,success,failure); }
   { atomic<double,strong::pun> a(0);  inc    (a,  success,failure); }
   { atomic<double,strong::pun> a(0);  preinc (a,  success,failure); }
   { atomic<double,strong::pun> a(0);  postinc(a,  success,failure); }
   { atomic<double,strong::pun> a(0);  dec    (a,  success,failure); }
   { atomic<double,strong::pun> a(0);  predec (a,  success,failure); }
   { atomic<double,strong::pun> a(0);  postdec(a,  success,failure); }

   { atomic<double,weak> a(0);  add    (a,2); }
   { atomic<double,weak> a(0);  sub    (a,2); }
   { atomic<double,weak> a(0);  mul    (a,2); }
   { atomic<double,weak> a(0);  div    (a,2); }
// { atomic<double,weak> a(0);  mod    (a,2); }
// { atomic<double,weak> a(0);  lshift (a,2); }
// { atomic<double,weak> a(0);  rshift (a,2); }
// { atomic<double,weak> a(0);  andeq  (a,2); }
// { atomic<double,weak> a(0);  oreq   (a,2); }
// { atomic<double,weak> a(0);  xoreq  (a,2); }
   { atomic<double,weak> a(0);  min    (a,2); }
   { atomic<double,weak> a(0);  max    (a,2); }
   { atomic<double,weak> a(0);  inc    (a); }
   { atomic<double,weak> a(0);  preinc (a); }
   { atomic<double,weak> a(0);  postinc(a); }
   { atomic<double,weak> a(0);  dec    (a); }
   { atomic<double,weak> a(0);  predec (a); }
   { atomic<double,weak> a(0);  postdec(a); }
   { atomic<double,weak> a(0);  add    (a,2,sync); }
   { atomic<double,weak> a(0);  sub    (a,2,sync); }
   { atomic<double,weak> a(0);  mul    (a,2,sync); }
   { atomic<double,weak> a(0);  div    (a,2,sync); }
// { atomic<double,weak> a(0);  mod    (a,2,sync); }
// { atomic<double,weak> a(0);  lshift (a,2,sync); }
// { atomic<double,weak> a(0);  rshift (a,2,sync); }
// { atomic<double,weak> a(0);  andeq  (a,2,sync); }
// { atomic<double,weak> a(0);  oreq   (a,2,sync); }
// { atomic<double,weak> a(0);  xoreq  (a,2,sync); }
   { atomic<double,weak> a(0);  min    (a,2,sync); }
   { atomic<double,weak> a(0);  max    (a,2,sync); }
   { atomic<double,weak> a(0);  inc    (a,  sync); }
   { atomic<double,weak> a(0);  preinc (a,  sync); }
   { atomic<double,weak> a(0);  postinc(a,  sync); }
   { atomic<double,weak> a(0);  dec    (a,  sync); }
   { atomic<double,weak> a(0);  predec (a,  sync); }
   { atomic<double,weak> a(0);  postdec(a,  sync); }
   { atomic<double,weak> a(0);  add    (a,2,success,failure); }
   { atomic<double,weak> a(0);  sub    (a,2,success,failure); }
   { atomic<double,weak> a(0);  mul    (a,2,success,failure); }
   { atomic<double,weak> a(0);  div    (a,2,success,failure); }
// { atomic<double,weak> a(0);  mod    (a,2,success,failure); }
// { atomic<double,weak> a(0);  lshift (a,2,success,failure); }
// { atomic<double,weak> a(0);  rshift (a,2,success,failure); }
// { atomic<double,weak> a(0);  andeq  (a,2,success,failure); }
// { atomic<double,weak> a(0);  oreq   (a,2,success,failure); }
// { atomic<double,weak> a(0);  xoreq  (a,2,success,failure); }
   { atomic<double,weak> a(0);  min    (a,2,success,failure); }
   { atomic<double,weak> a(0);  max    (a,2,success,failure); }
   { atomic<double,weak> a(0);  inc    (a,  success,failure); }
   { atomic<double,weak> a(0);  preinc (a,  success,failure); }
   { atomic<double,weak> a(0);  postinc(a,  success,failure); }
   { atomic<double,weak> a(0);  dec    (a,  success,failure); }
   { atomic<double,weak> a(0);  predec (a,  success,failure); }
   { atomic<double,weak> a(0);  postdec(a,  success,failure); }

   { atomic<double,weak::pun> a(0);  add    (a,2); }
   { atomic<double,weak::pun> a(0);  sub    (a,2); }
   { atomic<double,weak::pun> a(0);  mul    (a,2); }
   { atomic<double,weak::pun> a(0);  div    (a,2); }
// { atomic<double,weak::pun> a(0);  mod    (a,2); }
// { atomic<double,weak::pun> a(0);  lshift (a,2); }
// { atomic<double,weak::pun> a(0);  rshift (a,2); }
// { atomic<double,weak::pun> a(0);  andeq  (a,2); }
// { atomic<double,weak::pun> a(0);  oreq   (a,2); }
// { atomic<double,weak::pun> a(0);  xoreq  (a,2); }
   { atomic<double,weak::pun> a(0);  min    (a,2); }
   { atomic<double,weak::pun> a(0);  max    (a,2); }
   { atomic<double,weak::pun> a(0);  inc    (a); }
   { atomic<double,weak::pun> a(0);  preinc (a); }
   { atomic<double,weak::pun> a(0);  postinc(a); }
   { atomic<double,weak::pun> a(0);  dec    (a); }
   { atomic<double,weak::pun> a(0);  predec (a); }
   { atomic<double,weak::pun> a(0);  postdec(a); }
   { atomic<double,weak::pun> a(0);  add    (a,2,sync); }
   { atomic<double,weak::pun> a(0);  sub    (a,2,sync); }
   { atomic<double,weak::pun> a(0);  mul    (a,2,sync); }
   { atomic<double,weak::pun> a(0);  div    (a,2,sync); }
// { atomic<double,weak::pun> a(0);  mod    (a,2,sync); }
// { atomic<double,weak::pun> a(0);  lshift (a,2,sync); }
// { atomic<double,weak::pun> a(0);  rshift (a,2,sync); }
// { atomic<double,weak::pun> a(0);  andeq  (a,2,sync); }
// { atomic<double,weak::pun> a(0);  oreq   (a,2,sync); }
// { atomic<double,weak::pun> a(0);  xoreq  (a,2,sync); }
   { atomic<double,weak::pun> a(0);  min    (a,2,sync); }
   { atomic<double,weak::pun> a(0);  max    (a,2,sync); }
   { atomic<double,weak::pun> a(0);  inc    (a,  sync); }
   { atomic<double,weak::pun> a(0);  preinc (a,  sync); }
   { atomic<double,weak::pun> a(0);  postinc(a,  sync); }
   { atomic<double,weak::pun> a(0);  dec    (a,  sync); }
   { atomic<double,weak::pun> a(0);  predec (a,  sync); }
   { atomic<double,weak::pun> a(0);  postdec(a,  sync); }
   { atomic<double,weak::pun> a(0);  add    (a,2,success,failure); }
   { atomic<double,weak::pun> a(0);  sub    (a,2,success,failure); }
   { atomic<double,weak::pun> a(0);  mul    (a,2,success,failure); }
   { atomic<double,weak::pun> a(0);  div    (a,2,success,failure); }
// { atomic<double,weak::pun> a(0);  mod    (a,2,success,failure); }
// { atomic<double,weak::pun> a(0);  lshift (a,2,success,failure); }
// { atomic<double,weak::pun> a(0);  rshift (a,2,success,failure); }
// { atomic<double,weak::pun> a(0);  andeq  (a,2,success,failure); }
// { atomic<double,weak::pun> a(0);  oreq   (a,2,success,failure); }
// { atomic<double,weak::pun> a(0);  xoreq  (a,2,success,failure); }
   { atomic<double,weak::pun> a(0);  min    (a,2,success,failure); }
   { atomic<double,weak::pun> a(0);  max    (a,2,success,failure); }
   { atomic<double,weak::pun> a(0);  inc    (a,  success,failure); }
   { atomic<double,weak::pun> a(0);  preinc (a,  success,failure); }
   { atomic<double,weak::pun> a(0);  postinc(a,  success,failure); }
   { atomic<double,weak::pun> a(0);  dec    (a,  success,failure); }
   { atomic<double,weak::pun> a(0);  predec (a,  success,failure); }
   { atomic<double,weak::pun> a(0);  postdec(a,  success,failure); }

   { atomic<double,lock> a(0);  add    (a,2); }
   { atomic<double,lock> a(0);  sub    (a,2); }
   { atomic<double,lock> a(0);  mul    (a,2); }
   { atomic<double,lock> a(0);  div    (a,2); }
// { atomic<double,lock> a(0);  mod    (a,2); }
// { atomic<double,lock> a(0);  lshift (a,2); }
// { atomic<double,lock> a(0);  rshift (a,2); }
// { atomic<double,lock> a(0);  andeq  (a,2); }
// { atomic<double,lock> a(0);  oreq   (a,2); }
// { atomic<double,lock> a(0);  xoreq  (a,2); }
   { atomic<double,lock> a(0);  min    (a,2); }
   { atomic<double,lock> a(0);  max    (a,2); }
   { atomic<double,lock> a(0);  inc    (a); }
   { atomic<double,lock> a(0);  preinc (a); }
   { atomic<double,lock> a(0);  postinc(a); }
   { atomic<double,lock> a(0);  dec    (a); }
   { atomic<double,lock> a(0);  predec (a); }
   { atomic<double,lock> a(0);  postdec(a); }
// { atomic<double,lock> a(0);  add    (a,2,sync); }
// { atomic<double,lock> a(0);  sub    (a,2,sync); }
// { atomic<double,lock> a(0);  mul    (a,2,sync); }
// { atomic<double,lock> a(0);  div    (a,2,sync); }
// { atomic<double,lock> a(0);  mod    (a,2,sync); }
// { atomic<double,lock> a(0);  lshift (a,2,sync); }
// { atomic<double,lock> a(0);  rshift (a,2,sync); }
// { atomic<double,lock> a(0);  andeq  (a,2,sync); }
// { atomic<double,lock> a(0);  oreq   (a,2,sync); }
// { atomic<double,lock> a(0);  xoreq  (a,2,sync); }
// { atomic<double,lock> a(0);  min    (a,2,sync); }
// { atomic<double,lock> a(0);  max    (a,2,sync); }
// { atomic<double,lock> a(0);  inc    (a,  sync); }
// { atomic<double,lock> a(0);  preinc (a,  sync); }
// { atomic<double,lock> a(0);  postinc(a,  sync); }
// { atomic<double,lock> a(0);  dec    (a,  sync); }
// { atomic<double,lock> a(0);  predec (a,  sync); }
// { atomic<double,lock> a(0);  postdec(a,  sync); }
// { atomic<double,lock> a(0);  add    (a,2,success,failure); }
// { atomic<double,lock> a(0);  sub    (a,2,success,failure); }
// { atomic<double,lock> a(0);  mul    (a,2,success,failure); }
// { atomic<double,lock> a(0);  div    (a,2,success,failure); }
// { atomic<double,lock> a(0);  mod    (a,2,success,failure); }
// { atomic<double,lock> a(0);  lshift (a,2,success,failure); }
// { atomic<double,lock> a(0);  rshift (a,2,success,failure); }
// { atomic<double,lock> a(0);  andeq  (a,2,success,failure); }
// { atomic<double,lock> a(0);  oreq   (a,2,success,failure); }
// { atomic<double,lock> a(0);  xoreq  (a,2,success,failure); }
// { atomic<double,lock> a(0);  min    (a,2,success,failure); }
// { atomic<double,lock> a(0);  max    (a,2,success,failure); }
// { atomic<double,lock> a(0);  inc    (a,  success,failure); }
// { atomic<double,lock> a(0);  preinc (a,  success,failure); }
// { atomic<double,lock> a(0);  postinc(a,  success,failure); }
// { atomic<double,lock> a(0);  dec    (a,  success,failure); }
// { atomic<double,lock> a(0);  predec (a,  success,failure); }
// { atomic<double,lock> a(0);  postdec(a,  success,failure); }

   { atomic<double,serial> a(0);  add    (a,2); }
   { atomic<double,serial> a(0);  sub    (a,2); }
   { atomic<double,serial> a(0);  mul    (a,2); }
   { atomic<double,serial> a(0);  div    (a,2); }
// { atomic<double,serial> a(0);  mod    (a,2); }
// { atomic<double,serial> a(0);  lshift (a,2); }
// { atomic<double,serial> a(0);  rshift (a,2); }
// { atomic<double,serial> a(0);  andeq  (a,2); }
// { atomic<double,serial> a(0);  oreq   (a,2); }
// { atomic<double,serial> a(0);  xoreq  (a,2); }
   { atomic<double,serial> a(0);  min    (a,2); }
   { atomic<double,serial> a(0);  max    (a,2); }
   { atomic<double,serial> a(0);  inc    (a); }
   { atomic<double,serial> a(0);  preinc (a); }
   { atomic<double,serial> a(0);  postinc(a); }
   { atomic<double,serial> a(0);  dec    (a); }
   { atomic<double,serial> a(0);  predec (a); }
   { atomic<double,serial> a(0);  postdec(a); }
// { atomic<double,serial> a(0);  add    (a,2,sync); }
// { atomic<double,serial> a(0);  sub    (a,2,sync); }
// { atomic<double,serial> a(0);  mul    (a,2,sync); }
// { atomic<double,serial> a(0);  div    (a,2,sync); }
// { atomic<double,serial> a(0);  mod    (a,2,sync); }
// { atomic<double,serial> a(0);  lshift (a,2,sync); }
// { atomic<double,serial> a(0);  rshift (a,2,sync); }
// { atomic<double,serial> a(0);  andeq  (a,2,sync); }
// { atomic<double,serial> a(0);  oreq   (a,2,sync); }
// { atomic<double,serial> a(0);  xoreq  (a,2,sync); }
// { atomic<double,serial> a(0);  min    (a,2,sync); }
// { atomic<double,serial> a(0);  max    (a,2,sync); }
// { atomic<double,serial> a(0);  inc    (a,  sync); }
// { atomic<double,serial> a(0);  preinc (a,  sync); }
// { atomic<double,serial> a(0);  postinc(a,  sync); }
// { atomic<double,serial> a(0);  dec    (a,  sync); }
// { atomic<double,serial> a(0);  predec (a,  sync); }
// { atomic<double,serial> a(0);  postdec(a,  sync); }
// { atomic<double,serial> a(0);  add    (a,2,success,failure); }
// { atomic<double,serial> a(0);  sub    (a,2,success,failure); }
// { atomic<double,serial> a(0);  mul    (a,2,success,failure); }
// { atomic<double,serial> a(0);  div    (a,2,success,failure); }
// { atomic<double,serial> a(0);  mod    (a,2,success,failure); }
// { atomic<double,serial> a(0);  lshift (a,2,success,failure); }
// { atomic<double,serial> a(0);  rshift (a,2,success,failure); }
// { atomic<double,serial> a(0);  andeq  (a,2,success,failure); }
// { atomic<double,serial> a(0);  oreq   (a,2,success,failure); }
// { atomic<double,serial> a(0);  xoreq  (a,2,success,failure); }
// { atomic<double,serial> a(0);  min    (a,2,success,failure); }
// { atomic<double,serial> a(0);  max    (a,2,success,failure); }
// { atomic<double,serial> a(0);  inc    (a,  success,failure); }
// { atomic<double,serial> a(0);  preinc (a,  success,failure); }
// { atomic<double,serial> a(0);  postinc(a,  success,failure); }
// { atomic<double,serial> a(0);  dec    (a,  success,failure); }
// { atomic<double,serial> a(0);  predec (a,  success,failure); }
// { atomic<double,serial> a(0);  postdec(a,  success,failure); }



   // ------------------------
   // int*
   // ------------------------

   (void)i;
   (void)j;
#if !defined(ATOMICS_TEST)
   { atomic<int*,cpp> a(&i);  add    (a,2); }
   { atomic<int*,cpp> a(&i);  sub    (a,2); }
// { atomic<int*,cpp> a(&i);  mul    (a,2); }
// { atomic<int*,cpp> a(&i);  div    (a,2); }
// { atomic<int*,cpp> a(&i);  mod    (a,2); }
// { atomic<int*,cpp> a(&i);  lshift (a,2); }
// { atomic<int*,cpp> a(&i);  rshift (a,2); }
// { atomic<int*,cpp> a(&i);  andeq  (a,2); }
// { atomic<int*,cpp> a(&i);  oreq   (a,2); }
// { atomic<int*,cpp> a(&i);  xoreq  (a,2); }
// { atomic<int*,cpp> a(&i);  min    (a,&j); }
// { atomic<int*,cpp> a(&i);  max    (a,&j); }
   { atomic<int*,cpp> a(&i);  inc    (a); }
   { atomic<int*,cpp> a(&i);  preinc (a); }
   { atomic<int*,cpp> a(&i);  postinc(a); }
   { atomic<int*,cpp> a(&i);  dec    (a); }
   { atomic<int*,cpp> a(&i);  predec (a); }
   { atomic<int*,cpp> a(&i);  postdec(a); }
   { atomic<int*,cpp> a(&i);  add    (a,2,sync); }
   { atomic<int*,cpp> a(&i);  sub    (a,2,sync); }
// { atomic<int*,cpp> a(&i);  mul    (a,2,sync); }
// { atomic<int*,cpp> a(&i);  div    (a,2,sync); }
// { atomic<int*,cpp> a(&i);  mod    (a,2,sync); }
// { atomic<int*,cpp> a(&i);  lshift (a,2,sync); }
// { atomic<int*,cpp> a(&i);  rshift (a,2,sync); }
// { atomic<int*,cpp> a(&i);  andeq  (a,2,sync); }
// { atomic<int*,cpp> a(&i);  oreq   (a,2,sync); }
// { atomic<int*,cpp> a(&i);  xoreq  (a,2,sync); }
// { atomic<int*,cpp> a(&i);  min    (a,&j,sync); }
// { atomic<int*,cpp> a(&i);  max    (a,&j,sync); }
// { atomic<int*,cpp> a(&i);  inc    (a,  sync); }
// { atomic<int*,cpp> a(&i);  preinc (a,  sync); }
// { atomic<int*,cpp> a(&i);  postinc(a,  sync); }
// { atomic<int*,cpp> a(&i);  dec    (a,  sync); }
// { atomic<int*,cpp> a(&i);  predec (a,  sync); }
// { atomic<int*,cpp> a(&i);  postdec(a,  sync); }
// { atomic<int*,cpp> a(&i);  add    (a,2,success,failure); }
// { atomic<int*,cpp> a(&i);  sub    (a,2,success,failure); }
// { atomic<int*,cpp> a(&i);  mul    (a,2,success,failure); }
// { atomic<int*,cpp> a(&i);  div    (a,2,success,failure); }
// { atomic<int*,cpp> a(&i);  mod    (a,2,success,failure); }
// { atomic<int*,cpp> a(&i);  lshift (a,2,success,failure); }
// { atomic<int*,cpp> a(&i);  rshift (a,2,success,failure); }
// { atomic<int*,cpp> a(&i);  andeq  (a,2,success,failure); }
// { atomic<int*,cpp> a(&i);  oreq   (a,2,success,failure); }
// { atomic<int*,cpp> a(&i);  xoreq  (a,2,success,failure); }
// { atomic<int*,cpp> a(&i);  min    (a,&j,success,failure); }
// { atomic<int*,cpp> a(&i);  max    (a,&j,success,failure); }
// { atomic<int*,cpp> a(&i);  inc    (a,  success,failure); }
// { atomic<int*,cpp> a(&i);  preinc (a,  success,failure); }
// { atomic<int*,cpp> a(&i);  postinc(a,  success,failure); }
// { atomic<int*,cpp> a(&i);  dec    (a,  success,failure); }
// { atomic<int*,cpp> a(&i);  predec (a,  success,failure); }
// { atomic<int*,cpp> a(&i);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { atomic<int*,kokkos> a(&i);  add    (a,2); }
// { atomic<int*,kokkos> a(&i);  sub    (a,2); }
// { atomic<int*,kokkos> a(&i);  mul    (a,2); }
// { atomic<int*,kokkos> a(&i);  div    (a,2); }
// { atomic<int*,kokkos> a(&i);  mod    (a,2); }
// { atomic<int*,kokkos> a(&i);  lshift (a,2); }
// { atomic<int*,kokkos> a(&i);  rshift (a,2); }
// { atomic<int*,kokkos> a(&i);  andeq  (a,2); }
// { atomic<int*,kokkos> a(&i);  oreq   (a,2); }
// { atomic<int*,kokkos> a(&i);  xoreq  (a,2); }
// { atomic<int*,kokkos> a(&i);  min    (a,&j); }
// { atomic<int*,kokkos> a(&i);  max    (a,&j); }
// { atomic<int*,kokkos> a(&i);  inc    (a); }
// { atomic<int*,kokkos> a(&i);  preinc (a); }
// { atomic<int*,kokkos> a(&i);  postinc(a); }
// { atomic<int*,kokkos> a(&i);  dec    (a); }
// { atomic<int*,kokkos> a(&i);  predec (a); }
// { atomic<int*,kokkos> a(&i);  postdec(a); }
// { atomic<int*,kokkos> a(&i);  add    (a,2,sync); }
// { atomic<int*,kokkos> a(&i);  sub    (a,2,sync); }
// { atomic<int*,kokkos> a(&i);  mul    (a,2,sync); }
// { atomic<int*,kokkos> a(&i);  div    (a,2,sync); }
// { atomic<int*,kokkos> a(&i);  mod    (a,2,sync); }
// { atomic<int*,kokkos> a(&i);  lshift (a,2,sync); }
// { atomic<int*,kokkos> a(&i);  rshift (a,2,sync); }
// { atomic<int*,kokkos> a(&i);  andeq  (a,2,sync); }
// { atomic<int*,kokkos> a(&i);  oreq   (a,2,sync); }
// { atomic<int*,kokkos> a(&i);  xoreq  (a,2,sync); }
// { atomic<int*,kokkos> a(&i);  min    (a,&j,sync); }
// { atomic<int*,kokkos> a(&i);  max    (a,&j,sync); }
// { atomic<int*,kokkos> a(&i);  inc    (a,  sync); }
// { atomic<int*,kokkos> a(&i);  preinc (a,  sync); }
// { atomic<int*,kokkos> a(&i);  postinc(a,  sync); }
// { atomic<int*,kokkos> a(&i);  dec    (a,  sync); }
// { atomic<int*,kokkos> a(&i);  predec (a,  sync); }
// { atomic<int*,kokkos> a(&i);  postdec(a,  sync); }
// { atomic<int*,kokkos> a(&i);  add    (a,2,success,failure); }
// { atomic<int*,kokkos> a(&i);  sub    (a,2,success,failure); }
// { atomic<int*,kokkos> a(&i);  mul    (a,2,success,failure); }
// { atomic<int*,kokkos> a(&i);  div    (a,2,success,failure); }
// { atomic<int*,kokkos> a(&i);  mod    (a,2,success,failure); }
// { atomic<int*,kokkos> a(&i);  lshift (a,2,success,failure); }
// { atomic<int*,kokkos> a(&i);  rshift (a,2,success,failure); }
// { atomic<int*,kokkos> a(&i);  andeq  (a,2,success,failure); }
// { atomic<int*,kokkos> a(&i);  oreq   (a,2,success,failure); }
// { atomic<int*,kokkos> a(&i);  xoreq  (a,2,success,failure); }
// { atomic<int*,kokkos> a(&i);  min    (a,&j,success,failure); }
// { atomic<int*,kokkos> a(&i);  max    (a,&j,success,failure); }
// { atomic<int*,kokkos> a(&i);  inc    (a,  success,failure); }
// { atomic<int*,kokkos> a(&i);  preinc (a,  success,failure); }
// { atomic<int*,kokkos> a(&i);  postinc(a,  success,failure); }
// { atomic<int*,kokkos> a(&i);  dec    (a,  success,failure); }
// { atomic<int*,kokkos> a(&i);  predec (a,  success,failure); }
// { atomic<int*,kokkos> a(&i);  postdec(a,  success,failure); }
#endif

   { atomic<int*,strong> a(&i);  add    (a,2); }
   { atomic<int*,strong> a(&i);  sub    (a,2); }
// { atomic<int*,strong> a(&i);  mul    (a,2); }
// { atomic<int*,strong> a(&i);  div    (a,2); }
// { atomic<int*,strong> a(&i);  mod    (a,2); }
// { atomic<int*,strong> a(&i);  lshift (a,2); }
// { atomic<int*,strong> a(&i);  rshift (a,2); }
// { atomic<int*,strong> a(&i);  andeq  (a,2); }
// { atomic<int*,strong> a(&i);  oreq   (a,2); }
// { atomic<int*,strong> a(&i);  xoreq  (a,2); }
   { atomic<int*,strong> a(&i);  min    (a,&j); }
   { atomic<int*,strong> a(&i);  max    (a,&j); }
   { atomic<int*,strong> a(&i);  inc    (a); }
   { atomic<int*,strong> a(&i);  preinc (a); }
   { atomic<int*,strong> a(&i);  postinc(a); }
   { atomic<int*,strong> a(&i);  dec    (a); }
   { atomic<int*,strong> a(&i);  predec (a); }
   { atomic<int*,strong> a(&i);  postdec(a); }
   { atomic<int*,strong> a(&i);  add    (a,2,sync); }
   { atomic<int*,strong> a(&i);  sub    (a,2,sync); }
// { atomic<int*,strong> a(&i);  mul    (a,2,sync); }
// { atomic<int*,strong> a(&i);  div    (a,2,sync); }
// { atomic<int*,strong> a(&i);  mod    (a,2,sync); }
// { atomic<int*,strong> a(&i);  lshift (a,2,sync); }
// { atomic<int*,strong> a(&i);  rshift (a,2,sync); }
// { atomic<int*,strong> a(&i);  andeq  (a,2,sync); }
// { atomic<int*,strong> a(&i);  oreq   (a,2,sync); }
// { atomic<int*,strong> a(&i);  xoreq  (a,2,sync); }
   { atomic<int*,strong> a(&i);  min    (a,&j,sync); }
   { atomic<int*,strong> a(&i);  max    (a,&j,sync); }
   { atomic<int*,strong> a(&i);  inc    (a,  sync); }
   { atomic<int*,strong> a(&i);  preinc (a,  sync); }
   { atomic<int*,strong> a(&i);  postinc(a,  sync); }
   { atomic<int*,strong> a(&i);  dec    (a,  sync); }
   { atomic<int*,strong> a(&i);  predec (a,  sync); }
   { atomic<int*,strong> a(&i);  postdec(a,  sync); }
   { atomic<int*,strong> a(&i);  add    (a,2,success,failure); }
   { atomic<int*,strong> a(&i);  sub    (a,2,success,failure); }
// { atomic<int*,strong> a(&i);  mul    (a,2,success,failure); }
// { atomic<int*,strong> a(&i);  div    (a,2,success,failure); }
// { atomic<int*,strong> a(&i);  mod    (a,2,success,failure); }
// { atomic<int*,strong> a(&i);  lshift (a,2,success,failure); }
// { atomic<int*,strong> a(&i);  rshift (a,2,success,failure); }
// { atomic<int*,strong> a(&i);  andeq  (a,2,success,failure); }
// { atomic<int*,strong> a(&i);  oreq   (a,2,success,failure); }
// { atomic<int*,strong> a(&i);  xoreq  (a,2,success,failure); }
   { atomic<int*,strong> a(&i);  min    (a,&j,success,failure); }
   { atomic<int*,strong> a(&i);  max    (a,&j,success,failure); }
   { atomic<int*,strong> a(&i);  inc    (a,  success,failure); }
   { atomic<int*,strong> a(&i);  preinc (a,  success,failure); }
   { atomic<int*,strong> a(&i);  postinc(a,  success,failure); }
   { atomic<int*,strong> a(&i);  dec    (a,  success,failure); }
   { atomic<int*,strong> a(&i);  predec (a,  success,failure); }
   { atomic<int*,strong> a(&i);  postdec(a,  success,failure); }

   { atomic<int*,strong::pun> a(&i);  add    (a,2); }
   { atomic<int*,strong::pun> a(&i);  sub    (a,2); }
// { atomic<int*,strong::pun> a(&i);  mul    (a,2); }
// { atomic<int*,strong::pun> a(&i);  div    (a,2); }
// { atomic<int*,strong::pun> a(&i);  mod    (a,2); }
// { atomic<int*,strong::pun> a(&i);  lshift (a,2); }
// { atomic<int*,strong::pun> a(&i);  rshift (a,2); }
// { atomic<int*,strong::pun> a(&i);  andeq  (a,2); }
// { atomic<int*,strong::pun> a(&i);  oreq   (a,2); }
// { atomic<int*,strong::pun> a(&i);  xoreq  (a,2); }
   { atomic<int*,strong::pun> a(&i);  min    (a,&j); }
   { atomic<int*,strong::pun> a(&i);  max    (a,&j); }
   { atomic<int*,strong::pun> a(&i);  inc    (a); }
   { atomic<int*,strong::pun> a(&i);  preinc (a); }
   { atomic<int*,strong::pun> a(&i);  postinc(a); }
   { atomic<int*,strong::pun> a(&i);  dec    (a); }
   { atomic<int*,strong::pun> a(&i);  predec (a); }
   { atomic<int*,strong::pun> a(&i);  postdec(a); }
   { atomic<int*,strong::pun> a(&i);  add    (a,2,sync); }
   { atomic<int*,strong::pun> a(&i);  sub    (a,2,sync); }
// { atomic<int*,strong::pun> a(&i);  mul    (a,2,sync); }
// { atomic<int*,strong::pun> a(&i);  div    (a,2,sync); }
// { atomic<int*,strong::pun> a(&i);  mod    (a,2,sync); }
// { atomic<int*,strong::pun> a(&i);  lshift (a,2,sync); }
// { atomic<int*,strong::pun> a(&i);  rshift (a,2,sync); }
// { atomic<int*,strong::pun> a(&i);  andeq  (a,2,sync); }
// { atomic<int*,strong::pun> a(&i);  oreq   (a,2,sync); }
// { atomic<int*,strong::pun> a(&i);  xoreq  (a,2,sync); }
   { atomic<int*,strong::pun> a(&i);  min    (a,&j,sync); }
   { atomic<int*,strong::pun> a(&i);  max    (a,&j,sync); }
   { atomic<int*,strong::pun> a(&i);  inc    (a,  sync); }
   { atomic<int*,strong::pun> a(&i);  preinc (a,  sync); }
   { atomic<int*,strong::pun> a(&i);  postinc(a,  sync); }
   { atomic<int*,strong::pun> a(&i);  dec    (a,  sync); }
   { atomic<int*,strong::pun> a(&i);  predec (a,  sync); }
   { atomic<int*,strong::pun> a(&i);  postdec(a,  sync); }
   { atomic<int*,strong::pun> a(&i);  add    (a,2,success,failure); }
   { atomic<int*,strong::pun> a(&i);  sub    (a,2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  mul    (a,2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  div    (a,2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  mod    (a,2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  lshift (a,2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  rshift (a,2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  andeq  (a,2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  oreq   (a,2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  xoreq  (a,2,success,failure); }
   { atomic<int*,strong::pun> a(&i);  min    (a,&j,success,failure); }
   { atomic<int*,strong::pun> a(&i);  max    (a,&j,success,failure); }
   { atomic<int*,strong::pun> a(&i);  inc    (a,  success,failure); }
   { atomic<int*,strong::pun> a(&i);  preinc (a,  success,failure); }
   { atomic<int*,strong::pun> a(&i);  postinc(a,  success,failure); }
   { atomic<int*,strong::pun> a(&i);  dec    (a,  success,failure); }
   { atomic<int*,strong::pun> a(&i);  predec (a,  success,failure); }
   { atomic<int*,strong::pun> a(&i);  postdec(a,  success,failure); }

   { atomic<int*,weak> a(&i);  add    (a,2); }
   { atomic<int*,weak> a(&i);  sub    (a,2); }
// { atomic<int*,weak> a(&i);  mul    (a,2); }
// { atomic<int*,weak> a(&i);  div    (a,2); }
// { atomic<int*,weak> a(&i);  mod    (a,2); }
// { atomic<int*,weak> a(&i);  lshift (a,2); }
// { atomic<int*,weak> a(&i);  rshift (a,2); }
// { atomic<int*,weak> a(&i);  andeq  (a,2); }
// { atomic<int*,weak> a(&i);  oreq   (a,2); }
// { atomic<int*,weak> a(&i);  xoreq  (a,2); }
   { atomic<int*,weak> a(&i);  min    (a,&j); }
   { atomic<int*,weak> a(&i);  max    (a,&j); }
   { atomic<int*,weak> a(&i);  inc    (a); }
   { atomic<int*,weak> a(&i);  preinc (a); }
   { atomic<int*,weak> a(&i);  postinc(a); }
   { atomic<int*,weak> a(&i);  dec    (a); }
   { atomic<int*,weak> a(&i);  predec (a); }
   { atomic<int*,weak> a(&i);  postdec(a); }
   { atomic<int*,weak> a(&i);  add    (a,2,sync); }
   { atomic<int*,weak> a(&i);  sub    (a,2,sync); }
// { atomic<int*,weak> a(&i);  mul    (a,2,sync); }
// { atomic<int*,weak> a(&i);  div    (a,2,sync); }
// { atomic<int*,weak> a(&i);  mod    (a,2,sync); }
// { atomic<int*,weak> a(&i);  lshift (a,2,sync); }
// { atomic<int*,weak> a(&i);  rshift (a,2,sync); }
// { atomic<int*,weak> a(&i);  andeq  (a,2,sync); }
// { atomic<int*,weak> a(&i);  oreq   (a,2,sync); }
// { atomic<int*,weak> a(&i);  xoreq  (a,2,sync); }
   { atomic<int*,weak> a(&i);  min    (a,&j,sync); }
   { atomic<int*,weak> a(&i);  max    (a,&j,sync); }
   { atomic<int*,weak> a(&i);  inc    (a,  sync); }
   { atomic<int*,weak> a(&i);  preinc (a,  sync); }
   { atomic<int*,weak> a(&i);  postinc(a,  sync); }
   { atomic<int*,weak> a(&i);  dec    (a,  sync); }
   { atomic<int*,weak> a(&i);  predec (a,  sync); }
   { atomic<int*,weak> a(&i);  postdec(a,  sync); }
   { atomic<int*,weak> a(&i);  add    (a,2,success,failure); }
   { atomic<int*,weak> a(&i);  sub    (a,2,success,failure); }
// { atomic<int*,weak> a(&i);  mul    (a,2,success,failure); }
// { atomic<int*,weak> a(&i);  div    (a,2,success,failure); }
// { atomic<int*,weak> a(&i);  mod    (a,2,success,failure); }
// { atomic<int*,weak> a(&i);  lshift (a,2,success,failure); }
// { atomic<int*,weak> a(&i);  rshift (a,2,success,failure); }
// { atomic<int*,weak> a(&i);  andeq  (a,2,success,failure); }
// { atomic<int*,weak> a(&i);  oreq   (a,2,success,failure); }
// { atomic<int*,weak> a(&i);  xoreq  (a,2,success,failure); }
   { atomic<int*,weak> a(&i);  min    (a,&j,success,failure); }
   { atomic<int*,weak> a(&i);  max    (a,&j,success,failure); }
   { atomic<int*,weak> a(&i);  inc    (a,  success,failure); }
   { atomic<int*,weak> a(&i);  preinc (a,  success,failure); }
   { atomic<int*,weak> a(&i);  postinc(a,  success,failure); }
   { atomic<int*,weak> a(&i);  dec    (a,  success,failure); }
   { atomic<int*,weak> a(&i);  predec (a,  success,failure); }
   { atomic<int*,weak> a(&i);  postdec(a,  success,failure); }

   { atomic<int*,weak::pun> a(&i);  add    (a,2); }
   { atomic<int*,weak::pun> a(&i);  sub    (a,2); }
// { atomic<int*,weak::pun> a(&i);  mul    (a,2); }
// { atomic<int*,weak::pun> a(&i);  div    (a,2); }
// { atomic<int*,weak::pun> a(&i);  mod    (a,2); }
// { atomic<int*,weak::pun> a(&i);  lshift (a,2); }
// { atomic<int*,weak::pun> a(&i);  rshift (a,2); }
// { atomic<int*,weak::pun> a(&i);  andeq  (a,2); }
// { atomic<int*,weak::pun> a(&i);  oreq   (a,2); }
// { atomic<int*,weak::pun> a(&i);  xoreq  (a,2); }
   { atomic<int*,weak::pun> a(&i);  min    (a,&j); }
   { atomic<int*,weak::pun> a(&i);  max    (a,&j); }
   { atomic<int*,weak::pun> a(&i);  inc    (a); }
   { atomic<int*,weak::pun> a(&i);  preinc (a); }
   { atomic<int*,weak::pun> a(&i);  postinc(a); }
   { atomic<int*,weak::pun> a(&i);  dec    (a); }
   { atomic<int*,weak::pun> a(&i);  predec (a); }
   { atomic<int*,weak::pun> a(&i);  postdec(a); }
   { atomic<int*,weak::pun> a(&i);  add    (a,2,sync); }
   { atomic<int*,weak::pun> a(&i);  sub    (a,2,sync); }
// { atomic<int*,weak::pun> a(&i);  mul    (a,2,sync); }
// { atomic<int*,weak::pun> a(&i);  div    (a,2,sync); }
// { atomic<int*,weak::pun> a(&i);  mod    (a,2,sync); }
// { atomic<int*,weak::pun> a(&i);  lshift (a,2,sync); }
// { atomic<int*,weak::pun> a(&i);  rshift (a,2,sync); }
// { atomic<int*,weak::pun> a(&i);  andeq  (a,2,sync); }
// { atomic<int*,weak::pun> a(&i);  oreq   (a,2,sync); }
// { atomic<int*,weak::pun> a(&i);  xoreq  (a,2,sync); }
   { atomic<int*,weak::pun> a(&i);  min    (a,&j,sync); }
   { atomic<int*,weak::pun> a(&i);  max    (a,&j,sync); }
   { atomic<int*,weak::pun> a(&i);  inc    (a,  sync); }
   { atomic<int*,weak::pun> a(&i);  preinc (a,  sync); }
   { atomic<int*,weak::pun> a(&i);  postinc(a,  sync); }
   { atomic<int*,weak::pun> a(&i);  dec    (a,  sync); }
   { atomic<int*,weak::pun> a(&i);  predec (a,  sync); }
   { atomic<int*,weak::pun> a(&i);  postdec(a,  sync); }
   { atomic<int*,weak::pun> a(&i);  add    (a,2,success,failure); }
   { atomic<int*,weak::pun> a(&i);  sub    (a,2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  mul    (a,2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  div    (a,2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  mod    (a,2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  lshift (a,2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  rshift (a,2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  andeq  (a,2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  oreq   (a,2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  xoreq  (a,2,success,failure); }
   { atomic<int*,weak::pun> a(&i);  min    (a,&j,success,failure); }
   { atomic<int*,weak::pun> a(&i);  max    (a,&j,success,failure); }
   { atomic<int*,weak::pun> a(&i);  inc    (a,  success,failure); }
   { atomic<int*,weak::pun> a(&i);  preinc (a,  success,failure); }
   { atomic<int*,weak::pun> a(&i);  postinc(a,  success,failure); }
   { atomic<int*,weak::pun> a(&i);  dec    (a,  success,failure); }
   { atomic<int*,weak::pun> a(&i);  predec (a,  success,failure); }
   { atomic<int*,weak::pun> a(&i);  postdec(a,  success,failure); }

   { atomic<int*,lock> a(&i);  add    (a,2); }
   { atomic<int*,lock> a(&i);  sub    (a,2); }
// { atomic<int*,lock> a(&i);  mul    (a,2); }
// { atomic<int*,lock> a(&i);  div    (a,2); }
// { atomic<int*,lock> a(&i);  mod    (a,2); }
// { atomic<int*,lock> a(&i);  lshift (a,2); }
// { atomic<int*,lock> a(&i);  rshift (a,2); }
// { atomic<int*,lock> a(&i);  andeq  (a,2); }
// { atomic<int*,lock> a(&i);  oreq   (a,2); }
// { atomic<int*,lock> a(&i);  xoreq  (a,2); }
   { atomic<int*,lock> a(&i);  min    (a,&j); }
   { atomic<int*,lock> a(&i);  max    (a,&j); }
   { atomic<int*,lock> a(&i);  inc    (a); }
   { atomic<int*,lock> a(&i);  preinc (a); }
   { atomic<int*,lock> a(&i);  postinc(a); }
   { atomic<int*,lock> a(&i);  dec    (a); }
   { atomic<int*,lock> a(&i);  predec (a); }
   { atomic<int*,lock> a(&i);  postdec(a); }
// { atomic<int*,lock> a(&i);  add    (a,2,sync); }
// { atomic<int*,lock> a(&i);  sub    (a,2,sync); }
// { atomic<int*,lock> a(&i);  mul    (a,2,sync); }
// { atomic<int*,lock> a(&i);  div    (a,2,sync); }
// { atomic<int*,lock> a(&i);  mod    (a,2,sync); }
// { atomic<int*,lock> a(&i);  lshift (a,2,sync); }
// { atomic<int*,lock> a(&i);  rshift (a,2,sync); }
// { atomic<int*,lock> a(&i);  andeq  (a,2,sync); }
// { atomic<int*,lock> a(&i);  oreq   (a,2,sync); }
// { atomic<int*,lock> a(&i);  xoreq  (a,2,sync); }
// { atomic<int*,lock> a(&i);  min    (a,&j,sync); }
// { atomic<int*,lock> a(&i);  max    (a,&j,sync); }
// { atomic<int*,lock> a(&i);  inc    (a,  sync); }
// { atomic<int*,lock> a(&i);  preinc (a,  sync); }
// { atomic<int*,lock> a(&i);  postinc(a,  sync); }
// { atomic<int*,lock> a(&i);  dec    (a,  sync); }
// { atomic<int*,lock> a(&i);  predec (a,  sync); }
// { atomic<int*,lock> a(&i);  postdec(a,  sync); }
// { atomic<int*,lock> a(&i);  add    (a,2,success,failure); }
// { atomic<int*,lock> a(&i);  sub    (a,2,success,failure); }
// { atomic<int*,lock> a(&i);  mul    (a,2,success,failure); }
// { atomic<int*,lock> a(&i);  div    (a,2,success,failure); }
// { atomic<int*,lock> a(&i);  mod    (a,2,success,failure); }
// { atomic<int*,lock> a(&i);  lshift (a,2,success,failure); }
// { atomic<int*,lock> a(&i);  rshift (a,2,success,failure); }
// { atomic<int*,lock> a(&i);  andeq  (a,2,success,failure); }
// { atomic<int*,lock> a(&i);  oreq   (a,2,success,failure); }
// { atomic<int*,lock> a(&i);  xoreq  (a,2,success,failure); }
// { atomic<int*,lock> a(&i);  min    (a,&j,success,failure); }
// { atomic<int*,lock> a(&i);  max    (a,&j,success,failure); }
// { atomic<int*,lock> a(&i);  inc    (a,  success,failure); }
// { atomic<int*,lock> a(&i);  preinc (a,  success,failure); }
// { atomic<int*,lock> a(&i);  postinc(a,  success,failure); }
// { atomic<int*,lock> a(&i);  dec    (a,  success,failure); }
// { atomic<int*,lock> a(&i);  predec (a,  success,failure); }
// { atomic<int*,lock> a(&i);  postdec(a,  success,failure); }

   { atomic<int*,serial> a(&i);  add    (a,2); }
   { atomic<int*,serial> a(&i);  sub    (a,2); }
// { atomic<int*,serial> a(&i);  mul    (a,2); }
// { atomic<int*,serial> a(&i);  div    (a,2); }
// { atomic<int*,serial> a(&i);  mod    (a,2); }
// { atomic<int*,serial> a(&i);  lshift (a,2); }
// { atomic<int*,serial> a(&i);  rshift (a,2); }
// { atomic<int*,serial> a(&i);  andeq  (a,2); }
// { atomic<int*,serial> a(&i);  oreq   (a,2); }
// { atomic<int*,serial> a(&i);  xoreq  (a,2); }
   { atomic<int*,serial> a(&i);  min    (a,&j); }
   { atomic<int*,serial> a(&i);  max    (a,&j); }
   { atomic<int*,serial> a(&i);  inc    (a); }
   { atomic<int*,serial> a(&i);  preinc (a); }
   { atomic<int*,serial> a(&i);  postinc(a); }
   { atomic<int*,serial> a(&i);  dec    (a); }
   { atomic<int*,serial> a(&i);  predec (a); }
   { atomic<int*,serial> a(&i);  postdec(a); }
// { atomic<int*,serial> a(&i);  add    (a,2,sync); }
// { atomic<int*,serial> a(&i);  sub    (a,2,sync); }
// { atomic<int*,serial> a(&i);  mul    (a,2,sync); }
// { atomic<int*,serial> a(&i);  div    (a,2,sync); }
// { atomic<int*,serial> a(&i);  mod    (a,2,sync); }
// { atomic<int*,serial> a(&i);  lshift (a,2,sync); }
// { atomic<int*,serial> a(&i);  rshift (a,2,sync); }
// { atomic<int*,serial> a(&i);  andeq  (a,2,sync); }
// { atomic<int*,serial> a(&i);  oreq   (a,2,sync); }
// { atomic<int*,serial> a(&i);  xoreq  (a,2,sync); }
// { atomic<int*,serial> a(&i);  min    (a,&j,sync); }
// { atomic<int*,serial> a(&i);  max    (a,&j,sync); }
// { atomic<int*,serial> a(&i);  inc    (a,  sync); }
// { atomic<int*,serial> a(&i);  preinc (a,  sync); }
// { atomic<int*,serial> a(&i);  postinc(a,  sync); }
// { atomic<int*,serial> a(&i);  dec    (a,  sync); }
// { atomic<int*,serial> a(&i);  predec (a,  sync); }
// { atomic<int*,serial> a(&i);  postdec(a,  sync); }
// { atomic<int*,serial> a(&i);  add    (a,2,success,failure); }
// { atomic<int*,serial> a(&i);  sub    (a,2,success,failure); }
// { atomic<int*,serial> a(&i);  mul    (a,2,success,failure); }
// { atomic<int*,serial> a(&i);  div    (a,2,success,failure); }
// { atomic<int*,serial> a(&i);  mod    (a,2,success,failure); }
// { atomic<int*,serial> a(&i);  lshift (a,2,success,failure); }
// { atomic<int*,serial> a(&i);  rshift (a,2,success,failure); }
// { atomic<int*,serial> a(&i);  andeq  (a,2,success,failure); }
// { atomic<int*,serial> a(&i);  oreq   (a,2,success,failure); }
// { atomic<int*,serial> a(&i);  xoreq  (a,2,success,failure); }
// { atomic<int*,serial> a(&i);  min    (a,&j,success,failure); }
// { atomic<int*,serial> a(&i);  max    (a,&j,success,failure); }
// { atomic<int*,serial> a(&i);  inc    (a,  success,failure); }
// { atomic<int*,serial> a(&i);  preinc (a,  success,failure); }
// { atomic<int*,serial> a(&i);  postinc(a,  success,failure); }
// { atomic<int*,serial> a(&i);  dec    (a,  success,failure); }
// { atomic<int*,serial> a(&i);  predec (a,  success,failure); }
// { atomic<int*,serial> a(&i);  postdec(a,  success,failure); }
#endif



   // ------------------------
   // std::complex
   // ------------------------

// { atomic<cmplx,cpp> a(0);  add    (a,c); }
// { atomic<cmplx,cpp> a(0);  sub    (a,c); }
// { atomic<cmplx,cpp> a(0);  mul    (a,c); }
// { atomic<cmplx,cpp> a(0);  div    (a,c); }
// { atomic<cmplx,cpp> a(0);  mod    (a,c); }
// { atomic<cmplx,cpp> a(0);  lshift (a,c); }
// { atomic<cmplx,cpp> a(0);  rshift (a,c); }
// { atomic<cmplx,cpp> a(0);  andeq  (a,c); }
// { atomic<cmplx,cpp> a(0);  oreq   (a,c); }
// { atomic<cmplx,cpp> a(0);  xoreq  (a,c); }
// { atomic<cmplx,cpp> a(0);  min    (a,c); }
// { atomic<cmplx,cpp> a(0);  max    (a,c); }
// { atomic<cmplx,cpp> a(0);  inc    (a); }
// { atomic<cmplx,cpp> a(0);  preinc (a); }
// { atomic<cmplx,cpp> a(0);  postinc(a); }
// { atomic<cmplx,cpp> a(0);  dec    (a); }
// { atomic<cmplx,cpp> a(0);  predec (a); }
// { atomic<cmplx,cpp> a(0);  postdec(a); }
// { atomic<cmplx,cpp> a(0);  add    (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  sub    (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  mul    (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  div    (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  mod    (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  lshift (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  rshift (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  andeq  (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  oreq   (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  xoreq  (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  min    (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  max    (a,c,sync); }
// { atomic<cmplx,cpp> a(0);  inc    (a,  sync); }
// { atomic<cmplx,cpp> a(0);  preinc (a,  sync); }
// { atomic<cmplx,cpp> a(0);  postinc(a,  sync); }
// { atomic<cmplx,cpp> a(0);  dec    (a,  sync); }
// { atomic<cmplx,cpp> a(0);  predec (a,  sync); }
// { atomic<cmplx,cpp> a(0);  postdec(a,  sync); }
// { atomic<cmplx,cpp> a(0);  add    (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  sub    (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  mul    (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  div    (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  mod    (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  lshift (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  rshift (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  andeq  (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  oreq   (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  xoreq  (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  min    (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  max    (a,c,success,failure); }
// { atomic<cmplx,cpp> a(0);  inc    (a,  success,failure); }
// { atomic<cmplx,cpp> a(0);  preinc (a,  success,failure); }
// { atomic<cmplx,cpp> a(0);  postinc(a,  success,failure); }
// { atomic<cmplx,cpp> a(0);  dec    (a,  success,failure); }
// { atomic<cmplx,cpp> a(0);  predec (a,  success,failure); }
// { atomic<cmplx,cpp> a(0);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { atomic<cmplx,kokkos> a(0);  add    (a,c); }
// { atomic<cmplx,kokkos> a(0);  sub    (a,c); }
// { atomic<cmplx,kokkos> a(0);  mul    (a,c); }
// { atomic<cmplx,kokkos> a(0);  div    (a,c); }
// { atomic<cmplx,kokkos> a(0);  mod    (a,c); }
// { atomic<cmplx,kokkos> a(0);  lshift (a,c); }
// { atomic<cmplx,kokkos> a(0);  rshift (a,c); }
// { atomic<cmplx,kokkos> a(0);  andeq  (a,c); }
// { atomic<cmplx,kokkos> a(0);  oreq   (a,c); }
// { atomic<cmplx,kokkos> a(0);  xoreq  (a,c); }
// { atomic<cmplx,kokkos> a(0);  min    (a,c); }
// { atomic<cmplx,kokkos> a(0);  max    (a,c); }
// { atomic<cmplx,kokkos> a(0);  inc    (a); }
// { atomic<cmplx,kokkos> a(0);  preinc (a); }
// { atomic<cmplx,kokkos> a(0);  postinc(a); }
// { atomic<cmplx,kokkos> a(0);  dec    (a); }
// { atomic<cmplx,kokkos> a(0);  predec (a); }
// { atomic<cmplx,kokkos> a(0);  postdec(a); }
// { atomic<cmplx,kokkos> a(0);  add    (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  sub    (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  mul    (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  div    (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  mod    (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  lshift (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  rshift (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  andeq  (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  oreq   (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  xoreq  (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  min    (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  max    (a,c,sync); }
// { atomic<cmplx,kokkos> a(0);  inc    (a,  sync); }
// { atomic<cmplx,kokkos> a(0);  preinc (a,  sync); }
// { atomic<cmplx,kokkos> a(0);  postinc(a,  sync); }
// { atomic<cmplx,kokkos> a(0);  dec    (a,  sync); }
// { atomic<cmplx,kokkos> a(0);  predec (a,  sync); }
// { atomic<cmplx,kokkos> a(0);  postdec(a,  sync); }
// { atomic<cmplx,kokkos> a(0);  add    (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  sub    (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  mul    (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  div    (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  mod    (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  lshift (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  rshift (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  andeq  (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  oreq   (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  xoreq  (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  min    (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  max    (a,c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  inc    (a,  success,failure); }
// { atomic<cmplx,kokkos> a(0);  preinc (a,  success,failure); }
// { atomic<cmplx,kokkos> a(0);  postinc(a,  success,failure); }
// { atomic<cmplx,kokkos> a(0);  dec    (a,  success,failure); }
// { atomic<cmplx,kokkos> a(0);  predec (a,  success,failure); }
// { atomic<cmplx,kokkos> a(0);  postdec(a,  success,failure); }
#endif

   { atomic<cmplx,strong> a(0);  add    (a,c); }
   { atomic<cmplx,strong> a(0);  sub    (a,c); }
   { atomic<cmplx,strong> a(0);  mul    (a,c); }
   { atomic<cmplx,strong> a(0);  div    (a,c); }
// { atomic<cmplx,strong> a(0);  mod    (a,c); }
// { atomic<cmplx,strong> a(0);  lshift (a,c); }
// { atomic<cmplx,strong> a(0);  rshift (a,c); }
// { atomic<cmplx,strong> a(0);  andeq  (a,c); }
// { atomic<cmplx,strong> a(0);  oreq   (a,c); }
// { atomic<cmplx,strong> a(0);  xoreq  (a,c); }
// { atomic<cmplx,strong> a(0);  min    (a,c); }
// { atomic<cmplx,strong> a(0);  max    (a,c); }
// { atomic<cmplx,strong> a(0);  inc    (a); }
// { atomic<cmplx,strong> a(0);  preinc (a); }
// { atomic<cmplx,strong> a(0);  postinc(a); }
// { atomic<cmplx,strong> a(0);  dec    (a); }
// { atomic<cmplx,strong> a(0);  predec (a); }
// { atomic<cmplx,strong> a(0);  postdec(a); }
   { atomic<cmplx,strong> a(0);  add    (a,c,sync); }
   { atomic<cmplx,strong> a(0);  sub    (a,c,sync); }
   { atomic<cmplx,strong> a(0);  mul    (a,c,sync); }
   { atomic<cmplx,strong> a(0);  div    (a,c,sync); }
// { atomic<cmplx,strong> a(0);  mod    (a,c,sync); }
// { atomic<cmplx,strong> a(0);  lshift (a,c,sync); }
// { atomic<cmplx,strong> a(0);  rshift (a,c,sync); }
// { atomic<cmplx,strong> a(0);  andeq  (a,c,sync); }
// { atomic<cmplx,strong> a(0);  oreq   (a,c,sync); }
// { atomic<cmplx,strong> a(0);  xoreq  (a,c,sync); }
// { atomic<cmplx,strong> a(0);  min    (a,c,sync); }
// { atomic<cmplx,strong> a(0);  max    (a,c,sync); }
// { atomic<cmplx,strong> a(0);  inc    (a,  sync); }
// { atomic<cmplx,strong> a(0);  preinc (a,  sync); }
// { atomic<cmplx,strong> a(0);  postinc(a,  sync); }
// { atomic<cmplx,strong> a(0);  dec    (a,  sync); }
// { atomic<cmplx,strong> a(0);  predec (a,  sync); }
// { atomic<cmplx,strong> a(0);  postdec(a,  sync); }
   { atomic<cmplx,strong> a(0);  add    (a,c,success,failure); }
   { atomic<cmplx,strong> a(0);  sub    (a,c,success,failure); }
   { atomic<cmplx,strong> a(0);  mul    (a,c,success,failure); }
   { atomic<cmplx,strong> a(0);  div    (a,c,success,failure); }
// { atomic<cmplx,strong> a(0);  mod    (a,c,success,failure); }
// { atomic<cmplx,strong> a(0);  lshift (a,c,success,failure); }
// { atomic<cmplx,strong> a(0);  rshift (a,c,success,failure); }
// { atomic<cmplx,strong> a(0);  andeq  (a,c,success,failure); }
// { atomic<cmplx,strong> a(0);  oreq   (a,c,success,failure); }
// { atomic<cmplx,strong> a(0);  xoreq  (a,c,success,failure); }
// { atomic<cmplx,strong> a(0);  min    (a,c,success,failure); }
// { atomic<cmplx,strong> a(0);  max    (a,c,success,failure); }
// { atomic<cmplx,strong> a(0);  inc    (a,  success,failure); }
// { atomic<cmplx,strong> a(0);  preinc (a,  success,failure); }
// { atomic<cmplx,strong> a(0);  postinc(a,  success,failure); }
// { atomic<cmplx,strong> a(0);  dec    (a,  success,failure); }
// { atomic<cmplx,strong> a(0);  predec (a,  success,failure); }
// { atomic<cmplx,strong> a(0);  postdec(a,  success,failure); }

   { atomic<cmplx,strong::pun> a(0);  add    (a,c); }
   { atomic<cmplx,strong::pun> a(0);  sub    (a,c); }
   { atomic<cmplx,strong::pun> a(0);  mul    (a,c); }
   { atomic<cmplx,strong::pun> a(0);  div    (a,c); }
// { atomic<cmplx,strong::pun> a(0);  mod    (a,c); }
// { atomic<cmplx,strong::pun> a(0);  lshift (a,c); }
// { atomic<cmplx,strong::pun> a(0);  rshift (a,c); }
// { atomic<cmplx,strong::pun> a(0);  andeq  (a,c); }
// { atomic<cmplx,strong::pun> a(0);  oreq   (a,c); }
// { atomic<cmplx,strong::pun> a(0);  xoreq  (a,c); }
// { atomic<cmplx,strong::pun> a(0);  min    (a,c); }
// { atomic<cmplx,strong::pun> a(0);  max    (a,c); }
// { atomic<cmplx,strong::pun> a(0);  inc    (a); }
// { atomic<cmplx,strong::pun> a(0);  preinc (a); }
// { atomic<cmplx,strong::pun> a(0);  postinc(a); }
// { atomic<cmplx,strong::pun> a(0);  dec    (a); }
// { atomic<cmplx,strong::pun> a(0);  predec (a); }
// { atomic<cmplx,strong::pun> a(0);  postdec(a); }
   { atomic<cmplx,strong::pun> a(0);  add    (a,c,sync); }
   { atomic<cmplx,strong::pun> a(0);  sub    (a,c,sync); }
   { atomic<cmplx,strong::pun> a(0);  mul    (a,c,sync); }
   { atomic<cmplx,strong::pun> a(0);  div    (a,c,sync); }
// { atomic<cmplx,strong::pun> a(0);  mod    (a,c,sync); }
// { atomic<cmplx,strong::pun> a(0);  lshift (a,c,sync); }
// { atomic<cmplx,strong::pun> a(0);  rshift (a,c,sync); }
// { atomic<cmplx,strong::pun> a(0);  andeq  (a,c,sync); }
// { atomic<cmplx,strong::pun> a(0);  oreq   (a,c,sync); }
// { atomic<cmplx,strong::pun> a(0);  xoreq  (a,c,sync); }
// { atomic<cmplx,strong::pun> a(0);  min    (a,c,sync); }
// { atomic<cmplx,strong::pun> a(0);  max    (a,c,sync); }
// { atomic<cmplx,strong::pun> a(0);  inc    (a,  sync); }
// { atomic<cmplx,strong::pun> a(0);  preinc (a,  sync); }
// { atomic<cmplx,strong::pun> a(0);  postinc(a,  sync); }
// { atomic<cmplx,strong::pun> a(0);  dec    (a,  sync); }
// { atomic<cmplx,strong::pun> a(0);  predec (a,  sync); }
// { atomic<cmplx,strong::pun> a(0);  postdec(a,  sync); }
   { atomic<cmplx,strong::pun> a(0);  add    (a,c,success,failure); }
   { atomic<cmplx,strong::pun> a(0);  sub    (a,c,success,failure); }
   { atomic<cmplx,strong::pun> a(0);  mul    (a,c,success,failure); }
   { atomic<cmplx,strong::pun> a(0);  div    (a,c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  mod    (a,c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  lshift (a,c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  rshift (a,c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  andeq  (a,c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  oreq   (a,c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  xoreq  (a,c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  min    (a,c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  max    (a,c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  inc    (a,  success,failure); }
// { atomic<cmplx,strong::pun> a(0);  preinc (a,  success,failure); }
// { atomic<cmplx,strong::pun> a(0);  postinc(a,  success,failure); }
// { atomic<cmplx,strong::pun> a(0);  dec    (a,  success,failure); }
// { atomic<cmplx,strong::pun> a(0);  predec (a,  success,failure); }
// { atomic<cmplx,strong::pun> a(0);  postdec(a,  success,failure); }

   { atomic<cmplx,weak> a(0);  add    (a,c); }
   { atomic<cmplx,weak> a(0);  sub    (a,c); }
   { atomic<cmplx,weak> a(0);  mul    (a,c); }
   { atomic<cmplx,weak> a(0);  div    (a,c); }
// { atomic<cmplx,weak> a(0);  mod    (a,c); }
// { atomic<cmplx,weak> a(0);  lshift (a,c); }
// { atomic<cmplx,weak> a(0);  rshift (a,c); }
// { atomic<cmplx,weak> a(0);  andeq  (a,c); }
// { atomic<cmplx,weak> a(0);  oreq   (a,c); }
// { atomic<cmplx,weak> a(0);  xoreq  (a,c); }
// { atomic<cmplx,weak> a(0);  min    (a,c); }
// { atomic<cmplx,weak> a(0);  max    (a,c); }
// { atomic<cmplx,weak> a(0);  inc    (a); }
// { atomic<cmplx,weak> a(0);  preinc (a); }
// { atomic<cmplx,weak> a(0);  postinc(a); }
// { atomic<cmplx,weak> a(0);  dec    (a); }
// { atomic<cmplx,weak> a(0);  predec (a); }
// { atomic<cmplx,weak> a(0);  postdec(a); }
   { atomic<cmplx,weak> a(0);  add    (a,c,sync); }
   { atomic<cmplx,weak> a(0);  sub    (a,c,sync); }
   { atomic<cmplx,weak> a(0);  mul    (a,c,sync); }
   { atomic<cmplx,weak> a(0);  div    (a,c,sync); }
// { atomic<cmplx,weak> a(0);  mod    (a,c,sync); }
// { atomic<cmplx,weak> a(0);  lshift (a,c,sync); }
// { atomic<cmplx,weak> a(0);  rshift (a,c,sync); }
// { atomic<cmplx,weak> a(0);  andeq  (a,c,sync); }
// { atomic<cmplx,weak> a(0);  oreq   (a,c,sync); }
// { atomic<cmplx,weak> a(0);  xoreq  (a,c,sync); }
// { atomic<cmplx,weak> a(0);  min    (a,c,sync); }
// { atomic<cmplx,weak> a(0);  max    (a,c,sync); }
// { atomic<cmplx,weak> a(0);  inc    (a,  sync); }
// { atomic<cmplx,weak> a(0);  preinc (a,  sync); }
// { atomic<cmplx,weak> a(0);  postinc(a,  sync); }
// { atomic<cmplx,weak> a(0);  dec    (a,  sync); }
// { atomic<cmplx,weak> a(0);  predec (a,  sync); }
// { atomic<cmplx,weak> a(0);  postdec(a,  sync); }
   { atomic<cmplx,weak> a(0);  add    (a,c,success,failure); }
   { atomic<cmplx,weak> a(0);  sub    (a,c,success,failure); }
   { atomic<cmplx,weak> a(0);  mul    (a,c,success,failure); }
   { atomic<cmplx,weak> a(0);  div    (a,c,success,failure); }
// { atomic<cmplx,weak> a(0);  mod    (a,c,success,failure); }
// { atomic<cmplx,weak> a(0);  lshift (a,c,success,failure); }
// { atomic<cmplx,weak> a(0);  rshift (a,c,success,failure); }
// { atomic<cmplx,weak> a(0);  andeq  (a,c,success,failure); }
// { atomic<cmplx,weak> a(0);  oreq   (a,c,success,failure); }
// { atomic<cmplx,weak> a(0);  xoreq  (a,c,success,failure); }
// { atomic<cmplx,weak> a(0);  min    (a,c,success,failure); }
// { atomic<cmplx,weak> a(0);  max    (a,c,success,failure); }
// { atomic<cmplx,weak> a(0);  inc    (a,  success,failure); }
// { atomic<cmplx,weak> a(0);  preinc (a,  success,failure); }
// { atomic<cmplx,weak> a(0);  postinc(a,  success,failure); }
// { atomic<cmplx,weak> a(0);  dec    (a,  success,failure); }
// { atomic<cmplx,weak> a(0);  predec (a,  success,failure); }
// { atomic<cmplx,weak> a(0);  postdec(a,  success,failure); }

   { atomic<cmplx,weak::pun> a(0);  add    (a,c); }
   { atomic<cmplx,weak::pun> a(0);  sub    (a,c); }
   { atomic<cmplx,weak::pun> a(0);  mul    (a,c); }
   { atomic<cmplx,weak::pun> a(0);  div    (a,c); }
// { atomic<cmplx,weak::pun> a(0);  mod    (a,c); }
// { atomic<cmplx,weak::pun> a(0);  lshift (a,c); }
// { atomic<cmplx,weak::pun> a(0);  rshift (a,c); }
// { atomic<cmplx,weak::pun> a(0);  andeq  (a,c); }
// { atomic<cmplx,weak::pun> a(0);  oreq   (a,c); }
// { atomic<cmplx,weak::pun> a(0);  xoreq  (a,c); }
// { atomic<cmplx,weak::pun> a(0);  min    (a,c); }
// { atomic<cmplx,weak::pun> a(0);  max    (a,c); }
// { atomic<cmplx,weak::pun> a(0);  inc    (a); }
// { atomic<cmplx,weak::pun> a(0);  preinc (a); }
// { atomic<cmplx,weak::pun> a(0);  postinc(a); }
// { atomic<cmplx,weak::pun> a(0);  dec    (a); }
// { atomic<cmplx,weak::pun> a(0);  predec (a); }
// { atomic<cmplx,weak::pun> a(0);  postdec(a); }
   { atomic<cmplx,weak::pun> a(0);  add    (a,c,sync); }
   { atomic<cmplx,weak::pun> a(0);  sub    (a,c,sync); }
   { atomic<cmplx,weak::pun> a(0);  mul    (a,c,sync); }
   { atomic<cmplx,weak::pun> a(0);  div    (a,c,sync); }
// { atomic<cmplx,weak::pun> a(0);  mod    (a,c,sync); }
// { atomic<cmplx,weak::pun> a(0);  lshift (a,c,sync); }
// { atomic<cmplx,weak::pun> a(0);  rshift (a,c,sync); }
// { atomic<cmplx,weak::pun> a(0);  andeq  (a,c,sync); }
// { atomic<cmplx,weak::pun> a(0);  oreq   (a,c,sync); }
// { atomic<cmplx,weak::pun> a(0);  xoreq  (a,c,sync); }
// { atomic<cmplx,weak::pun> a(0);  min    (a,c,sync); }
// { atomic<cmplx,weak::pun> a(0);  max    (a,c,sync); }
// { atomic<cmplx,weak::pun> a(0);  inc    (a,  sync); }
// { atomic<cmplx,weak::pun> a(0);  preinc (a,  sync); }
// { atomic<cmplx,weak::pun> a(0);  postinc(a,  sync); }
// { atomic<cmplx,weak::pun> a(0);  dec    (a,  sync); }
// { atomic<cmplx,weak::pun> a(0);  predec (a,  sync); }
// { atomic<cmplx,weak::pun> a(0);  postdec(a,  sync); }
   { atomic<cmplx,weak::pun> a(0);  add    (a,c,success,failure); }
   { atomic<cmplx,weak::pun> a(0);  sub    (a,c,success,failure); }
   { atomic<cmplx,weak::pun> a(0);  mul    (a,c,success,failure); }
   { atomic<cmplx,weak::pun> a(0);  div    (a,c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  mod    (a,c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  lshift (a,c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  rshift (a,c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  andeq  (a,c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  oreq   (a,c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  xoreq  (a,c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  min    (a,c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  max    (a,c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  inc    (a,  success,failure); }
// { atomic<cmplx,weak::pun> a(0);  preinc (a,  success,failure); }
// { atomic<cmplx,weak::pun> a(0);  postinc(a,  success,failure); }
// { atomic<cmplx,weak::pun> a(0);  dec    (a,  success,failure); }
// { atomic<cmplx,weak::pun> a(0);  predec (a,  success,failure); }
// { atomic<cmplx,weak::pun> a(0);  postdec(a,  success,failure); }

   { atomic<cmplx,lock> a(0);  add    (a,c); }
   { atomic<cmplx,lock> a(0);  sub    (a,c); }
   { atomic<cmplx,lock> a(0);  mul    (a,c); }
   { atomic<cmplx,lock> a(0);  div    (a,c); }
// { atomic<cmplx,lock> a(0);  mod    (a,c); }
// { atomic<cmplx,lock> a(0);  lshift (a,c); }
// { atomic<cmplx,lock> a(0);  rshift (a,c); }
// { atomic<cmplx,lock> a(0);  andeq  (a,c); }
// { atomic<cmplx,lock> a(0);  oreq   (a,c); }
// { atomic<cmplx,lock> a(0);  xoreq  (a,c); }
// { atomic<cmplx,lock> a(0);  min    (a,c); }
// { atomic<cmplx,lock> a(0);  max    (a,c); }
// { atomic<cmplx,lock> a(0);  inc    (a); }
// { atomic<cmplx,lock> a(0);  preinc (a); }
// { atomic<cmplx,lock> a(0);  postinc(a); }
// { atomic<cmplx,lock> a(0);  dec    (a); }
// { atomic<cmplx,lock> a(0);  predec (a); }
// { atomic<cmplx,lock> a(0);  postdec(a); }
// { atomic<cmplx,lock> a(0);  add    (a,c,sync); }
// { atomic<cmplx,lock> a(0);  sub    (a,c,sync); }
// { atomic<cmplx,lock> a(0);  mul    (a,c,sync); }
// { atomic<cmplx,lock> a(0);  div    (a,c,sync); }
// { atomic<cmplx,lock> a(0);  mod    (a,c,sync); }
// { atomic<cmplx,lock> a(0);  lshift (a,c,sync); }
// { atomic<cmplx,lock> a(0);  rshift (a,c,sync); }
// { atomic<cmplx,lock> a(0);  andeq  (a,c,sync); }
// { atomic<cmplx,lock> a(0);  oreq   (a,c,sync); }
// { atomic<cmplx,lock> a(0);  xoreq  (a,c,sync); }
// { atomic<cmplx,lock> a(0);  min    (a,c,sync); }
// { atomic<cmplx,lock> a(0);  max    (a,c,sync); }
// { atomic<cmplx,lock> a(0);  inc    (a,  sync); }
// { atomic<cmplx,lock> a(0);  preinc (a,  sync); }
// { atomic<cmplx,lock> a(0);  postinc(a,  sync); }
// { atomic<cmplx,lock> a(0);  dec    (a,  sync); }
// { atomic<cmplx,lock> a(0);  predec (a,  sync); }
// { atomic<cmplx,lock> a(0);  postdec(a,  sync); }
// { atomic<cmplx,lock> a(0);  add    (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  sub    (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  mul    (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  div    (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  mod    (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  lshift (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  rshift (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  andeq  (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  oreq   (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  xoreq  (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  min    (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  max    (a,c,success,failure); }
// { atomic<cmplx,lock> a(0);  inc    (a,  success,failure); }
// { atomic<cmplx,lock> a(0);  preinc (a,  success,failure); }
// { atomic<cmplx,lock> a(0);  postinc(a,  success,failure); }
// { atomic<cmplx,lock> a(0);  dec    (a,  success,failure); }
// { atomic<cmplx,lock> a(0);  predec (a,  success,failure); }
// { atomic<cmplx,lock> a(0);  postdec(a,  success,failure); }

   { atomic<cmplx,serial> a(0);  add    (a,c); }
   { atomic<cmplx,serial> a(0);  sub    (a,c); }
   { atomic<cmplx,serial> a(0);  mul    (a,c); }
   { atomic<cmplx,serial> a(0);  div    (a,c); }
// { atomic<cmplx,serial> a(0);  mod    (a,c); }
// { atomic<cmplx,serial> a(0);  lshift (a,c); }
// { atomic<cmplx,serial> a(0);  rshift (a,c); }
// { atomic<cmplx,serial> a(0);  andeq  (a,c); }
// { atomic<cmplx,serial> a(0);  oreq   (a,c); }
// { atomic<cmplx,serial> a(0);  xoreq  (a,c); }
// { atomic<cmplx,serial> a(0);  min    (a,c); }
// { atomic<cmplx,serial> a(0);  max    (a,c); }
// { atomic<cmplx,serial> a(0);  inc    (a); }
// { atomic<cmplx,serial> a(0);  preinc (a); }
// { atomic<cmplx,serial> a(0);  postinc(a); }
// { atomic<cmplx,serial> a(0);  dec    (a); }
// { atomic<cmplx,serial> a(0);  predec (a); }
// { atomic<cmplx,serial> a(0);  postdec(a); }
// { atomic<cmplx,serial> a(0);  add    (a,c,sync); }
// { atomic<cmplx,serial> a(0);  sub    (a,c,sync); }
// { atomic<cmplx,serial> a(0);  mul    (a,c,sync); }
// { atomic<cmplx,serial> a(0);  div    (a,c,sync); }
// { atomic<cmplx,serial> a(0);  mod    (a,c,sync); }
// { atomic<cmplx,serial> a(0);  lshift (a,c,sync); }
// { atomic<cmplx,serial> a(0);  rshift (a,c,sync); }
// { atomic<cmplx,serial> a(0);  andeq  (a,c,sync); }
// { atomic<cmplx,serial> a(0);  oreq   (a,c,sync); }
// { atomic<cmplx,serial> a(0);  xoreq  (a,c,sync); }
// { atomic<cmplx,serial> a(0);  min    (a,c,sync); }
// { atomic<cmplx,serial> a(0);  max    (a,c,sync); }
// { atomic<cmplx,serial> a(0);  inc    (a,  sync); }
// { atomic<cmplx,serial> a(0);  preinc (a,  sync); }
// { atomic<cmplx,serial> a(0);  postinc(a,  sync); }
// { atomic<cmplx,serial> a(0);  dec    (a,  sync); }
// { atomic<cmplx,serial> a(0);  predec (a,  sync); }
// { atomic<cmplx,serial> a(0);  postdec(a,  sync); }
// { atomic<cmplx,serial> a(0);  add    (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  sub    (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  mul    (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  div    (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  mod    (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  lshift (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  rshift (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  andeq  (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  oreq   (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  xoreq  (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  min    (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  max    (a,c,success,failure); }
// { atomic<cmplx,serial> a(0);  inc    (a,  success,failure); }
// { atomic<cmplx,serial> a(0);  preinc (a,  success,failure); }
// { atomic<cmplx,serial> a(0);  postinc(a,  success,failure); }
// { atomic<cmplx,serial> a(0);  dec    (a,  success,failure); }
// { atomic<cmplx,serial> a(0);  predec (a,  success,failure); }
// { atomic<cmplx,serial> a(0);  postdec(a,  success,failure); }



   // ------------------------
   // foo
   // ------------------------

// { atomic<foo,cpp> a(0);  add    (a,b); }
// { atomic<foo,cpp> a(0);  sub    (a,b); }
// { atomic<foo,cpp> a(0);  mul    (a,b); }
// { atomic<foo,cpp> a(0);  div    (a,b); }
// { atomic<foo,cpp> a(0);  mod    (a,b); }
// { atomic<foo,cpp> a(0);  lshift (a,b); }
// { atomic<foo,cpp> a(0);  rshift (a,b); }
// { atomic<foo,cpp> a(0);  andeq  (a,b); }
// { atomic<foo,cpp> a(0);  oreq   (a,b); }
// { atomic<foo,cpp> a(0);  xoreq  (a,b); }
// { atomic<foo,cpp> a(0);  min    (a,b); }
// { atomic<foo,cpp> a(0);  max    (a,b); }
// { atomic<foo,cpp> a(0);  inc    (a); }
// { atomic<foo,cpp> a(0);  preinc (a); }
// { atomic<foo,cpp> a(0);  postinc(a); }
// { atomic<foo,cpp> a(0);  dec    (a); }
// { atomic<foo,cpp> a(0);  predec (a); }
// { atomic<foo,cpp> a(0);  postdec(a); }
// { atomic<foo,cpp> a(0);  add    (a,b,sync); }
// { atomic<foo,cpp> a(0);  sub    (a,b,sync); }
// { atomic<foo,cpp> a(0);  mul    (a,b,sync); }
// { atomic<foo,cpp> a(0);  div    (a,b,sync); }
// { atomic<foo,cpp> a(0);  mod    (a,b,sync); }
// { atomic<foo,cpp> a(0);  lshift (a,b,sync); }
// { atomic<foo,cpp> a(0);  rshift (a,b,sync); }
// { atomic<foo,cpp> a(0);  andeq  (a,b,sync); }
// { atomic<foo,cpp> a(0);  oreq   (a,b,sync); }
// { atomic<foo,cpp> a(0);  xoreq  (a,b,sync); }
// { atomic<foo,cpp> a(0);  min    (a,b,sync); }
// { atomic<foo,cpp> a(0);  max    (a,b,sync); }
// { atomic<foo,cpp> a(0);  inc    (a,  sync); }
// { atomic<foo,cpp> a(0);  preinc (a,  sync); }
// { atomic<foo,cpp> a(0);  postinc(a,  sync); }
// { atomic<foo,cpp> a(0);  dec    (a,  sync); }
// { atomic<foo,cpp> a(0);  predec (a,  sync); }
// { atomic<foo,cpp> a(0);  postdec(a,  sync); }
// { atomic<foo,cpp> a(0);  add    (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  sub    (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  mul    (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  div    (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  mod    (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  lshift (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  rshift (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  andeq  (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  oreq   (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  xoreq  (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  min    (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  max    (a,b,success,failure); }
// { atomic<foo,cpp> a(0);  inc    (a,  success,failure); }
// { atomic<foo,cpp> a(0);  preinc (a,  success,failure); }
// { atomic<foo,cpp> a(0);  postinc(a,  success,failure); }
// { atomic<foo,cpp> a(0);  dec    (a,  success,failure); }
// { atomic<foo,cpp> a(0);  predec (a,  success,failure); }
// { atomic<foo,cpp> a(0);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { atomic<foo,kokkos> a(0);  add    (a,b); }
// { atomic<foo,kokkos> a(0);  sub    (a,b); }
// { atomic<foo,kokkos> a(0);  mul    (a,b); }
// { atomic<foo,kokkos> a(0);  div    (a,b); }
// { atomic<foo,kokkos> a(0);  mod    (a,b); }
// { atomic<foo,kokkos> a(0);  lshift (a,b); }
// { atomic<foo,kokkos> a(0);  rshift (a,b); }
// { atomic<foo,kokkos> a(0);  andeq  (a,b); }
// { atomic<foo,kokkos> a(0);  oreq   (a,b); }
// { atomic<foo,kokkos> a(0);  xoreq  (a,b); }
// { atomic<foo,kokkos> a(0);  min    (a,b); }
// { atomic<foo,kokkos> a(0);  max    (a,b); }
// { atomic<foo,kokkos> a(0);  inc    (a); }
// { atomic<foo,kokkos> a(0);  preinc (a); }
// { atomic<foo,kokkos> a(0);  postinc(a); }
// { atomic<foo,kokkos> a(0);  dec    (a); }
// { atomic<foo,kokkos> a(0);  predec (a); }
// { atomic<foo,kokkos> a(0);  postdec(a); }
// { atomic<foo,kokkos> a(0);  add    (a,b,sync); }
// { atomic<foo,kokkos> a(0);  sub    (a,b,sync); }
// { atomic<foo,kokkos> a(0);  mul    (a,b,sync); }
// { atomic<foo,kokkos> a(0);  div    (a,b,sync); }
// { atomic<foo,kokkos> a(0);  mod    (a,b,sync); }
// { atomic<foo,kokkos> a(0);  lshift (a,b,sync); }
// { atomic<foo,kokkos> a(0);  rshift (a,b,sync); }
// { atomic<foo,kokkos> a(0);  andeq  (a,b,sync); }
// { atomic<foo,kokkos> a(0);  oreq   (a,b,sync); }
// { atomic<foo,kokkos> a(0);  xoreq  (a,b,sync); }
// { atomic<foo,kokkos> a(0);  min    (a,b,sync); }
// { atomic<foo,kokkos> a(0);  max    (a,b,sync); }
// { atomic<foo,kokkos> a(0);  inc    (a,  sync); }
// { atomic<foo,kokkos> a(0);  preinc (a,  sync); }
// { atomic<foo,kokkos> a(0);  postinc(a,  sync); }
// { atomic<foo,kokkos> a(0);  dec    (a,  sync); }
// { atomic<foo,kokkos> a(0);  predec (a,  sync); }
// { atomic<foo,kokkos> a(0);  postdec(a,  sync); }
// { atomic<foo,kokkos> a(0);  add    (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  sub    (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  mul    (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  div    (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  mod    (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  lshift (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  rshift (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  andeq  (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  oreq   (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  xoreq  (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  min    (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  max    (a,b,success,failure); }
// { atomic<foo,kokkos> a(0);  inc    (a,  success,failure); }
// { atomic<foo,kokkos> a(0);  preinc (a,  success,failure); }
// { atomic<foo,kokkos> a(0);  postinc(a,  success,failure); }
// { atomic<foo,kokkos> a(0);  dec    (a,  success,failure); }
// { atomic<foo,kokkos> a(0);  predec (a,  success,failure); }
// { atomic<foo,kokkos> a(0);  postdec(a,  success,failure); }
#endif

   { atomic<foo,strong> a(0);  add    (a,b); }
   { atomic<foo,strong> a(0);  sub    (a,b); }
   { atomic<foo,strong> a(0);  mul    (a,b); }
   { atomic<foo,strong> a(0);  div    (a,b); }
   { atomic<foo,strong> a(0);  mod    (a,b); }
   { atomic<foo,strong> a(0);  lshift (a,b); }
   { atomic<foo,strong> a(0);  rshift (a,b); }
   { atomic<foo,strong> a(0);  andeq  (a,b); }
   { atomic<foo,strong> a(0);  oreq   (a,b); }
   { atomic<foo,strong> a(0);  xoreq  (a,b); }
   { atomic<foo,strong> a(0);  min    (a,b); }
   { atomic<foo,strong> a(0);  max    (a,b); }
   { atomic<foo,strong> a(0);  inc    (a); }
   { atomic<foo,strong> a(0);  preinc (a); }
   { atomic<foo,strong> a(0);  postinc(a); }
   { atomic<foo,strong> a(0);  dec    (a); }
   { atomic<foo,strong> a(0);  predec (a); }
   { atomic<foo,strong> a(0);  postdec(a); }
   { atomic<foo,strong> a(0);  add    (a,b,sync); }
   { atomic<foo,strong> a(0);  sub    (a,b,sync); }
   { atomic<foo,strong> a(0);  mul    (a,b,sync); }
   { atomic<foo,strong> a(0);  div    (a,b,sync); }
   { atomic<foo,strong> a(0);  mod    (a,b,sync); }
   { atomic<foo,strong> a(0);  lshift (a,b,sync); }
   { atomic<foo,strong> a(0);  rshift (a,b,sync); }
   { atomic<foo,strong> a(0);  andeq  (a,b,sync); }
   { atomic<foo,strong> a(0);  oreq   (a,b,sync); }
   { atomic<foo,strong> a(0);  xoreq  (a,b,sync); }
   { atomic<foo,strong> a(0);  min    (a,b,sync); }
   { atomic<foo,strong> a(0);  max    (a,b,sync); }
   { atomic<foo,strong> a(0);  inc    (a,  sync); }
   { atomic<foo,strong> a(0);  preinc (a,  sync); }
   { atomic<foo,strong> a(0);  postinc(a,  sync); }
   { atomic<foo,strong> a(0);  dec    (a,  sync); }
   { atomic<foo,strong> a(0);  predec (a,  sync); }
   { atomic<foo,strong> a(0);  postdec(a,  sync); }
   { atomic<foo,strong> a(0);  add    (a,b,success,failure); }
   { atomic<foo,strong> a(0);  sub    (a,b,success,failure); }
   { atomic<foo,strong> a(0);  mul    (a,b,success,failure); }
   { atomic<foo,strong> a(0);  div    (a,b,success,failure); }
   { atomic<foo,strong> a(0);  mod    (a,b,success,failure); }
   { atomic<foo,strong> a(0);  lshift (a,b,success,failure); }
   { atomic<foo,strong> a(0);  rshift (a,b,success,failure); }
   { atomic<foo,strong> a(0);  andeq  (a,b,success,failure); }
   { atomic<foo,strong> a(0);  oreq   (a,b,success,failure); }
   { atomic<foo,strong> a(0);  xoreq  (a,b,success,failure); }
   { atomic<foo,strong> a(0);  min    (a,b,success,failure); }
   { atomic<foo,strong> a(0);  max    (a,b,success,failure); }
   { atomic<foo,strong> a(0);  inc    (a,  success,failure); }
   { atomic<foo,strong> a(0);  preinc (a,  success,failure); }
   { atomic<foo,strong> a(0);  postinc(a,  success,failure); }
   { atomic<foo,strong> a(0);  dec    (a,  success,failure); }
   { atomic<foo,strong> a(0);  predec (a,  success,failure); }
   { atomic<foo,strong> a(0);  postdec(a,  success,failure); }

   { atomic<foo,strong::pun> a(0);  add    (a,b); }
   { atomic<foo,strong::pun> a(0);  sub    (a,b); }
   { atomic<foo,strong::pun> a(0);  mul    (a,b); }
   { atomic<foo,strong::pun> a(0);  div    (a,b); }
   { atomic<foo,strong::pun> a(0);  mod    (a,b); }
   { atomic<foo,strong::pun> a(0);  lshift (a,b); }
   { atomic<foo,strong::pun> a(0);  rshift (a,b); }
   { atomic<foo,strong::pun> a(0);  andeq  (a,b); }
   { atomic<foo,strong::pun> a(0);  oreq   (a,b); }
   { atomic<foo,strong::pun> a(0);  xoreq  (a,b); }
   { atomic<foo,strong::pun> a(0);  min    (a,b); }
   { atomic<foo,strong::pun> a(0);  max    (a,b); }
   { atomic<foo,strong::pun> a(0);  inc    (a); }
   { atomic<foo,strong::pun> a(0);  preinc (a); }
   { atomic<foo,strong::pun> a(0);  postinc(a); }
   { atomic<foo,strong::pun> a(0);  dec    (a); }
   { atomic<foo,strong::pun> a(0);  predec (a); }
   { atomic<foo,strong::pun> a(0);  postdec(a); }
   { atomic<foo,strong::pun> a(0);  add    (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  sub    (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  mul    (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  div    (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  mod    (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  lshift (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  rshift (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  andeq  (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  oreq   (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  xoreq  (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  min    (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  max    (a,b,sync); }
   { atomic<foo,strong::pun> a(0);  inc    (a,  sync); }
   { atomic<foo,strong::pun> a(0);  preinc (a,  sync); }
   { atomic<foo,strong::pun> a(0);  postinc(a,  sync); }
   { atomic<foo,strong::pun> a(0);  dec    (a,  sync); }
   { atomic<foo,strong::pun> a(0);  predec (a,  sync); }
   { atomic<foo,strong::pun> a(0);  postdec(a,  sync); }
   { atomic<foo,strong::pun> a(0);  add    (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  sub    (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  mul    (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  div    (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  mod    (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  lshift (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  rshift (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  andeq  (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  oreq   (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  xoreq  (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  min    (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  max    (a,b,success,failure); }
   { atomic<foo,strong::pun> a(0);  inc    (a,  success,failure); }
   { atomic<foo,strong::pun> a(0);  preinc (a,  success,failure); }
   { atomic<foo,strong::pun> a(0);  postinc(a,  success,failure); }
   { atomic<foo,strong::pun> a(0);  dec    (a,  success,failure); }
   { atomic<foo,strong::pun> a(0);  predec (a,  success,failure); }
   { atomic<foo,strong::pun> a(0);  postdec(a,  success,failure); }

   { atomic<foo,weak> a(0);  add    (a,b); }
   { atomic<foo,weak> a(0);  sub    (a,b); }
   { atomic<foo,weak> a(0);  mul    (a,b); }
   { atomic<foo,weak> a(0);  div    (a,b); }
   { atomic<foo,weak> a(0);  mod    (a,b); }
   { atomic<foo,weak> a(0);  lshift (a,b); }
   { atomic<foo,weak> a(0);  rshift (a,b); }
   { atomic<foo,weak> a(0);  andeq  (a,b); }
   { atomic<foo,weak> a(0);  oreq   (a,b); }
   { atomic<foo,weak> a(0);  xoreq  (a,b); }
   { atomic<foo,weak> a(0);  min    (a,b); }
   { atomic<foo,weak> a(0);  max    (a,b); }
   { atomic<foo,weak> a(0);  inc    (a); }
   { atomic<foo,weak> a(0);  preinc (a); }
   { atomic<foo,weak> a(0);  postinc(a); }
   { atomic<foo,weak> a(0);  dec    (a); }
   { atomic<foo,weak> a(0);  predec (a); }
   { atomic<foo,weak> a(0);  postdec(a); }
   { atomic<foo,weak> a(0);  add    (a,b,sync); }
   { atomic<foo,weak> a(0);  sub    (a,b,sync); }
   { atomic<foo,weak> a(0);  mul    (a,b,sync); }
   { atomic<foo,weak> a(0);  div    (a,b,sync); }
   { atomic<foo,weak> a(0);  mod    (a,b,sync); }
   { atomic<foo,weak> a(0);  lshift (a,b,sync); }
   { atomic<foo,weak> a(0);  rshift (a,b,sync); }
   { atomic<foo,weak> a(0);  andeq  (a,b,sync); }
   { atomic<foo,weak> a(0);  oreq   (a,b,sync); }
   { atomic<foo,weak> a(0);  xoreq  (a,b,sync); }
   { atomic<foo,weak> a(0);  min    (a,b,sync); }
   { atomic<foo,weak> a(0);  max    (a,b,sync); }
   { atomic<foo,weak> a(0);  inc    (a,  sync); }
   { atomic<foo,weak> a(0);  preinc (a,  sync); }
   { atomic<foo,weak> a(0);  postinc(a,  sync); }
   { atomic<foo,weak> a(0);  dec    (a,  sync); }
   { atomic<foo,weak> a(0);  predec (a,  sync); }
   { atomic<foo,weak> a(0);  postdec(a,  sync); }
   { atomic<foo,weak> a(0);  add    (a,b,success,failure); }
   { atomic<foo,weak> a(0);  sub    (a,b,success,failure); }
   { atomic<foo,weak> a(0);  mul    (a,b,success,failure); }
   { atomic<foo,weak> a(0);  div    (a,b,success,failure); }
   { atomic<foo,weak> a(0);  mod    (a,b,success,failure); }
   { atomic<foo,weak> a(0);  lshift (a,b,success,failure); }
   { atomic<foo,weak> a(0);  rshift (a,b,success,failure); }
   { atomic<foo,weak> a(0);  andeq  (a,b,success,failure); }
   { atomic<foo,weak> a(0);  oreq   (a,b,success,failure); }
   { atomic<foo,weak> a(0);  xoreq  (a,b,success,failure); }
   { atomic<foo,weak> a(0);  min    (a,b,success,failure); }
   { atomic<foo,weak> a(0);  max    (a,b,success,failure); }
   { atomic<foo,weak> a(0);  inc    (a,  success,failure); }
   { atomic<foo,weak> a(0);  preinc (a,  success,failure); }
   { atomic<foo,weak> a(0);  postinc(a,  success,failure); }
   { atomic<foo,weak> a(0);  dec    (a,  success,failure); }
   { atomic<foo,weak> a(0);  predec (a,  success,failure); }
   { atomic<foo,weak> a(0);  postdec(a,  success,failure); }

   { atomic<foo,weak::pun> a(0);  add    (a,b); }
   { atomic<foo,weak::pun> a(0);  sub    (a,b); }
   { atomic<foo,weak::pun> a(0);  mul    (a,b); }
   { atomic<foo,weak::pun> a(0);  div    (a,b); }
   { atomic<foo,weak::pun> a(0);  mod    (a,b); }
   { atomic<foo,weak::pun> a(0);  lshift (a,b); }
   { atomic<foo,weak::pun> a(0);  rshift (a,b); }
   { atomic<foo,weak::pun> a(0);  andeq  (a,b); }
   { atomic<foo,weak::pun> a(0);  oreq   (a,b); }
   { atomic<foo,weak::pun> a(0);  xoreq  (a,b); }
   { atomic<foo,weak::pun> a(0);  min    (a,b); }
   { atomic<foo,weak::pun> a(0);  max    (a,b); }
   { atomic<foo,weak::pun> a(0);  inc    (a); }
   { atomic<foo,weak::pun> a(0);  preinc (a); }
   { atomic<foo,weak::pun> a(0);  postinc(a); }
   { atomic<foo,weak::pun> a(0);  dec    (a); }
   { atomic<foo,weak::pun> a(0);  predec (a); }
   { atomic<foo,weak::pun> a(0);  postdec(a); }
   { atomic<foo,weak::pun> a(0);  add    (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  sub    (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  mul    (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  div    (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  mod    (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  lshift (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  rshift (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  andeq  (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  oreq   (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  xoreq  (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  min    (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  max    (a,b,sync); }
   { atomic<foo,weak::pun> a(0);  inc    (a,  sync); }
   { atomic<foo,weak::pun> a(0);  preinc (a,  sync); }
   { atomic<foo,weak::pun> a(0);  postinc(a,  sync); }
   { atomic<foo,weak::pun> a(0);  dec    (a,  sync); }
   { atomic<foo,weak::pun> a(0);  predec (a,  sync); }
   { atomic<foo,weak::pun> a(0);  postdec(a,  sync); }
   { atomic<foo,weak::pun> a(0);  add    (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  sub    (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  mul    (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  div    (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  mod    (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  lshift (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  rshift (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  andeq  (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  oreq   (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  xoreq  (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  min    (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  max    (a,b,success,failure); }
   { atomic<foo,weak::pun> a(0);  inc    (a,  success,failure); }
   { atomic<foo,weak::pun> a(0);  preinc (a,  success,failure); }
   { atomic<foo,weak::pun> a(0);  postinc(a,  success,failure); }
   { atomic<foo,weak::pun> a(0);  dec    (a,  success,failure); }
   { atomic<foo,weak::pun> a(0);  predec (a,  success,failure); }
   { atomic<foo,weak::pun> a(0);  postdec(a,  success,failure); }

   { atomic<foo,lock> a(0);  add    (a,b); }
   { atomic<foo,lock> a(0);  sub    (a,b); }
   { atomic<foo,lock> a(0);  mul    (a,b); }
   { atomic<foo,lock> a(0);  div    (a,b); }
   { atomic<foo,lock> a(0);  mod    (a,b); }
   { atomic<foo,lock> a(0);  lshift (a,b); }
   { atomic<foo,lock> a(0);  rshift (a,b); }
   { atomic<foo,lock> a(0);  andeq  (a,b); }
   { atomic<foo,lock> a(0);  oreq   (a,b); }
   { atomic<foo,lock> a(0);  xoreq  (a,b); }
   { atomic<foo,lock> a(0);  min    (a,b); }
   { atomic<foo,lock> a(0);  max    (a,b); }
   { atomic<foo,lock> a(0);  inc    (a); }
   { atomic<foo,lock> a(0);  preinc (a); }
   { atomic<foo,lock> a(0);  postinc(a); }
   { atomic<foo,lock> a(0);  dec    (a); }
   { atomic<foo,lock> a(0);  predec (a); }
   { atomic<foo,lock> a(0);  postdec(a); }
// { atomic<foo,lock> a(0);  add    (a,b,sync); }
// { atomic<foo,lock> a(0);  sub    (a,b,sync); }
// { atomic<foo,lock> a(0);  mul    (a,b,sync); }
// { atomic<foo,lock> a(0);  div    (a,b,sync); }
// { atomic<foo,lock> a(0);  mod    (a,b,sync); }
// { atomic<foo,lock> a(0);  lshift (a,b,sync); }
// { atomic<foo,lock> a(0);  rshift (a,b,sync); }
// { atomic<foo,lock> a(0);  andeq  (a,b,sync); }
// { atomic<foo,lock> a(0);  oreq   (a,b,sync); }
// { atomic<foo,lock> a(0);  xoreq  (a,b,sync); }
// { atomic<foo,lock> a(0);  min    (a,b,sync); }
// { atomic<foo,lock> a(0);  max    (a,b,sync); }
// { atomic<foo,lock> a(0);  inc    (a,  sync); }
// { atomic<foo,lock> a(0);  preinc (a,  sync); }
// { atomic<foo,lock> a(0);  postinc(a,  sync); }
// { atomic<foo,lock> a(0);  dec    (a,  sync); }
// { atomic<foo,lock> a(0);  predec (a,  sync); }
// { atomic<foo,lock> a(0);  postdec(a,  sync); }
// { atomic<foo,lock> a(0);  add    (a,b,success,failure); }
// { atomic<foo,lock> a(0);  sub    (a,b,success,failure); }
// { atomic<foo,lock> a(0);  mul    (a,b,success,failure); }
// { atomic<foo,lock> a(0);  div    (a,b,success,failure); }
// { atomic<foo,lock> a(0);  mod    (a,b,success,failure); }
// { atomic<foo,lock> a(0);  lshift (a,b,success,failure); }
// { atomic<foo,lock> a(0);  rshift (a,b,success,failure); }
// { atomic<foo,lock> a(0);  andeq  (a,b,success,failure); }
// { atomic<foo,lock> a(0);  oreq   (a,b,success,failure); }
// { atomic<foo,lock> a(0);  xoreq  (a,b,success,failure); }
// { atomic<foo,lock> a(0);  min    (a,b,success,failure); }
// { atomic<foo,lock> a(0);  max    (a,b,success,failure); }
// { atomic<foo,lock> a(0);  inc    (a,  success,failure); }
// { atomic<foo,lock> a(0);  preinc (a,  success,failure); }
// { atomic<foo,lock> a(0);  postinc(a,  success,failure); }
// { atomic<foo,lock> a(0);  dec    (a,  success,failure); }
// { atomic<foo,lock> a(0);  predec (a,  success,failure); }
// { atomic<foo,lock> a(0);  postdec(a,  success,failure); }

   { atomic<foo,serial> a(0);  add    (a,b); }
   { atomic<foo,serial> a(0);  sub    (a,b); }
   { atomic<foo,serial> a(0);  mul    (a,b); }
   { atomic<foo,serial> a(0);  div    (a,b); }
   { atomic<foo,serial> a(0);  mod    (a,b); }
   { atomic<foo,serial> a(0);  lshift (a,b); }
   { atomic<foo,serial> a(0);  rshift (a,b); }
   { atomic<foo,serial> a(0);  andeq  (a,b); }
   { atomic<foo,serial> a(0);  oreq   (a,b); }
   { atomic<foo,serial> a(0);  xoreq  (a,b); }
   { atomic<foo,serial> a(0);  min    (a,b); }
   { atomic<foo,serial> a(0);  max    (a,b); }
   { atomic<foo,serial> a(0);  inc    (a); }
   { atomic<foo,serial> a(0);  preinc (a); }
   { atomic<foo,serial> a(0);  postinc(a); }
   { atomic<foo,serial> a(0);  dec    (a); }
   { atomic<foo,serial> a(0);  predec (a); }
   { atomic<foo,serial> a(0);  postdec(a); }
// { atomic<foo,serial> a(0);  add    (a,b,sync); }
// { atomic<foo,serial> a(0);  sub    (a,b,sync); }
// { atomic<foo,serial> a(0);  mul    (a,b,sync); }
// { atomic<foo,serial> a(0);  div    (a,b,sync); }
// { atomic<foo,serial> a(0);  mod    (a,b,sync); }
// { atomic<foo,serial> a(0);  lshift (a,b,sync); }
// { atomic<foo,serial> a(0);  rshift (a,b,sync); }
// { atomic<foo,serial> a(0);  andeq  (a,b,sync); }
// { atomic<foo,serial> a(0);  oreq   (a,b,sync); }
// { atomic<foo,serial> a(0);  xoreq  (a,b,sync); }
// { atomic<foo,serial> a(0);  min    (a,b,sync); }
// { atomic<foo,serial> a(0);  max    (a,b,sync); }
// { atomic<foo,serial> a(0);  inc    (a,  sync); }
// { atomic<foo,serial> a(0);  preinc (a,  sync); }
// { atomic<foo,serial> a(0);  postinc(a,  sync); }
// { atomic<foo,serial> a(0);  dec    (a,  sync); }
// { atomic<foo,serial> a(0);  predec (a,  sync); }
// { atomic<foo,serial> a(0);  postdec(a,  sync); }
// { atomic<foo,serial> a(0);  add    (a,b,success,failure); }
// { atomic<foo,serial> a(0);  sub    (a,b,success,failure); }
// { atomic<foo,serial> a(0);  mul    (a,b,success,failure); }
// { atomic<foo,serial> a(0);  div    (a,b,success,failure); }
// { atomic<foo,serial> a(0);  mod    (a,b,success,failure); }
// { atomic<foo,serial> a(0);  lshift (a,b,success,failure); }
// { atomic<foo,serial> a(0);  rshift (a,b,success,failure); }
// { atomic<foo,serial> a(0);  andeq  (a,b,success,failure); }
// { atomic<foo,serial> a(0);  oreq   (a,b,success,failure); }
// { atomic<foo,serial> a(0);  xoreq  (a,b,success,failure); }
// { atomic<foo,serial> a(0);  min    (a,b,success,failure); }
// { atomic<foo,serial> a(0);  max    (a,b,success,failure); }
// { atomic<foo,serial> a(0);  inc    (a,  success,failure); }
// { atomic<foo,serial> a(0);  preinc (a,  success,failure); }
// { atomic<foo,serial> a(0);  postinc(a,  success,failure); }
// { atomic<foo,serial> a(0);  dec    (a,  success,failure); }
// { atomic<foo,serial> a(0);  predec (a,  success,failure); }
// { atomic<foo,serial> a(0);  postdec(a,  success,failure); }



   // --------------------------------------------------------------------------
   // volatile
   // --------------------------------------------------------------------------

   // ------------------------
   // int
   // ------------------------

   { volatile atomic<int,cpp> a(0);  add    (a,2); }
   { volatile atomic<int,cpp> a(0);  sub    (a,2); }
// { volatile atomic<int,cpp> a(0);  mul    (a,2); }
// { volatile atomic<int,cpp> a(0);  div    (a,2); }
// { volatile atomic<int,cpp> a(0);  mod    (a,2); }
// { volatile atomic<int,cpp> a(0);  lshift (a,2); }
// { volatile atomic<int,cpp> a(0);  rshift (a,2); }
   { volatile atomic<int,cpp> a(0);  andeq  (a,2); }
   { volatile atomic<int,cpp> a(0);  oreq   (a,2); }
   { volatile atomic<int,cpp> a(0);  xoreq  (a,2); }
// { volatile atomic<int,cpp> a(0);  min    (a,2); }
// { volatile atomic<int,cpp> a(0);  max    (a,2); }
   { volatile atomic<int,cpp> a(0);  inc    (a); }
   { volatile atomic<int,cpp> a(0);  preinc (a); }
   { volatile atomic<int,cpp> a(0);  postinc(a); }
   { volatile atomic<int,cpp> a(0);  dec    (a); }
   { volatile atomic<int,cpp> a(0);  predec (a); }
   { volatile atomic<int,cpp> a(0);  postdec(a); }
   { volatile atomic<int,cpp> a(0);  add    (a,2,sync); }
   { volatile atomic<int,cpp> a(0);  sub    (a,2,sync); }
// { volatile atomic<int,cpp> a(0);  mul    (a,2,sync); }
// { volatile atomic<int,cpp> a(0);  div    (a,2,sync); }
// { volatile atomic<int,cpp> a(0);  mod    (a,2,sync); }
// { volatile atomic<int,cpp> a(0);  lshift (a,2,sync); }
// { volatile atomic<int,cpp> a(0);  rshift (a,2,sync); }
   { volatile atomic<int,cpp> a(0);  andeq  (a,2,sync); }
   { volatile atomic<int,cpp> a(0);  oreq   (a,2,sync); }
   { volatile atomic<int,cpp> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<int,cpp> a(0);  min    (a,2,sync); }
// { volatile atomic<int,cpp> a(0);  max    (a,2,sync); }
// { volatile atomic<int,cpp> a(0);  inc    (a,  sync); }
// { volatile atomic<int,cpp> a(0);  preinc (a,  sync); }
// { volatile atomic<int,cpp> a(0);  postinc(a,  sync); }
// { volatile atomic<int,cpp> a(0);  dec    (a,  sync); }
// { volatile atomic<int,cpp> a(0);  predec (a,  sync); }
// { volatile atomic<int,cpp> a(0);  postdec(a,  sync); }
// { volatile atomic<int,cpp> a(0);  add    (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  div    (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  min    (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  max    (a,2,success,failure); }
// { volatile atomic<int,cpp> a(0);  inc    (a,  success,failure); }
// { volatile atomic<int,cpp> a(0);  preinc (a,  success,failure); }
// { volatile atomic<int,cpp> a(0);  postinc(a,  success,failure); }
// { volatile atomic<int,cpp> a(0);  dec    (a,  success,failure); }
// { volatile atomic<int,cpp> a(0);  predec (a,  success,failure); }
// { volatile atomic<int,cpp> a(0);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { volatile atomic<int,kokkos> a(0);  add    (a,2); }
   { volatile atomic<int,kokkos> a(0);  sub    (a,2); }
   { volatile atomic<int,kokkos> a(0);  mul    (a,2); }
   { volatile atomic<int,kokkos> a(0);  div    (a,2); }
   { volatile atomic<int,kokkos> a(0);  mod    (a,2); }
   { volatile atomic<int,kokkos> a(0);  lshift (a,2); }
   { volatile atomic<int,kokkos> a(0);  rshift (a,2); }
   { volatile atomic<int,kokkos> a(0);  andeq  (a,2); }
   { volatile atomic<int,kokkos> a(0);  oreq   (a,2); }
   { volatile atomic<int,kokkos> a(0);  xoreq  (a,2); }
   { volatile atomic<int,kokkos> a(0);  min    (a,2); }
   { volatile atomic<int,kokkos> a(0);  max    (a,2); }
   { volatile atomic<int,kokkos> a(0);  inc    (a); }
   { volatile atomic<int,kokkos> a(0);  preinc (a); }
   { volatile atomic<int,kokkos> a(0);  postinc(a); }
   { volatile atomic<int,kokkos> a(0);  dec    (a); }
   { volatile atomic<int,kokkos> a(0);  predec (a); }
   { volatile atomic<int,kokkos> a(0);  postdec(a); }
// { volatile atomic<int,kokkos> a(0);  add    (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  sub    (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  mul    (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  div    (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  mod    (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  lshift (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  rshift (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  andeq  (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  oreq   (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  min    (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  max    (a,2,sync); }
// { volatile atomic<int,kokkos> a(0);  inc    (a,  sync); }
// { volatile atomic<int,kokkos> a(0);  preinc (a,  sync); }
// { volatile atomic<int,kokkos> a(0);  postinc(a,  sync); }
// { volatile atomic<int,kokkos> a(0);  dec    (a,  sync); }
// { volatile atomic<int,kokkos> a(0);  predec (a,  sync); }
// { volatile atomic<int,kokkos> a(0);  postdec(a,  sync); }
// { volatile atomic<int,kokkos> a(0);  add    (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  div    (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  min    (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  max    (a,2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  inc    (a,  success,failure); }
// { volatile atomic<int,kokkos> a(0);  preinc (a,  success,failure); }
// { volatile atomic<int,kokkos> a(0);  postinc(a,  success,failure); }
// { volatile atomic<int,kokkos> a(0);  dec    (a,  success,failure); }
// { volatile atomic<int,kokkos> a(0);  predec (a,  success,failure); }
// { volatile atomic<int,kokkos> a(0);  postdec(a,  success,failure); }
#endif

   { volatile atomic<int,strong> a(0);  add    (a,2); }
   { volatile atomic<int,strong> a(0);  sub    (a,2); }
   { volatile atomic<int,strong> a(0);  mul    (a,2); }
   { volatile atomic<int,strong> a(0);  div    (a,2); }
   { volatile atomic<int,strong> a(0);  mod    (a,2); }
   { volatile atomic<int,strong> a(0);  lshift (a,2); }
   { volatile atomic<int,strong> a(0);  rshift (a,2); }
   { volatile atomic<int,strong> a(0);  andeq  (a,2); }
   { volatile atomic<int,strong> a(0);  oreq   (a,2); }
   { volatile atomic<int,strong> a(0);  xoreq  (a,2); }
   { volatile atomic<int,strong> a(0);  min    (a,2); }
   { volatile atomic<int,strong> a(0);  max    (a,2); }
   { volatile atomic<int,strong> a(0);  inc    (a); }
   { volatile atomic<int,strong> a(0);  preinc (a); }
   { volatile atomic<int,strong> a(0);  postinc(a); }
   { volatile atomic<int,strong> a(0);  dec    (a); }
   { volatile atomic<int,strong> a(0);  predec (a); }
   { volatile atomic<int,strong> a(0);  postdec(a); }
   { volatile atomic<int,strong> a(0);  add    (a,2,sync); }
   { volatile atomic<int,strong> a(0);  sub    (a,2,sync); }
   { volatile atomic<int,strong> a(0);  mul    (a,2,sync); }
   { volatile atomic<int,strong> a(0);  div    (a,2,sync); }
   { volatile atomic<int,strong> a(0);  mod    (a,2,sync); }
   { volatile atomic<int,strong> a(0);  lshift (a,2,sync); }
   { volatile atomic<int,strong> a(0);  rshift (a,2,sync); }
   { volatile atomic<int,strong> a(0);  andeq  (a,2,sync); }
   { volatile atomic<int,strong> a(0);  oreq   (a,2,sync); }
   { volatile atomic<int,strong> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<int,strong> a(0);  min    (a,2,sync); }
   { volatile atomic<int,strong> a(0);  max    (a,2,sync); }
   { volatile atomic<int,strong> a(0);  inc    (a,  sync); }
   { volatile atomic<int,strong> a(0);  preinc (a,  sync); }
   { volatile atomic<int,strong> a(0);  postinc(a,  sync); }
   { volatile atomic<int,strong> a(0);  dec    (a,  sync); }
   { volatile atomic<int,strong> a(0);  predec (a,  sync); }
   { volatile atomic<int,strong> a(0);  postdec(a,  sync); }
   { volatile atomic<int,strong> a(0);  add    (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  div    (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  mod    (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  lshift (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  rshift (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  andeq  (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  oreq   (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  min    (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  max    (a,2,success,failure); }
   { volatile atomic<int,strong> a(0);  inc    (a,  success,failure); }
   { volatile atomic<int,strong> a(0);  preinc (a,  success,failure); }
   { volatile atomic<int,strong> a(0);  postinc(a,  success,failure); }
   { volatile atomic<int,strong> a(0);  dec    (a,  success,failure); }
   { volatile atomic<int,strong> a(0);  predec (a,  success,failure); }
   { volatile atomic<int,strong> a(0);  postdec(a,  success,failure); }

   { volatile atomic<int,strong::pun> a(0);  add    (a,2); }
   { volatile atomic<int,strong::pun> a(0);  sub    (a,2); }
   { volatile atomic<int,strong::pun> a(0);  mul    (a,2); }
   { volatile atomic<int,strong::pun> a(0);  div    (a,2); }
   { volatile atomic<int,strong::pun> a(0);  mod    (a,2); }
   { volatile atomic<int,strong::pun> a(0);  lshift (a,2); }
   { volatile atomic<int,strong::pun> a(0);  rshift (a,2); }
   { volatile atomic<int,strong::pun> a(0);  andeq  (a,2); }
   { volatile atomic<int,strong::pun> a(0);  oreq   (a,2); }
   { volatile atomic<int,strong::pun> a(0);  xoreq  (a,2); }
   { volatile atomic<int,strong::pun> a(0);  min    (a,2); }
   { volatile atomic<int,strong::pun> a(0);  max    (a,2); }
   { volatile atomic<int,strong::pun> a(0);  inc    (a); }
   { volatile atomic<int,strong::pun> a(0);  preinc (a); }
   { volatile atomic<int,strong::pun> a(0);  postinc(a); }
   { volatile atomic<int,strong::pun> a(0);  dec    (a); }
   { volatile atomic<int,strong::pun> a(0);  predec (a); }
   { volatile atomic<int,strong::pun> a(0);  postdec(a); }
   { volatile atomic<int,strong::pun> a(0);  add    (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  sub    (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  mul    (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  div    (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  mod    (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  lshift (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  rshift (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  andeq  (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  oreq   (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  min    (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  max    (a,2,sync); }
   { volatile atomic<int,strong::pun> a(0);  inc    (a,  sync); }
   { volatile atomic<int,strong::pun> a(0);  preinc (a,  sync); }
   { volatile atomic<int,strong::pun> a(0);  postinc(a,  sync); }
   { volatile atomic<int,strong::pun> a(0);  dec    (a,  sync); }
   { volatile atomic<int,strong::pun> a(0);  predec (a,  sync); }
   { volatile atomic<int,strong::pun> a(0);  postdec(a,  sync); }
   { volatile atomic<int,strong::pun> a(0);  add    (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  div    (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  mod    (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  lshift (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  rshift (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  andeq  (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  oreq   (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  min    (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  max    (a,2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  inc    (a,  success,failure); }
   { volatile atomic<int,strong::pun> a(0);  preinc (a,  success,failure); }
   { volatile atomic<int,strong::pun> a(0);  postinc(a,  success,failure); }
   { volatile atomic<int,strong::pun> a(0);  dec    (a,  success,failure); }
   { volatile atomic<int,strong::pun> a(0);  predec (a,  success,failure); }
   { volatile atomic<int,strong::pun> a(0);  postdec(a,  success,failure); }

   { volatile atomic<int,weak> a(0);  add    (a,2); }
   { volatile atomic<int,weak> a(0);  sub    (a,2); }
   { volatile atomic<int,weak> a(0);  mul    (a,2); }
   { volatile atomic<int,weak> a(0);  div    (a,2); }
   { volatile atomic<int,weak> a(0);  mod    (a,2); }
   { volatile atomic<int,weak> a(0);  lshift (a,2); }
   { volatile atomic<int,weak> a(0);  rshift (a,2); }
   { volatile atomic<int,weak> a(0);  andeq  (a,2); }
   { volatile atomic<int,weak> a(0);  oreq   (a,2); }
   { volatile atomic<int,weak> a(0);  xoreq  (a,2); }
   { volatile atomic<int,weak> a(0);  min    (a,2); }
   { volatile atomic<int,weak> a(0);  max    (a,2); }
   { volatile atomic<int,weak> a(0);  inc    (a); }
   { volatile atomic<int,weak> a(0);  preinc (a); }
   { volatile atomic<int,weak> a(0);  postinc(a); }
   { volatile atomic<int,weak> a(0);  dec    (a); }
   { volatile atomic<int,weak> a(0);  predec (a); }
   { volatile atomic<int,weak> a(0);  postdec(a); }
   { volatile atomic<int,weak> a(0);  add    (a,2,sync); }
   { volatile atomic<int,weak> a(0);  sub    (a,2,sync); }
   { volatile atomic<int,weak> a(0);  mul    (a,2,sync); }
   { volatile atomic<int,weak> a(0);  div    (a,2,sync); }
   { volatile atomic<int,weak> a(0);  mod    (a,2,sync); }
   { volatile atomic<int,weak> a(0);  lshift (a,2,sync); }
   { volatile atomic<int,weak> a(0);  rshift (a,2,sync); }
   { volatile atomic<int,weak> a(0);  andeq  (a,2,sync); }
   { volatile atomic<int,weak> a(0);  oreq   (a,2,sync); }
   { volatile atomic<int,weak> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<int,weak> a(0);  min    (a,2,sync); }
   { volatile atomic<int,weak> a(0);  max    (a,2,sync); }
   { volatile atomic<int,weak> a(0);  inc    (a,  sync); }
   { volatile atomic<int,weak> a(0);  preinc (a,  sync); }
   { volatile atomic<int,weak> a(0);  postinc(a,  sync); }
   { volatile atomic<int,weak> a(0);  dec    (a,  sync); }
   { volatile atomic<int,weak> a(0);  predec (a,  sync); }
   { volatile atomic<int,weak> a(0);  postdec(a,  sync); }
   { volatile atomic<int,weak> a(0);  add    (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  div    (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  mod    (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  lshift (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  rshift (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  andeq  (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  oreq   (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  min    (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  max    (a,2,success,failure); }
   { volatile atomic<int,weak> a(0);  inc    (a,  success,failure); }
   { volatile atomic<int,weak> a(0);  preinc (a,  success,failure); }
   { volatile atomic<int,weak> a(0);  postinc(a,  success,failure); }
   { volatile atomic<int,weak> a(0);  dec    (a,  success,failure); }
   { volatile atomic<int,weak> a(0);  predec (a,  success,failure); }
   { volatile atomic<int,weak> a(0);  postdec(a,  success,failure); }

   { volatile atomic<int,weak::pun> a(0);  add    (a,2); }
   { volatile atomic<int,weak::pun> a(0);  sub    (a,2); }
   { volatile atomic<int,weak::pun> a(0);  mul    (a,2); }
   { volatile atomic<int,weak::pun> a(0);  div    (a,2); }
   { volatile atomic<int,weak::pun> a(0);  mod    (a,2); }
   { volatile atomic<int,weak::pun> a(0);  lshift (a,2); }
   { volatile atomic<int,weak::pun> a(0);  rshift (a,2); }
   { volatile atomic<int,weak::pun> a(0);  andeq  (a,2); }
   { volatile atomic<int,weak::pun> a(0);  oreq   (a,2); }
   { volatile atomic<int,weak::pun> a(0);  xoreq  (a,2); }
   { volatile atomic<int,weak::pun> a(0);  min    (a,2); }
   { volatile atomic<int,weak::pun> a(0);  max    (a,2); }
   { volatile atomic<int,weak::pun> a(0);  inc    (a); }
   { volatile atomic<int,weak::pun> a(0);  preinc (a); }
   { volatile atomic<int,weak::pun> a(0);  postinc(a); }
   { volatile atomic<int,weak::pun> a(0);  dec    (a); }
   { volatile atomic<int,weak::pun> a(0);  predec (a); }
   { volatile atomic<int,weak::pun> a(0);  postdec(a); }
   { volatile atomic<int,weak::pun> a(0);  add    (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  sub    (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  mul    (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  div    (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  mod    (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  lshift (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  rshift (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  andeq  (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  oreq   (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  min    (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  max    (a,2,sync); }
   { volatile atomic<int,weak::pun> a(0);  inc    (a,  sync); }
   { volatile atomic<int,weak::pun> a(0);  preinc (a,  sync); }
   { volatile atomic<int,weak::pun> a(0);  postinc(a,  sync); }
   { volatile atomic<int,weak::pun> a(0);  dec    (a,  sync); }
   { volatile atomic<int,weak::pun> a(0);  predec (a,  sync); }
   { volatile atomic<int,weak::pun> a(0);  postdec(a,  sync); }
   { volatile atomic<int,weak::pun> a(0);  add    (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  div    (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  mod    (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  lshift (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  rshift (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  andeq  (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  oreq   (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  min    (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  max    (a,2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  inc    (a,  success,failure); }
   { volatile atomic<int,weak::pun> a(0);  preinc (a,  success,failure); }
   { volatile atomic<int,weak::pun> a(0);  postinc(a,  success,failure); }
   { volatile atomic<int,weak::pun> a(0);  dec    (a,  success,failure); }
   { volatile atomic<int,weak::pun> a(0);  predec (a,  success,failure); }
   { volatile atomic<int,weak::pun> a(0);  postdec(a,  success,failure); }

   { volatile atomic<int,lock> a(0);  add    (a,2); }
   { volatile atomic<int,lock> a(0);  sub    (a,2); }
   { volatile atomic<int,lock> a(0);  mul    (a,2); }
   { volatile atomic<int,lock> a(0);  div    (a,2); }
   { volatile atomic<int,lock> a(0);  mod    (a,2); }
   { volatile atomic<int,lock> a(0);  lshift (a,2); }
   { volatile atomic<int,lock> a(0);  rshift (a,2); }
   { volatile atomic<int,lock> a(0);  andeq  (a,2); }
   { volatile atomic<int,lock> a(0);  oreq   (a,2); }
   { volatile atomic<int,lock> a(0);  xoreq  (a,2); }
   { volatile atomic<int,lock> a(0);  min    (a,2); }
   { volatile atomic<int,lock> a(0);  max    (a,2); }
   { volatile atomic<int,lock> a(0);  inc    (a); }
   { volatile atomic<int,lock> a(0);  preinc (a); }
   { volatile atomic<int,lock> a(0);  postinc(a); }
   { volatile atomic<int,lock> a(0);  dec    (a); }
   { volatile atomic<int,lock> a(0);  predec (a); }
   { volatile atomic<int,lock> a(0);  postdec(a); }
// { volatile atomic<int,lock> a(0);  add    (a,2,sync); }
// { volatile atomic<int,lock> a(0);  sub    (a,2,sync); }
// { volatile atomic<int,lock> a(0);  mul    (a,2,sync); }
// { volatile atomic<int,lock> a(0);  div    (a,2,sync); }
// { volatile atomic<int,lock> a(0);  mod    (a,2,sync); }
// { volatile atomic<int,lock> a(0);  lshift (a,2,sync); }
// { volatile atomic<int,lock> a(0);  rshift (a,2,sync); }
// { volatile atomic<int,lock> a(0);  andeq  (a,2,sync); }
// { volatile atomic<int,lock> a(0);  oreq   (a,2,sync); }
// { volatile atomic<int,lock> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<int,lock> a(0);  min    (a,2,sync); }
// { volatile atomic<int,lock> a(0);  max    (a,2,sync); }
// { volatile atomic<int,lock> a(0);  inc    (a,  sync); }
// { volatile atomic<int,lock> a(0);  preinc (a,  sync); }
// { volatile atomic<int,lock> a(0);  postinc(a,  sync); }
// { volatile atomic<int,lock> a(0);  dec    (a,  sync); }
// { volatile atomic<int,lock> a(0);  predec (a,  sync); }
// { volatile atomic<int,lock> a(0);  postdec(a,  sync); }
// { volatile atomic<int,lock> a(0);  add    (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  div    (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  min    (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  max    (a,2,success,failure); }
// { volatile atomic<int,lock> a(0);  inc    (a,  success,failure); }
// { volatile atomic<int,lock> a(0);  preinc (a,  success,failure); }
// { volatile atomic<int,lock> a(0);  postinc(a,  success,failure); }
// { volatile atomic<int,lock> a(0);  dec    (a,  success,failure); }
// { volatile atomic<int,lock> a(0);  predec (a,  success,failure); }
// { volatile atomic<int,lock> a(0);  postdec(a,  success,failure); }

   { volatile atomic<int,serial> a(0);  add    (a,2); }
   { volatile atomic<int,serial> a(0);  sub    (a,2); }
   { volatile atomic<int,serial> a(0);  mul    (a,2); }
   { volatile atomic<int,serial> a(0);  div    (a,2); }
   { volatile atomic<int,serial> a(0);  mod    (a,2); }
   { volatile atomic<int,serial> a(0);  lshift (a,2); }
   { volatile atomic<int,serial> a(0);  rshift (a,2); }
   { volatile atomic<int,serial> a(0);  andeq  (a,2); }
   { volatile atomic<int,serial> a(0);  oreq   (a,2); }
   { volatile atomic<int,serial> a(0);  xoreq  (a,2); }
   { volatile atomic<int,serial> a(0);  min    (a,2); }
   { volatile atomic<int,serial> a(0);  max    (a,2); }
   { volatile atomic<int,serial> a(0);  inc    (a); }
   { volatile atomic<int,serial> a(0);  preinc (a); }
   { volatile atomic<int,serial> a(0);  postinc(a); }
   { volatile atomic<int,serial> a(0);  dec    (a); }
   { volatile atomic<int,serial> a(0);  predec (a); }
   { volatile atomic<int,serial> a(0);  postdec(a); }
// { volatile atomic<int,serial> a(0);  add    (a,2,sync); }
// { volatile atomic<int,serial> a(0);  sub    (a,2,sync); }
// { volatile atomic<int,serial> a(0);  mul    (a,2,sync); }
// { volatile atomic<int,serial> a(0);  div    (a,2,sync); }
// { volatile atomic<int,serial> a(0);  mod    (a,2,sync); }
// { volatile atomic<int,serial> a(0);  lshift (a,2,sync); }
// { volatile atomic<int,serial> a(0);  rshift (a,2,sync); }
// { volatile atomic<int,serial> a(0);  andeq  (a,2,sync); }
// { volatile atomic<int,serial> a(0);  oreq   (a,2,sync); }
// { volatile atomic<int,serial> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<int,serial> a(0);  min    (a,2,sync); }
// { volatile atomic<int,serial> a(0);  max    (a,2,sync); }
// { volatile atomic<int,serial> a(0);  inc    (a,  sync); }
// { volatile atomic<int,serial> a(0);  preinc (a,  sync); }
// { volatile atomic<int,serial> a(0);  postinc(a,  sync); }
// { volatile atomic<int,serial> a(0);  dec    (a,  sync); }
// { volatile atomic<int,serial> a(0);  predec (a,  sync); }
// { volatile atomic<int,serial> a(0);  postdec(a,  sync); }
// { volatile atomic<int,serial> a(0);  add    (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  div    (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  min    (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  max    (a,2,success,failure); }
// { volatile atomic<int,serial> a(0);  inc    (a,  success,failure); }
// { volatile atomic<int,serial> a(0);  preinc (a,  success,failure); }
// { volatile atomic<int,serial> a(0);  postinc(a,  success,failure); }
// { volatile atomic<int,serial> a(0);  dec    (a,  success,failure); }
// { volatile atomic<int,serial> a(0);  predec (a,  success,failure); }
// { volatile atomic<int,serial> a(0);  postdec(a,  success,failure); }



   // ------------------------
   // ulong
   // ------------------------

   { volatile atomic<ulong,cpp> a(0);  add    (a,2); }
   { volatile atomic<ulong,cpp> a(0);  sub    (a,2); }
// { volatile atomic<ulong,cpp> a(0);  mul    (a,2); }
// { volatile atomic<ulong,cpp> a(0);  div    (a,2); }
// { volatile atomic<ulong,cpp> a(0);  mod    (a,2); }
// { volatile atomic<ulong,cpp> a(0);  lshift (a,2); }
// { volatile atomic<ulong,cpp> a(0);  rshift (a,2); }
   { volatile atomic<ulong,cpp> a(0);  andeq  (a,2); }
   { volatile atomic<ulong,cpp> a(0);  oreq   (a,2); }
   { volatile atomic<ulong,cpp> a(0);  xoreq  (a,2); }
// { volatile atomic<ulong,cpp> a(0);  min    (a,2); }
// { volatile atomic<ulong,cpp> a(0);  max    (a,2); }
   { volatile atomic<ulong,cpp> a(0);  inc    (a); }
   { volatile atomic<ulong,cpp> a(0);  preinc (a); }
   { volatile atomic<ulong,cpp> a(0);  postinc(a); }
   { volatile atomic<ulong,cpp> a(0);  dec    (a); }
   { volatile atomic<ulong,cpp> a(0);  predec (a); }
   { volatile atomic<ulong,cpp> a(0);  postdec(a); }
   { volatile atomic<ulong,cpp> a(0);  add    (a,2,sync); }
   { volatile atomic<ulong,cpp> a(0);  sub    (a,2,sync); }
// { volatile atomic<ulong,cpp> a(0);  mul    (a,2,sync); }
// { volatile atomic<ulong,cpp> a(0);  div    (a,2,sync); }
// { volatile atomic<ulong,cpp> a(0);  mod    (a,2,sync); }
// { volatile atomic<ulong,cpp> a(0);  lshift (a,2,sync); }
// { volatile atomic<ulong,cpp> a(0);  rshift (a,2,sync); }
   { volatile atomic<ulong,cpp> a(0);  andeq  (a,2,sync); }
   { volatile atomic<ulong,cpp> a(0);  oreq   (a,2,sync); }
   { volatile atomic<ulong,cpp> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<ulong,cpp> a(0);  min    (a,2,sync); }
// { volatile atomic<ulong,cpp> a(0);  max    (a,2,sync); }
// { volatile atomic<ulong,cpp> a(0);  inc    (a,  sync); }
// { volatile atomic<ulong,cpp> a(0);  preinc (a,  sync); }
// { volatile atomic<ulong,cpp> a(0);  postinc(a,  sync); }
// { volatile atomic<ulong,cpp> a(0);  dec    (a,  sync); }
// { volatile atomic<ulong,cpp> a(0);  predec (a,  sync); }
// { volatile atomic<ulong,cpp> a(0);  postdec(a,  sync); }
// { volatile atomic<ulong,cpp> a(0);  add    (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  div    (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  min    (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  max    (a,2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  inc    (a,  success,failure); }
// { volatile atomic<ulong,cpp> a(0);  preinc (a,  success,failure); }
// { volatile atomic<ulong,cpp> a(0);  postinc(a,  success,failure); }
// { volatile atomic<ulong,cpp> a(0);  dec    (a,  success,failure); }
// { volatile atomic<ulong,cpp> a(0);  predec (a,  success,failure); }
// { volatile atomic<ulong,cpp> a(0);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { volatile atomic<ulong,kokkos> a(0);  add    (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  sub    (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  mul    (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  div    (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  mod    (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  lshift (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  rshift (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  andeq  (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  oreq   (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  xoreq  (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  min    (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  max    (a,2); }
   { volatile atomic<ulong,kokkos> a(0);  inc    (a); }
   { volatile atomic<ulong,kokkos> a(0);  preinc (a); }
   { volatile atomic<ulong,kokkos> a(0);  postinc(a); }
   { volatile atomic<ulong,kokkos> a(0);  dec    (a); }
   { volatile atomic<ulong,kokkos> a(0);  predec (a); }
   { volatile atomic<ulong,kokkos> a(0);  postdec(a); }
// { volatile atomic<ulong,kokkos> a(0);  add    (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  sub    (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  mul    (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  div    (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  mod    (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  lshift (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  rshift (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  andeq  (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  oreq   (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  min    (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  max    (a,2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  inc    (a,  sync); }
// { volatile atomic<ulong,kokkos> a(0);  preinc (a,  sync); }
// { volatile atomic<ulong,kokkos> a(0);  postinc(a,  sync); }
// { volatile atomic<ulong,kokkos> a(0);  dec    (a,  sync); }
// { volatile atomic<ulong,kokkos> a(0);  predec (a,  sync); }
// { volatile atomic<ulong,kokkos> a(0);  postdec(a,  sync); }
// { volatile atomic<ulong,kokkos> a(0);  add    (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  div    (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  min    (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  max    (a,2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  inc    (a,  success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  preinc (a,  success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  postinc(a,  success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  dec    (a,  success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  predec (a,  success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  postdec(a,  success,failure); }
#endif

   { volatile atomic<ulong,strong> a(0);  add    (a,2); }
   { volatile atomic<ulong,strong> a(0);  sub    (a,2); }
   { volatile atomic<ulong,strong> a(0);  mul    (a,2); }
   { volatile atomic<ulong,strong> a(0);  div    (a,2); }
   { volatile atomic<ulong,strong> a(0);  mod    (a,2); }
   { volatile atomic<ulong,strong> a(0);  lshift (a,2); }
   { volatile atomic<ulong,strong> a(0);  rshift (a,2); }
   { volatile atomic<ulong,strong> a(0);  andeq  (a,2); }
   { volatile atomic<ulong,strong> a(0);  oreq   (a,2); }
   { volatile atomic<ulong,strong> a(0);  xoreq  (a,2); }
   { volatile atomic<ulong,strong> a(0);  min    (a,2); }
   { volatile atomic<ulong,strong> a(0);  max    (a,2); }
   { volatile atomic<ulong,strong> a(0);  inc    (a); }
   { volatile atomic<ulong,strong> a(0);  preinc (a); }
   { volatile atomic<ulong,strong> a(0);  postinc(a); }
   { volatile atomic<ulong,strong> a(0);  dec    (a); }
   { volatile atomic<ulong,strong> a(0);  predec (a); }
   { volatile atomic<ulong,strong> a(0);  postdec(a); }
   { volatile atomic<ulong,strong> a(0);  add    (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  sub    (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  mul    (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  div    (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  mod    (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  lshift (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  rshift (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  andeq  (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  oreq   (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  min    (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  max    (a,2,sync); }
   { volatile atomic<ulong,strong> a(0);  inc    (a,  sync); }
   { volatile atomic<ulong,strong> a(0);  preinc (a,  sync); }
   { volatile atomic<ulong,strong> a(0);  postinc(a,  sync); }
   { volatile atomic<ulong,strong> a(0);  dec    (a,  sync); }
   { volatile atomic<ulong,strong> a(0);  predec (a,  sync); }
   { volatile atomic<ulong,strong> a(0);  postdec(a,  sync); }
   { volatile atomic<ulong,strong> a(0);  add    (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  div    (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  mod    (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  lshift (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  rshift (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  andeq  (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  oreq   (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  min    (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  max    (a,2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  inc    (a,  success,failure); }
   { volatile atomic<ulong,strong> a(0);  preinc (a,  success,failure); }
   { volatile atomic<ulong,strong> a(0);  postinc(a,  success,failure); }
   { volatile atomic<ulong,strong> a(0);  dec    (a,  success,failure); }
   { volatile atomic<ulong,strong> a(0);  predec (a,  success,failure); }
   { volatile atomic<ulong,strong> a(0);  postdec(a,  success,failure); }

   { volatile atomic<ulong,strong::pun> a(0);  add    (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  sub    (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  mul    (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  div    (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  mod    (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  lshift (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  rshift (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  andeq  (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  oreq   (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  xoreq  (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  min    (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  max    (a,2); }
   { volatile atomic<ulong,strong::pun> a(0);  inc    (a); }
   { volatile atomic<ulong,strong::pun> a(0);  preinc (a); }
   { volatile atomic<ulong,strong::pun> a(0);  postinc(a); }
   { volatile atomic<ulong,strong::pun> a(0);  dec    (a); }
   { volatile atomic<ulong,strong::pun> a(0);  predec (a); }
   { volatile atomic<ulong,strong::pun> a(0);  postdec(a); }
   { volatile atomic<ulong,strong::pun> a(0);  add    (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  sub    (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  mul    (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  div    (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  mod    (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  lshift (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  rshift (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  andeq  (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  oreq   (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  min    (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  max    (a,2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  inc    (a,  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  preinc (a,  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  postinc(a,  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  dec    (a,  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  predec (a,  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  postdec(a,  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  add    (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  div    (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  mod    (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  lshift (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  rshift (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  andeq  (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  oreq   (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  min    (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  max    (a,2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  inc    (a,  success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  preinc (a,  success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  postinc(a,  success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  dec    (a,  success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  predec (a,  success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  postdec(a,  success,failure); }

   { volatile atomic<ulong,weak> a(0);  add    (a,2); }
   { volatile atomic<ulong,weak> a(0);  sub    (a,2); }
   { volatile atomic<ulong,weak> a(0);  mul    (a,2); }
   { volatile atomic<ulong,weak> a(0);  div    (a,2); }
   { volatile atomic<ulong,weak> a(0);  mod    (a,2); }
   { volatile atomic<ulong,weak> a(0);  lshift (a,2); }
   { volatile atomic<ulong,weak> a(0);  rshift (a,2); }
   { volatile atomic<ulong,weak> a(0);  andeq  (a,2); }
   { volatile atomic<ulong,weak> a(0);  oreq   (a,2); }
   { volatile atomic<ulong,weak> a(0);  xoreq  (a,2); }
   { volatile atomic<ulong,weak> a(0);  min    (a,2); }
   { volatile atomic<ulong,weak> a(0);  max    (a,2); }
   { volatile atomic<ulong,weak> a(0);  inc    (a); }
   { volatile atomic<ulong,weak> a(0);  preinc (a); }
   { volatile atomic<ulong,weak> a(0);  postinc(a); }
   { volatile atomic<ulong,weak> a(0);  dec    (a); }
   { volatile atomic<ulong,weak> a(0);  predec (a); }
   { volatile atomic<ulong,weak> a(0);  postdec(a); }
   { volatile atomic<ulong,weak> a(0);  add    (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  sub    (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  mul    (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  div    (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  mod    (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  lshift (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  rshift (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  andeq  (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  oreq   (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  min    (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  max    (a,2,sync); }
   { volatile atomic<ulong,weak> a(0);  inc    (a,  sync); }
   { volatile atomic<ulong,weak> a(0);  preinc (a,  sync); }
   { volatile atomic<ulong,weak> a(0);  postinc(a,  sync); }
   { volatile atomic<ulong,weak> a(0);  dec    (a,  sync); }
   { volatile atomic<ulong,weak> a(0);  predec (a,  sync); }
   { volatile atomic<ulong,weak> a(0);  postdec(a,  sync); }
   { volatile atomic<ulong,weak> a(0);  add    (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  div    (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  mod    (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  lshift (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  rshift (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  andeq  (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  oreq   (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  min    (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  max    (a,2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  inc    (a,  success,failure); }
   { volatile atomic<ulong,weak> a(0);  preinc (a,  success,failure); }
   { volatile atomic<ulong,weak> a(0);  postinc(a,  success,failure); }
   { volatile atomic<ulong,weak> a(0);  dec    (a,  success,failure); }
   { volatile atomic<ulong,weak> a(0);  predec (a,  success,failure); }
   { volatile atomic<ulong,weak> a(0);  postdec(a,  success,failure); }

   { volatile atomic<ulong,weak::pun> a(0);  add    (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  sub    (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  mul    (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  div    (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  mod    (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  lshift (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  rshift (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  andeq  (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  oreq   (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  xoreq  (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  min    (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  max    (a,2); }
   { volatile atomic<ulong,weak::pun> a(0);  inc    (a); }
   { volatile atomic<ulong,weak::pun> a(0);  preinc (a); }
   { volatile atomic<ulong,weak::pun> a(0);  postinc(a); }
   { volatile atomic<ulong,weak::pun> a(0);  dec    (a); }
   { volatile atomic<ulong,weak::pun> a(0);  predec (a); }
   { volatile atomic<ulong,weak::pun> a(0);  postdec(a); }
   { volatile atomic<ulong,weak::pun> a(0);  add    (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  sub    (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  mul    (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  div    (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  mod    (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  lshift (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  rshift (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  andeq  (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  oreq   (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  min    (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  max    (a,2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  inc    (a,  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  preinc (a,  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  postinc(a,  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  dec    (a,  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  predec (a,  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  postdec(a,  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  add    (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  div    (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  mod    (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  lshift (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  rshift (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  andeq  (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  oreq   (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  min    (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  max    (a,2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  inc    (a,  success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  preinc (a,  success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  postinc(a,  success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  dec    (a,  success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  predec (a,  success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  postdec(a,  success,failure); }

   { volatile atomic<ulong,lock> a(0);  add    (a,2); }
   { volatile atomic<ulong,lock> a(0);  sub    (a,2); }
   { volatile atomic<ulong,lock> a(0);  mul    (a,2); }
   { volatile atomic<ulong,lock> a(0);  div    (a,2); }
   { volatile atomic<ulong,lock> a(0);  mod    (a,2); }
   { volatile atomic<ulong,lock> a(0);  lshift (a,2); }
   { volatile atomic<ulong,lock> a(0);  rshift (a,2); }
   { volatile atomic<ulong,lock> a(0);  andeq  (a,2); }
   { volatile atomic<ulong,lock> a(0);  oreq   (a,2); }
   { volatile atomic<ulong,lock> a(0);  xoreq  (a,2); }
   { volatile atomic<ulong,lock> a(0);  min    (a,2); }
   { volatile atomic<ulong,lock> a(0);  max    (a,2); }
   { volatile atomic<ulong,lock> a(0);  inc    (a); }
   { volatile atomic<ulong,lock> a(0);  preinc (a); }
   { volatile atomic<ulong,lock> a(0);  postinc(a); }
   { volatile atomic<ulong,lock> a(0);  dec    (a); }
   { volatile atomic<ulong,lock> a(0);  predec (a); }
   { volatile atomic<ulong,lock> a(0);  postdec(a); }
// { volatile atomic<ulong,lock> a(0);  add    (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  sub    (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  mul    (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  div    (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  mod    (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  lshift (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  rshift (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  andeq  (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  oreq   (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  min    (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  max    (a,2,sync); }
// { volatile atomic<ulong,lock> a(0);  inc    (a,  sync); }
// { volatile atomic<ulong,lock> a(0);  preinc (a,  sync); }
// { volatile atomic<ulong,lock> a(0);  postinc(a,  sync); }
// { volatile atomic<ulong,lock> a(0);  dec    (a,  sync); }
// { volatile atomic<ulong,lock> a(0);  predec (a,  sync); }
// { volatile atomic<ulong,lock> a(0);  postdec(a,  sync); }
// { volatile atomic<ulong,lock> a(0);  add    (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  div    (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  min    (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  max    (a,2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  inc    (a,  success,failure); }
// { volatile atomic<ulong,lock> a(0);  preinc (a,  success,failure); }
// { volatile atomic<ulong,lock> a(0);  postinc(a,  success,failure); }
// { volatile atomic<ulong,lock> a(0);  dec    (a,  success,failure); }
// { volatile atomic<ulong,lock> a(0);  predec (a,  success,failure); }
// { volatile atomic<ulong,lock> a(0);  postdec(a,  success,failure); }

   { volatile atomic<ulong,serial> a(0);  add    (a,2); }
   { volatile atomic<ulong,serial> a(0);  sub    (a,2); }
   { volatile atomic<ulong,serial> a(0);  mul    (a,2); }
   { volatile atomic<ulong,serial> a(0);  div    (a,2); }
   { volatile atomic<ulong,serial> a(0);  mod    (a,2); }
   { volatile atomic<ulong,serial> a(0);  lshift (a,2); }
   { volatile atomic<ulong,serial> a(0);  rshift (a,2); }
   { volatile atomic<ulong,serial> a(0);  andeq  (a,2); }
   { volatile atomic<ulong,serial> a(0);  oreq   (a,2); }
   { volatile atomic<ulong,serial> a(0);  xoreq  (a,2); }
   { volatile atomic<ulong,serial> a(0);  min    (a,2); }
   { volatile atomic<ulong,serial> a(0);  max    (a,2); }
   { volatile atomic<ulong,serial> a(0);  inc    (a); }
   { volatile atomic<ulong,serial> a(0);  preinc (a); }
   { volatile atomic<ulong,serial> a(0);  postinc(a); }
   { volatile atomic<ulong,serial> a(0);  dec    (a); }
   { volatile atomic<ulong,serial> a(0);  predec (a); }
   { volatile atomic<ulong,serial> a(0);  postdec(a); }
// { volatile atomic<ulong,serial> a(0);  add    (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  sub    (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  mul    (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  div    (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  mod    (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  lshift (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  rshift (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  andeq  (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  oreq   (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  min    (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  max    (a,2,sync); }
// { volatile atomic<ulong,serial> a(0);  inc    (a,  sync); }
// { volatile atomic<ulong,serial> a(0);  preinc (a,  sync); }
// { volatile atomic<ulong,serial> a(0);  postinc(a,  sync); }
// { volatile atomic<ulong,serial> a(0);  dec    (a,  sync); }
// { volatile atomic<ulong,serial> a(0);  predec (a,  sync); }
// { volatile atomic<ulong,serial> a(0);  postdec(a,  sync); }
// { volatile atomic<ulong,serial> a(0);  add    (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  div    (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  min    (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  max    (a,2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  inc    (a,  success,failure); }
// { volatile atomic<ulong,serial> a(0);  preinc (a,  success,failure); }
// { volatile atomic<ulong,serial> a(0);  postinc(a,  success,failure); }
// { volatile atomic<ulong,serial> a(0);  dec    (a,  success,failure); }
// { volatile atomic<ulong,serial> a(0);  predec (a,  success,failure); }
// { volatile atomic<ulong,serial> a(0);  postdec(a,  success,failure); }



   // ------------------------
   // double
   // ------------------------

// { volatile atomic<double,cpp> a(0);  add    (a,2); }
// { volatile atomic<double,cpp> a(0);  sub    (a,2); }
// { volatile atomic<double,cpp> a(0);  mul    (a,2); }
// { volatile atomic<double,cpp> a(0);  div    (a,2); }
// { volatile atomic<double,cpp> a(0);  mod    (a,2); }
// { volatile atomic<double,cpp> a(0);  lshift (a,2); }
// { volatile atomic<double,cpp> a(0);  rshift (a,2); }
// { volatile atomic<double,cpp> a(0);  andeq  (a,2); }
// { volatile atomic<double,cpp> a(0);  oreq   (a,2); }
// { volatile atomic<double,cpp> a(0);  xoreq  (a,2); }
// { volatile atomic<double,cpp> a(0);  min    (a,2); }
// { volatile atomic<double,cpp> a(0);  max    (a,2); }
// { volatile atomic<double,cpp> a(0);  inc    (a); }
// { volatile atomic<double,cpp> a(0);  preinc (a); }
// { volatile atomic<double,cpp> a(0);  postinc(a); }
// { volatile atomic<double,cpp> a(0);  dec    (a); }
// { volatile atomic<double,cpp> a(0);  predec (a); }
// { volatile atomic<double,cpp> a(0);  postdec(a); }
// { volatile atomic<double,cpp> a(0);  add    (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  sub    (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  mul    (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  div    (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  mod    (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  lshift (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  rshift (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  andeq  (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  oreq   (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  min    (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  max    (a,2,sync); }
// { volatile atomic<double,cpp> a(0);  inc    (a,  sync); }
// { volatile atomic<double,cpp> a(0);  preinc (a,  sync); }
// { volatile atomic<double,cpp> a(0);  postinc(a,  sync); }
// { volatile atomic<double,cpp> a(0);  dec    (a,  sync); }
// { volatile atomic<double,cpp> a(0);  predec (a,  sync); }
// { volatile atomic<double,cpp> a(0);  postdec(a,  sync); }
// { volatile atomic<double,cpp> a(0);  add    (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  div    (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  min    (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  max    (a,2,success,failure); }
// { volatile atomic<double,cpp> a(0);  inc    (a,  success,failure); }
// { volatile atomic<double,cpp> a(0);  preinc (a,  success,failure); }
// { volatile atomic<double,cpp> a(0);  postinc(a,  success,failure); }
// { volatile atomic<double,cpp> a(0);  dec    (a,  success,failure); }
// { volatile atomic<double,cpp> a(0);  predec (a,  success,failure); }
// { volatile atomic<double,cpp> a(0);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { volatile atomic<double,kokkos> a(0);  add    (a,2); }
   { volatile atomic<double,kokkos> a(0);  sub    (a,2); }
   { volatile atomic<double,kokkos> a(0);  mul    (a,2); }
   { volatile atomic<double,kokkos> a(0);  div    (a,2); }
// { volatile atomic<double,kokkos> a(0);  mod    (a,2); }
// { volatile atomic<double,kokkos> a(0);  lshift (a,2); }
// { volatile atomic<double,kokkos> a(0);  rshift (a,2); }
// { volatile atomic<double,kokkos> a(0);  andeq  (a,2); }
// { volatile atomic<double,kokkos> a(0);  oreq   (a,2); }
// { volatile atomic<double,kokkos> a(0);  xoreq  (a,2); }
   { volatile atomic<double,kokkos> a(0);  min    (a,2); }
   { volatile atomic<double,kokkos> a(0);  max    (a,2); }
   { volatile atomic<double,kokkos> a(0);  inc    (a); }
   { volatile atomic<double,kokkos> a(0);  preinc (a); }
   { volatile atomic<double,kokkos> a(0);  postinc(a); }
   { volatile atomic<double,kokkos> a(0);  dec    (a); }
   { volatile atomic<double,kokkos> a(0);  predec (a); }
   { volatile atomic<double,kokkos> a(0);  postdec(a); }
// { volatile atomic<double,kokkos> a(0);  add    (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  sub    (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  mul    (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  div    (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  mod    (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  lshift (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  rshift (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  andeq  (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  oreq   (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  min    (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  max    (a,2,sync); }
// { volatile atomic<double,kokkos> a(0);  inc    (a,  sync); }
// { volatile atomic<double,kokkos> a(0);  preinc (a,  sync); }
// { volatile atomic<double,kokkos> a(0);  postinc(a,  sync); }
// { volatile atomic<double,kokkos> a(0);  dec    (a,  sync); }
// { volatile atomic<double,kokkos> a(0);  predec (a,  sync); }
// { volatile atomic<double,kokkos> a(0);  postdec(a,  sync); }
// { volatile atomic<double,kokkos> a(0);  add    (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  div    (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  min    (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  max    (a,2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  inc    (a,  success,failure); }
// { volatile atomic<double,kokkos> a(0);  preinc (a,  success,failure); }
// { volatile atomic<double,kokkos> a(0);  postinc(a,  success,failure); }
// { volatile atomic<double,kokkos> a(0);  dec    (a,  success,failure); }
// { volatile atomic<double,kokkos> a(0);  predec (a,  success,failure); }
// { volatile atomic<double,kokkos> a(0);  postdec(a,  success,failure); }
#endif

   { volatile atomic<double,strong> a(0);  add    (a,2); }
   { volatile atomic<double,strong> a(0);  sub    (a,2); }
   { volatile atomic<double,strong> a(0);  mul    (a,2); }
   { volatile atomic<double,strong> a(0);  div    (a,2); }
// { volatile atomic<double,strong> a(0);  mod    (a,2); }
// { volatile atomic<double,strong> a(0);  lshift (a,2); }
// { volatile atomic<double,strong> a(0);  rshift (a,2); }
// { volatile atomic<double,strong> a(0);  andeq  (a,2); }
// { volatile atomic<double,strong> a(0);  oreq   (a,2); }
// { volatile atomic<double,strong> a(0);  xoreq  (a,2); }
   { volatile atomic<double,strong> a(0);  min    (a,2); }
   { volatile atomic<double,strong> a(0);  max    (a,2); }
   { volatile atomic<double,strong> a(0);  inc    (a); }
   { volatile atomic<double,strong> a(0);  preinc (a); }
   { volatile atomic<double,strong> a(0);  postinc(a); }
   { volatile atomic<double,strong> a(0);  dec    (a); }
   { volatile atomic<double,strong> a(0);  predec (a); }
   { volatile atomic<double,strong> a(0);  postdec(a); }
   { volatile atomic<double,strong> a(0);  add    (a,2,sync); }
   { volatile atomic<double,strong> a(0);  sub    (a,2,sync); }
   { volatile atomic<double,strong> a(0);  mul    (a,2,sync); }
   { volatile atomic<double,strong> a(0);  div    (a,2,sync); }
// { volatile atomic<double,strong> a(0);  mod    (a,2,sync); }
// { volatile atomic<double,strong> a(0);  lshift (a,2,sync); }
// { volatile atomic<double,strong> a(0);  rshift (a,2,sync); }
// { volatile atomic<double,strong> a(0);  andeq  (a,2,sync); }
// { volatile atomic<double,strong> a(0);  oreq   (a,2,sync); }
// { volatile atomic<double,strong> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<double,strong> a(0);  min    (a,2,sync); }
   { volatile atomic<double,strong> a(0);  max    (a,2,sync); }
   { volatile atomic<double,strong> a(0);  inc    (a,  sync); }
   { volatile atomic<double,strong> a(0);  preinc (a,  sync); }
   { volatile atomic<double,strong> a(0);  postinc(a,  sync); }
   { volatile atomic<double,strong> a(0);  dec    (a,  sync); }
   { volatile atomic<double,strong> a(0);  predec (a,  sync); }
   { volatile atomic<double,strong> a(0);  postdec(a,  sync); }
   { volatile atomic<double,strong> a(0);  add    (a,2,success,failure); }
   { volatile atomic<double,strong> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<double,strong> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<double,strong> a(0);  div    (a,2,success,failure); }
// { volatile atomic<double,strong> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<double,strong> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<double,strong> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<double,strong> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<double,strong> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<double,strong> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<double,strong> a(0);  min    (a,2,success,failure); }
   { volatile atomic<double,strong> a(0);  max    (a,2,success,failure); }
   { volatile atomic<double,strong> a(0);  inc    (a,  success,failure); }
   { volatile atomic<double,strong> a(0);  preinc (a,  success,failure); }
   { volatile atomic<double,strong> a(0);  postinc(a,  success,failure); }
   { volatile atomic<double,strong> a(0);  dec    (a,  success,failure); }
   { volatile atomic<double,strong> a(0);  predec (a,  success,failure); }
   { volatile atomic<double,strong> a(0);  postdec(a,  success,failure); }

   { volatile atomic<double,strong::pun> a(0);  add    (a,2); }
   { volatile atomic<double,strong::pun> a(0);  sub    (a,2); }
   { volatile atomic<double,strong::pun> a(0);  mul    (a,2); }
   { volatile atomic<double,strong::pun> a(0);  div    (a,2); }
// { volatile atomic<double,strong::pun> a(0);  mod    (a,2); }
// { volatile atomic<double,strong::pun> a(0);  lshift (a,2); }
// { volatile atomic<double,strong::pun> a(0);  rshift (a,2); }
// { volatile atomic<double,strong::pun> a(0);  andeq  (a,2); }
// { volatile atomic<double,strong::pun> a(0);  oreq   (a,2); }
// { volatile atomic<double,strong::pun> a(0);  xoreq  (a,2); }
   { volatile atomic<double,strong::pun> a(0);  min    (a,2); }
   { volatile atomic<double,strong::pun> a(0);  max    (a,2); }
   { volatile atomic<double,strong::pun> a(0);  inc    (a); }
   { volatile atomic<double,strong::pun> a(0);  preinc (a); }
   { volatile atomic<double,strong::pun> a(0);  postinc(a); }
   { volatile atomic<double,strong::pun> a(0);  dec    (a); }
   { volatile atomic<double,strong::pun> a(0);  predec (a); }
   { volatile atomic<double,strong::pun> a(0);  postdec(a); }
   { volatile atomic<double,strong::pun> a(0);  add    (a,2,sync); }
   { volatile atomic<double,strong::pun> a(0);  sub    (a,2,sync); }
   { volatile atomic<double,strong::pun> a(0);  mul    (a,2,sync); }
   { volatile atomic<double,strong::pun> a(0);  div    (a,2,sync); }
// { volatile atomic<double,strong::pun> a(0);  mod    (a,2,sync); }
// { volatile atomic<double,strong::pun> a(0);  lshift (a,2,sync); }
// { volatile atomic<double,strong::pun> a(0);  rshift (a,2,sync); }
// { volatile atomic<double,strong::pun> a(0);  andeq  (a,2,sync); }
// { volatile atomic<double,strong::pun> a(0);  oreq   (a,2,sync); }
// { volatile atomic<double,strong::pun> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<double,strong::pun> a(0);  min    (a,2,sync); }
   { volatile atomic<double,strong::pun> a(0);  max    (a,2,sync); }
   { volatile atomic<double,strong::pun> a(0);  inc    (a,  sync); }
   { volatile atomic<double,strong::pun> a(0);  preinc (a,  sync); }
   { volatile atomic<double,strong::pun> a(0);  postinc(a,  sync); }
   { volatile atomic<double,strong::pun> a(0);  dec    (a,  sync); }
   { volatile atomic<double,strong::pun> a(0);  predec (a,  sync); }
   { volatile atomic<double,strong::pun> a(0);  postdec(a,  sync); }
   { volatile atomic<double,strong::pun> a(0);  add    (a,2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  div    (a,2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  min    (a,2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  max    (a,2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  inc    (a,  success,failure); }
   { volatile atomic<double,strong::pun> a(0);  preinc (a,  success,failure); }
   { volatile atomic<double,strong::pun> a(0);  postinc(a,  success,failure); }
   { volatile atomic<double,strong::pun> a(0);  dec    (a,  success,failure); }
   { volatile atomic<double,strong::pun> a(0);  predec (a,  success,failure); }
   { volatile atomic<double,strong::pun> a(0);  postdec(a,  success,failure); }

   { volatile atomic<double,weak> a(0);  add    (a,2); }
   { volatile atomic<double,weak> a(0);  sub    (a,2); }
   { volatile atomic<double,weak> a(0);  mul    (a,2); }
   { volatile atomic<double,weak> a(0);  div    (a,2); }
// { volatile atomic<double,weak> a(0);  mod    (a,2); }
// { volatile atomic<double,weak> a(0);  lshift (a,2); }
// { volatile atomic<double,weak> a(0);  rshift (a,2); }
// { volatile atomic<double,weak> a(0);  andeq  (a,2); }
// { volatile atomic<double,weak> a(0);  oreq   (a,2); }
// { volatile atomic<double,weak> a(0);  xoreq  (a,2); }
   { volatile atomic<double,weak> a(0);  min    (a,2); }
   { volatile atomic<double,weak> a(0);  max    (a,2); }
   { volatile atomic<double,weak> a(0);  inc    (a); }
   { volatile atomic<double,weak> a(0);  preinc (a); }
   { volatile atomic<double,weak> a(0);  postinc(a); }
   { volatile atomic<double,weak> a(0);  dec    (a); }
   { volatile atomic<double,weak> a(0);  predec (a); }
   { volatile atomic<double,weak> a(0);  postdec(a); }
   { volatile atomic<double,weak> a(0);  add    (a,2,sync); }
   { volatile atomic<double,weak> a(0);  sub    (a,2,sync); }
   { volatile atomic<double,weak> a(0);  mul    (a,2,sync); }
   { volatile atomic<double,weak> a(0);  div    (a,2,sync); }
// { volatile atomic<double,weak> a(0);  mod    (a,2,sync); }
// { volatile atomic<double,weak> a(0);  lshift (a,2,sync); }
// { volatile atomic<double,weak> a(0);  rshift (a,2,sync); }
// { volatile atomic<double,weak> a(0);  andeq  (a,2,sync); }
// { volatile atomic<double,weak> a(0);  oreq   (a,2,sync); }
// { volatile atomic<double,weak> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<double,weak> a(0);  min    (a,2,sync); }
   { volatile atomic<double,weak> a(0);  max    (a,2,sync); }
   { volatile atomic<double,weak> a(0);  inc    (a,  sync); }
   { volatile atomic<double,weak> a(0);  preinc (a,  sync); }
   { volatile atomic<double,weak> a(0);  postinc(a,  sync); }
   { volatile atomic<double,weak> a(0);  dec    (a,  sync); }
   { volatile atomic<double,weak> a(0);  predec (a,  sync); }
   { volatile atomic<double,weak> a(0);  postdec(a,  sync); }
   { volatile atomic<double,weak> a(0);  add    (a,2,success,failure); }
   { volatile atomic<double,weak> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<double,weak> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<double,weak> a(0);  div    (a,2,success,failure); }
// { volatile atomic<double,weak> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<double,weak> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<double,weak> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<double,weak> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<double,weak> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<double,weak> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<double,weak> a(0);  min    (a,2,success,failure); }
   { volatile atomic<double,weak> a(0);  max    (a,2,success,failure); }
   { volatile atomic<double,weak> a(0);  inc    (a,  success,failure); }
   { volatile atomic<double,weak> a(0);  preinc (a,  success,failure); }
   { volatile atomic<double,weak> a(0);  postinc(a,  success,failure); }
   { volatile atomic<double,weak> a(0);  dec    (a,  success,failure); }
   { volatile atomic<double,weak> a(0);  predec (a,  success,failure); }
   { volatile atomic<double,weak> a(0);  postdec(a,  success,failure); }

   { volatile atomic<double,weak::pun> a(0);  add    (a,2); }
   { volatile atomic<double,weak::pun> a(0);  sub    (a,2); }
   { volatile atomic<double,weak::pun> a(0);  mul    (a,2); }
   { volatile atomic<double,weak::pun> a(0);  div    (a,2); }
// { volatile atomic<double,weak::pun> a(0);  mod    (a,2); }
// { volatile atomic<double,weak::pun> a(0);  lshift (a,2); }
// { volatile atomic<double,weak::pun> a(0);  rshift (a,2); }
// { volatile atomic<double,weak::pun> a(0);  andeq  (a,2); }
// { volatile atomic<double,weak::pun> a(0);  oreq   (a,2); }
// { volatile atomic<double,weak::pun> a(0);  xoreq  (a,2); }
   { volatile atomic<double,weak::pun> a(0);  min    (a,2); }
   { volatile atomic<double,weak::pun> a(0);  max    (a,2); }
   { volatile atomic<double,weak::pun> a(0);  inc    (a); }
   { volatile atomic<double,weak::pun> a(0);  preinc (a); }
   { volatile atomic<double,weak::pun> a(0);  postinc(a); }
   { volatile atomic<double,weak::pun> a(0);  dec    (a); }
   { volatile atomic<double,weak::pun> a(0);  predec (a); }
   { volatile atomic<double,weak::pun> a(0);  postdec(a); }
   { volatile atomic<double,weak::pun> a(0);  add    (a,2,sync); }
   { volatile atomic<double,weak::pun> a(0);  sub    (a,2,sync); }
   { volatile atomic<double,weak::pun> a(0);  mul    (a,2,sync); }
   { volatile atomic<double,weak::pun> a(0);  div    (a,2,sync); }
// { volatile atomic<double,weak::pun> a(0);  mod    (a,2,sync); }
// { volatile atomic<double,weak::pun> a(0);  lshift (a,2,sync); }
// { volatile atomic<double,weak::pun> a(0);  rshift (a,2,sync); }
// { volatile atomic<double,weak::pun> a(0);  andeq  (a,2,sync); }
// { volatile atomic<double,weak::pun> a(0);  oreq   (a,2,sync); }
// { volatile atomic<double,weak::pun> a(0);  xoreq  (a,2,sync); }
   { volatile atomic<double,weak::pun> a(0);  min    (a,2,sync); }
   { volatile atomic<double,weak::pun> a(0);  max    (a,2,sync); }
   { volatile atomic<double,weak::pun> a(0);  inc    (a,  sync); }
   { volatile atomic<double,weak::pun> a(0);  preinc (a,  sync); }
   { volatile atomic<double,weak::pun> a(0);  postinc(a,  sync); }
   { volatile atomic<double,weak::pun> a(0);  dec    (a,  sync); }
   { volatile atomic<double,weak::pun> a(0);  predec (a,  sync); }
   { volatile atomic<double,weak::pun> a(0);  postdec(a,  sync); }
   { volatile atomic<double,weak::pun> a(0);  add    (a,2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  sub    (a,2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  mul    (a,2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  div    (a,2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  xoreq  (a,2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  min    (a,2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  max    (a,2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  inc    (a,  success,failure); }
   { volatile atomic<double,weak::pun> a(0);  preinc (a,  success,failure); }
   { volatile atomic<double,weak::pun> a(0);  postinc(a,  success,failure); }
   { volatile atomic<double,weak::pun> a(0);  dec    (a,  success,failure); }
   { volatile atomic<double,weak::pun> a(0);  predec (a,  success,failure); }
   { volatile atomic<double,weak::pun> a(0);  postdec(a,  success,failure); }

   { volatile atomic<double,lock> a(0);  add    (a,2); }
   { volatile atomic<double,lock> a(0);  sub    (a,2); }
   { volatile atomic<double,lock> a(0);  mul    (a,2); }
   { volatile atomic<double,lock> a(0);  div    (a,2); }
// { volatile atomic<double,lock> a(0);  mod    (a,2); }
// { volatile atomic<double,lock> a(0);  lshift (a,2); }
// { volatile atomic<double,lock> a(0);  rshift (a,2); }
// { volatile atomic<double,lock> a(0);  andeq  (a,2); }
// { volatile atomic<double,lock> a(0);  oreq   (a,2); }
// { volatile atomic<double,lock> a(0);  xoreq  (a,2); }
   { volatile atomic<double,lock> a(0);  min    (a,2); }
   { volatile atomic<double,lock> a(0);  max    (a,2); }
   { volatile atomic<double,lock> a(0);  inc    (a); }
   { volatile atomic<double,lock> a(0);  preinc (a); }
   { volatile atomic<double,lock> a(0);  postinc(a); }
   { volatile atomic<double,lock> a(0);  dec    (a); }
   { volatile atomic<double,lock> a(0);  predec (a); }
   { volatile atomic<double,lock> a(0);  postdec(a); }
// { volatile atomic<double,lock> a(0);  add    (a,2,sync); }
// { volatile atomic<double,lock> a(0);  sub    (a,2,sync); }
// { volatile atomic<double,lock> a(0);  mul    (a,2,sync); }
// { volatile atomic<double,lock> a(0);  div    (a,2,sync); }
// { volatile atomic<double,lock> a(0);  mod    (a,2,sync); }
// { volatile atomic<double,lock> a(0);  lshift (a,2,sync); }
// { volatile atomic<double,lock> a(0);  rshift (a,2,sync); }
// { volatile atomic<double,lock> a(0);  andeq  (a,2,sync); }
// { volatile atomic<double,lock> a(0);  oreq   (a,2,sync); }
// { volatile atomic<double,lock> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<double,lock> a(0);  min    (a,2,sync); }
// { volatile atomic<double,lock> a(0);  max    (a,2,sync); }
// { volatile atomic<double,lock> a(0);  inc    (a,  sync); }
// { volatile atomic<double,lock> a(0);  preinc (a,  sync); }
// { volatile atomic<double,lock> a(0);  postinc(a,  sync); }
// { volatile atomic<double,lock> a(0);  dec    (a,  sync); }
// { volatile atomic<double,lock> a(0);  predec (a,  sync); }
// { volatile atomic<double,lock> a(0);  postdec(a,  sync); }
// { volatile atomic<double,lock> a(0);  add    (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  div    (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  min    (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  max    (a,2,success,failure); }
// { volatile atomic<double,lock> a(0);  inc    (a,  success,failure); }
// { volatile atomic<double,lock> a(0);  preinc (a,  success,failure); }
// { volatile atomic<double,lock> a(0);  postinc(a,  success,failure); }
// { volatile atomic<double,lock> a(0);  dec    (a,  success,failure); }
// { volatile atomic<double,lock> a(0);  predec (a,  success,failure); }
// { volatile atomic<double,lock> a(0);  postdec(a,  success,failure); }

   { volatile atomic<double,serial> a(0);  add    (a,2); }
   { volatile atomic<double,serial> a(0);  sub    (a,2); }
   { volatile atomic<double,serial> a(0);  mul    (a,2); }
   { volatile atomic<double,serial> a(0);  div    (a,2); }
// { volatile atomic<double,serial> a(0);  mod    (a,2); }
// { volatile atomic<double,serial> a(0);  lshift (a,2); }
// { volatile atomic<double,serial> a(0);  rshift (a,2); }
// { volatile atomic<double,serial> a(0);  andeq  (a,2); }
// { volatile atomic<double,serial> a(0);  oreq   (a,2); }
// { volatile atomic<double,serial> a(0);  xoreq  (a,2); }
   { volatile atomic<double,serial> a(0);  min    (a,2); }
   { volatile atomic<double,serial> a(0);  max    (a,2); }
   { volatile atomic<double,serial> a(0);  inc    (a); }
   { volatile atomic<double,serial> a(0);  preinc (a); }
   { volatile atomic<double,serial> a(0);  postinc(a); }
   { volatile atomic<double,serial> a(0);  dec    (a); }
   { volatile atomic<double,serial> a(0);  predec (a); }
   { volatile atomic<double,serial> a(0);  postdec(a); }
// { volatile atomic<double,serial> a(0);  add    (a,2,sync); }
// { volatile atomic<double,serial> a(0);  sub    (a,2,sync); }
// { volatile atomic<double,serial> a(0);  mul    (a,2,sync); }
// { volatile atomic<double,serial> a(0);  div    (a,2,sync); }
// { volatile atomic<double,serial> a(0);  mod    (a,2,sync); }
// { volatile atomic<double,serial> a(0);  lshift (a,2,sync); }
// { volatile atomic<double,serial> a(0);  rshift (a,2,sync); }
// { volatile atomic<double,serial> a(0);  andeq  (a,2,sync); }
// { volatile atomic<double,serial> a(0);  oreq   (a,2,sync); }
// { volatile atomic<double,serial> a(0);  xoreq  (a,2,sync); }
// { volatile atomic<double,serial> a(0);  min    (a,2,sync); }
// { volatile atomic<double,serial> a(0);  max    (a,2,sync); }
// { volatile atomic<double,serial> a(0);  inc    (a,  sync); }
// { volatile atomic<double,serial> a(0);  preinc (a,  sync); }
// { volatile atomic<double,serial> a(0);  postinc(a,  sync); }
// { volatile atomic<double,serial> a(0);  dec    (a,  sync); }
// { volatile atomic<double,serial> a(0);  predec (a,  sync); }
// { volatile atomic<double,serial> a(0);  postdec(a,  sync); }
// { volatile atomic<double,serial> a(0);  add    (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  sub    (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  mul    (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  div    (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  mod    (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  lshift (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  rshift (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  andeq  (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  oreq   (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  xoreq  (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  min    (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  max    (a,2,success,failure); }
// { volatile atomic<double,serial> a(0);  inc    (a,  success,failure); }
// { volatile atomic<double,serial> a(0);  preinc (a,  success,failure); }
// { volatile atomic<double,serial> a(0);  postinc(a,  success,failure); }
// { volatile atomic<double,serial> a(0);  dec    (a,  success,failure); }
// { volatile atomic<double,serial> a(0);  predec (a,  success,failure); }
// { volatile atomic<double,serial> a(0);  postdec(a,  success,failure); }



   // ------------------------
   // int*
   // ------------------------

#if !defined(ATOMICS_TEST)
   { volatile atomic<int*,cpp> a(&i);  add    (a,2); }
   { volatile atomic<int*,cpp> a(&i);  sub    (a,2); }
// { volatile atomic<int*,cpp> a(&i);  mul    (a,2); }
// { volatile atomic<int*,cpp> a(&i);  div    (a,2); }
// { volatile atomic<int*,cpp> a(&i);  mod    (a,2); }
// { volatile atomic<int*,cpp> a(&i);  lshift (a,2); }
// { volatile atomic<int*,cpp> a(&i);  rshift (a,2); }
// { volatile atomic<int*,cpp> a(&i);  andeq  (a,2); }
// { volatile atomic<int*,cpp> a(&i);  oreq   (a,2); }
// { volatile atomic<int*,cpp> a(&i);  xoreq  (a,2); }
// { volatile atomic<int*,cpp> a(&i);  min    (a,&j); }
// { volatile atomic<int*,cpp> a(&i);  max    (a,&j); }
   { volatile atomic<int*,cpp> a(&i);  inc    (a); }
   { volatile atomic<int*,cpp> a(&i);  preinc (a); }
   { volatile atomic<int*,cpp> a(&i);  postinc(a); }
   { volatile atomic<int*,cpp> a(&i);  dec    (a); }
   { volatile atomic<int*,cpp> a(&i);  predec (a); }
   { volatile atomic<int*,cpp> a(&i);  postdec(a); }
   { volatile atomic<int*,cpp> a(&i);  add    (a,2,sync); }
   { volatile atomic<int*,cpp> a(&i);  sub    (a,2,sync); }
// { volatile atomic<int*,cpp> a(&i);  mul    (a,2,sync); }
// { volatile atomic<int*,cpp> a(&i);  div    (a,2,sync); }
// { volatile atomic<int*,cpp> a(&i);  mod    (a,2,sync); }
// { volatile atomic<int*,cpp> a(&i);  lshift (a,2,sync); }
// { volatile atomic<int*,cpp> a(&i);  rshift (a,2,sync); }
// { volatile atomic<int*,cpp> a(&i);  andeq  (a,2,sync); }
// { volatile atomic<int*,cpp> a(&i);  oreq   (a,2,sync); }
// { volatile atomic<int*,cpp> a(&i);  xoreq  (a,2,sync); }
// { volatile atomic<int*,cpp> a(&i);  min    (a,&j,sync); }
// { volatile atomic<int*,cpp> a(&i);  max    (a,&j,sync); }
// { volatile atomic<int*,cpp> a(&i);  inc    (a,  sync); }
// { volatile atomic<int*,cpp> a(&i);  preinc (a,  sync); }
// { volatile atomic<int*,cpp> a(&i);  postinc(a,  sync); }
// { volatile atomic<int*,cpp> a(&i);  dec    (a,  sync); }
// { volatile atomic<int*,cpp> a(&i);  predec (a,  sync); }
// { volatile atomic<int*,cpp> a(&i);  postdec(a,  sync); }
// { volatile atomic<int*,cpp> a(&i);  add    (a,2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  sub    (a,2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  mul    (a,2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  div    (a,2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  mod    (a,2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  lshift (a,2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  rshift (a,2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  andeq  (a,2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  oreq   (a,2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  xoreq  (a,2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  min    (a,&j,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  max    (a,&j,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  inc    (a,  success,failure); }
// { volatile atomic<int*,cpp> a(&i);  preinc (a,  success,failure); }
// { volatile atomic<int*,cpp> a(&i);  postinc(a,  success,failure); }
// { volatile atomic<int*,cpp> a(&i);  dec    (a,  success,failure); }
// { volatile atomic<int*,cpp> a(&i);  predec (a,  success,failure); }
// { volatile atomic<int*,cpp> a(&i);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { volatile atomic<int*,kokkos> a(&i);  add    (a,2); }
// { volatile atomic<int*,kokkos> a(&i);  sub    (a,2); }
// { volatile atomic<int*,kokkos> a(&i);  mul    (a,2); }
// { volatile atomic<int*,kokkos> a(&i);  div    (a,2); }
// { volatile atomic<int*,kokkos> a(&i);  mod    (a,2); }
// { volatile atomic<int*,kokkos> a(&i);  lshift (a,2); }
// { volatile atomic<int*,kokkos> a(&i);  rshift (a,2); }
// { volatile atomic<int*,kokkos> a(&i);  andeq  (a,2); }
// { volatile atomic<int*,kokkos> a(&i);  oreq   (a,2); }
// { volatile atomic<int*,kokkos> a(&i);  xoreq  (a,2); }
// { volatile atomic<int*,kokkos> a(&i);  min    (a,&j); }
// { volatile atomic<int*,kokkos> a(&i);  max    (a,&j); }
// { volatile atomic<int*,kokkos> a(&i);  inc    (a); }
// { volatile atomic<int*,kokkos> a(&i);  preinc (a); }
// { volatile atomic<int*,kokkos> a(&i);  postinc(a); }
// { volatile atomic<int*,kokkos> a(&i);  dec    (a); }
// { volatile atomic<int*,kokkos> a(&i);  predec (a); }
// { volatile atomic<int*,kokkos> a(&i);  postdec(a); }
// { volatile atomic<int*,kokkos> a(&i);  add    (a,2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  sub    (a,2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  mul    (a,2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  div    (a,2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  mod    (a,2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  lshift (a,2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  rshift (a,2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  andeq  (a,2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  oreq   (a,2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  xoreq  (a,2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  min    (a,&j,sync); }
// { volatile atomic<int*,kokkos> a(&i);  max    (a,&j,sync); }
// { volatile atomic<int*,kokkos> a(&i);  inc    (a,  sync); }
// { volatile atomic<int*,kokkos> a(&i);  preinc (a,  sync); }
// { volatile atomic<int*,kokkos> a(&i);  postinc(a,  sync); }
// { volatile atomic<int*,kokkos> a(&i);  dec    (a,  sync); }
// { volatile atomic<int*,kokkos> a(&i);  predec (a,  sync); }
// { volatile atomic<int*,kokkos> a(&i);  postdec(a,  sync); }
// { volatile atomic<int*,kokkos> a(&i);  add    (a,2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  sub    (a,2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  mul    (a,2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  div    (a,2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  mod    (a,2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  lshift (a,2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  rshift (a,2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  andeq  (a,2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  oreq   (a,2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  xoreq  (a,2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  min    (a,&j,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  max    (a,&j,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  inc    (a,  success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  preinc (a,  success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  postinc(a,  success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  dec    (a,  success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  predec (a,  success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  postdec(a,  success,failure); }
#endif

   { volatile atomic<int*,strong> a(&i);  add    (a,2); }
   { volatile atomic<int*,strong> a(&i);  sub    (a,2); }
// { volatile atomic<int*,strong> a(&i);  mul    (a,2); }
// { volatile atomic<int*,strong> a(&i);  div    (a,2); }
// { volatile atomic<int*,strong> a(&i);  mod    (a,2); }
// { volatile atomic<int*,strong> a(&i);  lshift (a,2); }
// { volatile atomic<int*,strong> a(&i);  rshift (a,2); }
// { volatile atomic<int*,strong> a(&i);  andeq  (a,2); }
// { volatile atomic<int*,strong> a(&i);  oreq   (a,2); }
// { volatile atomic<int*,strong> a(&i);  xoreq  (a,2); }
   { volatile atomic<int*,strong> a(&i);  min    (a,&j); }
   { volatile atomic<int*,strong> a(&i);  max    (a,&j); }
   { volatile atomic<int*,strong> a(&i);  inc    (a); }
   { volatile atomic<int*,strong> a(&i);  preinc (a); }
   { volatile atomic<int*,strong> a(&i);  postinc(a); }
   { volatile atomic<int*,strong> a(&i);  dec    (a); }
   { volatile atomic<int*,strong> a(&i);  predec (a); }
   { volatile atomic<int*,strong> a(&i);  postdec(a); }
   { volatile atomic<int*,strong> a(&i);  add    (a,2,sync); }
   { volatile atomic<int*,strong> a(&i);  sub    (a,2,sync); }
// { volatile atomic<int*,strong> a(&i);  mul    (a,2,sync); }
// { volatile atomic<int*,strong> a(&i);  div    (a,2,sync); }
// { volatile atomic<int*,strong> a(&i);  mod    (a,2,sync); }
// { volatile atomic<int*,strong> a(&i);  lshift (a,2,sync); }
// { volatile atomic<int*,strong> a(&i);  rshift (a,2,sync); }
// { volatile atomic<int*,strong> a(&i);  andeq  (a,2,sync); }
// { volatile atomic<int*,strong> a(&i);  oreq   (a,2,sync); }
// { volatile atomic<int*,strong> a(&i);  xoreq  (a,2,sync); }
   { volatile atomic<int*,strong> a(&i);  min    (a,&j,sync); }
   { volatile atomic<int*,strong> a(&i);  max    (a,&j,sync); }
   { volatile atomic<int*,strong> a(&i);  inc    (a,  sync); }
   { volatile atomic<int*,strong> a(&i);  preinc (a,  sync); }
   { volatile atomic<int*,strong> a(&i);  postinc(a,  sync); }
   { volatile atomic<int*,strong> a(&i);  dec    (a,  sync); }
   { volatile atomic<int*,strong> a(&i);  predec (a,  sync); }
   { volatile atomic<int*,strong> a(&i);  postdec(a,  sync); }
   { volatile atomic<int*,strong> a(&i);  add    (a,2,success,failure); }
   { volatile atomic<int*,strong> a(&i);  sub    (a,2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  mul    (a,2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  div    (a,2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  mod    (a,2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  lshift (a,2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  rshift (a,2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  andeq  (a,2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  oreq   (a,2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  xoreq  (a,2,success,failure); }
   { volatile atomic<int*,strong> a(&i);  min    (a,&j,success,failure); }
   { volatile atomic<int*,strong> a(&i);  max    (a,&j,success,failure); }
   { volatile atomic<int*,strong> a(&i);  inc    (a,  success,failure); }
   { volatile atomic<int*,strong> a(&i);  preinc (a,  success,failure); }
   { volatile atomic<int*,strong> a(&i);  postinc(a,  success,failure); }
   { volatile atomic<int*,strong> a(&i);  dec    (a,  success,failure); }
   { volatile atomic<int*,strong> a(&i);  predec (a,  success,failure); }
   { volatile atomic<int*,strong> a(&i);  postdec(a,  success,failure); }

   { volatile atomic<int*,strong::pun> a(&i);  add    (a,2); }
   { volatile atomic<int*,strong::pun> a(&i);  sub    (a,2); }
// { volatile atomic<int*,strong::pun> a(&i);  mul    (a,2); }
// { volatile atomic<int*,strong::pun> a(&i);  div    (a,2); }
// { volatile atomic<int*,strong::pun> a(&i);  mod    (a,2); }
// { volatile atomic<int*,strong::pun> a(&i);  lshift (a,2); }
// { volatile atomic<int*,strong::pun> a(&i);  rshift (a,2); }
// { volatile atomic<int*,strong::pun> a(&i);  andeq  (a,2); }
// { volatile atomic<int*,strong::pun> a(&i);  oreq   (a,2); }
// { volatile atomic<int*,strong::pun> a(&i);  xoreq  (a,2); }
   { volatile atomic<int*,strong::pun> a(&i);  min    (a,&j); }
   { volatile atomic<int*,strong::pun> a(&i);  max    (a,&j); }
   { volatile atomic<int*,strong::pun> a(&i);  inc    (a); }
   { volatile atomic<int*,strong::pun> a(&i);  preinc (a); }
   { volatile atomic<int*,strong::pun> a(&i);  postinc(a); }
   { volatile atomic<int*,strong::pun> a(&i);  dec    (a); }
   { volatile atomic<int*,strong::pun> a(&i);  predec (a); }
   { volatile atomic<int*,strong::pun> a(&i);  postdec(a); }
   { volatile atomic<int*,strong::pun> a(&i);  add    (a,2,sync); }
   { volatile atomic<int*,strong::pun> a(&i);  sub    (a,2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  mul    (a,2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  div    (a,2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  mod    (a,2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  lshift (a,2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  rshift (a,2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  andeq  (a,2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  oreq   (a,2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  xoreq  (a,2,sync); }
   { volatile atomic<int*,strong::pun> a(&i);  min    (a,&j,sync); }
   { volatile atomic<int*,strong::pun> a(&i);  max    (a,&j,sync); }
   { volatile atomic<int*,strong::pun> a(&i);  inc    (a,  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  preinc (a,  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  postinc(a,  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  dec    (a,  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  predec (a,  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  postdec(a,  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  add    (a,2,success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  sub    (a,2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  mul    (a,2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  div    (a,2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  mod    (a,2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  lshift (a,2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  rshift (a,2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  andeq  (a,2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  oreq   (a,2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  xoreq  (a,2,success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  min    (a,&j,success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  max    (a,&j,success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  inc    (a,  success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  preinc (a,  success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  postinc(a,  success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  dec    (a,  success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  predec (a,  success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  postdec(a,  success,failure); }

   { volatile atomic<int*,weak> a(&i);  add    (a,2); }
   { volatile atomic<int*,weak> a(&i);  sub    (a,2); }
// { volatile atomic<int*,weak> a(&i);  mul    (a,2); }
// { volatile atomic<int*,weak> a(&i);  div    (a,2); }
// { volatile atomic<int*,weak> a(&i);  mod    (a,2); }
// { volatile atomic<int*,weak> a(&i);  lshift (a,2); }
// { volatile atomic<int*,weak> a(&i);  rshift (a,2); }
// { volatile atomic<int*,weak> a(&i);  andeq  (a,2); }
// { volatile atomic<int*,weak> a(&i);  oreq   (a,2); }
// { volatile atomic<int*,weak> a(&i);  xoreq  (a,2); }
   { volatile atomic<int*,weak> a(&i);  min    (a,&j); }
   { volatile atomic<int*,weak> a(&i);  max    (a,&j); }
   { volatile atomic<int*,weak> a(&i);  inc    (a); }
   { volatile atomic<int*,weak> a(&i);  preinc (a); }
   { volatile atomic<int*,weak> a(&i);  postinc(a); }
   { volatile atomic<int*,weak> a(&i);  dec    (a); }
   { volatile atomic<int*,weak> a(&i);  predec (a); }
   { volatile atomic<int*,weak> a(&i);  postdec(a); }
   { volatile atomic<int*,weak> a(&i);  add    (a,2,sync); }
   { volatile atomic<int*,weak> a(&i);  sub    (a,2,sync); }
// { volatile atomic<int*,weak> a(&i);  mul    (a,2,sync); }
// { volatile atomic<int*,weak> a(&i);  div    (a,2,sync); }
// { volatile atomic<int*,weak> a(&i);  mod    (a,2,sync); }
// { volatile atomic<int*,weak> a(&i);  lshift (a,2,sync); }
// { volatile atomic<int*,weak> a(&i);  rshift (a,2,sync); }
// { volatile atomic<int*,weak> a(&i);  andeq  (a,2,sync); }
// { volatile atomic<int*,weak> a(&i);  oreq   (a,2,sync); }
// { volatile atomic<int*,weak> a(&i);  xoreq  (a,2,sync); }
   { volatile atomic<int*,weak> a(&i);  min    (a,&j,sync); }
   { volatile atomic<int*,weak> a(&i);  max    (a,&j,sync); }
   { volatile atomic<int*,weak> a(&i);  inc    (a,  sync); }
   { volatile atomic<int*,weak> a(&i);  preinc (a,  sync); }
   { volatile atomic<int*,weak> a(&i);  postinc(a,  sync); }
   { volatile atomic<int*,weak> a(&i);  dec    (a,  sync); }
   { volatile atomic<int*,weak> a(&i);  predec (a,  sync); }
   { volatile atomic<int*,weak> a(&i);  postdec(a,  sync); }
   { volatile atomic<int*,weak> a(&i);  add    (a,2,success,failure); }
   { volatile atomic<int*,weak> a(&i);  sub    (a,2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  mul    (a,2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  div    (a,2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  mod    (a,2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  lshift (a,2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  rshift (a,2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  andeq  (a,2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  oreq   (a,2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  xoreq  (a,2,success,failure); }
   { volatile atomic<int*,weak> a(&i);  min    (a,&j,success,failure); }
   { volatile atomic<int*,weak> a(&i);  max    (a,&j,success,failure); }
   { volatile atomic<int*,weak> a(&i);  inc    (a,  success,failure); }
   { volatile atomic<int*,weak> a(&i);  preinc (a,  success,failure); }
   { volatile atomic<int*,weak> a(&i);  postinc(a,  success,failure); }
   { volatile atomic<int*,weak> a(&i);  dec    (a,  success,failure); }
   { volatile atomic<int*,weak> a(&i);  predec (a,  success,failure); }
   { volatile atomic<int*,weak> a(&i);  postdec(a,  success,failure); }

   { volatile atomic<int*,weak::pun> a(&i);  add    (a,2); }
   { volatile atomic<int*,weak::pun> a(&i);  sub    (a,2); }
// { volatile atomic<int*,weak::pun> a(&i);  mul    (a,2); }
// { volatile atomic<int*,weak::pun> a(&i);  div    (a,2); }
// { volatile atomic<int*,weak::pun> a(&i);  mod    (a,2); }
// { volatile atomic<int*,weak::pun> a(&i);  lshift (a,2); }
// { volatile atomic<int*,weak::pun> a(&i);  rshift (a,2); }
// { volatile atomic<int*,weak::pun> a(&i);  andeq  (a,2); }
// { volatile atomic<int*,weak::pun> a(&i);  oreq   (a,2); }
// { volatile atomic<int*,weak::pun> a(&i);  xoreq  (a,2); }
   { volatile atomic<int*,weak::pun> a(&i);  min    (a,&j); }
   { volatile atomic<int*,weak::pun> a(&i);  max    (a,&j); }
   { volatile atomic<int*,weak::pun> a(&i);  inc    (a); }
   { volatile atomic<int*,weak::pun> a(&i);  preinc (a); }
   { volatile atomic<int*,weak::pun> a(&i);  postinc(a); }
   { volatile atomic<int*,weak::pun> a(&i);  dec    (a); }
   { volatile atomic<int*,weak::pun> a(&i);  predec (a); }
   { volatile atomic<int*,weak::pun> a(&i);  postdec(a); }
   { volatile atomic<int*,weak::pun> a(&i);  add    (a,2,sync); }
   { volatile atomic<int*,weak::pun> a(&i);  sub    (a,2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  mul    (a,2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  div    (a,2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  mod    (a,2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  lshift (a,2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  rshift (a,2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  andeq  (a,2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  oreq   (a,2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  xoreq  (a,2,sync); }
   { volatile atomic<int*,weak::pun> a(&i);  min    (a,&j,sync); }
   { volatile atomic<int*,weak::pun> a(&i);  max    (a,&j,sync); }
   { volatile atomic<int*,weak::pun> a(&i);  inc    (a,  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  preinc (a,  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  postinc(a,  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  dec    (a,  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  predec (a,  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  postdec(a,  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  add    (a,2,success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  sub    (a,2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  mul    (a,2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  div    (a,2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  mod    (a,2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  lshift (a,2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  rshift (a,2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  andeq  (a,2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  oreq   (a,2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  xoreq  (a,2,success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  min    (a,&j,success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  max    (a,&j,success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  inc    (a,  success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  preinc (a,  success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  postinc(a,  success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  dec    (a,  success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  predec (a,  success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  postdec(a,  success,failure); }

   { volatile atomic<int*,lock> a(&i);  add    (a,2); }
   { volatile atomic<int*,lock> a(&i);  sub    (a,2); }
// { volatile atomic<int*,lock> a(&i);  mul    (a,2); }
// { volatile atomic<int*,lock> a(&i);  div    (a,2); }
// { volatile atomic<int*,lock> a(&i);  mod    (a,2); }
// { volatile atomic<int*,lock> a(&i);  lshift (a,2); }
// { volatile atomic<int*,lock> a(&i);  rshift (a,2); }
// { volatile atomic<int*,lock> a(&i);  andeq  (a,2); }
// { volatile atomic<int*,lock> a(&i);  oreq   (a,2); }
// { volatile atomic<int*,lock> a(&i);  xoreq  (a,2); }
   { volatile atomic<int*,lock> a(&i);  min    (a,&j); }
   { volatile atomic<int*,lock> a(&i);  max    (a,&j); }
   { volatile atomic<int*,lock> a(&i);  inc    (a); }
   { volatile atomic<int*,lock> a(&i);  preinc (a); }
   { volatile atomic<int*,lock> a(&i);  postinc(a); }
   { volatile atomic<int*,lock> a(&i);  dec    (a); }
   { volatile atomic<int*,lock> a(&i);  predec (a); }
   { volatile atomic<int*,lock> a(&i);  postdec(a); }
// { volatile atomic<int*,lock> a(&i);  add    (a,2,sync); }
// { volatile atomic<int*,lock> a(&i);  sub    (a,2,sync); }
// { volatile atomic<int*,lock> a(&i);  mul    (a,2,sync); }
// { volatile atomic<int*,lock> a(&i);  div    (a,2,sync); }
// { volatile atomic<int*,lock> a(&i);  mod    (a,2,sync); }
// { volatile atomic<int*,lock> a(&i);  lshift (a,2,sync); }
// { volatile atomic<int*,lock> a(&i);  rshift (a,2,sync); }
// { volatile atomic<int*,lock> a(&i);  andeq  (a,2,sync); }
// { volatile atomic<int*,lock> a(&i);  oreq   (a,2,sync); }
// { volatile atomic<int*,lock> a(&i);  xoreq  (a,2,sync); }
// { volatile atomic<int*,lock> a(&i);  min    (a,&j,sync); }
// { volatile atomic<int*,lock> a(&i);  max    (a,&j,sync); }
// { volatile atomic<int*,lock> a(&i);  inc    (a,  sync); }
// { volatile atomic<int*,lock> a(&i);  preinc (a,  sync); }
// { volatile atomic<int*,lock> a(&i);  postinc(a,  sync); }
// { volatile atomic<int*,lock> a(&i);  dec    (a,  sync); }
// { volatile atomic<int*,lock> a(&i);  predec (a,  sync); }
// { volatile atomic<int*,lock> a(&i);  postdec(a,  sync); }
// { volatile atomic<int*,lock> a(&i);  add    (a,2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  sub    (a,2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  mul    (a,2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  div    (a,2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  mod    (a,2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  lshift (a,2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  rshift (a,2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  andeq  (a,2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  oreq   (a,2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  xoreq  (a,2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  min    (a,&j,success,failure); }
// { volatile atomic<int*,lock> a(&i);  max    (a,&j,success,failure); }
// { volatile atomic<int*,lock> a(&i);  inc    (a,  success,failure); }
// { volatile atomic<int*,lock> a(&i);  preinc (a,  success,failure); }
// { volatile atomic<int*,lock> a(&i);  postinc(a,  success,failure); }
// { volatile atomic<int*,lock> a(&i);  dec    (a,  success,failure); }
// { volatile atomic<int*,lock> a(&i);  predec (a,  success,failure); }
// { volatile atomic<int*,lock> a(&i);  postdec(a,  success,failure); }

   { volatile atomic<int*,serial> a(&i);  add    (a,2); }
   { volatile atomic<int*,serial> a(&i);  sub    (a,2); }
// { volatile atomic<int*,serial> a(&i);  mul    (a,2); }
// { volatile atomic<int*,serial> a(&i);  div    (a,2); }
// { volatile atomic<int*,serial> a(&i);  mod    (a,2); }
// { volatile atomic<int*,serial> a(&i);  lshift (a,2); }
// { volatile atomic<int*,serial> a(&i);  rshift (a,2); }
// { volatile atomic<int*,serial> a(&i);  andeq  (a,2); }
// { volatile atomic<int*,serial> a(&i);  oreq   (a,2); }
// { volatile atomic<int*,serial> a(&i);  xoreq  (a,2); }
   { volatile atomic<int*,serial> a(&i);  min    (a,&j); }
   { volatile atomic<int*,serial> a(&i);  max    (a,&j); }
   { volatile atomic<int*,serial> a(&i);  inc    (a); }
   { volatile atomic<int*,serial> a(&i);  preinc (a); }
   { volatile atomic<int*,serial> a(&i);  postinc(a); }
   { volatile atomic<int*,serial> a(&i);  dec    (a); }
   { volatile atomic<int*,serial> a(&i);  predec (a); }
   { volatile atomic<int*,serial> a(&i);  postdec(a); }
// { volatile atomic<int*,serial> a(&i);  add    (a,2,sync); }
// { volatile atomic<int*,serial> a(&i);  sub    (a,2,sync); }
// { volatile atomic<int*,serial> a(&i);  mul    (a,2,sync); }
// { volatile atomic<int*,serial> a(&i);  div    (a,2,sync); }
// { volatile atomic<int*,serial> a(&i);  mod    (a,2,sync); }
// { volatile atomic<int*,serial> a(&i);  lshift (a,2,sync); }
// { volatile atomic<int*,serial> a(&i);  rshift (a,2,sync); }
// { volatile atomic<int*,serial> a(&i);  andeq  (a,2,sync); }
// { volatile atomic<int*,serial> a(&i);  oreq   (a,2,sync); }
// { volatile atomic<int*,serial> a(&i);  xoreq  (a,2,sync); }
// { volatile atomic<int*,serial> a(&i);  min    (a,&j,sync); }
// { volatile atomic<int*,serial> a(&i);  max    (a,&j,sync); }
// { volatile atomic<int*,serial> a(&i);  inc    (a,  sync); }
// { volatile atomic<int*,serial> a(&i);  preinc (a,  sync); }
// { volatile atomic<int*,serial> a(&i);  postinc(a,  sync); }
// { volatile atomic<int*,serial> a(&i);  dec    (a,  sync); }
// { volatile atomic<int*,serial> a(&i);  predec (a,  sync); }
// { volatile atomic<int*,serial> a(&i);  postdec(a,  sync); }
// { volatile atomic<int*,serial> a(&i);  add    (a,2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  sub    (a,2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  mul    (a,2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  div    (a,2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  mod    (a,2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  lshift (a,2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  rshift (a,2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  andeq  (a,2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  oreq   (a,2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  xoreq  (a,2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  min    (a,&j,success,failure); }
// { volatile atomic<int*,serial> a(&i);  max    (a,&j,success,failure); }
// { volatile atomic<int*,serial> a(&i);  inc    (a,  success,failure); }
// { volatile atomic<int*,serial> a(&i);  preinc (a,  success,failure); }
// { volatile atomic<int*,serial> a(&i);  postinc(a,  success,failure); }
// { volatile atomic<int*,serial> a(&i);  dec    (a,  success,failure); }
// { volatile atomic<int*,serial> a(&i);  predec (a,  success,failure); }
// { volatile atomic<int*,serial> a(&i);  postdec(a,  success,failure); }
#endif



   // ------------------------
   // std::complex
   // ------------------------

// { volatile atomic<cmplx,cpp> a(0);  add    (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  sub    (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  mul    (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  div    (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  mod    (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  lshift (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  rshift (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  andeq  (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  oreq   (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  xoreq  (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  min    (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  max    (a,c); }
// { volatile atomic<cmplx,cpp> a(0);  inc    (a); }
// { volatile atomic<cmplx,cpp> a(0);  preinc (a); }
// { volatile atomic<cmplx,cpp> a(0);  postinc(a); }
// { volatile atomic<cmplx,cpp> a(0);  dec    (a); }
// { volatile atomic<cmplx,cpp> a(0);  predec (a); }
// { volatile atomic<cmplx,cpp> a(0);  postdec(a); }
// { volatile atomic<cmplx,cpp> a(0);  add    (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  sub    (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  mul    (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  div    (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  mod    (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  lshift (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  rshift (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  andeq  (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  oreq   (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  xoreq  (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  min    (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  max    (a,c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  inc    (a,  sync); }
// { volatile atomic<cmplx,cpp> a(0);  preinc (a,  sync); }
// { volatile atomic<cmplx,cpp> a(0);  postinc(a,  sync); }
// { volatile atomic<cmplx,cpp> a(0);  dec    (a,  sync); }
// { volatile atomic<cmplx,cpp> a(0);  predec (a,  sync); }
// { volatile atomic<cmplx,cpp> a(0);  postdec(a,  sync); }
// { volatile atomic<cmplx,cpp> a(0);  add    (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  sub    (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  mul    (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  div    (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  mod    (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  lshift (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  rshift (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  andeq  (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  oreq   (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  xoreq  (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  min    (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  max    (a,c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  inc    (a,  success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  preinc (a,  success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  postinc(a,  success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  dec    (a,  success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  predec (a,  success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { volatile atomic<cmplx,kokkos> a(0);  add    (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  sub    (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  mul    (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  div    (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  mod    (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  lshift (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  rshift (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  andeq  (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  oreq   (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  xoreq  (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  min    (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  max    (a,c); }
// { volatile atomic<cmplx,kokkos> a(0);  inc    (a); }
// { volatile atomic<cmplx,kokkos> a(0);  preinc (a); }
// { volatile atomic<cmplx,kokkos> a(0);  postinc(a); }
// { volatile atomic<cmplx,kokkos> a(0);  dec    (a); }
// { volatile atomic<cmplx,kokkos> a(0);  predec (a); }
// { volatile atomic<cmplx,kokkos> a(0);  postdec(a); }
// { volatile atomic<cmplx,kokkos> a(0);  add    (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  sub    (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  mul    (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  div    (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  mod    (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  lshift (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  rshift (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  andeq  (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  oreq   (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  xoreq  (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  min    (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  max    (a,c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  inc    (a,  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  preinc (a,  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  postinc(a,  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  dec    (a,  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  predec (a,  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  postdec(a,  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  add    (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  sub    (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  mul    (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  div    (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  mod    (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  lshift (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  rshift (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  andeq  (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  oreq   (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  xoreq  (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  min    (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  max    (a,c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  inc    (a,  success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  preinc (a,  success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  postinc(a,  success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  dec    (a,  success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  predec (a,  success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  postdec(a,  success,failure); }
#endif

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong> a(0);  add    (a,c); }
   { volatile atomic<cmplx,strong> a(0);  sub    (a,c); }
   { volatile atomic<cmplx,strong> a(0);  mul    (a,c); }
   { volatile atomic<cmplx,strong> a(0);  div    (a,c); }
#endif
// { volatile atomic<cmplx,strong> a(0);  mod    (a,c); }
// { volatile atomic<cmplx,strong> a(0);  lshift (a,c); }
// { volatile atomic<cmplx,strong> a(0);  rshift (a,c); }
// { volatile atomic<cmplx,strong> a(0);  andeq  (a,c); }
// { volatile atomic<cmplx,strong> a(0);  oreq   (a,c); }
// { volatile atomic<cmplx,strong> a(0);  xoreq  (a,c); }
// { volatile atomic<cmplx,strong> a(0);  min    (a,c); }
// { volatile atomic<cmplx,strong> a(0);  max    (a,c); }
// { volatile atomic<cmplx,strong> a(0);  inc    (a); }
// { volatile atomic<cmplx,strong> a(0);  preinc (a); }
// { volatile atomic<cmplx,strong> a(0);  postinc(a); }
// { volatile atomic<cmplx,strong> a(0);  dec    (a); }
// { volatile atomic<cmplx,strong> a(0);  predec (a); }
// { volatile atomic<cmplx,strong> a(0);  postdec(a); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong> a(0);  add    (a,c,sync); }
   { volatile atomic<cmplx,strong> a(0);  sub    (a,c,sync); }
   { volatile atomic<cmplx,strong> a(0);  mul    (a,c,sync); }
   { volatile atomic<cmplx,strong> a(0);  div    (a,c,sync); }
#endif
// { volatile atomic<cmplx,strong> a(0);  mod    (a,c,sync); }
// { volatile atomic<cmplx,strong> a(0);  lshift (a,c,sync); }
// { volatile atomic<cmplx,strong> a(0);  rshift (a,c,sync); }
// { volatile atomic<cmplx,strong> a(0);  andeq  (a,c,sync); }
// { volatile atomic<cmplx,strong> a(0);  oreq   (a,c,sync); }
// { volatile atomic<cmplx,strong> a(0);  xoreq  (a,c,sync); }
// { volatile atomic<cmplx,strong> a(0);  min    (a,c,sync); }
// { volatile atomic<cmplx,strong> a(0);  max    (a,c,sync); }
// { volatile atomic<cmplx,strong> a(0);  inc    (a,  sync); }
// { volatile atomic<cmplx,strong> a(0);  preinc (a,  sync); }
// { volatile atomic<cmplx,strong> a(0);  postinc(a,  sync); }
// { volatile atomic<cmplx,strong> a(0);  dec    (a,  sync); }
// { volatile atomic<cmplx,strong> a(0);  predec (a,  sync); }
// { volatile atomic<cmplx,strong> a(0);  postdec(a,  sync); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong> a(0);  add    (a,c,success,failure); }
   { volatile atomic<cmplx,strong> a(0);  sub    (a,c,success,failure); }
   { volatile atomic<cmplx,strong> a(0);  mul    (a,c,success,failure); }
   { volatile atomic<cmplx,strong> a(0);  div    (a,c,success,failure); }
#endif
// { volatile atomic<cmplx,strong> a(0);  mod    (a,c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  lshift (a,c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  rshift (a,c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  andeq  (a,c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  oreq   (a,c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  xoreq  (a,c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  min    (a,c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  max    (a,c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  inc    (a,  success,failure); }
// { volatile atomic<cmplx,strong> a(0);  preinc (a,  success,failure); }
// { volatile atomic<cmplx,strong> a(0);  postinc(a,  success,failure); }
// { volatile atomic<cmplx,strong> a(0);  dec    (a,  success,failure); }
// { volatile atomic<cmplx,strong> a(0);  predec (a,  success,failure); }
// { volatile atomic<cmplx,strong> a(0);  postdec(a,  success,failure); }

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong::pun> a(0);  add    (a,c); }
   { volatile atomic<cmplx,strong::pun> a(0);  sub    (a,c); }
   { volatile atomic<cmplx,strong::pun> a(0);  mul    (a,c); }
   { volatile atomic<cmplx,strong::pun> a(0);  div    (a,c); }
#endif
// { volatile atomic<cmplx,strong::pun> a(0);  mod    (a,c); }
// { volatile atomic<cmplx,strong::pun> a(0);  lshift (a,c); }
// { volatile atomic<cmplx,strong::pun> a(0);  rshift (a,c); }
// { volatile atomic<cmplx,strong::pun> a(0);  andeq  (a,c); }
// { volatile atomic<cmplx,strong::pun> a(0);  oreq   (a,c); }
// { volatile atomic<cmplx,strong::pun> a(0);  xoreq  (a,c); }
// { volatile atomic<cmplx,strong::pun> a(0);  min    (a,c); }
// { volatile atomic<cmplx,strong::pun> a(0);  max    (a,c); }
// { volatile atomic<cmplx,strong::pun> a(0);  inc    (a); }
// { volatile atomic<cmplx,strong::pun> a(0);  preinc (a); }
// { volatile atomic<cmplx,strong::pun> a(0);  postinc(a); }
// { volatile atomic<cmplx,strong::pun> a(0);  dec    (a); }
// { volatile atomic<cmplx,strong::pun> a(0);  predec (a); }
// { volatile atomic<cmplx,strong::pun> a(0);  postdec(a); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong::pun> a(0);  add    (a,c,sync); }
   { volatile atomic<cmplx,strong::pun> a(0);  sub    (a,c,sync); }
   { volatile atomic<cmplx,strong::pun> a(0);  mul    (a,c,sync); }
   { volatile atomic<cmplx,strong::pun> a(0);  div    (a,c,sync); }
#endif
// { volatile atomic<cmplx,strong::pun> a(0);  mod    (a,c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  lshift (a,c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  rshift (a,c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  andeq  (a,c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  oreq   (a,c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  xoreq  (a,c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  min    (a,c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  max    (a,c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  inc    (a,  sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  preinc (a,  sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  postinc(a,  sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  dec    (a,  sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  predec (a,  sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  postdec(a,  sync); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong::pun> a(0);  add    (a,c,success,failure); }
   { volatile atomic<cmplx,strong::pun> a(0);  sub    (a,c,success,failure); }
   { volatile atomic<cmplx,strong::pun> a(0);  mul    (a,c,success,failure); }
   { volatile atomic<cmplx,strong::pun> a(0);  div    (a,c,success,failure); }
#endif
// { volatile atomic<cmplx,strong::pun> a(0);  mod    (a,c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  lshift (a,c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  rshift (a,c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  andeq  (a,c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  oreq   (a,c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  xoreq  (a,c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  min    (a,c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  max    (a,c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  inc    (a,  success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  preinc (a,  success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  postinc(a,  success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  dec    (a,  success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  predec (a,  success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  postdec(a,  success,failure); }

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak> a(0);  add    (a,c); }
   { volatile atomic<cmplx,weak> a(0);  sub    (a,c); }
   { volatile atomic<cmplx,weak> a(0);  mul    (a,c); }
   { volatile atomic<cmplx,weak> a(0);  div    (a,c); }
#endif
// { volatile atomic<cmplx,weak> a(0);  mod    (a,c); }
// { volatile atomic<cmplx,weak> a(0);  lshift (a,c); }
// { volatile atomic<cmplx,weak> a(0);  rshift (a,c); }
// { volatile atomic<cmplx,weak> a(0);  andeq  (a,c); }
// { volatile atomic<cmplx,weak> a(0);  oreq   (a,c); }
// { volatile atomic<cmplx,weak> a(0);  xoreq  (a,c); }
// { volatile atomic<cmplx,weak> a(0);  min    (a,c); }
// { volatile atomic<cmplx,weak> a(0);  max    (a,c); }
// { volatile atomic<cmplx,weak> a(0);  inc    (a); }
// { volatile atomic<cmplx,weak> a(0);  preinc (a); }
// { volatile atomic<cmplx,weak> a(0);  postinc(a); }
// { volatile atomic<cmplx,weak> a(0);  dec    (a); }
// { volatile atomic<cmplx,weak> a(0);  predec (a); }
// { volatile atomic<cmplx,weak> a(0);  postdec(a); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak> a(0);  add    (a,c,sync); }
   { volatile atomic<cmplx,weak> a(0);  sub    (a,c,sync); }
   { volatile atomic<cmplx,weak> a(0);  mul    (a,c,sync); }
   { volatile atomic<cmplx,weak> a(0);  div    (a,c,sync); }
#endif
// { volatile atomic<cmplx,weak> a(0);  mod    (a,c,sync); }
// { volatile atomic<cmplx,weak> a(0);  lshift (a,c,sync); }
// { volatile atomic<cmplx,weak> a(0);  rshift (a,c,sync); }
// { volatile atomic<cmplx,weak> a(0);  andeq  (a,c,sync); }
// { volatile atomic<cmplx,weak> a(0);  oreq   (a,c,sync); }
// { volatile atomic<cmplx,weak> a(0);  xoreq  (a,c,sync); }
// { volatile atomic<cmplx,weak> a(0);  min    (a,c,sync); }
// { volatile atomic<cmplx,weak> a(0);  max    (a,c,sync); }
// { volatile atomic<cmplx,weak> a(0);  inc    (a,  sync); }
// { volatile atomic<cmplx,weak> a(0);  preinc (a,  sync); }
// { volatile atomic<cmplx,weak> a(0);  postinc(a,  sync); }
// { volatile atomic<cmplx,weak> a(0);  dec    (a,  sync); }
// { volatile atomic<cmplx,weak> a(0);  predec (a,  sync); }
// { volatile atomic<cmplx,weak> a(0);  postdec(a,  sync); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak> a(0);  add    (a,c,success,failure); }
   { volatile atomic<cmplx,weak> a(0);  sub    (a,c,success,failure); }
   { volatile atomic<cmplx,weak> a(0);  mul    (a,c,success,failure); }
   { volatile atomic<cmplx,weak> a(0);  div    (a,c,success,failure); }
#endif
// { volatile atomic<cmplx,weak> a(0);  mod    (a,c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  lshift (a,c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  rshift (a,c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  andeq  (a,c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  oreq   (a,c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  xoreq  (a,c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  min    (a,c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  max    (a,c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  inc    (a,  success,failure); }
// { volatile atomic<cmplx,weak> a(0);  preinc (a,  success,failure); }
// { volatile atomic<cmplx,weak> a(0);  postinc(a,  success,failure); }
// { volatile atomic<cmplx,weak> a(0);  dec    (a,  success,failure); }
// { volatile atomic<cmplx,weak> a(0);  predec (a,  success,failure); }
// { volatile atomic<cmplx,weak> a(0);  postdec(a,  success,failure); }

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak::pun> a(0);  add    (a,c); }
   { volatile atomic<cmplx,weak::pun> a(0);  sub    (a,c); }
   { volatile atomic<cmplx,weak::pun> a(0);  mul    (a,c); }
   { volatile atomic<cmplx,weak::pun> a(0);  div    (a,c); }
#endif
// { volatile atomic<cmplx,weak::pun> a(0);  mod    (a,c); }
// { volatile atomic<cmplx,weak::pun> a(0);  lshift (a,c); }
// { volatile atomic<cmplx,weak::pun> a(0);  rshift (a,c); }
// { volatile atomic<cmplx,weak::pun> a(0);  andeq  (a,c); }
// { volatile atomic<cmplx,weak::pun> a(0);  oreq   (a,c); }
// { volatile atomic<cmplx,weak::pun> a(0);  xoreq  (a,c); }
// { volatile atomic<cmplx,weak::pun> a(0);  min    (a,c); }
// { volatile atomic<cmplx,weak::pun> a(0);  max    (a,c); }
// { volatile atomic<cmplx,weak::pun> a(0);  inc    (a); }
// { volatile atomic<cmplx,weak::pun> a(0);  preinc (a); }
// { volatile atomic<cmplx,weak::pun> a(0);  postinc(a); }
// { volatile atomic<cmplx,weak::pun> a(0);  dec    (a); }
// { volatile atomic<cmplx,weak::pun> a(0);  predec (a); }
// { volatile atomic<cmplx,weak::pun> a(0);  postdec(a); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak::pun> a(0);  add    (a,c,sync); }
   { volatile atomic<cmplx,weak::pun> a(0);  sub    (a,c,sync); }
   { volatile atomic<cmplx,weak::pun> a(0);  mul    (a,c,sync); }
   { volatile atomic<cmplx,weak::pun> a(0);  div    (a,c,sync); }
#endif
// { volatile atomic<cmplx,weak::pun> a(0);  mod    (a,c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  lshift (a,c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  rshift (a,c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  andeq  (a,c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  oreq   (a,c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  xoreq  (a,c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  min    (a,c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  max    (a,c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  inc    (a,  sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  preinc (a,  sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  postinc(a,  sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  dec    (a,  sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  predec (a,  sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  postdec(a,  sync); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak::pun> a(0);  add    (a,c,success,failure); }
   { volatile atomic<cmplx,weak::pun> a(0);  sub    (a,c,success,failure); }
   { volatile atomic<cmplx,weak::pun> a(0);  mul    (a,c,success,failure); }
   { volatile atomic<cmplx,weak::pun> a(0);  div    (a,c,success,failure); }
#endif
// { volatile atomic<cmplx,weak::pun> a(0);  mod    (a,c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  lshift (a,c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  rshift (a,c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  andeq  (a,c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  oreq   (a,c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  xoreq  (a,c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  min    (a,c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  max    (a,c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  inc    (a,  success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  preinc (a,  success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  postinc(a,  success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  dec    (a,  success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  predec (a,  success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  postdec(a,  success,failure); }

//v{ volatile atomic<cmplx,lock> a(0);  add    (a,c); }
//v{ volatile atomic<cmplx,lock> a(0);  sub    (a,c); }
//v{ volatile atomic<cmplx,lock> a(0);  mul    (a,c); }
//v{ volatile atomic<cmplx,lock> a(0);  div    (a,c); }
// { volatile atomic<cmplx,lock> a(0);  mod    (a,c); }
// { volatile atomic<cmplx,lock> a(0);  lshift (a,c); }
// { volatile atomic<cmplx,lock> a(0);  rshift (a,c); }
// { volatile atomic<cmplx,lock> a(0);  andeq  (a,c); }
// { volatile atomic<cmplx,lock> a(0);  oreq   (a,c); }
// { volatile atomic<cmplx,lock> a(0);  xoreq  (a,c); }
// { volatile atomic<cmplx,lock> a(0);  min    (a,c); }
// { volatile atomic<cmplx,lock> a(0);  max    (a,c); }
// { volatile atomic<cmplx,lock> a(0);  inc    (a); }
// { volatile atomic<cmplx,lock> a(0);  preinc (a); }
// { volatile atomic<cmplx,lock> a(0);  postinc(a); }
// { volatile atomic<cmplx,lock> a(0);  dec    (a); }
// { volatile atomic<cmplx,lock> a(0);  predec (a); }
// { volatile atomic<cmplx,lock> a(0);  postdec(a); }
// { volatile atomic<cmplx,lock> a(0);  add    (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  sub    (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  mul    (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  div    (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  mod    (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  lshift (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  rshift (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  andeq  (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  oreq   (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  xoreq  (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  min    (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  max    (a,c,sync); }
// { volatile atomic<cmplx,lock> a(0);  inc    (a,  sync); }
// { volatile atomic<cmplx,lock> a(0);  preinc (a,  sync); }
// { volatile atomic<cmplx,lock> a(0);  postinc(a,  sync); }
// { volatile atomic<cmplx,lock> a(0);  dec    (a,  sync); }
// { volatile atomic<cmplx,lock> a(0);  predec (a,  sync); }
// { volatile atomic<cmplx,lock> a(0);  postdec(a,  sync); }
// { volatile atomic<cmplx,lock> a(0);  add    (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  sub    (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  mul    (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  div    (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  mod    (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  lshift (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  rshift (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  andeq  (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  oreq   (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  xoreq  (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  min    (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  max    (a,c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  inc    (a,  success,failure); }
// { volatile atomic<cmplx,lock> a(0);  preinc (a,  success,failure); }
// { volatile atomic<cmplx,lock> a(0);  postinc(a,  success,failure); }
// { volatile atomic<cmplx,lock> a(0);  dec    (a,  success,failure); }
// { volatile atomic<cmplx,lock> a(0);  predec (a,  success,failure); }
// { volatile atomic<cmplx,lock> a(0);  postdec(a,  success,failure); }

//v{ volatile atomic<cmplx,serial> a(0);  add    (a,c); }
//v{ volatile atomic<cmplx,serial> a(0);  sub    (a,c); }
//v{ volatile atomic<cmplx,serial> a(0);  mul    (a,c); }
//v{ volatile atomic<cmplx,serial> a(0);  div    (a,c); }
// { volatile atomic<cmplx,serial> a(0);  mod    (a,c); }
// { volatile atomic<cmplx,serial> a(0);  lshift (a,c); }
// { volatile atomic<cmplx,serial> a(0);  rshift (a,c); }
// { volatile atomic<cmplx,serial> a(0);  andeq  (a,c); }
// { volatile atomic<cmplx,serial> a(0);  oreq   (a,c); }
// { volatile atomic<cmplx,serial> a(0);  xoreq  (a,c); }
// { volatile atomic<cmplx,serial> a(0);  min    (a,c); }
// { volatile atomic<cmplx,serial> a(0);  max    (a,c); }
// { volatile atomic<cmplx,serial> a(0);  inc    (a); }
// { volatile atomic<cmplx,serial> a(0);  preinc (a); }
// { volatile atomic<cmplx,serial> a(0);  postinc(a); }
// { volatile atomic<cmplx,serial> a(0);  dec    (a); }
// { volatile atomic<cmplx,serial> a(0);  predec (a); }
// { volatile atomic<cmplx,serial> a(0);  postdec(a); }
// { volatile atomic<cmplx,serial> a(0);  add    (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  sub    (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  mul    (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  div    (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  mod    (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  lshift (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  rshift (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  andeq  (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  oreq   (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  xoreq  (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  min    (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  max    (a,c,sync); }
// { volatile atomic<cmplx,serial> a(0);  inc    (a,  sync); }
// { volatile atomic<cmplx,serial> a(0);  preinc (a,  sync); }
// { volatile atomic<cmplx,serial> a(0);  postinc(a,  sync); }
// { volatile atomic<cmplx,serial> a(0);  dec    (a,  sync); }
// { volatile atomic<cmplx,serial> a(0);  predec (a,  sync); }
// { volatile atomic<cmplx,serial> a(0);  postdec(a,  sync); }
// { volatile atomic<cmplx,serial> a(0);  add    (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  sub    (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  mul    (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  div    (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  mod    (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  lshift (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  rshift (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  andeq  (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  oreq   (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  xoreq  (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  min    (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  max    (a,c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  inc    (a,  success,failure); }
// { volatile atomic<cmplx,serial> a(0);  preinc (a,  success,failure); }
// { volatile atomic<cmplx,serial> a(0);  postinc(a,  success,failure); }
// { volatile atomic<cmplx,serial> a(0);  dec    (a,  success,failure); }
// { volatile atomic<cmplx,serial> a(0);  predec (a,  success,failure); }
// { volatile atomic<cmplx,serial> a(0);  postdec(a,  success,failure); }



   // ------------------------
   // foo
   // ------------------------

// { volatile atomic<foo,cpp> a(0);  add    (a,b); }
// { volatile atomic<foo,cpp> a(0);  sub    (a,b); }
// { volatile atomic<foo,cpp> a(0);  mul    (a,b); }
// { volatile atomic<foo,cpp> a(0);  div    (a,b); }
// { volatile atomic<foo,cpp> a(0);  mod    (a,b); }
// { volatile atomic<foo,cpp> a(0);  lshift (a,b); }
// { volatile atomic<foo,cpp> a(0);  rshift (a,b); }
// { volatile atomic<foo,cpp> a(0);  andeq  (a,b); }
// { volatile atomic<foo,cpp> a(0);  oreq   (a,b); }
// { volatile atomic<foo,cpp> a(0);  xoreq  (a,b); }
// { volatile atomic<foo,cpp> a(0);  min    (a,b); }
// { volatile atomic<foo,cpp> a(0);  max    (a,b); }
// { volatile atomic<foo,cpp> a(0);  inc    (a); }
// { volatile atomic<foo,cpp> a(0);  preinc (a); }
// { volatile atomic<foo,cpp> a(0);  postinc(a); }
// { volatile atomic<foo,cpp> a(0);  dec    (a); }
// { volatile atomic<foo,cpp> a(0);  predec (a); }
// { volatile atomic<foo,cpp> a(0);  postdec(a); }
// { volatile atomic<foo,cpp> a(0);  add    (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  sub    (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  mul    (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  div    (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  mod    (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  lshift (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  rshift (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  andeq  (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  oreq   (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  xoreq  (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  min    (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  max    (a,b,sync); }
// { volatile atomic<foo,cpp> a(0);  inc    (a,  sync); }
// { volatile atomic<foo,cpp> a(0);  preinc (a,  sync); }
// { volatile atomic<foo,cpp> a(0);  postinc(a,  sync); }
// { volatile atomic<foo,cpp> a(0);  dec    (a,  sync); }
// { volatile atomic<foo,cpp> a(0);  predec (a,  sync); }
// { volatile atomic<foo,cpp> a(0);  postdec(a,  sync); }
// { volatile atomic<foo,cpp> a(0);  add    (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  sub    (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  mul    (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  div    (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  mod    (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  lshift (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  rshift (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  andeq  (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  oreq   (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  xoreq  (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  min    (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  max    (a,b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  inc    (a,  success,failure); }
// { volatile atomic<foo,cpp> a(0);  preinc (a,  success,failure); }
// { volatile atomic<foo,cpp> a(0);  postinc(a,  success,failure); }
// { volatile atomic<foo,cpp> a(0);  dec    (a,  success,failure); }
// { volatile atomic<foo,cpp> a(0);  predec (a,  success,failure); }
// { volatile atomic<foo,cpp> a(0);  postdec(a,  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { volatile atomic<foo,kokkos> a(0);  add    (a,b); }
// { volatile atomic<foo,kokkos> a(0);  sub    (a,b); }
// { volatile atomic<foo,kokkos> a(0);  mul    (a,b); }
// { volatile atomic<foo,kokkos> a(0);  div    (a,b); }
// { volatile atomic<foo,kokkos> a(0);  mod    (a,b); }
// { volatile atomic<foo,kokkos> a(0);  lshift (a,b); }
// { volatile atomic<foo,kokkos> a(0);  rshift (a,b); }
// { volatile atomic<foo,kokkos> a(0);  andeq  (a,b); }
// { volatile atomic<foo,kokkos> a(0);  oreq   (a,b); }
// { volatile atomic<foo,kokkos> a(0);  xoreq  (a,b); }
// { volatile atomic<foo,kokkos> a(0);  min    (a,b); }
// { volatile atomic<foo,kokkos> a(0);  max    (a,b); }
// { volatile atomic<foo,kokkos> a(0);  inc    (a); }
// { volatile atomic<foo,kokkos> a(0);  preinc (a); }
// { volatile atomic<foo,kokkos> a(0);  postinc(a); }
// { volatile atomic<foo,kokkos> a(0);  dec    (a); }
// { volatile atomic<foo,kokkos> a(0);  predec (a); }
// { volatile atomic<foo,kokkos> a(0);  postdec(a); }
// { volatile atomic<foo,kokkos> a(0);  add    (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  sub    (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  mul    (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  div    (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  mod    (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  lshift (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  rshift (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  andeq  (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  oreq   (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  xoreq  (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  min    (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  max    (a,b,sync); }
// { volatile atomic<foo,kokkos> a(0);  inc    (a,  sync); }
// { volatile atomic<foo,kokkos> a(0);  preinc (a,  sync); }
// { volatile atomic<foo,kokkos> a(0);  postinc(a,  sync); }
// { volatile atomic<foo,kokkos> a(0);  dec    (a,  sync); }
// { volatile atomic<foo,kokkos> a(0);  predec (a,  sync); }
// { volatile atomic<foo,kokkos> a(0);  postdec(a,  sync); }
// { volatile atomic<foo,kokkos> a(0);  add    (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  sub    (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  mul    (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  div    (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  mod    (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  lshift (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  rshift (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  andeq  (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  oreq   (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  xoreq  (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  min    (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  max    (a,b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  inc    (a,  success,failure); }
// { volatile atomic<foo,kokkos> a(0);  preinc (a,  success,failure); }
// { volatile atomic<foo,kokkos> a(0);  postinc(a,  success,failure); }
// { volatile atomic<foo,kokkos> a(0);  dec    (a,  success,failure); }
// { volatile atomic<foo,kokkos> a(0);  predec (a,  success,failure); }
// { volatile atomic<foo,kokkos> a(0);  postdec(a,  success,failure); }
#endif

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,strong> a(0);  add    (a,b); }
   { volatile atomic<foo,strong> a(0);  sub    (a,b); }
   { volatile atomic<foo,strong> a(0);  mul    (a,b); }
   { volatile atomic<foo,strong> a(0);  div    (a,b); }
   { volatile atomic<foo,strong> a(0);  mod    (a,b); }
   { volatile atomic<foo,strong> a(0);  lshift (a,b); }
   { volatile atomic<foo,strong> a(0);  rshift (a,b); }
   { volatile atomic<foo,strong> a(0);  andeq  (a,b); }
   { volatile atomic<foo,strong> a(0);  oreq   (a,b); }
   { volatile atomic<foo,strong> a(0);  xoreq  (a,b); }
   { volatile atomic<foo,strong> a(0);  min    (a,b); }
   { volatile atomic<foo,strong> a(0);  max    (a,b); }
   { volatile atomic<foo,strong> a(0);  inc    (a); }
   { volatile atomic<foo,strong> a(0);  preinc (a); }
   { volatile atomic<foo,strong> a(0);  postinc(a); }
   { volatile atomic<foo,strong> a(0);  dec    (a); }
   { volatile atomic<foo,strong> a(0);  predec (a); }
   { volatile atomic<foo,strong> a(0);  postdec(a); }
   { volatile atomic<foo,strong> a(0);  add    (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  sub    (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  mul    (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  div    (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  mod    (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  lshift (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  rshift (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  andeq  (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  oreq   (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  xoreq  (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  min    (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  max    (a,b,sync); }
   { volatile atomic<foo,strong> a(0);  inc    (a,  sync); }
   { volatile atomic<foo,strong> a(0);  preinc (a,  sync); }
   { volatile atomic<foo,strong> a(0);  postinc(a,  sync); }
   { volatile atomic<foo,strong> a(0);  dec    (a,  sync); }
   { volatile atomic<foo,strong> a(0);  predec (a,  sync); }
   { volatile atomic<foo,strong> a(0);  postdec(a,  sync); }
   { volatile atomic<foo,strong> a(0);  add    (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  sub    (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  mul    (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  div    (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  mod    (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  lshift (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  rshift (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  andeq  (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  oreq   (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  xoreq  (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  min    (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  max    (a,b,success,failure); }
   { volatile atomic<foo,strong> a(0);  inc    (a,  success,failure); }
   { volatile atomic<foo,strong> a(0);  preinc (a,  success,failure); }
   { volatile atomic<foo,strong> a(0);  postinc(a,  success,failure); }
   { volatile atomic<foo,strong> a(0);  dec    (a,  success,failure); }
   { volatile atomic<foo,strong> a(0);  predec (a,  success,failure); }
   { volatile atomic<foo,strong> a(0);  postdec(a,  success,failure); }
#endif

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,strong::pun> a(0);  add    (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  sub    (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  mul    (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  div    (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  mod    (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  lshift (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  rshift (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  andeq  (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  oreq   (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  xoreq  (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  min    (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  max    (a,b); }
   { volatile atomic<foo,strong::pun> a(0);  inc    (a); }
   { volatile atomic<foo,strong::pun> a(0);  preinc (a); }
   { volatile atomic<foo,strong::pun> a(0);  postinc(a); }
   { volatile atomic<foo,strong::pun> a(0);  dec    (a); }
   { volatile atomic<foo,strong::pun> a(0);  predec (a); }
   { volatile atomic<foo,strong::pun> a(0);  postdec(a); }
   { volatile atomic<foo,strong::pun> a(0);  add    (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  sub    (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  mul    (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  div    (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  mod    (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  lshift (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  rshift (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  andeq  (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  oreq   (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  xoreq  (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  min    (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  max    (a,b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  inc    (a,  sync); }
   { volatile atomic<foo,strong::pun> a(0);  preinc (a,  sync); }
   { volatile atomic<foo,strong::pun> a(0);  postinc(a,  sync); }
   { volatile atomic<foo,strong::pun> a(0);  dec    (a,  sync); }
   { volatile atomic<foo,strong::pun> a(0);  predec (a,  sync); }
   { volatile atomic<foo,strong::pun> a(0);  postdec(a,  sync); }
   { volatile atomic<foo,strong::pun> a(0);  add    (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  sub    (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  mul    (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  div    (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  mod    (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  lshift (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  rshift (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  andeq  (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  oreq   (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  xoreq  (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  min    (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  max    (a,b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  inc    (a,  success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  preinc (a,  success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  postinc(a,  success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  dec    (a,  success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  predec (a,  success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  postdec(a,  success,failure); }
#endif

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,weak> a(0);  add    (a,b); }
   { volatile atomic<foo,weak> a(0);  sub    (a,b); }
   { volatile atomic<foo,weak> a(0);  mul    (a,b); }
   { volatile atomic<foo,weak> a(0);  div    (a,b); }
   { volatile atomic<foo,weak> a(0);  mod    (a,b); }
   { volatile atomic<foo,weak> a(0);  lshift (a,b); }
   { volatile atomic<foo,weak> a(0);  rshift (a,b); }
   { volatile atomic<foo,weak> a(0);  andeq  (a,b); }
   { volatile atomic<foo,weak> a(0);  oreq   (a,b); }
   { volatile atomic<foo,weak> a(0);  xoreq  (a,b); }
   { volatile atomic<foo,weak> a(0);  min    (a,b); }
   { volatile atomic<foo,weak> a(0);  max    (a,b); }
   { volatile atomic<foo,weak> a(0);  inc    (a); }
   { volatile atomic<foo,weak> a(0);  preinc (a); }
   { volatile atomic<foo,weak> a(0);  postinc(a); }
   { volatile atomic<foo,weak> a(0);  dec    (a); }
   { volatile atomic<foo,weak> a(0);  predec (a); }
   { volatile atomic<foo,weak> a(0);  postdec(a); }
   { volatile atomic<foo,weak> a(0);  add    (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  sub    (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  mul    (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  div    (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  mod    (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  lshift (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  rshift (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  andeq  (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  oreq   (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  xoreq  (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  min    (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  max    (a,b,sync); }
   { volatile atomic<foo,weak> a(0);  inc    (a,  sync); }
   { volatile atomic<foo,weak> a(0);  preinc (a,  sync); }
   { volatile atomic<foo,weak> a(0);  postinc(a,  sync); }
   { volatile atomic<foo,weak> a(0);  dec    (a,  sync); }
   { volatile atomic<foo,weak> a(0);  predec (a,  sync); }
   { volatile atomic<foo,weak> a(0);  postdec(a,  sync); }
   { volatile atomic<foo,weak> a(0);  add    (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  sub    (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  mul    (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  div    (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  mod    (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  lshift (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  rshift (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  andeq  (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  oreq   (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  xoreq  (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  min    (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  max    (a,b,success,failure); }
   { volatile atomic<foo,weak> a(0);  inc    (a,  success,failure); }
   { volatile atomic<foo,weak> a(0);  preinc (a,  success,failure); }
   { volatile atomic<foo,weak> a(0);  postinc(a,  success,failure); }
   { volatile atomic<foo,weak> a(0);  dec    (a,  success,failure); }
   { volatile atomic<foo,weak> a(0);  predec (a,  success,failure); }
   { volatile atomic<foo,weak> a(0);  postdec(a,  success,failure); }
#endif

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,weak::pun> a(0);  add    (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  sub    (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  mul    (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  div    (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  mod    (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  lshift (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  rshift (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  andeq  (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  oreq   (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  xoreq  (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  min    (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  max    (a,b); }
   { volatile atomic<foo,weak::pun> a(0);  inc    (a); }
   { volatile atomic<foo,weak::pun> a(0);  preinc (a); }
   { volatile atomic<foo,weak::pun> a(0);  postinc(a); }
   { volatile atomic<foo,weak::pun> a(0);  dec    (a); }
   { volatile atomic<foo,weak::pun> a(0);  predec (a); }
   { volatile atomic<foo,weak::pun> a(0);  postdec(a); }
   { volatile atomic<foo,weak::pun> a(0);  add    (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  sub    (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  mul    (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  div    (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  mod    (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  lshift (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  rshift (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  andeq  (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  oreq   (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  xoreq  (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  min    (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  max    (a,b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  inc    (a,  sync); }
   { volatile atomic<foo,weak::pun> a(0);  preinc (a,  sync); }
   { volatile atomic<foo,weak::pun> a(0);  postinc(a,  sync); }
   { volatile atomic<foo,weak::pun> a(0);  dec    (a,  sync); }
   { volatile atomic<foo,weak::pun> a(0);  predec (a,  sync); }
   { volatile atomic<foo,weak::pun> a(0);  postdec(a,  sync); }
   { volatile atomic<foo,weak::pun> a(0);  add    (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  sub    (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  mul    (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  div    (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  mod    (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  lshift (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  rshift (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  andeq  (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  oreq   (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  xoreq  (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  min    (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  max    (a,b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  inc    (a,  success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  preinc (a,  success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  postinc(a,  success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  dec    (a,  success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  predec (a,  success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  postdec(a,  success,failure); }
#endif

//v{ volatile atomic<foo,lock> a(0);  add    (a,b); }
//v{ volatile atomic<foo,lock> a(0);  sub    (a,b); }
//v{ volatile atomic<foo,lock> a(0);  mul    (a,b); }
//v{ volatile atomic<foo,lock> a(0);  div    (a,b); }
//v{ volatile atomic<foo,lock> a(0);  mod    (a,b); }
//v{ volatile atomic<foo,lock> a(0);  lshift (a,b); }
//v{ volatile atomic<foo,lock> a(0);  rshift (a,b); }
//v{ volatile atomic<foo,lock> a(0);  andeq  (a,b); }
//v{ volatile atomic<foo,lock> a(0);  oreq   (a,b); }
//v{ volatile atomic<foo,lock> a(0);  xoreq  (a,b); }
//v{ volatile atomic<foo,lock> a(0);  min    (a,b); }
//v{ volatile atomic<foo,lock> a(0);  max    (a,b); }
//v{ volatile atomic<foo,lock> a(0);  inc    (a); }
//v{ volatile atomic<foo,lock> a(0);  preinc (a); }
//v{ volatile atomic<foo,lock> a(0);  postinc(a); }
//v{ volatile atomic<foo,lock> a(0);  dec    (a); }
//v{ volatile atomic<foo,lock> a(0);  predec (a); }
//v{ volatile atomic<foo,lock> a(0);  postdec(a); }
// { volatile atomic<foo,lock> a(0);  add    (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  sub    (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  mul    (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  div    (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  mod    (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  lshift (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  rshift (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  andeq  (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  oreq   (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  xoreq  (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  min    (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  max    (a,b,sync); }
// { volatile atomic<foo,lock> a(0);  inc    (a,  sync); }
// { volatile atomic<foo,lock> a(0);  preinc (a,  sync); }
// { volatile atomic<foo,lock> a(0);  postinc(a,  sync); }
// { volatile atomic<foo,lock> a(0);  dec    (a,  sync); }
// { volatile atomic<foo,lock> a(0);  predec (a,  sync); }
// { volatile atomic<foo,lock> a(0);  postdec(a,  sync); }
// { volatile atomic<foo,lock> a(0);  add    (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  sub    (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  mul    (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  div    (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  mod    (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  lshift (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  rshift (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  andeq  (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  oreq   (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  xoreq  (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  min    (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  max    (a,b,success,failure); }
// { volatile atomic<foo,lock> a(0);  inc    (a,  success,failure); }
// { volatile atomic<foo,lock> a(0);  preinc (a,  success,failure); }
// { volatile atomic<foo,lock> a(0);  postinc(a,  success,failure); }
// { volatile atomic<foo,lock> a(0);  dec    (a,  success,failure); }
// { volatile atomic<foo,lock> a(0);  predec (a,  success,failure); }
// { volatile atomic<foo,lock> a(0);  postdec(a,  success,failure); }

//v{ volatile atomic<foo,serial> a(0);  add    (a,b); }
//v{ volatile atomic<foo,serial> a(0);  sub    (a,b); }
//v{ volatile atomic<foo,serial> a(0);  mul    (a,b); }
//v{ volatile atomic<foo,serial> a(0);  div    (a,b); }
//v{ volatile atomic<foo,serial> a(0);  mod    (a,b); }
//v{ volatile atomic<foo,serial> a(0);  lshift (a,b); }
//v{ volatile atomic<foo,serial> a(0);  rshift (a,b); }
//v{ volatile atomic<foo,serial> a(0);  andeq  (a,b); }
//v{ volatile atomic<foo,serial> a(0);  oreq   (a,b); }
//v{ volatile atomic<foo,serial> a(0);  xoreq  (a,b); }
//v{ volatile atomic<foo,serial> a(0);  min    (a,b); }
//v{ volatile atomic<foo,serial> a(0);  max    (a,b); }
//v{ volatile atomic<foo,serial> a(0);  inc    (a); }
//v{ volatile atomic<foo,serial> a(0);  preinc (a); }
//v{ volatile atomic<foo,serial> a(0);  postinc(a); }
//v{ volatile atomic<foo,serial> a(0);  dec    (a); }
//v{ volatile atomic<foo,serial> a(0);  predec (a); }
//v{ volatile atomic<foo,serial> a(0);  postdec(a); }
// { volatile atomic<foo,serial> a(0);  add    (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  sub    (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  mul    (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  div    (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  mod    (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  lshift (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  rshift (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  andeq  (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  oreq   (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  xoreq  (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  min    (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  max    (a,b,sync); }
// { volatile atomic<foo,serial> a(0);  inc    (a,  sync); }
// { volatile atomic<foo,serial> a(0);  preinc (a,  sync); }
// { volatile atomic<foo,serial> a(0);  postinc(a,  sync); }
// { volatile atomic<foo,serial> a(0);  dec    (a,  sync); }
// { volatile atomic<foo,serial> a(0);  predec (a,  sync); }
// { volatile atomic<foo,serial> a(0);  postdec(a,  sync); }
// { volatile atomic<foo,serial> a(0);  add    (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  sub    (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  mul    (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  div    (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  mod    (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  lshift (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  rshift (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  andeq  (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  oreq   (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  xoreq  (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  min    (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  max    (a,b,success,failure); }
// { volatile atomic<foo,serial> a(0);  inc    (a,  success,failure); }
// { volatile atomic<foo,serial> a(0);  preinc (a,  success,failure); }
// { volatile atomic<foo,serial> a(0);  postinc(a,  success,failure); }
// { volatile atomic<foo,serial> a(0);  dec    (a,  success,failure); }
// { volatile atomic<foo,serial> a(0);  predec (a,  success,failure); }
// { volatile atomic<foo,serial> a(0);  postdec(a,  success,failure); }
}
