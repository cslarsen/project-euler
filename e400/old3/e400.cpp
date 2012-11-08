/*
 * ProjectEuler.net Problem 400
 * Solved by Christian Stigen Larsen
 *
 *
 * Theory
 * ======
 *
 * If you look at Red-Blue-Green Hackenbush Misere games and the Colon
 * Principle, we can  reduce each of these games to a misere game of Nim.
 *
 * Such games can be won if the nimsum is zero.  So for each Fibonacci tree,
 * remove a node and calculate its nimsum.  If it's zero, we will win.
 *
 * Currently we use a bitset to represent the tree.  This will only be
 * practical for very small trees.
 *
 * So we need to eliminate the use of bitsets.
 *
 * Strategy
 * ========
 *
 * When constructing a Fibonacci tree, also record the node number we're at
 * and a target node to remove.
 *
 * When we reach the node to remove, stop and then calculate the nimsum as
 * we go back up the tree.  Using memoization, we should be able to get the
 * nimsum in somewhere around O(k) for T(k).
 */

#include <iostream>
#include <cassert>
#include <map>
#include <inttypes.h>
#include <gmpxx.h>

using namespace std;
typedef uint32_t Z;
//typedef mpz_class M;
typedef uint32_t M;

#define MAXK 100


/*
 * mknodes(k) == Fib(k-2)-1
 */
static map<Z, M> mkm;
static M mknodes(const Z& k)
{
  M a=1, b=2;

  if ( k == 0 ) return 0;
  if ( k == 1 ) return a;

  // lookup
  if ( mkm.find(k) != mkm.end() )
    return mkm[k];

  for ( Z n=2; n<k; ++n ) {
    mkm[n] = b; // save
    M t = b;
    b = a+b+1;
    a = t;
  }

  return b;
}

/*
 * Memoized nimsum of Fibonacci tree k.
 */
static map<M, M> Nmemo;
static inline M N(const M& k)
{
  if ( k == 0 ) return 0;
  if ( k == 1 ) return 1;

  if ( Nmemo.find(k) != Nmemo.end() )
    return Nmemo[k];

  const M r = 1 + (N(k-1) ^ N(k-2));
  Nmemo[k] = r;
  return r;
}

/*
 * TODO: Make this ITERATIVE instead of using recursion.
 */
static M msum(const Z& k, const Z& n, const bool refresh = false)
{
  // Keep a running count of the current node number
  static Z id = 0;
  static bool found = false;

  // ORDER DEPENDENCY:
  if ( refresh ) { found = false; id = 0; }
  if ( k == 0 ) return 0;
  if ( id++ == n ) { found = true; return 0; }
  if ( k == 1 ) return 1;

  // if found, use fast memoized ones
  if ( found )
    return 1 + (N(k-2) ^ N(k-1));

  return 1 + (msum(k-2,n) ^ msum(k-1, n));
}

int main()
{
  Z k=6;
  cout << "n("<<k-1<<") = " << N(k-1) << endl;
  cout << "n("<<k-2<<") = " << N(k-2) << endl;
  cout << "1+xor: " << 1+(N(k-1) ^ N(k-2)) << endl;
  cout << "nimsum " << N(k) << endl;
  cout << endl;

  k = 5;
  cout << "n("<<k-1<<") = " << N(k-1) << endl;
  cout << "n("<<k-2<<") = " << N(k-2) << endl;
  cout << "1+xor: " << 1+(N(k-1) ^ N(k-2)) << endl;
  cout << "nimsum " << N(k) << endl;

  return 0;
  /*
  Z big = mknodes(10000);
  Z wins=0;
  for ( M n=2; n<big; ++n ) {
    if ( msum(10000, n, true) == 1 ) {
      ++wins;
      if ( (wins % 100) == 0 ) {
        mpf_class i(n);
        i /= big;
        i *= 100;
        cout << wins << " at " << i << "%" << endl;
      }
    }
  }
  cout << "Answer: " << wins << endl;
  return 0;
  */

  for ( Z k=1; k<=MAXK; ++k ) {
    M size = mknodes(k);
    Z wins = 0;

    for ( M n=2; n<size; ++n ) {
      M s = msum(k, n, true); //nimsum(k, n);

   //   cout << "nimsum(k=" << k << ", n=" << n << ") = " << nimsum(k,n)
    //       << " vs " << msum(k, n, true) << endl;

      if ( s == 1 ) {
        ++wins;
      }
    }

    cout << k << " " << wins << " " << N(k) << endl;
  }
}
