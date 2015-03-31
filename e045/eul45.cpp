#include <stdio.h>
#include <math.h>

typedef long int aint;

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
	aint sq = (aint)sqrt(b*b - 4*a*c);
	x.a = (-b + sq) / (a<<1);
	x.b = (-b - sq) / (a<<1);
	return x;
}

int main()
{
	int count = 0;

	for ( aint t=0; t>=0; ++t ) {
		aint ft = tri(t);

		aint p = 0;
		pair pr = solve_quad(3, -1, -2 * ft);
		if ( pr.a>=0 && pent(pr.a) == ft ) p = pr.a;
		if ( pr.b>=0 && pent(pr.b) == ft ) p = pr.b;
		if ( p == 0 ) continue;

		aint h = 0;
		pair hr = solve_quad(2, -1, -ft);
		if ( hr.a>=0 && hex(hr.a) == ft ) h = hr.a;
		if ( hr.b>=0 && hex(hr.b) == ft ) h = hr.b;
		if ( h == 0 ) continue;

		printf("T%d = P%d = H%d = %d\n", t, p, h, ft);

		if ( ++count >= 3 )
			break;
	}
}
