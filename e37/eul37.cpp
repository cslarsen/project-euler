// Prime number sieve, public domain
// (C) Christian Stigen Larsen, 2007

#include <stdio.h>
#include <bitset>

using namespace std;
typedef int aint;

const size_t MAXSIEVE = 1000000;
bitset<MAXSIEVE> sieve;

void build_sieve()
{
	sieve = 0;
	sieve.flip();
	sieve[0] = sieve[1] = 0;

	for ( aint n=2; n<MAXSIEVE; ++n ) {
		if ( !sieve[n] )
			continue;
		for ( aint i=2*n; i<MAXSIEVE; i+=n )
			sieve[i] = 0;
	}
}

#define isprime(n) (sieve[n])

int truncprime(aint n)
{
	char s[16];
	sprintf(s, "%lu", n);
	size_t l = strlen(s);

	char *p = s;
	for ( int n=0; n<l; ++n ) {
		if ( !isprime(atol(p+n)) )
			return 0;
	}

	for ( int n=l-1; n>0; --n ) {
		s[n] = 0;
		if ( !isprime(atol(s)) )
			return 0;
	}

	return 1;
}

int main()
{
	build_sieve();

	for ( aint sum=0, n=11; n<MAXSIEVE; n += 2 ) {

		if ( !isprime(n) ) continue;

		if ( truncprime(n) ) {
			sum += n;
			printf("%lu is trunc-prime, sum = %lu\n", n, sum);
		}
	}
}
