
// Make a class with operator()s that implement "++" and other operations
// that require no arguments other than the single atomic variable to which
// they're applied. The atomics_* tokens are #defined before coming here.

class atomics_class {
public:

   // constructor
   inline explicit atomics_class() noexcept { }


   // ------------------------
   // operator() for cpp
   // ------------------------

   // Apply std::atomic's ++ or --
   template<class STDATOMIC>
   inline typename is_std_atomic<STDATOMIC>::value_type operator()(
      STDATOMIC &atom,
      const cpp
   ) const noexcept {
      #if defined(atomics_pre)
         #ifdef ATOMICS_PRINT
            debug_unary_cpp_pre (atomics_stringify(atomics_pre), atom);
         #endif
         return atomics_pre atom;
      #endif
      #if defined(atomics_post)
         #ifdef ATOMICS_PRINT
            debug_unary_cpp_post(atomics_stringify(atomics_post),atom);
         #endif
         return atom atomics_post;
      #endif
   }


   // ------------------------
   // operator() for kokkos
   // ------------------------

   // Apply Kokkos' function atomics_kokkos
   #if defined(ATOMICS_KOKKOS)
   template<class ATOMIC>
   inline typename is_atomic<ATOMIC>::value_type operator()(
      ATOMIC &atom,
      const kokkos // for overload resolution vs. other operator()s
   ) const {
      using T = typename is_atomic<ATOMIC>::value_type;

      #ifdef ATOMICS_PRINT
         debug_unary_kokkos(atomics_stringify(atomics_kokkos),atom);
      #endif

      #if defined(atomics_post)
         const T val = T(atom);
      #endif
      Kokkos::atomics_kokkos(&atom.ref());
      #if defined(atomics_pre)
         const T val = T(atom);
      #endif

      // Possible issue (look into this): Unfortunately, the atomic_increment
      // and atomic_decrement functions in Kokkos don't return values. Without
      // doing extra work, then, we're stuck with the above val=T(atom) stuff,
      // which (being outside of any atomicity) is subject to race conditions.
      // The upshot is that the return value from the present function may be
      // nonsense. That is to say: doing a pre- or post- increment or decrement,
      // with our "kokkos" scheme (which ultimately comes here), may not give
      // a meaningful return value. The good news is that it shouldn't matter
      // unless someone uses the return value. As in saying val = ++x and then
      // using val (as opposed to just incrementing x, which itself is fine.)
      return val;
   }
   #endif


   // ------------------------
   // operator() for other
   // schemes
   // ------------------------

   // Apply the underlying data type's ++ or --
   template<class T>
   inline T operator()(
      T &lhs
   ) const noexcept {
      #if defined(atomics_pre)
         #ifdef ATOMICS_PRINT
            debug_unary_op_pre (atomics_stringify(atomics_pre), lhs);
         #endif
         return atomics_pre lhs;
      #endif
      #if defined(atomics_post)
         #ifdef ATOMICS_PRINT
            debug_unary_op_post(atomics_stringify(atomics_post),lhs);
         #endif
         return lhs atomics_post;
      #endif
   }
};

#undef atomics_class
#undef atomics_pre
#undef atomics_post
#undef atomics_kokkos
