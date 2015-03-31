/*
 * ProjectEuler.net Problem 51
 * Solved by Christian Stigen Larsen
 */

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "primes.h"
#include "digits.h"

using namespace std;

#define PRIMES 1000000

static int maxdigits = 0;
static prime_sieve<PRIMES> primes;

/*
 * Convert number to binary representation.
 */
static string binary(const uint32_t n, size_t len)
{
  string s;

  for ( int bit=1; bit<32; ++bit ) {
    if ( n & (1<<(bit-1)) )
      s = '1' + s;
    else
      s = '0' + s;
  }

  return s.substr(s.length()-len);
}

/*
 * Create all possible masks, e.g.:
 * n=13 -> '1*', '*3', '**'
 */
static vector<string> masks(const unsigned int n)
{
  stringstream ss;
  ss << n;
  string s = ss.str();

  vector<string> v;
  int maxbits = digits(n);

  for ( int pat=1; pat < (1<<maxbits); ++pat ) {
    string m = s;
    string b = binary(pat, maxbits);

    // create mask, e.g. 13 -> '*3' and then '1*', etc.
    for ( size_t i=0; i<b.length(); ++i ) {
      if ( b[i] == '1' )
        m[i] = '*';
    }

    v.push_back(m);
  }

  // remove last one, which contains all stars
  v.pop_back();
  return v;
}

template<class X>
ostream& operator<<(ostream& s, const vector<X>& v)
{
  for ( typename vector<X>::const_iterator i = v.begin();
        i != v.end(); ++i )
  {
    s << *i << " ";
  }

  return s;
}

/*
 * Replace all sfind in s with srepl.
 */
string replace(string s, string sfind, string srepl)
{
  for ( size_t p=0; (p = s.find(sfind, p)) != string::npos; ) {
    s.replace(p, sfind.length(), srepl);
    p += srepl.length();
  }

  return s;
}

static size_t maxn = 0;

static vector<int64_t> replace_numbers(const unsigned int n)
{
  const unsigned int theprime = n;
  vector<string> m = masks(n);

  for ( vector<string>::iterator i = m.begin();
        i != m.end(); ++i )
  {
    vector<int64_t> ret;

    for ( char n='0'; n<='9'; ++n ) {
      char ns[2] = {n, '\0'};
      string s = replace(*i, "*", ns);

      // do not replace zero in first positions
      if ( s[0] == '0' )
        continue;

      int64_t num = atoi(s.c_str());

      if ( primes.isprime(num) )
        ret.push_back(num);
    }

    static bool shown = false;
    if ( *i == "56**3" && shown == false ) {
      shown = true;
      cout << *i << " yields " << ret.size() << " primes: "
        << ret << endl;
    }

    if ( ret.size() > maxn ) {
      maxn = ret.size();
      cout << *i << " yields " << ret.size() << " primes: "
        << ret << endl;
    }

    if ( ret.size() == 8 ) {
      cout << endl;
      cout << "The prime number " << theprime << " with pattern "
        << *i << " yields " << endl<< endl  << ret.size() << " primes: "
        << ret << endl;

      cout << "The smallest prime in this family is "
        << *min_element(ret.begin(), ret.end()) << endl;
      _exit(0);
    }
  }

  vector<int64_t> r;
  return r;
}

int main()
{
  maxdigits = digits(primes.at(primes.size()-1));
  cout << "Longest prime has " << maxdigits << " digits: "
    << primes.at(primes.size()-1) << endl;

  for ( size_t n=0; n<primes.size(); ++n ) {
    int64_t prime = primes.at(n);
    replace_numbers(prime);
  }

//  cout << replace_numbers(13) << endl;
}
