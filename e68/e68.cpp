/*
 * ProjectEuler.net problem 68
 * Solved by Christian Stigen Larsen
 *
 * Magic 3-gon:
 *
 *      O 4
 *       \
 *        O 3
 *       / \
 *    1 O---O--O 6
 *     /   2
 *  5 O
 *
 * For the magic 5-gon, remember that 10 must be in the outer nodes.
 */

#include <iostream>
#include <set>
#include <algorithm>
#include <inttypes.h>

using namespace std;

typedef uint32_t I;
typedef set<I> SET;

std::ostream& operator<<(std::ostream& o, const set<I>& s)
{
  for ( const auto& x : s )
    o << x << " ";

  return o;
}


int main()
{
  I inner[3];
  I outer[3];
  I digits[] = {1,2,3,4,5,6};

  do {
    inner[0] = digits[0];
    inner[1] = digits[1];
    inner[2] = digits[2];

    outer[0] = digits[3];
    outer[1] = digits[4];
    outer[2] = digits[5];

    I sum1 = outer[0] + inner[0] + inner[1];
    I sum2 = outer[1] + inner[1] + inner[2];
    I sum3 = outer[2] + inner[2] + inner[0];

    if ( sum1 == sum2 && sum3 == sum2 ) {
      cout.width(2);
      cout << sum1 << " ";
      cout << outer[0] << "," << inner[0] << "," << inner[1] << ";";
      cout << outer[1] << "," << inner[1] << "," << inner[2] << ";";
      cout << outer[2] << "," << inner[2] << "," << inner[0] << endl;
    }

  } while ( next_permutation(digits, digits+sizeof(digits)/sizeof(I)) );
}
