/*
 * ProjectEuler.net problem 68
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <set>
#include <inttypes.h>

#define SIZE 3
typedef uint32_t I;

using namespace std;

static set<I> range(const I a, const I b)
{
  set<I> r;

  for ( I i=a; i<=b; ++i )
    r.insert(i);

  return r;
}

static I sum(const set<I>& s)
{
  I r = 0;

  for ( set<I>::const_iterator i = s.begin();
        i != s.end(); ++i )
  {
    r += *i;
  }

  return r;
}

int main()
{
  I inner[SIZE];
  I outer[SIZE];

  set<I> s = range(1, SIZE*2);

  I minsum = sum(range(1, SIZE));
  I maxsum = sum(range(SIZE+1, SIZE*2));
}
