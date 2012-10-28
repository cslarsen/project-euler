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

int digits(aint n)
{
	char s[16];
	sprintf(s, "%lu", n);
	return strlen(s);
}

aint cycle(aint n, aint cycles=1)
{
	char s[16];
	sprintf(s, "%lu", n);
	size_t len = strlen(s)-1;

	while ( cycles ) {
		char a = s[0];
		memmove(s, s+1, len);
		s[len] = a;
		--cycles;
	}

	return atol(s);
}

#define isprime(n) (sieve[n])

int main()
{
	build_sieve();

	for ( aint count=1, n=3; n<MAXSIEVE; n += 2 ) {

		if ( !isprime(n) ) continue;

		int circ_prime = 1;
	
		for ( int c=0, d=digits(n); c < d; ++c )
			if ( !isprime(cycle(n, c)) ) {
				circ_prime = 0;
				break;
			}

		if ( circ_prime )
			printf("%lu is circular prime, count = %lu\n", n, ++count);
	}
}
