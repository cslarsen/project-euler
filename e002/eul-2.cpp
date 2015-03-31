#include <stdio.h>

typedef unsigned long int ulint;

int main()
{
	ulint a = 1, b = 2;
	ulint next, sum = 2;

	printf("%d %d (added) ", a, b);

	do {
		next = a + b;

		if ( ~next & 01 && next < 1000000 ) {
			printf("(added) ");
			sum += next;
		}

		a = b;
		b = next;

		printf("%u ", next);

	} while ( next < 1000000 );

	printf("\nsum = %u\n", sum);	
}
