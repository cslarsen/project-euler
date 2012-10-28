/*
 * ProjectEuler.net Problem 112
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <cassert>
#include <inttypes.h>
#include <math.h>
#include <gmpxx.h>

using namespace std;

#define Z mpz_class

static bool increasing(Z n)
{
  for ( Z prev=9; n > 0; n /= 10 ) {
    const Z digit = (n % 10);

    if ( prev < digit )
      return false;
    
    prev = digit;
  }

  return true;
}

// Decreasing number
static bool decreasing(Z n)
{
  for ( Z prev=0; n != 0; n /= 10 ) {
    const Z digit = (n % 10);

    if ( prev > digit )
      return false;
    
    prev = digit;
  }

  return true;
}

static bool bouncy(const Z& n)
{
  return !increasing(n) && !decreasing(n);
}

static bool not_bouncy(const Z& n)
{
  return increasing(n) || decreasing(n);
}

void test()
{
  // from problem
  assert(increasing(134468));
  assert(!decreasing(134468));
  assert(!bouncy(134468));

  // from problem
  assert(decreasing(66420));
  assert(!increasing(66420));
  assert(!bouncy(66420));

  // from problem
  assert(!increasing(155349));
  assert(!decreasing(155349));
  assert(bouncy(155349));

  // own tests
  assert(decreasing(9876));
  assert(!decreasing(9836));
  assert(decreasing(5310));
  assert(increasing(4589));
  assert(increasing(1));
  assert(decreasing(1));
  assert(!bouncy(1));
  assert(increasing(12345678));
  assert(increasing(112233));
  assert(!increasing(11321));
  assert(!increasing(4586));
  assert(increasing(4589));
  assert(!increasing(4580));
  assert(!decreasing(11321));
  assert(bouncy(11321));
}

int main()
{
  test();

  Z gogool;
  mpz_pow_ui(gogool.get_mpz_t(), Z(10).get_mpz_t(), 100);

  Z count = 0;
  //Z stop = gogool;
  Z stop = 1000000;
//  Z stop("10000000000");
  size_t c = 0;

  for ( Z n=1; n < 1000; ++n ) {
    if ( not_bouncy(n) )
      ++count;

    if ( ++c == 1000000 ) {
      c = 0;
      cout << "n=" << n << " " << count << endl;
    }
  }

//  count *= 2;
  cout << count << " non-bouncy numbers below " << stop << endl;
  cout << (stop - count) << endl;
}
