#include <iostream>
#include <bitset>
#include <math.h>

typedef unsigned long long aint;

aint prim[1000000];

struct Exp {
        aint base;
        aint exp;
};

Exp fact[600];

void prime_sieve()
{
        const size_t SIZE = sizeof(prim)/sizeof(aint);

        std::bitset<SIZE> sieve;

        sieve.flip(); // assume all numbers prime
        sieve[0].flip(); // except 0
        sieve[1].flip(); // except 1

        for ( int n=2, pr=0; n < SIZE; ++n ) {

                if ( !sieve[n] )
                        continue;

                prim[pr++] = n;

                for ( int j=n<<1; j<SIZE; j+=n )
                        sieve[j] = 0;
        }
}

aint fac(aint n)
{
        if ( n <= 0 ) return 1;
        aint r=1;
        while ( n > 1 ) r *= n--;
        return r;
}

aint binom(aint n, aint k)
{
        return fac(n) / ( fac(k) * fac(n-k) );
}

int main()
{
        printf("calculating primes\n");
        prime_sieve();

        aint maxdivs=0;
        aint c=1, n=0;

        for (;;) {
                n += c++;

               // std::cout << n << " = ";
                aint divs=0;
                aint dp=0;

                for ( aint d=(aint)sqrt((double)n); d >= 0; --d ) {

                        if ( prim[d] == 0 )
                                break;

                        if ( n % prim[d] == 0 ) {
                                //std::cout << prim[d];

                                aint num = n, exp=1;
                                num /= prim[d];

                                while ( num % prim[d] == 0 ) {
                                        num /= prim[d];
                                        ++exp;
                                }
				
                                fact[dp].base = prim[d];
                                fact[dp].exp = exp;
                                ++dp;
                                //std::cout << "^" << exp << " ";
                        }
                }
                //std::cout << std::endl;

divs = 1;
for ( aint r=0; r<dp; ++r ) {
	divs *= (fact[r].exp + 1);
}
                // count how many ways we can combine factors

                if ( divs > maxdivs ) {
                        maxdivs = divs;
                        std::cout << n << " has " << divs << " divisors " << std::endl;
                }

                if ( divs > 500 )
                        break;
        }
}
