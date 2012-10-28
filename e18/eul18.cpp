#include <stdio.h>

static int n[] = {
75,
95, 64,
17, 47, 82,
18, 35, 87, 10,
20,  4, 82, 47, 65,
19,  1, 23, 75,  3, 34,
88,  2, 77, 73,  7, 63, 67,
99, 65,  4, 28,  6, 16, 70, 92,
41, 41, 26, 56, 83, 40, 80, 70, 33,
41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
63, 66,  4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
 4, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23
};

static int t[] = {
3,
7, 5,
2, 4, 6,
8, 5, 9, 3
};

/*
 *pos 0, 1, 3, 6
 *y   0, 1  2  3
 *
 */

int h = 3;

int stack[15];
int s=0;

int sum(int x=0, int y=0, int sofar=0)
{
	int n = t[x+y*(y+1)/2];
	sofar += n;
	stack[s++] = n;

	if ( y<h ) {
		int right = sum(x+1, y+1, sofar);
		int left  = sum(  x, y+1, sofar);
		--s;
		return sofar + (right>left ? right : left);
	}

	for ( int a=0; a<s; ++a )
		printf("%d ", stack[a]);

	printf("= %d\n", sofar);
	--s;
	return 0;
}

int main()
{
	printf("max sum %d\n", sum());
}

