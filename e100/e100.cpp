/*
 * ProjectEuler.net problem 100
 * Solved by Christian Stigen Larsen
 *
 * find(0) gives
 *
 * r=1 b=3 r+b=4
 * r=6 b=15 r+b=21
 * r=35 b=85 r+b=120
 * r=204 b=493 r+b=697
 * r=1189 b=2871 r+b=4060
 * r=6930 b=16731 r+b=23661
 * r=40391 b=97513 r+b=137904
 * r=235416 b=568345 r+b=803761
 * r=1372105 b=3312555 r+b=4684660
 * r=7997214 b=19306983 r+b=27304197
 * r=46611179 b=112529341 r+b=159140520
 * r=271669860 b=655869061 r+b=927538921
 *
 * Using uint64_t instead of mpz_class causes incorrect results:
 *
 * r=4294967296 b=4294967297 r+b=8589934593
 * r=8589934592 b=8589934593 r+b=17179869185
 * r=8589936640 b=8598325249 r+b=17188261889
 *
 */

#include <iostream>
#include <inttypes.h>
#include <gmpxx.h>

using namespace std;
typedef mpz_class Z;

static inline bool good_r(const Z& r)
{
  const Z rad = 8*r*r+1;
  const Z s = sqrt(rad);

  // is s an integer?
  return s*s == rad;
}

static bool correct(const Z& r, const Z& b)
{
  return b>1 && r+b>1 && 2*b*(b-1) == (b+r)*(b+r-1);
}

static Z solve_b(const Z& r)
{
  return (sqrt(8*r*r+1) + 2*r + 1) / 2;
}

static void find(const Z& start)
{
  const Z STOP = 1e12;

  for ( Z r=start; ; ++r ) {
    if ( !good_r(r) )
      continue;

    const Z b = solve_b(r);

    if ( correct(r, b) ) {
      cout << "r=" << r << " b=" << b << " r+b=" << b+r << endl;

      if ( r+b > STOP )
        return;
    }
  }
}

int main()
{
  find(271669860-1);
}
