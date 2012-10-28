/*
 * ProjectEuler.net problem 145
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <cassert>
#include <inttypes.h>

using namespace std;

typedef uint32_t Z;

static inline Z reverse(Z n)
{
  register Z r = 0;

  while ( n ) {
    r *= 10;
    r += n % 10;
    n /= 10;
  }

  return r;
}

static inline bool zerotrail(const Z& n)
{
  return (n % 10) == 0;
}

static inline bool odd(const Z& n)
{
  return (n & 1) == 1;
}

static bool allodd(Z n)
{
  while ( n ) {
    if ( !odd(n % 10) )
      return false;
    n /= 10;
  }

  return true;
}

static bool reversible(const Z& n)
{
  return !zerotrail(n) && allodd(n + reverse(n));
}

static Z count(const Z& limit, const Z& notify = 10000000)
{
  register Z count = 0;

  for ( Z n=10; n<limit; ++n ) {
    if ( reversible(n) )
      ++count;

    if ( (n % notify)  == 0 )
      cout << "Remaining: " << (limit-n) << endl;
  }

  return count;
}

void test()
{
  assert(reverse(0) == 0);
  assert(reverse(1) == 1);
  assert(reverse(9) == 9);
  assert(reverse(10) == 1);
  assert(reverse(12) == 21);
  assert(reverse(123) == 321);
  assert(reverse(321) == 123);
  assert(reverse(21) == 12);

  assert(zerotrail(10));
  assert(zerotrail(0));
  assert(!zerotrail(12));
  assert(!zerotrail(101));
  assert(zerotrail(14000));
  assert(!zerotrail(14001));
  assert(zerotrail(14030));
  assert(!zerotrail(14031));
  assert(!zerotrail(14431));
  assert(!zerotrail(14401));
  assert(zerotrail(14440));

  assert(odd(1));
  assert(!odd(2));
  assert(odd(11));
  assert(!odd(12));
  assert(!odd(0));

  assert(!reversible(0));
  assert(!reversible(123));
  assert(reversible(36));
  assert(reversible(63));
  assert(reversible(409));
  assert(reversible(904));

  assert(count(1000) == 120);
}

int main()
{
  test();
  
  const Z stop = 1000000000UL;

  cout << "There are " << count(stop)
       << " reversibles below " << stop << endl;
}
