#include <stdio.h>
#include <math.h>

typedef long int uint;

int main()
{
	printf("euler-136\n");

	uint n, x, y, z, diff, max = 2000;
	uint total_sols = 0;

	for ( n=1; n < 100; ++n ) {

		uint solutions = 0;

		for ( diff = ((uint)sqrt(n))>>1; diff < 3*max; ++diff ) {
			for ( x = -2*diff; x < max; ++x ) {
				y = x + diff;
				z = y + diff;

				if ( y<0 || z<0 )
					continue;

				if ( (x*x)-(y*y)-(z*z) == n ) {
					++solutions;
					if ( solutions > 1 )
						goto next_n;
//					printf("%d = (%d)^2 - (%d)^2 - (%d)^2 (diff = %d)\n", 
//						n, x, y, z, diff);
				}
			}
		}

next_n:
		if ( solutions == 1 ) {
			++total_sols;
			printf("%d solutions for n = %d (%d in total)\n", solutions, n, total_sols);
		}
	}
}
