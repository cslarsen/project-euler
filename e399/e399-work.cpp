#include <iostream>
#include <cassert>
#include <vector>
#include <inttypes.h>

using namespace std;

#define ZEROES 10000000000000000U
#define SQUARES 100000000

template<typename INT>
static bool square_free(const INT& n)
{
  static vector<INT> squares;

  // build vector
  if ( squares.size() == 0 ) {
    for ( INT n=2; n<SQUARES; ++n )
      squares.push_back(n*n);
  }

  // todo: use some tables here to help
  INT i;
  for ( i=0; i<squares.size(); ++i ) {
    INT sq = squares[i];

    if ( sq >= n )
      break;

    if ( (n % sq) == 0 )
      return false;
  }

  if ( i==squares.size() )
    assert(false);

  return true;
}

int main()
{
  uint64_t n=1, stop=200;

  // right side
  uint64_t a=0, b=1;

  for(;;) {
    uint64_t tmp = b;
    b += a % ZEROES;
    b %= ZEROES;
    a = tmp;

    if ( square_free(b) ) {
      cout << ++n << " square-free Fibonacci-number is " << b << endl;

      if ( n == stop )
        break;
    }
  }

  cout << n << " square-free Fibonacci-number is " << b << endl;
}
