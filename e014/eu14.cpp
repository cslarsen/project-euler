#include <stdio.h>

typedef unsigned int uint;

int main()
{
        for ( uint num=500001, max = 0; num<1000000; num += 2 ) {

                uint terms = 1, n = num;

                while ( n != 1 ) {
                        n = n & 01 ? (n<<1) + n + 1 : n>>1;
                        ++terms;
                }

                if ( terms > max ) {
                        max = terms;
                        printf("%lu terms for %lu\n", terms, num);
                }
        }
}
