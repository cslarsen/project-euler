/*
 * ProjectEuler.net Problem 160
 * Solved by Christian Stigen Larsen
 */

#include <iostream>

using namespace std;
typedef uint64_t Z;

#define MASK 100000UL

int main()
{
  register Z f=1;

  //for ( register Z n=2; n < 1000000000000UL; ++n ) {
  for ( register Z n=2; n < 1000000UL; ++n ) {
    f = (f * n) % 100000;
    if (f == 0 )
      f = 1;
//    if ( (n % 1000000) == 0 )
      cout << "n=" << n << " f=" << f << endl;
  }

  cout << f << endl;
}

