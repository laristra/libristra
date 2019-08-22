
// Make atomic<> member functions for an atomic operation: add, sub, etc.
// The atomics_* tokens are #defined before coming here.

// ------------------------
// no memory order
// ------------------------

template<class S = SCHEME, class X>
inline T atomics_fun(
   const X val
) noexcept {
   return atomics::atomics_fun<S>(*this, val);
}

template<class S = SCHEME, class X>
inline T atomics_fun(
   const X val
) volatile noexcept {
   return atomics::atomics_fun<S>(*this, val);
}


// ------------------------
// memory order sync
// ------------------------

template<class S = SCHEME, class X>
inline T atomics_fun(
   const X val,
   const std::memory_order sync
) noexcept {
   return atomics::atomics_fun<S>(*this, val, sync);
}

template<class S = SCHEME, class X>
inline T atomics_fun(
   const X val,
   const std::memory_order sync
) volatile noexcept {
   return atomics::atomics_fun<S>(*this, val, sync);
}


// ------------------------
// memory order success, failure
// ------------------------

template<class S = SCHEME, class X>
inline T atomics_fun(
   const X val,
   const std::memory_order success,
   const std::memory_order failure
) noexcept {
   return atomics::atomics_fun<S>(*this, val, success, failure);
}

template<class S = SCHEME, class X>
inline T atomics_fun(
   const X val,
   const std::memory_order success,
   const std::memory_order failure
) volatile noexcept {
   return atomics::atomics_fun<S>(*this, val, success, failure);
}

#undef atomics_fun
