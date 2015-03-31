#include <cstdio>
#include <bitset>

using namespace std;

template<size_t N>
void sieve_primes(bitset<N>& p)
{
  printf("Generating %lu primes\n", p.size());

  p.reset();
  p.flip();
  p[0] = p[1] = 0;

  for ( int n=2; n < N; ++n )
    if ( p[n] )
      for ( int m=n<<1; m < N; m += n )
        p[m] = 0;
}

template<size_t N>
int seqsum(int start, int end, bitset<N>& p)
{
  int sum = 0;
  for ( int n=start; n <= end; ++n )
    if ( p[n] ) sum += n;
  return sum;
}

template<size_t N>
int primes_in_seq(int start, int end, bitset<N>& p)
{
  int n = 0;

  while ( start <= end )
    n += p[start++];

  return n;
}

template<size_t N>
int findseq(int sum, bitset<N>& p)
{
  int start=2, end=2;
  int max=0;

  printf("."); //Searching for %d\n", sum);
  fflush(stdout);

  for ( start=2; start <= sum; ++start ) {
    if ( !p[start] )
      continue; // not prime

    for ( end=start; end <= sum; ++end ) {
      if ( !p[end] )
        continue; // not prime

      int trysum = seqsum(start,end,p);

      if ( trysum > sum )
        goto next_a;

      if ( trysum != sum )
        continue;

      if ( !p[trysum] )
        continue; // not a prime

      int primes = primes_in_seq(start, end, p);
      if ( primes > max )
        max = primes;
    }

    next_a:
      ;
  }

  return max;
}

int main()
{
  bitset<1000000> p;
  sieve_primes(p);

  // todo: lookup "maximum contiguous subsequence" in algo book
  int maxN = 0;
  for ( int n=(1000000-1); n>2; --n ) {
    if ( !p[n] )
      continue;

    int numP = findseq(n, p);
    if ( numP > maxN ) {
      maxN = numP;
      printf("\n%d is the sum of %d primes\n", n, maxN);
    }
  }
}
