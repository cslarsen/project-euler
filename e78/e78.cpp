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
#include <unordered_map>
#include <inttypes.h>

using namespace std;

typedef uint32_t Z;

/*
 * The integer partition intermediate function MOD m, see:
 * http://en.wikipedia.org/wiki/Partition_(number_theory)#Intermediate_function
 */
static unordered_map<Z, Z> memo;
static Z pmod(const Z& k, const Z& n, const Z& m)
{
  if ( k > n ) return 0;
  if ( k == n ) return 1;

  const Z kn((n<<(sizeof(Z)*4)) ^ k);
  if ( memo.find(kn) != memo.end() )
    return memo[kn];

  const Z r = (pmod(k+1, n, m) + pmod(k, n-k, m)) % m;
  memo[kn] = r;
  return r;
}

/*
 * Sum of divisors of n; naive implementation.
 */
static Z sigma(const Z& n)
{
  Z r=0;
  for ( Z i=1; i<=n; ++i )
    if ( (n%i) == 0 ) r += i;
  return r;
}

/*
 * Same as P(n) in http://oeis.org/A000041
 *
 * a(n) = (1/n) * Sum_{k=0, 1, ..., n-1} sigma(n-k)*a(k), where sigma(k) is
 * the sum of divisors of k (A000203).
 *
 */
static Z a(const Z& n)
{
  if ( n==0 ) return 1;
  Z r = 0;
  for ( Z k=0; k<n; ++k )
    r += sigma(n-k)*a(k);
  if ( r>0 ) r /= n;
  return r;
}

static Z find(const Z& DIV)
{
  // P(11224) is div by 10^5
  for ( Z n=0; ; ++n ) {
    Z r = 1;
    for ( Z k=1; k<=n/2; ++k ) {
      r += pmod(k,n-k, DIV);
      r %= DIV;
    }

    if ( (n % 1000) == 0 ) {
      cout << n << " ";
      cout.flush();
    }

    // P(n) is divisible by DIV
    if ( r == 0 )
      return n;
  }
}

int main()
{
  assert(sigma(123)==168);
  assert(a(5)==7);

  const Z d = 1e5;
  const Z n = find(d);

  cout << endl;
  cout << "P(" << n << ") is divisible by " << d << endl;
}
