/*
 * projecteuler.net problem 19
 *
 * how many sundays fell on the first of the month during the
 * twentieth century (1 jan 1901 to 31 dec 2000) ?
 *
 */

#include <stdio.h>

int mdays[2][12] = {
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} /* leap year */
};

#define LEAP(y) y%4==0 && (y%400==0 || y%100!=0)

int main()
{
	int sum=0, dow=0, y, m, d;

	for ( y=1900; y <= 2000; ++y )
	for ( m=0; m < 12; ++m )
	for ( d=0; d < mdays[LEAP(y)][m]; ++d, dow = (dow+1)%7 ) {
			
		if ( y>1900 && d==0 && dow==6 )
			printf("%4d-%.2d-%.2d fell on a sunday (sum=%d)\n",
				y, m+1, d+1, ++sum);
	}
}
