#include <stdio.h>
#include <string.h>
#include <bitset>

using namespace std;

typedef unsigned int aint;

const size_t MAXSIEVE = 1000;
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


int pandigital(aint a, aint b, aint c)
{
	char p[16];
	sprintf(p, "%lu%lu%lu", a, b, c);

	if ( strlen(p) != 9 ) return 0;

	int n[10];
	memset(n, 0, sizeof(n));

	for ( char *s = p; *s; ++s ) {
		if ( *s=='0' || n[*s-'0'] ) return 0;
		n[*s - '0'] = 1;
	}

	for ( int a=1; a<10; ++a )
		if ( !n[a] ) return 0;

	return 1;
}

int main()
{
	aint sum = 0;
	std::bitset<99999> hit = 0;

	for ( aint a=1; a<99; ++a )
	for ( aint b=1; b<9999; ++b ) {
		aint c = a*b;
		if ( c > 99999 ) continue;
		if ( pandigital(a,b,c) ) {
			if ( !hit[c] ) {
				hit[c] = 1;
				sum += c;
				printf("%lu * %lu = %lu, sum = %lu\n", a,b,c,sum);
			}
		}
	}
}
