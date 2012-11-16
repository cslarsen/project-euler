#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <inttypes.h>
#include <ctype.h>
#include <math.h>

using namespace std;

static const char* words[] = {
  #include "words.txt"
  ,NULL
};

typedef uint64_t Z;

vector<Z> squares;

// uh oh, seems we have to deduce this table!
int charval[] = {
  2, // a
  -1, // b (unknown)
  1, // c
  -1, // d
  6, // e
  -1, // f
  -1, // g
  -1, // h
  -1, // i
  -1, // j
  -1, // k
  -1, // l
  -1, // m
  -1, // n
  -1, // o
  -1, // p
  -1, // q
  9, // r
  -1, // s
  -1, // t
  -1, // u
  -1, // v
  -1, // w
  -1, // x
  -1, // y
  -1, // z
};


/*
static ostream& operator<<(ostream& o, const vector<Z>& v)
{
  for ( Z i=0; i<v.size(); ++i )
    o << v[i] << " ";
  return o;
}
*/

static vector<Z> freq(const char* s)
{
  char r[26] = {0};

  while ( *s )
    ++r[toupper(*s++) - 'A'];

  return vector<Z>(r, r+sizeof(r));
}

// anagrams
typedef map<vector<Z>, vector<const char*> > strmap;
strmap anags;

static bool square(const Z& n)
{
  const Z s = sqrt(n);
  return s*s == n;
}

static Z num(const char* s)
{
  Z n = 0;

  while ( *s ) {
    n *= 10;
    int v = charval[toupper(*s++) - 'A'];
    if ( v!=-1 )
    n += v;
  }

  return n;
}

static void test()
{
  assert(num("race") == 9216);
  assert(num("care") == 1296);
  assert(freq("race") == freq("cARe"));
  assert(freq("Care") == freq("RAcE"));
  assert(square(num("race")));
  assert(square(num("care")));
}

void show()
{
  for ( strmap::iterator i = anags.begin();
        i != anags.end(); ++i )
  {
    for ( Z j=0; j<(*i).second.size(); ++j )
      cout << (*i).second[j] << " ";
    cout << endl;
  }
}

static Z missing(const char* s)
{
  Z c=0;
  while ( *s ) {
    if ( charval[toupper(*s++) - 'A'] == -1 )
      ++c;
  }

  return c;
}

static Z nearest_square(const char* a)
{
  Z n = num(a);

  for ( Z i=0; i<squares.size(); ++i ) {
    if ( squares[i] < n )
      continue;
    return squares[i];
  }

  return 0;
}

static bool find(const char* a, const char* b)
{
  // nearest square
  Z na = nearest_square(a);
  Z nb = nearest_square(b);

  cout << "* " << a << "=" << num(a) << " ";
  cout << "nsquare=" << na << " diff=" << na-num(a) << endl;

  cout << "* " << b << "=" << num(b) << " ";
  cout << "nsquare=" << nb << " diff=" << nb-num(b) << endl;

  return nb-num(b) == na-num(a);
}

int main()
{
  for ( Z i=1; i<100; ++i )
    squares.push_back(i*i);

  test();

  // find anagrams
  for ( const char **s = words; *s; ++s )
      anags[freq(*s)].push_back(*s);

  // filter away words that do not have anagrams
  for ( strmap::iterator i = anags.begin();
        i != anags.end(); )
  {
    if ( (*i).second.size() <= 1 )
      anags.erase(i++);
    else
      ++i;
  }

  //show();

  /*
   * Ikke square: ACT og CAT
   * T kunne vaert 24 da 120+24=144, men stemmer ikke for
   * neste tall, 225 (=15) og 256 (=46)
   * cout << "act = " << num("act") << endl; = 210
   * cout << "cat = " << num("cat") << endl; = 120
   */
  for ( Z i=1; i<100; ++i )
    cout << i*i << " ";
  cout << endl;

  for ( strmap::iterator i = anags.begin(); i != anags.end(); ++i)
  {
    if ( missing((*i).second[0]) == 2 ) {
      bool ok = true;
      for ( Z j=1; j<(*i).second.size(); ++j ) {
        ok &= find((*i).second[j-1], (*i).second[j]);
      }

      if ( ok )
        cout << "MATCH!!!" << endl;
    }
  }

  cout << endl;
  show();

  // look for zero
  bool ch[30];
  for ( char c='A'; c<='Z'; ++c )
    ch[c-'A'] = true;

  for ( strmap::iterator i = anags.begin(); i != anags.end(); ++i)
  {
      for ( Z j=0; j<(*i).second.size(); ++j ) {
        ch[(*i).second[j][0] - 'A'] = false;
      }
  }

  for ( char c='A'; c<='Z'; ++c ) {
    if ( ch[c-'A'] == false )
      cout << c << ", ";
  }
  cout << endl;

  return 0;
}
