#include <cstdio>
#include <bitset>
#include <vector>

using namespace std;

template<size_t N>
void sieve_primes(bitset<N>& p)
{
  p.reset();
  p.flip();
  p[0] = p[1] = 0;

  for ( int n=2; n < N; ++n )
    if ( p[n] )
      for ( int m=n<<1; m < N; m += n )
        p[m] = 0;
}

template<size_t N>
void push_primes(bitset<N>& p, vector<int>& v)
{
  for ( int n=2; n < N; ++n )
    if ( p[n] ) v.push_back(n);
}

bitset<1000000> p;
vector<int> v;
typedef vector<int>::const_iterator cit;

inline int sum(cit& a, const cit& b)
{
  int s = 0;

  while ( a != b )
    s += *a++;

  return s;
}

inline int dist(const cit& a, const cit& b)
{
  return b>=a ? b - a : a - b;
}

int main()
{
  sieve_primes(p);
  push_primes(p, v);

  for ( cit a=v.begin(); a != v.end(); ++a ) {
    for ( cit b=a+1; b != v.end(); ++b ) {
        printf("%d %d\n", *a, *b);
    }
return 0;
  }
}
