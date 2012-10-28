#include <stdio.h>
#include <string.h>

int main()
{
	for ( float a=0.0f; a<10.0f; ++a )
	for ( float b=0.0f; b<10.0f; ++b )
	for ( float c=0.0f; c<10.0f; ++c )
	for ( float d=1.0f; d<10.0f; ++d )
	{
		float n=(a*10.0f)+b, de=(c*10.0f)+d;
		if ( n==0.0f || de==0.0f ) continue;

		float v = n/de;
		if ( v>=1.0f ) continue;

		if ( b==c && a/d==v ) printf("%.0f/%.0f == %.0f/%.0f == %.2f (1)\n",n,de,a,d,v);
		if ( b==d && a/c==v ) printf("%.0f/%.0f == %.0f/%.0f == %.2f (2)\n",n,de,a,c,v);
		if ( a==c && b/d==v ) printf("%.0f/%.0f == %.0f/%.0f == %.2f (3)\n",n,de,b,d,v);
		if ( a==d && b/c==v ) printf("%.0f/%.0f == %.0f/%.0f == %.2f (4)\n",n,de,b,c,v);
	}

}

