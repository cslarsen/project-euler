/*
 * ProjectEuler.net problem 72
 * by Christian Stigen Larsen
 *
 * Using Farey Sequence:
 * https://en.wikipedia.org/wiki/Farey_sequence
 *
 * Specifically, we use the length of the Farey sequence:
 *
 * |F_n| = 1 + SUM from m=1 to n of totient(m)
 *
 * using Euler's totient function.
 *
 * Runs in about 1 second for D = 1M.
 */

#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <inttypes.h>
#include "phi.h"

using namespace std;

typedef int64_t Z;
typedef long double F;

const Z M = 10000000UL;
const Z STOP = 10000000UL;
const Z PRIMES = 10000000UL;

static vector<Z> ifreq(Z n)
{
  vector<Z> r(9);

  while ( n ) {
    Z digit = n % 10;
    n /= 10;
    ++r[digit];
  }

  return r;
}

bool operator==(const vector<Z>& l, const vector<Z>& r)
{
  vector<Z>::const_iterator i=l.begin(),
    j=r.begin();

  while ( i<l.end() && j<r.end() )
    if ( *i++ != *j++ )
      return false;

  return i==l.end() && j==r.end();
}

static bool ispermut(const Z& a, const Z& b)
{
  return ifreq(a) == ifreq(b);
}

ostream& operator<<(ostream& o, const vector<Z>& v)
{
  for ( vector<Z>::const_iterator i = v.begin();
        i != v.end(); ++i )
  {
    o << *i;
    if ((i+1) != v.end() )
      o << ", ";
  }

  return o;
}

int main()
{
  assert(phi<PRIMES>(Z(1)) == 1);
  assert(phi<PRIMES>(Z(9)) == 6);
  assert(ispermut(123, 321));
  assert(ispermut(0, 0));
  assert(!ispermut(123, 230));
  assert(!ispermut(123, 1234));
  assert(ispermut(phi<PRIMES>(87109), 79180));

  F MIN = 999999999;

  for ( Z n=2; n<STOP; ++n ) {
    Z p = phi<PRIMES>(n);
    F r = (F)n / p;
    bool perm = ispermut(n, p);

 //   if ( perm )
//      cout << "n=" << n << " phi(n)=" << p << " ratio=" << r << endl;

    if ( perm && r < MIN ) {
      MIN = r;
      cout << "n=" << n << " phi(n)=" << p << " ratio=" << r << endl;
    }

    if ( (n % 1000000) == 0 ) {
      cout << n << endl;
    }
  }

  return 0;
}
