
// Make regular (non-member) functions for an atomic operation: add, sub, etc.
// The atomics_* tokens are #defined before coming here.

// no memory order
template<class S = char, class ATOMIC, class X>
inline typename internal::is_atomic<ATOMIC>::value_type atomics_fun(
   ATOMIC &atom,
   const X &val
) noexcept {
   return internal::apply(
      atom,
      typename internal::get_scheme<typename ATOMIC::scheme_type,S>::scheme{},
      internal::atomics_class<X>{val}
   );
}

// memory order sync
template<class S = char, class ATOMIC, class X>
inline typename internal::is_atomic<ATOMIC>::value_type atomics_fun(
   ATOMIC &atom,
   const X &val,
   const std::memory_order sync
) noexcept {
   return internal::apply(
      atom,
      typename internal::get_scheme<typename ATOMIC::scheme_type,S>::scheme{},
      internal::atomics_class<X>{val},
      sync
   );
}

// memory order success, failure
template<class S = char, class ATOMIC, class X>
inline typename internal::is_atomic<ATOMIC>::value_type atomics_fun(
   ATOMIC &atom,
   const X &val,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   return internal::apply(
      atom,
      typename internal::get_scheme<typename ATOMIC::scheme_type,S>::scheme{},
      internal::atomics_class<X>{val},
      success, failure
   );
}

#undef atomics_fun
#undef atomics_class
