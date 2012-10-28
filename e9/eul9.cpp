#include <stdio.h>

typedef long int aint;

int main()
{
	aint a,b,c;
	for ( c=1; c<1000; ++c )
	for ( b=1; b<c; ++b )
	for ( a=1; a<b; ++a ) {
		if ( a*a + b*b == c*c && a + b + c == 1000 ) {
			printf("%d^2 + %d^2 = %d^2, abc=%d\n",
				a, b, c, a*b*c);
			return 0;
		}
	}

	printf("no match\n");
}

