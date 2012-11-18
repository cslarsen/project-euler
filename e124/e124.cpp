/*
 * ProjectEuler.net Problem 124
 * Solved by Christian Stigen Larsen
 *
 * Straight-forward, brute-force way.
 */

#include <iostream>
#include <cassert>
#include <inttypes.h>
#include "primes.h"

using namespace std;

#define N_MAX 100000

typedef uint32_t Z;
typedef pair<Z,Z> ZZ;

static prime_sieve<Z, 1+N_MAX> primes;

static Z rad(const Z& n)
{
  Z r = 1;

  for ( auto p : primes.v ) {
    if ( p > n )
      break;

    if ( (n % p) == 0 )
      r *= p;
  }

  return r;
}

static bool compare(const ZZ& l, const ZZ& r)
{
  // sort on rad(n)
  if ( l.second != r.second )
    return l.second < r.second;

  // if equal, sort on n
  return l.first < r.first;
}

int main()
{
  assert(rad(504)==42);
  assert(rad(1)==1); assert(rad(2)==2);
  assert(rad(3)==3); assert(rad(4)==2);
  assert(rad(5)==5); assert(rad(6)==6);
  assert(rad(7)==7); assert(rad(8)==2);
  assert(rad(9)==3); assert(rad(10)==10);

  cout << "Generating" << endl;

  ZZ E[N_MAX];
  for ( Z n=1; n<=N_MAX; ++n )
    E[n-1] = ZZ(n, rad(n));

  sort(E, E+N_MAX, compare);

  cout << "E[10000] = " << E[10000-1].first << endl;
}
