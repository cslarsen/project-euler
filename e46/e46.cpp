#include <stdio.h>
#include "primes.h"

int main()
{
  const size_t PRIMES = 100000;
  prime_sieve<PRIMES> sieve;
  sieve.rebuild();

  printf("Testing Christian Goldbach's conjecture that every odd\n");
  printf("composite is the sum of a prime and twice a square.\n");

  for ( size_t n=2; n<PRIMES; ++n ) {
    // skip even numbers
    if ( !(n & 1) ) continue;

    // skip primes
    if ( sieve.isprime(n) ) continue;

    // try all prime numbers
    for ( size_t i=2; i<sieve.v.size(); ++i ) {
      size_t prime = sieve.v[i];

      if ( prime >= n )
        break;
     
      // try all numbers less than half the prime 
      for ( size_t m=1; m < n>>1; ++m ) {
        if ( n == prime + 2*m*m ) {
          printf("%lu = %lu + 2*%lu^2\n", n, prime, m);
          goto NEXT_N;
        }
      }
    }
    printf("None found for %lu\n", n);
    return 0;
NEXT_N:
    continue;
  }
}
