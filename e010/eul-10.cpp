#include <vector>
#include <stdio.h>
#include <math.h>

typedef unsigned long int digit;
typedef std::vector<digit> digitvec;
typedef std::vector<digit>::const_iterator digitcitr;

// find the 10001st prime, brute-force

int main()
{
	digitvec primes;
	primes.push_back(2);
	printf("%d. prime is %d\n", primes.size(), primes.back());

	digit sum = 2;
	for ( digit n=3; n < 1000000; n += 2 ) {

		for ( digitcitr p = primes.begin() + 1; p != primes.end(); ++p )
		{
			// check for divisibility
			if ( n % (*p) == 0 )
				goto next_prime;
		}

		primes.push_back(n);
		sum += n;
		printf("%d. prime is %d (sum = %lu)\n", primes.size(), primes.back(), sum);
next_prime:
		continue;
	}

	printf("sum: %lu\n", sum);
}

