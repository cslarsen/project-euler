#include <stdio.h>
#include <stdint.h>
#include <math.h>

static uint64_t pow_mod(uint64_t a, uint64_t x, uint64_t n)
{
  // See
  // https://secure.wikimedia.org/wikipedia/en/wiki/Modular_exponentiation

  uint64_t r=1;

  while ( x ) {
    if ( (x & 1) == 1 )
      r = a*r % n;

    x >>= 1;
    a = a*a % n;
  }

  return r;
}

int main()
{
  static const uint64_t MAX = 10000;

  uint64_t count=0;
  register uint64_t m=0, n=0;

  for ( n=2; n<=MAX; ++n ) {
    register uint64_t m = 2*n*n - 1;
  }

  printf("count = %lld\n", count);

  return 0;
}
