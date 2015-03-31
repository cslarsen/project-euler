#include <stdio.h>
#include <math.h>

typedef long long int aint;

aint tri(aint n)
{
	return n*(n+1)>>1;
}

aint pent(aint n)
{
	return n*(3*n-1)>>1;
}

aint hex(aint n)
{
	return n*((n<<1)-1);
}

struct pair {
	aint a, b;
};

pair solve_quad(aint a, aint b, aint c)
{
	pair x;
	aint sq = (aint)sqrt(b*b - ((a*c)<<2) );
	x.a = (-b + sq) / (a<<1);
	x.b = (-b - sq) / (a<<1);
	return x;
}

aint inv_pent(aint n)
{
	pair r = solve_quad(3, -1, -2 * n);
	if ( r.a>=0 && pent(r.a) == n ) return r.a;
	if ( r.b>=0 && pent(r.b) == n ) return r.b;
	return 0;
}

aint inv_hex(aint n)
{
	pair r = solve_quad(2, -1, -n);
	if ( r.a>=0 && hex(r.a) == n ) return r.a;
	if ( r.b>=0 && hex(r.b) == n ) return r.b;
	return 0;
}

int main()
{
	int count = 0;
	aint ft, p, h;

	printf("go\n");

	for ( aint t=1; t>=0; t+=2 ) {

		ft = tri(t);

		if ( (p = inv_pent(ft)) == 0 )
			continue;

		h = 0;
		// we can skip this, since every hexagonal
		// number is also a triangle number
		/*
		if ( (h = inv_hex(ft)) == 0 )
			continue;
		*/

		printf("T%Ld = P%Ld = %Ld (%d)\n", t, p, ft, ++count);

		if ( count >= 4 ) break;
	}
}
