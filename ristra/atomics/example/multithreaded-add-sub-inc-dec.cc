
#define ATOMICS_KOKKOS
// #define ATOMICS_DEBUG
// #define ATOMICS_PRINT

#include "atomics.h"
#include <iostream>
#include <thread>
#include <vector>

using namespace ristra::atomics;

// command-line arguments
std::size_t nthreads = 0; // number of threads
std::size_t niters   = 0; // number of iterations

// atomic value
atomic<unsigned long, strong> atom(0);

// some constant
const int num = 10;


// loop()
// Each thread runs this
template<class SCHEME>
void loop()
{
   for (std::size_t c = 0;  c < niters;  ++c) {
      atom.add    <SCHEME>(   num);
      atom.add    <SCHEME>( 2*num);
      atom.add    <SCHEME>(-3*num);

      atom.sub    <SCHEME>(   num);
      atom.sub    <SCHEME>( 2*num);
      atom.sub    <SCHEME>(-3*num);

      atom.inc    <SCHEME>();
      atom.preinc <SCHEME>();
      atom.postinc<SCHEME>();

      atom.dec    <SCHEME>();
      atom.predec <SCHEME>();
      atom.postdec<SCHEME>();
   }
}


// action()
// Set up and launch threads
template<class SCHEME>
void action(const std::string &scheme)
{
   std::cout << "Scheme: " << scheme << std::endl;

   // create and start threads
   std::vector<std::thread> vec;
   for (std::size_t t = 0;  t < nthreads;  ++t)
      vec.push_back(std::thread(loop<SCHEME>));
   for (std::size_t t = 0;  t < nthreads;  ++t)
      vec[t].join();

   // print result
   std::cout << "Result: " << std::fixed << atom << std::endl;
}


// main()
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
