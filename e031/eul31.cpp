#include <stdio.h>
#include <bitset>

int v[] = {200, 100, 50, 20, 10, 5, 2, 1};

// number of solutions of ax+by=c
int sols(int a, int b, int c)
{
	static int memo[200*200*200];

	if ( memo[a*b*c] )
		return memo[a*b*c];

	int s=0;

	for ( int x=0; x <= c/a; ++x )
	for ( int y=0; y <= c/b; ++y )
		if ( x*a + y*b == c )
			++s;

	memo[a*b*c] = s;
	return s;
}

int main()
{
	// number of solutions of a+2b+5c=200
	int s=0;

	for ( int c=0; c<=200/5; ++c )
		s += sols(1, 2, 200 - 5*c);

	printf("%d\n", s);
}
