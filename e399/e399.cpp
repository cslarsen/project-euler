/*
 * ProjectEuler.net Problem 399
 * Solved by Christian Stigen Larsen
 *
 * Theorems and tricks we will use:
 *
 * - Note, see: http://math.ucsd.edu/~erickson/research/pdf/fibonacci3.pdf
 *
 * - We can quickly get the last n digits of F(n) by calculating
 *   F(n) mod 10^n = (F(n-2) + F(n-1)) mod 10^n
 *
 * - Because F(k*n) is divisible by F(n), all F(k) where k is a prime
 *   number must also be a prime number.
 *
 * - Divisibility of F(n) is related to the Legendre symbol (p/5), which
 *   has the definition
 *
 *           {  0 if p = 5
 *   (p/5) = {  1 if p = +/- 1 (mod 5)
 *           { -1 if p = +/- 2 (mod 5)
 * 
 *   If p is a prime number then F(p) = (p/5) (mod p) and
 *   F(p-(p/5)) = 0 (mod p)
 *
 *   So for any given F(n), if we find a p so that p-(p/5) = n, then p
 *   must divide F(n) and thus be a factor of F(n).
 *
 * - F(n) divides F(m) iff n divides m.
 *
 */

#include <iostream>
#include <vector>
#include <inttypes.h>
#include <math.h>
#include "primes.h"
#include "jacobi.h"

using namespace std;

// will eventually be 10^16
#define ZEROES 10000000000000000ULL
#define PRIMES 1000000ULL

// stop at the Nth squarefree Fibonacci
#define STOP 200

// index of squarefree Fibonacci numbers
vector<int64_t> *sffi;

prime_sieve<int64_t, PRIMES> *primes = NULL;

static void show(const int64_t& n, const int64_t& F)
{
  cout << "F_" << n << "=" << F << endl;
}

static void mark(const int64_t& n, const int64_t& F)
{
  static size_t count = 0;
  ++count;

  sffi->push_back(n);

  cout << count << "th squarefree ";
  show(n, F);

  if ( count == STOP ) {
    cout << "STOP" << endl;
    exit(0);
  }
}

static bool squarefree(const int64_t& n, const int64_t& F)
{
  if ( n < PRIMES && primes->isprime(n) )
    return true;

  if ( (n % 1) == 1 && n!=25 )
    return true;

  // F(m)|F(n) iff m|n, so if F(m) is NOT square-free,
  // then F(n) cannot be either
  for ( size_t m=3, i=3; m < n && m < sffi->size(); ++m ) {
    if ( m == sffi->operator[](i) ) {
      ++i;
      continue;
    }

    if ( (n % m) == 0 )
      return false;
  }

  // Old way
//  if ( n < 45 ) // F(45) > ZEROES
    for ( int64_t i=2, sqn=sqrt(F); ; ++i ) {
      if ( i > sqn )
        break;

      if ( (F % (i*i)) == 0 )
 //     if ( (F % i)==0 && ((F/i) % i) == 0 )
        return false;
    }

  // ... at this point, we have a problem :)

/*
  // for all primes > 2, check for divisibility
  for ( size_t i=1; i < primes->size(); ++i ) {
    const int64_t p = primes->operator[](i);
    const int64_t p5 = jacobi_symbol(p, static_cast<int64_t>(5));

    if ( n == (p - p5) )
      return false;
  }
*/
  // possibly undecided

  return true;
}

static void init()
{
  sffi = new vector<int64_t>();

  cout << "Sieving primes less than " << PRIMES << endl;
  primes = new prime_sieve<int64_t, PRIMES>();
  cout << "Done" << endl;
}

void show_known()
{
  cout << "Known squarefree Fibonacci numbers" << endl;
  cout 
    << "1,1,2,3,5,13,21,34,55,89,233,377,610,987,1597,4181,6765,10946,17711,"
    << "28657,121393,196418,317811,514229,1346269,2178309,3524578,5702887,"
    << "9227465,24157817,39088169,63245986,102334155,165580141,433494437,701408733,1134903170,1836311903"
    << endl;
}

int main()
{
  init();
  atexit(show_known);

  int64_t a=0, b=1, n=0;

  mark(n++, 0);
  mark(n++, 1);

  for ( ; ; ++n ) {
    const int64_t tmp = b;
    b += a;
    b %= ZEROES;
    a = tmp;

    if ( squarefree(n, b) )
      mark(n, b);
  }
}
