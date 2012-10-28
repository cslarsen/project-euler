/*
 * Better solution from euler problem 73 forum
 */

#include <stdio.h>
#include "gcd.h"

int main()
{
  int total = 0;

  for ( register int d = 3; d<=12000; ++d )
  for ( register int n = ((d/3) + 1); n <= d/2; ++n )
    if ( binary_gcd(d, n) == 1 ) ++total;

  printf("%d\n", total);
  return 0;
}
