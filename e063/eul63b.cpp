#include <stdio.h>

typedef unsigned long long xint;
typedef double xfloat;

xint powr(xint b, xint ex)
{
	xint n = b;
        for ( ; ex>1; --ex )
		n *= b;
	return n;
}

xint digits(xint n)
{
	xint d=0;
	while ( n>0 ) n/=10, ++d;
	return d;
}

int main()
{
	xint count = 0;

	for ( xint base=1; ; ++base )
	for ( xint ex=9; ex>0; --ex ) {
		xint p = powr(base, ex);
		xint d = digits(p);

		if ( d == ex ) {
			++count;
			printf("%lu^%lu = %lu has %lu digits, count=%lu\n",
				base, ex, p, d, count);
		} else
			break; // next base
	}
	printf("count=%lu\n", count);
}

