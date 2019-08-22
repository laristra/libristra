
// Make operator for an atomic operation: ++, --, etc.
// The atomics_* tokens are #defined before coming here.

template<class ATOMIC>
inline typename internal::is_atomic<ATOMIC>::value_type operator atomics_op (
   ATOMIC &atom
   #if defined(atomics_post)
     , const int  // to indicate postincrement/postdecrement
   #endif
) noexcept {
   return atom.atomics_fun();
}

#undef atomics_op
#undef atomics_pre
#undef atomics_post
#undef atomics_fun
