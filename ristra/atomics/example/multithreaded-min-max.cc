
#define ATOMICS_KOKKOS
//#define ATOMICS_DEBUG
//#define ATOMICS_PRINT

#include "atomics.h"
#include <iostream>
#include <thread>
#include <vector>

using namespace ristra::atomics;

const int a = 1000;
const int b = 1000000;
atomic<int,strong> themin((a+b)/2);
atomic<int,strong> themax((a+b)/2);

void athreads()
{
   for (int iter = a;  iter <= b;  ++iter) {
      themin.min(iter);
      themax.max(iter);
   }
}

void bthreads()
{
   for (int iter = b;  iter >= a;  --iter) {
      themin.min(iter);
      themax.max(iter);
   }
}

int main()
{
   std::cout << "themin == " << themin << std::endl;
   std::cout << "themax == " << themax << std::endl;

   // create threads
   std::size_t nthreads = 10;
   std::vector<std::thread> threads;
   for (std::size_t t = 0;  t < nthreads;  ++t)
      threads.push_back(
         t % 2 == 0
       ? std::thread(athreads)
       : std::thread(bthreads));
   for (std::size_t t = 0;  t < nthreads;  ++t)
      threads[t].join();

   // check results
   std::cout << "themin == " << themin << std::endl;
   std::cout << "themax == " << themax << std::endl;
}
