#include <stdio.h>

int sols(int p)
{
	int s=0;

	for ( int a=1, aa; a<p; ++a ) {
		aa = a*a;

		for ( int b=a, bb; b<p; ++b ) {
			bb = b*b;
			for ( int c=b; c<p; ++c )
				if ( a+b+c==p && c*c=aa+bb )
					++s;
		}
	}

	return s;
}

int main()
{
	printf("120=%d\n", sols(120));
	printf("12=%d\n", sols(12));
return 0;
	printf("go\n");
	int maxs=0, maxp=0, s;
	for ( int p=1; p<1000; ++p )
		if ( (s = sols(p)) > maxs ) {
			maxs = s;
			maxp = p;
		}

	printf("p=%d gives %d solutions\n", maxp, maxs);
}
