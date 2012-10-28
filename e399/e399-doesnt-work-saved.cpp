#include <iostream>
#include <inttypes.h>
#include <math.h>
#include "primes.h"

using namespace std;

#define ZEROES 10000000000000000U
#define PRIMES 100000000

prime_sieve<uint64_t, PRIMES> primes;

template<typename INT>
static bool square_free(const INT& n)
{
  for ( size_t i=0; i<primes.size(); ++i ) {
    const INT f = primes.v[i];

    if ( f >= n )
      break;

    if ( (n % f)==0 && ((n/f) % f)==0 )
      return false;
  }

  if ( primes.v[primes.size()-1] < sqrt(n) ) {
    cout << "oops" << endl;
    exit(0);
  }

  return true;
}

int main()
{
  cout << "Finding all primes below " << PRIMES << endl;

  uint64_t n=1, stop=200, k=1;

  // right side
  uint64_t a=0, b=1;

  for(;;) {
    ++k;
    uint64_t tmp = b;
    b += a;
    b %= ZEROES;
    a = tmp;

    if ( primes.isprime(k) || square_free(b) ) {
      cout << "fib(" << k << ") is the "
        << ++n << "th square-free Fibonacci-number is " << b << endl;

      if ( n == stop )
        break;
    }
  }

  cout << "1,1,2,3,5,13,21,34,55,89,233,377,610,987,1597,4181,6765,10946,17711" << endl;
  cout << "28657,121393,196418,317811,514229,1346269,2178309,3524578,5702887" << endl;
}
