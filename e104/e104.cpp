#include <string>
#include <iostream>
#include <gmpxx.h>

using namespace std;

/*
 * Calculate the kth Fibonacci number, iteratively.
 */
static mpz_class fib(int k)
{
  if ( k <= 0 )
    return 0;

  mpz_class a(0), b(1);

  while ( --k ) {
    b += a;
    a = b-a; // avoids one temp variable
  }

  return b;
}

/*
 * Return true if string is 1-9 pandigital, i.e.
 * contains all the numbers from 1 to 9, and only numbers.
 */
static inline bool ispandigital(const std::string& s, int start)
{
  uint32_t mask = 0;

  for ( int n=start; n<start+9; ++n )
    mask |= 1 << (s[n] - '0');
 
  return mask == 0x3FE; // 0b1111111110
}

/*
 * A faster way to check that the number ENDS with a 1-9 pandigital number.
 */
static bool pandigital_end(mpz_class n)
{
  uint32_t mask = 0;

  for ( int i=0; i<9; ++i ) {
    mpz_class m = n % 10;
    mask |= 1 << m.get_ui();
    n /= 10;
  }

  return mask == 0x3FE;
}

static inline bool pandigital_start(const mpz_class& n)
{
  return ispandigital(n.get_str(), 0);
}

/*
 * Return true if we've found what we were looking for.
 */
static inline bool found(const mpz_class& n)
{
  return
    pandigital_end(n) &&
    pandigital_start(n);
}

/*
 * Find the index of the first Fibonacci number whose first and last 9
 * digits are pandigital.
 */
static int search()
{
  mpz_class a(0), b(1), tmp;

  for ( int k=2; ; ++k ) {
    tmp = b;
    b += a;
    a = tmp;
    // note: can avoid using tmp by doing a=b-a

    if ( found(b) )
      return k;

    if ( (k % 1000) == 0 ) {
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
  cout << "|F_k| = " << fib(k).get_str().length() << endl;
}
