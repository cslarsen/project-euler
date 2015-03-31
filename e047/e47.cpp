#include <cstdio>
#include "to_s.h"
#include "factors.h"
#include "unique.h"

using namespace std;

typedef std::vector<int> ints;
typedef std::set<int> intset;

const size_t primes = 1000000;
prime_sieve<primes> p;

int main()
{
  printf("Sieve contains %lu primes below %lu\n", p.size(), primes);

  // find a four-digit number with FOUR prime factors
  size_t prev=0;
  size_t conseq=1;
  size_t match=4;

  for ( size_t n=2; n < primes; ++n ) {
    ints f = factors(n, p);
    ints u = unique(f);

    if ( u.size() == match ) {
      //printf("%lu has %lu unique factors %s\n", n, match, to_s(f));
      if ( n==(prev+1) ) {
        if ( ++conseq == match ) {
          printf("found %lu\n", n - conseq + 1);
          break;
        }
      } else
        conseq = 1;
      prev = n;
    }
  }
}
