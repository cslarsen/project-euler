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
 * r=1583407981 b=3822685023 r+b=5406093004
 * r=9228778026 b=22280241075 r+b=31509019101
 *
 */

#include <iostream>
#include <cassert>
#include <inttypes.h>
#include <math.h>
#include <omp.h>

using namespace std;
typedef __uint128_t Z;

static inline bool good_r(const Z& r)
{
  const Z rad = 8*r*r+1;
  const Z s = sqrt(rad);
  return s*s == rad;
}

static inline bool solution(const Z& r, const Z& b)
{
  return 2*b*(b-1) == (b+r)*(b+r-1);
}

static inline Z solve_b(const Z& r)
{
  return (sqrt(8*r*r+1) + 2*r + 1) / 2;
}

static ostream& operator<<(ostream& o, const __uint128_t& n)
{
  if ( n < 0xFFFFFFFFFFFFFFFF )
    return o << static_cast<uint64_t>(n);

  o << "0x" << static_cast<uint64_t>(n>>64) << static_cast<uint64_t>(n);
  return o;
}

static void find(const Z& start)
{
  assert(start>0);

  /*
   * Benchmark: r<=271669860 should take about 3.5-4.0 secs
   *
   * The reason we want such a huge number of threads is to
   * avoid the threads in the lower space to stop too quickly.
   */

  const Z STOP = 1e12;
  const Z MARK = 1e12;

  #pragma omp parallel for schedule(dynamic, 10000000) num_threads(16)
  for ( Z r=start; r<STOP; ++r ) {
    if ( !good_r(r) )
      continue;

    const Z b = solve_b(r);

    if ( !solution(r, b) )
      continue;

    int i = omp_get_thread_num()+1;
    int j = omp_get_num_threads();

    #pragma omp critical
    cout << i << "/" << j << " " // thread no.
         << "r=" << r << " b=" << b << " r+b=" << b+r << " "
         << (r+b>MARK? "*" : "") << endl;
  }
}

int main()
{
  find(1);
}
