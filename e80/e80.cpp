/*
 * ProjectEuler.net problem 80
 * Solved by Christian Stigen Larsen
 *
 * Brute-force using GMP, not very elegant.
 *
 * Expected sum is: 40886
 *
 * For larger ranges/numbers you need to increase BITS.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <gmpxx.h>

using namespace std;

#define BITS 512
#define DIGITS 100

typedef size_t I;
typedef mpf_class F;
typedef mpz_class Z;

static string str(const F& f)
{
  stringstream s;
  s.precision(DIGITS*2);
  s << f;
  return s.str();
}

// Digital square sum of digits after comma
static Z dss(const F f)
{
  F sq;
  mpf_sqrt(sq.get_mpf_t(), f.get_mpf_t());

  // Skip non-irrationals
  if ( Z(sq)*Z(sq) == f )
    return 0;

  string s = str(sq);

  Z sum = 0;
  I digits = DIGITS;

  for ( I i=0; i<digits && i<s.size(); ++i ) {
    if ( s[i] == '.' ) {
      digits += i;
      continue;
    }

    sum += s[i] - '0';
  }

  return sum;
}

int main()
{
  mpf_set_default_prec(BITS);

  Z sum = 0;
  for ( Z i=2; i<=DIGITS; ++i ) {
    Z s = dss(i);
    //cout << i << " -> " << s << endl;
    sum += s;
  }
  
  cout << "Sum: " << sum << endl;
}
