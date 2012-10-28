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

#define MAX 50000000

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

static void initprimes()
{
  for ( size_t n=0; n<primes.size(); ++n ) {
    Z p = primes[n];
    Z sq = p*p;
    Z cb = p*p*p;
    Z qd = p*p*p*p;

    if ( sq < MAX ) sqprimes.push_back(sq);
    if ( cb < MAX ) cbprimes.push_back(cb);
    if ( qd < MAX ) qdprimes.push_back(qd);
    if ( qd > MAX )
      continue;
  }
}

static Z find(const Z& n)
{
  for ( Z c=0; qdprimes[c]<n; ++c ) {
    const Z lb = n-qdprimes[c];

    for ( Z b=0; cbprimes[b]<lb; ++b ) {
      const Z la = lb-cbprimes[b];

      for ( Z a=0; sqprimes[a]<=la; ++a )
      {
        if ( la - sqprimes[a] == 0 ) {
          cout  << n << " = "
            << primes[a] << "^2 + "
            << primes[b] << "^3 + "
            << primes[c] << "^4" << endl;
          return 1;
        }
      }
    }
  }

  return 0;
}

static Z count2(const Z& upper)
{
  Z count = 0;
  Z start = 28;

  for ( Z n=start; n<upper; ++n ) {
    for ( Z c=0; qdprimes[c]<n; ++c ) {
      const Z lb = n-qdprimes[c];

      for ( Z b=0; cbprimes[b]<lb; ++b ) {
        const Z la = lb-cbprimes[b];

        for ( Z a=0; sqprimes[a]<=la; ++a )
        {
          if ( la - sqprimes[a] == 0 ) {
            ++count;
            goto NEXT_N;
          }
        }
      }
    }
NEXT_N:
    if ( (n % 10000) == 0 )
      cout << "n=" << n << " count=" << count << endl;
  }

  return count;
}

static Z count3(const Z& upper)
{
  Z a=0, b=0, c=0, count=0, sum=0;

  while ( (sum = (sqprimes[a]+cbprimes[b]+qdprimes[c])) < upper ) {
    cout << sum << " = " << primes[a] << "^2 + "
      << primes[b] << "^3 + " << primes[c] << "^4" << endl;

    ++count;

    Z na = sqprimes[a+1];
    Z nb = cbprimes[b+1];
    Z nc = qdprimes[c+1];

    if ( na < nb && na < nc )
      ++a;
    else if ( nb < na && nb < nc ) {
      a=0;
      ++b;
    }
    else {
      a=b=0;
      ++c;
    }

    // increment the a, b or c that gives the
    // smallest increment in sum, i.e. the smallest
    // of na, nb or nc

    /*
    if ( ++a > sqprimes.size() ) {
      a = 0;
      if ( ++b > cbprimes.size() ) {
        b = 0;
        if ( ++c > qdprimes.size() ) {
          c = 0;
        }
      }
    }
    */
  }

  return count;
}

// below 1M: Count 33616
// below 100k: Count 4704
// below 1k: Count 98
Z count(const Z& upper)
{
  Z c = 0;
  for ( Z n=28; n<upper; ++n ) {
    Z i = find(n);
    c += i;
  //  if ( (n % 10000) == 0 )
  //    cout << "n=" << n << " count=" << c << endl;
  }

  return c;
}

int main()
{
  initprimes();
  //cout << "50 ==> " << count3(50) << endl;
  cout << "100 ==> " << count3(100) << endl;
  cout << "---" << endl;
  cout << "100 ==> " << count(100) << endl;
//  cout << "100 ==> " << count(100) << endl;
 
 //    cout << "1000 ==> " << count3(1000) << endl;
/*
  assert(count3(50) == 4);
  assert(count3(100) == 10);
  assert(count3(1000) == 98);
  assert(count3(100000) == 4704);
  assert(count3(250000) == 10391);
  */

//  cout << "big: " << count3(1000000) << endl;
}
