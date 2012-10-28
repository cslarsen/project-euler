#include <stdio.h>

int main()
{
	for ( int n=1; n<181; ++n ) {
		printf("%d = ", n);

		int divs=0;
		for ( int d=1; d<=n; ++d )
			if ( n % d == 0 ) {
				++divs;
				printf("%d ", d);
			}

		printf(" (%d divisors)\n", divs);
	}
}
