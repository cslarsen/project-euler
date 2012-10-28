/*
 * ProjectEuler.net Problem 112
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <cassert>
#include <inttypes.h>
#include <math.h>

using namespace std;

#define Z uint32_t

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

  Z count = 0;
  double cutoff = 0.99;

  for ( Z n=1; n>0; ++n ) {
    if ( bouncy(n) )
      ++count;

    double ratio = (double)count/n;

    if ( ratio >= cutoff ) {
      cout << "At n=" << n << " we get ratio of " << ratio << endl;
      break;
    }
  }
}
