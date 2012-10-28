/*
 * Project Euler, problem 216
 * by Christian Stigen Larsen
 *
 * Note: THis algorithm is SLOOOOOOOOOOOOOOOOOOOOOOOOOOOW.
 * Requires about 20 minutes on Intel Core i7.
 *
 * The answer, by the way, is 5437849.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include "miller-rabin.h"
#include "mersenne-twister.h"

typedef unsigned int uint128_t __attribute__((mode(TI)));

static inline uint64_t mul_mod(uint64_t a, uint64_t b, const uint64_t n)
{
  a %= n;
  b %= n;
  uint128_t m = ((uint128_t)a)*b;
  m %= n;
  return static_cast<uint64_t>(m);
}

static inline uint64_t pow_mod(uint64_t a, uint64_t x, uint64_t n)
{
  uint64_t r=1;

  while ( x ) {
    if ( (x & 1) == 1 )
      r = mul_mod(a, r, n);

    x >>= 1;
    a = mul_mod(a, a, n);
  }

  return r;
}

int main()
{
  seed(time(0));
  static const uint64_t MAX = 50000000;
  //static const uint64_t MAX = 100000;
  register uint64_t count=0;

  printf("153595205858038274^1152921504606846975 "
         "mod 2305843009213693951 =\n %lld\n",
           pow_mod(153595205858038274,
                   1152921504606846975,
                   2305843009213693951));

  uint64_t N = 2305843009213693951;
  printf("is %lld prime? %s\n", N, isprime(N, 10)? "Yes" : "No");

  for ( register uint64_t n=2; n<=MAX; ++n ) {
    uint64_t i=n;
    i *= n;
    i <<= 1;
    --i;

    //if ( isprime(((n*n)<<1) - 1, 5000) )
    if ( isprime(i, 10) ) {
      ++count;
      //printf("t(%lld) = %lld (prime)\n", n, i);
    }

    if ( (n % 1000000)  == 0 ) {
      printf(".");
      fflush(stdout);
    }
  }

  printf("count = %lld\n", count);
  return 0;
}
