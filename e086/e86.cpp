/*
 * Project Euler problem 86
 * Solved by Christian Stigen Larsen
 *
 * Runs in ~4 secs, but there is probably a much faster version.
 */
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define LIMIT 1000000
typedef unsigned Z;

static inline bool perfect_square(const Z& n)
{
  // See
  // http://stackoverflow.com/questions/295579/fastest-way-to-determine-if-an-integers-square-root-is-an-integer
  switch ( n & 0xF ) {
  case 0: case 1: case 4: case 9:
    break;
  default:
    return false;
  }

  const float s = sqrtf(n);
  return static_cast<Z>(s) == s;
}

static inline Z next(const Z& l)
{
  Z c = 0;

  for ( Z h=1; h<=l; ++h )
    for ( Z w=h; w<=l; ++w )
      c += perfect_square((w+h)*(w+h) + l*l);

  return c;
}

int main()
{
  Z c=0;

  for ( Z l=0; c<LIMIT; ++l ) {
    c += next(l);
    printf("M(%u) = %u\n", l, c);
  }

  return 0;
}
