#include <stdio.h>

typedef unsigned int ulint;

int main()
{
	for ( ulint c=1, max = 0; c<1000000; ++c ) {

		ulint terms = 1, n = c;
	
		while ( n != 1 ) {
			n = n & 01 ? (n<<1) + n +1 : n>>1;
			++terms;
		}

		if ( terms > max ) {
			max = terms;
			printf("%lu terms for %lu\n", terms, c);
		}
	}
}
