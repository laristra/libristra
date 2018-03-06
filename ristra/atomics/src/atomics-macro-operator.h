
// Make operator for an atomic operation: +=, -=, etc.
// The atomics_* tokens are #defined before coming here.

template<class T, class SCHEME, std::size_t NMUX, class X>
inline T operator atomics_op(
   atomic<T,SCHEME,NMUX> &atom,
   const X &val
) noexcept {
   return atom.atomics_fun(val);
}

template<class T, class SCHEME, std::size_t NMUX, class X>
inline T operator atomics_op(
   volatile atomic<T,SCHEME,NMUX> &atom,
   const X &val
) noexcept {
   return atom.atomics_fun(val);
}

#undef atomics_op
#undef atomics_fun
