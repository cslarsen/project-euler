#include <stdio.h>
#include <stdlib.h>

const int height = 99;
static int t[(height+1)*(height+2)/2];

int sum(int x=0, int y=0, int sofar=0)
{
	int n = t[x + (y*(y+1) >> 1)];

	if ( y < height ) {
		int right = sum(x+1, y+1, sofar + n);
		int left  = sum(  x, y+1, sofar + n);
		return right>left ? right : left;
	}

	return sofar + n;
}

void read()
{
	int *pt = t, c;

	while ( (c = getchar()) != EOF ) {
		if ( c=='\r' )
			continue;

		if ( c>='0' && c<='9' ) {
			*pt *= 10;
			*pt += c-'0';
		} else
			++pt;
	}	
}

int main()
{
	read();
	printf("max sum %d\n", sum());
}

