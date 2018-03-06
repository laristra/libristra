
// Make operator for an atomic operation: ++, --, etc.
// The atomics_* tokens are #defined before coming here.

template<class T, class SCHEME, std::size_t NMUX>
inline T operator atomics_op (
   atomic<T,SCHEME,NMUX> &atom
   #if defined(atomics_post)
     , const int
   #endif
) noexcept {
   return atom.atomics_fun();
}

template<class T, class SCHEME, std::size_t NMUX>
inline T operator atomics_op (
   volatile atomic<T,SCHEME,NMUX> &atom
   #if defined(atomics_post)
     , const int
   #endif
) noexcept {
   return atom.atomics_fun();
}

#undef atomics_op
#undef atomics_pre
#undef atomics_post
#undef atomics_fun
