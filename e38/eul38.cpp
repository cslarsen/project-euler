// projecteuler.net problem 38

#include <stdio.h>
#include <gmpxx.h>

#define str(n) n.get_str().c_str()
#define touint(n) n.get_ui()
typedef mpz_class xint;

int pandigits(xint n)
{
	unsigned int bitset = 0;

	do {
		xint a = n % 10;
		bitset |= 1 << touint(a);
		n /= 10;
	} while ( n > 0 );

	return bitset;
}

static int pandigital0to9_p(xint n)
{
	return pandigits(n) == 0x3FF;
}

static int pandigital1to9_p(xint n)
{
	return pandigits(n) == 0x3FE;
}

static int digits_in(xint n)
{
	int d = 0;
	do {
		++d;
		n /= 10;
	} while ( n > 0 );
	return d;
}

static xint power(xint base, xint ex)
{
	if ( ex==0 ) return 1;
	xint n = base;
	while ( --ex > 0 ) n *= base;
	return n;
}

xint reverse(xint n)
{
	xint r=0;
	while ( n > 0 ) {
		r *= 10;
		r += n % 10;
		n /= 10;
	}
	return r;
}

xint pandigit_mul_concat(xint n)
{
	xint i=1;
	xint p=0;

	while ( !pandigital1to9_p(p) && digits_in(p)<10 ) {
		xint next = n * i;
		if ( p>0 ) p *= power(10, digits_in(next));
		p += next;
		++i;
	}

	return p;
}

int main()
{
	xint max = 0;
	for ( xint n=1; ; ++n ) {
		xint p = pandigit_mul_concat(n);

		if ( !pandigital1to9_p(p) || digits_in(p) > 9 )
			continue;

		if ( digits_in(n) > 4 )
			break;

		if ( p > max ) {
			max = p;
			printf("-- %s for n=%s\n", str(max), str(n));
		}
	}
	printf("end\n");
}
