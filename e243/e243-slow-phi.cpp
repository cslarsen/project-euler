/*
 * ProjectEuler.net Problem 243
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <bitset>
#include <cassert>
#include <inttypes.h>
#include <math.h>
#include "phi.h"

using namespace std;

/*
 * We can test every number n from 1 to d-1 and see if
 *
 *     gcd(n,d) == hcf(n,d) == 1
 *
 * A much faster way is to simply use Euler's totient function phi, which
 * does *exactly* that.
 *
 * So just return phi(d-1).
 *
 */
#define R(x) phi(x)

/*
 * To test whether a/b < c/d, transform into
 *
 *     a*d/b*d < b*c/b*d -> * a*d < b*c
 *
 * Since we have c/d = 15499/94744, then to test whether a/b is less than
 * that, we do
 *
 *     a*94744 < b*15499
 *
 */
int main()
{
  double best = 1000;
  assert(R(12) == 4);

  for ( uint64_t d=1; ; ++d ) {
    // ratio is n/(d-1)
    uint64_t n = R(d);

    if ( n == 0 )
      continue;

    if ( n*94744 < (d-1)*15499 ) {
      cout << "R(" << d << ") = "
           << n << "/" << (d-1) << " ~ "
           << (double)n/(d-1) << endl;
      break;
    }

    if ( (double)n/(d-1) < best ) {
      best = (double)n/(d-1);
      cout << "R(" << d << ") = "
           << n << "/" << (d-1) << " ~ "
           << (double)n/(d-1) << endl;
    }

    if ( (d % 1000) == 0 ) {
      cout << d << "\r";
      cout.flush();
    }
  }
}
