
// Make regular (non-member) functions for an atomic increment or decrement
// operation. The atomics_* tokens are #defined before coming here.

// no "memory order"
template<class S = char, class T, class SCHEME, std::size_t NMUX>
inline T atomics_fun(
   atomic<T,SCHEME,NMUX> &atom
) noexcept {
   return internal::apply(
      atom,
      typename internal::get_scheme<SCHEME,S>::scheme{},
      internal::atomics_class{}
   );
}

// memory order sync
template<class S = char, class T, class SCHEME, std::size_t NMUX>
inline T atomics_fun(
   atomic<T,SCHEME,NMUX> &atom,
   const std::memory_order sync
) noexcept {
   return internal::apply(
      atom,
      typename internal::get_scheme<SCHEME,S>::scheme{},
      internal::atomics_class{},
      sync
   );
}

// memory order success, failure
template<class S = char, class T, class SCHEME, std::size_t NMUX>
inline T atomics_fun(
   atomic<T,SCHEME,NMUX> &atom,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   return internal::apply(
      atom,
      typename internal::get_scheme<SCHEME,S>::scheme{},
      internal::atomics_class{},
      success, failure
   );
}

#undef atomics_fun
#undef atomics_class
