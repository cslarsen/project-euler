#include <stdio.h>
#include <gmpxx.h>

typedef mpz_class xint;

#define str(n) n.get_str().c_str()

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
	while ( n > 0 ) n/=10, ++d;
	return d;
}

int main()
{

	xint count = 0;

	for ( xint i=1; i<100; ++i )
	for ( xint j=1; j<100; ++j ) {
		xint x = powr(i, j);
		xint y = digits(x);
		if ( y == j ) {
			printf("%s^%s = %s (%s digits)\n",
				str(i), str(j), str(x), str(y));
			++count;
		}
	}
	printf("count=%s\n", str(count));

}

