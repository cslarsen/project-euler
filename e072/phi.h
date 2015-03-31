/*
 * Euler's totient function phi(n).
 * http://en.wikipedia.org/wiki/Euler%27s_totient_function
 *
 * This is an *EXTREMELY* fast function and uses
 * several tricks to recurse.
 *
 * It assumes you have a list of primes and a fast
 * isprime() function.  Typically, you use a bitset
 * to implement the sieve of Eratosthenes and use
 * isprime() on that.  You should also have a vector
 * of all known primes below a certain limit.
 * 
 * Additionally, you should have a fast gcd algorithm.
 *
 * So, we have three dependencies here:
 *
 * - isprime(int) (typically look up bitset sieve)
 * - std::vector<int> primes (vector of prime numbers, typically sieved)
 * - binary_gcd(int, int) or similar, fast, gcd function.
 *
 * This function is placed in the public domain by the author,
 * Christian Stigen Larsen, http://csl.sublevel3.org
 *
 */

#include <vector>
#include <inttypes.h>
#include "gcd.h"
#include "primes.h"

prime_sieve<1000000> primes;

static bool isprime(int64_t n)
{
  return primes.isprime(n);
}

int64_t phi(const int64_t n)
{
  // Base case
  if ( n < 2 )
    return 0;

  // Lehmer's conjecture
  if ( isprime(n) )
    return n-1;

  // Even number?
  if ( n & 1 == 0 ) {
    int m = n >> 1;
    return !(m & 1) ? phi(m)<<1 : phi(m);
  }

  // For all primes ...
  for ( std::vector<int64_t>::const_iterator p = primes.first();
        p != primes.last() && *p <= n;
        ++p )
  {
    int m = *p;
    if ( n % m  ) continue;

    // phi is multiplicative
    int o = n/m;
    int d = binary_gcd(m, o);
    return d==1? phi(m)*phi(o) : phi(m)*phi(o)*d/phi(d);
  }
}
