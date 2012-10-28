/*
 * ProjectEuler.net Problem 85
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <inttypes.h>
#include <cassert>

using namespace std;

typedef int32_t Z;

Z grid(const Z x, const Z y)
{
  Z c = 0;

  for ( Z w=0; w<x; ++w )
  for ( Z h=0; h<y; ++h )
  for ( Z xp=w; xp<x; ++xp )
  for ( Z yp=h; yp<y; ++yp )
    ++c;

  return c;
}

int main()
{
  assert(grid(1, 1) == 1);
  assert(grid(1, 2) == 3);
  assert(grid(2, 1) == 3);
  assert(grid(2, 2) == 9);
  assert(grid(3, 2) == 18);
  assert(grid(2, 3) == 18);

  Z target = 2000000;
  Z nearest = 2*target;

  Z stop = 100;

  for ( Z x=1; x<stop; ++x )
  for ( Z y=1; y<=x; ++y ) {
    Z c = grid(x, y);

    if ( abs(target-c) < nearest ) {
      nearest = abs(target-c);
      cout << x << "x" << y << " A=" << x*y
           << " contains " << c
           << " rectangles" << endl;
    }
  }
}
