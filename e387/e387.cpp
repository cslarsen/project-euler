#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef uint64_t Z;

static Z digitsum(Z n)
{
  Z s = 0;

  while ( n ) {
    s += n % 10;
    n /= 10;
  }

  return s;
}

static bool harshad(const Z& n)
{
  return (n % digitsum(n)) == 0;
}

static bool isprime(const Z& n)
{
  if ( n <= 1 )
    return false;

  for ( Z d=2, sq=sqrt(n); d <= sq; ++d )
    if ( (n % d) == 0 )
      return false;

  return true;
}

static bool strong_harshad(const Z& n)
{
  return n <= 1 ? false : isprime(n / digitsum(n));
}

static bool rt_harshad(Z n)
{
  for ( ; n > 1; n /= 10 )
    if ( !harshad(n) )
      return false;

  return true;
}

static bool strong_rt_harshad(const Z& n)
{
  if ( !isprime(n) )
    return false;

  return strong_harshad(n/10) and rt_harshad(n/10);
}

static Z srt_sum(const Z& limit)
{
  Z s = 0;

  for ( Z n=1; n < limit; ++n )
    if ( strong_rt_harshad(n) )
      s += n;

  return s;
}

int main()
{
  Z s = srt_sum(10000);
  if ( s != 90619 ) {
    printf("srt_sum(10000) == %llu != 90619n", s);
    return 1;
  }

  const Z limit = 10000000;
  printf("limit=%llu\ncalculating ... ", limit);
  fflush(stdout);
  printf("%llu\n", srt_sum(10000000));
  return 0;
}
