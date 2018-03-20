/* -*- C++ -*- */

// -----------------------------------------------------------------------------
//
// atomics.h
//
// Description
//
//    Some constructs to support atomics.
//    Header-only library.
//
// Author
//
//    Martin Staley
//    CCS-7, Applied Computer Science
//    Los Alamos National Laboratory
//    staley@lanl.gov
//
// -----------------------------------------------------------------------------

/// \file
/// \brief Support for atomic operations on general data

#ifndef ristra_atomics_h
#define ristra_atomics_h

// C++
#include <atomic>
#include <cstddef>
#include <mutex>
#include <type_traits>

// Kokkos (optional)
#if defined(ATOMICS_KOKKOS)
#include <Kokkos_Atomic.hpp>
#endif

// For debug-mode assertions
#if defined(ATOMICS_DEBUG)
#include <cassert>
#endif

// For print-mode printing
#if defined(ATOMICS_PRINT)
#include <iostream>
#include <boost/core/demangle.hpp>
#endif

// Everything in the rest of this file is placed into the ristra::atomics.
// Helper constructs, scattered throughout the file, are additionally placed
// into a namespace called "internal" wherever they appear. That's my way
// of saying, "for internal use; call only if you know what you're doing."

/// As for other Ristra projects
namespace ristra {

/// Atomics support
namespace atomics {

/// Miscellaneous "internal use only" constructs
namespace internal {
}



// -----------------------------------------------------------------------------
// Schemes for achieving atomicity
// Represented by classes, to be used for overloading
// -----------------------------------------------------------------------------

/// Tag: atomicize via C++ std::atomic functions
class cpp { };

#if defined(ATOMICS_KOKKOS)
/// Tag: atomicize via Kokkos atomic functions
class kokkos { };
#endif

/// Tag: atomicize via strong compare-and-swap loop
class strong {
public:
   /// Tag: pun type to integral in CAS
   class pun { };
};

/// Tag: atomicize via weak compare-and-swap loop
class weak {
public:
   /// Tag: pun type to integral in CAS
   class pun { };
};

/// Tag: atomicize via lock_guard(mutex)
class lock { };

/// Tag: don't atomicize
class serial { };

// Default scheme
// You can change the default by #defining ATOMICS_DEFAULT_SCHEME
// before #including this file.
#ifndef ATOMICS_DEFAULT_SCHEME
   #define ATOMICS_DEFAULT_SCHEME atomics::strong
#endif

// atomic<T,SCHEME,NMUX>
// Forward declaration
template<class T, class SCHEME = ATOMICS_DEFAULT_SCHEME, std::size_t NMUX = 0>
class atomic;



// -----------------------------------------------------------------------------
// Constructs for debugging and printing
// -----------------------------------------------------------------------------

namespace internal {

// ------------------------
// Assertions
// For debug mode
// ------------------------

#if defined(ATOMICS_DEBUG)
   #define atomics_assert(x) assert(x)
#else
   #define atomics_assert(x)
#endif


// ------------------------
// Printing
// For print mode
// ------------------------

#define _atomics_stringify(x) #x
#define  atomics_stringify(x) _atomics_stringify(x)

// atomics_print_var
// Simple macro for printing something's name and value.
#define atomics_print_var(x) std::cout << #x " == " << (x) << std::endl

#if defined(ATOMICS_PRINT)

/// Print type T's type name as determined by Boost's demangle()
template<class T>
inline void print_type() noexcept
{
   std::cout << boost::core::demangle(typeid(T).name());
}

/// Print the name of a std::memory_order value
inline void print_memord(const std::memory_order sync) noexcept
{
   if (sync == std::memory_order_relaxed)
      std::cout << "memory_order_relaxed" << std::endl;
   if (sync == std::memory_order_consume)
      std::cout << "memory_order_consume" << std::endl;
   if (sync == std::memory_order_acquire)
      std::cout << "memory_order_acquire" << std::endl;
   if (sync == std::memory_order_release)
      std::cout << "memory_order_release" << std::endl;
   if (sync == std::memory_order_acq_rel)
      std::cout << "memory_order_acq_rel" << std::endl;
   if (sync == std::memory_order_seq_cst)
      std::cout << "memory_order_seq_cst" << std::endl;
}

#endif // #if defined(ATOMICS_PRINT)

} // namespace internal



// -----------------------------------------------------------------------------
// get_scheme
// Helper function
// -----------------------------------------------------------------------------

namespace internal {

// The following class assists the code in determining what atomicity scheme
// to use if the user calls an atomic function with, or without, providing an
// override of the atomic variable's own scheme. Consider:
//
//    atomic<double,strong> var(0); // var's scheme == strong
//
//    add(var,10);       // <== uses var's scheme (strong)
//    add<weak>(var,20); // <== override; use scheme == weak instead
//
// Functions like add() begin with template<class S = char, ...>. Then, the
// atomic parameter's own SCHEME, and the given (or not given) override S,
// are fed into get_scheme, below, which selects S (if not char) or SCHEME.

/// Traits; the default extracts S
template<class SCHEME, class S>
class get_scheme {
public:
   using scheme = S;
};

/// Traits; the S == char version extracts SCHEME
template<class SCHEME>
class get_scheme<SCHEME,char> {
public:
   using scheme = SCHEME;
};

} // namespace internal



// -----------------------------------------------------------------------------
// Traits
// -----------------------------------------------------------------------------

namespace internal {

// ------------------------
// is_atomic
// ------------------------

template<class T>
class is_atomic {
};

template<class T, class SCHEME, std::size_t NMUX>
class is_atomic<atomic<T,SCHEME,NMUX>> {
public:
   using value_type = T;
};

template<class T, class SCHEME, std::size_t NMUX>
class is_atomic<volatile atomic<T,SCHEME,NMUX>> {
public:
   using value_type = T;
};


// ------------------------
// is_std_atomic
// ------------------------

template<class T>
class is_std_atomic {
};

template<class T>
class is_std_atomic<std::atomic<T>> {
public:
   using value_type = T;
};

template<class T>
class is_std_atomic<volatile std::atomic<T>> {
public:
   using value_type = T;
};

} // namespace internal



// -----------------------------------------------------------------------------
// debug_apply
// Called from the various apply() functions, to print debugging information.
// No-ops, unless ATOMICS_PRINT is #defined. (There are enough calls to these
// functions that making them no-ops like this was shorter than preprocessing
// out the calls themselves.)
// -----------------------------------------------------------------------------

namespace internal {

// scheme
/// Print debugging info for one of our apply() functions
template<class ATOMIC, class OPERATION>
inline void debug_apply(
   const char *const scheme
) noexcept {
   #if defined(ATOMICS_PRINT)
      using T = typename is_atomic<ATOMIC>::value_type;
      std::cout << "apply\n";
      std::cout << "   left side: ";  print_type<ATOMIC>();
      std::cout << "\n";
      std::cout << "   scheme   : " << scheme << "\n";
      std::cout << "   function : ";  print_type<OPERATION>();
      std::cout << "\n";
      std::cout << "   T/return : ";  print_type<T>();
      std::cout << "\n";
   #else
      // disappear unused-parameter warnings
      (void)scheme;
   #endif
}

// scheme; memory order sync
/// Print debugging info for one of our apply() functions
template<class ATOMIC, class OPERATION>
inline void debug_apply(
   const char *const scheme,
   const std::memory_order sync
) noexcept {
   #if defined(ATOMICS_PRINT)
      using T = typename is_atomic<ATOMIC>::value_type;
      std::cout << "apply\n";
      std::cout << "   left side: ";  print_type<ATOMIC>();
      std::cout << "\n";
      std::cout << "   scheme   : " << scheme << "\n";
      std::cout << "   function : ";  print_type<OPERATION>();
      std::cout << "\n";
      std::cout << "   sync     : ";  print_memord(sync);
      std::cout << "   T/return : ";  print_type<T>();
      std::cout << "\n";
   #else
      // disappear unused-parameter warnings
      (void)scheme;
      (void)sync;
   #endif
}

// scheme; memory order success, failure
/// Print debugging info for one of our apply() functions
template<class ATOMIC, class OPERATION>
inline void debug_apply(
   const char *const scheme,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   #if defined(ATOMICS_PRINT)
      using T = typename is_atomic<ATOMIC>::value_type;
      std::cout << "apply\n";
      std::cout << "   left side: ";  print_type<ATOMIC>();
      std::cout << "\n";
      std::cout << "   scheme   : " << scheme << "\n";
      std::cout << "   function : ";  print_type<OPERATION>();
      std::cout << "\n";
      std::cout << "   success  : ";  print_memord(success);
      std::cout << "   failure  : ";  print_memord(failure);
      std::cout << "   T/return : ";  print_type<T>();
      std::cout << "\n";
   #else
      (void)scheme;
      (void)success;
      (void)failure;
   #endif
}

// scheme; pun
/// Print debugging info for one of our apply() functions
template<class ATOMIC, class OPERATION, class P>
inline void debug_apply(
   const char *const scheme
) noexcept {
   debug_apply<ATOMIC,OPERATION>(scheme);
   #if defined(ATOMICS_PRINT)
      std::cout << "   P/pun    : ";
      print_type<P>();
      std::cout << "\n";
   #endif
}

// scheme; memory_order sync; pun
/// Print debugging info for one of our apply() functions
template<class ATOMIC, class OPERATION, class P>
inline void debug_apply(
   const char *const scheme,
   const std::memory_order sync
) noexcept {
   debug_apply<ATOMIC,OPERATION>(scheme,sync);
   #if defined(ATOMICS_PRINT)
      std::cout << "   P/pun    : ";
      print_type<P>();
      std::cout << "\n";
   #endif
}

// scheme; memory_order success, failure; pun
/// Print debugging info for one of our apply() functions
template<class ATOMIC, class OPERATION, class P>
inline void debug_apply(
   const char *const scheme,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   debug_apply<ATOMIC,OPERATION>(scheme,success,failure);
   #if defined(ATOMICS_PRINT)
      std::cout << "   P/pun    : ";
      print_type<P>();
      std::cout << "\n";
   #endif
}

} // namespace internal



// -----------------------------------------------------------------------------
// punxstrong: punned compare/exchange strong
// punxweak:   punned compare/exchange weak
// -----------------------------------------------------------------------------

namespace internal {

#define atomics_make_compexch_punned(fun,vol,compexch) \
   template<class T, class P> \
   inline bool fun( \
      vol std::atomic<T> &atom, \
      P &old, const P &neu, \
      const std::memory_order sync \
   ) { \
      atomics_assert(sizeof(std::atomic<P>) == sizeof(std::atomic<T>)); \
      return reinterpret_cast<vol std::atomic<P> *>(&atom)-> \
         compexch(old, neu, sync); \
   } \
   \
   template<class T, class P> \
   inline bool fun( \
      vol std::atomic<T> &atom, \
      P &old, const P &neu, \
      const std::memory_order success, \
      const std::memory_order failure \
   ) { \
      atomics_assert(sizeof(std::atomic<P>) == sizeof(std::atomic<T>)); \
      return reinterpret_cast<vol std::atomic<P> *>(&atom)-> \
         compexch(old, neu, success, failure); \
   }

/// Helper for strong compare/exchange; forwards reinterpreted data
atomics_make_compexch_punned(punxstrong,         , compare_exchange_strong)

/// Helper for strong compare/exchange; forwards reinterpreted data
atomics_make_compexch_punned(punxstrong, volatile, compare_exchange_strong)

/// Helper for weak compare/exchange; forwards reinterpreted data
atomics_make_compexch_punned(punxweak,           , compare_exchange_weak)

/// Helper for weak compare/exchange; forwards reinterpreted data
atomics_make_compexch_punned(punxweak,   volatile, compare_exchange_weak)

#undef atomics_make_compexch_punned

} // namespace internal



// -----------------------------------------------------------------------------
// apply: cpp
// OPERATION should have an appropriate operator() that forwards
// to an available underlying std::atomic member function.
// -----------------------------------------------------------------------------

namespace internal {

/// Apply operation, using the cpp scheme (underlying std::atomic capability)
template<class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply(
   ATOMIC &atom,
   const cpp,
   const OPERATION &operation
) noexcept {
   debug_apply<ATOMIC,OPERATION>("cpp");
   return operation(atom.base(),cpp{});
}

/// Apply operation, using the cpp scheme, w/memory_order sync
template<class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply(
   ATOMIC &atom,
   const cpp,
   const OPERATION &operation,
   const std::memory_order sync
) noexcept {
   debug_apply<ATOMIC,OPERATION>("cpp",sync);
   return operation(atom.base(),cpp{},sync);
}

} // namespace internal



// -----------------------------------------------------------------------------
// apply: kokkos
// OPERATION should have an appropriate operator() that forwards
// to an available underlying Kokkos:: function.
// -----------------------------------------------------------------------------

#if defined(ATOMICS_KOKKOS)
namespace internal {

/// Apply operation, using a Kokkos atomic function
template<class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply(
   ATOMIC &atom,
   const kokkos,
   const OPERATION &operation
) noexcept {
   debug_apply<ATOMIC,OPERATION>("kokkos");
   return operation(atom,kokkos{});
}

} // namespace internal
#endif // #if defined(ATOMICS_KOKKOS)



// -----------------------------------------------------------------------------
// apply: strong
// OPERATION's operator() is embedded here into a strong compare-and-swap,
// in order to achieve atomicity with respect to the destination datum.
// Bear in mind that the compare-and-swap scheme doesn't atomicize any side
// effects (e.g. printing) that may occur when the operation is applied!!
// It just ensures that the destination ("atom" here) is updated atomically.
// -----------------------------------------------------------------------------

namespace internal {

/// Apply operation via strong CAS embedding; optional memory_order sync
template<class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply(
   ATOMIC &atom,
   const strong,
   const OPERATION &operation,
   const std::memory_order sync = std::memory_order_seq_cst
) noexcept {
   using T = typename is_atomic<ATOMIC>::value_type;
   debug_apply<ATOMIC,OPERATION>("strong",sync);

   T old = T(atom);
   T neu, ret;

   do {
      neu = old;
      ret = operation(neu);
      // Remark: here's how the following compare_exchange_strong() works.
      //    If atom == old
      //       atom <-- neu
      //       return true
      //    Else
      //       old <-- atom
      //       return false
      // That's all done atomically (so, we can't just write it directly).
      // Notice that if iteration continues, old will have been updated
      // to atom, which presumably was changed by another thread. That's
      // why *we* don't need to reassign old = T(atom) in our do-loop.
   } while (!atom.compare_exchange_strong(old, neu, sync));

   // Remark: operation(neu), above, modifies neu (think +=, -=, etc.)
   // For most operations, then, ret == neu. However, that wouldn't be
   // the case with postincrement and postdecrement, which is why we
   // have (and return) ret, not neu.
   return ret;
}

/// Apply operation via strong CAS embedding; memory_order success, failure
template<class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply(
   ATOMIC &atom,
   const strong,
   const OPERATION &operation,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   using T = typename is_atomic<ATOMIC>::value_type;
   debug_apply<ATOMIC,OPERATION>("strong", success, failure);

   T old = T(atom);
   T neu, ret;

   do {
      neu = old;
      ret = operation(neu);
   } while (!atom.compare_exchange_strong(old, neu, success, failure));

   return ret;
}

} // namespace internal



// -----------------------------------------------------------------------------
// apply: strong::pun
// As for strong (above), with the destination datum type punned to an integral
// type that might give faster compare-and-swap behavior.
// -----------------------------------------------------------------------------

namespace internal {

// ------------------------
// Helper functions
// ------------------------

/// Helper for punned strong CAS apply(); memory_order sync
template<class P, class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply_pun(
   ATOMIC &atom,
   const strong::pun,
   const OPERATION &operation,
   const std::memory_order sync
) {
   using T = typename is_atomic<ATOMIC>::value_type;
   debug_apply<ATOMIC,OPERATION,P>("strong::pun",sync);

   union u {
      T tee;
      P pun;
      // Need default ctor on this and similar unions, to avoid compilation
      // error due to call to implicitly-deleted default ctor
      inline u() { }
   } old, neu;
   old.tee = T(atom);

   atomics_assert(sizeof(old) == sizeof(T));
   atomics_assert(sizeof(old) == sizeof(P));

   T ret;
   do {
      neu.pun = old.pun;
      ret = operation(neu.tee);
   } while (!punxstrong(atom, old.pun, neu.pun, sync));

   return ret;
}

/// Helper for punned strong CAS apply(); memory_order success, failure
template<class P, class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply_pun(
   ATOMIC &atom,
   const strong::pun,
   const OPERATION &operation,
   const std::memory_order success,
   const std::memory_order failure
) {
   using T = typename is_atomic<ATOMIC>::value_type;
   debug_apply<ATOMIC,OPERATION,P>("strong::pun", success, failure);

   union u {
      T tee;
      P pun;
      inline u() { }
   } old, neu;
   old.tee = T(atom);

   atomics_assert(sizeof(old) == sizeof(T));
   atomics_assert(sizeof(old) == sizeof(P));

   T ret;
   do {
      neu.pun = old.pun;
      ret = operation(neu.tee);
   } while (!punxstrong(atom, old.pun, neu.pun, success, failure));

   return ret;
}


// ------------------------
// Helper macro
// ------------------------

#define atomics_make_apply(condition,cas,P) \
   template<class ATOMIC, class OPERATION> \
   inline typename \
   std::enable_if<condition,typename is_atomic<ATOMIC>::value_type>::type \
   apply( \
      ATOMIC &atom, \
      const cas::pun, \
      const OPERATION &operation, \
      const std::memory_order sync = std::memory_order_seq_cst \
   ) { \
      return apply_pun<P>(atom, cas::pun{}, operation, sync); \
   } \
   \
   template<class ATOMIC, class OPERATION> \
   inline typename \
   std::enable_if<condition,typename is_atomic<ATOMIC>::value_type>::type \
   apply( \
      ATOMIC &atom, \
      const cas::pun, \
      const OPERATION &operation, \
      const std::memory_order success, \
      const std::memory_order failure \
   ) { \
      return apply_pun<P>(atom, cas::pun{}, operation, success, failure); \
   }


// ------------------------
// Puns to several plain
// old integral types
// ------------------------

// != requirements are sufficient,
// because sizeof(signed char) <= sizeof(short) <= sizeof(int) <= ...

/// Punned strong CAS; long long
atomics_make_apply(
   sizeof(typename is_atomic<ATOMIC>::value_type) == sizeof(long long) &&
   sizeof(typename is_atomic<ATOMIC>::value_type) != sizeof(long),
   strong, long long)

/// Punned strong CAS; long
atomics_make_apply(
   sizeof(typename is_atomic<ATOMIC>::value_type) == sizeof(long) &&
   sizeof(typename is_atomic<ATOMIC>::value_type) != sizeof(int),
   strong, long)

/// Punned strong CAS; int
atomics_make_apply(
   sizeof(typename is_atomic<ATOMIC>::value_type) == sizeof(int) &&
   sizeof(typename is_atomic<ATOMIC>::value_type) != sizeof(short),
   strong, int)

/// Punned strong CAS; short
atomics_make_apply(
   sizeof(typename is_atomic<ATOMIC>::value_type) == sizeof(short) &&
   sizeof(typename is_atomic<ATOMIC>::value_type) != sizeof(signed char),
   strong, short)

/// Punned strong CAS; signed char
atomics_make_apply(
   sizeof(typename is_atomic<ATOMIC>::value_type) == sizeof(signed char),
   strong, signed char)

} // namespace internal



// -----------------------------------------------------------------------------
// apply: weak
// OPERATION's operator() is embedded here into a weak compare-and-swap,
// in order to achieve atomicity with respect to the destination datum.
// -----------------------------------------------------------------------------

namespace internal {

/// Apply operation via weak CAS embedding; optional memory_order sync
template<class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply(
   ATOMIC &atom,
   const weak,
   const OPERATION &operation,
   const std::memory_order sync = std::memory_order_seq_cst
) noexcept {
   using T = typename is_atomic<ATOMIC>::value_type;
   debug_apply<ATOMIC,OPERATION>("weak",sync);

   T old = T(atom);
   T neu, ret;

   do {
      neu = old;
      ret = operation(neu);
   } while (!atom.compare_exchange_weak(old, neu, sync));

   return ret;
}

/// Apply operation via weak CAS embedding; memory_order success, failure
template<class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply(
   ATOMIC &atom,
   const weak,
   const OPERATION &operation,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   using T = typename is_atomic<ATOMIC>::value_type;
   debug_apply<ATOMIC,OPERATION>("weak", success, failure);

   T old = T(atom);
   T neu, ret;

   do {
      neu = old;
      ret = operation(neu);
   } while (!atom.compare_exchange_weak(old, neu, success, failure));

   return ret;
}

} // namespace internal



// -----------------------------------------------------------------------------
// apply: weak::pun
// As for weak (above), with the destination datum type punned to an integral
// type that might give faster compare-and-swap behavior.
// -----------------------------------------------------------------------------

namespace internal {

// ------------------------
// Helper functions
// ------------------------

/// Helper for punned weak CAS apply(); memory_order sync
template<class P, class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply_pun(
   ATOMIC &atom,
   const weak::pun,
   const OPERATION &operation,
   const std::memory_order sync
) {
   using T = typename is_atomic<ATOMIC>::value_type;
   debug_apply<ATOMIC,OPERATION,P>("weak::pun",sync);

   union u {
      T tee;
      P pun;
      inline u() { }
   } old, neu;
   old.tee = T(atom);

   atomics_assert(sizeof(old) == sizeof(T));
   atomics_assert(sizeof(old) == sizeof(P));

   T ret;
   do {
      neu.pun = old.pun;
      ret = operation(neu.tee);
   } while (!punxweak(atom, old.pun, neu.pun, sync));

   return ret;
}

/// Helper for punned weak CAS apply(); memory_order success, failure
template<class P, class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply_pun(
   ATOMIC &atom,
   const weak::pun,
   const OPERATION &operation,
   const std::memory_order success,
   const std::memory_order failure
) {
   using T = typename is_atomic<ATOMIC>::value_type;
   debug_apply<ATOMIC,OPERATION,P>("weak::pun", success, failure);

   union u {
      T tee;
      P pun;
      inline u() { }
   } old, neu;
   old.tee = T(atom);

   atomics_assert(sizeof(old) == sizeof(T));
   atomics_assert(sizeof(old) == sizeof(P));

   T ret;
   do {
      neu.pun = old.pun;
      ret = operation(neu.tee);
   } while (!punxweak(atom, old.pun, neu.pun, success, failure));

   return ret;
}


// ------------------------
// Puns to several plain
// old integral types
// ------------------------

// Re-use the macro from the strong::pun section...

/// Punned strong CAS; long long
atomics_make_apply(
   sizeof(typename is_atomic<ATOMIC>::value_type) == sizeof(long long) &&
   sizeof(typename is_atomic<ATOMIC>::value_type) != sizeof(long),
   weak, long long)

/// Punned strong CAS; long
atomics_make_apply(
   sizeof(typename is_atomic<ATOMIC>::value_type) == sizeof(long) &&
   sizeof(typename is_atomic<ATOMIC>::value_type) != sizeof(int),
   weak, long)

/// Punned strong CAS; int
atomics_make_apply(
   sizeof(typename is_atomic<ATOMIC>::value_type) == sizeof(int) &&
   sizeof(typename is_atomic<ATOMIC>::value_type) != sizeof(short),
   weak, int)

/// Punned strong CAS; short
atomics_make_apply(
   sizeof(typename is_atomic<ATOMIC>::value_type) == sizeof(short) &&
   sizeof(typename is_atomic<ATOMIC>::value_type) != sizeof(signed char),
   weak, short)

/// Punned strong CAS; signed char
atomics_make_apply(
   sizeof(typename is_atomic<ATOMIC>::value_type) == sizeof(signed char),
   weak, signed char)

// Done with the macro
#undef atomics_make_apply

} // namespace internal



// -----------------------------------------------------------------------------
// apply: lock
// OPERATION's operator() is embedded into a lock_guard(mutex), giving a limited
// form of atomicity. Understand, however, that mutexes protect code, not data.
// If we run two operations (say, x.add(1) and x.sub(2)) on an atomic variable
// x, with BOTH operations using the lock scheme, then we're good. However, if
// one operation uses lock while the other uses something else (say, one of our
// compare-and-swap schemes), then the latter knows nothing of the mutex! The
// lock scheme would then blindly forge ahead and perform its operation inside
// of an effectively useless mutex (because the other operations isn't using the
// mutex), with the probable result being race conditions. :-(  The take-away
// message: for a given "atomic" variable that's being modified simultaneously
// by multiple threads, use lock for either all, or none, of those threads.
// -----------------------------------------------------------------------------

namespace internal {

/// Apply operation within lock_guard(mutex)
template<class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply(
   ATOMIC &atom,
   const lock,
   const OPERATION &operation
) {
   debug_apply<ATOMIC,OPERATION>("lock");
   std::lock_guard<std::mutex> lock(ATOMIC::singleton_mutex::instance());
   return operation(atom.ref());
}

} // namespace internal



// -----------------------------------------------------------------------------
// apply: serial
// OPERATION's operator() is called plainly, giving no atomicity at all. Use
// for speed in single-threaded contexts. Multi-threaded behavior is UNDEFINED!
// -----------------------------------------------------------------------------

namespace internal {

// NO! unless single-threaded
/// Apply operation plainly, with no atomicity mechanism
template<class ATOMIC, class OPERATION>
inline typename is_atomic<ATOMIC>::value_type apply(
   ATOMIC &atom,
   const serial,
   const OPERATION &operation
) noexcept {
   debug_apply<ATOMIC,OPERATION>("serial");
   return operation(atom.ref());
}

} // namespace internal



// -----------------------------------------------------------------------------
// mineq
// maxeq
// Might as well have these return A &, even if their wrappings into atomic
// operations dumb the return type to A.
// Note: these are intentionally written the way they are, as opposed to using,
// say, std::min and std::max to do the work. The way they're written, A and B
// could both be user-defined types, with only the operator<s and a conversion,
// implicit or explicit, from a B to an A.
// -----------------------------------------------------------------------------

// mineq
/// General "a = min(a,b)"; used by atomic min() functions
template<class A, class B>
inline A &mineq(A &a, const B &b)
{
   if (b < a) a = A(b);
   return a;
}

// maxeq
/// General "a = max(a,b)"; used by atomic max() functions
template<class A, class B>
inline A &maxeq(A &a, const B &b)
{
   if (a < b) a = A(b);
   return a;
}



// -----------------------------------------------------------------------------
// Miscellaneous functions for diagnostic printing.
// Code for this printing was originally located in the atomics-macro-class.h
// and atomics-macro-class-prepost.h files, which are #included multiple times
// later in this file. We moved the printing business here in order to make the
// code in those files less cluttered.
// -----------------------------------------------------------------------------

#ifdef ATOMICS_PRINT
namespace internal {

/// Print debugging info, re: cpp scheme
template<class T, class X>
inline void debug_binary_cpp(
   const char *const name,
   const std::atomic<T> &atom,
   const X &val,
   const std::memory_order sync
) noexcept {
   // Example: operation: std::atomic<long>(10).add(int(1),memory_order_seq_cst)
   std::cout << "   operation: ";
   print_type<std::atomic<T>>();
   std::cout << "(" << T(atom) << ")." << name << "(";
   print_type<X>();
   std::cout << "(" << val << "),";
   print_memord(sync);
   std::cout << ")" << std::endl;
}

/// Print debugging info, re: kokkos scheme
template<class T, class X, class SCHEME, std::size_t NMUX>
inline void debug_binary_kokkos(
   const char *const name,
   const atomics::atomic<T,SCHEME,NMUX> &atom,
   const X &val
) noexcept {
   // Example: operation: Kokkos::atomic_fetch_add(&(long(10)),int(1))
   std::cout << "   operation: ";
   std::cout << "Kokkos::" << name << "(&(";
   print_type<T>();
   std::cout << "(" << T(atom) << ")),";
   print_type<X>();
   std::cout << "(" << val << "))" << std::endl;
}

/// Print debugging info, re: general scheme, binary operation
template<class T, class X>
inline void debug_binary_op(
   const char *const name,
   const T &lhs,
   const X &val
) noexcept {
   // Example: operation: long(10) += int(1)
   std::cout << "   operation: ";
   print_type<T>();
   std::cout << "(" << lhs << ") " << name << " ";
   print_type<X>();
   std::cout << "(" << val << ")" << std::endl;
}

/// Print debugging info, re: general scheme, binary function
template<class T, class X>
inline void debug_binary_fun(
   const char *const name,
   const T &lhs,
   const X &val
) noexcept {
   // Example: operation: mineq(long(10),int(1))
   std::cout << "   operation: ";
   std::cout << name << "(";
   print_type<T>();
   std::cout << "(" << lhs << "),";
   print_type<X>();
   std::cout << "(" << val << "))" << std::endl;
}

/// Print debugging info, re: cpp scheme, unary preincrement/predecrement
template<class T>
inline void debug_unary_cpp_pre(
   const char *const name,
   const std::atomic<T> &atom
) noexcept {
   // Example: operation: ++std::atomic<long>(10)
   std::cout << "   operation: ";
   std::cout << name;
   print_type<std::atomic<T>>();
   std::cout << "(" << T(atom) << ")";
   std::cout << std::endl;
}

/// Print debugging info, re: cpp scheme, unary postincrement/postdecrement
template<class T>
inline void debug_unary_cpp_post(
   const char *const name,
   const std::atomic<T> &atom
) noexcept {
   // Example: operation: std::atomic<long>(10)++
   std::cout << "   operation: ";
   print_type<std::atomic<T>>();
   std::cout << "(" << T(atom) << ")";
   std::cout << name;
   std::cout << std::endl;
}

/// Print debugging info, re: kokkos scheme
template<class T, class SCHEME, std::size_t NMUX>
inline void debug_unary_kokkos(
   const char *const name,
   const atomics::atomic<T,SCHEME,NMUX> &atom
) noexcept {
   // Example: operation: Kokkos::increment(&(long(10)))
   std::cout << "   operation: ";
   std::cout << "Kokkos::" << name << "(&(";
   print_type<T>();
   std::cout << "(" << T(atom) << ")))" << std::endl;
}

/// Print debugging info, re: general scheme, unary preincrement/predecrement
template<class T>
inline void debug_unary_op_pre(
   const char *const name,
   const T &lhs
) noexcept {
   // Example: operation: ++long(10)
   std::cout << "   operation: ";
   std::cout << name;
   print_type<T>();
   std::cout << "(" << lhs << ")";
   std::cout << std::endl;
}

/// Print debugging info, re: general scheme, unary postincrement/postdecrement
template<class T>
inline void debug_unary_op_post(
   const char *const name,
   const T &lhs
) noexcept {
   // Example: operation: long(10)++
   std::cout << "   operation: ";
   print_type<T>();
   std::cout << "(" << lhs << ")";
   std::cout << name;
   std::cout << std::endl;
}

} // namespace internal
#endif // #ifdef ATOMICS_PRINT



// -----------------------------------------------------------------------------
// Functors
// -----------------------------------------------------------------------------

namespace internal {

// ------------------------
// Binary
// ------------------------

// Note: Most of the Kokkos atomic_fetch_* functions take:
//    (volatile T * const, const T).
//
// The exceptions are atomic_fetch_lshift and atomic_fetch_rshift, which take:
//    (volatile T * const, const unsigned).
//
// We'd prefer to just pass parameters through as-is, but doing so creates
// ambiguities in the former cases above: the compiler reports T as being
// indeterminate. To handle this, below, we'll #define atomics_kokkos_to_t
// to indicate that the right-hand side should be converted explicitly to T.
// Where that token *isn't* defined, the right-hand side will be left as-is.

/// Function object for += implementation
#define   atomics_class  addequal
#define   atomics_op     +=
#define   atomics_cpp    fetch_add
#define   atomics_kokkos atomic_fetch_add
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

/// Function object for -= implementation
#define   atomics_class  subequal
#define   atomics_op     -=
#define   atomics_cpp    fetch_sub
#define   atomics_kokkos atomic_fetch_sub
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

/// Function object for *= implementation
#define   atomics_class  mulequal
#define   atomics_op     *=
#define   atomics_kokkos atomic_fetch_mul
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

/// Function object for /= implementation
#define   atomics_class  divequal
#define   atomics_op     /=
#define   atomics_kokkos atomic_fetch_div
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

/// Function object for %= implementation
#define   atomics_class  modequal
#define   atomics_op     %=
#define   atomics_kokkos atomic_fetch_mod
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

/// Function object for <<= implementation
#define   atomics_class  lshiftequal
#define   atomics_op     <<=
#define   atomics_kokkos atomic_fetch_lshift
#include "atomics-macro-class.h"

/// Function object for >>= implementation
#define   atomics_class  rshiftequal
#define   atomics_op     >>=
#define   atomics_kokkos atomic_fetch_rshift
#include "atomics-macro-class.h"

/// Function object for &= implementation
#define   atomics_class  andequal
#define   atomics_op     &=
#define   atomics_cpp    fetch_and
#define   atomics_kokkos atomic_fetch_and
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

/// Function object for |= implementation
#define   atomics_class  orequal
#define   atomics_op     |=
#define   atomics_cpp    fetch_or
#define   atomics_kokkos atomic_fetch_or
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

/// Function object for ^= implementation
#define   atomics_class  xorequal
#define   atomics_op     ^=
#define   atomics_cpp    fetch_xor
#define   atomics_kokkos atomic_fetch_xor
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

/// Function object for "min=" implementation
#define   atomics_class  minequal
#define   atomics_fun    mineq
#define   atomics_kokkos atomic_fetch_min
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

/// Function object for "max=" implementation
#define   atomics_class  maxequal
#define   atomics_fun    maxeq
#define   atomics_kokkos atomic_fetch_max
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"


// ------------------------
// Unary
// ------------------------

/// Function object for ++value implementation
#define   atomics_class  preincclass
#define   atomics_pre    ++
#define   atomics_kokkos atomic_increment
#include "atomics-macro-class-prepost.h"

/// Function object for value++ implementation
#define   atomics_class  postincclass
#define   atomics_post   ++
#define   atomics_kokkos atomic_increment
#include "atomics-macro-class-prepost.h"

/// Function object for --value implementation
#define   atomics_class  predecclass
#define   atomics_pre    --
#define   atomics_kokkos atomic_decrement
#include "atomics-macro-class-prepost.h"

/// Function object for value-- implementation
#define   atomics_class  postdecclass
#define   atomics_post   --
#define   atomics_kokkos atomic_decrement
#include "atomics-macro-class-prepost.h"

} // namespace internal



// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------

// ------------------------
// add() etc.
// ------------------------

/// Function version of atomic +=
#define   atomics_fun   add
#define   atomics_class addequal
#include "atomics-macro-function.h"

/// Function version of atomic -=
#define   atomics_fun   sub
#define   atomics_class subequal
#include "atomics-macro-function.h"

/// Function version of atomic *=
#define   atomics_fun   mul
#define   atomics_class mulequal
#include "atomics-macro-function.h"

/// Function version of atomic /=
#define   atomics_fun   div
#define   atomics_class divequal
#include "atomics-macro-function.h"

/// Function version of atomic %=
#define   atomics_fun   mod
#define   atomics_class modequal
#include "atomics-macro-function.h"

/// Function version of atomic <<=
#define   atomics_fun   lshift
#define   atomics_class lshiftequal
#include "atomics-macro-function.h"

/// Function version of atomic >>=
#define   atomics_fun   rshift
#define   atomics_class rshiftequal
#include "atomics-macro-function.h"

/// Function version of atomic &=
#define   atomics_fun   andeq
#define   atomics_class andequal
#include "atomics-macro-function.h"

/// Function version of atomic |=
#define   atomics_fun   oreq
#define   atomics_class orequal
#include "atomics-macro-function.h"

/// Function version of atomic ^=
#define   atomics_fun   xoreq
#define   atomics_class xorequal
#include "atomics-macro-function.h"

/// Function version of atomic min
#define   atomics_fun   min
#define   atomics_class minequal
#include "atomics-macro-function.h"

/// Function version of atomic max
#define   atomics_fun   max
#define   atomics_class maxequal
#include "atomics-macro-function.h"


// ------------------------
// pre- and post- increment
// and decrement
// ------------------------

// Note:
// inc == preinc
// dec == predec

/// Function version of atomic ++value
#define   atomics_fun   inc
#define   atomics_class preincclass
#include "atomics-macro-function-prepost.h"

/// Function version of atomic ++value
#define   atomics_fun   preinc
#define   atomics_class preincclass
#include "atomics-macro-function-prepost.h"

/// Function version of atomic value++
#define   atomics_fun   postinc
#define   atomics_class postincclass
#include "atomics-macro-function-prepost.h"

/// Function version of atomic --value
#define   atomics_fun   dec
#define   atomics_class predecclass
#include "atomics-macro-function-prepost.h"

/// Function version of atomic --value
#define   atomics_fun   predec
#define   atomics_class predecclass
#include "atomics-macro-function-prepost.h"

/// Function version of atomic value--
#define   atomics_fun   postdec
#define   atomics_class postdecclass
#include "atomics-macro-function-prepost.h"



// -----------------------------------------------------------------------------
// atomic
// -----------------------------------------------------------------------------

/**
This is the primary class in the Ristra Atomics library. For a value of type
atomic<T,...>, the library provides a set of atomic operations that can be
performed on the value. T must be a trivially-copyable type; informally, a
type for which a shallow copy, as with memcpy(), has the correct semantics.

\tparam T
The underlying data type; for example, int, int *, or double. Trivially copyable
user-defined types are allowed. T and SCHEME, together, determine what atomic
operations are available. For example, only operations on integral and pointer
types T are supported by the atomics::cpp scheme, and the atomics::kokkos scheme
has nothing for pointer T.

\tparam SCHEME
The "atomicity scheme," i.e. the methodology by which Ristra Atomics will cause
an operation on a variable of this type to be performed atomically. SCHEME and
T, together, determine what atomic operations can be performed. SCHEME defaults
to strong compare-and-swap (atomics::strong), unless the user has #defined
ATOMICS_DEFAULT_SCHEME to something else before #including atomics.h. The strong
and weak compare-and-swap schemes offer the most flexibility (not necessarily
the best speed) in terms of the availability of operations.

\tparam NMUX
This optimization feature, for advanced users, is relevant only in concert with
the atomics::lock atomicity scheme. Via NMUX, two variables that would otherwise
have the same atomic<T,SCHEME> type can instead be outfitted with different
"singleton" mutexes, so that any atomic operations being performed on one won't
unnecessarily stall any atomic operations being performed on the other.
*/

template<class T, class SCHEME, std::size_t NMUX>
class atomic : public std::atomic<T> {

   // T must be trivially copyable.
   // std::atomic<T> already checks this, but we might
   // as well make the error message more direct.
   static_assert(
      std::is_trivially_copyable<T>::value,
     "atomics::atomic requires a trivially copyable type"
   );

   // BASE
   using BASE = std::atomic<T>;

public:

   // ------------------------
   // A singleton std::mutex
   // for each atomic<> type.
   // ------------------------

   /// Produce a singleton mutex for this specific atomic<> type instantiation
   class singleton_mutex {
      // private!
      inline singleton_mutex() noexcept
      { }
      inline singleton_mutex(const singleton_mutex &) noexcept
      { }
      inline singleton_mutex &operator=(const singleton_mutex &) noexcept
      { return *this; }
   public:
      static inline std::mutex &instance() noexcept
      {
         static std::mutex mux;
         return mux;
      }
   };


   // ------------------------
   // Basics
   // ------------------------

   // For whomever might use them
   using value_type  = T;
   using scheme_type = SCHEME;
   static constexpr std::size_t nmux = NMUX;

   // Constructors
   // As for std::atomic
   inline atomic() noexcept
   {
      (void)singleton_mutex::instance();
   }

   inline constexpr atomic(const T &val) noexcept : BASE(val)
   {
      (void)singleton_mutex::instance();
   };

   inline atomic(const atomic &) = delete;

   // Assignment
   // As for std::atomic:
   //    T operator= (T val) noexcept;
   //    T operator= (T val) volatile noexcept;
   //    atomic& operator= (const atomic&) = delete;
   //    atomic& operator= (const atomic&) volatile = delete;
   // See http://www.cplusplus.com/reference/atomic/atomic/operator=/
   using BASE::operator=;

   // Conversion to T
   // For now I'll have *explicit* operator Ts, instead of inheriting
   // std::atomic's implicit ones. It seems safer, but may not matter
   // in the (probably rvalue) contexts in which it would most likely
   // be invoked. Let's see how our atomic's usability shakes out.
   inline explicit operator T() const          noexcept { return T(base()); }
   inline explicit operator T() const volatile noexcept { return T(base()); }

   // ref()
   // Get reference to underlying data, via reinterpret_cast.
   // Know what you're doing if you use any of these.
   #define atomics_make_ref(cv) \
      inline cv T &ref() cv noexcept \
      { \
         atomics_assert(sizeof(*this) == sizeof(T)); \
         return *reinterpret_cast<cv T *const>(this); \
      }

   /// Return reference to contained data, via reinterpret_cast
   atomics_make_ref()
   atomics_make_ref(const)
   atomics_make_ref(volatile)
   atomics_make_ref(const volatile)
   #undef atomics_make_ref


   // ------------------------
   // Miscellaneous functions
   // ------------------------

   // base()
   /// Return reference to underlying std::atomic
   inline                BASE &base()                noexcept { return *this; }
   inline const          BASE &base() const          noexcept { return *this; }
   inline       volatile BASE &base()       volatile noexcept { return *this; }
   inline const volatile BASE &base() const volatile noexcept { return *this; }

   // Regarding std::atomic's is_lock_free() function:
   // Given that we handle our own atomic's atomicity in possibly a different
   // way from how std::atomic handles theirs, it might be misleading to allow
   // an is_lock_free() query. So, for now, I decided to delete these. I could
   // probably be convinced to *not* do this. Bear in mind that you can always
   // still get to the functions, via the std::atomic base class.
   inline bool is_lock_free() const          noexcept = delete;
   inline bool is_lock_free() const volatile noexcept = delete;


   // ------------------------
   // Atomic functions:
   // add() etc.
   // ------------------------

   /// Member function version of atomic +=
   #define   atomics_fun add
   #include "atomics-macro-member.h"

   /// Member function version of atomic -=
   #define   atomics_fun sub
   #include "atomics-macro-member.h"

   /// Member function version of atomic *=
   #define   atomics_fun mul
   #include "atomics-macro-member.h"

   /// Member function version of atomic /=
   #define   atomics_fun div
   #include "atomics-macro-member.h"

   /// Member function version of atomic %=
   #define   atomics_fun mod
   #include "atomics-macro-member.h"

   /// Member function version of atomic <<=
   #define   atomics_fun lshift
   #include "atomics-macro-member.h"

   /// Member function version of atomic >>=
   #define   atomics_fun rshift
   #include "atomics-macro-member.h"

   /// Member function version of atomic &=
   #define   atomics_fun andeq
   #include "atomics-macro-member.h"

   /// Member function version of atomic |=
   #define   atomics_fun oreq
   #include "atomics-macro-member.h"

   /// Member function version of atomic ^=
   #define   atomics_fun xoreq
   #include "atomics-macro-member.h"

   /// Member function version of atomic min
   #define   atomics_fun min
   #include "atomics-macro-member.h"

   /// Member function version of atomic max
   #define   atomics_fun max
   #include "atomics-macro-member.h"


   // ------------------------
   // Atomic functions:
   // pre- and post- increment
   // and decrement
   // ------------------------

   // Note:
   // inc == preinc
   // dec == predec

   /// Member function version of atomic ++value
   #define   atomics_fun inc
   #include "atomics-macro-member-prepost.h"

   /// Member function version of atomic ++value
   #define   atomics_fun preinc
   #include "atomics-macro-member-prepost.h"

   /// Member function version of atomic value++
   #define   atomics_fun postinc
   #include "atomics-macro-member-prepost.h"

   /// Member function version of atomic --value
   #define   atomics_fun dec
   #include "atomics-macro-member-prepost.h"

   /// Member function version of atomic --value
   #define   atomics_fun predec
   #include "atomics-macro-member-prepost.h"

   /// Member function version of atomic value--
   #define   atomics_fun postdec
   #include "atomics-macro-member-prepost.h"
};



// -----------------------------------------------------------------------------
// Operators
// Consistent with std::atomic's behavior, these return T, not T &.
// -----------------------------------------------------------------------------

// ------------------------
// Binary
// ------------------------

/// Atomic +=
#define   atomics_op  +=
#define   atomics_fun add
#include "atomics-macro-operator.h"

/// Atomic -=
#define   atomics_op  -=
#define   atomics_fun sub
#include "atomics-macro-operator.h"

/// Atomic *=
#define   atomics_op  *=
#define   atomics_fun mul
#include "atomics-macro-operator.h"

/// Atomic /=
#define   atomics_op  /=
#define   atomics_fun div
#include "atomics-macro-operator.h"

/// Atomic %=
#define   atomics_op  %=
#define   atomics_fun mod
#include "atomics-macro-operator.h"

/// Atomic <<=
#define   atomics_op  <<=
#define   atomics_fun lshift
#include "atomics-macro-operator.h"

/// Atomic >>=
#define   atomics_op  >>=
#define   atomics_fun rshift
#include "atomics-macro-operator.h"

/// Atomic &=
#define   atomics_op  &=
#define   atomics_fun andeq
#include "atomics-macro-operator.h"

/// Atomic |=
#define   atomics_op  |=
#define   atomics_fun oreq
#include "atomics-macro-operator.h"

/// Atomic ^=
#define   atomics_op  ^=
#define   atomics_fun xoreq
#include "atomics-macro-operator.h"


// ------------------------
// Unary
// ------------------------

/// Atomic ++value
#define   atomics_op   ++
#define   atomics_pre
#define   atomics_fun  preinc
#include "atomics-macro-operator-prepost.h"

/// Atomic value++
#define   atomics_op   ++
#define   atomics_post
#define   atomics_fun  postinc
#include "atomics-macro-operator-prepost.h"

/// Atomic --value
#define   atomics_op   --
#define   atomics_pre
#define   atomics_fun  predec
#include "atomics-macro-operator-prepost.h"

/// Atomic value--
#define   atomics_op   --
#define   atomics_post
#define   atomics_fun  postdec
#include "atomics-macro-operator-prepost.h"



// -----------------------------------------------------------------------------
// Miscellaneous conveniences
// -----------------------------------------------------------------------------

// Shorthand
using Float  = atomics::atomic< float,       ATOMICS_DEFAULT_SCHEME, 0 >;
using Double = atomics::atomic< double,      ATOMICS_DEFAULT_SCHEME, 0 >;
using Quad   = atomics::atomic< long double, ATOMICS_DEFAULT_SCHEME, 0 >;

// operator<<
template<class T, class SCHEME, std::size_t NMUX>
inline std::ostream &operator<<(
   std::ostream &os,
   const volatile atomic<T,SCHEME,NMUX> &obj
) {
   return os << T(obj);
}



// -----------------------------------------------------------------------------
// Done
// -----------------------------------------------------------------------------

#undef _atomics_stringify
#undef  atomics_stringify

} // namespace atomics
} // namespace ristra

#endif
