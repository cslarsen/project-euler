/*
 * ProjectEuler.net Problem 204
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <inttypes.h>

using namespace std;

typedef uint64_t Z;

static inline Z last(const Z& n)
{
  return n % 10;
}

static inline void div10(Z& n, Z tens)
{
  while ( tens-- )
    n /= 10;
}


// is n like 1_2_3_4_5_6_7_8_9_0
static bool accepted(const Z& b)
{
  Z n = b*b;

  // last number must be zero
  if ( last(n) != 0 ) return false;

  div10(n, 2); if ( last(n) != 9 ) return false;
  div10(n, 2); if ( last(n) != 8 ) return false;
  div10(n, 2); if ( last(n) != 7 ) return false;
  div10(n, 2); if ( last(n) != 6 ) return false;
  div10(n, 2); if ( last(n) != 5 ) return false;
  div10(n, 2); if ( last(n) != 4 ) return false;
  div10(n, 2); if ( last(n) != 3 ) return false;
  div10(n, 2); if ( last(n) != 2 ) return false;
  div10(n, 2); if ( last(n) != 1 ) return false;

  return true;
}

int main()
{
  // math.sqrt(1020304050607080900) == 1010101010.1010101
  Z n = 1010101010;

  while ( !accepted(n) )
    ++n;

  cout << n << " squared is: " << endl;
  cout << (n*n) << endl;
  cout << "1_2_3_4_5_6_7_8_9_0" << endl;
}
