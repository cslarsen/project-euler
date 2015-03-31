#ifndef INC_PRIMES_H
#define INC_PRIMES_H

#include <vector>
#include <algorithm>
#include <bitset>

template<size_t PRIMES>
class prime_sieve
{
public:
  std::bitset<PRIMES> p;
  std::vector<int> v;

  prime_sieve()
  {
    rebuild();
  }

  void rebuild()
  {
    p.reset();
    p.flip();

    p[0] = p[1] = 1;

    for ( size_t n=2; n < PRIMES; ++n )
      if ( p[n] ) {
        v.push_back(n);

        for ( size_t m=n<<1; m < PRIMES; m += n )
          p[m] = 0;
      }
  }

  inline bool isprime(int n) const
  {
    return p[n];
  }

  inline size_t size() const
  {
    return v.size();
  }

  inline std::vector<int>::const_iterator first() const
  {
    return v.begin();
  }
 
  inline std::vector<int>::const_iterator last() const
  {
    return v.end();
  }

  inline std::vector<int>::const_iterator find(int n) const
  {
    return std::equal_range(v.begin(), v.end(), n).second;
  }
};

#endif
