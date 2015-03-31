/*
 * projecteuler.net problem 24
 *
 */

#include <stdio.h>
#include <vector>

using namespace std;

size_t fac(int n)
{
	return n>1 ? n*fac(n-1) : 1;
}

template<class X>
vector<X> permut(vector<X> n, size_t pos /* starts from zero */)
{
	vector<X> r;
	size_t p;

	while ( !n.empty() ) {
		p = pos / fac(n.size() - 1);
		pos -= p * fac(n.size() - 1);

		r.push_back(n[p]);
		n.erase(n.begin() + p);
	}

	return r;
}

int main()
{
	vector<int> n;

	for ( int i=0; i<10; ++i ) // add 0..9
		n.push_back(i);

	vector<int> p = permut(n, 1000000 - 1);

	for ( int n=0; n < p.size(); ++n )
		printf("%d", p[n]);

	printf("\n");
}
