
// Make operator for an atomic operation: +=, -=, etc.
// The atomics_* tokens are #defined before coming here.

template<class ATOMIC, class X>
inline typename internal::is_atomic<ATOMIC>::value_type operator atomics_op(
   ATOMIC &atom,
   const X &val
) noexcept {
   return atom.atomics_fun(val);
}

#undef atomics_op
#undef atomics_fun
