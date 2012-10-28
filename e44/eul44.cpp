// projecteuler.net problem 44

#include <stdio.h>

typedef unsigned int uint;

#define MAX 5000
#define MAXPENT MAX*(3*MAX-1)/2

uint P[MAX];
bool ISPENT[MAXPENT << 1];

int main()
{
	for ( uint *p = P, n=1; p<&P[MAX-1]; ++n, ++p )
		ISPENT[*p = n * ((n<<1) + n - 1) >> 1] = 1;

	for ( uint *p1 = P; p1<&P[MAX-1]; ++p1 )
	for ( uint *p2 = P; p2<p1; ++p2 ) {

		if ( ISPENT[*p1 + *p2] && ISPENT[*p1 - *p2] ) {
			printf("P(%d) +/- P(%d) are pentagonal, difference = %d\n",
				p1-P+1, p2-P+1, *p1 - *p2);
			return 0;
		}
	}
}
