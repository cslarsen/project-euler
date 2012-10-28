#include <stdio.h>
#include <bitset>

using namespace std;

const int N=1000;
bitset<N*N> sieve;

void sieve_primes()
{
	sieve = 0;
	sieve.flip();

	for ( int n=2; n<sieve.size(); ++n ) {
		if ( !sieve[n] )
			continue;

		for ( int j=n*2; j<sieve.size(); j+=n )
			sieve[j] = 0;
	}
}

static inline
int f(int n, int a, int b)
{
	return n==0 ? b : n*n + a*n + b;
}

int main()
{
	sieve_primes();

	int max=0, fn;

	for ( int b=2; b<N; ++b )
	for ( int a=-N+1; sieve[b] && a<N; a+=2 ) {

		int n=0;
		while ( (fn = f(n,a,b)) > 0 && sieve[fn] )
			++n;

		if ( n > max ) {
			max = n;
			printf("a=%d, b=%d -> %d primes, a*b=%d\n",
				a, b, n, a*b);
		}
	}
}
