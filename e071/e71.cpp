/*
 * ProjectEuler.net Problem 71
 *
 * Solution by Christian Stigen Larsen
 * http://csl.sublevel3.org
 *
 * Check out Wikipedia on "Farey sequence".
 *
 * Iterating through the Farey sequence is too slow:  For the order
 * n = 1M there are about 303 billion fractions.  We therefore need
 * a clever method to find the fraction.
 *
 * For a Farey-pair a/b < c/d, we have
 *
 *     bc - ad = 1.
 *
 * Given c/d = 3/7 and that the order max(b,d) <= 1M, we solve for a:
 *
 *     a = (b*c - 1) / d
 *
 * The numerator a must be an integer, so we'll start with d=1M and
 * decrement it by one until we get an integer.  That is our solution.
 *
 * Since every 7th number is divisible by 7 (by definition), and having
 *
 *   b*c - 1 = 1M*3 - 1 = 2999999  and  d = 1M
 *
 * along with b = n (the order), starting at 1M, we simply recursively
 * call our test() function to find a.
 *
 * You can do it by hand as well, since you should find an integer a
 * within 7 tries.
 *
 */

#include <iostream>
#include <limits>
#include <inttypes.h>

static const double epsilon = std::numeric_limits<double>::epsilon();

static uint32_t search(uint32_t order)
{
  uint32_t i = (order*3 - 1)/7;
  double   f = (order*3 - 1)/7.0;

  // Return `i` if it's an integer, else decrement order
  return f-i <= epsilon? i : search(order-1);
}

int main()
{
  std::cout << search(1000000) << std::endl;
}
