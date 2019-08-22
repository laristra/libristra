
/*
Member-function versions of the code in all-global-functions.cc.
See comments there.
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

   { atomic<int,cpp> a(0);  a.add    (2); }
   { atomic<int,cpp> a(0);  a.sub    (2); }
// { atomic<int,cpp> a(0);  a.mul    (2); }
// { atomic<int,cpp> a(0);  a.div    (2); }
// { atomic<int,cpp> a(0);  a.mod    (2); }
// { atomic<int,cpp> a(0);  a.lshift (2); }
// { atomic<int,cpp> a(0);  a.rshift (2); }
   { atomic<int,cpp> a(0);  a.andeq  (2); }
   { atomic<int,cpp> a(0);  a.oreq   (2); }
   { atomic<int,cpp> a(0);  a.xoreq  (2); }
// { atomic<int,cpp> a(0);  a.min    (2); }
// { atomic<int,cpp> a(0);  a.max    (2); }
   { atomic<int,cpp> a(0);  a.inc    ( ); }
   { atomic<int,cpp> a(0);  a.preinc ( ); }
   { atomic<int,cpp> a(0);  a.postinc( ); }
   { atomic<int,cpp> a(0);  a.dec    ( ); }
   { atomic<int,cpp> a(0);  a.predec ( ); }
   { atomic<int,cpp> a(0);  a.postdec( ); }
   { atomic<int,cpp> a(0);  a.add    (2,sync); }
   { atomic<int,cpp> a(0);  a.sub    (2,sync); }
// { atomic<int,cpp> a(0);  a.mul    (2,sync); }
// { atomic<int,cpp> a(0);  a.div    (2,sync); }
// { atomic<int,cpp> a(0);  a.mod    (2,sync); }
// { atomic<int,cpp> a(0);  a.lshift (2,sync); }
// { atomic<int,cpp> a(0);  a.rshift (2,sync); }
   { atomic<int,cpp> a(0);  a.andeq  (2,sync); }
   { atomic<int,cpp> a(0);  a.oreq   (2,sync); }
   { atomic<int,cpp> a(0);  a.xoreq  (2,sync); }
// { atomic<int,cpp> a(0);  a.min    (2,sync); }
// { atomic<int,cpp> a(0);  a.max    (2,sync); }
// { atomic<int,cpp> a(0);  a.inc    (  sync); }
// { atomic<int,cpp> a(0);  a.preinc (  sync); }
// { atomic<int,cpp> a(0);  a.postinc(  sync); }
// { atomic<int,cpp> a(0);  a.dec    (  sync); }
// { atomic<int,cpp> a(0);  a.predec (  sync); }
// { atomic<int,cpp> a(0);  a.postdec(  sync); }
// { atomic<int,cpp> a(0);  a.add    (2,success,failure); }
// { atomic<int,cpp> a(0);  a.sub    (2,success,failure); }
// { atomic<int,cpp> a(0);  a.mul    (2,success,failure); }
// { atomic<int,cpp> a(0);  a.div    (2,success,failure); }
// { atomic<int,cpp> a(0);  a.mod    (2,success,failure); }
// { atomic<int,cpp> a(0);  a.lshift (2,success,failure); }
// { atomic<int,cpp> a(0);  a.rshift (2,success,failure); }
// { atomic<int,cpp> a(0);  a.andeq  (2,success,failure); }
// { atomic<int,cpp> a(0);  a.oreq   (2,success,failure); }
// { atomic<int,cpp> a(0);  a.xoreq  (2,success,failure); }
// { atomic<int,cpp> a(0);  a.min    (2,success,failure); }
// { atomic<int,cpp> a(0);  a.max    (2,success,failure); }
// { atomic<int,cpp> a(0);  a.inc    (  success,failure); }
// { atomic<int,cpp> a(0);  a.preinc (  success,failure); }
// { atomic<int,cpp> a(0);  a.postinc(  success,failure); }
// { atomic<int,cpp> a(0);  a.dec    (  success,failure); }
// { atomic<int,cpp> a(0);  a.predec (  success,failure); }
// { atomic<int,cpp> a(0);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { atomic<int,kokkos> a(0);  a.add    (2); }
   { atomic<int,kokkos> a(0);  a.sub    (2); }
   { atomic<int,kokkos> a(0);  a.mul    (2); }
   { atomic<int,kokkos> a(0);  a.div    (2); }
   { atomic<int,kokkos> a(0);  a.mod    (2); }
   { atomic<int,kokkos> a(0);  a.lshift (2); }
   { atomic<int,kokkos> a(0);  a.rshift (2); }
   { atomic<int,kokkos> a(0);  a.andeq  (2); }
   { atomic<int,kokkos> a(0);  a.oreq   (2); }
   { atomic<int,kokkos> a(0);  a.xoreq  (2); }
   { atomic<int,kokkos> a(0);  a.min    (2); }
   { atomic<int,kokkos> a(0);  a.max    (2); }
   { atomic<int,kokkos> a(0);  a.inc    ( ); }
   { atomic<int,kokkos> a(0);  a.preinc ( ); }
   { atomic<int,kokkos> a(0);  a.postinc( ); }
   { atomic<int,kokkos> a(0);  a.dec    ( ); }
   { atomic<int,kokkos> a(0);  a.predec ( ); }
   { atomic<int,kokkos> a(0);  a.postdec( ); }
// { atomic<int,kokkos> a(0);  a.add    (2,sync); }
// { atomic<int,kokkos> a(0);  a.sub    (2,sync); }
// { atomic<int,kokkos> a(0);  a.mul    (2,sync); }
// { atomic<int,kokkos> a(0);  a.div    (2,sync); }
// { atomic<int,kokkos> a(0);  a.mod    (2,sync); }
// { atomic<int,kokkos> a(0);  a.lshift (2,sync); }
// { atomic<int,kokkos> a(0);  a.rshift (2,sync); }
// { atomic<int,kokkos> a(0);  a.andeq  (2,sync); }
// { atomic<int,kokkos> a(0);  a.oreq   (2,sync); }
// { atomic<int,kokkos> a(0);  a.xoreq  (2,sync); }
// { atomic<int,kokkos> a(0);  a.min    (2,sync); }
// { atomic<int,kokkos> a(0);  a.max    (2,sync); }
// { atomic<int,kokkos> a(0);  a.inc    (  sync); }
// { atomic<int,kokkos> a(0);  a.preinc (  sync); }
// { atomic<int,kokkos> a(0);  a.postinc(  sync); }
// { atomic<int,kokkos> a(0);  a.dec    (  sync); }
// { atomic<int,kokkos> a(0);  a.predec (  sync); }
// { atomic<int,kokkos> a(0);  a.postdec(  sync); }
// { atomic<int,kokkos> a(0);  a.add    (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.sub    (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.mul    (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.div    (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.mod    (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.lshift (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.rshift (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.andeq  (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.oreq   (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.xoreq  (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.min    (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.max    (2,success,failure); }
// { atomic<int,kokkos> a(0);  a.inc    (  success,failure); }
// { atomic<int,kokkos> a(0);  a.preinc (  success,failure); }
// { atomic<int,kokkos> a(0);  a.postinc(  success,failure); }
// { atomic<int,kokkos> a(0);  a.dec    (  success,failure); }
// { atomic<int,kokkos> a(0);  a.predec (  success,failure); }
// { atomic<int,kokkos> a(0);  a.postdec(  success,failure); }
#endif

   { atomic<int,strong> a(0);  a.add    (2); }
   { atomic<int,strong> a(0);  a.sub    (2); }
   { atomic<int,strong> a(0);  a.mul    (2); }
   { atomic<int,strong> a(0);  a.div    (2); }
   { atomic<int,strong> a(0);  a.mod    (2); }
   { atomic<int,strong> a(0);  a.lshift (2); }
   { atomic<int,strong> a(0);  a.rshift (2); }
   { atomic<int,strong> a(0);  a.andeq  (2); }
   { atomic<int,strong> a(0);  a.oreq   (2); }
   { atomic<int,strong> a(0);  a.xoreq  (2); }
   { atomic<int,strong> a(0);  a.min    (2); }
   { atomic<int,strong> a(0);  a.max    (2); }
   { atomic<int,strong> a(0);  a.inc    ( ); }
   { atomic<int,strong> a(0);  a.preinc ( ); }
   { atomic<int,strong> a(0);  a.postinc( ); }
   { atomic<int,strong> a(0);  a.dec    ( ); }
   { atomic<int,strong> a(0);  a.predec ( ); }
   { atomic<int,strong> a(0);  a.postdec( ); }
   { atomic<int,strong> a(0);  a.add    (2,sync); }
   { atomic<int,strong> a(0);  a.sub    (2,sync); }
   { atomic<int,strong> a(0);  a.mul    (2,sync); }
   { atomic<int,strong> a(0);  a.div    (2,sync); }
   { atomic<int,strong> a(0);  a.mod    (2,sync); }
   { atomic<int,strong> a(0);  a.lshift (2,sync); }
   { atomic<int,strong> a(0);  a.rshift (2,sync); }
   { atomic<int,strong> a(0);  a.andeq  (2,sync); }
   { atomic<int,strong> a(0);  a.oreq   (2,sync); }
   { atomic<int,strong> a(0);  a.xoreq  (2,sync); }
   { atomic<int,strong> a(0);  a.min    (2,sync); }
   { atomic<int,strong> a(0);  a.max    (2,sync); }
   { atomic<int,strong> a(0);  a.inc    (  sync); }
   { atomic<int,strong> a(0);  a.preinc (  sync); }
   { atomic<int,strong> a(0);  a.postinc(  sync); }
   { atomic<int,strong> a(0);  a.dec    (  sync); }
   { atomic<int,strong> a(0);  a.predec (  sync); }
   { atomic<int,strong> a(0);  a.postdec(  sync); }
   { atomic<int,strong> a(0);  a.add    (2,success,failure); }
   { atomic<int,strong> a(0);  a.sub    (2,success,failure); }
   { atomic<int,strong> a(0);  a.mul    (2,success,failure); }
   { atomic<int,strong> a(0);  a.div    (2,success,failure); }
   { atomic<int,strong> a(0);  a.mod    (2,success,failure); }
   { atomic<int,strong> a(0);  a.lshift (2,success,failure); }
   { atomic<int,strong> a(0);  a.rshift (2,success,failure); }
   { atomic<int,strong> a(0);  a.andeq  (2,success,failure); }
   { atomic<int,strong> a(0);  a.oreq   (2,success,failure); }
   { atomic<int,strong> a(0);  a.xoreq  (2,success,failure); }
   { atomic<int,strong> a(0);  a.min    (2,success,failure); }
   { atomic<int,strong> a(0);  a.max    (2,success,failure); }
   { atomic<int,strong> a(0);  a.inc    (  success,failure); }
   { atomic<int,strong> a(0);  a.preinc (  success,failure); }
   { atomic<int,strong> a(0);  a.postinc(  success,failure); }
   { atomic<int,strong> a(0);  a.dec    (  success,failure); }
   { atomic<int,strong> a(0);  a.predec (  success,failure); }
   { atomic<int,strong> a(0);  a.postdec(  success,failure); }

   { atomic<int,strong::pun> a(0);  a.add    (2); }
   { atomic<int,strong::pun> a(0);  a.sub    (2); }
   { atomic<int,strong::pun> a(0);  a.mul    (2); }
   { atomic<int,strong::pun> a(0);  a.div    (2); }
   { atomic<int,strong::pun> a(0);  a.mod    (2); }
   { atomic<int,strong::pun> a(0);  a.lshift (2); }
   { atomic<int,strong::pun> a(0);  a.rshift (2); }
   { atomic<int,strong::pun> a(0);  a.andeq  (2); }
   { atomic<int,strong::pun> a(0);  a.oreq   (2); }
   { atomic<int,strong::pun> a(0);  a.xoreq  (2); }
   { atomic<int,strong::pun> a(0);  a.min    (2); }
   { atomic<int,strong::pun> a(0);  a.max    (2); }
   { atomic<int,strong::pun> a(0);  a.inc    ( ); }
   { atomic<int,strong::pun> a(0);  a.preinc ( ); }
   { atomic<int,strong::pun> a(0);  a.postinc( ); }
   { atomic<int,strong::pun> a(0);  a.dec    ( ); }
   { atomic<int,strong::pun> a(0);  a.predec ( ); }
   { atomic<int,strong::pun> a(0);  a.postdec( ); }
   { atomic<int,strong::pun> a(0);  a.add    (2,sync); }
   { atomic<int,strong::pun> a(0);  a.sub    (2,sync); }
   { atomic<int,strong::pun> a(0);  a.mul    (2,sync); }
   { atomic<int,strong::pun> a(0);  a.div    (2,sync); }
   { atomic<int,strong::pun> a(0);  a.mod    (2,sync); }
   { atomic<int,strong::pun> a(0);  a.lshift (2,sync); }
   { atomic<int,strong::pun> a(0);  a.rshift (2,sync); }
   { atomic<int,strong::pun> a(0);  a.andeq  (2,sync); }
   { atomic<int,strong::pun> a(0);  a.oreq   (2,sync); }
   { atomic<int,strong::pun> a(0);  a.xoreq  (2,sync); }
   { atomic<int,strong::pun> a(0);  a.min    (2,sync); }
   { atomic<int,strong::pun> a(0);  a.max    (2,sync); }
   { atomic<int,strong::pun> a(0);  a.inc    (  sync); }
   { atomic<int,strong::pun> a(0);  a.preinc (  sync); }
   { atomic<int,strong::pun> a(0);  a.postinc(  sync); }
   { atomic<int,strong::pun> a(0);  a.dec    (  sync); }
   { atomic<int,strong::pun> a(0);  a.predec (  sync); }
   { atomic<int,strong::pun> a(0);  a.postdec(  sync); }
   { atomic<int,strong::pun> a(0);  a.add    (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.sub    (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.mul    (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.div    (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.mod    (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.lshift (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.rshift (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.andeq  (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.oreq   (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.xoreq  (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.min    (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.max    (2,success,failure); }
   { atomic<int,strong::pun> a(0);  a.inc    (  success,failure); }
   { atomic<int,strong::pun> a(0);  a.preinc (  success,failure); }
   { atomic<int,strong::pun> a(0);  a.postinc(  success,failure); }
   { atomic<int,strong::pun> a(0);  a.dec    (  success,failure); }
   { atomic<int,strong::pun> a(0);  a.predec (  success,failure); }
   { atomic<int,strong::pun> a(0);  a.postdec(  success,failure); }

   { atomic<int,weak> a(0);  a.add    (2); }
   { atomic<int,weak> a(0);  a.sub    (2); }
   { atomic<int,weak> a(0);  a.mul    (2); }
   { atomic<int,weak> a(0);  a.div    (2); }
   { atomic<int,weak> a(0);  a.mod    (2); }
   { atomic<int,weak> a(0);  a.lshift (2); }
   { atomic<int,weak> a(0);  a.rshift (2); }
   { atomic<int,weak> a(0);  a.andeq  (2); }
   { atomic<int,weak> a(0);  a.oreq   (2); }
   { atomic<int,weak> a(0);  a.xoreq  (2); }
   { atomic<int,weak> a(0);  a.min    (2); }
   { atomic<int,weak> a(0);  a.max    (2); }
   { atomic<int,weak> a(0);  a.inc    ( ); }
   { atomic<int,weak> a(0);  a.preinc ( ); }
   { atomic<int,weak> a(0);  a.postinc( ); }
   { atomic<int,weak> a(0);  a.dec    ( ); }
   { atomic<int,weak> a(0);  a.predec ( ); }
   { atomic<int,weak> a(0);  a.postdec( ); }
   { atomic<int,weak> a(0);  a.add    (2,sync); }
   { atomic<int,weak> a(0);  a.sub    (2,sync); }
   { atomic<int,weak> a(0);  a.mul    (2,sync); }
   { atomic<int,weak> a(0);  a.div    (2,sync); }
   { atomic<int,weak> a(0);  a.mod    (2,sync); }
   { atomic<int,weak> a(0);  a.lshift (2,sync); }
   { atomic<int,weak> a(0);  a.rshift (2,sync); }
   { atomic<int,weak> a(0);  a.andeq  (2,sync); }
   { atomic<int,weak> a(0);  a.oreq   (2,sync); }
   { atomic<int,weak> a(0);  a.xoreq  (2,sync); }
   { atomic<int,weak> a(0);  a.min    (2,sync); }
   { atomic<int,weak> a(0);  a.max    (2,sync); }
   { atomic<int,weak> a(0);  a.inc    (  sync); }
   { atomic<int,weak> a(0);  a.preinc (  sync); }
   { atomic<int,weak> a(0);  a.postinc(  sync); }
   { atomic<int,weak> a(0);  a.dec    (  sync); }
   { atomic<int,weak> a(0);  a.predec (  sync); }
   { atomic<int,weak> a(0);  a.postdec(  sync); }
   { atomic<int,weak> a(0);  a.add    (2,success,failure); }
   { atomic<int,weak> a(0);  a.sub    (2,success,failure); }
   { atomic<int,weak> a(0);  a.mul    (2,success,failure); }
   { atomic<int,weak> a(0);  a.div    (2,success,failure); }
   { atomic<int,weak> a(0);  a.mod    (2,success,failure); }
   { atomic<int,weak> a(0);  a.lshift (2,success,failure); }
   { atomic<int,weak> a(0);  a.rshift (2,success,failure); }
   { atomic<int,weak> a(0);  a.andeq  (2,success,failure); }
   { atomic<int,weak> a(0);  a.oreq   (2,success,failure); }
   { atomic<int,weak> a(0);  a.xoreq  (2,success,failure); }
   { atomic<int,weak> a(0);  a.min    (2,success,failure); }
   { atomic<int,weak> a(0);  a.max    (2,success,failure); }
   { atomic<int,weak> a(0);  a.inc    (  success,failure); }
   { atomic<int,weak> a(0);  a.preinc (  success,failure); }
   { atomic<int,weak> a(0);  a.postinc(  success,failure); }
   { atomic<int,weak> a(0);  a.dec    (  success,failure); }
   { atomic<int,weak> a(0);  a.predec (  success,failure); }
   { atomic<int,weak> a(0);  a.postdec(  success,failure); }

   { atomic<int,weak::pun> a(0);  a.add    (2); }
   { atomic<int,weak::pun> a(0);  a.sub    (2); }
   { atomic<int,weak::pun> a(0);  a.mul    (2); }
   { atomic<int,weak::pun> a(0);  a.div    (2); }
   { atomic<int,weak::pun> a(0);  a.mod    (2); }
   { atomic<int,weak::pun> a(0);  a.lshift (2); }
   { atomic<int,weak::pun> a(0);  a.rshift (2); }
   { atomic<int,weak::pun> a(0);  a.andeq  (2); }
   { atomic<int,weak::pun> a(0);  a.oreq   (2); }
   { atomic<int,weak::pun> a(0);  a.xoreq  (2); }
   { atomic<int,weak::pun> a(0);  a.min    (2); }
   { atomic<int,weak::pun> a(0);  a.max    (2); }
   { atomic<int,weak::pun> a(0);  a.inc    ( ); }
   { atomic<int,weak::pun> a(0);  a.preinc ( ); }
   { atomic<int,weak::pun> a(0);  a.postinc( ); }
   { atomic<int,weak::pun> a(0);  a.dec    ( ); }
   { atomic<int,weak::pun> a(0);  a.predec ( ); }
   { atomic<int,weak::pun> a(0);  a.postdec( ); }
   { atomic<int,weak::pun> a(0);  a.add    (2,sync); }
   { atomic<int,weak::pun> a(0);  a.sub    (2,sync); }
   { atomic<int,weak::pun> a(0);  a.mul    (2,sync); }
   { atomic<int,weak::pun> a(0);  a.div    (2,sync); }
   { atomic<int,weak::pun> a(0);  a.mod    (2,sync); }
   { atomic<int,weak::pun> a(0);  a.lshift (2,sync); }
   { atomic<int,weak::pun> a(0);  a.rshift (2,sync); }
   { atomic<int,weak::pun> a(0);  a.andeq  (2,sync); }
   { atomic<int,weak::pun> a(0);  a.oreq   (2,sync); }
   { atomic<int,weak::pun> a(0);  a.xoreq  (2,sync); }
   { atomic<int,weak::pun> a(0);  a.min    (2,sync); }
   { atomic<int,weak::pun> a(0);  a.max    (2,sync); }
   { atomic<int,weak::pun> a(0);  a.inc    (  sync); }
   { atomic<int,weak::pun> a(0);  a.preinc (  sync); }
   { atomic<int,weak::pun> a(0);  a.postinc(  sync); }
   { atomic<int,weak::pun> a(0);  a.dec    (  sync); }
   { atomic<int,weak::pun> a(0);  a.predec (  sync); }
   { atomic<int,weak::pun> a(0);  a.postdec(  sync); }
   { atomic<int,weak::pun> a(0);  a.add    (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.sub    (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.mul    (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.div    (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.mod    (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.lshift (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.rshift (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.andeq  (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.oreq   (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.xoreq  (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.min    (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.max    (2,success,failure); }
   { atomic<int,weak::pun> a(0);  a.inc    (  success,failure); }
   { atomic<int,weak::pun> a(0);  a.preinc (  success,failure); }
   { atomic<int,weak::pun> a(0);  a.postinc(  success,failure); }
   { atomic<int,weak::pun> a(0);  a.dec    (  success,failure); }
   { atomic<int,weak::pun> a(0);  a.predec (  success,failure); }
   { atomic<int,weak::pun> a(0);  a.postdec(  success,failure); }

   { atomic<int,lock> a(0);  a.add    (2); }
   { atomic<int,lock> a(0);  a.sub    (2); }
   { atomic<int,lock> a(0);  a.mul    (2); }
   { atomic<int,lock> a(0);  a.div    (2); }
   { atomic<int,lock> a(0);  a.mod    (2); }
   { atomic<int,lock> a(0);  a.lshift (2); }
   { atomic<int,lock> a(0);  a.rshift (2); }
   { atomic<int,lock> a(0);  a.andeq  (2); }
   { atomic<int,lock> a(0);  a.oreq   (2); }
   { atomic<int,lock> a(0);  a.xoreq  (2); }
   { atomic<int,lock> a(0);  a.min    (2); }
   { atomic<int,lock> a(0);  a.max    (2); }
   { atomic<int,lock> a(0);  a.inc    ( ); }
   { atomic<int,lock> a(0);  a.preinc ( ); }
   { atomic<int,lock> a(0);  a.postinc( ); }
   { atomic<int,lock> a(0);  a.dec    ( ); }
   { atomic<int,lock> a(0);  a.predec ( ); }
   { atomic<int,lock> a(0);  a.postdec( ); }
// { atomic<int,lock> a(0);  a.add    (2,sync); }
// { atomic<int,lock> a(0);  a.sub    (2,sync); }
// { atomic<int,lock> a(0);  a.mul    (2,sync); }
// { atomic<int,lock> a(0);  a.div    (2,sync); }
// { atomic<int,lock> a(0);  a.mod    (2,sync); }
// { atomic<int,lock> a(0);  a.lshift (2,sync); }
// { atomic<int,lock> a(0);  a.rshift (2,sync); }
// { atomic<int,lock> a(0);  a.andeq  (2,sync); }
// { atomic<int,lock> a(0);  a.oreq   (2,sync); }
// { atomic<int,lock> a(0);  a.xoreq  (2,sync); }
// { atomic<int,lock> a(0);  a.min    (2,sync); }
// { atomic<int,lock> a(0);  a.max    (2,sync); }
// { atomic<int,lock> a(0);  a.inc    (  sync); }
// { atomic<int,lock> a(0);  a.preinc (  sync); }
// { atomic<int,lock> a(0);  a.postinc(  sync); }
// { atomic<int,lock> a(0);  a.dec    (  sync); }
// { atomic<int,lock> a(0);  a.predec (  sync); }
// { atomic<int,lock> a(0);  a.postdec(  sync); }
// { atomic<int,lock> a(0);  a.add    (2,success,failure); }
// { atomic<int,lock> a(0);  a.sub    (2,success,failure); }
// { atomic<int,lock> a(0);  a.mul    (2,success,failure); }
// { atomic<int,lock> a(0);  a.div    (2,success,failure); }
// { atomic<int,lock> a(0);  a.mod    (2,success,failure); }
// { atomic<int,lock> a(0);  a.lshift (2,success,failure); }
// { atomic<int,lock> a(0);  a.rshift (2,success,failure); }
// { atomic<int,lock> a(0);  a.andeq  (2,success,failure); }
// { atomic<int,lock> a(0);  a.oreq   (2,success,failure); }
// { atomic<int,lock> a(0);  a.xoreq  (2,success,failure); }
// { atomic<int,lock> a(0);  a.min    (2,success,failure); }
// { atomic<int,lock> a(0);  a.max    (2,success,failure); }
// { atomic<int,lock> a(0);  a.inc    (  success,failure); }
// { atomic<int,lock> a(0);  a.preinc (  success,failure); }
// { atomic<int,lock> a(0);  a.postinc(  success,failure); }
// { atomic<int,lock> a(0);  a.dec    (  success,failure); }
// { atomic<int,lock> a(0);  a.predec (  success,failure); }
// { atomic<int,lock> a(0);  a.postdec(  success,failure); }

   { atomic<int,serial> a(0);  a.add    (2); }
   { atomic<int,serial> a(0);  a.sub    (2); }
   { atomic<int,serial> a(0);  a.mul    (2); }
   { atomic<int,serial> a(0);  a.div    (2); }
   { atomic<int,serial> a(0);  a.mod    (2); }
   { atomic<int,serial> a(0);  a.lshift (2); }
   { atomic<int,serial> a(0);  a.rshift (2); }
   { atomic<int,serial> a(0);  a.andeq  (2); }
   { atomic<int,serial> a(0);  a.oreq   (2); }
   { atomic<int,serial> a(0);  a.xoreq  (2); }
   { atomic<int,serial> a(0);  a.min    (2); }
   { atomic<int,serial> a(0);  a.max    (2); }
   { atomic<int,serial> a(0);  a.inc    ( ); }
   { atomic<int,serial> a(0);  a.preinc ( ); }
   { atomic<int,serial> a(0);  a.postinc( ); }
   { atomic<int,serial> a(0);  a.dec    ( ); }
   { atomic<int,serial> a(0);  a.predec ( ); }
   { atomic<int,serial> a(0);  a.postdec( ); }
// { atomic<int,serial> a(0);  a.add    (2,sync); }
// { atomic<int,serial> a(0);  a.sub    (2,sync); }
// { atomic<int,serial> a(0);  a.mul    (2,sync); }
// { atomic<int,serial> a(0);  a.div    (2,sync); }
// { atomic<int,serial> a(0);  a.mod    (2,sync); }
// { atomic<int,serial> a(0);  a.lshift (2,sync); }
// { atomic<int,serial> a(0);  a.rshift (2,sync); }
// { atomic<int,serial> a(0);  a.andeq  (2,sync); }
// { atomic<int,serial> a(0);  a.oreq   (2,sync); }
// { atomic<int,serial> a(0);  a.xoreq  (2,sync); }
// { atomic<int,serial> a(0);  a.min    (2,sync); }
// { atomic<int,serial> a(0);  a.max    (2,sync); }
// { atomic<int,serial> a(0);  a.inc    (  sync); }
// { atomic<int,serial> a(0);  a.preinc (  sync); }
// { atomic<int,serial> a(0);  a.postinc(  sync); }
// { atomic<int,serial> a(0);  a.dec    (  sync); }
// { atomic<int,serial> a(0);  a.predec (  sync); }
// { atomic<int,serial> a(0);  a.postdec(  sync); }
// { atomic<int,serial> a(0);  a.add    (2,success,failure); }
// { atomic<int,serial> a(0);  a.sub    (2,success,failure); }
// { atomic<int,serial> a(0);  a.mul    (2,success,failure); }
// { atomic<int,serial> a(0);  a.div    (2,success,failure); }
// { atomic<int,serial> a(0);  a.mod    (2,success,failure); }
// { atomic<int,serial> a(0);  a.lshift (2,success,failure); }
// { atomic<int,serial> a(0);  a.rshift (2,success,failure); }
// { atomic<int,serial> a(0);  a.andeq  (2,success,failure); }
// { atomic<int,serial> a(0);  a.oreq   (2,success,failure); }
// { atomic<int,serial> a(0);  a.xoreq  (2,success,failure); }
// { atomic<int,serial> a(0);  a.min    (2,success,failure); }
// { atomic<int,serial> a(0);  a.max    (2,success,failure); }
// { atomic<int,serial> a(0);  a.inc    (  success,failure); }
// { atomic<int,serial> a(0);  a.preinc (  success,failure); }
// { atomic<int,serial> a(0);  a.postinc(  success,failure); }
// { atomic<int,serial> a(0);  a.dec    (  success,failure); }
// { atomic<int,serial> a(0);  a.predec (  success,failure); }
// { atomic<int,serial> a(0);  a.postdec(  success,failure); }



   // ------------------------
   // ulong
   // ------------------------

   { atomic<ulong,cpp> a(0);  a.add    (2); }
   { atomic<ulong,cpp> a(0);  a.sub    (2); }
// { atomic<ulong,cpp> a(0);  a.mul    (2); }
// { atomic<ulong,cpp> a(0);  a.div    (2); }
// { atomic<ulong,cpp> a(0);  a.mod    (2); }
// { atomic<ulong,cpp> a(0);  a.lshift (2); }
// { atomic<ulong,cpp> a(0);  a.rshift (2); }
   { atomic<ulong,cpp> a(0);  a.andeq  (2); }
   { atomic<ulong,cpp> a(0);  a.oreq   (2); }
   { atomic<ulong,cpp> a(0);  a.xoreq  (2); }
// { atomic<ulong,cpp> a(0);  a.min    (2); }
// { atomic<ulong,cpp> a(0);  a.max    (2); }
   { atomic<ulong,cpp> a(0);  a.inc    ( ); }
   { atomic<ulong,cpp> a(0);  a.preinc ( ); }
   { atomic<ulong,cpp> a(0);  a.postinc( ); }
   { atomic<ulong,cpp> a(0);  a.dec    ( ); }
   { atomic<ulong,cpp> a(0);  a.predec ( ); }
   { atomic<ulong,cpp> a(0);  a.postdec( ); }
   { atomic<ulong,cpp> a(0);  a.add    (2,sync); }
   { atomic<ulong,cpp> a(0);  a.sub    (2,sync); }
// { atomic<ulong,cpp> a(0);  a.mul    (2,sync); }
// { atomic<ulong,cpp> a(0);  a.div    (2,sync); }
// { atomic<ulong,cpp> a(0);  a.mod    (2,sync); }
// { atomic<ulong,cpp> a(0);  a.lshift (2,sync); }
// { atomic<ulong,cpp> a(0);  a.rshift (2,sync); }
   { atomic<ulong,cpp> a(0);  a.andeq  (2,sync); }
   { atomic<ulong,cpp> a(0);  a.oreq   (2,sync); }
   { atomic<ulong,cpp> a(0);  a.xoreq  (2,sync); }
// { atomic<ulong,cpp> a(0);  a.min    (2,sync); }
// { atomic<ulong,cpp> a(0);  a.max    (2,sync); }
// { atomic<ulong,cpp> a(0);  a.inc    (  sync); }
// { atomic<ulong,cpp> a(0);  a.preinc (  sync); }
// { atomic<ulong,cpp> a(0);  a.postinc(  sync); }
// { atomic<ulong,cpp> a(0);  a.dec    (  sync); }
// { atomic<ulong,cpp> a(0);  a.predec (  sync); }
// { atomic<ulong,cpp> a(0);  a.postdec(  sync); }
// { atomic<ulong,cpp> a(0);  a.add    (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.sub    (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.mul    (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.div    (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.mod    (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.lshift (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.rshift (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.andeq  (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.oreq   (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.xoreq  (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.min    (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.max    (2,success,failure); }
// { atomic<ulong,cpp> a(0);  a.inc    (  success,failure); }
// { atomic<ulong,cpp> a(0);  a.preinc (  success,failure); }
// { atomic<ulong,cpp> a(0);  a.postinc(  success,failure); }
// { atomic<ulong,cpp> a(0);  a.dec    (  success,failure); }
// { atomic<ulong,cpp> a(0);  a.predec (  success,failure); }
// { atomic<ulong,cpp> a(0);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { atomic<ulong,kokkos> a(0);  a.add    (2); }
   { atomic<ulong,kokkos> a(0);  a.sub    (2); }
   { atomic<ulong,kokkos> a(0);  a.mul    (2); }
   { atomic<ulong,kokkos> a(0);  a.div    (2); }
   { atomic<ulong,kokkos> a(0);  a.mod    (2); }
   { atomic<ulong,kokkos> a(0);  a.lshift (2); }
   { atomic<ulong,kokkos> a(0);  a.rshift (2); }
   { atomic<ulong,kokkos> a(0);  a.andeq  (2); }
   { atomic<ulong,kokkos> a(0);  a.oreq   (2); }
   { atomic<ulong,kokkos> a(0);  a.xoreq  (2); }
   { atomic<ulong,kokkos> a(0);  a.min    (2); }
   { atomic<ulong,kokkos> a(0);  a.max    (2); }
   { atomic<ulong,kokkos> a(0);  a.inc    ( ); }
   { atomic<ulong,kokkos> a(0);  a.preinc ( ); }
   { atomic<ulong,kokkos> a(0);  a.postinc( ); }
   { atomic<ulong,kokkos> a(0);  a.dec    ( ); }
   { atomic<ulong,kokkos> a(0);  a.predec ( ); }
   { atomic<ulong,kokkos> a(0);  a.postdec( ); }
// { atomic<ulong,kokkos> a(0);  a.add    (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.sub    (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.mul    (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.div    (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.mod    (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.lshift (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.rshift (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.andeq  (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.oreq   (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.xoreq  (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.min    (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.max    (2,sync); }
// { atomic<ulong,kokkos> a(0);  a.inc    (  sync); }
// { atomic<ulong,kokkos> a(0);  a.preinc (  sync); }
// { atomic<ulong,kokkos> a(0);  a.postinc(  sync); }
// { atomic<ulong,kokkos> a(0);  a.dec    (  sync); }
// { atomic<ulong,kokkos> a(0);  a.predec (  sync); }
// { atomic<ulong,kokkos> a(0);  a.postdec(  sync); }
// { atomic<ulong,kokkos> a(0);  a.add    (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.sub    (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.mul    (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.div    (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.mod    (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.lshift (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.rshift (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.andeq  (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.oreq   (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.xoreq  (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.min    (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.max    (2,success,failure); }
// { atomic<ulong,kokkos> a(0);  a.inc    (  success,failure); }
// { atomic<ulong,kokkos> a(0);  a.preinc (  success,failure); }
// { atomic<ulong,kokkos> a(0);  a.postinc(  success,failure); }
// { atomic<ulong,kokkos> a(0);  a.dec    (  success,failure); }
// { atomic<ulong,kokkos> a(0);  a.predec (  success,failure); }
// { atomic<ulong,kokkos> a(0);  a.postdec(  success,failure); }
#endif

   { atomic<ulong,strong> a(0);  a.add    (2); }
   { atomic<ulong,strong> a(0);  a.sub    (2); }
   { atomic<ulong,strong> a(0);  a.mul    (2); }
   { atomic<ulong,strong> a(0);  a.div    (2); }
   { atomic<ulong,strong> a(0);  a.mod    (2); }
   { atomic<ulong,strong> a(0);  a.lshift (2); }
   { atomic<ulong,strong> a(0);  a.rshift (2); }
   { atomic<ulong,strong> a(0);  a.andeq  (2); }
   { atomic<ulong,strong> a(0);  a.oreq   (2); }
   { atomic<ulong,strong> a(0);  a.xoreq  (2); }
   { atomic<ulong,strong> a(0);  a.min    (2); }
   { atomic<ulong,strong> a(0);  a.max    (2); }
   { atomic<ulong,strong> a(0);  a.inc    ( ); }
   { atomic<ulong,strong> a(0);  a.preinc ( ); }
   { atomic<ulong,strong> a(0);  a.postinc( ); }
   { atomic<ulong,strong> a(0);  a.dec    ( ); }
   { atomic<ulong,strong> a(0);  a.predec ( ); }
   { atomic<ulong,strong> a(0);  a.postdec( ); }
   { atomic<ulong,strong> a(0);  a.add    (2,sync); }
   { atomic<ulong,strong> a(0);  a.sub    (2,sync); }
   { atomic<ulong,strong> a(0);  a.mul    (2,sync); }
   { atomic<ulong,strong> a(0);  a.div    (2,sync); }
   { atomic<ulong,strong> a(0);  a.mod    (2,sync); }
   { atomic<ulong,strong> a(0);  a.lshift (2,sync); }
   { atomic<ulong,strong> a(0);  a.rshift (2,sync); }
   { atomic<ulong,strong> a(0);  a.andeq  (2,sync); }
   { atomic<ulong,strong> a(0);  a.oreq   (2,sync); }
   { atomic<ulong,strong> a(0);  a.xoreq  (2,sync); }
   { atomic<ulong,strong> a(0);  a.min    (2,sync); }
   { atomic<ulong,strong> a(0);  a.max    (2,sync); }
   { atomic<ulong,strong> a(0);  a.inc    (  sync); }
   { atomic<ulong,strong> a(0);  a.preinc (  sync); }
   { atomic<ulong,strong> a(0);  a.postinc(  sync); }
   { atomic<ulong,strong> a(0);  a.dec    (  sync); }
   { atomic<ulong,strong> a(0);  a.predec (  sync); }
   { atomic<ulong,strong> a(0);  a.postdec(  sync); }
   { atomic<ulong,strong> a(0);  a.add    (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.sub    (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.mul    (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.div    (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.mod    (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.lshift (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.rshift (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.andeq  (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.oreq   (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.xoreq  (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.min    (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.max    (2,success,failure); }
   { atomic<ulong,strong> a(0);  a.inc    (  success,failure); }
   { atomic<ulong,strong> a(0);  a.preinc (  success,failure); }
   { atomic<ulong,strong> a(0);  a.postinc(  success,failure); }
   { atomic<ulong,strong> a(0);  a.dec    (  success,failure); }
   { atomic<ulong,strong> a(0);  a.predec (  success,failure); }
   { atomic<ulong,strong> a(0);  a.postdec(  success,failure); }

   { atomic<ulong,strong::pun> a(0);  a.add    (2); }
   { atomic<ulong,strong::pun> a(0);  a.sub    (2); }
   { atomic<ulong,strong::pun> a(0);  a.mul    (2); }
   { atomic<ulong,strong::pun> a(0);  a.div    (2); }
   { atomic<ulong,strong::pun> a(0);  a.mod    (2); }
   { atomic<ulong,strong::pun> a(0);  a.lshift (2); }
   { atomic<ulong,strong::pun> a(0);  a.rshift (2); }
   { atomic<ulong,strong::pun> a(0);  a.andeq  (2); }
   { atomic<ulong,strong::pun> a(0);  a.oreq   (2); }
   { atomic<ulong,strong::pun> a(0);  a.xoreq  (2); }
   { atomic<ulong,strong::pun> a(0);  a.min    (2); }
   { atomic<ulong,strong::pun> a(0);  a.max    (2); }
   { atomic<ulong,strong::pun> a(0);  a.inc    ( ); }
   { atomic<ulong,strong::pun> a(0);  a.preinc ( ); }
   { atomic<ulong,strong::pun> a(0);  a.postinc( ); }
   { atomic<ulong,strong::pun> a(0);  a.dec    ( ); }
   { atomic<ulong,strong::pun> a(0);  a.predec ( ); }
   { atomic<ulong,strong::pun> a(0);  a.postdec( ); }
   { atomic<ulong,strong::pun> a(0);  a.add    (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.sub    (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.mul    (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.div    (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.mod    (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.lshift (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.rshift (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.andeq  (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.oreq   (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.xoreq  (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.min    (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.max    (2,sync); }
   { atomic<ulong,strong::pun> a(0);  a.inc    (  sync); }
   { atomic<ulong,strong::pun> a(0);  a.preinc (  sync); }
   { atomic<ulong,strong::pun> a(0);  a.postinc(  sync); }
   { atomic<ulong,strong::pun> a(0);  a.dec    (  sync); }
   { atomic<ulong,strong::pun> a(0);  a.predec (  sync); }
   { atomic<ulong,strong::pun> a(0);  a.postdec(  sync); }
   { atomic<ulong,strong::pun> a(0);  a.add    (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.sub    (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.mul    (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.div    (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.mod    (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.lshift (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.rshift (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.andeq  (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.oreq   (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.xoreq  (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.min    (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.max    (2,success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.inc    (  success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.preinc (  success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.postinc(  success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.dec    (  success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.predec (  success,failure); }
   { atomic<ulong,strong::pun> a(0);  a.postdec(  success,failure); }

   { atomic<ulong,weak> a(0);  a.add    (2); }
   { atomic<ulong,weak> a(0);  a.sub    (2); }
   { atomic<ulong,weak> a(0);  a.mul    (2); }
   { atomic<ulong,weak> a(0);  a.div    (2); }
   { atomic<ulong,weak> a(0);  a.mod    (2); }
   { atomic<ulong,weak> a(0);  a.lshift (2); }
   { atomic<ulong,weak> a(0);  a.rshift (2); }
   { atomic<ulong,weak> a(0);  a.andeq  (2); }
   { atomic<ulong,weak> a(0);  a.oreq   (2); }
   { atomic<ulong,weak> a(0);  a.xoreq  (2); }
   { atomic<ulong,weak> a(0);  a.min    (2); }
   { atomic<ulong,weak> a(0);  a.max    (2); }
   { atomic<ulong,weak> a(0);  a.inc    ( ); }
   { atomic<ulong,weak> a(0);  a.preinc ( ); }
   { atomic<ulong,weak> a(0);  a.postinc( ); }
   { atomic<ulong,weak> a(0);  a.dec    ( ); }
   { atomic<ulong,weak> a(0);  a.predec ( ); }
   { atomic<ulong,weak> a(0);  a.postdec( ); }
   { atomic<ulong,weak> a(0);  a.add    (2,sync); }
   { atomic<ulong,weak> a(0);  a.sub    (2,sync); }
   { atomic<ulong,weak> a(0);  a.mul    (2,sync); }
   { atomic<ulong,weak> a(0);  a.div    (2,sync); }
   { atomic<ulong,weak> a(0);  a.mod    (2,sync); }
   { atomic<ulong,weak> a(0);  a.lshift (2,sync); }
   { atomic<ulong,weak> a(0);  a.rshift (2,sync); }
   { atomic<ulong,weak> a(0);  a.andeq  (2,sync); }
   { atomic<ulong,weak> a(0);  a.oreq   (2,sync); }
   { atomic<ulong,weak> a(0);  a.xoreq  (2,sync); }
   { atomic<ulong,weak> a(0);  a.min    (2,sync); }
   { atomic<ulong,weak> a(0);  a.max    (2,sync); }
   { atomic<ulong,weak> a(0);  a.inc    (  sync); }
   { atomic<ulong,weak> a(0);  a.preinc (  sync); }
   { atomic<ulong,weak> a(0);  a.postinc(  sync); }
   { atomic<ulong,weak> a(0);  a.dec    (  sync); }
   { atomic<ulong,weak> a(0);  a.predec (  sync); }
   { atomic<ulong,weak> a(0);  a.postdec(  sync); }
   { atomic<ulong,weak> a(0);  a.add    (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.sub    (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.mul    (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.div    (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.mod    (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.lshift (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.rshift (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.andeq  (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.oreq   (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.xoreq  (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.min    (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.max    (2,success,failure); }
   { atomic<ulong,weak> a(0);  a.inc    (  success,failure); }
   { atomic<ulong,weak> a(0);  a.preinc (  success,failure); }
   { atomic<ulong,weak> a(0);  a.postinc(  success,failure); }
   { atomic<ulong,weak> a(0);  a.dec    (  success,failure); }
   { atomic<ulong,weak> a(0);  a.predec (  success,failure); }
   { atomic<ulong,weak> a(0);  a.postdec(  success,failure); }

   { atomic<ulong,weak::pun> a(0);  a.add    (2); }
   { atomic<ulong,weak::pun> a(0);  a.sub    (2); }
   { atomic<ulong,weak::pun> a(0);  a.mul    (2); }
   { atomic<ulong,weak::pun> a(0);  a.div    (2); }
   { atomic<ulong,weak::pun> a(0);  a.mod    (2); }
   { atomic<ulong,weak::pun> a(0);  a.lshift (2); }
   { atomic<ulong,weak::pun> a(0);  a.rshift (2); }
   { atomic<ulong,weak::pun> a(0);  a.andeq  (2); }
   { atomic<ulong,weak::pun> a(0);  a.oreq   (2); }
   { atomic<ulong,weak::pun> a(0);  a.xoreq  (2); }
   { atomic<ulong,weak::pun> a(0);  a.min    (2); }
   { atomic<ulong,weak::pun> a(0);  a.max    (2); }
   { atomic<ulong,weak::pun> a(0);  a.inc    ( ); }
   { atomic<ulong,weak::pun> a(0);  a.preinc ( ); }
   { atomic<ulong,weak::pun> a(0);  a.postinc( ); }
   { atomic<ulong,weak::pun> a(0);  a.dec    ( ); }
   { atomic<ulong,weak::pun> a(0);  a.predec ( ); }
   { atomic<ulong,weak::pun> a(0);  a.postdec( ); }
   { atomic<ulong,weak::pun> a(0);  a.add    (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.sub    (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.mul    (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.div    (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.mod    (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.lshift (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.rshift (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.andeq  (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.oreq   (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.xoreq  (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.min    (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.max    (2,sync); }
   { atomic<ulong,weak::pun> a(0);  a.inc    (  sync); }
   { atomic<ulong,weak::pun> a(0);  a.preinc (  sync); }
   { atomic<ulong,weak::pun> a(0);  a.postinc(  sync); }
   { atomic<ulong,weak::pun> a(0);  a.dec    (  sync); }
   { atomic<ulong,weak::pun> a(0);  a.predec (  sync); }
   { atomic<ulong,weak::pun> a(0);  a.postdec(  sync); }
   { atomic<ulong,weak::pun> a(0);  a.add    (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.sub    (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.mul    (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.div    (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.mod    (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.lshift (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.rshift (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.andeq  (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.oreq   (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.xoreq  (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.min    (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.max    (2,success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.inc    (  success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.preinc (  success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.postinc(  success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.dec    (  success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.predec (  success,failure); }
   { atomic<ulong,weak::pun> a(0);  a.postdec(  success,failure); }

   { atomic<ulong,lock> a(0);  a.add    (2); }
   { atomic<ulong,lock> a(0);  a.sub    (2); }
   { atomic<ulong,lock> a(0);  a.mul    (2); }
   { atomic<ulong,lock> a(0);  a.div    (2); }
   { atomic<ulong,lock> a(0);  a.mod    (2); }
   { atomic<ulong,lock> a(0);  a.lshift (2); }
   { atomic<ulong,lock> a(0);  a.rshift (2); }
   { atomic<ulong,lock> a(0);  a.andeq  (2); }
   { atomic<ulong,lock> a(0);  a.oreq   (2); }
   { atomic<ulong,lock> a(0);  a.xoreq  (2); }
   { atomic<ulong,lock> a(0);  a.min    (2); }
   { atomic<ulong,lock> a(0);  a.max    (2); }
   { atomic<ulong,lock> a(0);  a.inc    ( ); }
   { atomic<ulong,lock> a(0);  a.preinc ( ); }
   { atomic<ulong,lock> a(0);  a.postinc( ); }
   { atomic<ulong,lock> a(0);  a.dec    ( ); }
   { atomic<ulong,lock> a(0);  a.predec ( ); }
   { atomic<ulong,lock> a(0);  a.postdec( ); }
// { atomic<ulong,lock> a(0);  a.add    (2,sync); }
// { atomic<ulong,lock> a(0);  a.sub    (2,sync); }
// { atomic<ulong,lock> a(0);  a.mul    (2,sync); }
// { atomic<ulong,lock> a(0);  a.div    (2,sync); }
// { atomic<ulong,lock> a(0);  a.mod    (2,sync); }
// { atomic<ulong,lock> a(0);  a.lshift (2,sync); }
// { atomic<ulong,lock> a(0);  a.rshift (2,sync); }
// { atomic<ulong,lock> a(0);  a.andeq  (2,sync); }
// { atomic<ulong,lock> a(0);  a.oreq   (2,sync); }
// { atomic<ulong,lock> a(0);  a.xoreq  (2,sync); }
// { atomic<ulong,lock> a(0);  a.min    (2,sync); }
// { atomic<ulong,lock> a(0);  a.max    (2,sync); }
// { atomic<ulong,lock> a(0);  a.inc    (  sync); }
// { atomic<ulong,lock> a(0);  a.preinc (  sync); }
// { atomic<ulong,lock> a(0);  a.postinc(  sync); }
// { atomic<ulong,lock> a(0);  a.dec    (  sync); }
// { atomic<ulong,lock> a(0);  a.predec (  sync); }
// { atomic<ulong,lock> a(0);  a.postdec(  sync); }
// { atomic<ulong,lock> a(0);  a.add    (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.sub    (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.mul    (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.div    (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.mod    (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.lshift (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.rshift (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.andeq  (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.oreq   (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.xoreq  (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.min    (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.max    (2,success,failure); }
// { atomic<ulong,lock> a(0);  a.inc    (  success,failure); }
// { atomic<ulong,lock> a(0);  a.preinc (  success,failure); }
// { atomic<ulong,lock> a(0);  a.postinc(  success,failure); }
// { atomic<ulong,lock> a(0);  a.dec    (  success,failure); }
// { atomic<ulong,lock> a(0);  a.predec (  success,failure); }
// { atomic<ulong,lock> a(0);  a.postdec(  success,failure); }

   { atomic<ulong,serial> a(0);  a.add    (2); }
   { atomic<ulong,serial> a(0);  a.sub    (2); }
   { atomic<ulong,serial> a(0);  a.mul    (2); }
   { atomic<ulong,serial> a(0);  a.div    (2); }
   { atomic<ulong,serial> a(0);  a.mod    (2); }
   { atomic<ulong,serial> a(0);  a.lshift (2); }
   { atomic<ulong,serial> a(0);  a.rshift (2); }
   { atomic<ulong,serial> a(0);  a.andeq  (2); }
   { atomic<ulong,serial> a(0);  a.oreq   (2); }
   { atomic<ulong,serial> a(0);  a.xoreq  (2); }
   { atomic<ulong,serial> a(0);  a.min    (2); }
   { atomic<ulong,serial> a(0);  a.max    (2); }
   { atomic<ulong,serial> a(0);  a.inc    ( ); }
   { atomic<ulong,serial> a(0);  a.preinc ( ); }
   { atomic<ulong,serial> a(0);  a.postinc( ); }
   { atomic<ulong,serial> a(0);  a.dec    ( ); }
   { atomic<ulong,serial> a(0);  a.predec ( ); }
   { atomic<ulong,serial> a(0);  a.postdec( ); }
// { atomic<ulong,serial> a(0);  a.add    (2,sync); }
// { atomic<ulong,serial> a(0);  a.sub    (2,sync); }
// { atomic<ulong,serial> a(0);  a.mul    (2,sync); }
// { atomic<ulong,serial> a(0);  a.div    (2,sync); }
// { atomic<ulong,serial> a(0);  a.mod    (2,sync); }
// { atomic<ulong,serial> a(0);  a.lshift (2,sync); }
// { atomic<ulong,serial> a(0);  a.rshift (2,sync); }
// { atomic<ulong,serial> a(0);  a.andeq  (2,sync); }
// { atomic<ulong,serial> a(0);  a.oreq   (2,sync); }
// { atomic<ulong,serial> a(0);  a.xoreq  (2,sync); }
// { atomic<ulong,serial> a(0);  a.min    (2,sync); }
// { atomic<ulong,serial> a(0);  a.max    (2,sync); }
// { atomic<ulong,serial> a(0);  a.inc    (  sync); }
// { atomic<ulong,serial> a(0);  a.preinc (  sync); }
// { atomic<ulong,serial> a(0);  a.postinc(  sync); }
// { atomic<ulong,serial> a(0);  a.dec    (  sync); }
// { atomic<ulong,serial> a(0);  a.predec (  sync); }
// { atomic<ulong,serial> a(0);  a.postdec(  sync); }
// { atomic<ulong,serial> a(0);  a.add    (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.sub    (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.mul    (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.div    (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.mod    (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.lshift (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.rshift (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.andeq  (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.oreq   (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.xoreq  (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.min    (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.max    (2,success,failure); }
// { atomic<ulong,serial> a(0);  a.inc    (  success,failure); }
// { atomic<ulong,serial> a(0);  a.preinc (  success,failure); }
// { atomic<ulong,serial> a(0);  a.postinc(  success,failure); }
// { atomic<ulong,serial> a(0);  a.dec    (  success,failure); }
// { atomic<ulong,serial> a(0);  a.predec (  success,failure); }
// { atomic<ulong,serial> a(0);  a.postdec(  success,failure); }



   // ------------------------
   // double
   // ------------------------

// { atomic<double,cpp> a(0);  a.add    (2); }
// { atomic<double,cpp> a(0);  a.sub    (2); }
// { atomic<double,cpp> a(0);  a.mul    (2); }
// { atomic<double,cpp> a(0);  a.div    (2); }
// { atomic<double,cpp> a(0);  a.mod    (2); }
// { atomic<double,cpp> a(0);  a.lshift (2); }
// { atomic<double,cpp> a(0);  a.rshift (2); }
// { atomic<double,cpp> a(0);  a.andeq  (2); }
// { atomic<double,cpp> a(0);  a.oreq   (2); }
// { atomic<double,cpp> a(0);  a.xoreq  (2); }
// { atomic<double,cpp> a(0);  a.min    (2); }
// { atomic<double,cpp> a(0);  a.max    (2); }
// { atomic<double,cpp> a(0);  a.inc    ( ); }
// { atomic<double,cpp> a(0);  a.preinc ( ); }
// { atomic<double,cpp> a(0);  a.postinc( ); }
// { atomic<double,cpp> a(0);  a.dec    ( ); }
// { atomic<double,cpp> a(0);  a.predec ( ); }
// { atomic<double,cpp> a(0);  a.postdec( ); }
// { atomic<double,cpp> a(0);  a.add    (2,sync); }
// { atomic<double,cpp> a(0);  a.sub    (2,sync); }
// { atomic<double,cpp> a(0);  a.mul    (2,sync); }
// { atomic<double,cpp> a(0);  a.div    (2,sync); }
// { atomic<double,cpp> a(0);  a.mod    (2,sync); }
// { atomic<double,cpp> a(0);  a.lshift (2,sync); }
// { atomic<double,cpp> a(0);  a.rshift (2,sync); }
// { atomic<double,cpp> a(0);  a.andeq  (2,sync); }
// { atomic<double,cpp> a(0);  a.oreq   (2,sync); }
// { atomic<double,cpp> a(0);  a.xoreq  (2,sync); }
// { atomic<double,cpp> a(0);  a.min    (2,sync); }
// { atomic<double,cpp> a(0);  a.max    (2,sync); }
// { atomic<double,cpp> a(0);  a.inc    (  sync); }
// { atomic<double,cpp> a(0);  a.preinc (  sync); }
// { atomic<double,cpp> a(0);  a.postinc(  sync); }
// { atomic<double,cpp> a(0);  a.dec    (  sync); }
// { atomic<double,cpp> a(0);  a.predec (  sync); }
// { atomic<double,cpp> a(0);  a.postdec(  sync); }
// { atomic<double,cpp> a(0);  a.add    (2,success,failure); }
// { atomic<double,cpp> a(0);  a.sub    (2,success,failure); }
// { atomic<double,cpp> a(0);  a.mul    (2,success,failure); }
// { atomic<double,cpp> a(0);  a.div    (2,success,failure); }
// { atomic<double,cpp> a(0);  a.mod    (2,success,failure); }
// { atomic<double,cpp> a(0);  a.lshift (2,success,failure); }
// { atomic<double,cpp> a(0);  a.rshift (2,success,failure); }
// { atomic<double,cpp> a(0);  a.andeq  (2,success,failure); }
// { atomic<double,cpp> a(0);  a.oreq   (2,success,failure); }
// { atomic<double,cpp> a(0);  a.xoreq  (2,success,failure); }
// { atomic<double,cpp> a(0);  a.min    (2,success,failure); }
// { atomic<double,cpp> a(0);  a.max    (2,success,failure); }
// { atomic<double,cpp> a(0);  a.inc    (  success,failure); }
// { atomic<double,cpp> a(0);  a.preinc (  success,failure); }
// { atomic<double,cpp> a(0);  a.postinc(  success,failure); }
// { atomic<double,cpp> a(0);  a.dec    (  success,failure); }
// { atomic<double,cpp> a(0);  a.predec (  success,failure); }
// { atomic<double,cpp> a(0);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { atomic<double,kokkos> a(0);  a.add    (2); }
   { atomic<double,kokkos> a(0);  a.sub    (2); }
   { atomic<double,kokkos> a(0);  a.mul    (2); }
   { atomic<double,kokkos> a(0);  a.div    (2); }
// { atomic<double,kokkos> a(0);  a.mod    (2); }
// { atomic<double,kokkos> a(0);  a.lshift (2); }
// { atomic<double,kokkos> a(0);  a.rshift (2); }
// { atomic<double,kokkos> a(0);  a.andeq  (2); }
// { atomic<double,kokkos> a(0);  a.oreq   (2); }
// { atomic<double,kokkos> a(0);  a.xoreq  (2); }
   { atomic<double,kokkos> a(0);  a.min    (2); }
   { atomic<double,kokkos> a(0);  a.max    (2); }
   { atomic<double,kokkos> a(0);  a.inc    ( ); }
   { atomic<double,kokkos> a(0);  a.preinc ( ); }
   { atomic<double,kokkos> a(0);  a.postinc( ); }
   { atomic<double,kokkos> a(0);  a.dec    ( ); }
   { atomic<double,kokkos> a(0);  a.predec ( ); }
   { atomic<double,kokkos> a(0);  a.postdec( ); }
// { atomic<double,kokkos> a(0);  a.add    (2,sync); }
// { atomic<double,kokkos> a(0);  a.sub    (2,sync); }
// { atomic<double,kokkos> a(0);  a.mul    (2,sync); }
// { atomic<double,kokkos> a(0);  a.div    (2,sync); }
// { atomic<double,kokkos> a(0);  a.mod    (2,sync); }
// { atomic<double,kokkos> a(0);  a.lshift (2,sync); }
// { atomic<double,kokkos> a(0);  a.rshift (2,sync); }
// { atomic<double,kokkos> a(0);  a.andeq  (2,sync); }
// { atomic<double,kokkos> a(0);  a.oreq   (2,sync); }
// { atomic<double,kokkos> a(0);  a.xoreq  (2,sync); }
// { atomic<double,kokkos> a(0);  a.min    (2,sync); }
// { atomic<double,kokkos> a(0);  a.max    (2,sync); }
// { atomic<double,kokkos> a(0);  a.inc    (  sync); }
// { atomic<double,kokkos> a(0);  a.preinc (  sync); }
// { atomic<double,kokkos> a(0);  a.postinc(  sync); }
// { atomic<double,kokkos> a(0);  a.dec    (  sync); }
// { atomic<double,kokkos> a(0);  a.predec (  sync); }
// { atomic<double,kokkos> a(0);  a.postdec(  sync); }
// { atomic<double,kokkos> a(0);  a.add    (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.sub    (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.mul    (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.div    (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.mod    (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.lshift (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.rshift (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.andeq  (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.oreq   (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.xoreq  (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.min    (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.max    (2,success,failure); }
// { atomic<double,kokkos> a(0);  a.inc    (  success,failure); }
// { atomic<double,kokkos> a(0);  a.preinc (  success,failure); }
// { atomic<double,kokkos> a(0);  a.postinc(  success,failure); }
// { atomic<double,kokkos> a(0);  a.dec    (  success,failure); }
// { atomic<double,kokkos> a(0);  a.predec (  success,failure); }
// { atomic<double,kokkos> a(0);  a.postdec(  success,failure); }
#endif

   { atomic<double,strong> a(0);  a.add    (2); }
   { atomic<double,strong> a(0);  a.sub    (2); }
   { atomic<double,strong> a(0);  a.mul    (2); }
   { atomic<double,strong> a(0);  a.div    (2); }
// { atomic<double,strong> a(0);  a.mod    (2); }
// { atomic<double,strong> a(0);  a.lshift (2); }
// { atomic<double,strong> a(0);  a.rshift (2); }
// { atomic<double,strong> a(0);  a.andeq  (2); }
// { atomic<double,strong> a(0);  a.oreq   (2); }
// { atomic<double,strong> a(0);  a.xoreq  (2); }
   { atomic<double,strong> a(0);  a.min    (2); }
   { atomic<double,strong> a(0);  a.max    (2); }
   { atomic<double,strong> a(0);  a.inc    ( ); }
   { atomic<double,strong> a(0);  a.preinc ( ); }
   { atomic<double,strong> a(0);  a.postinc( ); }
   { atomic<double,strong> a(0);  a.dec    ( ); }
   { atomic<double,strong> a(0);  a.predec ( ); }
   { atomic<double,strong> a(0);  a.postdec( ); }
   { atomic<double,strong> a(0);  a.add    (2,sync); }
   { atomic<double,strong> a(0);  a.sub    (2,sync); }
   { atomic<double,strong> a(0);  a.mul    (2,sync); }
   { atomic<double,strong> a(0);  a.div    (2,sync); }
// { atomic<double,strong> a(0);  a.mod    (2,sync); }
// { atomic<double,strong> a(0);  a.lshift (2,sync); }
// { atomic<double,strong> a(0);  a.rshift (2,sync); }
// { atomic<double,strong> a(0);  a.andeq  (2,sync); }
// { atomic<double,strong> a(0);  a.oreq   (2,sync); }
// { atomic<double,strong> a(0);  a.xoreq  (2,sync); }
   { atomic<double,strong> a(0);  a.min    (2,sync); }
   { atomic<double,strong> a(0);  a.max    (2,sync); }
   { atomic<double,strong> a(0);  a.inc    (  sync); }
   { atomic<double,strong> a(0);  a.preinc (  sync); }
   { atomic<double,strong> a(0);  a.postinc(  sync); }
   { atomic<double,strong> a(0);  a.dec    (  sync); }
   { atomic<double,strong> a(0);  a.predec (  sync); }
   { atomic<double,strong> a(0);  a.postdec(  sync); }
   { atomic<double,strong> a(0);  a.add    (2,success,failure); }
   { atomic<double,strong> a(0);  a.sub    (2,success,failure); }
   { atomic<double,strong> a(0);  a.mul    (2,success,failure); }
   { atomic<double,strong> a(0);  a.div    (2,success,failure); }
// { atomic<double,strong> a(0);  a.mod    (2,success,failure); }
// { atomic<double,strong> a(0);  a.lshift (2,success,failure); }
// { atomic<double,strong> a(0);  a.rshift (2,success,failure); }
// { atomic<double,strong> a(0);  a.andeq  (2,success,failure); }
// { atomic<double,strong> a(0);  a.oreq   (2,success,failure); }
// { atomic<double,strong> a(0);  a.xoreq  (2,success,failure); }
   { atomic<double,strong> a(0);  a.min    (2,success,failure); }
   { atomic<double,strong> a(0);  a.max    (2,success,failure); }
   { atomic<double,strong> a(0);  a.inc    (  success,failure); }
   { atomic<double,strong> a(0);  a.preinc (  success,failure); }
   { atomic<double,strong> a(0);  a.postinc(  success,failure); }
   { atomic<double,strong> a(0);  a.dec    (  success,failure); }
   { atomic<double,strong> a(0);  a.predec (  success,failure); }
   { atomic<double,strong> a(0);  a.postdec(  success,failure); }

   { atomic<double,strong::pun> a(0);  a.add    (2); }
   { atomic<double,strong::pun> a(0);  a.sub    (2); }
   { atomic<double,strong::pun> a(0);  a.mul    (2); }
   { atomic<double,strong::pun> a(0);  a.div    (2); }
// { atomic<double,strong::pun> a(0);  a.mod    (2); }
// { atomic<double,strong::pun> a(0);  a.lshift (2); }
// { atomic<double,strong::pun> a(0);  a.rshift (2); }
// { atomic<double,strong::pun> a(0);  a.andeq  (2); }
// { atomic<double,strong::pun> a(0);  a.oreq   (2); }
// { atomic<double,strong::pun> a(0);  a.xoreq  (2); }
   { atomic<double,strong::pun> a(0);  a.min    (2); }
   { atomic<double,strong::pun> a(0);  a.max    (2); }
   { atomic<double,strong::pun> a(0);  a.inc    ( ); }
   { atomic<double,strong::pun> a(0);  a.preinc ( ); }
   { atomic<double,strong::pun> a(0);  a.postinc( ); }
   { atomic<double,strong::pun> a(0);  a.dec    ( ); }
   { atomic<double,strong::pun> a(0);  a.predec ( ); }
   { atomic<double,strong::pun> a(0);  a.postdec( ); }
   { atomic<double,strong::pun> a(0);  a.add    (2,sync); }
   { atomic<double,strong::pun> a(0);  a.sub    (2,sync); }
   { atomic<double,strong::pun> a(0);  a.mul    (2,sync); }
   { atomic<double,strong::pun> a(0);  a.div    (2,sync); }
// { atomic<double,strong::pun> a(0);  a.mod    (2,sync); }
// { atomic<double,strong::pun> a(0);  a.lshift (2,sync); }
// { atomic<double,strong::pun> a(0);  a.rshift (2,sync); }
// { atomic<double,strong::pun> a(0);  a.andeq  (2,sync); }
// { atomic<double,strong::pun> a(0);  a.oreq   (2,sync); }
// { atomic<double,strong::pun> a(0);  a.xoreq  (2,sync); }
   { atomic<double,strong::pun> a(0);  a.min    (2,sync); }
   { atomic<double,strong::pun> a(0);  a.max    (2,sync); }
   { atomic<double,strong::pun> a(0);  a.inc    (  sync); }
   { atomic<double,strong::pun> a(0);  a.preinc (  sync); }
   { atomic<double,strong::pun> a(0);  a.postinc(  sync); }
   { atomic<double,strong::pun> a(0);  a.dec    (  sync); }
   { atomic<double,strong::pun> a(0);  a.predec (  sync); }
   { atomic<double,strong::pun> a(0);  a.postdec(  sync); }
   { atomic<double,strong::pun> a(0);  a.add    (2,success,failure); }
   { atomic<double,strong::pun> a(0);  a.sub    (2,success,failure); }
   { atomic<double,strong::pun> a(0);  a.mul    (2,success,failure); }
   { atomic<double,strong::pun> a(0);  a.div    (2,success,failure); }
// { atomic<double,strong::pun> a(0);  a.mod    (2,success,failure); }
// { atomic<double,strong::pun> a(0);  a.lshift (2,success,failure); }
// { atomic<double,strong::pun> a(0);  a.rshift (2,success,failure); }
// { atomic<double,strong::pun> a(0);  a.andeq  (2,success,failure); }
// { atomic<double,strong::pun> a(0);  a.oreq   (2,success,failure); }
// { atomic<double,strong::pun> a(0);  a.xoreq  (2,success,failure); }
   { atomic<double,strong::pun> a(0);  a.min    (2,success,failure); }
   { atomic<double,strong::pun> a(0);  a.max    (2,success,failure); }
   { atomic<double,strong::pun> a(0);  a.inc    (  success,failure); }
   { atomic<double,strong::pun> a(0);  a.preinc (  success,failure); }
   { atomic<double,strong::pun> a(0);  a.postinc(  success,failure); }
   { atomic<double,strong::pun> a(0);  a.dec    (  success,failure); }
   { atomic<double,strong::pun> a(0);  a.predec (  success,failure); }
   { atomic<double,strong::pun> a(0);  a.postdec(  success,failure); }

   { atomic<double,weak> a(0);  a.add    (2); }
   { atomic<double,weak> a(0);  a.sub    (2); }
   { atomic<double,weak> a(0);  a.mul    (2); }
   { atomic<double,weak> a(0);  a.div    (2); }
// { atomic<double,weak> a(0);  a.mod    (2); }
// { atomic<double,weak> a(0);  a.lshift (2); }
// { atomic<double,weak> a(0);  a.rshift (2); }
// { atomic<double,weak> a(0);  a.andeq  (2); }
// { atomic<double,weak> a(0);  a.oreq   (2); }
// { atomic<double,weak> a(0);  a.xoreq  (2); }
   { atomic<double,weak> a(0);  a.min    (2); }
   { atomic<double,weak> a(0);  a.max    (2); }
   { atomic<double,weak> a(0);  a.inc    ( ); }
   { atomic<double,weak> a(0);  a.preinc ( ); }
   { atomic<double,weak> a(0);  a.postinc( ); }
   { atomic<double,weak> a(0);  a.dec    ( ); }
   { atomic<double,weak> a(0);  a.predec ( ); }
   { atomic<double,weak> a(0);  a.postdec( ); }
   { atomic<double,weak> a(0);  a.add    (2,sync); }
   { atomic<double,weak> a(0);  a.sub    (2,sync); }
   { atomic<double,weak> a(0);  a.mul    (2,sync); }
   { atomic<double,weak> a(0);  a.div    (2,sync); }
// { atomic<double,weak> a(0);  a.mod    (2,sync); }
// { atomic<double,weak> a(0);  a.lshift (2,sync); }
// { atomic<double,weak> a(0);  a.rshift (2,sync); }
// { atomic<double,weak> a(0);  a.andeq  (2,sync); }
// { atomic<double,weak> a(0);  a.oreq   (2,sync); }
// { atomic<double,weak> a(0);  a.xoreq  (2,sync); }
   { atomic<double,weak> a(0);  a.min    (2,sync); }
   { atomic<double,weak> a(0);  a.max    (2,sync); }
   { atomic<double,weak> a(0);  a.inc    (  sync); }
   { atomic<double,weak> a(0);  a.preinc (  sync); }
   { atomic<double,weak> a(0);  a.postinc(  sync); }
   { atomic<double,weak> a(0);  a.dec    (  sync); }
   { atomic<double,weak> a(0);  a.predec (  sync); }
   { atomic<double,weak> a(0);  a.postdec(  sync); }
   { atomic<double,weak> a(0);  a.add    (2,success,failure); }
   { atomic<double,weak> a(0);  a.sub    (2,success,failure); }
   { atomic<double,weak> a(0);  a.mul    (2,success,failure); }
   { atomic<double,weak> a(0);  a.div    (2,success,failure); }
// { atomic<double,weak> a(0);  a.mod    (2,success,failure); }
// { atomic<double,weak> a(0);  a.lshift (2,success,failure); }
// { atomic<double,weak> a(0);  a.rshift (2,success,failure); }
// { atomic<double,weak> a(0);  a.andeq  (2,success,failure); }
// { atomic<double,weak> a(0);  a.oreq   (2,success,failure); }
// { atomic<double,weak> a(0);  a.xoreq  (2,success,failure); }
   { atomic<double,weak> a(0);  a.min    (2,success,failure); }
   { atomic<double,weak> a(0);  a.max    (2,success,failure); }
   { atomic<double,weak> a(0);  a.inc    (  success,failure); }
   { atomic<double,weak> a(0);  a.preinc (  success,failure); }
   { atomic<double,weak> a(0);  a.postinc(  success,failure); }
   { atomic<double,weak> a(0);  a.dec    (  success,failure); }
   { atomic<double,weak> a(0);  a.predec (  success,failure); }
   { atomic<double,weak> a(0);  a.postdec(  success,failure); }

   { atomic<double,weak::pun> a(0);  a.add    (2); }
   { atomic<double,weak::pun> a(0);  a.sub    (2); }
   { atomic<double,weak::pun> a(0);  a.mul    (2); }
   { atomic<double,weak::pun> a(0);  a.div    (2); }
// { atomic<double,weak::pun> a(0);  a.mod    (2); }
// { atomic<double,weak::pun> a(0);  a.lshift (2); }
// { atomic<double,weak::pun> a(0);  a.rshift (2); }
// { atomic<double,weak::pun> a(0);  a.andeq  (2); }
// { atomic<double,weak::pun> a(0);  a.oreq   (2); }
// { atomic<double,weak::pun> a(0);  a.xoreq  (2); }
   { atomic<double,weak::pun> a(0);  a.min    (2); }
   { atomic<double,weak::pun> a(0);  a.max    (2); }
   { atomic<double,weak::pun> a(0);  a.inc    ( ); }
   { atomic<double,weak::pun> a(0);  a.preinc ( ); }
   { atomic<double,weak::pun> a(0);  a.postinc( ); }
   { atomic<double,weak::pun> a(0);  a.dec    ( ); }
   { atomic<double,weak::pun> a(0);  a.predec ( ); }
   { atomic<double,weak::pun> a(0);  a.postdec( ); }
   { atomic<double,weak::pun> a(0);  a.add    (2,sync); }
   { atomic<double,weak::pun> a(0);  a.sub    (2,sync); }
   { atomic<double,weak::pun> a(0);  a.mul    (2,sync); }
   { atomic<double,weak::pun> a(0);  a.div    (2,sync); }
// { atomic<double,weak::pun> a(0);  a.mod    (2,sync); }
// { atomic<double,weak::pun> a(0);  a.lshift (2,sync); }
// { atomic<double,weak::pun> a(0);  a.rshift (2,sync); }
// { atomic<double,weak::pun> a(0);  a.andeq  (2,sync); }
// { atomic<double,weak::pun> a(0);  a.oreq   (2,sync); }
// { atomic<double,weak::pun> a(0);  a.xoreq  (2,sync); }
   { atomic<double,weak::pun> a(0);  a.min    (2,sync); }
   { atomic<double,weak::pun> a(0);  a.max    (2,sync); }
   { atomic<double,weak::pun> a(0);  a.inc    (  sync); }
   { atomic<double,weak::pun> a(0);  a.preinc (  sync); }
   { atomic<double,weak::pun> a(0);  a.postinc(  sync); }
   { atomic<double,weak::pun> a(0);  a.dec    (  sync); }
   { atomic<double,weak::pun> a(0);  a.predec (  sync); }
   { atomic<double,weak::pun> a(0);  a.postdec(  sync); }
   { atomic<double,weak::pun> a(0);  a.add    (2,success,failure); }
   { atomic<double,weak::pun> a(0);  a.sub    (2,success,failure); }
   { atomic<double,weak::pun> a(0);  a.mul    (2,success,failure); }
   { atomic<double,weak::pun> a(0);  a.div    (2,success,failure); }
// { atomic<double,weak::pun> a(0);  a.mod    (2,success,failure); }
// { atomic<double,weak::pun> a(0);  a.lshift (2,success,failure); }
// { atomic<double,weak::pun> a(0);  a.rshift (2,success,failure); }
// { atomic<double,weak::pun> a(0);  a.andeq  (2,success,failure); }
// { atomic<double,weak::pun> a(0);  a.oreq   (2,success,failure); }
// { atomic<double,weak::pun> a(0);  a.xoreq  (2,success,failure); }
   { atomic<double,weak::pun> a(0);  a.min    (2,success,failure); }
   { atomic<double,weak::pun> a(0);  a.max    (2,success,failure); }
   { atomic<double,weak::pun> a(0);  a.inc    (  success,failure); }
   { atomic<double,weak::pun> a(0);  a.preinc (  success,failure); }
   { atomic<double,weak::pun> a(0);  a.postinc(  success,failure); }
   { atomic<double,weak::pun> a(0);  a.dec    (  success,failure); }
   { atomic<double,weak::pun> a(0);  a.predec (  success,failure); }
   { atomic<double,weak::pun> a(0);  a.postdec(  success,failure); }

   { atomic<double,lock> a(0);  a.add    (2); }
   { atomic<double,lock> a(0);  a.sub    (2); }
   { atomic<double,lock> a(0);  a.mul    (2); }
   { atomic<double,lock> a(0);  a.div    (2); }
// { atomic<double,lock> a(0);  a.mod    (2); }
// { atomic<double,lock> a(0);  a.lshift (2); }
// { atomic<double,lock> a(0);  a.rshift (2); }
// { atomic<double,lock> a(0);  a.andeq  (2); }
// { atomic<double,lock> a(0);  a.oreq   (2); }
// { atomic<double,lock> a(0);  a.xoreq  (2); }
   { atomic<double,lock> a(0);  a.min    (2); }
   { atomic<double,lock> a(0);  a.max    (2); }
   { atomic<double,lock> a(0);  a.inc    ( ); }
   { atomic<double,lock> a(0);  a.preinc ( ); }
   { atomic<double,lock> a(0);  a.postinc( ); }
   { atomic<double,lock> a(0);  a.dec    ( ); }
   { atomic<double,lock> a(0);  a.predec ( ); }
   { atomic<double,lock> a(0);  a.postdec( ); }
// { atomic<double,lock> a(0);  a.add    (2,sync); }
// { atomic<double,lock> a(0);  a.sub    (2,sync); }
// { atomic<double,lock> a(0);  a.mul    (2,sync); }
// { atomic<double,lock> a(0);  a.div    (2,sync); }
// { atomic<double,lock> a(0);  a.mod    (2,sync); }
// { atomic<double,lock> a(0);  a.lshift (2,sync); }
// { atomic<double,lock> a(0);  a.rshift (2,sync); }
// { atomic<double,lock> a(0);  a.andeq  (2,sync); }
// { atomic<double,lock> a(0);  a.oreq   (2,sync); }
// { atomic<double,lock> a(0);  a.xoreq  (2,sync); }
// { atomic<double,lock> a(0);  a.min    (2,sync); }
// { atomic<double,lock> a(0);  a.max    (2,sync); }
// { atomic<double,lock> a(0);  a.inc    (  sync); }
// { atomic<double,lock> a(0);  a.preinc (  sync); }
// { atomic<double,lock> a(0);  a.postinc(  sync); }
// { atomic<double,lock> a(0);  a.dec    (  sync); }
// { atomic<double,lock> a(0);  a.predec (  sync); }
// { atomic<double,lock> a(0);  a.postdec(  sync); }
// { atomic<double,lock> a(0);  a.add    (2,success,failure); }
// { atomic<double,lock> a(0);  a.sub    (2,success,failure); }
// { atomic<double,lock> a(0);  a.mul    (2,success,failure); }
// { atomic<double,lock> a(0);  a.div    (2,success,failure); }
// { atomic<double,lock> a(0);  a.mod    (2,success,failure); }
// { atomic<double,lock> a(0);  a.lshift (2,success,failure); }
// { atomic<double,lock> a(0);  a.rshift (2,success,failure); }
// { atomic<double,lock> a(0);  a.andeq  (2,success,failure); }
// { atomic<double,lock> a(0);  a.oreq   (2,success,failure); }
// { atomic<double,lock> a(0);  a.xoreq  (2,success,failure); }
// { atomic<double,lock> a(0);  a.min    (2,success,failure); }
// { atomic<double,lock> a(0);  a.max    (2,success,failure); }
// { atomic<double,lock> a(0);  a.inc    (  success,failure); }
// { atomic<double,lock> a(0);  a.preinc (  success,failure); }
// { atomic<double,lock> a(0);  a.postinc(  success,failure); }
// { atomic<double,lock> a(0);  a.dec    (  success,failure); }
// { atomic<double,lock> a(0);  a.predec (  success,failure); }
// { atomic<double,lock> a(0);  a.postdec(  success,failure); }

   { atomic<double,serial> a(0);  a.add    (2); }
   { atomic<double,serial> a(0);  a.sub    (2); }
   { atomic<double,serial> a(0);  a.mul    (2); }
   { atomic<double,serial> a(0);  a.div    (2); }
// { atomic<double,serial> a(0);  a.mod    (2); }
// { atomic<double,serial> a(0);  a.lshift (2); }
// { atomic<double,serial> a(0);  a.rshift (2); }
// { atomic<double,serial> a(0);  a.andeq  (2); }
// { atomic<double,serial> a(0);  a.oreq   (2); }
// { atomic<double,serial> a(0);  a.xoreq  (2); }
   { atomic<double,serial> a(0);  a.min    (2); }
   { atomic<double,serial> a(0);  a.max    (2); }
   { atomic<double,serial> a(0);  a.inc    ( ); }
   { atomic<double,serial> a(0);  a.preinc ( ); }
   { atomic<double,serial> a(0);  a.postinc( ); }
   { atomic<double,serial> a(0);  a.dec    ( ); }
   { atomic<double,serial> a(0);  a.predec ( ); }
   { atomic<double,serial> a(0);  a.postdec( ); }
// { atomic<double,serial> a(0);  a.add    (2,sync); }
// { atomic<double,serial> a(0);  a.sub    (2,sync); }
// { atomic<double,serial> a(0);  a.mul    (2,sync); }
// { atomic<double,serial> a(0);  a.div    (2,sync); }
// { atomic<double,serial> a(0);  a.mod    (2,sync); }
// { atomic<double,serial> a(0);  a.lshift (2,sync); }
// { atomic<double,serial> a(0);  a.rshift (2,sync); }
// { atomic<double,serial> a(0);  a.andeq  (2,sync); }
// { atomic<double,serial> a(0);  a.oreq   (2,sync); }
// { atomic<double,serial> a(0);  a.xoreq  (2,sync); }
// { atomic<double,serial> a(0);  a.min    (2,sync); }
// { atomic<double,serial> a(0);  a.max    (2,sync); }
// { atomic<double,serial> a(0);  a.inc    (  sync); }
// { atomic<double,serial> a(0);  a.preinc (  sync); }
// { atomic<double,serial> a(0);  a.postinc(  sync); }
// { atomic<double,serial> a(0);  a.dec    (  sync); }
// { atomic<double,serial> a(0);  a.predec (  sync); }
// { atomic<double,serial> a(0);  a.postdec(  sync); }
// { atomic<double,serial> a(0);  a.add    (2,success,failure); }
// { atomic<double,serial> a(0);  a.sub    (2,success,failure); }
// { atomic<double,serial> a(0);  a.mul    (2,success,failure); }
// { atomic<double,serial> a(0);  a.div    (2,success,failure); }
// { atomic<double,serial> a(0);  a.mod    (2,success,failure); }
// { atomic<double,serial> a(0);  a.lshift (2,success,failure); }
// { atomic<double,serial> a(0);  a.rshift (2,success,failure); }
// { atomic<double,serial> a(0);  a.andeq  (2,success,failure); }
// { atomic<double,serial> a(0);  a.oreq   (2,success,failure); }
// { atomic<double,serial> a(0);  a.xoreq  (2,success,failure); }
// { atomic<double,serial> a(0);  a.min    (2,success,failure); }
// { atomic<double,serial> a(0);  a.max    (2,success,failure); }
// { atomic<double,serial> a(0);  a.inc    (  success,failure); }
// { atomic<double,serial> a(0);  a.preinc (  success,failure); }
// { atomic<double,serial> a(0);  a.postinc(  success,failure); }
// { atomic<double,serial> a(0);  a.dec    (  success,failure); }
// { atomic<double,serial> a(0);  a.predec (  success,failure); }
// { atomic<double,serial> a(0);  a.postdec(  success,failure); }



   // ------------------------
   // int*
   // ------------------------

   (void)i;
   (void)j;
#if !defined(ATOMICS_TEST)
   { atomic<int*,cpp> a(&i);  a.add    (2); }
   { atomic<int*,cpp> a(&i);  a.sub    (2); }
// { atomic<int*,cpp> a(&i);  a.mul    (2); }
// { atomic<int*,cpp> a(&i);  a.div    (2); }
// { atomic<int*,cpp> a(&i);  a.mod    (2); }
// { atomic<int*,cpp> a(&i);  a.lshift (2); }
// { atomic<int*,cpp> a(&i);  a.rshift (2); }
// { atomic<int*,cpp> a(&i);  a.andeq  (2); }
// { atomic<int*,cpp> a(&i);  a.oreq   (2); }
// { atomic<int*,cpp> a(&i);  a.xoreq  (2); }
// { atomic<int*,cpp> a(&i);  a.min    (&j); }
// { atomic<int*,cpp> a(&i);  a.max    (&j); }
   { atomic<int*,cpp> a(&i);  a.inc    ( ); }
   { atomic<int*,cpp> a(&i);  a.preinc ( ); }
   { atomic<int*,cpp> a(&i);  a.postinc( ); }
   { atomic<int*,cpp> a(&i);  a.dec    ( ); }
   { atomic<int*,cpp> a(&i);  a.predec ( ); }
   { atomic<int*,cpp> a(&i);  a.postdec( ); }
   { atomic<int*,cpp> a(&i);  a.add    (2,sync); }
   { atomic<int*,cpp> a(&i);  a.sub    (2,sync); }
// { atomic<int*,cpp> a(&i);  a.mul    (2,sync); }
// { atomic<int*,cpp> a(&i);  a.div    (2,sync); }
// { atomic<int*,cpp> a(&i);  a.mod    (2,sync); }
// { atomic<int*,cpp> a(&i);  a.lshift (2,sync); }
// { atomic<int*,cpp> a(&i);  a.rshift (2,sync); }
// { atomic<int*,cpp> a(&i);  a.andeq  (2,sync); }
// { atomic<int*,cpp> a(&i);  a.oreq   (2,sync); }
// { atomic<int*,cpp> a(&i);  a.xoreq  (2,sync); }
// { atomic<int*,cpp> a(&i);  a.min    (&j,sync); }
// { atomic<int*,cpp> a(&i);  a.max    (&j,sync); }
// { atomic<int*,cpp> a(&i);  a.inc    (  sync); }
// { atomic<int*,cpp> a(&i);  a.preinc (  sync); }
// { atomic<int*,cpp> a(&i);  a.postinc(  sync); }
// { atomic<int*,cpp> a(&i);  a.dec    (  sync); }
// { atomic<int*,cpp> a(&i);  a.predec (  sync); }
// { atomic<int*,cpp> a(&i);  a.postdec(  sync); }
// { atomic<int*,cpp> a(&i);  a.add    (2,success,failure); }
// { atomic<int*,cpp> a(&i);  a.sub    (2,success,failure); }
// { atomic<int*,cpp> a(&i);  a.mul    (2,success,failure); }
// { atomic<int*,cpp> a(&i);  a.div    (2,success,failure); }
// { atomic<int*,cpp> a(&i);  a.mod    (2,success,failure); }
// { atomic<int*,cpp> a(&i);  a.lshift (2,success,failure); }
// { atomic<int*,cpp> a(&i);  a.rshift (2,success,failure); }
// { atomic<int*,cpp> a(&i);  a.andeq  (2,success,failure); }
// { atomic<int*,cpp> a(&i);  a.oreq   (2,success,failure); }
// { atomic<int*,cpp> a(&i);  a.xoreq  (2,success,failure); }
// { atomic<int*,cpp> a(&i);  a.min    (&j,success,failure); }
// { atomic<int*,cpp> a(&i);  a.max    (&j,success,failure); }
// { atomic<int*,cpp> a(&i);  a.inc    (  success,failure); }
// { atomic<int*,cpp> a(&i);  a.preinc (  success,failure); }
// { atomic<int*,cpp> a(&i);  a.postinc(  success,failure); }
// { atomic<int*,cpp> a(&i);  a.dec    (  success,failure); }
// { atomic<int*,cpp> a(&i);  a.predec (  success,failure); }
// { atomic<int*,cpp> a(&i);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { atomic<int*,kokkos> a(&i);  a.add    (2); }
// { atomic<int*,kokkos> a(&i);  a.sub    (2); }
// { atomic<int*,kokkos> a(&i);  a.mul    (2); }
// { atomic<int*,kokkos> a(&i);  a.div    (2); }
// { atomic<int*,kokkos> a(&i);  a.mod    (2); }
// { atomic<int*,kokkos> a(&i);  a.lshift (2); }
// { atomic<int*,kokkos> a(&i);  a.rshift (2); }
// { atomic<int*,kokkos> a(&i);  a.andeq  (2); }
// { atomic<int*,kokkos> a(&i);  a.oreq   (2); }
// { atomic<int*,kokkos> a(&i);  a.xoreq  (2); }
// { atomic<int*,kokkos> a(&i);  a.min    (&j); }
// { atomic<int*,kokkos> a(&i);  a.max    (&j); }
// { atomic<int*,kokkos> a(&i);  a.inc    ( ); }
// { atomic<int*,kokkos> a(&i);  a.preinc ( ); }
// { atomic<int*,kokkos> a(&i);  a.postinc( ); }
// { atomic<int*,kokkos> a(&i);  a.dec    ( ); }
// { atomic<int*,kokkos> a(&i);  a.predec ( ); }
// { atomic<int*,kokkos> a(&i);  a.postdec( ); }
// { atomic<int*,kokkos> a(&i);  a.add    (2,sync); }
// { atomic<int*,kokkos> a(&i);  a.sub    (2,sync); }
// { atomic<int*,kokkos> a(&i);  a.mul    (2,sync); }
// { atomic<int*,kokkos> a(&i);  a.div    (2,sync); }
// { atomic<int*,kokkos> a(&i);  a.mod    (2,sync); }
// { atomic<int*,kokkos> a(&i);  a.lshift (2,sync); }
// { atomic<int*,kokkos> a(&i);  a.rshift (2,sync); }
// { atomic<int*,kokkos> a(&i);  a.andeq  (2,sync); }
// { atomic<int*,kokkos> a(&i);  a.oreq   (2,sync); }
// { atomic<int*,kokkos> a(&i);  a.xoreq  (2,sync); }
// { atomic<int*,kokkos> a(&i);  a.min    (&j,sync); }
// { atomic<int*,kokkos> a(&i);  a.max    (&j,sync); }
// { atomic<int*,kokkos> a(&i);  a.inc    (  sync); }
// { atomic<int*,kokkos> a(&i);  a.preinc (  sync); }
// { atomic<int*,kokkos> a(&i);  a.postinc(  sync); }
// { atomic<int*,kokkos> a(&i);  a.dec    (  sync); }
// { atomic<int*,kokkos> a(&i);  a.predec (  sync); }
// { atomic<int*,kokkos> a(&i);  a.postdec(  sync); }
// { atomic<int*,kokkos> a(&i);  a.add    (2,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.sub    (2,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.mul    (2,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.div    (2,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.mod    (2,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.lshift (2,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.rshift (2,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.andeq  (2,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.oreq   (2,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.xoreq  (2,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.min    (&j,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.max    (&j,success,failure); }
// { atomic<int*,kokkos> a(&i);  a.inc    (  success,failure); }
// { atomic<int*,kokkos> a(&i);  a.preinc (  success,failure); }
// { atomic<int*,kokkos> a(&i);  a.postinc(  success,failure); }
// { atomic<int*,kokkos> a(&i);  a.dec    (  success,failure); }
// { atomic<int*,kokkos> a(&i);  a.predec (  success,failure); }
// { atomic<int*,kokkos> a(&i);  a.postdec(  success,failure); }
#endif

   { atomic<int*,strong> a(&i);  a.add    (2); }
   { atomic<int*,strong> a(&i);  a.sub    (2); }
// { atomic<int*,strong> a(&i);  a.mul    (2); }
// { atomic<int*,strong> a(&i);  a.div    (2); }
// { atomic<int*,strong> a(&i);  a.mod    (2); }
// { atomic<int*,strong> a(&i);  a.lshift (2); }
// { atomic<int*,strong> a(&i);  a.rshift (2); }
// { atomic<int*,strong> a(&i);  a.andeq  (2); }
// { atomic<int*,strong> a(&i);  a.oreq   (2); }
// { atomic<int*,strong> a(&i);  a.xoreq  (2); }
   { atomic<int*,strong> a(&i);  a.min    (&j); }
   { atomic<int*,strong> a(&i);  a.max    (&j); }
   { atomic<int*,strong> a(&i);  a.inc    ( ); }
   { atomic<int*,strong> a(&i);  a.preinc ( ); }
   { atomic<int*,strong> a(&i);  a.postinc( ); }
   { atomic<int*,strong> a(&i);  a.dec    ( ); }
   { atomic<int*,strong> a(&i);  a.predec ( ); }
   { atomic<int*,strong> a(&i);  a.postdec( ); }
   { atomic<int*,strong> a(&i);  a.add    (2,sync); }
   { atomic<int*,strong> a(&i);  a.sub    (2,sync); }
// { atomic<int*,strong> a(&i);  a.mul    (2,sync); }
// { atomic<int*,strong> a(&i);  a.div    (2,sync); }
// { atomic<int*,strong> a(&i);  a.mod    (2,sync); }
// { atomic<int*,strong> a(&i);  a.lshift (2,sync); }
// { atomic<int*,strong> a(&i);  a.rshift (2,sync); }
// { atomic<int*,strong> a(&i);  a.andeq  (2,sync); }
// { atomic<int*,strong> a(&i);  a.oreq   (2,sync); }
// { atomic<int*,strong> a(&i);  a.xoreq  (2,sync); }
   { atomic<int*,strong> a(&i);  a.min    (&j,sync); }
   { atomic<int*,strong> a(&i);  a.max    (&j,sync); }
   { atomic<int*,strong> a(&i);  a.inc    (  sync); }
   { atomic<int*,strong> a(&i);  a.preinc (  sync); }
   { atomic<int*,strong> a(&i);  a.postinc(  sync); }
   { atomic<int*,strong> a(&i);  a.dec    (  sync); }
   { atomic<int*,strong> a(&i);  a.predec (  sync); }
   { atomic<int*,strong> a(&i);  a.postdec(  sync); }
   { atomic<int*,strong> a(&i);  a.add    (2,success,failure); }
   { atomic<int*,strong> a(&i);  a.sub    (2,success,failure); }
// { atomic<int*,strong> a(&i);  a.mul    (2,success,failure); }
// { atomic<int*,strong> a(&i);  a.div    (2,success,failure); }
// { atomic<int*,strong> a(&i);  a.mod    (2,success,failure); }
// { atomic<int*,strong> a(&i);  a.lshift (2,success,failure); }
// { atomic<int*,strong> a(&i);  a.rshift (2,success,failure); }
// { atomic<int*,strong> a(&i);  a.andeq  (2,success,failure); }
// { atomic<int*,strong> a(&i);  a.oreq   (2,success,failure); }
// { atomic<int*,strong> a(&i);  a.xoreq  (2,success,failure); }
   { atomic<int*,strong> a(&i);  a.min    (&j,success,failure); }
   { atomic<int*,strong> a(&i);  a.max    (&j,success,failure); }
   { atomic<int*,strong> a(&i);  a.inc    (  success,failure); }
   { atomic<int*,strong> a(&i);  a.preinc (  success,failure); }
   { atomic<int*,strong> a(&i);  a.postinc(  success,failure); }
   { atomic<int*,strong> a(&i);  a.dec    (  success,failure); }
   { atomic<int*,strong> a(&i);  a.predec (  success,failure); }
   { atomic<int*,strong> a(&i);  a.postdec(  success,failure); }

   { atomic<int*,strong::pun> a(&i);  a.add    (2); }
   { atomic<int*,strong::pun> a(&i);  a.sub    (2); }
// { atomic<int*,strong::pun> a(&i);  a.mul    (2); }
// { atomic<int*,strong::pun> a(&i);  a.div    (2); }
// { atomic<int*,strong::pun> a(&i);  a.mod    (2); }
// { atomic<int*,strong::pun> a(&i);  a.lshift (2); }
// { atomic<int*,strong::pun> a(&i);  a.rshift (2); }
// { atomic<int*,strong::pun> a(&i);  a.andeq  (2); }
// { atomic<int*,strong::pun> a(&i);  a.oreq   (2); }
// { atomic<int*,strong::pun> a(&i);  a.xoreq  (2); }
   { atomic<int*,strong::pun> a(&i);  a.min    (&j); }
   { atomic<int*,strong::pun> a(&i);  a.max    (&j); }
   { atomic<int*,strong::pun> a(&i);  a.inc    ( ); }
   { atomic<int*,strong::pun> a(&i);  a.preinc ( ); }
   { atomic<int*,strong::pun> a(&i);  a.postinc( ); }
   { atomic<int*,strong::pun> a(&i);  a.dec    ( ); }
   { atomic<int*,strong::pun> a(&i);  a.predec ( ); }
   { atomic<int*,strong::pun> a(&i);  a.postdec( ); }
   { atomic<int*,strong::pun> a(&i);  a.add    (2,sync); }
   { atomic<int*,strong::pun> a(&i);  a.sub    (2,sync); }
// { atomic<int*,strong::pun> a(&i);  a.mul    (2,sync); }
// { atomic<int*,strong::pun> a(&i);  a.div    (2,sync); }
// { atomic<int*,strong::pun> a(&i);  a.mod    (2,sync); }
// { atomic<int*,strong::pun> a(&i);  a.lshift (2,sync); }
// { atomic<int*,strong::pun> a(&i);  a.rshift (2,sync); }
// { atomic<int*,strong::pun> a(&i);  a.andeq  (2,sync); }
// { atomic<int*,strong::pun> a(&i);  a.oreq   (2,sync); }
// { atomic<int*,strong::pun> a(&i);  a.xoreq  (2,sync); }
   { atomic<int*,strong::pun> a(&i);  a.min    (&j,sync); }
   { atomic<int*,strong::pun> a(&i);  a.max    (&j,sync); }
   { atomic<int*,strong::pun> a(&i);  a.inc    (  sync); }
   { atomic<int*,strong::pun> a(&i);  a.preinc (  sync); }
   { atomic<int*,strong::pun> a(&i);  a.postinc(  sync); }
   { atomic<int*,strong::pun> a(&i);  a.dec    (  sync); }
   { atomic<int*,strong::pun> a(&i);  a.predec (  sync); }
   { atomic<int*,strong::pun> a(&i);  a.postdec(  sync); }
   { atomic<int*,strong::pun> a(&i);  a.add    (2,success,failure); }
   { atomic<int*,strong::pun> a(&i);  a.sub    (2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  a.mul    (2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  a.div    (2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  a.mod    (2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  a.lshift (2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  a.rshift (2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  a.andeq  (2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  a.oreq   (2,success,failure); }
// { atomic<int*,strong::pun> a(&i);  a.xoreq  (2,success,failure); }
   { atomic<int*,strong::pun> a(&i);  a.min    (&j,success,failure); }
   { atomic<int*,strong::pun> a(&i);  a.max    (&j,success,failure); }
   { atomic<int*,strong::pun> a(&i);  a.inc    (  success,failure); }
   { atomic<int*,strong::pun> a(&i);  a.preinc (  success,failure); }
   { atomic<int*,strong::pun> a(&i);  a.postinc(  success,failure); }
   { atomic<int*,strong::pun> a(&i);  a.dec    (  success,failure); }
   { atomic<int*,strong::pun> a(&i);  a.predec (  success,failure); }
   { atomic<int*,strong::pun> a(&i);  a.postdec(  success,failure); }

   { atomic<int*,weak> a(&i);  a.add    (2); }
   { atomic<int*,weak> a(&i);  a.sub    (2); }
// { atomic<int*,weak> a(&i);  a.mul    (2); }
// { atomic<int*,weak> a(&i);  a.div    (2); }
// { atomic<int*,weak> a(&i);  a.mod    (2); }
// { atomic<int*,weak> a(&i);  a.lshift (2); }
// { atomic<int*,weak> a(&i);  a.rshift (2); }
// { atomic<int*,weak> a(&i);  a.andeq  (2); }
// { atomic<int*,weak> a(&i);  a.oreq   (2); }
// { atomic<int*,weak> a(&i);  a.xoreq  (2); }
   { atomic<int*,weak> a(&i);  a.min    (&j); }
   { atomic<int*,weak> a(&i);  a.max    (&j); }
   { atomic<int*,weak> a(&i);  a.inc    ( ); }
   { atomic<int*,weak> a(&i);  a.preinc ( ); }
   { atomic<int*,weak> a(&i);  a.postinc( ); }
   { atomic<int*,weak> a(&i);  a.dec    ( ); }
   { atomic<int*,weak> a(&i);  a.predec ( ); }
   { atomic<int*,weak> a(&i);  a.postdec( ); }
   { atomic<int*,weak> a(&i);  a.add    (2,sync); }
   { atomic<int*,weak> a(&i);  a.sub    (2,sync); }
// { atomic<int*,weak> a(&i);  a.mul    (2,sync); }
// { atomic<int*,weak> a(&i);  a.div    (2,sync); }
// { atomic<int*,weak> a(&i);  a.mod    (2,sync); }
// { atomic<int*,weak> a(&i);  a.lshift (2,sync); }
// { atomic<int*,weak> a(&i);  a.rshift (2,sync); }
// { atomic<int*,weak> a(&i);  a.andeq  (2,sync); }
// { atomic<int*,weak> a(&i);  a.oreq   (2,sync); }
// { atomic<int*,weak> a(&i);  a.xoreq  (2,sync); }
   { atomic<int*,weak> a(&i);  a.min    (&j,sync); }
   { atomic<int*,weak> a(&i);  a.max    (&j,sync); }
   { atomic<int*,weak> a(&i);  a.inc    (  sync); }
   { atomic<int*,weak> a(&i);  a.preinc (  sync); }
   { atomic<int*,weak> a(&i);  a.postinc(  sync); }
   { atomic<int*,weak> a(&i);  a.dec    (  sync); }
   { atomic<int*,weak> a(&i);  a.predec (  sync); }
   { atomic<int*,weak> a(&i);  a.postdec(  sync); }
   { atomic<int*,weak> a(&i);  a.add    (2,success,failure); }
   { atomic<int*,weak> a(&i);  a.sub    (2,success,failure); }
// { atomic<int*,weak> a(&i);  a.mul    (2,success,failure); }
// { atomic<int*,weak> a(&i);  a.div    (2,success,failure); }
// { atomic<int*,weak> a(&i);  a.mod    (2,success,failure); }
// { atomic<int*,weak> a(&i);  a.lshift (2,success,failure); }
// { atomic<int*,weak> a(&i);  a.rshift (2,success,failure); }
// { atomic<int*,weak> a(&i);  a.andeq  (2,success,failure); }
// { atomic<int*,weak> a(&i);  a.oreq   (2,success,failure); }
// { atomic<int*,weak> a(&i);  a.xoreq  (2,success,failure); }
   { atomic<int*,weak> a(&i);  a.min    (&j,success,failure); }
   { atomic<int*,weak> a(&i);  a.max    (&j,success,failure); }
   { atomic<int*,weak> a(&i);  a.inc    (  success,failure); }
   { atomic<int*,weak> a(&i);  a.preinc (  success,failure); }
   { atomic<int*,weak> a(&i);  a.postinc(  success,failure); }
   { atomic<int*,weak> a(&i);  a.dec    (  success,failure); }
   { atomic<int*,weak> a(&i);  a.predec (  success,failure); }
   { atomic<int*,weak> a(&i);  a.postdec(  success,failure); }

   { atomic<int*,weak::pun> a(&i);  a.add    (2); }
   { atomic<int*,weak::pun> a(&i);  a.sub    (2); }
// { atomic<int*,weak::pun> a(&i);  a.mul    (2); }
// { atomic<int*,weak::pun> a(&i);  a.div    (2); }
// { atomic<int*,weak::pun> a(&i);  a.mod    (2); }
// { atomic<int*,weak::pun> a(&i);  a.lshift (2); }
// { atomic<int*,weak::pun> a(&i);  a.rshift (2); }
// { atomic<int*,weak::pun> a(&i);  a.andeq  (2); }
// { atomic<int*,weak::pun> a(&i);  a.oreq   (2); }
// { atomic<int*,weak::pun> a(&i);  a.xoreq  (2); }
   { atomic<int*,weak::pun> a(&i);  a.min    (&j); }
   { atomic<int*,weak::pun> a(&i);  a.max    (&j); }
   { atomic<int*,weak::pun> a(&i);  a.inc    ( ); }
   { atomic<int*,weak::pun> a(&i);  a.preinc ( ); }
   { atomic<int*,weak::pun> a(&i);  a.postinc( ); }
   { atomic<int*,weak::pun> a(&i);  a.dec    ( ); }
   { atomic<int*,weak::pun> a(&i);  a.predec ( ); }
   { atomic<int*,weak::pun> a(&i);  a.postdec( ); }
   { atomic<int*,weak::pun> a(&i);  a.add    (2,sync); }
   { atomic<int*,weak::pun> a(&i);  a.sub    (2,sync); }
// { atomic<int*,weak::pun> a(&i);  a.mul    (2,sync); }
// { atomic<int*,weak::pun> a(&i);  a.div    (2,sync); }
// { atomic<int*,weak::pun> a(&i);  a.mod    (2,sync); }
// { atomic<int*,weak::pun> a(&i);  a.lshift (2,sync); }
// { atomic<int*,weak::pun> a(&i);  a.rshift (2,sync); }
// { atomic<int*,weak::pun> a(&i);  a.andeq  (2,sync); }
// { atomic<int*,weak::pun> a(&i);  a.oreq   (2,sync); }
// { atomic<int*,weak::pun> a(&i);  a.xoreq  (2,sync); }
   { atomic<int*,weak::pun> a(&i);  a.min    (&j,sync); }
   { atomic<int*,weak::pun> a(&i);  a.max    (&j,sync); }
   { atomic<int*,weak::pun> a(&i);  a.inc    (  sync); }
   { atomic<int*,weak::pun> a(&i);  a.preinc (  sync); }
   { atomic<int*,weak::pun> a(&i);  a.postinc(  sync); }
   { atomic<int*,weak::pun> a(&i);  a.dec    (  sync); }
   { atomic<int*,weak::pun> a(&i);  a.predec (  sync); }
   { atomic<int*,weak::pun> a(&i);  a.postdec(  sync); }
   { atomic<int*,weak::pun> a(&i);  a.add    (2,success,failure); }
   { atomic<int*,weak::pun> a(&i);  a.sub    (2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  a.mul    (2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  a.div    (2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  a.mod    (2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  a.lshift (2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  a.rshift (2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  a.andeq  (2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  a.oreq   (2,success,failure); }
// { atomic<int*,weak::pun> a(&i);  a.xoreq  (2,success,failure); }
   { atomic<int*,weak::pun> a(&i);  a.min    (&j,success,failure); }
   { atomic<int*,weak::pun> a(&i);  a.max    (&j,success,failure); }
   { atomic<int*,weak::pun> a(&i);  a.inc    (  success,failure); }
   { atomic<int*,weak::pun> a(&i);  a.preinc (  success,failure); }
   { atomic<int*,weak::pun> a(&i);  a.postinc(  success,failure); }
   { atomic<int*,weak::pun> a(&i);  a.dec    (  success,failure); }
   { atomic<int*,weak::pun> a(&i);  a.predec (  success,failure); }
   { atomic<int*,weak::pun> a(&i);  a.postdec(  success,failure); }

   { atomic<int*,lock> a(&i);  a.add    (2); }
   { atomic<int*,lock> a(&i);  a.sub    (2); }
// { atomic<int*,lock> a(&i);  a.mul    (2); }
// { atomic<int*,lock> a(&i);  a.div    (2); }
// { atomic<int*,lock> a(&i);  a.mod    (2); }
// { atomic<int*,lock> a(&i);  a.lshift (2); }
// { atomic<int*,lock> a(&i);  a.rshift (2); }
// { atomic<int*,lock> a(&i);  a.andeq  (2); }
// { atomic<int*,lock> a(&i);  a.oreq   (2); }
// { atomic<int*,lock> a(&i);  a.xoreq  (2); }
   { atomic<int*,lock> a(&i);  a.min    (&j); }
   { atomic<int*,lock> a(&i);  a.max    (&j); }
   { atomic<int*,lock> a(&i);  a.inc    ( ); }
   { atomic<int*,lock> a(&i);  a.preinc ( ); }
   { atomic<int*,lock> a(&i);  a.postinc( ); }
   { atomic<int*,lock> a(&i);  a.dec    ( ); }
   { atomic<int*,lock> a(&i);  a.predec ( ); }
   { atomic<int*,lock> a(&i);  a.postdec( ); }
// { atomic<int*,lock> a(&i);  a.add    (2,sync); }
// { atomic<int*,lock> a(&i);  a.sub    (2,sync); }
// { atomic<int*,lock> a(&i);  a.mul    (2,sync); }
// { atomic<int*,lock> a(&i);  a.div    (2,sync); }
// { atomic<int*,lock> a(&i);  a.mod    (2,sync); }
// { atomic<int*,lock> a(&i);  a.lshift (2,sync); }
// { atomic<int*,lock> a(&i);  a.rshift (2,sync); }
// { atomic<int*,lock> a(&i);  a.andeq  (2,sync); }
// { atomic<int*,lock> a(&i);  a.oreq   (2,sync); }
// { atomic<int*,lock> a(&i);  a.xoreq  (2,sync); }
// { atomic<int*,lock> a(&i);  a.min    (&j,sync); }
// { atomic<int*,lock> a(&i);  a.max    (&j,sync); }
// { atomic<int*,lock> a(&i);  a.inc    (  sync); }
// { atomic<int*,lock> a(&i);  a.preinc (  sync); }
// { atomic<int*,lock> a(&i);  a.postinc(  sync); }
// { atomic<int*,lock> a(&i);  a.dec    (  sync); }
// { atomic<int*,lock> a(&i);  a.predec (  sync); }
// { atomic<int*,lock> a(&i);  a.postdec(  sync); }
// { atomic<int*,lock> a(&i);  a.add    (2,success,failure); }
// { atomic<int*,lock> a(&i);  a.sub    (2,success,failure); }
// { atomic<int*,lock> a(&i);  a.mul    (2,success,failure); }
// { atomic<int*,lock> a(&i);  a.div    (2,success,failure); }
// { atomic<int*,lock> a(&i);  a.mod    (2,success,failure); }
// { atomic<int*,lock> a(&i);  a.lshift (2,success,failure); }
// { atomic<int*,lock> a(&i);  a.rshift (2,success,failure); }
// { atomic<int*,lock> a(&i);  a.andeq  (2,success,failure); }
// { atomic<int*,lock> a(&i);  a.oreq   (2,success,failure); }
// { atomic<int*,lock> a(&i);  a.xoreq  (2,success,failure); }
// { atomic<int*,lock> a(&i);  a.min    (&j,success,failure); }
// { atomic<int*,lock> a(&i);  a.max    (&j,success,failure); }
// { atomic<int*,lock> a(&i);  a.inc    (  success,failure); }
// { atomic<int*,lock> a(&i);  a.preinc (  success,failure); }
// { atomic<int*,lock> a(&i);  a.postinc(  success,failure); }
// { atomic<int*,lock> a(&i);  a.dec    (  success,failure); }
// { atomic<int*,lock> a(&i);  a.predec (  success,failure); }
// { atomic<int*,lock> a(&i);  a.postdec(  success,failure); }

   { atomic<int*,serial> a(&i);  a.add    (2); }
   { atomic<int*,serial> a(&i);  a.sub    (2); }
// { atomic<int*,serial> a(&i);  a.mul    (2); }
// { atomic<int*,serial> a(&i);  a.div    (2); }
// { atomic<int*,serial> a(&i);  a.mod    (2); }
// { atomic<int*,serial> a(&i);  a.lshift (2); }
// { atomic<int*,serial> a(&i);  a.rshift (2); }
// { atomic<int*,serial> a(&i);  a.andeq  (2); }
// { atomic<int*,serial> a(&i);  a.oreq   (2); }
// { atomic<int*,serial> a(&i);  a.xoreq  (2); }
   { atomic<int*,serial> a(&i);  a.min    (&j); }
   { atomic<int*,serial> a(&i);  a.max    (&j); }
   { atomic<int*,serial> a(&i);  a.inc    ( ); }
   { atomic<int*,serial> a(&i);  a.preinc ( ); }
   { atomic<int*,serial> a(&i);  a.postinc( ); }
   { atomic<int*,serial> a(&i);  a.dec    ( ); }
   { atomic<int*,serial> a(&i);  a.predec ( ); }
   { atomic<int*,serial> a(&i);  a.postdec( ); }
// { atomic<int*,serial> a(&i);  a.add    (2,sync); }
// { atomic<int*,serial> a(&i);  a.sub    (2,sync); }
// { atomic<int*,serial> a(&i);  a.mul    (2,sync); }
// { atomic<int*,serial> a(&i);  a.div    (2,sync); }
// { atomic<int*,serial> a(&i);  a.mod    (2,sync); }
// { atomic<int*,serial> a(&i);  a.lshift (2,sync); }
// { atomic<int*,serial> a(&i);  a.rshift (2,sync); }
// { atomic<int*,serial> a(&i);  a.andeq  (2,sync); }
// { atomic<int*,serial> a(&i);  a.oreq   (2,sync); }
// { atomic<int*,serial> a(&i);  a.xoreq  (2,sync); }
// { atomic<int*,serial> a(&i);  a.min    (&j,sync); }
// { atomic<int*,serial> a(&i);  a.max    (&j,sync); }
// { atomic<int*,serial> a(&i);  a.inc    (  sync); }
// { atomic<int*,serial> a(&i);  a.preinc (  sync); }
// { atomic<int*,serial> a(&i);  a.postinc(  sync); }
// { atomic<int*,serial> a(&i);  a.dec    (  sync); }
// { atomic<int*,serial> a(&i);  a.predec (  sync); }
// { atomic<int*,serial> a(&i);  a.postdec(  sync); }
// { atomic<int*,serial> a(&i);  a.add    (2,success,failure); }
// { atomic<int*,serial> a(&i);  a.sub    (2,success,failure); }
// { atomic<int*,serial> a(&i);  a.mul    (2,success,failure); }
// { atomic<int*,serial> a(&i);  a.div    (2,success,failure); }
// { atomic<int*,serial> a(&i);  a.mod    (2,success,failure); }
// { atomic<int*,serial> a(&i);  a.lshift (2,success,failure); }
// { atomic<int*,serial> a(&i);  a.rshift (2,success,failure); }
// { atomic<int*,serial> a(&i);  a.andeq  (2,success,failure); }
// { atomic<int*,serial> a(&i);  a.oreq   (2,success,failure); }
// { atomic<int*,serial> a(&i);  a.xoreq  (2,success,failure); }
// { atomic<int*,serial> a(&i);  a.min    (&j,success,failure); }
// { atomic<int*,serial> a(&i);  a.max    (&j,success,failure); }
// { atomic<int*,serial> a(&i);  a.inc    (  success,failure); }
// { atomic<int*,serial> a(&i);  a.preinc (  success,failure); }
// { atomic<int*,serial> a(&i);  a.postinc(  success,failure); }
// { atomic<int*,serial> a(&i);  a.dec    (  success,failure); }
// { atomic<int*,serial> a(&i);  a.predec (  success,failure); }
// { atomic<int*,serial> a(&i);  a.postdec(  success,failure); }
#endif



   // ------------------------
   // std::complex
   // ------------------------

// { atomic<cmplx,cpp> a(0);  a.add    (c); }
// { atomic<cmplx,cpp> a(0);  a.sub    (c); }
// { atomic<cmplx,cpp> a(0);  a.mul    (c); }
// { atomic<cmplx,cpp> a(0);  a.div    (c); }
// { atomic<cmplx,cpp> a(0);  a.mod    (c); }
// { atomic<cmplx,cpp> a(0);  a.lshift (c); }
// { atomic<cmplx,cpp> a(0);  a.rshift (c); }
// { atomic<cmplx,cpp> a(0);  a.andeq  (c); }
// { atomic<cmplx,cpp> a(0);  a.oreq   (c); }
// { atomic<cmplx,cpp> a(0);  a.xoreq  (c); }
// { atomic<cmplx,cpp> a(0);  a.min    (c); }
// { atomic<cmplx,cpp> a(0);  a.max    (c); }
// { atomic<cmplx,cpp> a(0);  a.inc    ( ); }
// { atomic<cmplx,cpp> a(0);  a.preinc ( ); }
// { atomic<cmplx,cpp> a(0);  a.postinc( ); }
// { atomic<cmplx,cpp> a(0);  a.dec    ( ); }
// { atomic<cmplx,cpp> a(0);  a.predec ( ); }
// { atomic<cmplx,cpp> a(0);  a.postdec( ); }
// { atomic<cmplx,cpp> a(0);  a.add    (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.sub    (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.mul    (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.div    (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.mod    (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.lshift (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.rshift (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.andeq  (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.oreq   (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.xoreq  (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.min    (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.max    (c,sync); }
// { atomic<cmplx,cpp> a(0);  a.inc    (  sync); }
// { atomic<cmplx,cpp> a(0);  a.preinc (  sync); }
// { atomic<cmplx,cpp> a(0);  a.postinc(  sync); }
// { atomic<cmplx,cpp> a(0);  a.dec    (  sync); }
// { atomic<cmplx,cpp> a(0);  a.predec (  sync); }
// { atomic<cmplx,cpp> a(0);  a.postdec(  sync); }
// { atomic<cmplx,cpp> a(0);  a.add    (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.sub    (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.mul    (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.div    (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.mod    (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.lshift (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.rshift (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.andeq  (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.oreq   (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.xoreq  (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.min    (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.max    (c,success,failure); }
// { atomic<cmplx,cpp> a(0);  a.inc    (  success,failure); }
// { atomic<cmplx,cpp> a(0);  a.preinc (  success,failure); }
// { atomic<cmplx,cpp> a(0);  a.postinc(  success,failure); }
// { atomic<cmplx,cpp> a(0);  a.dec    (  success,failure); }
// { atomic<cmplx,cpp> a(0);  a.predec (  success,failure); }
// { atomic<cmplx,cpp> a(0);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { atomic<cmplx,kokkos> a(0);  a.add    (c); }
// { atomic<cmplx,kokkos> a(0);  a.sub    (c); }
// { atomic<cmplx,kokkos> a(0);  a.mul    (c); }
// { atomic<cmplx,kokkos> a(0);  a.div    (c); }
// { atomic<cmplx,kokkos> a(0);  a.mod    (c); }
// { atomic<cmplx,kokkos> a(0);  a.lshift (c); }
// { atomic<cmplx,kokkos> a(0);  a.rshift (c); }
// { atomic<cmplx,kokkos> a(0);  a.andeq  (c); }
// { atomic<cmplx,kokkos> a(0);  a.oreq   (c); }
// { atomic<cmplx,kokkos> a(0);  a.xoreq  (c); }
// { atomic<cmplx,kokkos> a(0);  a.min    (c); }
// { atomic<cmplx,kokkos> a(0);  a.max    (c); }
// { atomic<cmplx,kokkos> a(0);  a.inc    ( ); }
// { atomic<cmplx,kokkos> a(0);  a.preinc ( ); }
// { atomic<cmplx,kokkos> a(0);  a.postinc( ); }
// { atomic<cmplx,kokkos> a(0);  a.dec    ( ); }
// { atomic<cmplx,kokkos> a(0);  a.predec ( ); }
// { atomic<cmplx,kokkos> a(0);  a.postdec( ); }
// { atomic<cmplx,kokkos> a(0);  a.add    (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.sub    (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.mul    (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.div    (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.mod    (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.lshift (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.rshift (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.andeq  (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.oreq   (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.xoreq  (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.min    (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.max    (c,sync); }
// { atomic<cmplx,kokkos> a(0);  a.inc    (  sync); }
// { atomic<cmplx,kokkos> a(0);  a.preinc (  sync); }
// { atomic<cmplx,kokkos> a(0);  a.postinc(  sync); }
// { atomic<cmplx,kokkos> a(0);  a.dec    (  sync); }
// { atomic<cmplx,kokkos> a(0);  a.predec (  sync); }
// { atomic<cmplx,kokkos> a(0);  a.postdec(  sync); }
// { atomic<cmplx,kokkos> a(0);  a.add    (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.sub    (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.mul    (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.div    (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.mod    (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.lshift (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.rshift (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.andeq  (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.oreq   (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.xoreq  (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.min    (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.max    (c,success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.inc    (  success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.preinc (  success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.postinc(  success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.dec    (  success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.predec (  success,failure); }
// { atomic<cmplx,kokkos> a(0);  a.postdec(  success,failure); }
#endif

   { atomic<cmplx,strong> a(0);  a.add    (c); }
   { atomic<cmplx,strong> a(0);  a.sub    (c); }
   { atomic<cmplx,strong> a(0);  a.mul    (c); }
   { atomic<cmplx,strong> a(0);  a.div    (c); }
// { atomic<cmplx,strong> a(0);  a.mod    (c); }
// { atomic<cmplx,strong> a(0);  a.lshift (c); }
// { atomic<cmplx,strong> a(0);  a.rshift (c); }
// { atomic<cmplx,strong> a(0);  a.andeq  (c); }
// { atomic<cmplx,strong> a(0);  a.oreq   (c); }
// { atomic<cmplx,strong> a(0);  a.xoreq  (c); }
// { atomic<cmplx,strong> a(0);  a.min    (c); }
// { atomic<cmplx,strong> a(0);  a.max    (c); }
// { atomic<cmplx,strong> a(0);  a.inc    ( ); }
// { atomic<cmplx,strong> a(0);  a.preinc ( ); }
// { atomic<cmplx,strong> a(0);  a.postinc( ); }
// { atomic<cmplx,strong> a(0);  a.dec    ( ); }
// { atomic<cmplx,strong> a(0);  a.predec ( ); }
// { atomic<cmplx,strong> a(0);  a.postdec( ); }
   { atomic<cmplx,strong> a(0);  a.add    (c,sync); }
   { atomic<cmplx,strong> a(0);  a.sub    (c,sync); }
   { atomic<cmplx,strong> a(0);  a.mul    (c,sync); }
   { atomic<cmplx,strong> a(0);  a.div    (c,sync); }
// { atomic<cmplx,strong> a(0);  a.mod    (c,sync); }
// { atomic<cmplx,strong> a(0);  a.lshift (c,sync); }
// { atomic<cmplx,strong> a(0);  a.rshift (c,sync); }
// { atomic<cmplx,strong> a(0);  a.andeq  (c,sync); }
// { atomic<cmplx,strong> a(0);  a.oreq   (c,sync); }
// { atomic<cmplx,strong> a(0);  a.xoreq  (c,sync); }
// { atomic<cmplx,strong> a(0);  a.min    (c,sync); }
// { atomic<cmplx,strong> a(0);  a.max    (c,sync); }
// { atomic<cmplx,strong> a(0);  a.inc    (  sync); }
// { atomic<cmplx,strong> a(0);  a.preinc (  sync); }
// { atomic<cmplx,strong> a(0);  a.postinc(  sync); }
// { atomic<cmplx,strong> a(0);  a.dec    (  sync); }
// { atomic<cmplx,strong> a(0);  a.predec (  sync); }
// { atomic<cmplx,strong> a(0);  a.postdec(  sync); }
   { atomic<cmplx,strong> a(0);  a.add    (c,success,failure); }
   { atomic<cmplx,strong> a(0);  a.sub    (c,success,failure); }
   { atomic<cmplx,strong> a(0);  a.mul    (c,success,failure); }
   { atomic<cmplx,strong> a(0);  a.div    (c,success,failure); }
// { atomic<cmplx,strong> a(0);  a.mod    (c,success,failure); }
// { atomic<cmplx,strong> a(0);  a.lshift (c,success,failure); }
// { atomic<cmplx,strong> a(0);  a.rshift (c,success,failure); }
// { atomic<cmplx,strong> a(0);  a.andeq  (c,success,failure); }
// { atomic<cmplx,strong> a(0);  a.oreq   (c,success,failure); }
// { atomic<cmplx,strong> a(0);  a.xoreq  (c,success,failure); }
// { atomic<cmplx,strong> a(0);  a.min    (c,success,failure); }
// { atomic<cmplx,strong> a(0);  a.max    (c,success,failure); }
// { atomic<cmplx,strong> a(0);  a.inc    (  success,failure); }
// { atomic<cmplx,strong> a(0);  a.preinc (  success,failure); }
// { atomic<cmplx,strong> a(0);  a.postinc(  success,failure); }
// { atomic<cmplx,strong> a(0);  a.dec    (  success,failure); }
// { atomic<cmplx,strong> a(0);  a.predec (  success,failure); }
// { atomic<cmplx,strong> a(0);  a.postdec(  success,failure); }

   { atomic<cmplx,strong::pun> a(0);  a.add    (c); }
   { atomic<cmplx,strong::pun> a(0);  a.sub    (c); }
   { atomic<cmplx,strong::pun> a(0);  a.mul    (c); }
   { atomic<cmplx,strong::pun> a(0);  a.div    (c); }
// { atomic<cmplx,strong::pun> a(0);  a.mod    (c); }
// { atomic<cmplx,strong::pun> a(0);  a.lshift (c); }
// { atomic<cmplx,strong::pun> a(0);  a.rshift (c); }
// { atomic<cmplx,strong::pun> a(0);  a.andeq  (c); }
// { atomic<cmplx,strong::pun> a(0);  a.oreq   (c); }
// { atomic<cmplx,strong::pun> a(0);  a.xoreq  (c); }
// { atomic<cmplx,strong::pun> a(0);  a.min    (c); }
// { atomic<cmplx,strong::pun> a(0);  a.max    (c); }
// { atomic<cmplx,strong::pun> a(0);  a.inc    ( ); }
// { atomic<cmplx,strong::pun> a(0);  a.preinc ( ); }
// { atomic<cmplx,strong::pun> a(0);  a.postinc( ); }
// { atomic<cmplx,strong::pun> a(0);  a.dec    ( ); }
// { atomic<cmplx,strong::pun> a(0);  a.predec ( ); }
// { atomic<cmplx,strong::pun> a(0);  a.postdec( ); }
   { atomic<cmplx,strong::pun> a(0);  a.add    (c,sync); }
   { atomic<cmplx,strong::pun> a(0);  a.sub    (c,sync); }
   { atomic<cmplx,strong::pun> a(0);  a.mul    (c,sync); }
   { atomic<cmplx,strong::pun> a(0);  a.div    (c,sync); }
// { atomic<cmplx,strong::pun> a(0);  a.mod    (c,sync); }
// { atomic<cmplx,strong::pun> a(0);  a.lshift (c,sync); }
// { atomic<cmplx,strong::pun> a(0);  a.rshift (c,sync); }
// { atomic<cmplx,strong::pun> a(0);  a.andeq  (c,sync); }
// { atomic<cmplx,strong::pun> a(0);  a.oreq   (c,sync); }
// { atomic<cmplx,strong::pun> a(0);  a.xoreq  (c,sync); }
// { atomic<cmplx,strong::pun> a(0);  a.min    (c,sync); }
// { atomic<cmplx,strong::pun> a(0);  a.max    (c,sync); }
// { atomic<cmplx,strong::pun> a(0);  a.inc    (  sync); }
// { atomic<cmplx,strong::pun> a(0);  a.preinc (  sync); }
// { atomic<cmplx,strong::pun> a(0);  a.postinc(  sync); }
// { atomic<cmplx,strong::pun> a(0);  a.dec    (  sync); }
// { atomic<cmplx,strong::pun> a(0);  a.predec (  sync); }
// { atomic<cmplx,strong::pun> a(0);  a.postdec(  sync); }
   { atomic<cmplx,strong::pun> a(0);  a.add    (c,success,failure); }
   { atomic<cmplx,strong::pun> a(0);  a.sub    (c,success,failure); }
   { atomic<cmplx,strong::pun> a(0);  a.mul    (c,success,failure); }
   { atomic<cmplx,strong::pun> a(0);  a.div    (c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.mod    (c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.lshift (c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.rshift (c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.andeq  (c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.oreq   (c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.xoreq  (c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.min    (c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.max    (c,success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.inc    (  success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.preinc (  success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.postinc(  success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.dec    (  success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.predec (  success,failure); }
// { atomic<cmplx,strong::pun> a(0);  a.postdec(  success,failure); }

   { atomic<cmplx,weak> a(0);  a.add    (c); }
   { atomic<cmplx,weak> a(0);  a.sub    (c); }
   { atomic<cmplx,weak> a(0);  a.mul    (c); }
   { atomic<cmplx,weak> a(0);  a.div    (c); }
// { atomic<cmplx,weak> a(0);  a.mod    (c); }
// { atomic<cmplx,weak> a(0);  a.lshift (c); }
// { atomic<cmplx,weak> a(0);  a.rshift (c); }
// { atomic<cmplx,weak> a(0);  a.andeq  (c); }
// { atomic<cmplx,weak> a(0);  a.oreq   (c); }
// { atomic<cmplx,weak> a(0);  a.xoreq  (c); }
// { atomic<cmplx,weak> a(0);  a.min    (c); }
// { atomic<cmplx,weak> a(0);  a.max    (c); }
// { atomic<cmplx,weak> a(0);  a.inc    ( ); }
// { atomic<cmplx,weak> a(0);  a.preinc ( ); }
// { atomic<cmplx,weak> a(0);  a.postinc( ); }
// { atomic<cmplx,weak> a(0);  a.dec    ( ); }
// { atomic<cmplx,weak> a(0);  a.predec ( ); }
// { atomic<cmplx,weak> a(0);  a.postdec( ); }
   { atomic<cmplx,weak> a(0);  a.add    (c,sync); }
   { atomic<cmplx,weak> a(0);  a.sub    (c,sync); }
   { atomic<cmplx,weak> a(0);  a.mul    (c,sync); }
   { atomic<cmplx,weak> a(0);  a.div    (c,sync); }
// { atomic<cmplx,weak> a(0);  a.mod    (c,sync); }
// { atomic<cmplx,weak> a(0);  a.lshift (c,sync); }
// { atomic<cmplx,weak> a(0);  a.rshift (c,sync); }
// { atomic<cmplx,weak> a(0);  a.andeq  (c,sync); }
// { atomic<cmplx,weak> a(0);  a.oreq   (c,sync); }
// { atomic<cmplx,weak> a(0);  a.xoreq  (c,sync); }
// { atomic<cmplx,weak> a(0);  a.min    (c,sync); }
// { atomic<cmplx,weak> a(0);  a.max    (c,sync); }
// { atomic<cmplx,weak> a(0);  a.inc    (  sync); }
// { atomic<cmplx,weak> a(0);  a.preinc (  sync); }
// { atomic<cmplx,weak> a(0);  a.postinc(  sync); }
// { atomic<cmplx,weak> a(0);  a.dec    (  sync); }
// { atomic<cmplx,weak> a(0);  a.predec (  sync); }
// { atomic<cmplx,weak> a(0);  a.postdec(  sync); }
   { atomic<cmplx,weak> a(0);  a.add    (c,success,failure); }
   { atomic<cmplx,weak> a(0);  a.sub    (c,success,failure); }
   { atomic<cmplx,weak> a(0);  a.mul    (c,success,failure); }
   { atomic<cmplx,weak> a(0);  a.div    (c,success,failure); }
// { atomic<cmplx,weak> a(0);  a.mod    (c,success,failure); }
// { atomic<cmplx,weak> a(0);  a.lshift (c,success,failure); }
// { atomic<cmplx,weak> a(0);  a.rshift (c,success,failure); }
// { atomic<cmplx,weak> a(0);  a.andeq  (c,success,failure); }
// { atomic<cmplx,weak> a(0);  a.oreq   (c,success,failure); }
// { atomic<cmplx,weak> a(0);  a.xoreq  (c,success,failure); }
// { atomic<cmplx,weak> a(0);  a.min    (c,success,failure); }
// { atomic<cmplx,weak> a(0);  a.max    (c,success,failure); }
// { atomic<cmplx,weak> a(0);  a.inc    (  success,failure); }
// { atomic<cmplx,weak> a(0);  a.preinc (  success,failure); }
// { atomic<cmplx,weak> a(0);  a.postinc(  success,failure); }
// { atomic<cmplx,weak> a(0);  a.dec    (  success,failure); }
// { atomic<cmplx,weak> a(0);  a.predec (  success,failure); }
// { atomic<cmplx,weak> a(0);  a.postdec(  success,failure); }

   { atomic<cmplx,weak::pun> a(0);  a.add    (c); }
   { atomic<cmplx,weak::pun> a(0);  a.sub    (c); }
   { atomic<cmplx,weak::pun> a(0);  a.mul    (c); }
   { atomic<cmplx,weak::pun> a(0);  a.div    (c); }
// { atomic<cmplx,weak::pun> a(0);  a.mod    (c); }
// { atomic<cmplx,weak::pun> a(0);  a.lshift (c); }
// { atomic<cmplx,weak::pun> a(0);  a.rshift (c); }
// { atomic<cmplx,weak::pun> a(0);  a.andeq  (c); }
// { atomic<cmplx,weak::pun> a(0);  a.oreq   (c); }
// { atomic<cmplx,weak::pun> a(0);  a.xoreq  (c); }
// { atomic<cmplx,weak::pun> a(0);  a.min    (c); }
// { atomic<cmplx,weak::pun> a(0);  a.max    (c); }
// { atomic<cmplx,weak::pun> a(0);  a.inc    ( ); }
// { atomic<cmplx,weak::pun> a(0);  a.preinc ( ); }
// { atomic<cmplx,weak::pun> a(0);  a.postinc( ); }
// { atomic<cmplx,weak::pun> a(0);  a.dec    ( ); }
// { atomic<cmplx,weak::pun> a(0);  a.predec ( ); }
// { atomic<cmplx,weak::pun> a(0);  a.postdec( ); }
   { atomic<cmplx,weak::pun> a(0);  a.add    (c,sync); }
   { atomic<cmplx,weak::pun> a(0);  a.sub    (c,sync); }
   { atomic<cmplx,weak::pun> a(0);  a.mul    (c,sync); }
   { atomic<cmplx,weak::pun> a(0);  a.div    (c,sync); }
// { atomic<cmplx,weak::pun> a(0);  a.mod    (c,sync); }
// { atomic<cmplx,weak::pun> a(0);  a.lshift (c,sync); }
// { atomic<cmplx,weak::pun> a(0);  a.rshift (c,sync); }
// { atomic<cmplx,weak::pun> a(0);  a.andeq  (c,sync); }
// { atomic<cmplx,weak::pun> a(0);  a.oreq   (c,sync); }
// { atomic<cmplx,weak::pun> a(0);  a.xoreq  (c,sync); }
// { atomic<cmplx,weak::pun> a(0);  a.min    (c,sync); }
// { atomic<cmplx,weak::pun> a(0);  a.max    (c,sync); }
// { atomic<cmplx,weak::pun> a(0);  a.inc    (  sync); }
// { atomic<cmplx,weak::pun> a(0);  a.preinc (  sync); }
// { atomic<cmplx,weak::pun> a(0);  a.postinc(  sync); }
// { atomic<cmplx,weak::pun> a(0);  a.dec    (  sync); }
// { atomic<cmplx,weak::pun> a(0);  a.predec (  sync); }
// { atomic<cmplx,weak::pun> a(0);  a.postdec(  sync); }
   { atomic<cmplx,weak::pun> a(0);  a.add    (c,success,failure); }
   { atomic<cmplx,weak::pun> a(0);  a.sub    (c,success,failure); }
   { atomic<cmplx,weak::pun> a(0);  a.mul    (c,success,failure); }
   { atomic<cmplx,weak::pun> a(0);  a.div    (c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.mod    (c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.lshift (c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.rshift (c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.andeq  (c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.oreq   (c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.xoreq  (c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.min    (c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.max    (c,success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.inc    (  success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.preinc (  success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.postinc(  success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.dec    (  success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.predec (  success,failure); }
// { atomic<cmplx,weak::pun> a(0);  a.postdec(  success,failure); }

   { atomic<cmplx,lock> a(0);  a.add    (c); }
   { atomic<cmplx,lock> a(0);  a.sub    (c); }
   { atomic<cmplx,lock> a(0);  a.mul    (c); }
   { atomic<cmplx,lock> a(0);  a.div    (c); }
// { atomic<cmplx,lock> a(0);  a.mod    (c); }
// { atomic<cmplx,lock> a(0);  a.lshift (c); }
// { atomic<cmplx,lock> a(0);  a.rshift (c); }
// { atomic<cmplx,lock> a(0);  a.andeq  (c); }
// { atomic<cmplx,lock> a(0);  a.oreq   (c); }
// { atomic<cmplx,lock> a(0);  a.xoreq  (c); }
// { atomic<cmplx,lock> a(0);  a.min    (c); }
// { atomic<cmplx,lock> a(0);  a.max    (c); }
// { atomic<cmplx,lock> a(0);  a.inc    ( ); }
// { atomic<cmplx,lock> a(0);  a.preinc ( ); }
// { atomic<cmplx,lock> a(0);  a.postinc( ); }
// { atomic<cmplx,lock> a(0);  a.dec    ( ); }
// { atomic<cmplx,lock> a(0);  a.predec ( ); }
// { atomic<cmplx,lock> a(0);  a.postdec( ); }
// { atomic<cmplx,lock> a(0);  a.add    (c,sync); }
// { atomic<cmplx,lock> a(0);  a.sub    (c,sync); }
// { atomic<cmplx,lock> a(0);  a.mul    (c,sync); }
// { atomic<cmplx,lock> a(0);  a.div    (c,sync); }
// { atomic<cmplx,lock> a(0);  a.mod    (c,sync); }
// { atomic<cmplx,lock> a(0);  a.lshift (c,sync); }
// { atomic<cmplx,lock> a(0);  a.rshift (c,sync); }
// { atomic<cmplx,lock> a(0);  a.andeq  (c,sync); }
// { atomic<cmplx,lock> a(0);  a.oreq   (c,sync); }
// { atomic<cmplx,lock> a(0);  a.xoreq  (c,sync); }
// { atomic<cmplx,lock> a(0);  a.min    (c,sync); }
// { atomic<cmplx,lock> a(0);  a.max    (c,sync); }
// { atomic<cmplx,lock> a(0);  a.inc    (  sync); }
// { atomic<cmplx,lock> a(0);  a.preinc (  sync); }
// { atomic<cmplx,lock> a(0);  a.postinc(  sync); }
// { atomic<cmplx,lock> a(0);  a.dec    (  sync); }
// { atomic<cmplx,lock> a(0);  a.predec (  sync); }
// { atomic<cmplx,lock> a(0);  a.postdec(  sync); }
// { atomic<cmplx,lock> a(0);  a.add    (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.sub    (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.mul    (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.div    (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.mod    (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.lshift (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.rshift (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.andeq  (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.oreq   (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.xoreq  (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.min    (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.max    (c,success,failure); }
// { atomic<cmplx,lock> a(0);  a.inc    (  success,failure); }
// { atomic<cmplx,lock> a(0);  a.preinc (  success,failure); }
// { atomic<cmplx,lock> a(0);  a.postinc(  success,failure); }
// { atomic<cmplx,lock> a(0);  a.dec    (  success,failure); }
// { atomic<cmplx,lock> a(0);  a.predec (  success,failure); }
// { atomic<cmplx,lock> a(0);  a.postdec(  success,failure); }

   { atomic<cmplx,serial> a(0);  a.add    (c); }
   { atomic<cmplx,serial> a(0);  a.sub    (c); }
   { atomic<cmplx,serial> a(0);  a.mul    (c); }
   { atomic<cmplx,serial> a(0);  a.div    (c); }
// { atomic<cmplx,serial> a(0);  a.mod    (c); }
// { atomic<cmplx,serial> a(0);  a.lshift (c); }
// { atomic<cmplx,serial> a(0);  a.rshift (c); }
// { atomic<cmplx,serial> a(0);  a.andeq  (c); }
// { atomic<cmplx,serial> a(0);  a.oreq   (c); }
// { atomic<cmplx,serial> a(0);  a.xoreq  (c); }
// { atomic<cmplx,serial> a(0);  a.min    (c); }
// { atomic<cmplx,serial> a(0);  a.max    (c); }
// { atomic<cmplx,serial> a(0);  a.inc    ( ); }
// { atomic<cmplx,serial> a(0);  a.preinc ( ); }
// { atomic<cmplx,serial> a(0);  a.postinc( ); }
// { atomic<cmplx,serial> a(0);  a.dec    ( ); }
// { atomic<cmplx,serial> a(0);  a.predec ( ); }
// { atomic<cmplx,serial> a(0);  a.postdec( ); }
// { atomic<cmplx,serial> a(0);  a.add    (c,sync); }
// { atomic<cmplx,serial> a(0);  a.sub    (c,sync); }
// { atomic<cmplx,serial> a(0);  a.mul    (c,sync); }
// { atomic<cmplx,serial> a(0);  a.div    (c,sync); }
// { atomic<cmplx,serial> a(0);  a.mod    (c,sync); }
// { atomic<cmplx,serial> a(0);  a.lshift (c,sync); }
// { atomic<cmplx,serial> a(0);  a.rshift (c,sync); }
// { atomic<cmplx,serial> a(0);  a.andeq  (c,sync); }
// { atomic<cmplx,serial> a(0);  a.oreq   (c,sync); }
// { atomic<cmplx,serial> a(0);  a.xoreq  (c,sync); }
// { atomic<cmplx,serial> a(0);  a.min    (c,sync); }
// { atomic<cmplx,serial> a(0);  a.max    (c,sync); }
// { atomic<cmplx,serial> a(0);  a.inc    (  sync); }
// { atomic<cmplx,serial> a(0);  a.preinc (  sync); }
// { atomic<cmplx,serial> a(0);  a.postinc(  sync); }
// { atomic<cmplx,serial> a(0);  a.dec    (  sync); }
// { atomic<cmplx,serial> a(0);  a.predec (  sync); }
// { atomic<cmplx,serial> a(0);  a.postdec(  sync); }
// { atomic<cmplx,serial> a(0);  a.add    (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.sub    (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.mul    (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.div    (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.mod    (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.lshift (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.rshift (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.andeq  (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.oreq   (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.xoreq  (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.min    (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.max    (c,success,failure); }
// { atomic<cmplx,serial> a(0);  a.inc    (  success,failure); }
// { atomic<cmplx,serial> a(0);  a.preinc (  success,failure); }
// { atomic<cmplx,serial> a(0);  a.postinc(  success,failure); }
// { atomic<cmplx,serial> a(0);  a.dec    (  success,failure); }
// { atomic<cmplx,serial> a(0);  a.predec (  success,failure); }
// { atomic<cmplx,serial> a(0);  a.postdec(  success,failure); }



   // ------------------------
   // foo
   // ------------------------

// { atomic<foo,cpp> a(0);  a.add    (b); }
// { atomic<foo,cpp> a(0);  a.sub    (b); }
// { atomic<foo,cpp> a(0);  a.mul    (b); }
// { atomic<foo,cpp> a(0);  a.div    (b); }
// { atomic<foo,cpp> a(0);  a.mod    (b); }
// { atomic<foo,cpp> a(0);  a.lshift (b); }
// { atomic<foo,cpp> a(0);  a.rshift (b); }
// { atomic<foo,cpp> a(0);  a.andeq  (b); }
// { atomic<foo,cpp> a(0);  a.oreq   (b); }
// { atomic<foo,cpp> a(0);  a.xoreq  (b); }
// { atomic<foo,cpp> a(0);  a.min    (b); }
// { atomic<foo,cpp> a(0);  a.max    (b); }
// { atomic<foo,cpp> a(0);  a.inc    ( ); }
// { atomic<foo,cpp> a(0);  a.preinc ( ); }
// { atomic<foo,cpp> a(0);  a.postinc( ); }
// { atomic<foo,cpp> a(0);  a.dec    ( ); }
// { atomic<foo,cpp> a(0);  a.predec ( ); }
// { atomic<foo,cpp> a(0);  a.postdec( ); }
// { atomic<foo,cpp> a(0);  a.add    (b,sync); }
// { atomic<foo,cpp> a(0);  a.sub    (b,sync); }
// { atomic<foo,cpp> a(0);  a.mul    (b,sync); }
// { atomic<foo,cpp> a(0);  a.div    (b,sync); }
// { atomic<foo,cpp> a(0);  a.mod    (b,sync); }
// { atomic<foo,cpp> a(0);  a.lshift (b,sync); }
// { atomic<foo,cpp> a(0);  a.rshift (b,sync); }
// { atomic<foo,cpp> a(0);  a.andeq  (b,sync); }
// { atomic<foo,cpp> a(0);  a.oreq   (b,sync); }
// { atomic<foo,cpp> a(0);  a.xoreq  (b,sync); }
// { atomic<foo,cpp> a(0);  a.min    (b,sync); }
// { atomic<foo,cpp> a(0);  a.max    (b,sync); }
// { atomic<foo,cpp> a(0);  a.inc    (  sync); }
// { atomic<foo,cpp> a(0);  a.preinc (  sync); }
// { atomic<foo,cpp> a(0);  a.postinc(  sync); }
// { atomic<foo,cpp> a(0);  a.dec    (  sync); }
// { atomic<foo,cpp> a(0);  a.predec (  sync); }
// { atomic<foo,cpp> a(0);  a.postdec(  sync); }
// { atomic<foo,cpp> a(0);  a.add    (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.sub    (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.mul    (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.div    (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.mod    (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.lshift (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.rshift (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.andeq  (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.oreq   (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.xoreq  (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.min    (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.max    (b,success,failure); }
// { atomic<foo,cpp> a(0);  a.inc    (  success,failure); }
// { atomic<foo,cpp> a(0);  a.preinc (  success,failure); }
// { atomic<foo,cpp> a(0);  a.postinc(  success,failure); }
// { atomic<foo,cpp> a(0);  a.dec    (  success,failure); }
// { atomic<foo,cpp> a(0);  a.predec (  success,failure); }
// { atomic<foo,cpp> a(0);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { atomic<foo,kokkos> a(0);  a.add    (b); }
// { atomic<foo,kokkos> a(0);  a.sub    (b); }
// { atomic<foo,kokkos> a(0);  a.mul    (b); }
// { atomic<foo,kokkos> a(0);  a.div    (b); }
// { atomic<foo,kokkos> a(0);  a.mod    (b); }
// { atomic<foo,kokkos> a(0);  a.lshift (b); }
// { atomic<foo,kokkos> a(0);  a.rshift (b); }
// { atomic<foo,kokkos> a(0);  a.andeq  (b); }
// { atomic<foo,kokkos> a(0);  a.oreq   (b); }
// { atomic<foo,kokkos> a(0);  a.xoreq  (b); }
// { atomic<foo,kokkos> a(0);  a.min    (b); }
// { atomic<foo,kokkos> a(0);  a.max    (b); }
// { atomic<foo,kokkos> a(0);  a.inc    ( ); }
// { atomic<foo,kokkos> a(0);  a.preinc ( ); }
// { atomic<foo,kokkos> a(0);  a.postinc( ); }
// { atomic<foo,kokkos> a(0);  a.dec    ( ); }
// { atomic<foo,kokkos> a(0);  a.predec ( ); }
// { atomic<foo,kokkos> a(0);  a.postdec( ); }
// { atomic<foo,kokkos> a(0);  a.add    (b,sync); }
// { atomic<foo,kokkos> a(0);  a.sub    (b,sync); }
// { atomic<foo,kokkos> a(0);  a.mul    (b,sync); }
// { atomic<foo,kokkos> a(0);  a.div    (b,sync); }
// { atomic<foo,kokkos> a(0);  a.mod    (b,sync); }
// { atomic<foo,kokkos> a(0);  a.lshift (b,sync); }
// { atomic<foo,kokkos> a(0);  a.rshift (b,sync); }
// { atomic<foo,kokkos> a(0);  a.andeq  (b,sync); }
// { atomic<foo,kokkos> a(0);  a.oreq   (b,sync); }
// { atomic<foo,kokkos> a(0);  a.xoreq  (b,sync); }
// { atomic<foo,kokkos> a(0);  a.min    (b,sync); }
// { atomic<foo,kokkos> a(0);  a.max    (b,sync); }
// { atomic<foo,kokkos> a(0);  a.inc    (  sync); }
// { atomic<foo,kokkos> a(0);  a.preinc (  sync); }
// { atomic<foo,kokkos> a(0);  a.postinc(  sync); }
// { atomic<foo,kokkos> a(0);  a.dec    (  sync); }
// { atomic<foo,kokkos> a(0);  a.predec (  sync); }
// { atomic<foo,kokkos> a(0);  a.postdec(  sync); }
// { atomic<foo,kokkos> a(0);  a.add    (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.sub    (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.mul    (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.div    (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.mod    (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.lshift (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.rshift (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.andeq  (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.oreq   (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.xoreq  (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.min    (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.max    (b,success,failure); }
// { atomic<foo,kokkos> a(0);  a.inc    (  success,failure); }
// { atomic<foo,kokkos> a(0);  a.preinc (  success,failure); }
// { atomic<foo,kokkos> a(0);  a.postinc(  success,failure); }
// { atomic<foo,kokkos> a(0);  a.dec    (  success,failure); }
// { atomic<foo,kokkos> a(0);  a.predec (  success,failure); }
// { atomic<foo,kokkos> a(0);  a.postdec(  success,failure); }
#endif

   { atomic<foo,strong> a(0);  a.add    (b); }
   { atomic<foo,strong> a(0);  a.sub    (b); }
   { atomic<foo,strong> a(0);  a.mul    (b); }
   { atomic<foo,strong> a(0);  a.div    (b); }
   { atomic<foo,strong> a(0);  a.mod    (b); }
   { atomic<foo,strong> a(0);  a.lshift (b); }
   { atomic<foo,strong> a(0);  a.rshift (b); }
   { atomic<foo,strong> a(0);  a.andeq  (b); }
   { atomic<foo,strong> a(0);  a.oreq   (b); }
   { atomic<foo,strong> a(0);  a.xoreq  (b); }
   { atomic<foo,strong> a(0);  a.min    (b); }
   { atomic<foo,strong> a(0);  a.max    (b); }
   { atomic<foo,strong> a(0);  a.inc    ( ); }
   { atomic<foo,strong> a(0);  a.preinc ( ); }
   { atomic<foo,strong> a(0);  a.postinc( ); }
   { atomic<foo,strong> a(0);  a.dec    ( ); }
   { atomic<foo,strong> a(0);  a.predec ( ); }
   { atomic<foo,strong> a(0);  a.postdec( ); }
   { atomic<foo,strong> a(0);  a.add    (b,sync); }
   { atomic<foo,strong> a(0);  a.sub    (b,sync); }
   { atomic<foo,strong> a(0);  a.mul    (b,sync); }
   { atomic<foo,strong> a(0);  a.div    (b,sync); }
   { atomic<foo,strong> a(0);  a.mod    (b,sync); }
   { atomic<foo,strong> a(0);  a.lshift (b,sync); }
   { atomic<foo,strong> a(0);  a.rshift (b,sync); }
   { atomic<foo,strong> a(0);  a.andeq  (b,sync); }
   { atomic<foo,strong> a(0);  a.oreq   (b,sync); }
   { atomic<foo,strong> a(0);  a.xoreq  (b,sync); }
   { atomic<foo,strong> a(0);  a.min    (b,sync); }
   { atomic<foo,strong> a(0);  a.max    (b,sync); }
   { atomic<foo,strong> a(0);  a.inc    (  sync); }
   { atomic<foo,strong> a(0);  a.preinc (  sync); }
   { atomic<foo,strong> a(0);  a.postinc(  sync); }
   { atomic<foo,strong> a(0);  a.dec    (  sync); }
   { atomic<foo,strong> a(0);  a.predec (  sync); }
   { atomic<foo,strong> a(0);  a.postdec(  sync); }
   { atomic<foo,strong> a(0);  a.add    (b,success,failure); }
   { atomic<foo,strong> a(0);  a.sub    (b,success,failure); }
   { atomic<foo,strong> a(0);  a.mul    (b,success,failure); }
   { atomic<foo,strong> a(0);  a.div    (b,success,failure); }
   { atomic<foo,strong> a(0);  a.mod    (b,success,failure); }
   { atomic<foo,strong> a(0);  a.lshift (b,success,failure); }
   { atomic<foo,strong> a(0);  a.rshift (b,success,failure); }
   { atomic<foo,strong> a(0);  a.andeq  (b,success,failure); }
   { atomic<foo,strong> a(0);  a.oreq   (b,success,failure); }
   { atomic<foo,strong> a(0);  a.xoreq  (b,success,failure); }
   { atomic<foo,strong> a(0);  a.min    (b,success,failure); }
   { atomic<foo,strong> a(0);  a.max    (b,success,failure); }
   { atomic<foo,strong> a(0);  a.inc    (  success,failure); }
   { atomic<foo,strong> a(0);  a.preinc (  success,failure); }
   { atomic<foo,strong> a(0);  a.postinc(  success,failure); }
   { atomic<foo,strong> a(0);  a.dec    (  success,failure); }
   { atomic<foo,strong> a(0);  a.predec (  success,failure); }
   { atomic<foo,strong> a(0);  a.postdec(  success,failure); }

   { atomic<foo,strong::pun> a(0);  a.add    (b); }
   { atomic<foo,strong::pun> a(0);  a.sub    (b); }
   { atomic<foo,strong::pun> a(0);  a.mul    (b); }
   { atomic<foo,strong::pun> a(0);  a.div    (b); }
   { atomic<foo,strong::pun> a(0);  a.mod    (b); }
   { atomic<foo,strong::pun> a(0);  a.lshift (b); }
   { atomic<foo,strong::pun> a(0);  a.rshift (b); }
   { atomic<foo,strong::pun> a(0);  a.andeq  (b); }
   { atomic<foo,strong::pun> a(0);  a.oreq   (b); }
   { atomic<foo,strong::pun> a(0);  a.xoreq  (b); }
   { atomic<foo,strong::pun> a(0);  a.min    (b); }
   { atomic<foo,strong::pun> a(0);  a.max    (b); }
   { atomic<foo,strong::pun> a(0);  a.inc    ( ); }
   { atomic<foo,strong::pun> a(0);  a.preinc ( ); }
   { atomic<foo,strong::pun> a(0);  a.postinc( ); }
   { atomic<foo,strong::pun> a(0);  a.dec    ( ); }
   { atomic<foo,strong::pun> a(0);  a.predec ( ); }
   { atomic<foo,strong::pun> a(0);  a.postdec( ); }
   { atomic<foo,strong::pun> a(0);  a.add    (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.sub    (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.mul    (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.div    (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.mod    (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.lshift (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.rshift (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.andeq  (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.oreq   (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.xoreq  (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.min    (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.max    (b,sync); }
   { atomic<foo,strong::pun> a(0);  a.inc    (  sync); }
   { atomic<foo,strong::pun> a(0);  a.preinc (  sync); }
   { atomic<foo,strong::pun> a(0);  a.postinc(  sync); }
   { atomic<foo,strong::pun> a(0);  a.dec    (  sync); }
   { atomic<foo,strong::pun> a(0);  a.predec (  sync); }
   { atomic<foo,strong::pun> a(0);  a.postdec(  sync); }
   { atomic<foo,strong::pun> a(0);  a.add    (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.sub    (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.mul    (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.div    (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.mod    (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.lshift (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.rshift (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.andeq  (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.oreq   (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.xoreq  (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.min    (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.max    (b,success,failure); }
   { atomic<foo,strong::pun> a(0);  a.inc    (  success,failure); }
   { atomic<foo,strong::pun> a(0);  a.preinc (  success,failure); }
   { atomic<foo,strong::pun> a(0);  a.postinc(  success,failure); }
   { atomic<foo,strong::pun> a(0);  a.dec    (  success,failure); }
   { atomic<foo,strong::pun> a(0);  a.predec (  success,failure); }
   { atomic<foo,strong::pun> a(0);  a.postdec(  success,failure); }

   { atomic<foo,weak> a(0);  a.add    (b); }
   { atomic<foo,weak> a(0);  a.sub    (b); }
   { atomic<foo,weak> a(0);  a.mul    (b); }
   { atomic<foo,weak> a(0);  a.div    (b); }
   { atomic<foo,weak> a(0);  a.mod    (b); }
   { atomic<foo,weak> a(0);  a.lshift (b); }
   { atomic<foo,weak> a(0);  a.rshift (b); }
   { atomic<foo,weak> a(0);  a.andeq  (b); }
   { atomic<foo,weak> a(0);  a.oreq   (b); }
   { atomic<foo,weak> a(0);  a.xoreq  (b); }
   { atomic<foo,weak> a(0);  a.min    (b); }
   { atomic<foo,weak> a(0);  a.max    (b); }
   { atomic<foo,weak> a(0);  a.inc    ( ); }
   { atomic<foo,weak> a(0);  a.preinc ( ); }
   { atomic<foo,weak> a(0);  a.postinc( ); }
   { atomic<foo,weak> a(0);  a.dec    ( ); }
   { atomic<foo,weak> a(0);  a.predec ( ); }
   { atomic<foo,weak> a(0);  a.postdec( ); }
   { atomic<foo,weak> a(0);  a.add    (b,sync); }
   { atomic<foo,weak> a(0);  a.sub    (b,sync); }
   { atomic<foo,weak> a(0);  a.mul    (b,sync); }
   { atomic<foo,weak> a(0);  a.div    (b,sync); }
   { atomic<foo,weak> a(0);  a.mod    (b,sync); }
   { atomic<foo,weak> a(0);  a.lshift (b,sync); }
   { atomic<foo,weak> a(0);  a.rshift (b,sync); }
   { atomic<foo,weak> a(0);  a.andeq  (b,sync); }
   { atomic<foo,weak> a(0);  a.oreq   (b,sync); }
   { atomic<foo,weak> a(0);  a.xoreq  (b,sync); }
   { atomic<foo,weak> a(0);  a.min    (b,sync); }
   { atomic<foo,weak> a(0);  a.max    (b,sync); }
   { atomic<foo,weak> a(0);  a.inc    (  sync); }
   { atomic<foo,weak> a(0);  a.preinc (  sync); }
   { atomic<foo,weak> a(0);  a.postinc(  sync); }
   { atomic<foo,weak> a(0);  a.dec    (  sync); }
   { atomic<foo,weak> a(0);  a.predec (  sync); }
   { atomic<foo,weak> a(0);  a.postdec(  sync); }
   { atomic<foo,weak> a(0);  a.add    (b,success,failure); }
   { atomic<foo,weak> a(0);  a.sub    (b,success,failure); }
   { atomic<foo,weak> a(0);  a.mul    (b,success,failure); }
   { atomic<foo,weak> a(0);  a.div    (b,success,failure); }
   { atomic<foo,weak> a(0);  a.mod    (b,success,failure); }
   { atomic<foo,weak> a(0);  a.lshift (b,success,failure); }
   { atomic<foo,weak> a(0);  a.rshift (b,success,failure); }
   { atomic<foo,weak> a(0);  a.andeq  (b,success,failure); }
   { atomic<foo,weak> a(0);  a.oreq   (b,success,failure); }
   { atomic<foo,weak> a(0);  a.xoreq  (b,success,failure); }
   { atomic<foo,weak> a(0);  a.min    (b,success,failure); }
   { atomic<foo,weak> a(0);  a.max    (b,success,failure); }
   { atomic<foo,weak> a(0);  a.inc    (  success,failure); }
   { atomic<foo,weak> a(0);  a.preinc (  success,failure); }
   { atomic<foo,weak> a(0);  a.postinc(  success,failure); }
   { atomic<foo,weak> a(0);  a.dec    (  success,failure); }
   { atomic<foo,weak> a(0);  a.predec (  success,failure); }
   { atomic<foo,weak> a(0);  a.postdec(  success,failure); }

   { atomic<foo,weak::pun> a(0);  a.add    (b); }
   { atomic<foo,weak::pun> a(0);  a.sub    (b); }
   { atomic<foo,weak::pun> a(0);  a.mul    (b); }
   { atomic<foo,weak::pun> a(0);  a.div    (b); }
   { atomic<foo,weak::pun> a(0);  a.mod    (b); }
   { atomic<foo,weak::pun> a(0);  a.lshift (b); }
   { atomic<foo,weak::pun> a(0);  a.rshift (b); }
   { atomic<foo,weak::pun> a(0);  a.andeq  (b); }
   { atomic<foo,weak::pun> a(0);  a.oreq   (b); }
   { atomic<foo,weak::pun> a(0);  a.xoreq  (b); }
   { atomic<foo,weak::pun> a(0);  a.min    (b); }
   { atomic<foo,weak::pun> a(0);  a.max    (b); }
   { atomic<foo,weak::pun> a(0);  a.inc    ( ); }
   { atomic<foo,weak::pun> a(0);  a.preinc ( ); }
   { atomic<foo,weak::pun> a(0);  a.postinc( ); }
   { atomic<foo,weak::pun> a(0);  a.dec    ( ); }
   { atomic<foo,weak::pun> a(0);  a.predec ( ); }
   { atomic<foo,weak::pun> a(0);  a.postdec( ); }
   { atomic<foo,weak::pun> a(0);  a.add    (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.sub    (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.mul    (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.div    (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.mod    (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.lshift (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.rshift (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.andeq  (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.oreq   (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.xoreq  (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.min    (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.max    (b,sync); }
   { atomic<foo,weak::pun> a(0);  a.inc    (  sync); }
   { atomic<foo,weak::pun> a(0);  a.preinc (  sync); }
   { atomic<foo,weak::pun> a(0);  a.postinc(  sync); }
   { atomic<foo,weak::pun> a(0);  a.dec    (  sync); }
   { atomic<foo,weak::pun> a(0);  a.predec (  sync); }
   { atomic<foo,weak::pun> a(0);  a.postdec(  sync); }
   { atomic<foo,weak::pun> a(0);  a.add    (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.sub    (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.mul    (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.div    (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.mod    (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.lshift (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.rshift (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.andeq  (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.oreq   (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.xoreq  (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.min    (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.max    (b,success,failure); }
   { atomic<foo,weak::pun> a(0);  a.inc    (  success,failure); }
   { atomic<foo,weak::pun> a(0);  a.preinc (  success,failure); }
   { atomic<foo,weak::pun> a(0);  a.postinc(  success,failure); }
   { atomic<foo,weak::pun> a(0);  a.dec    (  success,failure); }
   { atomic<foo,weak::pun> a(0);  a.predec (  success,failure); }
   { atomic<foo,weak::pun> a(0);  a.postdec(  success,failure); }

   { atomic<foo,lock> a(0);  a.add    (b); }
   { atomic<foo,lock> a(0);  a.sub    (b); }
   { atomic<foo,lock> a(0);  a.mul    (b); }
   { atomic<foo,lock> a(0);  a.div    (b); }
   { atomic<foo,lock> a(0);  a.mod    (b); }
   { atomic<foo,lock> a(0);  a.lshift (b); }
   { atomic<foo,lock> a(0);  a.rshift (b); }
   { atomic<foo,lock> a(0);  a.andeq  (b); }
   { atomic<foo,lock> a(0);  a.oreq   (b); }
   { atomic<foo,lock> a(0);  a.xoreq  (b); }
   { atomic<foo,lock> a(0);  a.min    (b); }
   { atomic<foo,lock> a(0);  a.max    (b); }
   { atomic<foo,lock> a(0);  a.inc    ( ); }
   { atomic<foo,lock> a(0);  a.preinc ( ); }
   { atomic<foo,lock> a(0);  a.postinc( ); }
   { atomic<foo,lock> a(0);  a.dec    ( ); }
   { atomic<foo,lock> a(0);  a.predec ( ); }
   { atomic<foo,lock> a(0);  a.postdec( ); }
// { atomic<foo,lock> a(0);  a.add    (b,sync); }
// { atomic<foo,lock> a(0);  a.sub    (b,sync); }
// { atomic<foo,lock> a(0);  a.mul    (b,sync); }
// { atomic<foo,lock> a(0);  a.div    (b,sync); }
// { atomic<foo,lock> a(0);  a.mod    (b,sync); }
// { atomic<foo,lock> a(0);  a.lshift (b,sync); }
// { atomic<foo,lock> a(0);  a.rshift (b,sync); }
// { atomic<foo,lock> a(0);  a.andeq  (b,sync); }
// { atomic<foo,lock> a(0);  a.oreq   (b,sync); }
// { atomic<foo,lock> a(0);  a.xoreq  (b,sync); }
// { atomic<foo,lock> a(0);  a.min    (b,sync); }
// { atomic<foo,lock> a(0);  a.max    (b,sync); }
// { atomic<foo,lock> a(0);  a.inc    (  sync); }
// { atomic<foo,lock> a(0);  a.preinc (  sync); }
// { atomic<foo,lock> a(0);  a.postinc(  sync); }
// { atomic<foo,lock> a(0);  a.dec    (  sync); }
// { atomic<foo,lock> a(0);  a.predec (  sync); }
// { atomic<foo,lock> a(0);  a.postdec(  sync); }
// { atomic<foo,lock> a(0);  a.add    (b,success,failure); }
// { atomic<foo,lock> a(0);  a.sub    (b,success,failure); }
// { atomic<foo,lock> a(0);  a.mul    (b,success,failure); }
// { atomic<foo,lock> a(0);  a.div    (b,success,failure); }
// { atomic<foo,lock> a(0);  a.mod    (b,success,failure); }
// { atomic<foo,lock> a(0);  a.lshift (b,success,failure); }
// { atomic<foo,lock> a(0);  a.rshift (b,success,failure); }
// { atomic<foo,lock> a(0);  a.andeq  (b,success,failure); }
// { atomic<foo,lock> a(0);  a.oreq   (b,success,failure); }
// { atomic<foo,lock> a(0);  a.xoreq  (b,success,failure); }
// { atomic<foo,lock> a(0);  a.min    (b,success,failure); }
// { atomic<foo,lock> a(0);  a.max    (b,success,failure); }
// { atomic<foo,lock> a(0);  a.inc    (  success,failure); }
// { atomic<foo,lock> a(0);  a.preinc (  success,failure); }
// { atomic<foo,lock> a(0);  a.postinc(  success,failure); }
// { atomic<foo,lock> a(0);  a.dec    (  success,failure); }
// { atomic<foo,lock> a(0);  a.predec (  success,failure); }
// { atomic<foo,lock> a(0);  a.postdec(  success,failure); }

   { atomic<foo,serial> a(0);  a.add    (b); }
   { atomic<foo,serial> a(0);  a.sub    (b); }
   { atomic<foo,serial> a(0);  a.mul    (b); }
   { atomic<foo,serial> a(0);  a.div    (b); }
   { atomic<foo,serial> a(0);  a.mod    (b); }
   { atomic<foo,serial> a(0);  a.lshift (b); }
   { atomic<foo,serial> a(0);  a.rshift (b); }
   { atomic<foo,serial> a(0);  a.andeq  (b); }
   { atomic<foo,serial> a(0);  a.oreq   (b); }
   { atomic<foo,serial> a(0);  a.xoreq  (b); }
   { atomic<foo,serial> a(0);  a.min    (b); }
   { atomic<foo,serial> a(0);  a.max    (b); }
   { atomic<foo,serial> a(0);  a.inc    ( ); }
   { atomic<foo,serial> a(0);  a.preinc ( ); }
   { atomic<foo,serial> a(0);  a.postinc( ); }
   { atomic<foo,serial> a(0);  a.dec    ( ); }
   { atomic<foo,serial> a(0);  a.predec ( ); }
   { atomic<foo,serial> a(0);  a.postdec( ); }
// { atomic<foo,serial> a(0);  a.add    (b,sync); }
// { atomic<foo,serial> a(0);  a.sub    (b,sync); }
// { atomic<foo,serial> a(0);  a.mul    (b,sync); }
// { atomic<foo,serial> a(0);  a.div    (b,sync); }
// { atomic<foo,serial> a(0);  a.mod    (b,sync); }
// { atomic<foo,serial> a(0);  a.lshift (b,sync); }
// { atomic<foo,serial> a(0);  a.rshift (b,sync); }
// { atomic<foo,serial> a(0);  a.andeq  (b,sync); }
// { atomic<foo,serial> a(0);  a.oreq   (b,sync); }
// { atomic<foo,serial> a(0);  a.xoreq  (b,sync); }
// { atomic<foo,serial> a(0);  a.min    (b,sync); }
// { atomic<foo,serial> a(0);  a.max    (b,sync); }
// { atomic<foo,serial> a(0);  a.inc    (  sync); }
// { atomic<foo,serial> a(0);  a.preinc (  sync); }
// { atomic<foo,serial> a(0);  a.postinc(  sync); }
// { atomic<foo,serial> a(0);  a.dec    (  sync); }
// { atomic<foo,serial> a(0);  a.predec (  sync); }
// { atomic<foo,serial> a(0);  a.postdec(  sync); }
// { atomic<foo,serial> a(0);  a.add    (b,success,failure); }
// { atomic<foo,serial> a(0);  a.sub    (b,success,failure); }
// { atomic<foo,serial> a(0);  a.mul    (b,success,failure); }
// { atomic<foo,serial> a(0);  a.div    (b,success,failure); }
// { atomic<foo,serial> a(0);  a.mod    (b,success,failure); }
// { atomic<foo,serial> a(0);  a.lshift (b,success,failure); }
// { atomic<foo,serial> a(0);  a.rshift (b,success,failure); }
// { atomic<foo,serial> a(0);  a.andeq  (b,success,failure); }
// { atomic<foo,serial> a(0);  a.oreq   (b,success,failure); }
// { atomic<foo,serial> a(0);  a.xoreq  (b,success,failure); }
// { atomic<foo,serial> a(0);  a.min    (b,success,failure); }
// { atomic<foo,serial> a(0);  a.max    (b,success,failure); }
// { atomic<foo,serial> a(0);  a.inc    (  success,failure); }
// { atomic<foo,serial> a(0);  a.preinc (  success,failure); }
// { atomic<foo,serial> a(0);  a.postinc(  success,failure); }
// { atomic<foo,serial> a(0);  a.dec    (  success,failure); }
// { atomic<foo,serial> a(0);  a.predec (  success,failure); }
// { atomic<foo,serial> a(0);  a.postdec(  success,failure); }



   // --------------------------------------------------------------------------
   // volatile
   // --------------------------------------------------------------------------

   // ------------------------
   // int
   // ------------------------

   { volatile atomic<int,cpp> a(0);  a.add    (2); }
   { volatile atomic<int,cpp> a(0);  a.sub    (2); }
// { volatile atomic<int,cpp> a(0);  a.mul    (2); }
// { volatile atomic<int,cpp> a(0);  a.div    (2); }
// { volatile atomic<int,cpp> a(0);  a.mod    (2); }
// { volatile atomic<int,cpp> a(0);  a.lshift (2); }
// { volatile atomic<int,cpp> a(0);  a.rshift (2); }
   { volatile atomic<int,cpp> a(0);  a.andeq  (2); }
   { volatile atomic<int,cpp> a(0);  a.oreq   (2); }
   { volatile atomic<int,cpp> a(0);  a.xoreq  (2); }
// { volatile atomic<int,cpp> a(0);  a.min    (2); }
// { volatile atomic<int,cpp> a(0);  a.max    (2); }
   { volatile atomic<int,cpp> a(0);  a.inc    ( ); }
   { volatile atomic<int,cpp> a(0);  a.preinc ( ); }
   { volatile atomic<int,cpp> a(0);  a.postinc( ); }
   { volatile atomic<int,cpp> a(0);  a.dec    ( ); }
   { volatile atomic<int,cpp> a(0);  a.predec ( ); }
   { volatile atomic<int,cpp> a(0);  a.postdec( ); }
   { volatile atomic<int,cpp> a(0);  a.add    (2,sync); }
   { volatile atomic<int,cpp> a(0);  a.sub    (2,sync); }
// { volatile atomic<int,cpp> a(0);  a.mul    (2,sync); }
// { volatile atomic<int,cpp> a(0);  a.div    (2,sync); }
// { volatile atomic<int,cpp> a(0);  a.mod    (2,sync); }
// { volatile atomic<int,cpp> a(0);  a.lshift (2,sync); }
// { volatile atomic<int,cpp> a(0);  a.rshift (2,sync); }
   { volatile atomic<int,cpp> a(0);  a.andeq  (2,sync); }
   { volatile atomic<int,cpp> a(0);  a.oreq   (2,sync); }
   { volatile atomic<int,cpp> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<int,cpp> a(0);  a.min    (2,sync); }
// { volatile atomic<int,cpp> a(0);  a.max    (2,sync); }
// { volatile atomic<int,cpp> a(0);  a.inc    (  sync); }
// { volatile atomic<int,cpp> a(0);  a.preinc (  sync); }
// { volatile atomic<int,cpp> a(0);  a.postinc(  sync); }
// { volatile atomic<int,cpp> a(0);  a.dec    (  sync); }
// { volatile atomic<int,cpp> a(0);  a.predec (  sync); }
// { volatile atomic<int,cpp> a(0);  a.postdec(  sync); }
// { volatile atomic<int,cpp> a(0);  a.add    (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.div    (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.min    (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.max    (2,success,failure); }
// { volatile atomic<int,cpp> a(0);  a.inc    (  success,failure); }
// { volatile atomic<int,cpp> a(0);  a.preinc (  success,failure); }
// { volatile atomic<int,cpp> a(0);  a.postinc(  success,failure); }
// { volatile atomic<int,cpp> a(0);  a.dec    (  success,failure); }
// { volatile atomic<int,cpp> a(0);  a.predec (  success,failure); }
// { volatile atomic<int,cpp> a(0);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { volatile atomic<int,kokkos> a(0);  a.add    (2); }
   { volatile atomic<int,kokkos> a(0);  a.sub    (2); }
   { volatile atomic<int,kokkos> a(0);  a.mul    (2); }
   { volatile atomic<int,kokkos> a(0);  a.div    (2); }
   { volatile atomic<int,kokkos> a(0);  a.mod    (2); }
   { volatile atomic<int,kokkos> a(0);  a.lshift (2); }
   { volatile atomic<int,kokkos> a(0);  a.rshift (2); }
   { volatile atomic<int,kokkos> a(0);  a.andeq  (2); }
   { volatile atomic<int,kokkos> a(0);  a.oreq   (2); }
   { volatile atomic<int,kokkos> a(0);  a.xoreq  (2); }
   { volatile atomic<int,kokkos> a(0);  a.min    (2); }
   { volatile atomic<int,kokkos> a(0);  a.max    (2); }
   { volatile atomic<int,kokkos> a(0);  a.inc    ( ); }
   { volatile atomic<int,kokkos> a(0);  a.preinc ( ); }
   { volatile atomic<int,kokkos> a(0);  a.postinc( ); }
   { volatile atomic<int,kokkos> a(0);  a.dec    ( ); }
   { volatile atomic<int,kokkos> a(0);  a.predec ( ); }
   { volatile atomic<int,kokkos> a(0);  a.postdec( ); }
// { volatile atomic<int,kokkos> a(0);  a.add    (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.sub    (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.mul    (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.div    (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.mod    (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.lshift (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.rshift (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.andeq  (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.oreq   (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.min    (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.max    (2,sync); }
// { volatile atomic<int,kokkos> a(0);  a.inc    (  sync); }
// { volatile atomic<int,kokkos> a(0);  a.preinc (  sync); }
// { volatile atomic<int,kokkos> a(0);  a.postinc(  sync); }
// { volatile atomic<int,kokkos> a(0);  a.dec    (  sync); }
// { volatile atomic<int,kokkos> a(0);  a.predec (  sync); }
// { volatile atomic<int,kokkos> a(0);  a.postdec(  sync); }
// { volatile atomic<int,kokkos> a(0);  a.add    (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.div    (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.min    (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.max    (2,success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.inc    (  success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.preinc (  success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.postinc(  success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.dec    (  success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.predec (  success,failure); }
// { volatile atomic<int,kokkos> a(0);  a.postdec(  success,failure); }
#endif

   { volatile atomic<int,strong> a(0);  a.add    (2); }
   { volatile atomic<int,strong> a(0);  a.sub    (2); }
   { volatile atomic<int,strong> a(0);  a.mul    (2); }
   { volatile atomic<int,strong> a(0);  a.div    (2); }
   { volatile atomic<int,strong> a(0);  a.mod    (2); }
   { volatile atomic<int,strong> a(0);  a.lshift (2); }
   { volatile atomic<int,strong> a(0);  a.rshift (2); }
   { volatile atomic<int,strong> a(0);  a.andeq  (2); }
   { volatile atomic<int,strong> a(0);  a.oreq   (2); }
   { volatile atomic<int,strong> a(0);  a.xoreq  (2); }
   { volatile atomic<int,strong> a(0);  a.min    (2); }
   { volatile atomic<int,strong> a(0);  a.max    (2); }
   { volatile atomic<int,strong> a(0);  a.inc    ( ); }
   { volatile atomic<int,strong> a(0);  a.preinc ( ); }
   { volatile atomic<int,strong> a(0);  a.postinc( ); }
   { volatile atomic<int,strong> a(0);  a.dec    ( ); }
   { volatile atomic<int,strong> a(0);  a.predec ( ); }
   { volatile atomic<int,strong> a(0);  a.postdec( ); }
   { volatile atomic<int,strong> a(0);  a.add    (2,sync); }
   { volatile atomic<int,strong> a(0);  a.sub    (2,sync); }
   { volatile atomic<int,strong> a(0);  a.mul    (2,sync); }
   { volatile atomic<int,strong> a(0);  a.div    (2,sync); }
   { volatile atomic<int,strong> a(0);  a.mod    (2,sync); }
   { volatile atomic<int,strong> a(0);  a.lshift (2,sync); }
   { volatile atomic<int,strong> a(0);  a.rshift (2,sync); }
   { volatile atomic<int,strong> a(0);  a.andeq  (2,sync); }
   { volatile atomic<int,strong> a(0);  a.oreq   (2,sync); }
   { volatile atomic<int,strong> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<int,strong> a(0);  a.min    (2,sync); }
   { volatile atomic<int,strong> a(0);  a.max    (2,sync); }
   { volatile atomic<int,strong> a(0);  a.inc    (  sync); }
   { volatile atomic<int,strong> a(0);  a.preinc (  sync); }
   { volatile atomic<int,strong> a(0);  a.postinc(  sync); }
   { volatile atomic<int,strong> a(0);  a.dec    (  sync); }
   { volatile atomic<int,strong> a(0);  a.predec (  sync); }
   { volatile atomic<int,strong> a(0);  a.postdec(  sync); }
   { volatile atomic<int,strong> a(0);  a.add    (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.div    (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.mod    (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.lshift (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.rshift (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.andeq  (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.oreq   (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.min    (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.max    (2,success,failure); }
   { volatile atomic<int,strong> a(0);  a.inc    (  success,failure); }
   { volatile atomic<int,strong> a(0);  a.preinc (  success,failure); }
   { volatile atomic<int,strong> a(0);  a.postinc(  success,failure); }
   { volatile atomic<int,strong> a(0);  a.dec    (  success,failure); }
   { volatile atomic<int,strong> a(0);  a.predec (  success,failure); }
   { volatile atomic<int,strong> a(0);  a.postdec(  success,failure); }

   { volatile atomic<int,strong::pun> a(0);  a.add    (2); }
   { volatile atomic<int,strong::pun> a(0);  a.sub    (2); }
   { volatile atomic<int,strong::pun> a(0);  a.mul    (2); }
   { volatile atomic<int,strong::pun> a(0);  a.div    (2); }
   { volatile atomic<int,strong::pun> a(0);  a.mod    (2); }
   { volatile atomic<int,strong::pun> a(0);  a.lshift (2); }
   { volatile atomic<int,strong::pun> a(0);  a.rshift (2); }
   { volatile atomic<int,strong::pun> a(0);  a.andeq  (2); }
   { volatile atomic<int,strong::pun> a(0);  a.oreq   (2); }
   { volatile atomic<int,strong::pun> a(0);  a.xoreq  (2); }
   { volatile atomic<int,strong::pun> a(0);  a.min    (2); }
   { volatile atomic<int,strong::pun> a(0);  a.max    (2); }
   { volatile atomic<int,strong::pun> a(0);  a.inc    ( ); }
   { volatile atomic<int,strong::pun> a(0);  a.preinc ( ); }
   { volatile atomic<int,strong::pun> a(0);  a.postinc( ); }
   { volatile atomic<int,strong::pun> a(0);  a.dec    ( ); }
   { volatile atomic<int,strong::pun> a(0);  a.predec ( ); }
   { volatile atomic<int,strong::pun> a(0);  a.postdec( ); }
   { volatile atomic<int,strong::pun> a(0);  a.add    (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.sub    (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.mul    (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.div    (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.mod    (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.lshift (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.rshift (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.andeq  (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.oreq   (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.min    (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.max    (2,sync); }
   { volatile atomic<int,strong::pun> a(0);  a.inc    (  sync); }
   { volatile atomic<int,strong::pun> a(0);  a.preinc (  sync); }
   { volatile atomic<int,strong::pun> a(0);  a.postinc(  sync); }
   { volatile atomic<int,strong::pun> a(0);  a.dec    (  sync); }
   { volatile atomic<int,strong::pun> a(0);  a.predec (  sync); }
   { volatile atomic<int,strong::pun> a(0);  a.postdec(  sync); }
   { volatile atomic<int,strong::pun> a(0);  a.add    (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.div    (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.mod    (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.lshift (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.rshift (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.andeq  (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.oreq   (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.min    (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.max    (2,success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.inc    (  success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.preinc (  success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.postinc(  success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.dec    (  success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.predec (  success,failure); }
   { volatile atomic<int,strong::pun> a(0);  a.postdec(  success,failure); }

   { volatile atomic<int,weak> a(0);  a.add    (2); }
   { volatile atomic<int,weak> a(0);  a.sub    (2); }
   { volatile atomic<int,weak> a(0);  a.mul    (2); }
   { volatile atomic<int,weak> a(0);  a.div    (2); }
   { volatile atomic<int,weak> a(0);  a.mod    (2); }
   { volatile atomic<int,weak> a(0);  a.lshift (2); }
   { volatile atomic<int,weak> a(0);  a.rshift (2); }
   { volatile atomic<int,weak> a(0);  a.andeq  (2); }
   { volatile atomic<int,weak> a(0);  a.oreq   (2); }
   { volatile atomic<int,weak> a(0);  a.xoreq  (2); }
   { volatile atomic<int,weak> a(0);  a.min    (2); }
   { volatile atomic<int,weak> a(0);  a.max    (2); }
   { volatile atomic<int,weak> a(0);  a.inc    ( ); }
   { volatile atomic<int,weak> a(0);  a.preinc ( ); }
   { volatile atomic<int,weak> a(0);  a.postinc( ); }
   { volatile atomic<int,weak> a(0);  a.dec    ( ); }
   { volatile atomic<int,weak> a(0);  a.predec ( ); }
   { volatile atomic<int,weak> a(0);  a.postdec( ); }
   { volatile atomic<int,weak> a(0);  a.add    (2,sync); }
   { volatile atomic<int,weak> a(0);  a.sub    (2,sync); }
   { volatile atomic<int,weak> a(0);  a.mul    (2,sync); }
   { volatile atomic<int,weak> a(0);  a.div    (2,sync); }
   { volatile atomic<int,weak> a(0);  a.mod    (2,sync); }
   { volatile atomic<int,weak> a(0);  a.lshift (2,sync); }
   { volatile atomic<int,weak> a(0);  a.rshift (2,sync); }
   { volatile atomic<int,weak> a(0);  a.andeq  (2,sync); }
   { volatile atomic<int,weak> a(0);  a.oreq   (2,sync); }
   { volatile atomic<int,weak> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<int,weak> a(0);  a.min    (2,sync); }
   { volatile atomic<int,weak> a(0);  a.max    (2,sync); }
   { volatile atomic<int,weak> a(0);  a.inc    (  sync); }
   { volatile atomic<int,weak> a(0);  a.preinc (  sync); }
   { volatile atomic<int,weak> a(0);  a.postinc(  sync); }
   { volatile atomic<int,weak> a(0);  a.dec    (  sync); }
   { volatile atomic<int,weak> a(0);  a.predec (  sync); }
   { volatile atomic<int,weak> a(0);  a.postdec(  sync); }
   { volatile atomic<int,weak> a(0);  a.add    (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.div    (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.mod    (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.lshift (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.rshift (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.andeq  (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.oreq   (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.min    (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.max    (2,success,failure); }
   { volatile atomic<int,weak> a(0);  a.inc    (  success,failure); }
   { volatile atomic<int,weak> a(0);  a.preinc (  success,failure); }
   { volatile atomic<int,weak> a(0);  a.postinc(  success,failure); }
   { volatile atomic<int,weak> a(0);  a.dec    (  success,failure); }
   { volatile atomic<int,weak> a(0);  a.predec (  success,failure); }
   { volatile atomic<int,weak> a(0);  a.postdec(  success,failure); }

   { volatile atomic<int,weak::pun> a(0);  a.add    (2); }
   { volatile atomic<int,weak::pun> a(0);  a.sub    (2); }
   { volatile atomic<int,weak::pun> a(0);  a.mul    (2); }
   { volatile atomic<int,weak::pun> a(0);  a.div    (2); }
   { volatile atomic<int,weak::pun> a(0);  a.mod    (2); }
   { volatile atomic<int,weak::pun> a(0);  a.lshift (2); }
   { volatile atomic<int,weak::pun> a(0);  a.rshift (2); }
   { volatile atomic<int,weak::pun> a(0);  a.andeq  (2); }
   { volatile atomic<int,weak::pun> a(0);  a.oreq   (2); }
   { volatile atomic<int,weak::pun> a(0);  a.xoreq  (2); }
   { volatile atomic<int,weak::pun> a(0);  a.min    (2); }
   { volatile atomic<int,weak::pun> a(0);  a.max    (2); }
   { volatile atomic<int,weak::pun> a(0);  a.inc    ( ); }
   { volatile atomic<int,weak::pun> a(0);  a.preinc ( ); }
   { volatile atomic<int,weak::pun> a(0);  a.postinc( ); }
   { volatile atomic<int,weak::pun> a(0);  a.dec    ( ); }
   { volatile atomic<int,weak::pun> a(0);  a.predec ( ); }
   { volatile atomic<int,weak::pun> a(0);  a.postdec( ); }
   { volatile atomic<int,weak::pun> a(0);  a.add    (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.sub    (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.mul    (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.div    (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.mod    (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.lshift (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.rshift (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.andeq  (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.oreq   (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.min    (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.max    (2,sync); }
   { volatile atomic<int,weak::pun> a(0);  a.inc    (  sync); }
   { volatile atomic<int,weak::pun> a(0);  a.preinc (  sync); }
   { volatile atomic<int,weak::pun> a(0);  a.postinc(  sync); }
   { volatile atomic<int,weak::pun> a(0);  a.dec    (  sync); }
   { volatile atomic<int,weak::pun> a(0);  a.predec (  sync); }
   { volatile atomic<int,weak::pun> a(0);  a.postdec(  sync); }
   { volatile atomic<int,weak::pun> a(0);  a.add    (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.div    (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.mod    (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.lshift (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.rshift (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.andeq  (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.oreq   (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.min    (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.max    (2,success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.inc    (  success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.preinc (  success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.postinc(  success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.dec    (  success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.predec (  success,failure); }
   { volatile atomic<int,weak::pun> a(0);  a.postdec(  success,failure); }

   { volatile atomic<int,lock> a(0);  a.add    (2); }
   { volatile atomic<int,lock> a(0);  a.sub    (2); }
   { volatile atomic<int,lock> a(0);  a.mul    (2); }
   { volatile atomic<int,lock> a(0);  a.div    (2); }
   { volatile atomic<int,lock> a(0);  a.mod    (2); }
   { volatile atomic<int,lock> a(0);  a.lshift (2); }
   { volatile atomic<int,lock> a(0);  a.rshift (2); }
   { volatile atomic<int,lock> a(0);  a.andeq  (2); }
   { volatile atomic<int,lock> a(0);  a.oreq   (2); }
   { volatile atomic<int,lock> a(0);  a.xoreq  (2); }
   { volatile atomic<int,lock> a(0);  a.min    (2); }
   { volatile atomic<int,lock> a(0);  a.max    (2); }
   { volatile atomic<int,lock> a(0);  a.inc    ( ); }
   { volatile atomic<int,lock> a(0);  a.preinc ( ); }
   { volatile atomic<int,lock> a(0);  a.postinc( ); }
   { volatile atomic<int,lock> a(0);  a.dec    ( ); }
   { volatile atomic<int,lock> a(0);  a.predec ( ); }
   { volatile atomic<int,lock> a(0);  a.postdec( ); }
// { volatile atomic<int,lock> a(0);  a.add    (2,sync); }
// { volatile atomic<int,lock> a(0);  a.sub    (2,sync); }
// { volatile atomic<int,lock> a(0);  a.mul    (2,sync); }
// { volatile atomic<int,lock> a(0);  a.div    (2,sync); }
// { volatile atomic<int,lock> a(0);  a.mod    (2,sync); }
// { volatile atomic<int,lock> a(0);  a.lshift (2,sync); }
// { volatile atomic<int,lock> a(0);  a.rshift (2,sync); }
// { volatile atomic<int,lock> a(0);  a.andeq  (2,sync); }
// { volatile atomic<int,lock> a(0);  a.oreq   (2,sync); }
// { volatile atomic<int,lock> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<int,lock> a(0);  a.min    (2,sync); }
// { volatile atomic<int,lock> a(0);  a.max    (2,sync); }
// { volatile atomic<int,lock> a(0);  a.inc    (  sync); }
// { volatile atomic<int,lock> a(0);  a.preinc (  sync); }
// { volatile atomic<int,lock> a(0);  a.postinc(  sync); }
// { volatile atomic<int,lock> a(0);  a.dec    (  sync); }
// { volatile atomic<int,lock> a(0);  a.predec (  sync); }
// { volatile atomic<int,lock> a(0);  a.postdec(  sync); }
// { volatile atomic<int,lock> a(0);  a.add    (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.div    (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.min    (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.max    (2,success,failure); }
// { volatile atomic<int,lock> a(0);  a.inc    (  success,failure); }
// { volatile atomic<int,lock> a(0);  a.preinc (  success,failure); }
// { volatile atomic<int,lock> a(0);  a.postinc(  success,failure); }
// { volatile atomic<int,lock> a(0);  a.dec    (  success,failure); }
// { volatile atomic<int,lock> a(0);  a.predec (  success,failure); }
// { volatile atomic<int,lock> a(0);  a.postdec(  success,failure); }

   { volatile atomic<int,serial> a(0);  a.add    (2); }
   { volatile atomic<int,serial> a(0);  a.sub    (2); }
   { volatile atomic<int,serial> a(0);  a.mul    (2); }
   { volatile atomic<int,serial> a(0);  a.div    (2); }
   { volatile atomic<int,serial> a(0);  a.mod    (2); }
   { volatile atomic<int,serial> a(0);  a.lshift (2); }
   { volatile atomic<int,serial> a(0);  a.rshift (2); }
   { volatile atomic<int,serial> a(0);  a.andeq  (2); }
   { volatile atomic<int,serial> a(0);  a.oreq   (2); }
   { volatile atomic<int,serial> a(0);  a.xoreq  (2); }
   { volatile atomic<int,serial> a(0);  a.min    (2); }
   { volatile atomic<int,serial> a(0);  a.max    (2); }
   { volatile atomic<int,serial> a(0);  a.inc    ( ); }
   { volatile atomic<int,serial> a(0);  a.preinc ( ); }
   { volatile atomic<int,serial> a(0);  a.postinc( ); }
   { volatile atomic<int,serial> a(0);  a.dec    ( ); }
   { volatile atomic<int,serial> a(0);  a.predec ( ); }
   { volatile atomic<int,serial> a(0);  a.postdec( ); }
// { volatile atomic<int,serial> a(0);  a.add    (2,sync); }
// { volatile atomic<int,serial> a(0);  a.sub    (2,sync); }
// { volatile atomic<int,serial> a(0);  a.mul    (2,sync); }
// { volatile atomic<int,serial> a(0);  a.div    (2,sync); }
// { volatile atomic<int,serial> a(0);  a.mod    (2,sync); }
// { volatile atomic<int,serial> a(0);  a.lshift (2,sync); }
// { volatile atomic<int,serial> a(0);  a.rshift (2,sync); }
// { volatile atomic<int,serial> a(0);  a.andeq  (2,sync); }
// { volatile atomic<int,serial> a(0);  a.oreq   (2,sync); }
// { volatile atomic<int,serial> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<int,serial> a(0);  a.min    (2,sync); }
// { volatile atomic<int,serial> a(0);  a.max    (2,sync); }
// { volatile atomic<int,serial> a(0);  a.inc    (  sync); }
// { volatile atomic<int,serial> a(0);  a.preinc (  sync); }
// { volatile atomic<int,serial> a(0);  a.postinc(  sync); }
// { volatile atomic<int,serial> a(0);  a.dec    (  sync); }
// { volatile atomic<int,serial> a(0);  a.predec (  sync); }
// { volatile atomic<int,serial> a(0);  a.postdec(  sync); }
// { volatile atomic<int,serial> a(0);  a.add    (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.div    (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.min    (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.max    (2,success,failure); }
// { volatile atomic<int,serial> a(0);  a.inc    (  success,failure); }
// { volatile atomic<int,serial> a(0);  a.preinc (  success,failure); }
// { volatile atomic<int,serial> a(0);  a.postinc(  success,failure); }
// { volatile atomic<int,serial> a(0);  a.dec    (  success,failure); }
// { volatile atomic<int,serial> a(0);  a.predec (  success,failure); }
// { volatile atomic<int,serial> a(0);  a.postdec(  success,failure); }



   // ------------------------
   // ulong
   // ------------------------

   { volatile atomic<ulong,cpp> a(0);  a.add    (2); }
   { volatile atomic<ulong,cpp> a(0);  a.sub    (2); }
// { volatile atomic<ulong,cpp> a(0);  a.mul    (2); }
// { volatile atomic<ulong,cpp> a(0);  a.div    (2); }
// { volatile atomic<ulong,cpp> a(0);  a.mod    (2); }
// { volatile atomic<ulong,cpp> a(0);  a.lshift (2); }
// { volatile atomic<ulong,cpp> a(0);  a.rshift (2); }
   { volatile atomic<ulong,cpp> a(0);  a.andeq  (2); }
   { volatile atomic<ulong,cpp> a(0);  a.oreq   (2); }
   { volatile atomic<ulong,cpp> a(0);  a.xoreq  (2); }
// { volatile atomic<ulong,cpp> a(0);  a.min    (2); }
// { volatile atomic<ulong,cpp> a(0);  a.max    (2); }
   { volatile atomic<ulong,cpp> a(0);  a.inc    ( ); }
   { volatile atomic<ulong,cpp> a(0);  a.preinc ( ); }
   { volatile atomic<ulong,cpp> a(0);  a.postinc( ); }
   { volatile atomic<ulong,cpp> a(0);  a.dec    ( ); }
   { volatile atomic<ulong,cpp> a(0);  a.predec ( ); }
   { volatile atomic<ulong,cpp> a(0);  a.postdec( ); }
   { volatile atomic<ulong,cpp> a(0);  a.add    (2,sync); }
   { volatile atomic<ulong,cpp> a(0);  a.sub    (2,sync); }
// { volatile atomic<ulong,cpp> a(0);  a.mul    (2,sync); }
// { volatile atomic<ulong,cpp> a(0);  a.div    (2,sync); }
// { volatile atomic<ulong,cpp> a(0);  a.mod    (2,sync); }
// { volatile atomic<ulong,cpp> a(0);  a.lshift (2,sync); }
// { volatile atomic<ulong,cpp> a(0);  a.rshift (2,sync); }
   { volatile atomic<ulong,cpp> a(0);  a.andeq  (2,sync); }
   { volatile atomic<ulong,cpp> a(0);  a.oreq   (2,sync); }
   { volatile atomic<ulong,cpp> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<ulong,cpp> a(0);  a.min    (2,sync); }
// { volatile atomic<ulong,cpp> a(0);  a.max    (2,sync); }
// { volatile atomic<ulong,cpp> a(0);  a.inc    (  sync); }
// { volatile atomic<ulong,cpp> a(0);  a.preinc (  sync); }
// { volatile atomic<ulong,cpp> a(0);  a.postinc(  sync); }
// { volatile atomic<ulong,cpp> a(0);  a.dec    (  sync); }
// { volatile atomic<ulong,cpp> a(0);  a.predec (  sync); }
// { volatile atomic<ulong,cpp> a(0);  a.postdec(  sync); }
// { volatile atomic<ulong,cpp> a(0);  a.add    (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.div    (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.min    (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.max    (2,success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.inc    (  success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.preinc (  success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.postinc(  success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.dec    (  success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.predec (  success,failure); }
// { volatile atomic<ulong,cpp> a(0);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { volatile atomic<ulong,kokkos> a(0);  a.add    (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.sub    (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.mul    (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.div    (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.mod    (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.lshift (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.rshift (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.andeq  (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.oreq   (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.xoreq  (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.min    (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.max    (2); }
   { volatile atomic<ulong,kokkos> a(0);  a.inc    ( ); }
   { volatile atomic<ulong,kokkos> a(0);  a.preinc ( ); }
   { volatile atomic<ulong,kokkos> a(0);  a.postinc( ); }
   { volatile atomic<ulong,kokkos> a(0);  a.dec    ( ); }
   { volatile atomic<ulong,kokkos> a(0);  a.predec ( ); }
   { volatile atomic<ulong,kokkos> a(0);  a.postdec( ); }
// { volatile atomic<ulong,kokkos> a(0);  a.add    (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.sub    (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.mul    (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.div    (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.mod    (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.lshift (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.rshift (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.andeq  (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.oreq   (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.min    (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.max    (2,sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.inc    (  sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.preinc (  sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.postinc(  sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.dec    (  sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.predec (  sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.postdec(  sync); }
// { volatile atomic<ulong,kokkos> a(0);  a.add    (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.div    (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.min    (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.max    (2,success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.inc    (  success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.preinc (  success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.postinc(  success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.dec    (  success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.predec (  success,failure); }
// { volatile atomic<ulong,kokkos> a(0);  a.postdec(  success,failure); }
#endif

   { volatile atomic<ulong,strong> a(0);  a.add    (2); }
   { volatile atomic<ulong,strong> a(0);  a.sub    (2); }
   { volatile atomic<ulong,strong> a(0);  a.mul    (2); }
   { volatile atomic<ulong,strong> a(0);  a.div    (2); }
   { volatile atomic<ulong,strong> a(0);  a.mod    (2); }
   { volatile atomic<ulong,strong> a(0);  a.lshift (2); }
   { volatile atomic<ulong,strong> a(0);  a.rshift (2); }
   { volatile atomic<ulong,strong> a(0);  a.andeq  (2); }
   { volatile atomic<ulong,strong> a(0);  a.oreq   (2); }
   { volatile atomic<ulong,strong> a(0);  a.xoreq  (2); }
   { volatile atomic<ulong,strong> a(0);  a.min    (2); }
   { volatile atomic<ulong,strong> a(0);  a.max    (2); }
   { volatile atomic<ulong,strong> a(0);  a.inc    ( ); }
   { volatile atomic<ulong,strong> a(0);  a.preinc ( ); }
   { volatile atomic<ulong,strong> a(0);  a.postinc( ); }
   { volatile atomic<ulong,strong> a(0);  a.dec    ( ); }
   { volatile atomic<ulong,strong> a(0);  a.predec ( ); }
   { volatile atomic<ulong,strong> a(0);  a.postdec( ); }
   { volatile atomic<ulong,strong> a(0);  a.add    (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.sub    (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.mul    (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.div    (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.mod    (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.lshift (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.rshift (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.andeq  (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.oreq   (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.min    (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.max    (2,sync); }
   { volatile atomic<ulong,strong> a(0);  a.inc    (  sync); }
   { volatile atomic<ulong,strong> a(0);  a.preinc (  sync); }
   { volatile atomic<ulong,strong> a(0);  a.postinc(  sync); }
   { volatile atomic<ulong,strong> a(0);  a.dec    (  sync); }
   { volatile atomic<ulong,strong> a(0);  a.predec (  sync); }
   { volatile atomic<ulong,strong> a(0);  a.postdec(  sync); }
   { volatile atomic<ulong,strong> a(0);  a.add    (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.div    (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.mod    (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.lshift (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.rshift (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.andeq  (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.oreq   (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.min    (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.max    (2,success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.inc    (  success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.preinc (  success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.postinc(  success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.dec    (  success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.predec (  success,failure); }
   { volatile atomic<ulong,strong> a(0);  a.postdec(  success,failure); }

   { volatile atomic<ulong,strong::pun> a(0);  a.add    (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.sub    (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.mul    (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.div    (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.mod    (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.lshift (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.rshift (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.andeq  (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.oreq   (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.xoreq  (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.min    (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.max    (2); }
   { volatile atomic<ulong,strong::pun> a(0);  a.inc    ( ); }
   { volatile atomic<ulong,strong::pun> a(0);  a.preinc ( ); }
   { volatile atomic<ulong,strong::pun> a(0);  a.postinc( ); }
   { volatile atomic<ulong,strong::pun> a(0);  a.dec    ( ); }
   { volatile atomic<ulong,strong::pun> a(0);  a.predec ( ); }
   { volatile atomic<ulong,strong::pun> a(0);  a.postdec( ); }
   { volatile atomic<ulong,strong::pun> a(0);  a.add    (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.sub    (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.mul    (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.div    (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.mod    (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.lshift (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.rshift (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.andeq  (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.oreq   (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.min    (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.max    (2,sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.inc    (  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.preinc (  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.postinc(  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.dec    (  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.predec (  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.postdec(  sync); }
   { volatile atomic<ulong,strong::pun> a(0);  a.add    (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.div    (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.mod    (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.lshift (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.rshift (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.andeq  (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.oreq   (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.min    (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.max    (2,success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.inc    (  success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.preinc (  success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.postinc(  success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.dec    (  success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.predec (  success,failure); }
   { volatile atomic<ulong,strong::pun> a(0);  a.postdec(  success,failure); }

   { volatile atomic<ulong,weak> a(0);  a.add    (2); }
   { volatile atomic<ulong,weak> a(0);  a.sub    (2); }
   { volatile atomic<ulong,weak> a(0);  a.mul    (2); }
   { volatile atomic<ulong,weak> a(0);  a.div    (2); }
   { volatile atomic<ulong,weak> a(0);  a.mod    (2); }
   { volatile atomic<ulong,weak> a(0);  a.lshift (2); }
   { volatile atomic<ulong,weak> a(0);  a.rshift (2); }
   { volatile atomic<ulong,weak> a(0);  a.andeq  (2); }
   { volatile atomic<ulong,weak> a(0);  a.oreq   (2); }
   { volatile atomic<ulong,weak> a(0);  a.xoreq  (2); }
   { volatile atomic<ulong,weak> a(0);  a.min    (2); }
   { volatile atomic<ulong,weak> a(0);  a.max    (2); }
   { volatile atomic<ulong,weak> a(0);  a.inc    ( ); }
   { volatile atomic<ulong,weak> a(0);  a.preinc ( ); }
   { volatile atomic<ulong,weak> a(0);  a.postinc( ); }
   { volatile atomic<ulong,weak> a(0);  a.dec    ( ); }
   { volatile atomic<ulong,weak> a(0);  a.predec ( ); }
   { volatile atomic<ulong,weak> a(0);  a.postdec( ); }
   { volatile atomic<ulong,weak> a(0);  a.add    (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.sub    (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.mul    (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.div    (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.mod    (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.lshift (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.rshift (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.andeq  (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.oreq   (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.min    (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.max    (2,sync); }
   { volatile atomic<ulong,weak> a(0);  a.inc    (  sync); }
   { volatile atomic<ulong,weak> a(0);  a.preinc (  sync); }
   { volatile atomic<ulong,weak> a(0);  a.postinc(  sync); }
   { volatile atomic<ulong,weak> a(0);  a.dec    (  sync); }
   { volatile atomic<ulong,weak> a(0);  a.predec (  sync); }
   { volatile atomic<ulong,weak> a(0);  a.postdec(  sync); }
   { volatile atomic<ulong,weak> a(0);  a.add    (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.div    (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.mod    (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.lshift (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.rshift (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.andeq  (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.oreq   (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.min    (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.max    (2,success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.inc    (  success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.preinc (  success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.postinc(  success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.dec    (  success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.predec (  success,failure); }
   { volatile atomic<ulong,weak> a(0);  a.postdec(  success,failure); }

   { volatile atomic<ulong,weak::pun> a(0);  a.add    (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.sub    (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.mul    (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.div    (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.mod    (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.lshift (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.rshift (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.andeq  (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.oreq   (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.xoreq  (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.min    (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.max    (2); }
   { volatile atomic<ulong,weak::pun> a(0);  a.inc    ( ); }
   { volatile atomic<ulong,weak::pun> a(0);  a.preinc ( ); }
   { volatile atomic<ulong,weak::pun> a(0);  a.postinc( ); }
   { volatile atomic<ulong,weak::pun> a(0);  a.dec    ( ); }
   { volatile atomic<ulong,weak::pun> a(0);  a.predec ( ); }
   { volatile atomic<ulong,weak::pun> a(0);  a.postdec( ); }
   { volatile atomic<ulong,weak::pun> a(0);  a.add    (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.sub    (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.mul    (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.div    (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.mod    (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.lshift (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.rshift (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.andeq  (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.oreq   (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.min    (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.max    (2,sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.inc    (  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.preinc (  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.postinc(  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.dec    (  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.predec (  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.postdec(  sync); }
   { volatile atomic<ulong,weak::pun> a(0);  a.add    (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.div    (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.mod    (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.lshift (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.rshift (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.andeq  (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.oreq   (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.min    (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.max    (2,success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.inc    (  success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.preinc (  success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.postinc(  success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.dec    (  success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.predec (  success,failure); }
   { volatile atomic<ulong,weak::pun> a(0);  a.postdec(  success,failure); }

   { volatile atomic<ulong,lock> a(0);  a.add    (2); }
   { volatile atomic<ulong,lock> a(0);  a.sub    (2); }
   { volatile atomic<ulong,lock> a(0);  a.mul    (2); }
   { volatile atomic<ulong,lock> a(0);  a.div    (2); }
   { volatile atomic<ulong,lock> a(0);  a.mod    (2); }
   { volatile atomic<ulong,lock> a(0);  a.lshift (2); }
   { volatile atomic<ulong,lock> a(0);  a.rshift (2); }
   { volatile atomic<ulong,lock> a(0);  a.andeq  (2); }
   { volatile atomic<ulong,lock> a(0);  a.oreq   (2); }
   { volatile atomic<ulong,lock> a(0);  a.xoreq  (2); }
   { volatile atomic<ulong,lock> a(0);  a.min    (2); }
   { volatile atomic<ulong,lock> a(0);  a.max    (2); }
   { volatile atomic<ulong,lock> a(0);  a.inc    ( ); }
   { volatile atomic<ulong,lock> a(0);  a.preinc ( ); }
   { volatile atomic<ulong,lock> a(0);  a.postinc( ); }
   { volatile atomic<ulong,lock> a(0);  a.dec    ( ); }
   { volatile atomic<ulong,lock> a(0);  a.predec ( ); }
   { volatile atomic<ulong,lock> a(0);  a.postdec( ); }
// { volatile atomic<ulong,lock> a(0);  a.add    (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.sub    (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.mul    (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.div    (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.mod    (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.lshift (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.rshift (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.andeq  (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.oreq   (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.min    (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.max    (2,sync); }
// { volatile atomic<ulong,lock> a(0);  a.inc    (  sync); }
// { volatile atomic<ulong,lock> a(0);  a.preinc (  sync); }
// { volatile atomic<ulong,lock> a(0);  a.postinc(  sync); }
// { volatile atomic<ulong,lock> a(0);  a.dec    (  sync); }
// { volatile atomic<ulong,lock> a(0);  a.predec (  sync); }
// { volatile atomic<ulong,lock> a(0);  a.postdec(  sync); }
// { volatile atomic<ulong,lock> a(0);  a.add    (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.div    (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.min    (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.max    (2,success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.inc    (  success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.preinc (  success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.postinc(  success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.dec    (  success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.predec (  success,failure); }
// { volatile atomic<ulong,lock> a(0);  a.postdec(  success,failure); }

   { volatile atomic<ulong,serial> a(0);  a.add    (2); }
   { volatile atomic<ulong,serial> a(0);  a.sub    (2); }
   { volatile atomic<ulong,serial> a(0);  a.mul    (2); }
   { volatile atomic<ulong,serial> a(0);  a.div    (2); }
   { volatile atomic<ulong,serial> a(0);  a.mod    (2); }
   { volatile atomic<ulong,serial> a(0);  a.lshift (2); }
   { volatile atomic<ulong,serial> a(0);  a.rshift (2); }
   { volatile atomic<ulong,serial> a(0);  a.andeq  (2); }
   { volatile atomic<ulong,serial> a(0);  a.oreq   (2); }
   { volatile atomic<ulong,serial> a(0);  a.xoreq  (2); }
   { volatile atomic<ulong,serial> a(0);  a.min    (2); }
   { volatile atomic<ulong,serial> a(0);  a.max    (2); }
   { volatile atomic<ulong,serial> a(0);  a.inc    ( ); }
   { volatile atomic<ulong,serial> a(0);  a.preinc ( ); }
   { volatile atomic<ulong,serial> a(0);  a.postinc( ); }
   { volatile atomic<ulong,serial> a(0);  a.dec    ( ); }
   { volatile atomic<ulong,serial> a(0);  a.predec ( ); }
   { volatile atomic<ulong,serial> a(0);  a.postdec( ); }
// { volatile atomic<ulong,serial> a(0);  a.add    (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.sub    (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.mul    (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.div    (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.mod    (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.lshift (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.rshift (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.andeq  (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.oreq   (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.min    (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.max    (2,sync); }
// { volatile atomic<ulong,serial> a(0);  a.inc    (  sync); }
// { volatile atomic<ulong,serial> a(0);  a.preinc (  sync); }
// { volatile atomic<ulong,serial> a(0);  a.postinc(  sync); }
// { volatile atomic<ulong,serial> a(0);  a.dec    (  sync); }
// { volatile atomic<ulong,serial> a(0);  a.predec (  sync); }
// { volatile atomic<ulong,serial> a(0);  a.postdec(  sync); }
// { volatile atomic<ulong,serial> a(0);  a.add    (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.div    (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.min    (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.max    (2,success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.inc    (  success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.preinc (  success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.postinc(  success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.dec    (  success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.predec (  success,failure); }
// { volatile atomic<ulong,serial> a(0);  a.postdec(  success,failure); }



   // ------------------------
   // double
   // ------------------------

// { volatile atomic<double,cpp> a(0);  a.add    (2); }
// { volatile atomic<double,cpp> a(0);  a.sub    (2); }
// { volatile atomic<double,cpp> a(0);  a.mul    (2); }
// { volatile atomic<double,cpp> a(0);  a.div    (2); }
// { volatile atomic<double,cpp> a(0);  a.mod    (2); }
// { volatile atomic<double,cpp> a(0);  a.lshift (2); }
// { volatile atomic<double,cpp> a(0);  a.rshift (2); }
// { volatile atomic<double,cpp> a(0);  a.andeq  (2); }
// { volatile atomic<double,cpp> a(0);  a.oreq   (2); }
// { volatile atomic<double,cpp> a(0);  a.xoreq  (2); }
// { volatile atomic<double,cpp> a(0);  a.min    (2); }
// { volatile atomic<double,cpp> a(0);  a.max    (2); }
// { volatile atomic<double,cpp> a(0);  a.inc    ( ); }
// { volatile atomic<double,cpp> a(0);  a.preinc ( ); }
// { volatile atomic<double,cpp> a(0);  a.postinc( ); }
// { volatile atomic<double,cpp> a(0);  a.dec    ( ); }
// { volatile atomic<double,cpp> a(0);  a.predec ( ); }
// { volatile atomic<double,cpp> a(0);  a.postdec( ); }
// { volatile atomic<double,cpp> a(0);  a.add    (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.sub    (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.mul    (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.div    (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.mod    (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.lshift (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.rshift (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.andeq  (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.oreq   (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.min    (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.max    (2,sync); }
// { volatile atomic<double,cpp> a(0);  a.inc    (  sync); }
// { volatile atomic<double,cpp> a(0);  a.preinc (  sync); }
// { volatile atomic<double,cpp> a(0);  a.postinc(  sync); }
// { volatile atomic<double,cpp> a(0);  a.dec    (  sync); }
// { volatile atomic<double,cpp> a(0);  a.predec (  sync); }
// { volatile atomic<double,cpp> a(0);  a.postdec(  sync); }
// { volatile atomic<double,cpp> a(0);  a.add    (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.div    (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.min    (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.max    (2,success,failure); }
// { volatile atomic<double,cpp> a(0);  a.inc    (  success,failure); }
// { volatile atomic<double,cpp> a(0);  a.preinc (  success,failure); }
// { volatile atomic<double,cpp> a(0);  a.postinc(  success,failure); }
// { volatile atomic<double,cpp> a(0);  a.dec    (  success,failure); }
// { volatile atomic<double,cpp> a(0);  a.predec (  success,failure); }
// { volatile atomic<double,cpp> a(0);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
   { volatile atomic<double,kokkos> a(0);  a.add    (2); }
   { volatile atomic<double,kokkos> a(0);  a.sub    (2); }
   { volatile atomic<double,kokkos> a(0);  a.mul    (2); }
   { volatile atomic<double,kokkos> a(0);  a.div    (2); }
// { volatile atomic<double,kokkos> a(0);  a.mod    (2); }
// { volatile atomic<double,kokkos> a(0);  a.lshift (2); }
// { volatile atomic<double,kokkos> a(0);  a.rshift (2); }
// { volatile atomic<double,kokkos> a(0);  a.andeq  (2); }
// { volatile atomic<double,kokkos> a(0);  a.oreq   (2); }
// { volatile atomic<double,kokkos> a(0);  a.xoreq  (2); }
   { volatile atomic<double,kokkos> a(0);  a.min    (2); }
   { volatile atomic<double,kokkos> a(0);  a.max    (2); }
   { volatile atomic<double,kokkos> a(0);  a.inc    ( ); }
   { volatile atomic<double,kokkos> a(0);  a.preinc ( ); }
   { volatile atomic<double,kokkos> a(0);  a.postinc( ); }
   { volatile atomic<double,kokkos> a(0);  a.dec    ( ); }
   { volatile atomic<double,kokkos> a(0);  a.predec ( ); }
   { volatile atomic<double,kokkos> a(0);  a.postdec( ); }
// { volatile atomic<double,kokkos> a(0);  a.add    (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.sub    (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.mul    (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.div    (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.mod    (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.lshift (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.rshift (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.andeq  (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.oreq   (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.min    (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.max    (2,sync); }
// { volatile atomic<double,kokkos> a(0);  a.inc    (  sync); }
// { volatile atomic<double,kokkos> a(0);  a.preinc (  sync); }
// { volatile atomic<double,kokkos> a(0);  a.postinc(  sync); }
// { volatile atomic<double,kokkos> a(0);  a.dec    (  sync); }
// { volatile atomic<double,kokkos> a(0);  a.predec (  sync); }
// { volatile atomic<double,kokkos> a(0);  a.postdec(  sync); }
// { volatile atomic<double,kokkos> a(0);  a.add    (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.div    (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.min    (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.max    (2,success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.inc    (  success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.preinc (  success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.postinc(  success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.dec    (  success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.predec (  success,failure); }
// { volatile atomic<double,kokkos> a(0);  a.postdec(  success,failure); }
#endif

   { volatile atomic<double,strong> a(0);  a.add    (2); }
   { volatile atomic<double,strong> a(0);  a.sub    (2); }
   { volatile atomic<double,strong> a(0);  a.mul    (2); }
   { volatile atomic<double,strong> a(0);  a.div    (2); }
// { volatile atomic<double,strong> a(0);  a.mod    (2); }
// { volatile atomic<double,strong> a(0);  a.lshift (2); }
// { volatile atomic<double,strong> a(0);  a.rshift (2); }
// { volatile atomic<double,strong> a(0);  a.andeq  (2); }
// { volatile atomic<double,strong> a(0);  a.oreq   (2); }
// { volatile atomic<double,strong> a(0);  a.xoreq  (2); }
   { volatile atomic<double,strong> a(0);  a.min    (2); }
   { volatile atomic<double,strong> a(0);  a.max    (2); }
   { volatile atomic<double,strong> a(0);  a.inc    ( ); }
   { volatile atomic<double,strong> a(0);  a.preinc ( ); }
   { volatile atomic<double,strong> a(0);  a.postinc( ); }
   { volatile atomic<double,strong> a(0);  a.dec    ( ); }
   { volatile atomic<double,strong> a(0);  a.predec ( ); }
   { volatile atomic<double,strong> a(0);  a.postdec( ); }
   { volatile atomic<double,strong> a(0);  a.add    (2,sync); }
   { volatile atomic<double,strong> a(0);  a.sub    (2,sync); }
   { volatile atomic<double,strong> a(0);  a.mul    (2,sync); }
   { volatile atomic<double,strong> a(0);  a.div    (2,sync); }
// { volatile atomic<double,strong> a(0);  a.mod    (2,sync); }
// { volatile atomic<double,strong> a(0);  a.lshift (2,sync); }
// { volatile atomic<double,strong> a(0);  a.rshift (2,sync); }
// { volatile atomic<double,strong> a(0);  a.andeq  (2,sync); }
// { volatile atomic<double,strong> a(0);  a.oreq   (2,sync); }
// { volatile atomic<double,strong> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<double,strong> a(0);  a.min    (2,sync); }
   { volatile atomic<double,strong> a(0);  a.max    (2,sync); }
   { volatile atomic<double,strong> a(0);  a.inc    (  sync); }
   { volatile atomic<double,strong> a(0);  a.preinc (  sync); }
   { volatile atomic<double,strong> a(0);  a.postinc(  sync); }
   { volatile atomic<double,strong> a(0);  a.dec    (  sync); }
   { volatile atomic<double,strong> a(0);  a.predec (  sync); }
   { volatile atomic<double,strong> a(0);  a.postdec(  sync); }
   { volatile atomic<double,strong> a(0);  a.add    (2,success,failure); }
   { volatile atomic<double,strong> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<double,strong> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<double,strong> a(0);  a.div    (2,success,failure); }
// { volatile atomic<double,strong> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<double,strong> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<double,strong> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<double,strong> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<double,strong> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<double,strong> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<double,strong> a(0);  a.min    (2,success,failure); }
   { volatile atomic<double,strong> a(0);  a.max    (2,success,failure); }
   { volatile atomic<double,strong> a(0);  a.inc    (  success,failure); }
   { volatile atomic<double,strong> a(0);  a.preinc (  success,failure); }
   { volatile atomic<double,strong> a(0);  a.postinc(  success,failure); }
   { volatile atomic<double,strong> a(0);  a.dec    (  success,failure); }
   { volatile atomic<double,strong> a(0);  a.predec (  success,failure); }
   { volatile atomic<double,strong> a(0);  a.postdec(  success,failure); }

   { volatile atomic<double,strong::pun> a(0);  a.add    (2); }
   { volatile atomic<double,strong::pun> a(0);  a.sub    (2); }
   { volatile atomic<double,strong::pun> a(0);  a.mul    (2); }
   { volatile atomic<double,strong::pun> a(0);  a.div    (2); }
// { volatile atomic<double,strong::pun> a(0);  a.mod    (2); }
// { volatile atomic<double,strong::pun> a(0);  a.lshift (2); }
// { volatile atomic<double,strong::pun> a(0);  a.rshift (2); }
// { volatile atomic<double,strong::pun> a(0);  a.andeq  (2); }
// { volatile atomic<double,strong::pun> a(0);  a.oreq   (2); }
// { volatile atomic<double,strong::pun> a(0);  a.xoreq  (2); }
   { volatile atomic<double,strong::pun> a(0);  a.min    (2); }
   { volatile atomic<double,strong::pun> a(0);  a.max    (2); }
   { volatile atomic<double,strong::pun> a(0);  a.inc    ( ); }
   { volatile atomic<double,strong::pun> a(0);  a.preinc ( ); }
   { volatile atomic<double,strong::pun> a(0);  a.postinc( ); }
   { volatile atomic<double,strong::pun> a(0);  a.dec    ( ); }
   { volatile atomic<double,strong::pun> a(0);  a.predec ( ); }
   { volatile atomic<double,strong::pun> a(0);  a.postdec( ); }
   { volatile atomic<double,strong::pun> a(0);  a.add    (2,sync); }
   { volatile atomic<double,strong::pun> a(0);  a.sub    (2,sync); }
   { volatile atomic<double,strong::pun> a(0);  a.mul    (2,sync); }
   { volatile atomic<double,strong::pun> a(0);  a.div    (2,sync); }
// { volatile atomic<double,strong::pun> a(0);  a.mod    (2,sync); }
// { volatile atomic<double,strong::pun> a(0);  a.lshift (2,sync); }
// { volatile atomic<double,strong::pun> a(0);  a.rshift (2,sync); }
// { volatile atomic<double,strong::pun> a(0);  a.andeq  (2,sync); }
// { volatile atomic<double,strong::pun> a(0);  a.oreq   (2,sync); }
// { volatile atomic<double,strong::pun> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<double,strong::pun> a(0);  a.min    (2,sync); }
   { volatile atomic<double,strong::pun> a(0);  a.max    (2,sync); }
   { volatile atomic<double,strong::pun> a(0);  a.inc    (  sync); }
   { volatile atomic<double,strong::pun> a(0);  a.preinc (  sync); }
   { volatile atomic<double,strong::pun> a(0);  a.postinc(  sync); }
   { volatile atomic<double,strong::pun> a(0);  a.dec    (  sync); }
   { volatile atomic<double,strong::pun> a(0);  a.predec (  sync); }
   { volatile atomic<double,strong::pun> a(0);  a.postdec(  sync); }
   { volatile atomic<double,strong::pun> a(0);  a.add    (2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  a.div    (2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<double,strong::pun> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  a.min    (2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  a.max    (2,success,failure); }
   { volatile atomic<double,strong::pun> a(0);  a.inc    (  success,failure); }
   { volatile atomic<double,strong::pun> a(0);  a.preinc (  success,failure); }
   { volatile atomic<double,strong::pun> a(0);  a.postinc(  success,failure); }
   { volatile atomic<double,strong::pun> a(0);  a.dec    (  success,failure); }
   { volatile atomic<double,strong::pun> a(0);  a.predec (  success,failure); }
   { volatile atomic<double,strong::pun> a(0);  a.postdec(  success,failure); }

   { volatile atomic<double,weak> a(0);  a.add    (2); }
   { volatile atomic<double,weak> a(0);  a.sub    (2); }
   { volatile atomic<double,weak> a(0);  a.mul    (2); }
   { volatile atomic<double,weak> a(0);  a.div    (2); }
// { volatile atomic<double,weak> a(0);  a.mod    (2); }
// { volatile atomic<double,weak> a(0);  a.lshift (2); }
// { volatile atomic<double,weak> a(0);  a.rshift (2); }
// { volatile atomic<double,weak> a(0);  a.andeq  (2); }
// { volatile atomic<double,weak> a(0);  a.oreq   (2); }
// { volatile atomic<double,weak> a(0);  a.xoreq  (2); }
   { volatile atomic<double,weak> a(0);  a.min    (2); }
   { volatile atomic<double,weak> a(0);  a.max    (2); }
   { volatile atomic<double,weak> a(0);  a.inc    ( ); }
   { volatile atomic<double,weak> a(0);  a.preinc ( ); }
   { volatile atomic<double,weak> a(0);  a.postinc( ); }
   { volatile atomic<double,weak> a(0);  a.dec    ( ); }
   { volatile atomic<double,weak> a(0);  a.predec ( ); }
   { volatile atomic<double,weak> a(0);  a.postdec( ); }
   { volatile atomic<double,weak> a(0);  a.add    (2,sync); }
   { volatile atomic<double,weak> a(0);  a.sub    (2,sync); }
   { volatile atomic<double,weak> a(0);  a.mul    (2,sync); }
   { volatile atomic<double,weak> a(0);  a.div    (2,sync); }
// { volatile atomic<double,weak> a(0);  a.mod    (2,sync); }
// { volatile atomic<double,weak> a(0);  a.lshift (2,sync); }
// { volatile atomic<double,weak> a(0);  a.rshift (2,sync); }
// { volatile atomic<double,weak> a(0);  a.andeq  (2,sync); }
// { volatile atomic<double,weak> a(0);  a.oreq   (2,sync); }
// { volatile atomic<double,weak> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<double,weak> a(0);  a.min    (2,sync); }
   { volatile atomic<double,weak> a(0);  a.max    (2,sync); }
   { volatile atomic<double,weak> a(0);  a.inc    (  sync); }
   { volatile atomic<double,weak> a(0);  a.preinc (  sync); }
   { volatile atomic<double,weak> a(0);  a.postinc(  sync); }
   { volatile atomic<double,weak> a(0);  a.dec    (  sync); }
   { volatile atomic<double,weak> a(0);  a.predec (  sync); }
   { volatile atomic<double,weak> a(0);  a.postdec(  sync); }
   { volatile atomic<double,weak> a(0);  a.add    (2,success,failure); }
   { volatile atomic<double,weak> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<double,weak> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<double,weak> a(0);  a.div    (2,success,failure); }
// { volatile atomic<double,weak> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<double,weak> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<double,weak> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<double,weak> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<double,weak> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<double,weak> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<double,weak> a(0);  a.min    (2,success,failure); }
   { volatile atomic<double,weak> a(0);  a.max    (2,success,failure); }
   { volatile atomic<double,weak> a(0);  a.inc    (  success,failure); }
   { volatile atomic<double,weak> a(0);  a.preinc (  success,failure); }
   { volatile atomic<double,weak> a(0);  a.postinc(  success,failure); }
   { volatile atomic<double,weak> a(0);  a.dec    (  success,failure); }
   { volatile atomic<double,weak> a(0);  a.predec (  success,failure); }
   { volatile atomic<double,weak> a(0);  a.postdec(  success,failure); }

   { volatile atomic<double,weak::pun> a(0);  a.add    (2); }
   { volatile atomic<double,weak::pun> a(0);  a.sub    (2); }
   { volatile atomic<double,weak::pun> a(0);  a.mul    (2); }
   { volatile atomic<double,weak::pun> a(0);  a.div    (2); }
// { volatile atomic<double,weak::pun> a(0);  a.mod    (2); }
// { volatile atomic<double,weak::pun> a(0);  a.lshift (2); }
// { volatile atomic<double,weak::pun> a(0);  a.rshift (2); }
// { volatile atomic<double,weak::pun> a(0);  a.andeq  (2); }
// { volatile atomic<double,weak::pun> a(0);  a.oreq   (2); }
// { volatile atomic<double,weak::pun> a(0);  a.xoreq  (2); }
   { volatile atomic<double,weak::pun> a(0);  a.min    (2); }
   { volatile atomic<double,weak::pun> a(0);  a.max    (2); }
   { volatile atomic<double,weak::pun> a(0);  a.inc    ( ); }
   { volatile atomic<double,weak::pun> a(0);  a.preinc ( ); }
   { volatile atomic<double,weak::pun> a(0);  a.postinc( ); }
   { volatile atomic<double,weak::pun> a(0);  a.dec    ( ); }
   { volatile atomic<double,weak::pun> a(0);  a.predec ( ); }
   { volatile atomic<double,weak::pun> a(0);  a.postdec( ); }
   { volatile atomic<double,weak::pun> a(0);  a.add    (2,sync); }
   { volatile atomic<double,weak::pun> a(0);  a.sub    (2,sync); }
   { volatile atomic<double,weak::pun> a(0);  a.mul    (2,sync); }
   { volatile atomic<double,weak::pun> a(0);  a.div    (2,sync); }
// { volatile atomic<double,weak::pun> a(0);  a.mod    (2,sync); }
// { volatile atomic<double,weak::pun> a(0);  a.lshift (2,sync); }
// { volatile atomic<double,weak::pun> a(0);  a.rshift (2,sync); }
// { volatile atomic<double,weak::pun> a(0);  a.andeq  (2,sync); }
// { volatile atomic<double,weak::pun> a(0);  a.oreq   (2,sync); }
// { volatile atomic<double,weak::pun> a(0);  a.xoreq  (2,sync); }
   { volatile atomic<double,weak::pun> a(0);  a.min    (2,sync); }
   { volatile atomic<double,weak::pun> a(0);  a.max    (2,sync); }
   { volatile atomic<double,weak::pun> a(0);  a.inc    (  sync); }
   { volatile atomic<double,weak::pun> a(0);  a.preinc (  sync); }
   { volatile atomic<double,weak::pun> a(0);  a.postinc(  sync); }
   { volatile atomic<double,weak::pun> a(0);  a.dec    (  sync); }
   { volatile atomic<double,weak::pun> a(0);  a.predec (  sync); }
   { volatile atomic<double,weak::pun> a(0);  a.postdec(  sync); }
   { volatile atomic<double,weak::pun> a(0);  a.add    (2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  a.sub    (2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  a.mul    (2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  a.div    (2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<double,weak::pun> a(0);  a.xoreq  (2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  a.min    (2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  a.max    (2,success,failure); }
   { volatile atomic<double,weak::pun> a(0);  a.inc    (  success,failure); }
   { volatile atomic<double,weak::pun> a(0);  a.preinc (  success,failure); }
   { volatile atomic<double,weak::pun> a(0);  a.postinc(  success,failure); }
   { volatile atomic<double,weak::pun> a(0);  a.dec    (  success,failure); }
   { volatile atomic<double,weak::pun> a(0);  a.predec (  success,failure); }
   { volatile atomic<double,weak::pun> a(0);  a.postdec(  success,failure); }

   { volatile atomic<double,lock> a(0);  a.add    (2); }
   { volatile atomic<double,lock> a(0);  a.sub    (2); }
   { volatile atomic<double,lock> a(0);  a.mul    (2); }
   { volatile atomic<double,lock> a(0);  a.div    (2); }
// { volatile atomic<double,lock> a(0);  a.mod    (2); }
// { volatile atomic<double,lock> a(0);  a.lshift (2); }
// { volatile atomic<double,lock> a(0);  a.rshift (2); }
// { volatile atomic<double,lock> a(0);  a.andeq  (2); }
// { volatile atomic<double,lock> a(0);  a.oreq   (2); }
// { volatile atomic<double,lock> a(0);  a.xoreq  (2); }
   { volatile atomic<double,lock> a(0);  a.min    (2); }
   { volatile atomic<double,lock> a(0);  a.max    (2); }
   { volatile atomic<double,lock> a(0);  a.inc    ( ); }
   { volatile atomic<double,lock> a(0);  a.preinc ( ); }
   { volatile atomic<double,lock> a(0);  a.postinc( ); }
   { volatile atomic<double,lock> a(0);  a.dec    ( ); }
   { volatile atomic<double,lock> a(0);  a.predec ( ); }
   { volatile atomic<double,lock> a(0);  a.postdec( ); }
// { volatile atomic<double,lock> a(0);  a.add    (2,sync); }
// { volatile atomic<double,lock> a(0);  a.sub    (2,sync); }
// { volatile atomic<double,lock> a(0);  a.mul    (2,sync); }
// { volatile atomic<double,lock> a(0);  a.div    (2,sync); }
// { volatile atomic<double,lock> a(0);  a.mod    (2,sync); }
// { volatile atomic<double,lock> a(0);  a.lshift (2,sync); }
// { volatile atomic<double,lock> a(0);  a.rshift (2,sync); }
// { volatile atomic<double,lock> a(0);  a.andeq  (2,sync); }
// { volatile atomic<double,lock> a(0);  a.oreq   (2,sync); }
// { volatile atomic<double,lock> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<double,lock> a(0);  a.min    (2,sync); }
// { volatile atomic<double,lock> a(0);  a.max    (2,sync); }
// { volatile atomic<double,lock> a(0);  a.inc    (  sync); }
// { volatile atomic<double,lock> a(0);  a.preinc (  sync); }
// { volatile atomic<double,lock> a(0);  a.postinc(  sync); }
// { volatile atomic<double,lock> a(0);  a.dec    (  sync); }
// { volatile atomic<double,lock> a(0);  a.predec (  sync); }
// { volatile atomic<double,lock> a(0);  a.postdec(  sync); }
// { volatile atomic<double,lock> a(0);  a.add    (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.div    (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.min    (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.max    (2,success,failure); }
// { volatile atomic<double,lock> a(0);  a.inc    (  success,failure); }
// { volatile atomic<double,lock> a(0);  a.preinc (  success,failure); }
// { volatile atomic<double,lock> a(0);  a.postinc(  success,failure); }
// { volatile atomic<double,lock> a(0);  a.dec    (  success,failure); }
// { volatile atomic<double,lock> a(0);  a.predec (  success,failure); }
// { volatile atomic<double,lock> a(0);  a.postdec(  success,failure); }

   { volatile atomic<double,serial> a(0);  a.add    (2); }
   { volatile atomic<double,serial> a(0);  a.sub    (2); }
   { volatile atomic<double,serial> a(0);  a.mul    (2); }
   { volatile atomic<double,serial> a(0);  a.div    (2); }
// { volatile atomic<double,serial> a(0);  a.mod    (2); }
// { volatile atomic<double,serial> a(0);  a.lshift (2); }
// { volatile atomic<double,serial> a(0);  a.rshift (2); }
// { volatile atomic<double,serial> a(0);  a.andeq  (2); }
// { volatile atomic<double,serial> a(0);  a.oreq   (2); }
// { volatile atomic<double,serial> a(0);  a.xoreq  (2); }
   { volatile atomic<double,serial> a(0);  a.min    (2); }
   { volatile atomic<double,serial> a(0);  a.max    (2); }
   { volatile atomic<double,serial> a(0);  a.inc    ( ); }
   { volatile atomic<double,serial> a(0);  a.preinc ( ); }
   { volatile atomic<double,serial> a(0);  a.postinc( ); }
   { volatile atomic<double,serial> a(0);  a.dec    ( ); }
   { volatile atomic<double,serial> a(0);  a.predec ( ); }
   { volatile atomic<double,serial> a(0);  a.postdec( ); }
// { volatile atomic<double,serial> a(0);  a.add    (2,sync); }
// { volatile atomic<double,serial> a(0);  a.sub    (2,sync); }
// { volatile atomic<double,serial> a(0);  a.mul    (2,sync); }
// { volatile atomic<double,serial> a(0);  a.div    (2,sync); }
// { volatile atomic<double,serial> a(0);  a.mod    (2,sync); }
// { volatile atomic<double,serial> a(0);  a.lshift (2,sync); }
// { volatile atomic<double,serial> a(0);  a.rshift (2,sync); }
// { volatile atomic<double,serial> a(0);  a.andeq  (2,sync); }
// { volatile atomic<double,serial> a(0);  a.oreq   (2,sync); }
// { volatile atomic<double,serial> a(0);  a.xoreq  (2,sync); }
// { volatile atomic<double,serial> a(0);  a.min    (2,sync); }
// { volatile atomic<double,serial> a(0);  a.max    (2,sync); }
// { volatile atomic<double,serial> a(0);  a.inc    (  sync); }
// { volatile atomic<double,serial> a(0);  a.preinc (  sync); }
// { volatile atomic<double,serial> a(0);  a.postinc(  sync); }
// { volatile atomic<double,serial> a(0);  a.dec    (  sync); }
// { volatile atomic<double,serial> a(0);  a.predec (  sync); }
// { volatile atomic<double,serial> a(0);  a.postdec(  sync); }
// { volatile atomic<double,serial> a(0);  a.add    (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.sub    (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.mul    (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.div    (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.mod    (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.lshift (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.rshift (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.andeq  (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.oreq   (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.xoreq  (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.min    (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.max    (2,success,failure); }
// { volatile atomic<double,serial> a(0);  a.inc    (  success,failure); }
// { volatile atomic<double,serial> a(0);  a.preinc (  success,failure); }
// { volatile atomic<double,serial> a(0);  a.postinc(  success,failure); }
// { volatile atomic<double,serial> a(0);  a.dec    (  success,failure); }
// { volatile atomic<double,serial> a(0);  a.predec (  success,failure); }
// { volatile atomic<double,serial> a(0);  a.postdec(  success,failure); }



   // ------------------------
   // int*
   // ------------------------

#if !defined(ATOMICS_TEST)
   { volatile atomic<int*,cpp> a(&i);  a.add    (2); }
   { volatile atomic<int*,cpp> a(&i);  a.sub    (2); }
// { volatile atomic<int*,cpp> a(&i);  a.mul    (2); }
// { volatile atomic<int*,cpp> a(&i);  a.div    (2); }
// { volatile atomic<int*,cpp> a(&i);  a.mod    (2); }
// { volatile atomic<int*,cpp> a(&i);  a.lshift (2); }
// { volatile atomic<int*,cpp> a(&i);  a.rshift (2); }
// { volatile atomic<int*,cpp> a(&i);  a.andeq  (2); }
// { volatile atomic<int*,cpp> a(&i);  a.oreq   (2); }
// { volatile atomic<int*,cpp> a(&i);  a.xoreq  (2); }
// { volatile atomic<int*,cpp> a(&i);  a.min    (&j); }
// { volatile atomic<int*,cpp> a(&i);  a.max    (&j); }
   { volatile atomic<int*,cpp> a(&i);  a.inc    ( ); }
   { volatile atomic<int*,cpp> a(&i);  a.preinc ( ); }
   { volatile atomic<int*,cpp> a(&i);  a.postinc( ); }
   { volatile atomic<int*,cpp> a(&i);  a.dec    ( ); }
   { volatile atomic<int*,cpp> a(&i);  a.predec ( ); }
   { volatile atomic<int*,cpp> a(&i);  a.postdec( ); }
   { volatile atomic<int*,cpp> a(&i);  a.add    (2,sync); }
   { volatile atomic<int*,cpp> a(&i);  a.sub    (2,sync); }
// { volatile atomic<int*,cpp> a(&i);  a.mul    (2,sync); }
// { volatile atomic<int*,cpp> a(&i);  a.div    (2,sync); }
// { volatile atomic<int*,cpp> a(&i);  a.mod    (2,sync); }
// { volatile atomic<int*,cpp> a(&i);  a.lshift (2,sync); }
// { volatile atomic<int*,cpp> a(&i);  a.rshift (2,sync); }
// { volatile atomic<int*,cpp> a(&i);  a.andeq  (2,sync); }
// { volatile atomic<int*,cpp> a(&i);  a.oreq   (2,sync); }
// { volatile atomic<int*,cpp> a(&i);  a.xoreq  (2,sync); }
// { volatile atomic<int*,cpp> a(&i);  a.min    (&j,sync); }
// { volatile atomic<int*,cpp> a(&i);  a.max    (&j,sync); }
// { volatile atomic<int*,cpp> a(&i);  a.inc    (  sync); }
// { volatile atomic<int*,cpp> a(&i);  a.preinc (  sync); }
// { volatile atomic<int*,cpp> a(&i);  a.postinc(  sync); }
// { volatile atomic<int*,cpp> a(&i);  a.dec    (  sync); }
// { volatile atomic<int*,cpp> a(&i);  a.predec (  sync); }
// { volatile atomic<int*,cpp> a(&i);  a.postdec(  sync); }
// { volatile atomic<int*,cpp> a(&i);  a.add    (2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.sub    (2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.mul    (2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.div    (2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.mod    (2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.lshift (2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.rshift (2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.andeq  (2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.oreq   (2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.xoreq  (2,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.min    (&j,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.max    (&j,success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.inc    (  success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.preinc (  success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.postinc(  success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.dec    (  success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.predec (  success,failure); }
// { volatile atomic<int*,cpp> a(&i);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { volatile atomic<int*,kokkos> a(&i);  a.add    (2); }
// { volatile atomic<int*,kokkos> a(&i);  a.sub    (2); }
// { volatile atomic<int*,kokkos> a(&i);  a.mul    (2); }
// { volatile atomic<int*,kokkos> a(&i);  a.div    (2); }
// { volatile atomic<int*,kokkos> a(&i);  a.mod    (2); }
// { volatile atomic<int*,kokkos> a(&i);  a.lshift (2); }
// { volatile atomic<int*,kokkos> a(&i);  a.rshift (2); }
// { volatile atomic<int*,kokkos> a(&i);  a.andeq  (2); }
// { volatile atomic<int*,kokkos> a(&i);  a.oreq   (2); }
// { volatile atomic<int*,kokkos> a(&i);  a.xoreq  (2); }
// { volatile atomic<int*,kokkos> a(&i);  a.min    (&j); }
// { volatile atomic<int*,kokkos> a(&i);  a.max    (&j); }
// { volatile atomic<int*,kokkos> a(&i);  a.inc    ( ); }
// { volatile atomic<int*,kokkos> a(&i);  a.preinc ( ); }
// { volatile atomic<int*,kokkos> a(&i);  a.postinc( ); }
// { volatile atomic<int*,kokkos> a(&i);  a.dec    ( ); }
// { volatile atomic<int*,kokkos> a(&i);  a.predec ( ); }
// { volatile atomic<int*,kokkos> a(&i);  a.postdec( ); }
// { volatile atomic<int*,kokkos> a(&i);  a.add    (2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.sub    (2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.mul    (2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.div    (2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.mod    (2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.lshift (2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.rshift (2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.andeq  (2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.oreq   (2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.xoreq  (2,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.min    (&j,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.max    (&j,sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.inc    (  sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.preinc (  sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.postinc(  sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.dec    (  sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.predec (  sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.postdec(  sync); }
// { volatile atomic<int*,kokkos> a(&i);  a.add    (2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.sub    (2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.mul    (2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.div    (2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.mod    (2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.lshift (2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.rshift (2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.andeq  (2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.oreq   (2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.xoreq  (2,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.min    (&j,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.max    (&j,success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.inc    (  success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.preinc (  success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.postinc(  success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.dec    (  success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.predec (  success,failure); }
// { volatile atomic<int*,kokkos> a(&i);  a.postdec(  success,failure); }
#endif

   { volatile atomic<int*,strong> a(&i);  a.add    (2); }
   { volatile atomic<int*,strong> a(&i);  a.sub    (2); }
// { volatile atomic<int*,strong> a(&i);  a.mul    (2); }
// { volatile atomic<int*,strong> a(&i);  a.div    (2); }
// { volatile atomic<int*,strong> a(&i);  a.mod    (2); }
// { volatile atomic<int*,strong> a(&i);  a.lshift (2); }
// { volatile atomic<int*,strong> a(&i);  a.rshift (2); }
// { volatile atomic<int*,strong> a(&i);  a.andeq  (2); }
// { volatile atomic<int*,strong> a(&i);  a.oreq   (2); }
// { volatile atomic<int*,strong> a(&i);  a.xoreq  (2); }
   { volatile atomic<int*,strong> a(&i);  a.min    (&j); }
   { volatile atomic<int*,strong> a(&i);  a.max    (&j); }
   { volatile atomic<int*,strong> a(&i);  a.inc    ( ); }
   { volatile atomic<int*,strong> a(&i);  a.preinc ( ); }
   { volatile atomic<int*,strong> a(&i);  a.postinc( ); }
   { volatile atomic<int*,strong> a(&i);  a.dec    ( ); }
   { volatile atomic<int*,strong> a(&i);  a.predec ( ); }
   { volatile atomic<int*,strong> a(&i);  a.postdec( ); }
   { volatile atomic<int*,strong> a(&i);  a.add    (2,sync); }
   { volatile atomic<int*,strong> a(&i);  a.sub    (2,sync); }
// { volatile atomic<int*,strong> a(&i);  a.mul    (2,sync); }
// { volatile atomic<int*,strong> a(&i);  a.div    (2,sync); }
// { volatile atomic<int*,strong> a(&i);  a.mod    (2,sync); }
// { volatile atomic<int*,strong> a(&i);  a.lshift (2,sync); }
// { volatile atomic<int*,strong> a(&i);  a.rshift (2,sync); }
// { volatile atomic<int*,strong> a(&i);  a.andeq  (2,sync); }
// { volatile atomic<int*,strong> a(&i);  a.oreq   (2,sync); }
// { volatile atomic<int*,strong> a(&i);  a.xoreq  (2,sync); }
   { volatile atomic<int*,strong> a(&i);  a.min    (&j,sync); }
   { volatile atomic<int*,strong> a(&i);  a.max    (&j,sync); }
   { volatile atomic<int*,strong> a(&i);  a.inc    (  sync); }
   { volatile atomic<int*,strong> a(&i);  a.preinc (  sync); }
   { volatile atomic<int*,strong> a(&i);  a.postinc(  sync); }
   { volatile atomic<int*,strong> a(&i);  a.dec    (  sync); }
   { volatile atomic<int*,strong> a(&i);  a.predec (  sync); }
   { volatile atomic<int*,strong> a(&i);  a.postdec(  sync); }
   { volatile atomic<int*,strong> a(&i);  a.add    (2,success,failure); }
   { volatile atomic<int*,strong> a(&i);  a.sub    (2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  a.mul    (2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  a.div    (2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  a.mod    (2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  a.lshift (2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  a.rshift (2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  a.andeq  (2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  a.oreq   (2,success,failure); }
// { volatile atomic<int*,strong> a(&i);  a.xoreq  (2,success,failure); }
   { volatile atomic<int*,strong> a(&i);  a.min    (&j,success,failure); }
   { volatile atomic<int*,strong> a(&i);  a.max    (&j,success,failure); }
   { volatile atomic<int*,strong> a(&i);  a.inc    (  success,failure); }
   { volatile atomic<int*,strong> a(&i);  a.preinc (  success,failure); }
   { volatile atomic<int*,strong> a(&i);  a.postinc(  success,failure); }
   { volatile atomic<int*,strong> a(&i);  a.dec    (  success,failure); }
   { volatile atomic<int*,strong> a(&i);  a.predec (  success,failure); }
   { volatile atomic<int*,strong> a(&i);  a.postdec(  success,failure); }

   { volatile atomic<int*,strong::pun> a(&i);  a.add    (2); }
   { volatile atomic<int*,strong::pun> a(&i);  a.sub    (2); }
// { volatile atomic<int*,strong::pun> a(&i);  a.mul    (2); }
// { volatile atomic<int*,strong::pun> a(&i);  a.div    (2); }
// { volatile atomic<int*,strong::pun> a(&i);  a.mod    (2); }
// { volatile atomic<int*,strong::pun> a(&i);  a.lshift (2); }
// { volatile atomic<int*,strong::pun> a(&i);  a.rshift (2); }
// { volatile atomic<int*,strong::pun> a(&i);  a.andeq  (2); }
// { volatile atomic<int*,strong::pun> a(&i);  a.oreq   (2); }
// { volatile atomic<int*,strong::pun> a(&i);  a.xoreq  (2); }
   { volatile atomic<int*,strong::pun> a(&i);  a.min    (&j); }
   { volatile atomic<int*,strong::pun> a(&i);  a.max    (&j); }
   { volatile atomic<int*,strong::pun> a(&i);  a.inc    ( ); }
   { volatile atomic<int*,strong::pun> a(&i);  a.preinc ( ); }
   { volatile atomic<int*,strong::pun> a(&i);  a.postinc( ); }
   { volatile atomic<int*,strong::pun> a(&i);  a.dec    ( ); }
   { volatile atomic<int*,strong::pun> a(&i);  a.predec ( ); }
   { volatile atomic<int*,strong::pun> a(&i);  a.postdec( ); }
   { volatile atomic<int*,strong::pun> a(&i);  a.add    (2,sync); }
   { volatile atomic<int*,strong::pun> a(&i);  a.sub    (2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  a.mul    (2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  a.div    (2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  a.mod    (2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  a.lshift (2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  a.rshift (2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  a.andeq  (2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  a.oreq   (2,sync); }
// { volatile atomic<int*,strong::pun> a(&i);  a.xoreq  (2,sync); }
   { volatile atomic<int*,strong::pun> a(&i);  a.min    (&j,sync); }
   { volatile atomic<int*,strong::pun> a(&i);  a.max    (&j,sync); }
   { volatile atomic<int*,strong::pun> a(&i);  a.inc    (  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  a.preinc (  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  a.postinc(  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  a.dec    (  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  a.predec (  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  a.postdec(  sync); }
   { volatile atomic<int*,strong::pun> a(&i);  a.add    (2,success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  a.sub    (2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  a.mul    (2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  a.div    (2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  a.mod    (2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  a.lshift (2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  a.rshift (2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  a.andeq  (2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  a.oreq   (2,success,failure); }
// { volatile atomic<int*,strong::pun> a(&i);  a.xoreq  (2,success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  a.min    (&j,success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  a.max    (&j,success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  a.inc    (  success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  a.preinc (  success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  a.postinc(  success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  a.dec    (  success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  a.predec (  success,failure); }
   { volatile atomic<int*,strong::pun> a(&i);  a.postdec(  success,failure); }

   { volatile atomic<int*,weak> a(&i);  a.add    (2); }
   { volatile atomic<int*,weak> a(&i);  a.sub    (2); }
// { volatile atomic<int*,weak> a(&i);  a.mul    (2); }
// { volatile atomic<int*,weak> a(&i);  a.div    (2); }
// { volatile atomic<int*,weak> a(&i);  a.mod    (2); }
// { volatile atomic<int*,weak> a(&i);  a.lshift (2); }
// { volatile atomic<int*,weak> a(&i);  a.rshift (2); }
// { volatile atomic<int*,weak> a(&i);  a.andeq  (2); }
// { volatile atomic<int*,weak> a(&i);  a.oreq   (2); }
// { volatile atomic<int*,weak> a(&i);  a.xoreq  (2); }
   { volatile atomic<int*,weak> a(&i);  a.min    (&j); }
   { volatile atomic<int*,weak> a(&i);  a.max    (&j); }
   { volatile atomic<int*,weak> a(&i);  a.inc    ( ); }
   { volatile atomic<int*,weak> a(&i);  a.preinc ( ); }
   { volatile atomic<int*,weak> a(&i);  a.postinc( ); }
   { volatile atomic<int*,weak> a(&i);  a.dec    ( ); }
   { volatile atomic<int*,weak> a(&i);  a.predec ( ); }
   { volatile atomic<int*,weak> a(&i);  a.postdec( ); }
   { volatile atomic<int*,weak> a(&i);  a.add    (2,sync); }
   { volatile atomic<int*,weak> a(&i);  a.sub    (2,sync); }
// { volatile atomic<int*,weak> a(&i);  a.mul    (2,sync); }
// { volatile atomic<int*,weak> a(&i);  a.div    (2,sync); }
// { volatile atomic<int*,weak> a(&i);  a.mod    (2,sync); }
// { volatile atomic<int*,weak> a(&i);  a.lshift (2,sync); }
// { volatile atomic<int*,weak> a(&i);  a.rshift (2,sync); }
// { volatile atomic<int*,weak> a(&i);  a.andeq  (2,sync); }
// { volatile atomic<int*,weak> a(&i);  a.oreq   (2,sync); }
// { volatile atomic<int*,weak> a(&i);  a.xoreq  (2,sync); }
   { volatile atomic<int*,weak> a(&i);  a.min    (&j,sync); }
   { volatile atomic<int*,weak> a(&i);  a.max    (&j,sync); }
   { volatile atomic<int*,weak> a(&i);  a.inc    (  sync); }
   { volatile atomic<int*,weak> a(&i);  a.preinc (  sync); }
   { volatile atomic<int*,weak> a(&i);  a.postinc(  sync); }
   { volatile atomic<int*,weak> a(&i);  a.dec    (  sync); }
   { volatile atomic<int*,weak> a(&i);  a.predec (  sync); }
   { volatile atomic<int*,weak> a(&i);  a.postdec(  sync); }
   { volatile atomic<int*,weak> a(&i);  a.add    (2,success,failure); }
   { volatile atomic<int*,weak> a(&i);  a.sub    (2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  a.mul    (2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  a.div    (2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  a.mod    (2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  a.lshift (2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  a.rshift (2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  a.andeq  (2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  a.oreq   (2,success,failure); }
// { volatile atomic<int*,weak> a(&i);  a.xoreq  (2,success,failure); }
   { volatile atomic<int*,weak> a(&i);  a.min    (&j,success,failure); }
   { volatile atomic<int*,weak> a(&i);  a.max    (&j,success,failure); }
   { volatile atomic<int*,weak> a(&i);  a.inc    (  success,failure); }
   { volatile atomic<int*,weak> a(&i);  a.preinc (  success,failure); }
   { volatile atomic<int*,weak> a(&i);  a.postinc(  success,failure); }
   { volatile atomic<int*,weak> a(&i);  a.dec    (  success,failure); }
   { volatile atomic<int*,weak> a(&i);  a.predec (  success,failure); }
   { volatile atomic<int*,weak> a(&i);  a.postdec(  success,failure); }

   { volatile atomic<int*,weak::pun> a(&i);  a.add    (2); }
   { volatile atomic<int*,weak::pun> a(&i);  a.sub    (2); }
// { volatile atomic<int*,weak::pun> a(&i);  a.mul    (2); }
// { volatile atomic<int*,weak::pun> a(&i);  a.div    (2); }
// { volatile atomic<int*,weak::pun> a(&i);  a.mod    (2); }
// { volatile atomic<int*,weak::pun> a(&i);  a.lshift (2); }
// { volatile atomic<int*,weak::pun> a(&i);  a.rshift (2); }
// { volatile atomic<int*,weak::pun> a(&i);  a.andeq  (2); }
// { volatile atomic<int*,weak::pun> a(&i);  a.oreq   (2); }
// { volatile atomic<int*,weak::pun> a(&i);  a.xoreq  (2); }
   { volatile atomic<int*,weak::pun> a(&i);  a.min    (&j); }
   { volatile atomic<int*,weak::pun> a(&i);  a.max    (&j); }
   { volatile atomic<int*,weak::pun> a(&i);  a.inc    ( ); }
   { volatile atomic<int*,weak::pun> a(&i);  a.preinc ( ); }
   { volatile atomic<int*,weak::pun> a(&i);  a.postinc( ); }
   { volatile atomic<int*,weak::pun> a(&i);  a.dec    ( ); }
   { volatile atomic<int*,weak::pun> a(&i);  a.predec ( ); }
   { volatile atomic<int*,weak::pun> a(&i);  a.postdec( ); }
   { volatile atomic<int*,weak::pun> a(&i);  a.add    (2,sync); }
   { volatile atomic<int*,weak::pun> a(&i);  a.sub    (2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  a.mul    (2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  a.div    (2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  a.mod    (2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  a.lshift (2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  a.rshift (2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  a.andeq  (2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  a.oreq   (2,sync); }
// { volatile atomic<int*,weak::pun> a(&i);  a.xoreq  (2,sync); }
   { volatile atomic<int*,weak::pun> a(&i);  a.min    (&j,sync); }
   { volatile atomic<int*,weak::pun> a(&i);  a.max    (&j,sync); }
   { volatile atomic<int*,weak::pun> a(&i);  a.inc    (  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  a.preinc (  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  a.postinc(  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  a.dec    (  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  a.predec (  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  a.postdec(  sync); }
   { volatile atomic<int*,weak::pun> a(&i);  a.add    (2,success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  a.sub    (2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  a.mul    (2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  a.div    (2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  a.mod    (2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  a.lshift (2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  a.rshift (2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  a.andeq  (2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  a.oreq   (2,success,failure); }
// { volatile atomic<int*,weak::pun> a(&i);  a.xoreq  (2,success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  a.min    (&j,success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  a.max    (&j,success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  a.inc    (  success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  a.preinc (  success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  a.postinc(  success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  a.dec    (  success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  a.predec (  success,failure); }
   { volatile atomic<int*,weak::pun> a(&i);  a.postdec(  success,failure); }

   { volatile atomic<int*,lock> a(&i);  a.add    (2); }
   { volatile atomic<int*,lock> a(&i);  a.sub    (2); }
// { volatile atomic<int*,lock> a(&i);  a.mul    (2); }
// { volatile atomic<int*,lock> a(&i);  a.div    (2); }
// { volatile atomic<int*,lock> a(&i);  a.mod    (2); }
// { volatile atomic<int*,lock> a(&i);  a.lshift (2); }
// { volatile atomic<int*,lock> a(&i);  a.rshift (2); }
// { volatile atomic<int*,lock> a(&i);  a.andeq  (2); }
// { volatile atomic<int*,lock> a(&i);  a.oreq   (2); }
// { volatile atomic<int*,lock> a(&i);  a.xoreq  (2); }
   { volatile atomic<int*,lock> a(&i);  a.min    (&j); }
   { volatile atomic<int*,lock> a(&i);  a.max    (&j); }
   { volatile atomic<int*,lock> a(&i);  a.inc    ( ); }
   { volatile atomic<int*,lock> a(&i);  a.preinc ( ); }
   { volatile atomic<int*,lock> a(&i);  a.postinc( ); }
   { volatile atomic<int*,lock> a(&i);  a.dec    ( ); }
   { volatile atomic<int*,lock> a(&i);  a.predec ( ); }
   { volatile atomic<int*,lock> a(&i);  a.postdec( ); }
// { volatile atomic<int*,lock> a(&i);  a.add    (2,sync); }
// { volatile atomic<int*,lock> a(&i);  a.sub    (2,sync); }
// { volatile atomic<int*,lock> a(&i);  a.mul    (2,sync); }
// { volatile atomic<int*,lock> a(&i);  a.div    (2,sync); }
// { volatile atomic<int*,lock> a(&i);  a.mod    (2,sync); }
// { volatile atomic<int*,lock> a(&i);  a.lshift (2,sync); }
// { volatile atomic<int*,lock> a(&i);  a.rshift (2,sync); }
// { volatile atomic<int*,lock> a(&i);  a.andeq  (2,sync); }
// { volatile atomic<int*,lock> a(&i);  a.oreq   (2,sync); }
// { volatile atomic<int*,lock> a(&i);  a.xoreq  (2,sync); }
// { volatile atomic<int*,lock> a(&i);  a.min    (&j,sync); }
// { volatile atomic<int*,lock> a(&i);  a.max    (&j,sync); }
// { volatile atomic<int*,lock> a(&i);  a.inc    (  sync); }
// { volatile atomic<int*,lock> a(&i);  a.preinc (  sync); }
// { volatile atomic<int*,lock> a(&i);  a.postinc(  sync); }
// { volatile atomic<int*,lock> a(&i);  a.dec    (  sync); }
// { volatile atomic<int*,lock> a(&i);  a.predec (  sync); }
// { volatile atomic<int*,lock> a(&i);  a.postdec(  sync); }
// { volatile atomic<int*,lock> a(&i);  a.add    (2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.sub    (2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.mul    (2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.div    (2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.mod    (2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.lshift (2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.rshift (2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.andeq  (2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.oreq   (2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.xoreq  (2,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.min    (&j,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.max    (&j,success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.inc    (  success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.preinc (  success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.postinc(  success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.dec    (  success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.predec (  success,failure); }
// { volatile atomic<int*,lock> a(&i);  a.postdec(  success,failure); }

   { volatile atomic<int*,serial> a(&i);  a.add    (2); }
   { volatile atomic<int*,serial> a(&i);  a.sub    (2); }
// { volatile atomic<int*,serial> a(&i);  a.mul    (2); }
// { volatile atomic<int*,serial> a(&i);  a.div    (2); }
// { volatile atomic<int*,serial> a(&i);  a.mod    (2); }
// { volatile atomic<int*,serial> a(&i);  a.lshift (2); }
// { volatile atomic<int*,serial> a(&i);  a.rshift (2); }
// { volatile atomic<int*,serial> a(&i);  a.andeq  (2); }
// { volatile atomic<int*,serial> a(&i);  a.oreq   (2); }
// { volatile atomic<int*,serial> a(&i);  a.xoreq  (2); }
   { volatile atomic<int*,serial> a(&i);  a.min    (&j); }
   { volatile atomic<int*,serial> a(&i);  a.max    (&j); }
   { volatile atomic<int*,serial> a(&i);  a.inc    ( ); }
   { volatile atomic<int*,serial> a(&i);  a.preinc ( ); }
   { volatile atomic<int*,serial> a(&i);  a.postinc( ); }
   { volatile atomic<int*,serial> a(&i);  a.dec    ( ); }
   { volatile atomic<int*,serial> a(&i);  a.predec ( ); }
   { volatile atomic<int*,serial> a(&i);  a.postdec( ); }
// { volatile atomic<int*,serial> a(&i);  a.add    (2,sync); }
// { volatile atomic<int*,serial> a(&i);  a.sub    (2,sync); }
// { volatile atomic<int*,serial> a(&i);  a.mul    (2,sync); }
// { volatile atomic<int*,serial> a(&i);  a.div    (2,sync); }
// { volatile atomic<int*,serial> a(&i);  a.mod    (2,sync); }
// { volatile atomic<int*,serial> a(&i);  a.lshift (2,sync); }
// { volatile atomic<int*,serial> a(&i);  a.rshift (2,sync); }
// { volatile atomic<int*,serial> a(&i);  a.andeq  (2,sync); }
// { volatile atomic<int*,serial> a(&i);  a.oreq   (2,sync); }
// { volatile atomic<int*,serial> a(&i);  a.xoreq  (2,sync); }
// { volatile atomic<int*,serial> a(&i);  a.min    (&j,sync); }
// { volatile atomic<int*,serial> a(&i);  a.max    (&j,sync); }
// { volatile atomic<int*,serial> a(&i);  a.inc    (  sync); }
// { volatile atomic<int*,serial> a(&i);  a.preinc (  sync); }
// { volatile atomic<int*,serial> a(&i);  a.postinc(  sync); }
// { volatile atomic<int*,serial> a(&i);  a.dec    (  sync); }
// { volatile atomic<int*,serial> a(&i);  a.predec (  sync); }
// { volatile atomic<int*,serial> a(&i);  a.postdec(  sync); }
// { volatile atomic<int*,serial> a(&i);  a.add    (2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.sub    (2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.mul    (2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.div    (2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.mod    (2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.lshift (2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.rshift (2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.andeq  (2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.oreq   (2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.xoreq  (2,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.min    (&j,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.max    (&j,success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.inc    (  success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.preinc (  success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.postinc(  success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.dec    (  success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.predec (  success,failure); }
// { volatile atomic<int*,serial> a(&i);  a.postdec(  success,failure); }
#endif



   // ------------------------
   // std::complex
   // ------------------------

// { volatile atomic<cmplx,cpp> a(0);  a.add    (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.sub    (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.mul    (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.div    (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.mod    (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.lshift (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.rshift (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.andeq  (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.oreq   (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.xoreq  (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.min    (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.max    (c); }
// { volatile atomic<cmplx,cpp> a(0);  a.inc    ( ); }
// { volatile atomic<cmplx,cpp> a(0);  a.preinc ( ); }
// { volatile atomic<cmplx,cpp> a(0);  a.postinc( ); }
// { volatile atomic<cmplx,cpp> a(0);  a.dec    ( ); }
// { volatile atomic<cmplx,cpp> a(0);  a.predec ( ); }
// { volatile atomic<cmplx,cpp> a(0);  a.postdec( ); }
// { volatile atomic<cmplx,cpp> a(0);  a.add    (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.sub    (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.mul    (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.div    (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.mod    (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.lshift (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.rshift (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.andeq  (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.oreq   (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.xoreq  (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.min    (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.max    (c,sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.inc    (  sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.preinc (  sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.postinc(  sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.dec    (  sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.predec (  sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.postdec(  sync); }
// { volatile atomic<cmplx,cpp> a(0);  a.add    (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.sub    (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.mul    (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.div    (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.mod    (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.lshift (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.rshift (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.andeq  (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.oreq   (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.xoreq  (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.min    (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.max    (c,success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.inc    (  success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.preinc (  success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.postinc(  success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.dec    (  success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.predec (  success,failure); }
// { volatile atomic<cmplx,cpp> a(0);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { volatile atomic<cmplx,kokkos> a(0);  a.add    (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.sub    (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.mul    (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.div    (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.mod    (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.lshift (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.rshift (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.andeq  (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.oreq   (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.xoreq  (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.min    (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.max    (c); }
// { volatile atomic<cmplx,kokkos> a(0);  a.inc    ( ); }
// { volatile atomic<cmplx,kokkos> a(0);  a.preinc ( ); }
// { volatile atomic<cmplx,kokkos> a(0);  a.postinc( ); }
// { volatile atomic<cmplx,kokkos> a(0);  a.dec    ( ); }
// { volatile atomic<cmplx,kokkos> a(0);  a.predec ( ); }
// { volatile atomic<cmplx,kokkos> a(0);  a.postdec( ); }
// { volatile atomic<cmplx,kokkos> a(0);  a.add    (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.sub    (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.mul    (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.div    (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.mod    (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.lshift (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.rshift (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.andeq  (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.oreq   (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.xoreq  (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.min    (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.max    (c,sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.inc    (  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.preinc (  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.postinc(  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.dec    (  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.predec (  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.postdec(  sync); }
// { volatile atomic<cmplx,kokkos> a(0);  a.add    (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.sub    (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.mul    (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.div    (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.mod    (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.lshift (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.rshift (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.andeq  (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.oreq   (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.xoreq  (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.min    (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.max    (c,success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.inc    (  success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.preinc (  success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.postinc(  success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.dec    (  success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.predec (  success,failure); }
// { volatile atomic<cmplx,kokkos> a(0);  a.postdec(  success,failure); }
#endif

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong> a(0);  a.add    (c); }
   { volatile atomic<cmplx,strong> a(0);  a.sub    (c); }
   { volatile atomic<cmplx,strong> a(0);  a.mul    (c); }
   { volatile atomic<cmplx,strong> a(0);  a.div    (c); }
#endif
// { volatile atomic<cmplx,strong> a(0);  a.mod    (c); }
// { volatile atomic<cmplx,strong> a(0);  a.lshift (c); }
// { volatile atomic<cmplx,strong> a(0);  a.rshift (c); }
// { volatile atomic<cmplx,strong> a(0);  a.andeq  (c); }
// { volatile atomic<cmplx,strong> a(0);  a.oreq   (c); }
// { volatile atomic<cmplx,strong> a(0);  a.xoreq  (c); }
// { volatile atomic<cmplx,strong> a(0);  a.min    (c); }
// { volatile atomic<cmplx,strong> a(0);  a.max    (c); }
// { volatile atomic<cmplx,strong> a(0);  a.inc    ( ); }
// { volatile atomic<cmplx,strong> a(0);  a.preinc ( ); }
// { volatile atomic<cmplx,strong> a(0);  a.postinc( ); }
// { volatile atomic<cmplx,strong> a(0);  a.dec    ( ); }
// { volatile atomic<cmplx,strong> a(0);  a.predec ( ); }
// { volatile atomic<cmplx,strong> a(0);  a.postdec( ); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong> a(0);  a.add    (c,sync); }
   { volatile atomic<cmplx,strong> a(0);  a.sub    (c,sync); }
   { volatile atomic<cmplx,strong> a(0);  a.mul    (c,sync); }
   { volatile atomic<cmplx,strong> a(0);  a.div    (c,sync); }
#endif
// { volatile atomic<cmplx,strong> a(0);  a.mod    (c,sync); }
// { volatile atomic<cmplx,strong> a(0);  a.lshift (c,sync); }
// { volatile atomic<cmplx,strong> a(0);  a.rshift (c,sync); }
// { volatile atomic<cmplx,strong> a(0);  a.andeq  (c,sync); }
// { volatile atomic<cmplx,strong> a(0);  a.oreq   (c,sync); }
// { volatile atomic<cmplx,strong> a(0);  a.xoreq  (c,sync); }
// { volatile atomic<cmplx,strong> a(0);  a.min    (c,sync); }
// { volatile atomic<cmplx,strong> a(0);  a.max    (c,sync); }
// { volatile atomic<cmplx,strong> a(0);  a.inc    (  sync); }
// { volatile atomic<cmplx,strong> a(0);  a.preinc (  sync); }
// { volatile atomic<cmplx,strong> a(0);  a.postinc(  sync); }
// { volatile atomic<cmplx,strong> a(0);  a.dec    (  sync); }
// { volatile atomic<cmplx,strong> a(0);  a.predec (  sync); }
// { volatile atomic<cmplx,strong> a(0);  a.postdec(  sync); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong> a(0);  a.add    (c,success,failure); }
   { volatile atomic<cmplx,strong> a(0);  a.sub    (c,success,failure); }
   { volatile atomic<cmplx,strong> a(0);  a.mul    (c,success,failure); }
   { volatile atomic<cmplx,strong> a(0);  a.div    (c,success,failure); }
#endif
// { volatile atomic<cmplx,strong> a(0);  a.mod    (c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.lshift (c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.rshift (c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.andeq  (c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.oreq   (c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.xoreq  (c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.min    (c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.max    (c,success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.inc    (  success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.preinc (  success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.postinc(  success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.dec    (  success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.predec (  success,failure); }
// { volatile atomic<cmplx,strong> a(0);  a.postdec(  success,failure); }

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong::pun> a(0);  a.add    (c); }
   { volatile atomic<cmplx,strong::pun> a(0);  a.sub    (c); }
   { volatile atomic<cmplx,strong::pun> a(0);  a.mul    (c); }
   { volatile atomic<cmplx,strong::pun> a(0);  a.div    (c); }
#endif
// { volatile atomic<cmplx,strong::pun> a(0);  a.mod    (c); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.lshift (c); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.rshift (c); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.andeq  (c); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.oreq   (c); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.xoreq  (c); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.min    (c); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.max    (c); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.inc    ( ); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.preinc ( ); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.postinc( ); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.dec    ( ); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.predec ( ); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.postdec( ); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong::pun> a(0);  a.add    (c,sync); }
   { volatile atomic<cmplx,strong::pun> a(0);  a.sub    (c,sync); }
   { volatile atomic<cmplx,strong::pun> a(0);  a.mul    (c,sync); }
   { volatile atomic<cmplx,strong::pun> a(0);  a.div    (c,sync); }
#endif
// { volatile atomic<cmplx,strong::pun> a(0);  a.mod    (c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.lshift (c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.rshift (c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.andeq  (c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.oreq   (c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.xoreq  (c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.min    (c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.max    (c,sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.inc    (  sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.preinc (  sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.postinc(  sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.dec    (  sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.predec (  sync); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.postdec(  sync); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,strong::pun> a(0);  a.add    (c,success,failure); }
   { volatile atomic<cmplx,strong::pun> a(0);  a.sub    (c,success,failure); }
   { volatile atomic<cmplx,strong::pun> a(0);  a.mul    (c,success,failure); }
   { volatile atomic<cmplx,strong::pun> a(0);  a.div    (c,success,failure); }
#endif
// { volatile atomic<cmplx,strong::pun> a(0);  a.mod    (c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.lshift (c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.rshift (c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.andeq  (c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.oreq   (c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.xoreq  (c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.min    (c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.max    (c,success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.inc    (  success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.preinc (  success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.postinc(  success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.dec    (  success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.predec (  success,failure); }
// { volatile atomic<cmplx,strong::pun> a(0);  a.postdec(  success,failure); }

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak> a(0);  a.add    (c); }
   { volatile atomic<cmplx,weak> a(0);  a.sub    (c); }
   { volatile atomic<cmplx,weak> a(0);  a.mul    (c); }
   { volatile atomic<cmplx,weak> a(0);  a.div    (c); }
#endif
// { volatile atomic<cmplx,weak> a(0);  a.mod    (c); }
// { volatile atomic<cmplx,weak> a(0);  a.lshift (c); }
// { volatile atomic<cmplx,weak> a(0);  a.rshift (c); }
// { volatile atomic<cmplx,weak> a(0);  a.andeq  (c); }
// { volatile atomic<cmplx,weak> a(0);  a.oreq   (c); }
// { volatile atomic<cmplx,weak> a(0);  a.xoreq  (c); }
// { volatile atomic<cmplx,weak> a(0);  a.min    (c); }
// { volatile atomic<cmplx,weak> a(0);  a.max    (c); }
// { volatile atomic<cmplx,weak> a(0);  a.inc    ( ); }
// { volatile atomic<cmplx,weak> a(0);  a.preinc ( ); }
// { volatile atomic<cmplx,weak> a(0);  a.postinc( ); }
// { volatile atomic<cmplx,weak> a(0);  a.dec    ( ); }
// { volatile atomic<cmplx,weak> a(0);  a.predec ( ); }
// { volatile atomic<cmplx,weak> a(0);  a.postdec( ); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak> a(0);  a.add    (c,sync); }
   { volatile atomic<cmplx,weak> a(0);  a.sub    (c,sync); }
   { volatile atomic<cmplx,weak> a(0);  a.mul    (c,sync); }
   { volatile atomic<cmplx,weak> a(0);  a.div    (c,sync); }
#endif
// { volatile atomic<cmplx,weak> a(0);  a.mod    (c,sync); }
// { volatile atomic<cmplx,weak> a(0);  a.lshift (c,sync); }
// { volatile atomic<cmplx,weak> a(0);  a.rshift (c,sync); }
// { volatile atomic<cmplx,weak> a(0);  a.andeq  (c,sync); }
// { volatile atomic<cmplx,weak> a(0);  a.oreq   (c,sync); }
// { volatile atomic<cmplx,weak> a(0);  a.xoreq  (c,sync); }
// { volatile atomic<cmplx,weak> a(0);  a.min    (c,sync); }
// { volatile atomic<cmplx,weak> a(0);  a.max    (c,sync); }
// { volatile atomic<cmplx,weak> a(0);  a.inc    (  sync); }
// { volatile atomic<cmplx,weak> a(0);  a.preinc (  sync); }
// { volatile atomic<cmplx,weak> a(0);  a.postinc(  sync); }
// { volatile atomic<cmplx,weak> a(0);  a.dec    (  sync); }
// { volatile atomic<cmplx,weak> a(0);  a.predec (  sync); }
// { volatile atomic<cmplx,weak> a(0);  a.postdec(  sync); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak> a(0);  a.add    (c,success,failure); }
   { volatile atomic<cmplx,weak> a(0);  a.sub    (c,success,failure); }
   { volatile atomic<cmplx,weak> a(0);  a.mul    (c,success,failure); }
   { volatile atomic<cmplx,weak> a(0);  a.div    (c,success,failure); }
#endif
// { volatile atomic<cmplx,weak> a(0);  a.mod    (c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.lshift (c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.rshift (c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.andeq  (c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.oreq   (c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.xoreq  (c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.min    (c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.max    (c,success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.inc    (  success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.preinc (  success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.postinc(  success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.dec    (  success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.predec (  success,failure); }
// { volatile atomic<cmplx,weak> a(0);  a.postdec(  success,failure); }

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak::pun> a(0);  a.add    (c); }
   { volatile atomic<cmplx,weak::pun> a(0);  a.sub    (c); }
   { volatile atomic<cmplx,weak::pun> a(0);  a.mul    (c); }
   { volatile atomic<cmplx,weak::pun> a(0);  a.div    (c); }
#endif
// { volatile atomic<cmplx,weak::pun> a(0);  a.mod    (c); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.lshift (c); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.rshift (c); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.andeq  (c); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.oreq   (c); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.xoreq  (c); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.min    (c); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.max    (c); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.inc    ( ); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.preinc ( ); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.postinc( ); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.dec    ( ); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.predec ( ); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.postdec( ); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak::pun> a(0);  a.add    (c,sync); }
   { volatile atomic<cmplx,weak::pun> a(0);  a.sub    (c,sync); }
   { volatile atomic<cmplx,weak::pun> a(0);  a.mul    (c,sync); }
   { volatile atomic<cmplx,weak::pun> a(0);  a.div    (c,sync); }
#endif
// { volatile atomic<cmplx,weak::pun> a(0);  a.mod    (c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.lshift (c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.rshift (c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.andeq  (c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.oreq   (c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.xoreq  (c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.min    (c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.max    (c,sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.inc    (  sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.preinc (  sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.postinc(  sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.dec    (  sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.predec (  sync); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.postdec(  sync); }
#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<cmplx,weak::pun> a(0);  a.add    (c,success,failure); }
   { volatile atomic<cmplx,weak::pun> a(0);  a.sub    (c,success,failure); }
   { volatile atomic<cmplx,weak::pun> a(0);  a.mul    (c,success,failure); }
   { volatile atomic<cmplx,weak::pun> a(0);  a.div    (c,success,failure); }
#endif
// { volatile atomic<cmplx,weak::pun> a(0);  a.mod    (c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.lshift (c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.rshift (c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.andeq  (c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.oreq   (c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.xoreq  (c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.min    (c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.max    (c,success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.inc    (  success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.preinc (  success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.postinc(  success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.dec    (  success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.predec (  success,failure); }
// { volatile atomic<cmplx,weak::pun> a(0);  a.postdec(  success,failure); }

//v{ volatile atomic<cmplx,lock> a(0);  a.add    (c); }
//v{ volatile atomic<cmplx,lock> a(0);  a.sub    (c); }
//v{ volatile atomic<cmplx,lock> a(0);  a.mul    (c); }
//v{ volatile atomic<cmplx,lock> a(0);  a.div    (c); }
// { volatile atomic<cmplx,lock> a(0);  a.mod    (c); }
// { volatile atomic<cmplx,lock> a(0);  a.lshift (c); }
// { volatile atomic<cmplx,lock> a(0);  a.rshift (c); }
// { volatile atomic<cmplx,lock> a(0);  a.andeq  (c); }
// { volatile atomic<cmplx,lock> a(0);  a.oreq   (c); }
// { volatile atomic<cmplx,lock> a(0);  a.xoreq  (c); }
// { volatile atomic<cmplx,lock> a(0);  a.min    (c); }
// { volatile atomic<cmplx,lock> a(0);  a.max    (c); }
// { volatile atomic<cmplx,lock> a(0);  a.inc    ( ); }
// { volatile atomic<cmplx,lock> a(0);  a.preinc ( ); }
// { volatile atomic<cmplx,lock> a(0);  a.postinc( ); }
// { volatile atomic<cmplx,lock> a(0);  a.dec    ( ); }
// { volatile atomic<cmplx,lock> a(0);  a.predec ( ); }
// { volatile atomic<cmplx,lock> a(0);  a.postdec( ); }
// { volatile atomic<cmplx,lock> a(0);  a.add    (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.sub    (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.mul    (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.div    (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.mod    (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.lshift (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.rshift (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.andeq  (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.oreq   (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.xoreq  (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.min    (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.max    (c,sync); }
// { volatile atomic<cmplx,lock> a(0);  a.inc    (  sync); }
// { volatile atomic<cmplx,lock> a(0);  a.preinc (  sync); }
// { volatile atomic<cmplx,lock> a(0);  a.postinc(  sync); }
// { volatile atomic<cmplx,lock> a(0);  a.dec    (  sync); }
// { volatile atomic<cmplx,lock> a(0);  a.predec (  sync); }
// { volatile atomic<cmplx,lock> a(0);  a.postdec(  sync); }
// { volatile atomic<cmplx,lock> a(0);  a.add    (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.sub    (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.mul    (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.div    (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.mod    (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.lshift (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.rshift (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.andeq  (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.oreq   (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.xoreq  (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.min    (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.max    (c,success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.inc    (  success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.preinc (  success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.postinc(  success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.dec    (  success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.predec (  success,failure); }
// { volatile atomic<cmplx,lock> a(0);  a.postdec(  success,failure); }

//v{ volatile atomic<cmplx,serial> a(0);  a.add    (c); }
//v{ volatile atomic<cmplx,serial> a(0);  a.sub    (c); }
//v{ volatile atomic<cmplx,serial> a(0);  a.mul    (c); }
//v{ volatile atomic<cmplx,serial> a(0);  a.div    (c); }
// { volatile atomic<cmplx,serial> a(0);  a.mod    (c); }
// { volatile atomic<cmplx,serial> a(0);  a.lshift (c); }
// { volatile atomic<cmplx,serial> a(0);  a.rshift (c); }
// { volatile atomic<cmplx,serial> a(0);  a.andeq  (c); }
// { volatile atomic<cmplx,serial> a(0);  a.oreq   (c); }
// { volatile atomic<cmplx,serial> a(0);  a.xoreq  (c); }
// { volatile atomic<cmplx,serial> a(0);  a.min    (c); }
// { volatile atomic<cmplx,serial> a(0);  a.max    (c); }
// { volatile atomic<cmplx,serial> a(0);  a.inc    ( ); }
// { volatile atomic<cmplx,serial> a(0);  a.preinc ( ); }
// { volatile atomic<cmplx,serial> a(0);  a.postinc( ); }
// { volatile atomic<cmplx,serial> a(0);  a.dec    ( ); }
// { volatile atomic<cmplx,serial> a(0);  a.predec ( ); }
// { volatile atomic<cmplx,serial> a(0);  a.postdec( ); }
// { volatile atomic<cmplx,serial> a(0);  a.add    (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.sub    (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.mul    (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.div    (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.mod    (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.lshift (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.rshift (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.andeq  (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.oreq   (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.xoreq  (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.min    (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.max    (c,sync); }
// { volatile atomic<cmplx,serial> a(0);  a.inc    (  sync); }
// { volatile atomic<cmplx,serial> a(0);  a.preinc (  sync); }
// { volatile atomic<cmplx,serial> a(0);  a.postinc(  sync); }
// { volatile atomic<cmplx,serial> a(0);  a.dec    (  sync); }
// { volatile atomic<cmplx,serial> a(0);  a.predec (  sync); }
// { volatile atomic<cmplx,serial> a(0);  a.postdec(  sync); }
// { volatile atomic<cmplx,serial> a(0);  a.add    (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.sub    (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.mul    (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.div    (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.mod    (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.lshift (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.rshift (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.andeq  (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.oreq   (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.xoreq  (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.min    (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.max    (c,success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.inc    (  success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.preinc (  success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.postinc(  success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.dec    (  success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.predec (  success,failure); }
// { volatile atomic<cmplx,serial> a(0);  a.postdec(  success,failure); }



   // ------------------------
   // foo
   // ------------------------

// { volatile atomic<foo,cpp> a(0);  a.add    (b); }
// { volatile atomic<foo,cpp> a(0);  a.sub    (b); }
// { volatile atomic<foo,cpp> a(0);  a.mul    (b); }
// { volatile atomic<foo,cpp> a(0);  a.div    (b); }
// { volatile atomic<foo,cpp> a(0);  a.mod    (b); }
// { volatile atomic<foo,cpp> a(0);  a.lshift (b); }
// { volatile atomic<foo,cpp> a(0);  a.rshift (b); }
// { volatile atomic<foo,cpp> a(0);  a.andeq  (b); }
// { volatile atomic<foo,cpp> a(0);  a.oreq   (b); }
// { volatile atomic<foo,cpp> a(0);  a.xoreq  (b); }
// { volatile atomic<foo,cpp> a(0);  a.min    (b); }
// { volatile atomic<foo,cpp> a(0);  a.max    (b); }
// { volatile atomic<foo,cpp> a(0);  a.inc    ( ); }
// { volatile atomic<foo,cpp> a(0);  a.preinc ( ); }
// { volatile atomic<foo,cpp> a(0);  a.postinc( ); }
// { volatile atomic<foo,cpp> a(0);  a.dec    ( ); }
// { volatile atomic<foo,cpp> a(0);  a.predec ( ); }
// { volatile atomic<foo,cpp> a(0);  a.postdec( ); }
// { volatile atomic<foo,cpp> a(0);  a.add    (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.sub    (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.mul    (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.div    (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.mod    (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.lshift (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.rshift (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.andeq  (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.oreq   (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.xoreq  (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.min    (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.max    (b,sync); }
// { volatile atomic<foo,cpp> a(0);  a.inc    (  sync); }
// { volatile atomic<foo,cpp> a(0);  a.preinc (  sync); }
// { volatile atomic<foo,cpp> a(0);  a.postinc(  sync); }
// { volatile atomic<foo,cpp> a(0);  a.dec    (  sync); }
// { volatile atomic<foo,cpp> a(0);  a.predec (  sync); }
// { volatile atomic<foo,cpp> a(0);  a.postdec(  sync); }
// { volatile atomic<foo,cpp> a(0);  a.add    (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.sub    (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.mul    (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.div    (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.mod    (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.lshift (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.rshift (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.andeq  (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.oreq   (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.xoreq  (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.min    (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.max    (b,success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.inc    (  success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.preinc (  success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.postinc(  success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.dec    (  success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.predec (  success,failure); }
// { volatile atomic<foo,cpp> a(0);  a.postdec(  success,failure); }

#if defined(ATOMICS_KOKKOS)
// { volatile atomic<foo,kokkos> a(0);  a.add    (b); }
// { volatile atomic<foo,kokkos> a(0);  a.sub    (b); }
// { volatile atomic<foo,kokkos> a(0);  a.mul    (b); }
// { volatile atomic<foo,kokkos> a(0);  a.div    (b); }
// { volatile atomic<foo,kokkos> a(0);  a.mod    (b); }
// { volatile atomic<foo,kokkos> a(0);  a.lshift (b); }
// { volatile atomic<foo,kokkos> a(0);  a.rshift (b); }
// { volatile atomic<foo,kokkos> a(0);  a.andeq  (b); }
// { volatile atomic<foo,kokkos> a(0);  a.oreq   (b); }
// { volatile atomic<foo,kokkos> a(0);  a.xoreq  (b); }
// { volatile atomic<foo,kokkos> a(0);  a.min    (b); }
// { volatile atomic<foo,kokkos> a(0);  a.max    (b); }
// { volatile atomic<foo,kokkos> a(0);  a.inc    ( ); }
// { volatile atomic<foo,kokkos> a(0);  a.preinc ( ); }
// { volatile atomic<foo,kokkos> a(0);  a.postinc( ); }
// { volatile atomic<foo,kokkos> a(0);  a.dec    ( ); }
// { volatile atomic<foo,kokkos> a(0);  a.predec ( ); }
// { volatile atomic<foo,kokkos> a(0);  a.postdec( ); }
// { volatile atomic<foo,kokkos> a(0);  a.add    (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.sub    (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.mul    (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.div    (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.mod    (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.lshift (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.rshift (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.andeq  (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.oreq   (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.xoreq  (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.min    (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.max    (b,sync); }
// { volatile atomic<foo,kokkos> a(0);  a.inc    (  sync); }
// { volatile atomic<foo,kokkos> a(0);  a.preinc (  sync); }
// { volatile atomic<foo,kokkos> a(0);  a.postinc(  sync); }
// { volatile atomic<foo,kokkos> a(0);  a.dec    (  sync); }
// { volatile atomic<foo,kokkos> a(0);  a.predec (  sync); }
// { volatile atomic<foo,kokkos> a(0);  a.postdec(  sync); }
// { volatile atomic<foo,kokkos> a(0);  a.add    (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.sub    (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.mul    (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.div    (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.mod    (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.lshift (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.rshift (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.andeq  (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.oreq   (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.xoreq  (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.min    (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.max    (b,success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.inc    (  success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.preinc (  success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.postinc(  success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.dec    (  success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.predec (  success,failure); }
// { volatile atomic<foo,kokkos> a(0);  a.postdec(  success,failure); }
#endif

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,strong> a(0);  a.add    (b); }
   { volatile atomic<foo,strong> a(0);  a.sub    (b); }
   { volatile atomic<foo,strong> a(0);  a.mul    (b); }
   { volatile atomic<foo,strong> a(0);  a.div    (b); }
   { volatile atomic<foo,strong> a(0);  a.mod    (b); }
   { volatile atomic<foo,strong> a(0);  a.lshift (b); }
   { volatile atomic<foo,strong> a(0);  a.rshift (b); }
   { volatile atomic<foo,strong> a(0);  a.andeq  (b); }
   { volatile atomic<foo,strong> a(0);  a.oreq   (b); }
   { volatile atomic<foo,strong> a(0);  a.xoreq  (b); }
   { volatile atomic<foo,strong> a(0);  a.min    (b); }
   { volatile atomic<foo,strong> a(0);  a.max    (b); }
   { volatile atomic<foo,strong> a(0);  a.inc    ( ); }
   { volatile atomic<foo,strong> a(0);  a.preinc ( ); }
   { volatile atomic<foo,strong> a(0);  a.postinc( ); }
   { volatile atomic<foo,strong> a(0);  a.dec    ( ); }
   { volatile atomic<foo,strong> a(0);  a.predec ( ); }
   { volatile atomic<foo,strong> a(0);  a.postdec( ); }
   { volatile atomic<foo,strong> a(0);  a.add    (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.sub    (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.mul    (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.div    (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.mod    (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.lshift (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.rshift (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.andeq  (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.oreq   (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.xoreq  (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.min    (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.max    (b,sync); }
   { volatile atomic<foo,strong> a(0);  a.inc    (  sync); }
   { volatile atomic<foo,strong> a(0);  a.preinc (  sync); }
   { volatile atomic<foo,strong> a(0);  a.postinc(  sync); }
   { volatile atomic<foo,strong> a(0);  a.dec    (  sync); }
   { volatile atomic<foo,strong> a(0);  a.predec (  sync); }
   { volatile atomic<foo,strong> a(0);  a.postdec(  sync); }
   { volatile atomic<foo,strong> a(0);  a.add    (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.sub    (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.mul    (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.div    (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.mod    (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.lshift (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.rshift (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.andeq  (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.oreq   (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.xoreq  (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.min    (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.max    (b,success,failure); }
   { volatile atomic<foo,strong> a(0);  a.inc    (  success,failure); }
   { volatile atomic<foo,strong> a(0);  a.preinc (  success,failure); }
   { volatile atomic<foo,strong> a(0);  a.postinc(  success,failure); }
   { volatile atomic<foo,strong> a(0);  a.dec    (  success,failure); }
   { volatile atomic<foo,strong> a(0);  a.predec (  success,failure); }
   { volatile atomic<foo,strong> a(0);  a.postdec(  success,failure); }
#endif

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,strong::pun> a(0);  a.add    (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.sub    (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.mul    (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.div    (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.mod    (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.lshift (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.rshift (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.andeq  (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.oreq   (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.xoreq  (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.min    (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.max    (b); }
   { volatile atomic<foo,strong::pun> a(0);  a.inc    ( ); }
   { volatile atomic<foo,strong::pun> a(0);  a.preinc ( ); }
   { volatile atomic<foo,strong::pun> a(0);  a.postinc( ); }
   { volatile atomic<foo,strong::pun> a(0);  a.dec    ( ); }
   { volatile atomic<foo,strong::pun> a(0);  a.predec ( ); }
   { volatile atomic<foo,strong::pun> a(0);  a.postdec( ); }
   { volatile atomic<foo,strong::pun> a(0);  a.add    (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.sub    (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.mul    (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.div    (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.mod    (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.lshift (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.rshift (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.andeq  (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.oreq   (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.xoreq  (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.min    (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.max    (b,sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.inc    (  sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.preinc (  sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.postinc(  sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.dec    (  sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.predec (  sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.postdec(  sync); }
   { volatile atomic<foo,strong::pun> a(0);  a.add    (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.sub    (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.mul    (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.div    (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.mod    (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.lshift (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.rshift (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.andeq  (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.oreq   (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.xoreq  (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.min    (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.max    (b,success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.inc    (  success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.preinc (  success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.postinc(  success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.dec    (  success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.predec (  success,failure); }
   { volatile atomic<foo,strong::pun> a(0);  a.postdec(  success,failure); }
#endif

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,weak> a(0);  a.add    (b); }
   { volatile atomic<foo,weak> a(0);  a.sub    (b); }
   { volatile atomic<foo,weak> a(0);  a.mul    (b); }
   { volatile atomic<foo,weak> a(0);  a.div    (b); }
   { volatile atomic<foo,weak> a(0);  a.mod    (b); }
   { volatile atomic<foo,weak> a(0);  a.lshift (b); }
   { volatile atomic<foo,weak> a(0);  a.rshift (b); }
   { volatile atomic<foo,weak> a(0);  a.andeq  (b); }
   { volatile atomic<foo,weak> a(0);  a.oreq   (b); }
   { volatile atomic<foo,weak> a(0);  a.xoreq  (b); }
   { volatile atomic<foo,weak> a(0);  a.min    (b); }
   { volatile atomic<foo,weak> a(0);  a.max    (b); }
   { volatile atomic<foo,weak> a(0);  a.inc    ( ); }
   { volatile atomic<foo,weak> a(0);  a.preinc ( ); }
   { volatile atomic<foo,weak> a(0);  a.postinc( ); }
   { volatile atomic<foo,weak> a(0);  a.dec    ( ); }
   { volatile atomic<foo,weak> a(0);  a.predec ( ); }
   { volatile atomic<foo,weak> a(0);  a.postdec( ); }
   { volatile atomic<foo,weak> a(0);  a.add    (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.sub    (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.mul    (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.div    (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.mod    (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.lshift (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.rshift (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.andeq  (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.oreq   (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.xoreq  (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.min    (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.max    (b,sync); }
   { volatile atomic<foo,weak> a(0);  a.inc    (  sync); }
   { volatile atomic<foo,weak> a(0);  a.preinc (  sync); }
   { volatile atomic<foo,weak> a(0);  a.postinc(  sync); }
   { volatile atomic<foo,weak> a(0);  a.dec    (  sync); }
   { volatile atomic<foo,weak> a(0);  a.predec (  sync); }
   { volatile atomic<foo,weak> a(0);  a.postdec(  sync); }
   { volatile atomic<foo,weak> a(0);  a.add    (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.sub    (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.mul    (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.div    (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.mod    (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.lshift (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.rshift (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.andeq  (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.oreq   (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.xoreq  (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.min    (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.max    (b,success,failure); }
   { volatile atomic<foo,weak> a(0);  a.inc    (  success,failure); }
   { volatile atomic<foo,weak> a(0);  a.preinc (  success,failure); }
   { volatile atomic<foo,weak> a(0);  a.postinc(  success,failure); }
   { volatile atomic<foo,weak> a(0);  a.dec    (  success,failure); }
   { volatile atomic<foo,weak> a(0);  a.predec (  success,failure); }
   { volatile atomic<foo,weak> a(0);  a.postdec(  success,failure); }
#endif

#if !defined(__clang__) && !defined(ATOMICS_TEST)
   { volatile atomic<foo,weak::pun> a(0);  a.add    (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.sub    (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.mul    (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.div    (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.mod    (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.lshift (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.rshift (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.andeq  (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.oreq   (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.xoreq  (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.min    (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.max    (b); }
   { volatile atomic<foo,weak::pun> a(0);  a.inc    ( ); }
   { volatile atomic<foo,weak::pun> a(0);  a.preinc ( ); }
   { volatile atomic<foo,weak::pun> a(0);  a.postinc( ); }
   { volatile atomic<foo,weak::pun> a(0);  a.dec    ( ); }
   { volatile atomic<foo,weak::pun> a(0);  a.predec ( ); }
   { volatile atomic<foo,weak::pun> a(0);  a.postdec( ); }
   { volatile atomic<foo,weak::pun> a(0);  a.add    (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.sub    (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.mul    (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.div    (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.mod    (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.lshift (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.rshift (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.andeq  (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.oreq   (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.xoreq  (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.min    (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.max    (b,sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.inc    (  sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.preinc (  sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.postinc(  sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.dec    (  sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.predec (  sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.postdec(  sync); }
   { volatile atomic<foo,weak::pun> a(0);  a.add    (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.sub    (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.mul    (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.div    (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.mod    (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.lshift (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.rshift (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.andeq  (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.oreq   (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.xoreq  (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.min    (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.max    (b,success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.inc    (  success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.preinc (  success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.postinc(  success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.dec    (  success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.predec (  success,failure); }
   { volatile atomic<foo,weak::pun> a(0);  a.postdec(  success,failure); }
#endif

//v{ volatile atomic<foo,lock> a(0);  a.add    (b); }
//v{ volatile atomic<foo,lock> a(0);  a.sub    (b); }
//v{ volatile atomic<foo,lock> a(0);  a.mul    (b); }
//v{ volatile atomic<foo,lock> a(0);  a.div    (b); }
//v{ volatile atomic<foo,lock> a(0);  a.mod    (b); }
//v{ volatile atomic<foo,lock> a(0);  a.lshift (b); }
//v{ volatile atomic<foo,lock> a(0);  a.rshift (b); }
//v{ volatile atomic<foo,lock> a(0);  a.andeq  (b); }
//v{ volatile atomic<foo,lock> a(0);  a.oreq   (b); }
//v{ volatile atomic<foo,lock> a(0);  a.xoreq  (b); }
//v{ volatile atomic<foo,lock> a(0);  a.min    (b); }
//v{ volatile atomic<foo,lock> a(0);  a.max    (b); }
//v{ volatile atomic<foo,lock> a(0);  a.inc    ( ); }
//v{ volatile atomic<foo,lock> a(0);  a.preinc ( ); }
//v{ volatile atomic<foo,lock> a(0);  a.postinc( ); }
//v{ volatile atomic<foo,lock> a(0);  a.dec    ( ); }
//v{ volatile atomic<foo,lock> a(0);  a.predec ( ); }
//v{ volatile atomic<foo,lock> a(0);  a.postdec( ); }
// { volatile atomic<foo,lock> a(0);  a.add    (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.sub    (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.mul    (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.div    (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.mod    (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.lshift (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.rshift (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.andeq  (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.oreq   (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.xoreq  (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.min    (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.max    (b,sync); }
// { volatile atomic<foo,lock> a(0);  a.inc    (  sync); }
// { volatile atomic<foo,lock> a(0);  a.preinc (  sync); }
// { volatile atomic<foo,lock> a(0);  a.postinc(  sync); }
// { volatile atomic<foo,lock> a(0);  a.dec    (  sync); }
// { volatile atomic<foo,lock> a(0);  a.predec (  sync); }
// { volatile atomic<foo,lock> a(0);  a.postdec(  sync); }
// { volatile atomic<foo,lock> a(0);  a.add    (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.sub    (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.mul    (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.div    (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.mod    (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.lshift (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.rshift (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.andeq  (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.oreq   (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.xoreq  (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.min    (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.max    (b,success,failure); }
// { volatile atomic<foo,lock> a(0);  a.inc    (  success,failure); }
// { volatile atomic<foo,lock> a(0);  a.preinc (  success,failure); }
// { volatile atomic<foo,lock> a(0);  a.postinc(  success,failure); }
// { volatile atomic<foo,lock> a(0);  a.dec    (  success,failure); }
// { volatile atomic<foo,lock> a(0);  a.predec (  success,failure); }
// { volatile atomic<foo,lock> a(0);  a.postdec(  success,failure); }

//v{ volatile atomic<foo,serial> a(0);  a.add    (b); }
//v{ volatile atomic<foo,serial> a(0);  a.sub    (b); }
//v{ volatile atomic<foo,serial> a(0);  a.mul    (b); }
//v{ volatile atomic<foo,serial> a(0);  a.div    (b); }
//v{ volatile atomic<foo,serial> a(0);  a.mod    (b); }
//v{ volatile atomic<foo,serial> a(0);  a.lshift (b); }
//v{ volatile atomic<foo,serial> a(0);  a.rshift (b); }
//v{ volatile atomic<foo,serial> a(0);  a.andeq  (b); }
//v{ volatile atomic<foo,serial> a(0);  a.oreq   (b); }
//v{ volatile atomic<foo,serial> a(0);  a.xoreq  (b); }
//v{ volatile atomic<foo,serial> a(0);  a.min    (b); }
//v{ volatile atomic<foo,serial> a(0);  a.max    (b); }
//v{ volatile atomic<foo,serial> a(0);  a.inc    ( ); }
//v{ volatile atomic<foo,serial> a(0);  a.preinc ( ); }
//v{ volatile atomic<foo,serial> a(0);  a.postinc( ); }
//v{ volatile atomic<foo,serial> a(0);  a.dec    ( ); }
//v{ volatile atomic<foo,serial> a(0);  a.predec ( ); }
//v{ volatile atomic<foo,serial> a(0);  a.postdec( ); }
// { volatile atomic<foo,serial> a(0);  a.add    (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.sub    (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.mul    (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.div    (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.mod    (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.lshift (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.rshift (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.andeq  (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.oreq   (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.xoreq  (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.min    (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.max    (b,sync); }
// { volatile atomic<foo,serial> a(0);  a.inc    (  sync); }
// { volatile atomic<foo,serial> a(0);  a.preinc (  sync); }
// { volatile atomic<foo,serial> a(0);  a.postinc(  sync); }
// { volatile atomic<foo,serial> a(0);  a.dec    (  sync); }
// { volatile atomic<foo,serial> a(0);  a.predec (  sync); }
// { volatile atomic<foo,serial> a(0);  a.postdec(  sync); }
// { volatile atomic<foo,serial> a(0);  a.add    (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.sub    (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.mul    (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.div    (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.mod    (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.lshift (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.rshift (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.andeq  (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.oreq   (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.xoreq  (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.min    (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.max    (b,success,failure); }
// { volatile atomic<foo,serial> a(0);  a.inc    (  success,failure); }
// { volatile atomic<foo,serial> a(0);  a.preinc (  success,failure); }
// { volatile atomic<foo,serial> a(0);  a.postinc(  success,failure); }
// { volatile atomic<foo,serial> a(0);  a.dec    (  success,failure); }
// { volatile atomic<foo,serial> a(0);  a.predec (  success,failure); }
// { volatile atomic<foo,serial> a(0);  a.postdec(  success,failure); }
}
