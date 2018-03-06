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

#ifndef ristra_atomics_h
#define ristra_atomics_h

// C++
#include <atomic>
#include <cstddef>
#include <mutex>
#include <type_traits>

// Kokkos (optional)
#if defined(ATOMICS_KOKKOS)
#include "Kokkos_Atomic.hpp"
#endif

// For debug-mode assertions
#if defined(ATOMICS_DEBUG)
#include <cassert>
#endif

// For print-mode printing
#if defined(ATOMICS_PRINT)
#include <iostream>
#include "boost/core/demangle.hpp"
#endif

// Everything in the rest of this file is placed into the following namespaces.
// Helper constructs, scattered throughout the file, are additionally placed
// into a namespace called "internal" wherever they appear. That's my way of
// saying, "for internal use; call directly only if you know what you're doing."
namespace ristra {
namespace atomics {



// -----------------------------------------------------------------------------
// Schemes for achieving atomicity
// Represented by classes, to be used for overloading
// -----------------------------------------------------------------------------

// Use the built-in C++ std::atomic capabilities
struct cpp { };

// Use Kokkos
#if defined(ATOMICS_KOKKOS)
   struct kokkos { };
#endif

// Our own schemes
struct strong { struct pun { }; };
struct weak   { struct pun { }; };
struct lock   { };
struct serial { };

// Alternative notation
struct pun {
   using strong = atomics::strong::pun;
   using weak   = atomics::weak  ::pun;
};
using mutex = lock; // our mutex, not std::'s

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

// print_var
// Simple macro for printing something's name and value.
#define print_var(x) std::cout << #x " == " << (x) << std::endl

#if defined(ATOMICS_PRINT)

// print_type
// Prints type T's type name as determined by Boost's demangle().
template<class T>
inline void print_type() noexcept
{
   std::cout << boost::core::demangle(typeid(T).name());
}

// print_mord
// Prints the name of a std::memory_order value.
inline void print_mord(const std::memory_order sync) noexcept
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

template<class SCHEME, class S>
struct get_scheme {
   using scheme = S;
};

template<class SCHEME>
struct get_scheme<SCHEME,char> {
   using scheme = SCHEME;
};

} // namespace internal



// -----------------------------------------------------------------------------
// debug_apply
// Called from the various apply() functions, to print debugging information.
// No-ops, unless ATOMICS_PRINT is #defined. There are enough calls to these
// functions that making them no-ops like this was shorter than preprocessing
// out the calls themselves.
// -----------------------------------------------------------------------------

namespace internal {

// scheme
template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline void debug_apply(
   const char *const scheme
) noexcept {
   #if defined(ATOMICS_PRINT)
      std::cout << "apply\n";
      std::cout << "   left side: ";  print_type<atomic<T,SCHEME,NMUX>>();
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
template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline void debug_apply(
   const char *const scheme,
   const std::memory_order sync
) noexcept {
   #if defined(ATOMICS_PRINT)
      std::cout << "apply\n";
      std::cout << "   left side: ";  print_type<atomic<T,SCHEME,NMUX>>();
      std::cout << "\n";
      std::cout << "   scheme   : " << scheme << "\n";
      std::cout << "   function : ";  print_type<OPERATION>();
      std::cout << "\n";
      std::cout << "   sync     : ";  print_mord(sync);
      std::cout << "   T/return : ";  print_type<T>();
      std::cout << "\n";
   #else
      // disappear unused-parameter warnings
      (void)scheme;
      (void)sync;
   #endif
}

// scheme; memory order success, failure
template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline void debug_apply(
   const char *const scheme,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   #if defined(ATOMICS_PRINT)
      std::cout << "apply\n";
      std::cout << "   left side: ";  print_type<atomic<T,SCHEME,NMUX>>();
      std::cout << "\n";
      std::cout << "   scheme   : " << scheme << "\n";
      std::cout << "   function : ";  print_type<OPERATION>();
      std::cout << "\n";
      std::cout << "   success  : ";  print_mord(success);
      std::cout << "   failure  : ";  print_mord(failure);
      std::cout << "   T/return : ";  print_type<T>();
      std::cout << "\n";
   #else
      (void)scheme;
      (void)success;
      (void)failure;
   #endif
}

// scheme; pun
template<class T, class SCHEME, std::size_t NMUX, class OPERATION, class P>
inline void debug_apply(
   const char *const scheme
) noexcept {
   debug_apply<T,SCHEME,NMUX,OPERATION>(scheme);
   #if defined(ATOMICS_PRINT)
      std::cout << "   P/pun    : ";
      print_type<P>();
      std::cout << "\n";
   #endif
}

// scheme; memory_order sync; pun
template<class T, class SCHEME, std::size_t NMUX, class OPERATION, class P>
inline void debug_apply(
   const char *const scheme,
   const std::memory_order sync
) noexcept {
   debug_apply<T,SCHEME,NMUX,OPERATION>(scheme,sync);
   #if defined(ATOMICS_PRINT)
      std::cout << "   P/pun    : ";
      print_type<P>();
      std::cout << "\n";
   #endif
}

// scheme; memory_order success, failure; pun
template<class T, class SCHEME, std::size_t NMUX, class OPERATION, class P>
inline void debug_apply(
   const char *const scheme,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   debug_apply<T,SCHEME,NMUX,OPERATION>(scheme,success,failure);
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

atomics_make_compexch_punned(punxstrong,         , compare_exchange_strong)
atomics_make_compexch_punned(punxstrong, volatile, compare_exchange_strong)
atomics_make_compexch_punned(punxweak,           , compare_exchange_weak)
atomics_make_compexch_punned(punxweak,   volatile, compare_exchange_weak)

#undef atomics_make_compexch_punned

} // namespace internal



// -----------------------------------------------------------------------------
// apply: cpp
// OPERATION should have an appropriate operator() that forwards
// to an available underlying std::atomic member function.
// -----------------------------------------------------------------------------

namespace internal {

// no "memory order"
template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply(
   atomic<T,SCHEME,NMUX> &atom,
   const cpp,
   const OPERATION &operation
) noexcept {
   debug_apply<T,SCHEME,NMUX,OPERATION>("cpp");
   return operation(atom.base(),cpp{});
}

// memory order sync
template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply(
   atomic<T,SCHEME,NMUX> &atom,
   const cpp,
   const OPERATION &operation,
   const std::memory_order sync
) noexcept {
   debug_apply<T,SCHEME,NMUX,OPERATION>("cpp",sync);
   return operation(atom.base(),cpp{},sync);
}

} // namespace internal



// -----------------------------------------------------------------------------
// apply: kokkos
// OPERATION should have an appropriate operator() that forwards
// to an available underlying Kokkos:: function.
// -----------------------------------------------------------------------------

namespace internal {
#if defined(ATOMICS_KOKKOS)

template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply(
   atomic<T,SCHEME,NMUX> &atom,
   const kokkos,
   const OPERATION &operation
) noexcept {
   debug_apply<T,SCHEME,NMUX,OPERATION>("kokkos");
   return operation(atom,kokkos{});
}

#endif // #if defined(ATOMICS_KOKKOS)
} // namespace internal



// -----------------------------------------------------------------------------
// apply: strong
// OPERATION's operator() is embedded here into a strong compare-and-swap,
// in order to achieve atomicity with respect to the destination datum.
// Bear in mind that the compare-and-swap scheme doesn't atomicize any side
// effects (e.g. printing) that may occur when the operation is applied!!
// It just ensures that the destination ("atom" here) is updated atomically.
// -----------------------------------------------------------------------------

namespace internal {

// memory order sync
template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply(
   atomic<T,SCHEME,NMUX> &atom,
   const strong,
   const OPERATION &operation,
   const std::memory_order sync = std::memory_order_seq_cst
) noexcept {
   debug_apply<T,SCHEME,NMUX,OPERATION>("strong",sync);

   T old = T(atom);
   T neu, rv;

   do {
      neu = old;
      rv = operation(neu);
   } while (!atom.compare_exchange_strong(old, neu, sync));

   return rv;
}

// memory order success, failure
template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply(
   atomic<T,SCHEME,NMUX> &atom,
   const strong,
   const OPERATION &operation,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   debug_apply<T,SCHEME,NMUX,OPERATION>("strong", success, failure);

   T old = T(atom);
   T neu, rv;

   do {
      neu = old;
      rv = operation(neu);
   } while (!atom.compare_exchange_strong(old, neu, success, failure));

   return rv;
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

template<class P, class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply_pun(
   atomic<T,SCHEME,NMUX> &atom,
   const strong::pun,
   const OPERATION &operation,
   const std::memory_order sync
) {
   debug_apply<T,SCHEME,NMUX,OPERATION,P>("strong::pun",sync);

   union u {
      T tee;
      P pun;
      // Need default ctor on this and similar unions, to avoid
      // error due to call to implicitly-deleted default ctor
      inline u() { }
   } old, neu;
   old.tee = T(atom);

   atomics_assert(sizeof(old) == sizeof(T));
   atomics_assert(sizeof(old) == sizeof(P));

   T rv;
   do {
      neu.pun = old.pun;
      rv = operation(neu.tee);
   } while (!punxstrong(atom, old.pun, neu.pun, sync));

   return rv;
}

template<class P, class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply_pun(
   atomic<T,SCHEME,NMUX> &atom,
   const strong::pun,
   const OPERATION &operation,
   const std::memory_order success,
   const std::memory_order failure
) {
   debug_apply<T,SCHEME,NMUX,OPERATION,P>("strong::pun", success, failure);

   union u {
      T tee;
      P pun;
      inline u() { }
   } old, neu;
   old.tee = T(atom);

   atomics_assert(sizeof(old) == sizeof(T));
   atomics_assert(sizeof(old) == sizeof(P));

   T rv;
   do {
      neu.pun = old.pun;
      rv = operation(neu.tee);
   } while (!punxstrong(atom, old.pun, neu.pun, success, failure));

   return rv;
}


// ------------------------
// Helper macro
// ------------------------

#define atomics_make_apply(condition,cas,P) \
   template<class T, class SCHEME, std::size_t NMUX, class OPERATION> \
   inline typename std::enable_if<condition,T>::type apply( \
      atomic<T,SCHEME,NMUX> &atom, \
      const cas::pun, \
      const OPERATION &operation, \
      const std::memory_order sync = std::memory_order_seq_cst \
   ) { \
      return apply_pun<P>(atom, cas::pun{}, operation, sync); \
   } \
   \
   template<class T, class SCHEME, std::size_t NMUX, class OPERATION> \
   inline typename std::enable_if<condition,T>::type apply( \
      atomic<T,SCHEME,NMUX> &atom, \
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

// != requirements are sufficient, because sizeof(short) <= sizeof(int) <= ...

// for long long
atomics_make_apply(
   sizeof(T) == sizeof(long long) &&
   sizeof(T) != sizeof(long),
   strong, long long)

// for long
atomics_make_apply(
   sizeof(T) == sizeof(long) &&
   sizeof(T) != sizeof(int),
   strong, long)

// for int
atomics_make_apply(
   sizeof(T) == sizeof(int) &&
   sizeof(T) != sizeof(short),
   strong, int)

// for short
atomics_make_apply(
   sizeof(T) == sizeof(short) &&
   sizeof(T) != sizeof(signed char),
   strong, short)

// for signed char
atomics_make_apply(
   sizeof(T) == sizeof(signed char),
   strong, signed char)

} // namespace internal



// -----------------------------------------------------------------------------
// apply: weak
// OPERATION's operator() is embedded here into a weak compare-and-swap,
// in order to achieve atomicity with respect to the destination datum.
// -----------------------------------------------------------------------------

namespace internal {

// memory order sync
template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply(
   atomic<T,SCHEME,NMUX> &atom,
   const weak,
   const OPERATION &operation,
   const std::memory_order sync = std::memory_order_seq_cst
) noexcept {
   debug_apply<T,SCHEME,NMUX,OPERATION>("weak",sync);

   T old = T(atom);
   T neu, rv;

   do {
      neu = old;
      rv = operation(neu);
   } while (!atom.compare_exchange_weak(old, neu, sync));

   return rv;
}

// memory order success, failure
template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply(
   atomic<T,SCHEME,NMUX> &atom,
   const weak,
   const OPERATION &operation,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   debug_apply<T,SCHEME,NMUX,OPERATION>("weak", success, failure);

   T old = T(atom);
   T neu, rv;

   do {
      neu = old;
      rv = operation(neu);
   } while (!atom.compare_exchange_weak(old, neu, success, failure));

   return rv;
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

template<class P, class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply_pun(
   atomic<T,SCHEME,NMUX> &atom,
   const weak::pun,
   const OPERATION &operation,
   const std::memory_order sync
) {
   debug_apply<T,SCHEME,NMUX,OPERATION,P>("weak::pun",sync);

   union u {
      T tee;
      P pun;
      inline u() { }
   } old, neu;
   old.tee = T(atom);

   atomics_assert(sizeof(old) == sizeof(T));
   atomics_assert(sizeof(old) == sizeof(P));

   T rv;
   do {
      neu.pun = old.pun;
      rv = operation(neu.tee);
   } while (!punxweak(atom, old.pun, neu.pun, sync));

   return rv;
}

template<class P, class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply_pun(
   atomic<T,SCHEME,NMUX> &atom,
   const weak::pun,
   const OPERATION &operation,
   const std::memory_order success,
   const std::memory_order failure
) {
   debug_apply<T,SCHEME,NMUX,OPERATION,P>("weak::pun", success, failure);

   union u {
      T tee;
      P pun;
      inline u() { }
   } old, neu;
   old.tee = T(atom);

   atomics_assert(sizeof(old) == sizeof(T));
   atomics_assert(sizeof(old) == sizeof(P));

   T rv;
   do {
      neu.pun = old.pun;
      rv = operation(neu.tee);
   } while (!punxweak(atom, old.pun, neu.pun, success, failure));

   return rv;
}


// ------------------------
// Puns to several plain
// old integral types
// ------------------------

// Re-use the macro from the strong::pun section...

// for long long
atomics_make_apply(
   sizeof(T) == sizeof(long long) &&
   sizeof(T) != sizeof(long),
   weak, long long)

// for long
atomics_make_apply(
   sizeof(T) == sizeof(long) &&
   sizeof(T) != sizeof(int),
   weak, long)

// for int
atomics_make_apply(
   sizeof(T) == sizeof(int) &&
   sizeof(T) != sizeof(short),
   weak, int)

// for short
atomics_make_apply(
   sizeof(T) == sizeof(short) &&
   sizeof(T) != sizeof(signed char),
   weak, short)

// for signed char
atomics_make_apply(
   sizeof(T) == sizeof(signed char),
   weak, signed char)

// Done with the macro
#undef atomics_make_apply

} // namespace internal



// -----------------------------------------------------------------------------
// apply: lock/mutex
// OPERATION's operator() is embedded into a lock_guard(mutex),
// giving effective, albeit simplistic and possibly slow, atomicity.
// -----------------------------------------------------------------------------

namespace internal {

template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply(
   atomic<T,SCHEME,NMUX> &atom,
   const lock,
   const OPERATION &operation
) {
   debug_apply<T,SCHEME,NMUX,OPERATION>("lock");
   std::lock_guard<std::mutex> lock(atomic<T,SCHEME,NMUX>::mutex::instance());
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
template<class T, class SCHEME, std::size_t NMUX, class OPERATION>
inline T apply(
   atomic<T,SCHEME,NMUX> &atom,
   const serial,
   const OPERATION &operation
) noexcept {
   debug_apply<T,SCHEME,NMUX,OPERATION>("serial");
   return operation(atom.ref());
}

} // namespace internal



// -----------------------------------------------------------------------------
// mineq
// maxeq
// Might as well have these return T &, even if their wrappings into atomic
// operations dumb the return type to T.
// -----------------------------------------------------------------------------

// mineq
template<class T, class X>
inline T &mineq(T &a, const X &b)
{
   if (b < a) a = T(b);
   return a;
}

// maxeq
template<class T, class X>
inline T &maxeq(T &a, const X &b)
{
   if (a < b) a = T(b);
   return a;
}



// -----------------------------------------------------------------------------
// Miscellaneous functions for diagnostic printing.
// Code for this printing was originally located in the atomics-macro-class.h
// and atomics-macro-class-prepost.h files, which are #included multiple times
// later in this file. We moved the printing business here in order to make the
// primary code in those files clearer and less cluttered.
// -----------------------------------------------------------------------------

namespace internal {
#ifdef ATOMICS_PRINT

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
   print_mord(sync);
   std::cout << ")" << std::endl;
}

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

#endif // #ifdef ATOMICS_PRINT
} // namespace internal



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

// +=
#define   atomics_class  addequal
#define   atomics_op     +=
#define   atomics_cpp    fetch_add
#define   atomics_kokkos atomic_fetch_add
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

// -=
#define   atomics_class  subequal
#define   atomics_op     -=
#define   atomics_cpp    fetch_sub
#define   atomics_kokkos atomic_fetch_sub
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

// *=
#define   atomics_class  mulequal
#define   atomics_op     *=
#define   atomics_kokkos atomic_fetch_mul
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

// /=
#define   atomics_class  divequal
#define   atomics_op     /=
#define   atomics_kokkos atomic_fetch_div
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

// %=
#define   atomics_class  modequal
#define   atomics_op     %=
#define   atomics_kokkos atomic_fetch_mod
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

// <<=
#define   atomics_class  lshiftequal
#define   atomics_op     <<=
#define   atomics_kokkos atomic_fetch_lshift
#include "atomics-macro-class.h"

// >>=
#define   atomics_class  rshiftequal
#define   atomics_op     >>=
#define   atomics_kokkos atomic_fetch_rshift
#include "atomics-macro-class.h"

// &=
#define   atomics_class  andequal
#define   atomics_op     &=
#define   atomics_cpp    fetch_and
#define   atomics_kokkos atomic_fetch_and
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

// |=
#define   atomics_class  orequal
#define   atomics_op     |=
#define   atomics_cpp    fetch_or
#define   atomics_kokkos atomic_fetch_or
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

// ^=
#define   atomics_class  xorequal
#define   atomics_op     ^=
#define   atomics_cpp    fetch_xor
#define   atomics_kokkos atomic_fetch_xor
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

// "min="
#define   atomics_class  minequal
#define   atomics_fun    mineq
#define   atomics_kokkos atomic_fetch_min
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"

// "max="
#define   atomics_class  maxequal
#define   atomics_fun    maxeq
#define   atomics_kokkos atomic_fetch_max
#define   atomics_kokkos_to_t
#include "atomics-macro-class.h"


// ------------------------
// Unary
// ------------------------

// ++value
#define   atomics_class  preincclass
#define   atomics_pre    ++
#define   atomics_kokkos atomic_increment
#include "atomics-macro-class-prepost.h"

// value++
#define   atomics_class  postincclass
#define   atomics_post   ++
#define   atomics_kokkos atomic_increment
#include "atomics-macro-class-prepost.h"

// --value
#define   atomics_class  predecclass
#define   atomics_pre    --
#define   atomics_kokkos atomic_decrement
#include "atomics-macro-class-prepost.h"

// value--
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

#define   atomics_fun   add
#define   atomics_class addequal
#include "atomics-macro-function.h"

#define   atomics_fun   sub
#define   atomics_class subequal
#include "atomics-macro-function.h"

#define   atomics_fun   mul
#define   atomics_class mulequal
#include "atomics-macro-function.h"

#define   atomics_fun   div
#define   atomics_class divequal
#include "atomics-macro-function.h"

#define   atomics_fun   mod
#define   atomics_class modequal
#include "atomics-macro-function.h"

#define   atomics_fun   lshift
#define   atomics_class lshiftequal
#include "atomics-macro-function.h"

#define   atomics_fun   rshift
#define   atomics_class rshiftequal
#include "atomics-macro-function.h"

// can't call it and
#define   atomics_fun   andeq
#define   atomics_class andequal
#include "atomics-macro-function.h"

// can't call it or
#define   atomics_fun   oreq
#define   atomics_class orequal
#include "atomics-macro-function.h"

// can't call it xor
#define   atomics_fun   xoreq
#define   atomics_class xorequal
#include "atomics-macro-function.h"

#define   atomics_fun   min
#define   atomics_class minequal
#include "atomics-macro-function.h"

#define   atomics_fun   max
#define   atomics_class maxequal
#include "atomics-macro-function.h"


// ------------------------
// pre- and post- increment
// and decrement
// ------------------------

// inc == preinc
#define   atomics_fun   inc
#define   atomics_class preincclass
#include "atomics-macro-function-prepost.h"

#define   atomics_fun   preinc
#define   atomics_class preincclass
#include "atomics-macro-function-prepost.h"

#define   atomics_fun   postinc
#define   atomics_class postincclass
#include "atomics-macro-function-prepost.h"

// dec == predec
#define   atomics_fun   dec
#define   atomics_class predecclass
#include "atomics-macro-function-prepost.h"

#define   atomics_fun   predec
#define   atomics_class predecclass
#include "atomics-macro-function-prepost.h"

#define   atomics_fun   postdec
#define   atomics_class postdecclass
#include "atomics-macro-function-prepost.h"



// -----------------------------------------------------------------------------
// atomic
// -----------------------------------------------------------------------------

template<class T, class SCHEME, std::size_t NMUX>
class atomic : public std::atomic<T> {

   // T must be trivially copyable
   static_assert(
      std::is_trivially_copyable<T>::value,
     "atomics::atomic requires a trivially copyable type"
   );

   // BASE
   using BASE = std::atomic<T>;

public:

   // ------------------------
   // Singleton std::mutex
   // ------------------------

   class mutex {
      inline mutex() noexcept { }
      inline mutex(const mutex &) noexcept { }
      inline mutex &operator=(const mutex &) noexcept { return *this; }
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

   // Constructors
   // As for std::atomic
   inline atomic() noexcept
   {
      (void)mutex::instance();
   }

   inline constexpr atomic(const T &val) noexcept : BASE(val)
   {
      (void)mutex::instance();
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
   #define atomics_make_ref(cv,type) \
      inline cv type &ref() cv noexcept \
      { \
         atomics_assert(sizeof(*this) == sizeof(type)); \
         return *reinterpret_cast<type *const>(this); \
      }
   atomics_make_ref(               , T)
   atomics_make_ref(const          , T)
   atomics_make_ref(      volatile , T)
   atomics_make_ref(const volatile , T)
   #undef atomics_make_ref


   // ------------------------
   // Miscellaneous functions
   // ------------------------

   // base()
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

   #define   atomics_fun add
   #include "atomics-macro-member.h"

   #define   atomics_fun sub
   #include "atomics-macro-member.h"

   #define   atomics_fun mul
   #include "atomics-macro-member.h"

   #define   atomics_fun div
   #include "atomics-macro-member.h"

   #define   atomics_fun mod
   #include "atomics-macro-member.h"

   #define   atomics_fun lshift
   #include "atomics-macro-member.h"

   #define   atomics_fun rshift
   #include "atomics-macro-member.h"

   #define   atomics_fun andeq
   #include "atomics-macro-member.h"

   #define   atomics_fun oreq
   #include "atomics-macro-member.h"

   #define   atomics_fun xoreq
   #include "atomics-macro-member.h"

   #define   atomics_fun min
   #include "atomics-macro-member.h"

   #define   atomics_fun max
   #include "atomics-macro-member.h"


   // ------------------------
   // Atomic functions:
   // pre- and post- increment
   // and decrement
   // ------------------------

   // inc == preinc
   #define   atomics_fun inc
   #include "atomics-macro-member-prepost.h"

   #define   atomics_fun preinc
   #include "atomics-macro-member-prepost.h"

   #define   atomics_fun postinc
   #include "atomics-macro-member-prepost.h"

   // dec == predec
   #define   atomics_fun dec
   #include "atomics-macro-member-prepost.h"

   #define   atomics_fun predec
   #include "atomics-macro-member-prepost.h"

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

// +=
#define   atomics_op  +=
#define   atomics_fun add
#include "atomics-macro-operator.h"

// -=
#define   atomics_op  -=
#define   atomics_fun sub
#include "atomics-macro-operator.h"

// *=
#define   atomics_op  *=
#define   atomics_fun mul
#include "atomics-macro-operator.h"

// /=
#define   atomics_op  /=
#define   atomics_fun div
#include "atomics-macro-operator.h"

// %=
#define   atomics_op  %=
#define   atomics_fun mod
#include "atomics-macro-operator.h"

// <<=
#define   atomics_op  <<=
#define   atomics_fun lshift
#include "atomics-macro-operator.h"

// >>=
#define   atomics_op  >>=
#define   atomics_fun rshift
#include "atomics-macro-operator.h"

// &=
#define   atomics_op  &=
#define   atomics_fun andeq
#include "atomics-macro-operator.h"

// |=
#define   atomics_op  |=
#define   atomics_fun oreq
#include "atomics-macro-operator.h"

// ^=
#define   atomics_op  ^=
#define   atomics_fun xoreq
#include "atomics-macro-operator.h"


// ------------------------
// Unary
// ------------------------

// ++value
#define   atomics_op   ++
#define   atomics_pre
#define   atomics_fun  preinc
#include "atomics-macro-operator-prepost.h"

// value++
#define   atomics_op   ++
#define   atomics_post
#define   atomics_fun  postinc
#include "atomics-macro-operator-prepost.h"

// --value
#define   atomics_op   --
#define   atomics_pre
#define   atomics_fun  predec
#include "atomics-macro-operator-prepost.h"

// value--
#define   atomics_op   --
#define   atomics_post
#define   atomics_fun  postdec
#include "atomics-macro-operator-prepost.h"



// -----------------------------------------------------------------------------
// Miscellaneous conveniences
// -----------------------------------------------------------------------------

// Shorthand
using Float  = atomics::atomic<float,       ATOMICS_DEFAULT_SCHEME, 0>;
using Double = atomics::atomic<double,      ATOMICS_DEFAULT_SCHEME, 0>;
using Quad   = atomics::atomic<long double, ATOMICS_DEFAULT_SCHEME, 0>;

// operator<<
template<class T, class SCHEME, std::size_t NMUX>
inline std::ostream &operator<<(
   std::ostream &os,
   const atomic<T,SCHEME,NMUX> &obj
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
