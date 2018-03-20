
/*
This example runs some operation (see the loop() function below), some number
of times (niter) and with some number of threads (nthreads).

Usage:

   exe nthreads niters scheme

where exe is the name of the executable file, nthreads is the number of threads
you want, niters the number of iterations, and scheme is the atomicity scheme.

Example:

   add 10 1000000 cpp

That's ten threads, each running the operation (currently, adding 1 to a value
that's initialized to 0), using the cpp scheme. In that case, the result should
be 10*1000000, i.e. 10000000.
*/



#define ATOMICS_KOKKOS
//#define ATOMICS_DEBUG
//#define ATOMICS_PRINT

#include "atomics.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace ristra::atomics;

// command-line parameters
std::size_t nthreads = 0; // number of threads
std::size_t niters = 0; // number of iterations

// atomic value
// Feel free to try other data types, e.g. double. Bear in mind that if you
// use anything other than an integral data type, you'll need to comment-out
// the "cpp" case in main, which won't compile for other than integral types.
// Note: the scheme that's actually used will come from the command line, so
// it doesn't really matter here.
atomic<long,strong> atom(0);


// ------------------------
// loop() function
// ------------------------

// Called by each thread
template<class SCHEME>
void loop()
{
   for (std::size_t c = 0;  c < niters;  ++c) {
      // Feel free to try other operations here...
      atom.add<SCHEME>(1);
   }
}


// ------------------------
// action() function
// ------------------------

// Set up and launch threads
template<class SCHEME>
void action(const std::string &scheme)
{
   std::cout << "Scheme: " << scheme << std::endl;

   // begin timer
   using namespace std::chrono;
   high_resolution_clock::time_point t1 = high_resolution_clock::now();

   // create and start nthreads threads
   std::vector<std::thread> vec;
   for (std::size_t t = 0;  t < nthreads;  ++t)
      vec.push_back(std::thread(loop<SCHEME>));
   for (std::size_t t = 0;  t < nthreads;  ++t)
      vec[t].join();

   // print result of calculation
   std::cout << "Result: " << std::fixed << atom << std::endl;

   // end timer
   high_resolution_clock::time_point t2 = high_resolution_clock::now();
   duration<double> time_span = duration_cast<duration<double>>(t2-t1);
   std::cout << "Timing: " << time_span.count() << " seconds" << std::endl;
}


// ------------------------
// main
// ------------------------

int main(const int argc, const char *const *const argv)
{
   if (argc != 4) {
      std::cout
         << "Usage: " << argv[0] << " nthreads niters scheme" << std::endl;
      exit(1);
   }

   nthreads = atol(argv[1]); if (nthreads < 1) nthreads = 1;
   niters   = atol(argv[2]);
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
