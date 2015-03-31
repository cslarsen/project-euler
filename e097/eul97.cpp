#include <stdio.h>
#include <bits/types.h>

int main()
{
	__uint64_t n = 1;

	for ( int a=0; a<7830457; ++a ) {
		n <<= 1;
		n %= 10000000000ULL;
	}

	n *= 28433;
	n %= 10000000000ULL;
	++n;

	printf("%10.10Lu\n", n);
}

