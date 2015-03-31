#include <stdio.h>
#include <string.h>
#include <memory.h>

typedef unsigned int aint;

const char* tobits(aint n)
{
	static char s[64];
	*s = 0;
	char *p = s;

	for ( int b=32; b>=0; --b )
		*p++ = n & (1<<b) ? '1' : '0';
	
	return s;
}

const char* trimz(const char* s)
{
	while ( *s++ == '0' );
	return s-1;
}

int ispalin(const char* s)
{
	s = trimz(s);
	int c=0, n=strlen(s);

	for ( ;c < n/2; ++c )
		if ( s[c] != s[n-1-c] )
			return 0;

	return 1;
}


int main() {
	aint n, sum=0;
	char s[256];

	for ( n=1; n<1000000; n += 2 ) {
		itoa(
		sprintf(s, "%d", n);

		if ( ispalin(s) && ispalin(tobits(n)) ) {
			sum += n;
			printf("%lu = %s, sum=%lu\n", n, trimz(tobits(n)), sum);
		}
	}
}
