/*
 * ProjectEuler.net Problem 60
 * Solved by Christian Stigen Larsen
 */

#include <math.h>
#include <iostream>
#include <cassert>
#include <inttypes.h>
#include "primes.h"

using namespace std;

typedef uint64_t Z;

static const Z PRIMES = 99999999+1;
static prime_sieve<Z, PRIMES> *primes;

/*
 * Return number of digits in `n`.
 */
template<typename Z>
static Z digits(const Z& n)
{
  if ( n < 0 ) return digits(-n);
  if ( n == 0 ) return 0;
  if ( n < 10 ) return 1;
  return ceil(log(n)/log(10));
}

/*
 * Compute a*10^x
 */
template<typename Z>
static Z pow10(Z a, Z x)
{
  while ( x-- ) a *= 10;
  return a;
}

/*
 * Output operator for vectors.
 */
template<typename X>
ostream& operator<<(ostream& s, const vector<X>& v)
{
  for ( typename vector<X>::const_iterator i = v.begin();
        i != v.end(); ++i )
  {
    s << *i << ((i+1) != v.end()? ", " : "");
  }

  return s;
}

/*
 * Calculate sum of vector.
 */
template<typename X>
X sum(const vector<X>& v)
{
  X s = 0;

  for ( typename vector<X>::const_iterator i = v.begin();
        i != v.end(); ++i )
  {
    s += *i;
  }

  return s;
}

static Z combine(const Z& l, const Z& r)
{
  Z x = l>r? min(digits(l), digits(r)) :
             max(digits(l), digits(r));
  return pow10(l, x) + r;
}

static bool match(Z p, const vector<Z>& v)
{
  for ( size_t n=0; n<v.size(); ++n ) {
    Z q = v[n];
    Z c1 = combine(p, q);
    Z c2 = combine(q, p);

    if ( c1<PRIMES && c2< PRIMES &&
        primes->isprime(c1) && primes->isprime(c2) )
    {
      continue;
    }

    return false;
  }

  return true;
}

vector<Z> next(const vector<Z>& v)
{
  vector<Z> r;

  for ( size_t n=0; n<primes->size(); ++n ) {
    Z p = primes->at(n);

    if ( match(p, v) )
      r.push_back(p);
  }

  return r;
}


void test()
{
  assert(digits(0) == 0);
  assert(digits(1) == 1);
  assert(digits(3) == 1);
  assert(digits(7) == 1);
  assert(digits(17) == 2);
  assert(digits(170) == 3);
  assert(digits(173) == 3);
  assert(digits(1234) == 4);
  assert(digits(12345) == 5);
  assert(digits(123456) == 6);
  assert(digits(1234567) == 7);
  assert(digits(12345678) == 8);
  assert(digits(123456789) == 9);
  assert(pow10(1, 1) == 10);
  assert(pow10(2, 0) == 2);
  assert(pow10(2, 1) == 20);
  assert(pow10(2, 2) == 200);
  assert(pow10(2, 3) == 2000);
  assert(combine(3,7) == 37);
  assert(combine(7,3) == 73);
  assert(combine(3,11) == 311);
  assert(combine(11,3) == 113);
  assert(combine(12,34) == 1234);
  assert(combine(34,12) == 3412);
  assert(combine(340,12) == 34012);
  assert(combine(112233,44) == 11223344);
  assert(combine(44,112233) == 44112233);
  assert(combine(3,109) == 3109);
  assert(combine(109,3) == 1093);
}

static size_t target = 5;
static vector<Z> minv;
static size_t minsum = 9999999999;

void search(vector<Z> v = vector<Z>(), size_t length=0, size_t startindex = 0)
{
  const Z MAX_SEARCH = 9999;

  if ( length == 5 ) {
      cout << "----------------------------------------" << endl;
      cout << "sum=" << sum(v) << " for " << v << "    minsum=" << sum(v) << " for " << v << endl;
      cout << "----------------------------------------" << endl;
      //exit(0);
  }

  if ( length == target ) {
    if ( sum(v) < minsum ) {
      minsum = sum(v);
      minv = v;
      cout << "minsum=" << sum(v) << " for " << minv << endl;
    } else {
      cout << "sum=" << sum(v) << " for " << v
           << "    minsum=" << minsum << " for " << minv << endl;
    }

    return;
  }

  // find a prime that fits
  for ( size_t n=startindex; primes->at(n) <= MAX_SEARCH; ++n ) {
    Z p = primes->at(n);
    if ( match(p, v) ) {
      vector<Z> i(v);
      i.push_back(p);
      search(i, length+1, n+1);
    }
  }
}

int main()
{
  test();

  cout << "Sieving primes below " << PRIMES << " ... " << endl;
  primes = new prime_sieve<Z, PRIMES>();

  cout << "Searching ... " << endl;
  search();
}
