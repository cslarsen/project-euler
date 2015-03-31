#include <stdio.h>
#include "prime_sieve.h"

int main()
{
  const int64_t MAX = 1000000000;
  printf("Calculating all prime numbers up to %llu\n", MAX);
  fflush(stdout);

  prime_sieve<MAX> s;
  s.rebuild();

  printf("Sieve contains %lu primes\n", s.size());
  return 0;
}
