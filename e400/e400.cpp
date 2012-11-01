/*
 * ProjectEuler.net Problem 400
 * Solved by Christian Stigen Larsen
 */

/*
 * Notes:
 * - See Fibonacci heap
 * - See the Nim game, https://en.wikipedia.org/wiki/Nim
 * - See game tree, https://en.wikipedia.org/wiki/Game_tree
 * - "A Fibonacci tree is the most unbalanced AVL tree allowed",
 *   http://xlinux.nist.gov/dads/HTML/fibonacciTree.html
 */

#include <iostream>
#include <cassert>
#include <bitset>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <inttypes.h>
#include "string.h"
#include "sha1.h"

using namespace std;

typedef uint32_t Z;

enum player
{
  US = 0,
  THEM = 1
};

/*
 * We'll use arrays for our binary tree implementation.
 * See https://en.wikipedia.org/wiki/Binary_tree#Arrays
 *
 * We'll use a bitset for representing the tree.
 * The bits represents whether a given node exists.
 *
 * Although this is a compact representation, it will
 * quickly be impractical for Fibonacci trees of low
 * order (k=43 gives 1B bits, or 125Mb of memory).
 *
 */
#define MAXK 7
#define MAXSIZE 8*1024

typedef bitset<MAXSIZE> tree;

class LessThan {
public:
   bool operator() (const tree& lhs, const tree& rhs) const
   {
      size_t i = MAXSIZE;
      while ( i > 0 ) {
         if ( lhs[i-1] == rhs[i-1] ) {
            i--;
         } else if ( lhs[i-1] < rhs[i-1] ) {
            return true;
         } else {
            return false;
         }
      }
      return false;
   }
};

static inline Z left(const Z& i)
{
  const Z r = (2*i)+1;
  assert(r < MAXSIZE);
  return r;
}

static inline Z right(const Z& i)
{
  const Z r = (2*i) + 2;
  assert(r < MAXSIZE);
  return r;
}

// Construct a Fibonacci tree
static void __build(tree& t, const Z& k, const Z& i=0)
{
  if ( k <= 0 )
    return;

  if ( k == 1 ) {
    t[i] = true;
    return;
  }

  t[i] = t[i+1] = true;
  __build(t, k-1, left(i));
  __build(t, k-2, right(i));
}

static tree build(const Z& k)
{
  tree t;
  __build(t, k);
  return t;
}

static void rmchildren(tree &t, const Z& i)
{
  if ( i<MAXSIZE && t[i] ) {
    t[i] = false;
    rmchildren(t, left(i));
    rmchildren(t, right(i));
  }
}

// Print path to given node
static string path(
    const tree& t,
    const Z& target,
    const Z& i=0,
    const bool refresh=true,
    string p="")
{
  // Keep a running count of the current node number
  static Z nodeid = 0;

  // ORDER DEPENDENCY:
  if ( refresh ) nodeid = 0;
  if ( i>=MAXSIZE || nodeid > target ) return "";
  if ( !refresh ) ++nodeid;

  if ( target == nodeid )
    return p;

  if ( t[i] ) {
    if ( t[left(i)] ) {
      string s = path(t, target, left(i), false, p + "L");
      if ( !s.empty() )
        return s;
    }
    if ( t[right(i)] ) {
      string s = path(t, target, right(i), false, p + "R");
      if ( !s.empty() )
        return s;
    }
  }

  return "";
}

static void remove(
    tree& t,
    const Z& target,
    const Z& i=0,
    const bool refresh=true)
{
  // Keep a running count of the current node number
  static Z nodeid = 0;

  // ORDER DEPENDENCY:
  if ( refresh ) nodeid = 0;
  if ( i>=MAXSIZE || nodeid > target ) return;
  if ( !refresh ) ++nodeid;

  if ( target == nodeid ) {
    // remove this node and child nodes
    rmchildren(t, i);
    return;
  }

  if ( t[i] ) {
    if ( t[left(i)] ) remove(t, target, left(i), false);
    if ( t[right(i)] ) remove(t, target, right(i), false);
  }
}

// find nodeid for root's right child
// (there MUST be a faster way to do this)
static Z rrch(const tree& t,
    const Z& i=0,
    const bool refresh=true)
{
  // Keep a running count of the current node number
  static Z nodeid = 0;

  // ORDER DEPENDENCY:
  if ( refresh ) nodeid = 0;
  if ( i>=MAXSIZE ) return 0;
  if ( !refresh ) ++nodeid;

  if ( right(0) == i ) {
    return nodeid;
  }

  if ( t[i] ) {
    Z a=0;
    if ( t[left(i)] ) a = rrch(t, left(i), false);
    if ( a != 0 ) return a;
    if ( t[right(i)] ) a = rrch(t, right(i), false);
    if ( a != 0 ) return a;
  }

  return 0;
}

/*
 * Node count in tree is the same as popcount.
 */
static inline Z nodes(const tree& t)
{
  return t.count();
}

/*
 * Calculate nodes in a tree with size k.
 *
 * This is the same as the Fibonacci number minus one:
 * http://oeis.org/A000071
 *
 */
static Z knodes(const Z& k)
{
  Z a=1, b=2;

  if ( k == 0 ) return 0;
  if ( k == 1 ) return a;

  for ( Z n=2; n<k; ++n ) {
    Z t = b;
    b = a+b+1;
    a = t;
  }

  return b;
}

static inline player other(const player p)
{
  return p==US? THEM : US;
}

//static map<tree, bool, LessThan> loss;
static map<Z, bool> loss;

Z tree_hash(const tree& t)
{
  SHA1Context c;
  SHA1Reset(&c);
  SHA1Input(&c, (uint8_t*)&t, sizeof(t));
  uint8_t dig[SHA1HashSize];
  SHA1Result(&c, dig);
  Z r=0;
  memcpy(&r, &dig[0], sizeof(r));
  return r;
}

static player winner(const tree& t, const player current)
{
  const Z size = nodes(t);

  // empty tree, the given player wins
  if ( size == 0 )
    return current;

  // One node left:  The given player loses.
  if ( size == 1 )
    return other(current);

  /*
   * Two nodes:  The current player wins.
   */
  if ( size == 2 )
    return current;

  /*
   * For size==3, if this is our turn, we can only win
   * if the tree is unbalanced.
   */
  if ( size == 3 ) {
    /*
     * Two possible trees of size 3:
     *
     *   O
     *  / \  If our turn, we cannot win (balanced tree)
     * O   O
     *
     *      O
     *     /
     *    O  If our turn, we choose the middle
     *   /   node and win (unbalanced tree)
     *  O
     */
    bool balanced = t[left(0)] && t[right(0)];

    // balanced tree, the given player loses
    if ( balanced )
      return other(current);

    // unbalanced, current player wins
    return current;
  }

  /*
   * For size 4, we have the following possible trees:
   *
   *        O     O        O
   *       /     / \      /
   *      O     O   O    O
   *     /     /        / \
   *    O     O        O   O
   *   /
   *  O
   *    (1)      (2)     (3)
   *
   * The point of the player is to chose a node so
   * that we know we win.  In other words, we want
   * to get to a balanced size 3 tree, or a tree
   * of size 1.
   *
   * If we have tree 1 or 3, we can remove node 1
   * and win.  If we have tree 2, we can removex
   * node 2 (the leaf node) and win.
   *
   * So the current player is guaranteed a win at
   * this point.
   *
   * However, we'd like to do this algorithmically,
   * so we just try to remove a node (removing any
   * node will reduce the size of the tree to a
   * known position).  If the current player can
   * find a node that gives a win, he will of course
   * chose that one and win the game.
   */

  /*
   * First some heuristics.
   *
   * If the root node has only one child, the current
   * player will automatically be able to win.
   */
  if ( (t[right(0)] + t[left(0)]) == 1 )
    return current;

  /*
   * The children of the root are guaranteed losses,
   * so start at n=2 and skip the right child of root.
   */
  const Z root_right_child = rrch(t);

  // Try all possibilities
  for ( Z n=2; n<size; ++n ) {
    if ( n == root_right_child )
      continue;

    tree c(t);
    remove(c, n);

    Z h = tree_hash(c);

    // seen it before, and it was a loss
    if ( loss.find(h) != loss.end() ) {
      if ( loss[h] == false )
        return current;
      continue;
    }

    // if there is a winning move, current player wins
    if ( winner(c, other(current)) == current ) {
      loss[h] = false;
      return current;
    }

    loss[h] = true;
  }

  // no winning moves, the current player loses
  return other(current);
}

/*
 * Same as f(k)
 */
static Z wins(const Z& k)
{
  Z w = 0;
  const Z size = knodes(k);

  cout << "   k=" << k << " size=" << size-1 << ": ";

  /*
   * Start a new game, remove a given node and
   * check if it leads to a guaranteed win.
   */
  for ( Z n=0; n<size; ++n ) {
    tree t = build(k);
    remove(t, n);

    cout << n << " "; cout.flush();

    // Other player's turn:
    if ( winner(t, THEM) == US ) {
      ++w;

      cout << endl
        << "   T(" << k << ") has winning node at " << n
        << " with path " << path(build(k), n) << endl << "   ";
    }
  }

  return w;
}

int main()
{
  for ( Z k=1; k<MAXK; ++k ) {
    Z w = wins(k);
    cout << endl;
    cout << "** T(" << k << ") has " << w << " winning node(s)" << endl;
  }
}
