#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "prime_sieve.h"

typedef uint64_t Z;
#define LIMIT 100000000

prime_sieve<LIMIT> *sieve = NULL;

static inline Z digitsum(Z n)
{
  Z s = 0;

  while ( n ) {
    s += n % 10;
    n /= 10;
  }

  return s;
}

static inline bool harshad(const Z& n)
{
  return (n % digitsum(n)) == 0;
}

static inline bool isprime(const Z& n)
{
  return sieve->isprime(n);
  /*
  if ( n <= 1 )
    return false;

  for ( Z d=2, sq=sqrt(n); d <= sq; ++d )
    if ( (n % d) == 0 )
      return false;

  return true;
  */
}

static inline bool strong_harshad(const Z& n)
{
  return n <= 1 ? false : isprime(n / digitsum(n));
}

static inline bool rt_harshad(Z n)
{
  for ( ; n > 1; n /= 10 )
    if ( !harshad(n) )
      return false;

  return true;
}

static inline bool strong_rt_harshad(const Z& n)
{
  if ( !isprime(n) )
    return false;

  return strong_harshad(n/10) and rt_harshad(n/10);
}

static Z srt_sum(const Z& limit)
{
  Z s = 0;

  for ( Z n=1; n < limit; ++n ) {
    if ( !sieve->isprime(n) )
      continue;

    if ( strong_rt_harshad(n) )
      s += n;

    if ( (n % 25000000) == 0 ) {
      printf("n=%llu sum=%llu\n", n, s);
      fflush(stdout);
    }
  }

  return s;
}

static bool test()
{
  Z s = srt_sum(10000);

  if ( s != 90619 ) {
    printf("test failed: srt_sum(10000) ==> %llu != 90619\n", s);
    return false;
  }

  printf("test ok\n");
  return true;
}


int main()
{
  const Z limit = LIMIT;

  printf("finding primes < %llu ... ", limit);
  fflush(stdout);
  sieve = new prime_sieve<limit>();
  printf("%llu primes\n", sieve->primes);
  fflush(stdout);

  if ( !test() )
    return 1;

  printf("calculating ... ");
  fflush(stdout);
  printf("sum < %llu = %llu\n", limit, srt_sum(limit));

  return 0;
}
