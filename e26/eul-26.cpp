#include <stdio.h>

int main()
{
	for ( long double n=1.0f; n<1000.0f; ++n ) {
		long double f = 1.0f/n;
		printf("1/%.0Lf = %.80Lf\n", n, f);
	}
}
