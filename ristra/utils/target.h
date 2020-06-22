/*
    @@@@@@@@  @@           @@@@@@   @@@@@@@@ @@
   /@@/////  /@@          @@////@@ @@////// /@@
   /@@       /@@  @@@@@  @@    // /@@       /@@
   /@@@@@@@  /@@ @@///@@/@@       /@@@@@@@@@/@@
   /@@////   /@@/@@@@@@@/@@       ////////@@/@@
   /@@       /@@/@@//// //@@    @@       /@@/@@
   /@@       @@@//@@@@@@ //@@@@@@  @@@@@@@@ /@@
   //       ///  //////   //////  ////////  //

   Copyright (c) 2016, Triad National Security, LLC
   All rights reserved.
                                                                              */
#pragma once

/*! @file */

//----------------------------------------------------------------------------//
// Pickup Kokkos defines if enabled.
//----------------------------------------------------------------------------//

#if defined(ENABLE_KOKKOS)
#include <Kokkos_Core.hpp>

#define RISTRA_TARGET KOKKOS_FUNCTION
#define RISTRA_INLINE_TARGET KOKKOS_INLINE_FUNCTION

#endif // RISTRA_ENABLE_KOKKOS

//----------------------------------------------------------------------------//
// Defaults.
//----------------------------------------------------------------------------//

#if !defined(RISTRA_TARGET)
#define RISTRA_TARGET
#endif

#if !defined(RISTRA_INLINE_TARGET)
#define RISTRA_INLINE_TARGET inline
#endif
