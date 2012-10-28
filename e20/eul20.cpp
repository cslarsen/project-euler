#include <stdio.h>

int main()
{
	long n=0; char c;
	while ( (c = getchar()) != EOF )
		if ( c>='0' && c<='9' )
			n += c - '0';
	printf("%ld\n", n);
}
