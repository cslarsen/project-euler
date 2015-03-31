#include <iostream>
#include <bitset>

typedef unsigned long long int aint;

int main()
{
	aint maxdivs=0;
	register aint c=1, n=0;

	for (;;) {
		n += c++;

		register aint divs=2;
		for ( aint d=2; d<n; ++d ) {
			if ( n % d == 0 )
				++divs;
		}

		if ( divs > maxdivs ) {
			maxdivs = divs;
			std::cout << n << " has " << divs << " divisors " << std::endl;
		}
		
		if ( divs > 500 )
			break;
	}
}

