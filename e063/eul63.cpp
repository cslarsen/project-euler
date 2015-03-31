#include <stdio.h>
#include <math.h>

typedef unsigned long long xint;
typedef long double xfloat;

static int digits(xint n)
{
	int r=0;
	while ( n!=0 ) ++r, n/=10;
	return r;
}

// returns true if a^x = n and a is integer and x = digits in n
static int nthpow_p(const xint& n)
{
	const int digits_n = digits(n);
	const xint base = exp(log(n)/digits_n);

	if ( pow(base, digits_n) == n ) {
		printf("%Lu = %Lu^%lu", n, base, digits_n);
		return 1;
	}

	return 0;
}

int main()
{
	printf("go\n");
	xint count = 0;
	for ( xint n=1; n<90000000; ++n ) {
		if ( nthpow_p(n) ) {
			printf(" count=%Lu\n", ++count);
		}
	}
	printf("count=%Lu\n", count);
}
