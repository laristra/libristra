
// Make atomic<> member functions for an atomic increment or decrement
// operation. The atomics_* tokens are #defined before coming here.

// no "memory order"
template<class S = SCHEME>
inline T atomics_fun(
) noexcept {
   return atomics::atomics_fun<S>(*this);
}

// no "memory order"; volatile
template<class S = SCHEME>
inline T atomics_fun(
) volatile noexcept {
   return atomics::atomics_fun<S>(*this);
}

// memory order sync
template<class S = SCHEME>
inline T atomics_fun(
   const std::memory_order sync
) noexcept {
   return atomics::atomics_fun<S>(*this, sync);
}

// memory order sync; volatile
template<class S = SCHEME>
inline T atomics_fun(
   const std::memory_order sync
) volatile noexcept {
   return atomics::atomics_fun<S>(*this, sync);
}

// memory order success, failure
template<class S = SCHEME>
inline T atomics_fun(
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   return atomics::atomics_fun<S>(*this, success, failure);
}

// memory order success, failure; volatile
template<class S = SCHEME>
inline T atomics_fun(
   const std::memory_order success,
   const std::memory_order failure
) volatile noexcept {
   return atomics::atomics_fun<S>(*this, success, failure);
}

#undef atomics_fun
