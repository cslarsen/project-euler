#include <iostream>
#include "gcd.h"

using namespace std;

struct frac {
  int n, d;

  frac(int N, int D) : n(N), d(D)
  {
  }
};

//const int D = 8;
const int D = 12000;
const frac LO(1,3);
const frac HI(1,2);

// is reduced proper fraction?
static bool isrpf(const frac& f)
{
  return binary_gcd(f.n, f.d) == 1;
}

// greater than LO ?
static bool gt_lo(const frac& f)
{
  /*
   * E.g. 1/3 vs 2/7 ->
   * 1*7/3*7 vs 2*3/7*3 ->
   * 7/21 vs 6/21 ->
   * is 6 > 7 ? no -> return false
   */
  return f.n*LO.d > f.d;
}

// less than HI ?
static bool lt_hi(const frac& f)
{
  return f.n*HI.d < f.d;
}

int main()
{
  int count = 0;

  for ( int d=1; d<=D; ++d )
  for ( int n=1; n<=d; ++n ) {
    const frac f(n, d);

    if ( !(f.n & 1) && !(f.d & 1) )
      continue;

    if ( !isrpf(f) )
      continue;

    if ( gt_lo(f) && lt_hi(f) )
      ++count;
  }

  cout << count << endl;
  return 0;
}
