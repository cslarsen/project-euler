/*
 * ProjectEuler.net problem 104
 * by Christian Stigen Larsen, http://csl.sublevel3.org
 *
 * I first did this by brute force and some micro-optimizations:
 * Using libgmp, I checked if the 9 least significant digits were 1-9
 * pandigital by using mod-10 div-10 to extract digits.  This is a bit
 * faster than convering to a string.  However, to check the left (most
 * significant) part, I had to use strings.
 *
 * It took about 4 minutes to get the answer this way.
 *
 * A faster way is to compute the Fibonacci sequence in two parts: A small
 * right part, and a big left part.
 *
 * The right part can be computed by doing a+b mod 10^9.  The left part must
 * be calculated normally (and fully), but you save so much time with the
 * first test that it runs in around 8 seconds.
 *
 */
#include <string>
#include <iostream>
#include <gmpxx.h>

using namespace std;

/*
 * A faster way to check that the number ENDS with a 1-9 pandigital number.
 */
static bool pandigital_end(uint64_t n)
{
  uint32_t mask = 0;

  for ( int i=0; i<9; ++i ) {
    mask |= 1 << (n % 10);
    n /= 10;
  }

  return mask == 0x3FE; // 0b1111111110
}

static inline bool pandigital_start(const mpz_class& n)
{
  const std::string s(n.get_str());
  uint32_t mask = 0;

  for ( int n=0; n<9; ++n )
    mask |= 1 << (s[n] - '0');
 
  return mask == 0x3FE; // 0b1111111110
}

/*
 * Find the index of the first Fibonacci number whose first and last 9
 * digits are pandigital.
 */
static int search()
{
  // only calculate right part of fibonacci
  uint64_t a(0), b(1);

  // left part is calculated fully
  mpz_class la(0), lb(1), tmp;

  for ( int k=2; ; ++k ) {
    // right part
    uint64_t t = b;
    b = (a+b) % 1000000000;
    a = t;
    // note: can avoid using tmp by doing a=b-a

    // left part
    tmp = lb;
    lb += la;
    la = tmp;

    // check the right (and fast) part first
    if ( pandigital_end(b) ) {
      // check left (MSB) part by using the full fibonacci number
      if ( pandigital_start(lb) )
        return k;
    }

    if ( (k % 10000) == 0 ) {
      cout << k << "\r";
      cout.flush();
    }
  }
}

int main()
{
  int k = search();
  cout << endl;
  cout << "k = " << k << endl;
}
