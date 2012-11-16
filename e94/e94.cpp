/*
 * ProjectEuler.net problem 94
 * Solved by Christian Stigen Larsen
 *
 * Triangle, perimeter, area:
 *
 * 5 5 6 circ 16 area 12
 * 65 65 66 circ 196 area 1848
 * 901 901 902 circ 2704 area 351780
 * 12545 12545 12546 circ 37636 area 68149872
 * 174725 174725 174726 circ 524176 area 13219419708
 * 2433601 2433601 2433602 circ 7300804 area 2564481115560
 * 33895685 33895685 33895686 circ 101687056 area 497495864091732
 */

#include <iostream>
#include <inttypes.h>
#include <cassert>
#include <math.h>
#include <gmpxx.h>
#include <omp.h>

using namespace std;

typedef int32_t I;
typedef mpz_class Z;
typedef mpf_class F;

const bool PRINT = true;

static F area(const Z& a, const Z& b)
{
  // Heron's formula
  return 0.25*F(b)*sqrt((a+a-b)*(a+a+b));
}

static bool integer_area(const Z& a, const Z& b)
{
  // Using Heron's formula
  const F f = sqrt((a+a-b)*(a+a+b));
  const Z i = f;

  if ( i*i != (a+a-b)*(a+a+b) )
    return false;

  // must also be divisible by four
  //return (i % 4) == 0;
  return true;
}

static Z circ(const Z& a, const Z& b)
{
  const Z c = a+a+b;

  if ( c>1e9 || !integer_area(a,b) )
    return 0;

  if ( PRINT ) {
    #pragma omp critical
    {
      cout << omp_get_thread_num() << "/"
        << omp_get_num_threads() << " ";
      cout << a << " " << a << " " << b <<
        " circ " << c << " area " << Z(area(a,b)) << endl;
    }
  }

  return c;
}

int main(int argc, char **argv)
{
  cout << "Should be 12: " << area(5,6) << endl;
  assert(area(5,6) == 12);

  Z S=0;
  const I STOP = argc<1? 100 : atoi(argv[1]);

  cout << "STOP at " << STOP << endl;

  #pragma omp parallel for schedule(dynamic) num_threads(4)
  for ( I a=2; a<=STOP; ++a ) {
    //if ( a+a+a-1 > 1000000000 )
    //  break;

    Z c = circ(a,a-1);
    if ( c!=0 ) {
      #pragma omp critical
      S += c;
    }

    c = circ(a,a+1);
    if ( c!=0 ) {
      #pragma omp critical
      S += c;
    }

    if ( (a % 1000000) == 0 ) {
      F p = 100.0*F(a+1)/STOP;
      #pragma omp critical
      cout << p << "% " << S << endl;
    }
  }

  cout << endl;
  cout << "Sum of perimeters: " << S << endl;
}
