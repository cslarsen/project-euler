#include <stdio.h>

typedef unsigned long int ulint;

ulint even(ulint n)
{
	return n>>1;
}

ulint odd(ulint n)
{
	return 3*n + 1;
}

ulint seq(ulint n, ulint term=1)
{
	return n==1 ? term : seq((~n&1 ? even : odd )(n), ++term);
}

int main()
{
	ulint max = 0, terms, num;

	for ( ulint n=1; n<1000000; ++n ) {
		if ( (terms = seq(n)) > max ) {
			num = n;
			max = terms;
			printf("%lu terms for %lu\n", terms, n);
		}
	}
}
