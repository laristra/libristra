
// Make regular (non-member) functions for an atomic operation: add, sub, etc.
// The atomics_* tokens are #defined before coming here.

// no "memory order"
template<class S = char, class T, class SCHEME, std::size_t NMUX, class X>
inline T atomics_fun(
   atomic<T,SCHEME,NMUX> &atom,
   const X &val
) noexcept {
   return internal::apply(
      atom,
      typename internal::get_scheme<SCHEME,S>::scheme{},
      internal::atomics_class<X>{val}
   );
}

// memory order sync
template<class S = char, class T, class SCHEME, std::size_t NMUX, class X>
inline T atomics_fun(
   atomic<T,SCHEME,NMUX> &atom,
   const X &val,
   const std::memory_order sync
) noexcept {
   return internal::apply(
      atom,
      typename internal::get_scheme<SCHEME,S>::scheme{},
      internal::atomics_class<X>{val},
      sync
   );
}

// memory order success, failure
template<class S = char, class T, class SCHEME, std::size_t NMUX, class X>
inline T atomics_fun(
   atomic<T,SCHEME,NMUX> &atom,
   const X &val,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   return internal::apply(
      atom,
      typename internal::get_scheme<SCHEME,S>::scheme{},
      internal::atomics_class<X>{val},
      success, failure
   );
}

#undef atomics_fun
#undef atomics_class
