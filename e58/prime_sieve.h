/*
 * A simple sieve of Eratosthenes using bitsets, written by Christian Stigen Larsen
 * You are free to use this code for anything (i.e., public domain).
 *
 * This sieve allocates the bitset on the heap, so you can calculate a lot
 * of prime numbers.
 */

#ifndef INC_PRIMES_H
#define INC_PRIMES_H

#include <bitset>

template<const size_t PRIMES>
class prime_sieve
{
public:
  std::bitset<PRIMES> *p;
  size_t primes;

  prime_sieve()
  {
    p = new std::bitset<PRIMES>();
    rebuild();
  }

  void rebuild()
  {
    p->reset();
    p->flip();

    (*p)[0] = (*p)[1] = primes = 0;

    for ( register size_t n=2; n < PRIMES; ++n )
      if ( (*p)[n] ) {
        ++primes;
        for ( register size_t m=n<<1; m < PRIMES; m += n )
          (*p)[m] = 0;
      }
  }

  inline bool isprime(int64_t n) const
  {
    return (*p)[n];
  }

  inline size_t size() const
  {
    return primes;
  }
};

#endif
