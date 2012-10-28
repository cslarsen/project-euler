/*
 * ProjectEuler.net problem 72
 * by Christian Stigen Larsen
 *
 * Using Farey Sequence:
 * https://en.wikipedia.org/wiki/Farey_sequence
 *
 * Specifically, we use the length of the Farey sequence:
 *
 * |F_n| = 1 + SUM from m=1 to n of totient(m)
 *
 * using Euler's totient function.
 *
 * Runs in about 1 second for D = 1M.
 */

#include <iostream>
#include <inttypes.h>
#include "phi.h"

using namespace std;

//const int D = 8; // should give 21 as answer
//const int D = 12000;
const int D = 1000000;

static int64_t sum(int m, int n)
{
  int64_t s = 0;

  for ( ; m<=n; ++m )
    s += phi(m);

  return s;
}

int main()
{
  // do not count 0/1 and 1/1:
  cout << sum(1, D) << endl;
  return 0;
}
