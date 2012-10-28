#include <stdio.h>

static const int digit[] = {
	/* (zero), one, two, three, four, ... nineteen */
	0, 3, 3, 5, 4, 4, 3, 5, 5, 4, 3, 6, 6, 8, 8, 7, 7, 9, 8, 8
};

static const int ten[] = {
	/* 0, 0, twenty, thirty, forty, ... ninety */
	0, 0, 6, 6, 5, 5, 5, 7, 6, 6
};

static const int hundred = 7;
static const int _and = 3;
static const int onethousand = 11;

int num(int n)
{
	if ( n < 20 )    return digit[n];
	if ( n < 100 )   return ten[n/10] + num(n % 10);
	if ( n < 1000 )  return digit[n/100] + hundred + (n%100!=0 ? _and : 0) + num(n % 100);
	if ( n == 1000 ) return onethousand;
	
}

int main()
{
	int sum = 0;

	for ( int n = 1; n <= 1000; ++n )
		sum += num(n);

	printf("%d\n", sum);
}
