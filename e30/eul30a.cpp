#include <stdio.h>
#include <math.h>

const int power = 5;
const size_t max = (size_t)pow(10, power+1);

size_t powsum(size_t n)
{
	size_t l=0;
	while ( n ) {
		l += (size_t)pow(n % 10, power);
		n /= 10;
	}
	return l;
}

int main()
{
	size_t sum = 0;

	for ( size_t n=2; n<max; ++n )
		if ( n == powsum(n) ) {
			sum += n;
			printf("%d, sum=%lu\n", n, sum);
		}
}
