#include <iostream>

typedef unsigned long long int aint;

int main()
{
	aint maxdivs=0;
	register aint c=1, n=0;

	for (;;) {
		n += c++;

		register aint divs=2, d=2;

		while ( d < n )
			if ( n % d++ == 0 ) ++divs;

		if ( divs > maxdivs ) {
			maxdivs = divs;
			std::cout << n << " has " << divs << " divisors " << std::endl;
		}
		
		if ( divs > 500 )
			break;
	}
}

