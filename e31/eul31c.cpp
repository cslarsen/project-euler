#include <stdio.h>
#include <bitset>

// number of solutions of ax+by=c
int sols(int a, int b, int c)
{
	static int memo[200*2];

	if ( c<0 ) return 0;

	int s=0, abc=a*b*c;
	if ( memo[abc] ) return memo[abc];

	for ( int x=0; x <= c/a; ++x )
	for ( int y=0; y <= c/b; ++y )
		if ( x*a + y*b == c )
			++s;

	return memo[abc] = s;
}

int main()
{
	int s=0;

	for ( int n=0; n<=200; ++n )
		printf("n=%d s=%d\n", n, sols(1,2,n));
	/*
	for ( int h=0; h<=200/200; ++h )
	for ( int g=0; g<=200/100; ++g )
	for ( int f=0; f<=200/50; ++f )
	for ( int e=0; e<=200/20; ++e )
	for ( int d=0; d<=200/10; ++d )
	for ( int c=0; c<=200/5; ++c )
		s += sols(1, 2, 200 - 5*c - 10*d - 20*e - 50*f - 100*g - 200*h);
	*/

	printf("solutions=%d\n", s);
}
