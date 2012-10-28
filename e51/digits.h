#include <inttypes.h>

/*
 * Return number of digits in n.
 */
int digits(int64_t n)
{
  int r = 0;

  while ( n )
    ++r, n /= 10;

  return r;
}
