
// Make a class with operator()s that implement "+=" and other operations
// that require an argument in addition to the atomic left-hand side. The
// atomics_* tokens are #defined before coming here.

template<class X>
class atomics_class {
   const X val;

public:

   // constructor
   inline explicit atomics_class(const X _val) noexcept : val(_val) { }


   // ------------------------
   // operator() for cpp
   // ------------------------

   // Apply std::atomic's member function atomics_cpp
   #if defined(atomics_cpp)
   template<class STDATOMIC>
   inline typename is_std_atomic<STDATOMIC>::value_type operator()(
      STDATOMIC &atom,
      const cpp,
      const std::memory_order sync = std::memory_order_seq_cst
   ) const noexcept {
      using T = typename is_std_atomic<STDATOMIC>::value_type;
      #ifdef ATOMICS_PRINT
         debug_binary_cpp(atomics_stringify(atomics_cpp),atom,val,sync);
      #endif

      // std::atomic<>'s fetch_add() etc. return the contained value BEFORE
      // the call, which is inconsistent with what we expect from "+=" etc.,
      // and with what we get from our other atomicity schemes (below). So,
      // we split the call and the return.
      atom.atomics_cpp(val,sync); // e.g. atom.fetch_add(val,sync)
      return T(atom);
   }
   #endif


   // ------------------------
   // operator() for kokkos
   // ------------------------

   // Apply Kokkos' function atomics_kokkos
   #if defined(ATOMICS_KOKKOS) // <== using Kokkos at all?
   #if defined(atomics_kokkos) // <== Kokkos supports this operation?
   template<class ATOMIC>
   inline typename is_atomic<ATOMIC>::value_type operator()(
      ATOMIC &atom,
      const kokkos // for overload resolution vs. other operator()s
   ) const {
      using T = typename is_atomic<ATOMIC>::value_type;
      #ifdef ATOMICS_PRINT
         debug_binary_kokkos(atomics_stringify(atomics_kokkos),atom,val);
      #endif
      #if defined(atomics_kokkos_to_t)
         // For most of the Kokkos functions, convert the right-hand side
         // to T; without this, different left- and right-hand sides would
         // make their Ts indeterminate.
         Kokkos::atomics_kokkos(&atom.ref(), T(val));
      #else
         // For the atomic_fetch_lshift and atomic_fetch_rshift functions,
         // however, Kokkos stipulates (T,unsigned); so, here, we *don't*
         // mess with the right-hand side.
         Kokkos::atomics_kokkos(&atom.ref(), val);
      #endif

      // Similar remark as for above operator()'s return value
      return T(atom);
   }
   #endif
   #endif


   // ------------------------
   // operator() for other
   // schemes
   // ------------------------

   // Apply the underlying data type's operator atomics_op
   #if defined(atomics_op)
   template<class T>
   inline T operator()(
      T &lhs
   ) const noexcept {
      #ifdef ATOMICS_PRINT
         debug_binary_op(atomics_stringify(atomics_op),lhs,val);
      #endif
      return lhs atomics_op val; // e.g. lhs += val
   }
   #endif

   // Apply this library's function atomics_fun (mineq or maxeq, at present;
   // these have no operator form, so can't be accessed from the above case)
   #if defined(atomics_fun)
   template<class T>
   inline T operator()(
      T &lhs
   ) const noexcept {
      #ifdef ATOMICS_PRINT
         debug_binary_fun(atomics_stringify(atomics_fun),lhs,val);
      #endif
      return atomics::atomics_fun(lhs,val); // e.g. atomics::mineq(lhs,val)
   }
   #endif
};

#undef atomics_class
#undef atomics_op
#undef atomics_fun
#undef atomics_cpp
#undef atomics_kokkos
#undef atomics_kokkos_to_t
