#include <stdio.h>
#include <bitset>

std::bitset<10> digits_in(int a)
{
	std::bitset<10> r;

	while ( a ) {
		r[a % 10] = 1;
		a /= 10;
	}

	return r;
}

int main()
{
	for ( int n=1; n>0; ++n ) {
		int f = 2;

		while ( digits_in(n) == digits_in(n*f) && f<=6 )
			++f;

		if ( f == 7 ) {
			printf("%d\n", n);
			break;
		}
	}
}
