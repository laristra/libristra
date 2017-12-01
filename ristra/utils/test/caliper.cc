/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
////////////////////////////////////////////////////////////////////////////////

#include<cinchtest.h>
#include<ristra-config.h>

#ifdef RISTRA_ENABLE_CALIPER

// caliper includes
#include <Annotation.h>

// system includes
#include<iostream>


///////////////////////////////////////////////////////////////////////////////
//! \brief Test the use of caliper.
///////////////////////////////////////////////////////////////////////////////
TEST(caliper, simple) 
{

  // Create annotation object for "phase" annotation
  cali::Annotation phase_ann("phase");

  // Mark begin of "initialization" phase
  phase_ann.begin("initialization");

  // perform initialization tasks
  int count = 4;
  double t = 0.0, delta_t = 1e-6;

  // Mark end of "initialization" phase and begin of "loop" phase
  phase_ann.end();
  phase_ann.begin("loop");

  // Create "iteration" attribute to export the iteration count
  cali::Annotation iteration_ann("iteration");

  for (int i = 0; i < count; ++i) {
    // Mark each loop iteration  
    // The Annotation::Guard object will automatically "end" 
    // the annotation at the end of the C++ scope
    cali::Annotation::Guard 
    g_iteration( iteration_ann.begin(i) );

    // A Caliper snapshot taken at this point will contain
    // { phase="loop", iteration=<i> }

    // perform computation
    t += delta_t;
  }

  // Mark end of "loop" phase
  phase_ann.end();

} // TEST

#endif // HAVE_CALIPER
