#include <stdio.h>

int even(int n)
{
	return n>>1;
}

int odd(int n)
{
	return 3*n + 1;
}

struct pair { int a, b; };

pair seq(int n, int term=1)
{
	printf("%d ", n);

	if ( n==1 ) {
		pair r = {1, term};
		return r;
	}

	return seq((~n&1 ? even : odd )(n), ++term);
}

int main()
{
	printf(" (%d terms)\n", seq(13).b);
}
