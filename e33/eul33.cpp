#include <stdio.h>
#include <string.h>
#include <vector>

int main()
{
	std::vector nums, denums;

	for ( int a=1; a<10; ++a )
	for ( int b=1; b<10; ++b )
	for ( int c=1; c<10; ++c )
	for ( int d=1; d<10; ++d )
	{
		int n=a*10+b, de=c*10+d;
		if ( n==0 || de==0 || n==de ) continue;

		float v = (float)n/(float)de;
		if ( v>=1.0f ) continue;

		float vv;

		if ( b==c && d>0.0f ) {
			vv = (float)a/(float)d;
			if ( vv==v ) {
				printf("%d/%d == %d/%d == %f\n",n,de,a,d,v);
				nums.push_back(n);
				denums.push_back(de);
			}
		}

		if ( b==d && c>0.0f ) {
			vv = (float)a/(float)c;
			if ( vv==v ) printf("%d/%d == %d/%d == %f\n",n,de,a,c,v);
		}

		if ( a==d && c>0.0f ) {
			vv = (float)b/(float)c;
			if ( vv==v ) printf("%d/%d == %d/%d == %f\n",n,de,b,c,v);
		}

		if ( a==c && d>0.0f ) {
			vv = (float)b/(float)d;
			if ( vv==v ) printf("%d/%d == %d/%d == %f\n",n,de,b,d,v);
		}
	}

}

