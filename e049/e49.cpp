#include <stdio.h>
#include <sstream>
#include <algorithm>
#include "primes.h"

bool ispermutation(size_t a, size_t b)
{
  std::string A, B;

  { std::stringstream sa, sb;
    sa << a;
    sb << b;
    A = sa.str();
    B = sb.str(); }

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  return A == B;
}

int main()
{
  const size_t MAX = 9999;
  prime_sieve<MAX> sieve;
  sieve.rebuild();

  for ( size_t n=0; n<sieve.v.size(); ++n ) {
    size_t prime = sieve.v[n];

    // find arithmetic triplet
    for ( size_t d=1; d<MAX; ++d ) {
      if ( sieve.isprime(prime+d) && sieve.isprime(prime+d*2) ) {
        if ( ispermutation(prime, prime+d) &&
             ispermutation(prime, prime+2*d) )
        {
          printf("permutative progression with d=%lu for %lu\n", d, prime);
          printf("  %lu\n", prime);
          printf("  %lu\n", prime+d);
          printf("  %lu\n", prime+d*2);
        }
      }
    }
  }

  return 0;
}
