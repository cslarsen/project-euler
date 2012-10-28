#include <stdio.h>
#include <math.h>

typedef long int aint;

int main()
{
	aint total = 0;
	aint maxn = 100;

	for ( aint n=1; n < maxn; ++n ) {

		aint d = static_cast<aint>(sqrt(n) / 2.0f);
		aint nsol = 0;
		
		for ( ; d < 1000000; ++d ) {
			aint x = static_cast<aint>(sqrt(n));

			aint sol = 0;
			aint soltype = 0;

			aint t = 3*d;
			double l = t + sqrt((d<<2)*d - n);
			double r = t - sqrt((d<<2)*d - n);

			if ( (d<<2)*d == n ) {
				soltype = 1;
				++sol;
			}

			if ( l>0.0f && l>2.0f*d && l - static_cast<aint>(l) == 0.0f ) {
				soltype = 2;	
				++sol;
			}

			if ( r>0.0f && r>2.0f*d && r - static_cast<aint>(r) == 0.0f ) {
				soltype = 3;
				++sol;
			}

			if ( sol == 1 ) {
				++total;
				++nsol;

				if ( nsol > 1 ) {
					--total;
					printf("%3d disregarded total = %d\n", n, total);
					break;
				}


				if ( soltype == 2 || soltype == 3 ) {
					double s = (r>0.0f && r>2.0f*d) ? r : l;
					aint a = (aint)s, b = (aint)s-d, c = (aint)s - d - d;
					printf("%3d = %3d^2 - %3d^2 - %3d^2   (d = %3d) root",
						n, a, b, c, d);
				} else if ( soltype == 1 ) {
					printf("%3d = %3d^2 - %3d^2 - %3d^2   (d = %3d) maxima",
						n, 3*d, 2*d, d, d);
				}

				printf(" total = %d\n", total);
			}
		}
	}

	printf("%d unique solutions for n less than %d\n", total, maxn);
}

