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
#include <inttypes.h>

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
#define MAXSIZE 2048

typedef bitset<MAXSIZE> tree;

static Z left(const Z& i)
{
  Z r = (2*i)+1;
  assert(r < MAXSIZE);
  return r;
}

static Z right(const Z& i)
{
  Z r = (2*i) + 2;
  assert(r < MAXSIZE);
  return r;
}

// Construct a Fibonacci tree
static void build(tree& t, const Z& k, const Z& i=0)
{
  if ( k <= 0 )
    return;

  if ( k == 1 ) {
    t[i] = true;
    return;
  }

  t[i] = t[i+1] = true;
  build(t, k-1, left(i));
  build(t, k-2, right(i));
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

/*
 * Count nodes in trees.
 * This is basically a popcount.
 */
static Z nodes(const tree& t)
{
  return t.count();
}

/*
 * Count nodes in a tree with size k.
 * This is the same as the Fibonacci number minus one:
 * http://oeis.org/A000071
 */
static Z kmemo[1+MAXK];
static Z knodes(const Z& k)
{
  if ( k == 0 ) return 0;
  if ( k == 1 ) return 1;

  if ( kmemo[k] != 0 )
    return kmemo[k];

  kmemo[k] = 1 + knodes(k-1) + knodes(k-2);
  return kmemo[k];
}

static player other(const player p)
{
  return p==US? THEM : US;
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
  for ( Z n=0; n<size; ++n ) {
    tree c(t);
    remove(c, n);

    // if there is a winning move, current player wins
    if ( winner(c, other(current)) == current )
      return current;
  }

  // no winning moves, the current player loses
  return other(current);
}

static Z wins(const Z& k)
{
  Z w = 0;
  const Z size = knodes(k);

  /*
   * Start a new game, remove a given node and
   * check if it leads to a guaranteed win.
   */
  for ( Z n=0; n<size; ++n ) {
    tree t;
    build(t, k);
    remove(t, n);

    cout << "   Checking k=" << k << " n=" << n << endl;

    // Other player's turn:
    if ( winner(t, THEM) == US ) {
      tree o;
      build(o, k);
      cout << "   T(" << k << ") has winning node at " << n <<
        " with path " << path(o, n) << endl;
      ++w;
    }
  }

  return w;
}

int main()
{
  for ( Z k=1; k<MAXK; ++k ) {
    tree t;
    build(t, k);
    Z w = wins(k);
    cout << "** T(" << k << ") has " << w << " winning node(s)" << endl;
  }
}
