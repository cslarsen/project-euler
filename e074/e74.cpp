/*
 * ProjectEuler.net Problem 74
 *
 * Solved by Christian Stigen Larsen
 * http://csl.sublevel3.org
 *
 * Brute force, but runs in 2.3 secs on Intel Core i7.
 */

#include <iostream>

using namespace std;

// factorials for digits 0..9
int fact[10] = {
  1,
  1,
  2,
  6,
  24,
  120,
  720,
  5040,
  40320,
  362880};

/*
 * Calculates sum of factorial of digits in n.
 */
static int sumfact(int n)
{
  int r = 0;

  while ( n )
    r += fact[n % 10], n /= 10;

  return r;
}

/*
 * Recursively calculate sumfact(n) and return number of steps in loop.
 *
 * E.g.:  chains(169, 0) -> chains(363601, 1) ->
 *        chains(1454, 2) -> chains(169, 3) ==> 3
 */
static int chains(int n, int steps=0)
{
  static int prev[61];

  // init prev
  if ( steps == 0 )
    memset(prev, 0, sizeof(prev));

  // have we seen n before?
  for ( int p=steps-1; p>=0; --p )
    if ( prev[p] == n )
      return steps;

  prev[steps] = n;
  return chains(sumfact(n), steps+1);
}

int main()
{
  int count = 0;

  for ( int n=1; n<1000000; ++n )
    if ( chains(n) == 60 )
      ++count;

  cout << count << endl;
}
