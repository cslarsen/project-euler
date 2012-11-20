/*
 * ProjectEuler.net Problem 187
 * Solved by Christian Stigen Larsen
 *
 * Brute-force, but solved in ~3 secs nevertheless.
 */

#include <iostream>
#include <bitset>
#include <inttypes.h>
#include "primes.h"

using namespace std;

typedef uint32_t Z;

const Z MAX = 1e8;
const Z MAXNUM = MAX/2;

static bitset<MAX+1> seen;
static Z cnt = 0;

static void check(const Z& n)
{
  if ( n < MAX && !seen[n] ) {
    ++cnt;
    seen[n] = true;
  }
}

int main()
{
  cout << "Sieving primes" << endl;
  cout.flush();

  const prime_sieve<Z, MAXNUM> primes;

  cout << "Starting loop" << endl;
  cout.flush();

  for ( size_t i=0; primes[i]<MAX && i<primes.size(); ++i ) {
    const Z a = primes[i];

    for ( size_t j=0; primes[j]*a<MAX && j<=i; ++j ) {
      const Z b = primes[j];
      check(b*b);
      check(a*b);
    }
  }

  cout << "Count:  " << cnt << endl;
  cout << "Expect: 17427258" << endl;
}
