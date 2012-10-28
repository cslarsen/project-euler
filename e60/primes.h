/*
 * A simple sieve of Eratosthenes using bitsets, written by Christian Stigen Larsen
 * You are free to use this code for anything (i.e., public domain).
 */

#ifndef INC_PRIMES_H
#define INC_PRIMES_H

#include <vector>
#include <algorithm>
#include <bitset>
#include <iostream>

template<typename INT, size_t PRIMES>
class prime_sieve
{
public:
  std::bitset<PRIMES> p;
  std::vector<INT> v;

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

  inline bool isprime(INT n) const
  {
    if ( n > PRIMES ) {
      std::cout << "isprime(" << n << ") is bigger than " << PRIMES << std::endl;
      exit(0);
    }

    return p[n];
  }

  inline size_t size() const
  {
    return v.size();
  }

  inline typename std::vector<INT>::const_iterator first() const
  {
    return v.begin();
  }
 
  inline typename std::vector<INT>::const_iterator last() const
  {
    return v.end();
  }

  inline typename std::vector<INT>::const_iterator find(INT n) const
  {
    return std::equal_range(v.begin(), v.end(), n).second;
  }

  inline INT operator[](const size_t& i) const
  {
    if ( i > size() ) {
      std::cout << "Op[" << i << "] is bigger than " << size() << std::endl;
      exit(0);
    }
    return v[i];
  }

  inline INT at(const size_t& i) const
  {
    if ( i > size() ) {
      std::cout << "at(" << i << ") is bigger than " << size() << std::endl;
      exit(0);
    }

    return v.at(i);
  }
};

#endif
