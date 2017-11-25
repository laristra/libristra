// test-announce.cc
// T. M. Kelley
// Aug 17, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#include "cinchtest.h"
#include "ristra/initialization/announce.h"

TEST(announce, only)
{
  std::string ann = ristra::announce();
  std::string exp =
    "Ristra version 1.0, Copyright (c) 2017 LANS LLC, all rights reserved";
  EXPECT_EQ(ann, exp);
}

// End of file
