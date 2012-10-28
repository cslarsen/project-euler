#include <stdio.h>

/*
 * calculate (1 + 2 + 3 + 4 + ... + N)^2 - (1^2 + 2^2 + ... + N^2)
 *
 * since 
 *
 *   (a+b+c)^2 = a^2 + b^2 + c^2 + 2ab + 2ac + 2bc
 *
 * we have
 *
 * (a+b+c)^2 - (a^2 + b^2 + c^2) = 2ab + 2ac + 2bc
 *
 * and can therefore calc
 *
 * 2*(ab + ac + bc)
 *
 */
int main()
{
	int elems=100, diff=0;

	for ( int x=1; x<=elems; ++x )
	for ( int y=1; y<=elems; ++y ) {
		if ( x != y )
			diff += x*y;
	}

	printf("diff = %d\n", diff);
}
