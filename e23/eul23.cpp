/*
 * projecteuler.net problem 23
 *
 */

#include <stdio.h>
#include <math.h>
#include <vector>

#define MAX 28123

// return sum of divisors of n
int d(int n)
{
	int sum=1, root = (int)sqrt(n);

	for ( int a=2; a<=root; ++a )
		if ( n % a == 0 )
			sum += a + ((n/a)!=a ? n/a : 0);

	return sum;
}

std::vector<int>   abundant;
bool abundant_sum[1 + MAX*2];

int main()
{
	// find all abundant numbers
	for ( int n=1; n < MAX; ++n )
		if ( d(n) > n )
			abundant.push_back(n);

	// find sum of all pairs of abundant numbers
	for ( int l=1; l < abundant.size(); ++l )
	for ( int r=1; r < l; ++r )
		abundant_sum[abundant[l] + abundant[r]] = true;

	unsigned long sum = 0;

	for ( int n=1; n < MAX; ++n )
		if ( !abundant_sum[n] )
			sum += n;

	printf("sum: %d\n", sum);
}
