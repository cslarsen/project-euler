/*
 * ProjectEuler.net problem 64
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <vector>
#include <set>
#include <math.h>

using namespace std;

typedef int32_t Z;
typedef vector<Z> Zs;

struct triplet {
  Z a, b, c;

  triplet(Z a_, Z b_, Z c_):
    a(a_), b(b_), c(c_)
  {
  }

  bool operator<(const triplet& t) const
  {
    if ( a<t.a ) return true;
    if ( b<t.b ) return true;
    if ( c<t.c ) return true;
    return false;
  }

  friend ostream& operator<<(ostream& s, const triplet& t)
  {
    return s << "{" << t.a << ", " << t.b << ", " << t.c << "}";
  }
};

ostream& operator<<(ostream& o, const set<triplet>& v)
{
  o << "[";

  for ( set<triplet>::const_iterator i = v.begin();
        i != v.end(); )
  {
    o << *i;
    if ( ++i != v.end() )
      o << ", ";
  }

  return o << "]";
}

const Z MAX = 100000;

static bool has(const set<triplet>& s, const triplet& t)
{
  return s.find(t) != s.end();
}

/*
 * See
 * http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Continued_fraction_expansion
 */
static Z period(const Z& S)
{
  Zs a;
  Z d, m, aN, a0 = sqrt(S);

  // not irrational?
  if ( a0*a0 == S )
    return 0;

  set<triplet> seen;

  m = 0;
  d = 1;
  aN = a0;
  a.push_back(aN);
  seen.insert(triplet(m, d, a0));

  Z n=0;
  for ( ; ; ++n ) {
    m = d*a[n] - m;

    if ( d == 0 ) break;
    d = (S - m*m)/d;

    if ( d == 0 ) break;
    aN = (a0+m)/d;

    if ( has(seen, triplet(m, d, aN)) )
      break;

    if ( S == 8 ) {
      cout << "for 8 got " << aN << " and triplet " << triplet(m,d,aN) << endl;
      cout << "set: " << seen << endl;
    }
    
    seen.insert(triplet(m, d, aN));
    a.push_back(aN);
  }

  return n;
}

static bool odd(const Z& n)
{
  return (n & 1) == 1;
}

int main()
{
  Z count = 0;
  for ( Z n=2; n<=13; ++n ) {
    Z p = period(n);
    cout << "n=" << n << " has period " << p << endl;
    if ( odd(p) )
      ++count;
  }

  cout << count << endl;
}
