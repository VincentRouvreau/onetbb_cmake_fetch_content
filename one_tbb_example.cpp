#include <iostream>
#include <vector>
#include <random>  // for std::default_random_engine, std::uniform_real_distribution
#include <algorithm>  // for std::generate
#include <chrono>  // for std::chrono::system_clock, std::chrono::duration_cast

#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

int main(int argc, char **argv)
{
  std::default_random_engine gen;
  std::uniform_real_distribution<double> dist(-1.,1.);
  
  std::vector<double> randr(1000000000);
  std::generate(std::begin(randr), std::end(randr), [&dist, &gen](){ return dist(gen); } );

  // Start
  auto start_time = std::chrono::system_clock::now();

  tbb::parallel_for( tbb::blocked_range<size_t>(0, randr.size()),
      [&randr](const tbb::blocked_range<size_t>& r) {
        for(size_t i=r.begin(); i!=r.end(); ++i)
            randr[i] = randr[i] * randr[i];
      }
    );

  auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - start_time
    ).count();
  // Stop

  std::cout << " in " << time_ms << " ms" << std::endl;

  // Start
  start_time = std::chrono::system_clock::now();

  for(auto& v: randr) {
    v = v * v;
  }

  time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now() - start_time
    ).count();
  // Stop

  std::cout << " in " << time_ms << " ms" << std::endl;
  return 0;
}