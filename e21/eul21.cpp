/*
 * projecteuler.net problem 21
 * find sum of all amicable pairs below 10000
 *
 */

#include <stdio.h>
#include <bitset>
#include <math.h>

typedef unsigned long int aint;

// return sum of divisors of n
int d(int n)
{
	aint sum=1;
	aint root = static_cast<aint>(sqrt(n));

	for ( int a=2; a<=root; ++a )
		if ( n % a == 0 )
			sum += a + static_cast<aint>(n/a);

	return sum;
}

int main()
{
	const aint MAX = 10000;
	std::bitset<2*MAX> ampair;
	aint sum=0;

	for ( int a=1; a<MAX; ++a ) {

		if ( ampair[a] )
			continue;

		aint da = d(a);

		if ( da == a || ampair[da] )
			continue;

		aint dda = d(da);

		if ( dda == a ) {
			ampair[a] = ampair[da] = 1;

			sum += da+dda;
			printf("d(%lu) == d(%lu), sum = %lu\n",
				dda, da, sum);
		}
	}
}
