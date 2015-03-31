#include <vector>
#include <stdio.h>
#include <math.h>

typedef unsigned int digit;
typedef std::vector<digit> digitvec;
typedef std::vector<digit>::const_iterator digitcitr;

// find the 10001st prime, brute-force

int main()
{
	digitvec primes;
	primes.push_back(2);

	for ( digit n=3; primes.size() < 10001; n += 2 ) {

		for ( digitcitr p = primes.begin() + 1; p != primes.end(); ++p )
		{
			// check for divisibility
			if ( n % (*p) == 0 )
				goto next_prime;
		}

		primes.push_back(n);
		//printf("%d. prime is %d\n", primes.size(), primes.back());
next_prime:
		continue;
	}

	printf("%d. prime is %d\n", primes.size(), primes.back());
}

