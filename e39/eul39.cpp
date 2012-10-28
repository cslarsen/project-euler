#include <stdio.h>

#define MAX 1000
#define MAXD2 500

int square[MAX];
int isquare[MAX*MAX];

// solutions for a+b+c=p, a^2+b^2=c^2
int sols(const int p)
{
	int s=0;

	for ( int a=1; a<MAXD2; ++a ) 
	for ( register int b=1; b<=a; ++b ) {
		int c = square[a] + square[b];
		if ( a + b + isquare[c] <= MAX )
//		if ( square[a] + square[b] == square[p-a-b] )
			++s;
	}

	return s;
}

int main()
{
	for ( int n=0; n<MAX; ++n ) {
		square[n] = n*n;
		isquare[n*n] = n;
	}

	int s, maxs=0;

	for ( int p=1; p<MAX; ++p )
		if ( (s = sols(p)) > maxs )
			printf("p=%d gives %d solutions\n", p, maxs = s);
}
