
/*
This example runs npairs pairs of threads, with half of the total threads doing
an add operation, and the other half doing a subtract operation. As currently
written, the result should be 0.

Usage:

   exe npairs niters scheme

where exe is the name of the executable file, npairs is the number of pairs of
threads you want, niters the number of iterations, and scheme is the atomicity
scheme.

Example:

   addsub 10 1000000 cpp

That's 20 total threads (10 pairs of threads), with half running:
   atom.add<SCHEME>(1); // add 1
and the other half running:
   atom.sub<SCHEME>(1); // subtract 1
with the cpp scheme.
*/



//#define ATOMICS_KOKKOS
//#define ATOMICS_DEBUG
//#define ATOMICS_PRINT

#include "atomics.h"
#include <iostream>
#include <thread>
#include <vector>

using namespace ristra::atomics;

// command-line parameters
std::size_t npairs = 0; // number of *pairs* of threads
std::size_t niters = 0; // number of iterations

// atomic value
// See comment in add.cc; the same applies here.
atomic<long,strong> atom(0);


// ------------------------
// Loops
// ------------------------

// loop of adds
// Called by half of the threads
template<class SCHEME>
void add()
{
   for (std::size_t c = 0;  c < niters;  ++c)
      atom.add<SCHEME>(1);
}

// loop of subtracts
// Called by half of the threads
template<class SCHEME>
void sub()
{
   for (std::size_t c = 0;  c < niters;  ++c)
      atom.sub<SCHEME>(1);
}


// ------------------------
// action() function
// ------------------------

// Set up and launch threads
template<class SCHEME>
void action(const std::string &scheme)
{
   std::cout << "Scheme: " << scheme << std::endl;

   // create and start 2*npairs threads
   std::vector<std::thread> vec;
   for (std::size_t t = 0;  t < 2*npairs;  ++t)
      vec.push_back(t%2 ? std::thread(sub<SCHEME>) : std::thread(add<SCHEME>));
   for (std::size_t t = 0;  t < 2*npairs;  ++t)
      vec[t].join();

   // print result of calculation
   std::cout << "Result: " << std::fixed << atom << std::endl;
}


// ------------------------
// main
// ------------------------

int main(const int argc, const char *const *const argv)
{
   if (argc != 4) {
      std::cout
         << "Usage: " << argv[0] << " npairs niters scheme" << std::endl;
      exit(1);
   }

   npairs = atol(argv[1]);  if (npairs < 1) npairs = 1;
   niters = atol(argv[2]);
   const std::string scheme = argv[3];

   if (scheme == "cpp")
      action<cpp>(scheme);
   else
   #if defined(ATOMICS_KOKKOS)
   if (scheme == "kokkos")
      action<kokkos>(scheme);
   else
   #endif
   if (scheme == "strong")
      action<strong>(scheme);
   else if (scheme == "strong::pun")
      action<strong::pun>(scheme);
   else if (scheme == "weak")
      action<weak>(scheme);
   else if (scheme == "weak::pun")
      action<weak::pun>(scheme);
   else if (scheme == "lock")
      action<lock>(scheme);
   else if (scheme == "serial")
      action<serial>(scheme);
   else {
      std::cout << "Scheme \"" << scheme << "\" not recognized" << std::endl;
      exit(1);
   }
}
