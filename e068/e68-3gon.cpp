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
 *
 * Run with
 *
 * $ ./e68 | sort
 *
 * and select the last line.
 */

#include <iostream>
#include <set>
#include <algorithm>
#include <inttypes.h>

using namespace std;

#define SIZE 3

typedef uint32_t I;

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
      I s = 0, sm=outer[0]; // start
      // Find lowest start point in outer ring
      for ( I i=1; i<SIZE; ++i )
        if ( sm > outer[i] ) {
          sm = outer[i];
          s = i;
        }

      for ( I i=0; i<SIZE; ++i )
        cout << outer[(i+s) % SIZE] << ","
             << inner[(i+s) % SIZE] << ","
             << inner[(i+s+1) % SIZE] << " ";

      cout.width(2);
      cout << sum1 << endl;
    }

  } while ( next_permutation(digits, digits+sizeof(digits)/sizeof(I)) );
}
