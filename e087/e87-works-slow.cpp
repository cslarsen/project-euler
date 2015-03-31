/*
 * ProjectEuler.net problem 87
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <inttypes.h>
#include <math.h>
#include "primes.h"

using namespace std;

typedef uint32_t Z;
typedef vector<Z> Zs;

static const Z PRIMES = 10000;
static prime_sieve<Z, PRIMES> primes;

ostream& operator<<(ostream& s, const Zs& v)
{
  for ( Zs::const_iterator i = v.begin();
        i != v.end(); ++i )
  {
    s << *i;
    if ((i+1) != v.end() )
      s << ",";
  }
  return s;
}

static Zs sqprimes; // square of primes
static Zs cbprimes; // cube of primes
static Zs qdprimes; // quad of primes

static Zs find(const Z& n)
{
  Z limit = 0;
  Z sqn = sqrt(n);
  for ( ; limit<primes.size() && primes[limit] <= sqn; ++limit )
    ;

  // quadroot
  Z qrn = 2;
  while ( qrn*qrn*qrn*qrn < n ) ++qrn;

  Z limitc = 0;
  for ( ; limitc<primes.size() && primes[limitc] <= qrn; ++limitc ) {
    Z l=primes[limitc];
    l = l*l*l*l;
    if ( l >= n )
      break;
  }

  // cuberoot
  Z crn = 2;
  while ( crn*crn*crn < n ) ++crn;

  Z limitb = 0;
  for ( ; limitb<primes.size() && primes[limitb] <= crn; ++limitb ) {
    Z l=primes[limitb];
    l = l*l*l;
    if ( l >= n )
      break;
  }

  for ( Z c=0; c<limitc; ++c ) {
    Z pc = primes[c];
    pc = pc*pc*pc*pc;

    for ( Z b=0; b<limitb; ++b ) {
      Z pb = primes[b];
      pb = pb*pb*pb;

      if ( pb+pc >= n )
        continue;

      for ( Z a=0; a<limit; ++a )
      {
        Z pa = primes[a];
        pa = pa*pa;

        if ( pa+pb+pc == n ) {
          Zs v(3);
          v[0] = primes[a];
          v[1] = primes[b];
          v[2] = primes[c];
          return v;
        }
      }
    }
  }

  return Zs();
}

// below 1M: Count 33616
// below 100k: Count 4704
// below 1k: Count 98
Z count(const Z& upper)
{
  Z c = 0;
  for ( Z n=28; n<upper; ++n ) {
    Zs v = find(n);
    if ( !v.empty() ) {
      ++c;
      if ( (c % 1000) == 0 )
        cout << n << " ==> " << v << endl;
    }
  }

  return c;
}

int main()
{
  cout << "Max prime: " << primes[primes.size()-1] << endl;

  assert(count(50) == 4);
  assert(count(1000) == 98);
  assert(count(100000) == 4704);
  cout << count(2000000) << endl;
}
