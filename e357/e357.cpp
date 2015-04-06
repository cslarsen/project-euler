// Project Euler problem 86
// https://oeis.org/search?q=1%2C2%2C6%2C10%2C22%2C30%2C42%2C58%2C70%2C78%2C82&language=english&go=Search

#include <stdio.h>
#include <stdint.h>
#include "prime_sieve.h"

typedef uint64_t Z;

//#define LIMIT 100
#define LIMIT 100000000
static const prime_sieve<LIMIT> sieve;

// For every divisor d of n, d + n/d must be prime
static inline bool primediv(const Z& n)
{
  for ( Z d=3; d<n; ++d ) {
    if ( (n % d) != 0 )
      continue;
    if ( !sieve.isprime(d + n/d) )
      return false;
  }

  return true;
}

int main()
{
  printf("Sieve contains %zu primes\n", sieve.prime_numbers());

  Z sum = 1;
  //for ( Z n=2; n<LIMIT; n += 2 ) {
  //for ( Z n=99996982; n>1; n -= 2 ) {
  const Z size = sieve.pp->size();
  for ( Z i=size-1; i>0; --i ) {
    const Z n = (*sieve.pp)[i] - 1;
    // when d=n or d=1, n + n/n = n+1 must be prime
    //if ( !sieve.isprime(n+1) )
    //  continue;

    // as n is even, d=n/2 is a factor and n/2 + 2n/n => n/2 + 2 must be prime
    if ( !sieve.isprime((n/2)+2) )
      continue;

    if ( primediv(n) ) {
      sum += n;
      printf("%zu %zu\n", n, sum);
    }
  }
}
