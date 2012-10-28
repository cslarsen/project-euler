#include <stdio.h>
#include <bitset>

// calc recurring cycles for 1/n
int cycle(int d)
{
	int n=1, count=0;
	std::bitset<10000> v;

	do {
		n *= 10;
		if ( v[n] ) return count;
		v[n] = 1;
		n = n % d;
		++count;
	} while ( n );
	return 0;
}


int main()
{
	int maxd = 0;
	for ( int n=2; n<=1000; ++n ) {
		int cyc = cycle(n);
		if ( cyc > maxd ) {
			maxd = n;
			printf("1/%d = %10.10f... has %d-digit recurring cycle\n",
				n, 1.0f/n, cyc);
		}
	}
}
