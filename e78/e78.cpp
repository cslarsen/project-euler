/*
 * ProjectEuler.net Problem 78
 * Solved by Christian Stigen Larsen
 *
 * Fun fact:  Total number of orderings for n items is 2^(n-1).
 *
 * Insight 1:  p(n) is the same as the number of integer partitions (ways to
 * write n as a sum between two or more integers).
 *
 * Insight 2:  Using the integer partition function p(k,n), we use the key
 * insight that any number  n=a+b is divisible by M iff (a%M) + (a%M) = 0.
 *
 * For example: * 2300 is divisible by 100 because the last two digits are
 * zero.
 *
 * 2377 + 5733 is divisible by 100 because 77+33=100 so we know the last two
 * digits of 2377+5733 are 0.
 */

#include <iostream>
#include <cassert>
#include <map>
#include <inttypes.h>
#include <gmpxx.h>

using namespace std;

typedef mpz_class Z;
typedef uint32_t I;


/*
 * Sum of divisors of n; naive implementation.
 */
static map<I,I> memos;
static Z sigma(const I& n)
{
  if ( memos.find(n) != memos.end() )
    return memos[n];

  I r=0;
  for ( I i=1; i<=n; ++i )
    if ( (n%i) == 0 ) r += i;

  memos[n]=r;
  return r;
}

/*
 * Same as P(n) in http://oeis.org/A000041
 *
 * a(n) = (1/n) * Sum_{k=0, 1, ..., n-1} sigma(n-k)*a(k), where sigma(k) is
 * the sum of divisors of k (A000203).
 *
 */
static map<I,Z> memoa;
static Z a(const I& n)
{
  if ( n==0 ) return 1;

  if ( memoa.find(n) != memoa.end() )
    return memoa[n];

  Z r = 0;
  for ( I k=0; k<n; ++k )
    r += sigma(n-k)*a(k);

  if ( r>0 ) r /= Z(n);
  memoa[n]=r;
  return r;
}

static Z find(const Z& mod)
{
  // P(11224) is div by 10^5
  for ( I n=1; ; ++n ) {
    Z r = 0;

    for ( I k=0; k<n; ++k )
      r += sigma(n-k) * a(k);

    r /= n;
    if ( (n % 1000) == 0 ) {
      cout << n << " ";
      cout.flush();
    }

    // found it
    if ( (r % mod) == 0 )
      return n;
  }

  return 0;
}

int main()
{
  assert(sigma(123)==168);
  assert(a(5)==7);
  assert(a(20)==627);

  /*
   * find(10) = 9
   * find(100) = 74
   * find(1000) = 449
   * find(1e4) = 599
   * find(1e5) = 11224 ?? correct?
   */

  const Z d = 1e6;
  const Z n = find(d);

  cout << endl;
  cout << "P(" << n << ") is divisible by " << d << endl;
}
