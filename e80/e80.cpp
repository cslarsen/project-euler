/*
 * ProjectEuler.net Problem 80
 * Solved by CHristian Stigen Larsen
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <inttypes.h>

using namespace std;

typedef uint32_t Z;
typedef vector<Z> Zs;

/*
 * Return number of digits in `n`.
 */
template<typename X>
X digits(X n, const X& base = 10)
{
  if ( n <= 9 )
    return 1;

  X r = 0;

  while ( n != 0 ) {
    ++r;
    n /= base;
  }

  return r;
}

/*
 * Return vector of digits in `n`.
 */
template<typename X>
vector<X> digitsv(X n, const X& base = 10)
{
  vector<X> r;

  if ( n <= 9 ) {
    r.push_back(n);
    return r;
  }

  while ( n != 0 ) {
    r.push_back(n % base);
    n /= base;
  }

  return r;
}

template<typename X>
X ipow(X base, X expo)
{
  assert(expo >= 0);

  if ( expo == 0 )
    return 1;

  X r = 1;

  while ( expo-- )
    r *= base;

  return r;
}

template<typename X>
std::ostream& operator<<(std::ostream& o, const vector<X>& v)
{
  for ( typename vector<X>::const_iterator i = v.begin();
        i != v.end(); ++i )
  {
    o << *i << ((i+1) != v.end()? ", " : "");
  }

  return o;
}

static void sqroot(Z n)
{
  Zs result;
  Zs d = digitsv(n);

  if ( d.size() <= 1 )
    d.insert(d.begin(), 0);

  Z msb1 = d[0];
  Z msb2 = d[1];
  Z msb = msb1 + msb2;

  Z rem = 0;

  Z c = rem*100 + msb;

  Z p = 0;

  Z y, x;

  // find x so that x(20*p+x) <= c
  Z smallest = 0;
  for ( x=0; x*(20*p+x) <= c; ++x )
    smallest = x;
  if ( x*(20*p+x) == c )
    smallest = x;
  x = smallest;

  result.push_back(x);
  cout << x << endl;
  p = p*10 + x;

}

int main()
{
  assert(digits(0) == 1);
  assert(digits(1) == 1);
  assert(digits(9) == 1);
  assert(digits(11) == 2);
  assert(digits(31) == 2);
  assert(digits(99) == 2);
  assert(digits(123) == 3);
  assert(ipow(2, 8) == 256);
  sqroot(2);
}
