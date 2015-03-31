/*
 * projecteuler.net problem 21
 * find sum of all amicable pairs below 10000
 *
 */

#include <stdio.h>

typedef unsigned long int aint;

// return sum of divisors of n
int d(int n)
{
	aint sum=0;

	for ( int a=1; a<n; ++a )
		if ( n % a == 0 )
			sum += a;

	return sum;
}

int main()
{
	const aint MAX = 10000;
	aint sum=0;

	for ( int a=1; a<MAX; ++a ) {

		aint da = d(a);
		aint dda = d(da);

		if ( dda == a && a!=da ) {
			sum += da+dda;
			printf("d(%lu) == d(%lu), sum = %lu\n",
				dda, da, sum);
		}
	}

	printf("sum of (unique) amicable pairs is %lu/2 = %lu\n", sum, sum>>1);
}
