/*
 * ProjectEuler.net Problem 243
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <inttypes.h>
#include <stdlib.h>
#include "gcd.h"

using namespace std;

const uint32_t MIN_N = 15499;
const uint32_t MIN_D = 94744;

static inline bool even(const int n)
{
  return (n & 1) == 0;
}

/*
 * Returns true if a/b is less than c/d
 */
static inline
bool less_than(const uint32_t a, const uint32_t b,
               const uint32_t c, const uint32_t d)
{
  // a/b < c/d ->
  // a*d/b*d < b*c/bdb ->
  // a*d < b*c
  return a*d < b*c;
}

static uint32_t R(const uint32_t& d)
{
  uint32_t c = 1;

  for ( uint32_t n=2; n<d; ++n ) {
    if ( even(n) && even(d) )
      continue;

    if ( binary_gcd(n, d) == 1 )
      ++c;
  }

  return c;
}

int main()
{
  uint32_t bestn = 1, bestd = 1;

  cout << "Target: " << MIN_N << "/" << MIN_D
    << " ~ " << (double)MIN_N / MIN_D << endl;

  for ( uint32_t d=1; ; ++d ) {
    uint32_t num = R(d);
    uint32_t den = d-1;

    if ( num == den )
      continue;

    if ( less_than(num, den, bestn, bestd) ) {
      cout << num << "/" << den << " = " << (double)num/den << endl;
      bestn = num;
      bestd = den;
    }

    if ( less_than(num, den, MIN_N, MIN_D) ) {
      cout << endl;
      cout << num << "/" << den << " = " << (double)num/den << endl;
      cout << "Answer: " << den << endl;
      exit(0);
    }

    if ( (d % 1000) == 0 ) {
      cout << d << "\r";
      cout.flush();
    }
  }
}
