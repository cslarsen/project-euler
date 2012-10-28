/*
 * ProjectEuler.net Problem 61
 * Solved by Christian Stigen Larsen
 *
 * So... this code is a total MESS.
 * But the way I solved it is very fast, taking 0.016 seconds
 * on my Core i7.
 *
 * So I won't bother fixing the code up. :-)
 */

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>
#include <inttypes.h>

using namespace std;

typedef int64_t Z;

template<typename X>
ostream& operator<<(ostream& s, const vector<X>& v)
{
  for ( typename vector<X>::const_iterator i = v.begin();
        i != v.end(); ++i )
  {
    s << *i;

    if ( (i+1) != v.end() )
      s << " ";
  }

  return s;
}

static Z last2(const Z& n)
{
  return ((n/10) % 10)*10 + (n % 10);
}

static Z first2(Z n)
{
  Z f, l;

  while ( n >= 10 ) {
    f = n % 10;
    l = (n/10) % 10;
    n /= 10;
  }

  return l*10+f;
}

void test()
{
  assert(first2(1234) == 12);
  assert(last2(1234) == 34);
  assert(first2(1001) == 10);
  assert(last2(1001) == 1);
  assert(first2(9030) == 90);
  assert(first2(9230) == 92);
  assert(last2(9230) == 30);
  assert(last2(9232) == 32);
  assert(last2(9202) == 2);
}

static Z tri(const Z& n)
{
  return n*(n+1)/2;
}

static Z sq(const Z& n)
{
  return n*n;
}

static Z penta(const Z& n)
{
  return n*(3*n-1)/2;
}

static Z hexa(const Z& n)
{
  return n*(2*n-1);
}

static Z hepta(const Z& n)
{
  return n*(5*n-3);
}

static Z octa(const Z& n)
{
  return n*(3*n-2);
}

static bool accepted(const vector<Z>& v)
{
  for ( size_t n=0; n<v.size(); ++n )
    if ( last2(v[n]) != first2(v[(n+1) % v.size()]) )
      return false;

  return true;
}

static Z find_first2(const Z& prefix, const vector<Z>& v)
{
  for ( size_t n=0; n < v.size(); ++n )
    if ( first2(v[n]) == prefix )
      return v[n];

  return -1;
}

static vector<Z> make_list(Z prefix, stack< vector<Z>* >& vv)
{
  vector<Z> found;

  Z next;
  do {
    next = find_first2(prefix, *vv.top());

    if ( next != -1 ) {
      found.push_back(next);
      prefix = last2(next);
    }

    vv.pop();
  } while ( !vv.empty() );

  return found;
}

static Z sum(const vector<Z>& v)
{
  Z s = 0;

  for ( size_t n=0; n < v.size(); ++n )
    s += v[n];

  return s;
}

int main()
{
  test();
  vector<Z> vt, vs, vp, vhx, vhp, voc;

  for ( Z n=45; n<=140; ++n ) vt.push_back(n*(n+1)/2);
  for ( Z n=32; n<=99; ++n ) vs.push_back(n*n);
  for ( Z n=26; n<=81; ++n ) vp.push_back(n*(3*n-1)/2);
  for ( Z n=23; n<=70; ++n ) vhx.push_back(n*(2*n-1));
  for ( Z n=15; n<=45; ++n ) vhp.push_back(n*(5*n-3)/2);
  for ( Z n=19; n<=58; ++n ) voc.push_back(n*(3*n-2));

  const vector<Z> *v = &vt;
  for ( size_t n=0; n < v->size(); ++n ) {
    Z prefix = last2(v->at(n));


    vector<vector<Z>* > select;
    select.push_back(&vt);
    select.push_back(&vs);
    select.push_back(&vp);
    select.push_back(&vhx);
    select.push_back(&vhp);
    select.push_back(&voc);

    size_t idx[] = {0,1,2,3,4,5};

    do {
      vector<Z> found;
      stack< vector<Z>* > vv;

      for ( size_t q=0; q<6; ++q )
        vv.push(select[idx[q]]);

      found = make_list(prefix, vv);

      if ( found.size() == 6 &&
           prefix == last2(*(found.end()-1)) )
      {
        cout << "Got something: "
          << found << endl;

        cout << "Their sum is: " << sum(found) << endl;
        exit(0);
      }
    } while ( next_permutation(idx, idx+6) );
  }

  cout << "No cigar" << endl;
}
