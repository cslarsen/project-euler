#include <stdio.h>
#include <math.h>

const int power = 5;

size_t powsum(size_t a)
{
	size_t s=0, n,
	       d=(int)pow(10, (int)(log(a+0.01f)/log(10)));

	while ( d ) {
		n = a/d;
		a -= n*d;
		d /= 10;
		s += (size_t)pow(n, power);
	}

	return s;
}

int main()
{
	size_t sum = 0, max = (size_t)pow(10, power+1);

	for ( size_t n=2; n<max; ++n )
		if ( n == powsum(n) ) {
			sum += n;
			printf("%d, sum=%lu\n", n, sum);
		}
}
