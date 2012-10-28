/*
 * ProjectEuler.net problem 87
 * Solved by Christian Stigen Larsen
 *
 * The big difficulty here was making sure sub-calculations didn't overflow!
 */

#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
#include <inttypes.h>
#include <math.h>
#include <gmpxx.h>
#include "primes.h"

using namespace std;

typedef int64_t Z;
typedef vector<Z> Zs;

#define MAX 50000000

static const Z PRIMES = MAX/1000;
static prime_sieve<Z, PRIMES> primes;

template<typename X>
ostream& operator<<(ostream& s, const vector<X>& v)
{
  for ( typename vector<X>::const_iterator i = v.begin();
        i != v.end(); ++i )
  {
    s << *i << ((i+1) != v.end()? "," :  "");
  }

  return s;
}

static Zs sqprimes; // square of primes
static Zs cbprimes; // cube of primes
static Zs qdprimes; // quad of primes

static Z ipow(const Z& a, Z x)
{
  Z r = 1;

  while ( x-- ) {
    r *= a;

    // overflow?
    if ( r < 0 )
      return -1;
  }

  return r;
}

static void initprimes()
{
  for ( size_t n=0; n<primes.size(); ++n ) {
    Z p = primes[n];
    Z sq = ipow(p, 2);
    Z cb = ipow(p, 3);
    Z qd = ipow(p, 4);

    if ( sq > 0 && sq < MAX ) sqprimes.push_back(sq);
    if ( cb > 0 && cb < MAX ) cbprimes.push_back(cb);
    if ( qd > 0 && qd < MAX ) qdprimes.push_back(qd);
  }
}

static Z count(const Z& upper)
{
  Z i[3] = {0,0,0};
  Z m[3] = {0,0,0};

  bitset<MAX> seen;

  for (;;) {
    if ( m[0]<sqprimes.size() && sqprimes[m[0]] < upper ) {
      ++m[0]; continue;
    }

    if ( m[1]<cbprimes.size() && cbprimes[m[1]] < upper ) {
      ++m[1]; continue;
    }

    if ( m[2]<qdprimes.size() && qdprimes[m[2]] < upper ) {
      ++m[2]; continue;
    }

    break;
  }

  Z count=0, sum=0;

  for(;;) {
    Z s1 = sqprimes[i[0]];
    Z s2 = cbprimes[i[1]];
    Z s3 = qdprimes[i[2]];

    if ( s1<0 || s2<0 || s3<0 ) goto NEXT_N;
    if ( (s1+s2)<0 || (s2+s3)<0 || (s1+s2+s3)<0 ) goto NEXT_N;
    sum = s1+s2+s3;
    /*
    if ( (sum = sqprimes[i[0]]) > upper ) goto NEXT_N;
    if ( (sum += cbprimes[i[1]]) > upper ) goto NEXT_N;
    if ( (sum += qdprimes[i[2]]) > upper ) goto NEXT_N;
    */

    if ( sum>0 && sum<upper && !seen[sum] ) {
      /*
      if ( difftime(time(0), last) > 3 ) {
        last = time(0);
        cout << count << " -> " << sum << " = "
             << primes[i[0]] << "^2 + "
             << primes[i[1]] << "^3 + "
             << primes[i[2]] << "^4" << endl;
      }
      */

      seen[sum] = true;
      ++count;
    }

NEXT_N:
    Z carry = 1;
    for ( Z n=0; n<3; ++n ) {
      i[n] += carry;

      if ( i[n]<m[n] )
        carry = 0;
      else {
        i[n] = 0;
        carry = 1;
      }
    }

    if ( carry == 1 )
      break;
  }

  return count;
}

int main()
{
  cout << "Initializing" << endl;
  initprimes();

  cout << "Assertions" << endl;
  assert(ipow(2, 8) == 256);
  assert(count(50) == 4);
  assert(count(100) == 10);
  assert(count(1000) == 98);
  assert(count(100000) == 4704);
  assert(count(250000) == 10391);
  assert(count(1000000) == 33616);
  assert(count(2000000) == 61522);

  cout << "Main part" << endl;
  cout << "Below 50M: " << count(MAX) << endl;
}
