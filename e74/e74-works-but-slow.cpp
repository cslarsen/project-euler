#include <inttypes.h>
#include <iostream>
#include <bitset>

#define MAX_NUM 1000000
#define MAX_SUMFACT 10*MAX_NUM // sumfact(10^6 - 1)

using namespace std;

int fact(int n)
{
  int r = 1;

  while ( n )
    r *= n--;

  return r;
}

/*
 * Calculates sum of factorial of digits
 */
int sumfact(int n)
{
  int r = 0;

  while ( n ) {
    r += fact(n % 10);
    n /= 10;
  }

  return r;
}

int chains(int n)
{
  static bool init = false;
  static int8_t memo[MAX_SUMFACT];

  if ( !init ) {
    for ( int i=0; i<MAX_SUMFACT; ++i )
      memo[i] = (int8_t)-1;
    init = true;
  }

  if ( memo[n] != (int8_t)-1 )
    return memo[n];

  int r = 0, N = n;
  bitset<MAX_SUMFACT> seen;

  while ( !seen[n] ) {
    if ( memo[n] != (int8_t)-1 ) {
      r += (int) memo[n];
      break;
    }

    seen[n] = 1;
    n = sumfact(n);
    ++r;
  }

  memo[N] = (int8_t)r;
  return r;
}

int main()
{
  int c = 0;
  for ( int n=1; n<MAX_NUM; ++n ) {
//  for ( int n=1; n<30000; ++n ) {
    if ( chains(n) == 60 )
      ++c;

    if ( (n % 100) == 0 ) {
      cout << n << "\r";
      cout.flush();
    }
  }

  cout << "Answer: " << c << endl;
}
