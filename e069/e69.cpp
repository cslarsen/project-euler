/*
 * ProjectEuler.net problem 69
 * Written by Christian Stigen Larsen
 */

#include <stdio.h>
#include <bitset>
#include <vector>

#define MAX 1000000

using namespace std;

std::bitset<MAX+1> bs;
std::vector<int> primes;

static void sieve()
{
  bs.reset();
  bs.flip();
  for ( int n=2; n<=MAX; ++n ) {
    if ( bs[n] ) {
      primes.push_back(n);
      for ( int m=2*n; m<=MAX; m+=n )
        bs[m] = 0;
    }
  }
}

/*
 * The binary gcd algorithm using iteration.
 * Should be fairly fast.
 *
 * Put in the public domain by the author:
 *
 * Christian Stigen Larsen
 * http://csl.sublevel3.org
 */
int binary_gcd(int u, int v)
{
  int shl = 0;

  while ( u && v && u!=v ) {
    bool eu = !(u & 1);
    bool ev = !(v & 1);

    if ( eu && ev ) {
      ++shl;
      u >>= 1;
      v >>= 1;
    }
    else if ( eu && !ev ) u >>= 1;
    else if ( !eu && ev ) v >>= 1;
    else if ( u>=v ) u = (u-v)>>1;
    else {
      int tmp = u;
      u = (v-u)>>1;
      v = tmp;
    }
  }

  return !u? v<<shl : u<<shl;
}

bool isprime(int n)
{
  return bs[n];
}

/*
 * Euler's totient function phi(n).
 * http://en.wikipedia.org/wiki/Euler%27s_totient_function
 *
 * This is an *EXTREMELY* fast function and uses
 * several tricks to recurse.
 *
 * It assumes you have a list of primes and a fast
 * isprime() function.  Typically, you use a bitset
 * to implement the sieve of Eratosthenes and use
 * isprime() on that.  You should also have a vector
 * of all known primes below a certain limit.
 * 
 * Additionally, you should have a fast gcd algorithm.
 *
 * So, we have three dependencies here:
 *
 * - isprime(int) (typically look up bitset sieve)
 * - std::vector<int> primes (vector of prime numbers, typically sieved)
 * - binary_gcd(int, int) or similar, fast, gcd function.
 *
 * This function is placed in the public domain by the author,
 * Christian Stigen Larsen, http://csl.sublevel3.org
 *
 */
int phi(const int n)
{
  // Base case
  if ( n < 2 )
    return 0;

  // Lehmer's conjecture
  if ( isprime(n) )
    return n-1;

  // Even number?
  if ( n & 1 == 0 ) {
    int m = n >> 1;
    return !(m & 1) ? phi(m)<<1 : phi(m);
  }

  // For all primes ...
  for ( std::vector<int>::iterator p = primes.begin();
        p != primes.end() && *p <= n;
        ++p )
  {
    int m = *p;
    if ( n % m  ) continue;

    // phi is multiplicative
    int o = n/m;
    int d = binary_gcd(m, o);
    return d==1? phi(m)*phi(o) : phi(m)*phi(o)*d/phi(d);
  }
}

int main()
{
  sieve();

  double nphimax = 0;
  int nmax = 0;

  for ( int n=2; n<=MAX; ++n ) {
    double nphi = static_cast<double>(n) / phi(n);

    if ( nphi > nphimax ) {
        nphimax = nphi;
        nmax = n;
        printf("phi(%d) = %d and gives n/phi(n) = %lf\n",
          n, phi(n), nphi);
    }
  }

  printf("\nThe answer you are looking for is n = %d\n", nmax);
}
