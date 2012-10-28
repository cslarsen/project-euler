/*
 * ProjectEuler.net problem 102
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <cassert>
#include <cmath>
#include <fstream>
#include <inttypes.h>

using namespace std;
typedef int32_t Z;
typedef double F;

struct P {
  F x, y;

  P(F X=0, F Y=0):
    x(X), y(Y)
  {
  }

  friend ostream& operator<<(ostream& o, const P& p)
  {
    return o << "(" << p.x << ", " << p.y << ")";
  }

  friend istream& operator>>(istream& i, P& p)
  {
    return i >> p.x >> p.y;
  }

  friend bool operator==(const P& l, const P& r)
  {
    return l.x==r.x && l.y==r.y;
  }
};

// see
// http://stackoverflow.com/questions/2049582/how-to-determine-a-point-in-a-triangle

static F sign(P p1, P p2, P p3)
{
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

static bool PointInTriangle(P pt, P v1, P v2, P v3)
{
  bool b1, b2, b3;

  b1 = sign(pt, v1, v2) < 0.0;
  b2 = sign(pt, v2, v3) < 0.0;
  b3 = sign(pt, v3, v1) < 0.0;

  return ((b1 == b2) && (b2 == b3));
}

static bool contains_origo(P v1, P v2, P v3)
{
  if ( v1==v2 && v2==v3 )
    return false; // not a triangle

  if ( v1==v2 || v1==v3 || v2==v3 )
    return false; // not a triangle

  return PointInTriangle(P(0,0), v1, v2, v3);
}

int main()
{
  assert(contains_origo(P(-340,495), P(-153,-910), P(835,-947)));
  assert(!contains_origo(P(-175,41), P(-421,-714), P(574,-645)));

  ifstream f;
  f.open("triangles.txt");

  Z count = 0;
  while ( !f.eof() ) {
    P x, y, z;
    f >> x >> y >> z;
   
    if ( contains_origo(x, y, z) ) {
      ++count;
      cout << "yes ";
    } else
      cout << "    ";

    cout << x << "," << y << "," << z << endl;
  }

  cout << count << endl;
}
