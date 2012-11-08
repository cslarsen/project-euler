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
#include <unordered_map>
#include <set>
#include <vector>
#include <inttypes.h>
#include <gmpxx.h>

using namespace std;

typedef int32_t Z;
typedef mpz_class M;
typedef pair<M, M> MM;
typedef pair<Z, M> ZM;

#define MAXK 100

struct MHash : std::unary_function<MHash, size_t>
{
  size_t operator()(const M& v) const {
    return v.get_ui();
  }
};

/*
 * Return number of nodes in a Fibonacci tree k.
 * Exactly the same as computing fib(k+2)-1
 */
static unordered_map<Z, M> mkm;
static M nodes(const Z& k)
{
  M a=1, b=2;

  if ( k <= 0 ) return 0;
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
 * See sequence http://oeis.org/A114375
 *
 * It basically converts the Fibonacci tree to a straight-line
 * bamboo-tree and returns its height.
 *
 * This function is very fast.
 */
static unordered_map<M, M, MHash> Nmemo;
static inline M N(const Z& k)
{
  if ( k <= 0 ) return 0;
  if ( k == 1 ) return 1;

  // Memoize
  if ( Nmemo.find(k) != Nmemo.end() )
    return Nmemo[k];

  /*
   * Equations from oeis.org:
   */
  M r = 0;
  if ( k % 3 ==0 ) {
    M n = k/3;
    r = 4*((n+1)/2);
  } else if ( (k-2) %3 == 0 ) {
    M n = (k-2)/3;
    r = 2*n+2 ;
  } else if ( (k-1) % 6 == 0 )
    r = 1;
  else
    // Do full calculation
    r = 1 + (N(k-1) ^ N(k-2));

  // Memoize
  Nmemo[k] = r;
  return r;
}

/*
 * Recurse a Fibonacci tree of order k and calculate nimsum on the fly.
 * It basically removes node n from Fib-tree k and returns its nimsum
 * (i.e., the height of a bamboo tree reduced by using the colon principle)
 *
 * It works by not following any children of the target node.
 *
 */
static M F(const Z& k, const M& n, const bool refresh = true)
{
  // Keep a running count of the current node number
  static Z id = 0;
  static bool found = false;

  // ORDER DEPENDENCY:
  if ( refresh ) { found = false; id = 0; }
  if ( k == 0 ) return 0;
  if ( id++ == n ) { found = true; return 0; }
  if ( k == 1 ) return 1;

  if ( found )
    // We can now use the faster function N()
    return 1 + (N(k-2) ^ N(k-1));

  return 1 + (F(k-2,n,false) ^ F(k-1,n,false));
}

map<ZM, M> mm;
map<MM, M> fm;
set<M> targets;

/*
 * Another way to calculate number of winning nodes.
 * The target should be set to N(k-1) or N(k+1) (see below).
 *
 * It works by looking at one of the root's (k+1) children.  For us to find
 * a winning node, this tree's bamboo height must be equal to the height of
 * the other tree (the other child of the root).  
 *
 * If that is so, then we get 1+(H^H)=0, or a winnnig nimsum of zero.
 *
 * What slows this down immensely is the loop.
 *
 * Note that there is only a limited set of target values, so we could
 * exploit that.
 */
static M match(const Z& k, const M& target)
{
  // Memoize
  ZM p(k, target);
  if ( mm.find(p) != mm.end() )
    return mm[p];

  const M size = nodes(k);

  M count = 0, foo=0;

  // Hmm, we just want to find all F(k,n) that equals target.
  // Must be a way to guess this?
  for ( M n=0; n<size; ++n )
    if ( F(k, n) == target )
      ++count;

  if ( foo!=0 ) {
    cout << "*** k=" << k << " count=" << count << " foo=" << foo << endl;
  }

  // Memoize
  mm[p] = count;
  return count;
}

/*
 * See above comment.
 *
 * We add up number of winning nodes in left and right subtrees.
 */
static M match(const Z& k)
{
  // If N(k)==1 then N(k-1)=N(k-2) which means that all we can't win,
  // because any pick will disturbe the system so that N(k)!=1.
  if ( N(k) == 1 )
    return 0;

  return match(k-1, N(k-2)) + match(k-2, N(k-1));
}

void all()
{
  for ( Z k=1; k<=MAXK; ++k ) {
    /*
    Z wins = 0;
    for ( M n=2, s=nodes(k); n<s; ++n )
      if ( F(k, n, true) == 1 )
        ++wins;
    */

    M m = match(k);
    cout << k << " " << m 
      << " N=" << N(k)
      << " " << N(k-1)
      << " " << N(k-2)
      << " s=" << nodes(k)
      << " s-w=" << nodes(k)-m << endl;

//    cout << k << " " << match(k) << endl;
  }
}

unordered_map< Z, set<M> > Fs;

static M H(const Z& k, const M& n, const bool refresh = true)
{
  // Keep a running count of the current node number
  static Z id = 0;
  static bool found = false;

  // ORDER DEPENDENCY:
  if ( refresh ) { found = false; id = 0; }
  if ( k == 0 ) return 0;

  if ( id++ == n ) {
    found = true;
    cout << " k=" << k << "," << (1+(N(k-1)^N(k-2))) << " ";
    return 0;
  }

  if ( k == 1 ) return 1;

  if ( found )
    // We can now use the faster function N()
    return 1 + (N(k-2) ^ N(k-1));

  return 1 + (H(k-2,n,false) ^ H(k-1,n,false));
}

void dill()
{
  Z k=6;
  M s=nodes(k);
  cout << "N(" << k << ") = " << N(k) << endl;
  cout << "N(" << (k-1) << ") = " << N(k-1) << endl;
  cout << "N(" << (k-2) << ") = " << N(k-2) << endl;
  for ( M n=0; n<s; ++n ) {
    cout << "k="<<k << " n=" << n << " F=" << H(k,n);
    if ( H(k,n)==1 ) cout << " *** ";
    cout << endl;
  }
}

void init()
{
//  dill();
//  exit(0);

  cout << "N(10k) = " << N(10000) << endl;
  cout << "N(10k-1) = " << N(10000-1) << endl;
  cout << "N(10k-2) = " << N(10000-2) << endl;

  all();
  exit(0);

  cout << "Computing tables" << endl;

  // For match(), compute all known targets
  for ( Z k=0; k<=MAXK; ++k )
    targets.insert(N(k));

  /*
    return match(k-1, N(k-2)) + match(k-2, N(k-1));
  */

  Z k=4;
  cout << "k=" << k << endl;
  cout << "N(k)   = " << N(k) << endl;
  cout << "N(k-1) = " << N(k-1) << endl;
  cout << "N(k-2) = " << N(k-2) << endl;
  cout << "Target: " << ((N(k)-1) ^ N(k-2)) << endl;

  /*
   * For k=4, we have N(left)=4 and N(right)=2 and N(k)=7
   *
   * We want to find a left-tree with height H so that
   *
   *   1 + (H ^ N(right) = N(k)
   *   H ^ N(right) = N(k)-1
   *   H = (N(k)-1) ^ N(right)
   *
   * By removing nodes from the left tree, we want to find
   * an n so that F(k-1, n) = H
   * 
   */
  k=3;
  for ( M n=0, s=nodes(k); n<s; ++n )
    cout << "k="<<k<<" n="<<n<< " "<<F(k,n) << endl;
  exit(0);

  // Calc F(k,n), put into Fs[k]
  for ( Z k=2; k<=MAXK; ++k ) {
    cout << k << " " << nodes(k) << endl;
    for ( M n=2, s=nodes(k); n<s; ++n )
      Fs[k].insert(F(k,n));
  }

  cout << "Done" << endl;
}

int main()
{
  all();
  for ( Z n=0; n<7; ++n )
    cout << "F(4," << n <<") = " << F(4,n) << endl;
  return 0;

  init();
  return 0;
  Z k = 6;
  M s = nodes(k);
  cout << "k=" << k << " gives size " << s << endl;
  cout << "N(k) = " << N(k) << endl;
  cout << "N(k-1) = " << N(k-1) << " (left subtree)" << endl;
  cout << "N(k-2) = " << N(k-2) << " (right subtree)" << endl;
  cout << "We want to get F(k,n)=1 for n=0...size" << endl;

  // in the left tree, we want to remove a node so
  // that we get nimsum(k-1,n)=N(k-2)
  cout << "LEFT" << endl;
  M target = N(k-2);
  for ( M n=2; n<nodes(k-1); ++n )
    cout << "F(" << k-1 << "," << n << ") = "
         << F(k-1,n) << " " << (F(k-1,n)==target?"***":"") << endl;
  cout << endl;

  // in the right tree, we want nimsum(k-2,n)=N(k-1)
  cout << "RIGHT" << endl;
  target = N(k-1);
  for ( M n=2; n<nodes(k-2); ++n )
    cout << "F(" << k-2 << "," << n << ") = "
         << F(k-2,n) << " " << (F(k-2,n)==target?"***":"") << endl;
  cout << endl;
  cout << "MATCH: " << match(k) << endl;

  for ( Z k=2; k<=10; ++k )
    cout << "k=" << k << " " << match(k) << endl;

  /*
  for ( M n=0; n<s; ++n )
    cout << "F(k," << n << ") = " << F(k,n) << " "
         << (F(k,n)==1? "***" : "") << endl;
  */
  cout << "---" << endl;
  all();
}
