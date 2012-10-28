#include <stdio.h>
#include "prime_sieve.h"

int main()
{
  const int64_t MAX = 1000000000;

  printf("Calculating all prime numbers up to %Lu\n", MAX);
  prime_sieve<MAX> s;
  s.rebuild();
  printf("Sieve contains %lu primes\n", s.size());

  // coordinates, number and radius
  int64_t x=0, y=0, n=0, r=0;

  // direction and its increment
  int64_t dir = 0;
  int64_t dx[] = {1,0,-1,0,1};
  int64_t dy[] = {0,-1,0,1,0};

  int64_t diagonal_number=1;
  int64_t diagonal_prime=0;

  for ( int64_t n=2; n<10 || (float)diagonal_prime/diagonal_number >= 0.1f; ++n ) {
    if ( n >= MAX ) {
      printf("We blew up the sieve for n=%Ld!\n", n);
      break;
    }

    x += dx[dir];
    y += dy[dir];

    bool corner = abs(x) == abs(y);
    bool spiral = x>r && y==r;

    if ( corner || spiral ) dir = (dir+1) % 5;
    if ( spiral ) ++r;
    if ( corner ) ++diagonal_number;
    if ( corner && s.isprime(n) ) ++diagonal_prime;

  }

  printf("Number spiral side length: %Ld\n", 1+r*2);
  printf("%Ld of %Ld diagonal numbers are prime, or %.2f%%\n",
    diagonal_prime, diagonal_number,
    100.0f*(float)diagonal_prime/diagonal_number);
}
