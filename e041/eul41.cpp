#include <stdio.h>
#include <string.h>
#include <bitset>

using namespace std;

typedef unsigned int aint;

const size_t MAXSIEVE = 10000000U;
bitset<MAXSIEVE> sieve;

int pandigital(aint a)
{
	char p[32];
	sprintf(p, "%lu", a);

	int len=strlen(p);

	int n[10];
	memset(n, 0, sizeof(n));

	for ( char *s = p; *s; ++s ) {
		if ( *s=='0' || n[*s-'0'] ) return 0;
		n[*s - '0'] = 1;
	}

	for ( int a=1; a<=len; ++a )
		if ( !n[a] ) return 0;

	return 1;
}

void build_sieve()
{
	sieve = 0;
	sieve.flip();
	sieve[0] = sieve[1] = 0;

	for ( aint n=2; n<MAXSIEVE; ++n ) {
		if ( !sieve[n] )
			continue;

		if ( pandigital(n) )
			printf("prime %lu is pan-digital\n", n);

		for ( aint i=2*n; i<MAXSIEVE; i+=n )
			sieve[i] = 0;
	}
}



int main()
{
	build_sieve();
}
