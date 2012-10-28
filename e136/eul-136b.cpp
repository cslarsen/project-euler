#include <stdio.h>
#include <math.h>

typedef long int num;

// return value of f(x,d) = x^2 - (x-d)^2 - (x-2d)^2 - n
inline num f(const num& x, const num& d, const num& n)
{
	return -(x*x) - (6*x*d) - (5*d*d) - n;
}

// return x for when f'(x,d) == 0
inline num fmax(const num& d)
{
	return -3*d;
}

// return right root for f(x,d,n)
inline double rroot(const num& d, const num& n)
{
	return (-6*d + sqrt(16*d*d - 20*n))/-2;
}

// return left root for f(x,d,n)
inline double lroot(const num& d, const num& n)
{
	return (-6*d - sqrt(16*d*d - 20*n))/-2;
}


int main()
{
	num xsols, tsols=0;
	printf("go\n");

	for ( num n = 1; n < 100; ++n ) {

		for ( num d = 5*(n>>2); d < 1000000; ++d ) {

			bool equals = false;

			if ( f(fmax(d), d, n) == 0 )
				equals = true;
			else {
				double l = lroot(d,n);
				double r = rroot(d,n);

				// rroot and lroot must be a positive integer
				num li = (num)l, ri = (num)r;
				if ( l - li != 0.0f )
					break;
				if ( r - ri != 0.0f )
					break;

				if ( f(ri, d, n) == 0 )
					equals = true;
				else if ( f(li, d, n) == 0 )
					equals = true;
			}

			if ( equals ) {
				++tsols;
				printf("%ld total, n=%ld\n", tsols, n);
			}
		}
	}
}
