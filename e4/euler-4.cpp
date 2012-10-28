#include <stdio.h>
#include <string.h>

int main() {
	int x,y,n,c,f,larg=0;
	char s[256];

	for ( y=999; y>0; --y )
	for ( x=999; x>0; --x ) {
		sprintf(s, "%d", x*y);

		for ( f=1, c=0, n=strlen(s); c<n/2; ++c ) {
			if ( s[c] != s[n-1-c] ) {
				f=0;
				break;
			}
		}

		if ( f==1 ) {
			if ( larg < (x*y) ) {
				larg = x*y;
				printf("%s = %d * %d\n", s, x, y);
			}
		}
	}

}
