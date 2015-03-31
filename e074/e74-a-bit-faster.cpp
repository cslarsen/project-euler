/*
 * ProjectEuler.net Problem 74
 * by Christian Stigen Larsen
 *
 * Brute force, a tad slow at 10 seconds on Core i7.
 */

#include <inttypes.h>
#include <iostream>
#include <bitset>

#define MAX_NUM 1000000
#define MAX_SUM 2177280 // max sumfact(n) for n=1...10^6

using namespace std;

static int fact(int n)
{
  int r = 1;

  while ( n )
    r *= n--;

  return r;
}

/*
 * Calculates sum of factorial of digits
 */
static int sumfact(int n)
{
  int r = 0;

  while ( n ) {
    r += fact(n % 10);
    n /= 10;
  }

  return r;
}

static int chains(int n, int steps=0)
{
  static bitset<MAX_SUM> seen;

  if ( steps == 0 )
    seen.reset();

  if ( seen[n] )
    return steps;

  seen[n] = 1;
  return chains(sumfact(n), steps+1);
}

int main()
{
  int count = 0;

  for ( int n=1; n<MAX_NUM; ++n ) {
    if ( chains(n) == 60 )
      ++count;

    if ( (n % 10000) == 0 ) {
      cout << "n=" << n << " count=" << count << "\r";
      cout.flush();
    }
  }

  cout << "Answer: " << count << "            " << endl;
}
