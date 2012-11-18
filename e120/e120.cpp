/*
 * ProjectEuler.net Problem 120
 * Solved by Christian Stigen Larsne
 *
 * This must be the easiest Euler problem ever.
 */

#include <iostream>
#include <cassert>
#include <inttypes.h>

using namespace std;

typedef uint32_t Z;

static Z f(const Z& a, Z n)
{
  const Z aa = a*a;
  Z a1 = 1, a2 = 1;

  while ( n-- ) {
    a1 = a1*(a-1) % aa;
    a2 = a2*(a+1) % aa;
  }

  return (a1+a2) % aa;
}

static Z largest(const Z& a, const Z& m)
{
  Z r = 0;

  for ( Z i=0; i<m; ++i ) {
    Z n = f(a,i);
    if ( n > r ) r = n;
  }

  return r;
}

int main()
{
  assert(f(7,3)==42);

  Z s = 0;

  for ( Z a=3; a<=1000; ++a ) {
    s += largest(a, a*2);
    cout << a << " ";
    cout.flush();
  }

  cout << endl;
  cout << s << endl;
}
