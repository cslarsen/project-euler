/*
 * ProjectEuler.net problem 100
 * Solved by Christian Stigen Larsen
 *
 * The chance is given as
 *
 *   P(BB) = b/(b+r) * (b-1)/(b+r-1) = 1/2
 *
 * This is the same as
 *
 *   2*b*(b-1) = (b+r)*(b+r-1)
 *
 * Solved for r we get from WolframAlpha:
 *
 *   0.5 * (sqrt(8*r*r+1) + 2*r + 1)
 *
 * So a fast check to see if r is an acceptable number is
 * to see if sqrt(8*r*r+1) is an integer.
 *
 * Example output:
 *
 * 2/16 r=1 b=3 r+b=4
 * 2/16 r=6 b=15 r+b=21
 * 2/16 r=35 b=85 r+b=120
 * 2/16 r=204 b=493 r+b=697
 * 2/16 r=1189 b=2871 r+b=4060
 * 2/16 r=6930 b=16731 r+b=23661
 * 2/16 r=40391 b=97513 r+b=137904
 * 2/16 r=235416 b=568345 r+b=803761
 * 2/16 r=1372105 b=3312555 r+b=4684660
 * 6/16 r=46611179 b=112529341 r+b=159140520
 * 2/16 r=7997214 b=19306983 r+b=27304197
 * 1/16 r=271669860 b=655869061 r+b=927538921
 * 15/16 r=1583407981 b=3822685023 r+b=5406093004
 * 12/16 r=9228778026 b=22280241075 r+b=31509019101
 * 1/16 r=53789260175 b=129858761425 r+b=183648021600
 *
 */

#include <iostream>
#include <cassert>
#include <inttypes.h>
#include <stdlib.h>
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

static void find(const Z& start, const Z& omp_interval)
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

  #pragma omp parallel for schedule(dynamic, omp_interval)
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
         << "r=" << r << " b=" << b << " r+b=" << b+r
         << ((r+b)>=MARK? " quack!" : "") << endl;
  }
}

static Z interval = 1e6;

static void help()
{
  cerr << "Usage: e100 [ threads ] [ interval size ]" << endl;
  cerr << "Defaults: e100 " << omp_get_num_threads() << " " << interval << endl;
  exit(1);
}

int main(int argc, char** argv)
{
  if ( argc > 1 ) {
    if ( isdigit(argv[1][0]) )
      omp_set_num_threads(atoi(argv[1]));
    else
      help();
  }

  if ( argc > 2 ) {
    if ( isdigit(argv[2][0]) ) {
      interval = atoi(argv[2]);
      cout << "interval size " << interval << endl;
    } else
      help();
  }


  find(1, interval);
  return 0;
}
