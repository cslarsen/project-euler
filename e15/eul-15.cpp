#include <stdio.h>

int MAX = 1;

unsigned long int routes(int x, int y)
{
	return x==MAX && y==MAX ? 1 : /* one route */
	       (x<MAX ? routes(x+1, y) : 0)
	     + (y<MAX ? routes(x, y+1) : 0);
}

int main()
{
	for ( MAX=1; MAX<=20; ++MAX )
		printf("%dx%d grid has %lu routes\n", MAX, MAX, routes(0, 0));
}
