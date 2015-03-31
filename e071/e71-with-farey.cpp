/*
 * ProjectEuler.net problem 71
 * by Christian Stigen Larsen
 *
 * Note, iterating through the Farey sequence is too slow. For n=1M there
 * are about 303 billion fractions, so good luck with that.
 *
 * We need a clever method to find the fraction. So, we use a pen-and-paper
 * method, although we code it up as well.
 *
 * SO, for a Farey-pair a/b < c/d, we have bc - ad = 1.
 *
 * Given c/d = 3/7 and that the order max(b,d) <= 1M, we solve for a:
 *
 *   a = (b*c - 1) / d
 *
 * The numerator a must be an integer, so we'll start with d=1M and
 * decrement it by one until we get an integer.  That is our solution.
 *
 * Since every 7th number is divisible by 7 (by definition), and having
 *
 *   b*c - 1 = 1M*3 - 1 = 2999999  and  d = 1M
 *
 * along with b = n (the order), starting at 1M, we simply recursively call
 * our test() function to find a.
 *
 * You can do it by hand as well, since you should find an integer a within
 * 7 tries.
 *
 */

#include <iostream>
#include <limits>
#include <inttypes.h>

using namespace std;
typedef uint32_t integer;

/*
 * Prints the fraction just before 3/7.
 * Impractical for large n.
 *
 * The method uses two fractions in sequence to calculate the third.
 * See Wikipedia for details.
 *
 * The code here is added just for fun.
 */
static void farey(const integer n)
{
  register integer
    a = 0,
    b = 1,
    c = 1,
    d = n,
    k = 0;

  integer preva=0, prevb=1;

  while ( c <= n ) {
    k = (n + b) / d;

    integer tmp = a;
    a = c;
    c = k*c - tmp;

    tmp = b;
    b = d;
    d = k*d - tmp;

    if ( a == 3 && b == 7 ) {
      cout << preva << "/" << prevb
        << " for n=" << n << endl;
      return;
    }

    preva = a;
    prevb = b;
  }
}

static integer test(integer n)
{
  integer b=n, c=3, d=7;
  integer a = (b*c - 1) / d;
  double fa = (b*c - 1) / (double)d;

  if ( (fa - a) <= numeric_limits<double>::epsilon() ) {
    cout << a << "/" << n << endl;
    return a;
  }

  return test(n-1);
}

int main()
{
//  farey(8);
//  farey(12000);
  test(1000000);
}
