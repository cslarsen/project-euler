#include <iostream>
#include <gmpxx.h>

using namespace std;

static bool square_free(const mpz_class& n)
{
  // todo: use some tables here to help
  for (mpz_class i=2;;++i) {
    mpz_class ii = i*i;

    if ( ii >= n )
      break;

    if ( (n % ii) == 0 )
      return false;
  }

  return true;
}

int main()
{
  mpz_class a(0), b(1);
  size_t n=1;

  for(;;) {
    // todo: use mod here for faster calc
    mpz_class tmp(b);
    b += a;
    a = tmp;

    if ( square_free(b) ) {
      ++n;
      cout << n << "th " << "square-free fibo: " << b << endl;

      if ( n == 100000000 )
        break;
    }
  }
}
