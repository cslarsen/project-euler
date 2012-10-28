#include <vector>
#include <primes.h>

/*
 * Naive factorization routine using precomputed prime sieve.
 *
 */
template<size_t PRIMES>
std::vector<int> factors(int n, const prime_sieve<PRIMES>& p)
{
  std::vector<int> v;

  for ( std::vector<int>::const_iterator a = p.first(),
            b = p.find(n); a != b; ++ a )
  {
    while ( !(n % *a) ) {
      v.push_back(*a);
      n /= *a;
    }
  }

  return v;
}
