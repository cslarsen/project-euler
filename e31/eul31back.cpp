#include <stdio.h>
#include <bitset>

int v[] = {200, 100, 50, 20, 10, 5, 2, 1};

// number of solutions of ax+by=c
int sols(int a, int b, int c)
{
	static int memo[200*200*200];

	if ( memo[a*b*c] != 0 )
		return memo[a*b*c];

	int s=0;
	for ( int aa=0; aa <= c/a; ++aa )
	for ( int bb=0; bb <= c/b; ++bb )
		if ( a*aa + b*bb == c )
			++s;

	memo[a*b*c] = s;
	return s;
}

int main()
{
	int c = 200;
	for ( int a=1; a<=5; ++a ) {
		if ( !(a==1 || a==2 || a==5) )
			continue;
	for ( int b=2; b<=10; ++b ) {
		if ( !(b==1 || b==2 || b==5 || b==10) )
			continue;
		printf("sols(%d,%d,%d) = %d\n", a, b, c, sols(a, b, c));
	}
	}
}
