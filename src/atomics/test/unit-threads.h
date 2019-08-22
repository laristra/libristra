
//#define ATOMICS_KOKKOS
#define ATOMICS_DEBUG
//#define ATOMICS_BOOST

#include "atomics.h"

#include <cassert>
#include <complex>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

//#include <typeinfo>
//#include <boost/core/demangle.hpp>

using namespace ristra::atomics;



// -----------------------------------------------------------------------------
// Helper constructs
// -----------------------------------------------------------------------------

// boolean
template<bool>
struct boolean {
};


// same
template<class A, class B>
struct same {
   static constexpr bool value = false;
};

template<class T>
struct same<T,T> {
   static constexpr bool value = true;
};


// compatible
// Fully and accurately realized, this would be more complicated,
// but it suffices as-is for our present test-code purposes.
template<class T, class SCHEME>
struct compatible {
   static constexpr bool value =
      // cpp, integral or pointer
      (same<SCHEME,cpp>::value &&
       (std::is_integral<T>::value || std::is_pointer<T>::value)) ||
#if defined(ATOMICS_KOKKOS)
      // kokkos, integral or double
      (same<SCHEME,kokkos>::value &&
       (std::is_integral<T>::value || same<T,double>::value)) ||
#endif
      // *::pun, and a (probably) acceptable sizeof. (Ideally, we'd check
      // against integral types <= long long; but this is sufficient here.)
      ((same<SCHEME,strong::pun>::value || same<SCHEME,weak::pun>::value) &&
       sizeof(T) <= sizeof(long long)) ||
      // neither cpp, kokkos, or *::pun (those are handled above)
      (!same<SCHEME,cpp>::value &&
#if defined(ATOMICS_KOKKOS)
       !same<SCHEME,kokkos>::value &&
#endif
       !same<SCHEME,strong::pun>::value &&
       !same<SCHEME,weak::pun>::value)
      ;
};


// approximately_equal: integral or pointer
template<class T>
typename std::enable_if<
   std::is_integral<T>::value || std::is_pointer<T>::value,
   bool
>::type
approximately_equal(const T a, const T b)
{
   return a == b;
}

// approximately_equal: general
template<class T>
typename std::enable_if<
   !(std::is_integral<T>::value || std::is_pointer<T>::value),
   bool
>::type
approximately_equal(const T a, const T b)
{
   // This is sort of simple-minded and has a magic number,
   // but for now it suffices for our purposes.
   return std::abs(a-b) < 1e-6*(std::abs(a) + std::abs(b));
}



// -----------------------------------------------------------------------------
// action
// -----------------------------------------------------------------------------

// op: forward
template<class T_OR_ATOMIC, class RHS>
void op(T_OR_ATOMIC &, const std::size_t niter, const RHS rhs);


/*
// info: helper
template<class T, class SCHEME>
std::string info()
{
   return
      boost::core::demangle(typeid(T     ).name()) + ", " +
      boost::core::demangle(typeid(SCHEME).name());
}
*/


// for compatible T and SCHEME
template<
   class T, class SCHEME,
   std::size_t NINITIAL,
   class R, std::size_t NRHS
>
void action(
   const T (&initial)[NINITIAL],
   const R (&rhs)[NRHS],
   const std::size_t nthread,
   const std::size_t niter,
   const std::size_t iinitial,
   const std::size_t irhs,
   const boolean<true>
) {
   // std::cout << "yes: " << info<T,SCHEME>() << std::endl;

   // ------------------------
   // serial result
   // ------------------------

   // initialize value
   T serial_value(initial[iinitial]);

   // serially, do as if nthread threads were done
   for (std::size_t ithread = 0;  ithread < nthread;  ++ithread)
      op<T,R>(std::ref(serial_value), niter, rhs[irhs]);


   // ------------------------
   // atomic result
   // ------------------------

   // initialize atomic value
   atomic<T,SCHEME> atomic_value(initial[iinitial]);

   // create threads
   std::vector<std::thread> thread;
   for (std::size_t ithread = 0;  ithread < nthread;  ++ithread)
      thread.push_back(
         std::thread(
            op<atomic<T,SCHEME>,R>,
            std::ref(atomic_value), niter, rhs[irhs]
         )
      );

   // join threads
   for (std::size_t ithread = 0;  ithread < nthread;  ++ithread)
      thread[ithread].join();


   // ------------------------
   // check that the above
   // two are the same
   // ------------------------

   if (!approximately_equal(T(atomic_value), serial_value)) {
      std::cout << "serial_value == " << serial_value << std::endl;
      std::cout << "atomic_value == " << T(atomic_value) << std::endl;
   }

   /*
   if (T(atomic_value) != serial_value) {
      std::cout << "Case:";
      std::cout << "\n   T        == "
                << boost::core::demangle(typeid(T).name());
      std::cout << "\n   SCHEME   == "
                << boost::core::demangle(typeid(SCHEME).name());
      std::cout << "\n   nthread  == " << nthread;
      std::cout << "\n   niter    == " << niter;
      std::cout << "\n   iinitial == " << iinitial;
      std::cout << "\n   irhs     == " << irhs;
      std::cout << std::endl;
      std::cout << "serial_value == " << serial_value << std::endl;
      std::cout << "atomic_value == " << atomic_value << std::endl;
   }
   std::cout << "serial_value == " << serial_value << std::endl;
   std::cout << "atomic_value == " << atomic_value << std::endl;

   typedef std::numeric_limits<T> NLT;
   std::cout.precision(NLT::max_digits10);
   std::cout << "serial_value == " << std::fixed << serial_value << std::endl;
   std::cout << "atomic_value == " << std::fixed << atomic_value << std::endl;
   */

   assert(approximately_equal(T(atomic_value), serial_value));
}



// for INcompatible T and SCHEME: do nothing
template<
   class T, class SCHEME,
   std::size_t NINITIAL,
   class R, std::size_t NRHS
>
void action(
   const T (&)[NINITIAL],
   const R (&)[NRHS],
   const std::size_t,
   const std::size_t,
   const std::size_t,
   const std::size_t,
   const boolean<false>
) {
   // std::cout << "NO:  " << info<T,SCHEME>() << std::endl;
}



// -----------------------------------------------------------------------------
// scheme
// type
// -----------------------------------------------------------------------------

// scheme
// For a given T and SCHEME, run lots of cases
template<
   class T, class SCHEME,
   std::size_t NINITIAL,
   class R, std::size_t NRHS
>
void scheme(
   const T (&initial)[NINITIAL],
   const R (&rhs)[NRHS],
   const bool is_serial = false
) {
   for (std::size_t nthread  = 1;  nthread  <= MAXNTHREAD;  ++nthread )
   for (std::size_t niter    = 1;  niter    <= MAXNITER;    ++niter   )
   for (std::size_t iinitial = 0;  iinitial <  NINITIAL;    ++iinitial)
   for (std::size_t irhs     = 0;  irhs     <  NRHS;        ++irhs    ) {
      if (is_serial && nthread != 1)
         continue;  // serial scheme shouldn't be used with multiple threads
      action<T,SCHEME>(
         initial, rhs,
         nthread, niter, iinitial, irhs,
         boolean<compatible<T,SCHEME>::value>{}
      );
   }
}


// type
// For a given T, runs lots of schemes (see above)
template<
   class T,
   std::size_t NINITIAL,
   class R, std::size_t NRHS
>
void type(
   const T (&initial)[NINITIAL],
   const R (&rhs)[NRHS]
) {
   /*
   std::cout <<
      boost::core::demangle(typeid(decltype(initial)).name()) << std::endl <<
      boost::core::demangle(typeid(decltype(rhs    )).name()) << std::endl;
   exit(1);
   */

#if !defined(ATOMICS_NO_CPP)
   scheme< T, cpp        >(initial, rhs);
#endif
#if defined(ATOMICS_KOKKOS)
   scheme< T, kokkos     >(initial, rhs);
#endif
   scheme< T, strong     >(initial, rhs);
   scheme< T, strong::pun>(initial, rhs);
   scheme< T, weak       >(initial, rhs);
   scheme< T, weak::pun  >(initial, rhs);
   scheme< T, lock       >(initial, rhs);
   scheme< T, serial     >(initial, rhs, true);  // true == is_serial
}
