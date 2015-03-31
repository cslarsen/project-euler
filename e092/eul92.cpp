#include <stdio.h>
#include <map>
#include <vector>
#include <gmpxx.h>

using namespace std;

typedef mpz_class bint;

typedef map<bint, bool> bool_map;

bool_map chain1, chain89; // true if chain terminates

static inline mpz_class reverse(bint n)
{
	bint r = 0;

	do {
		r *= 10;
		bint m = n % 10;
		r += m;
		n /= 10;
	} while ( n > 0 );

	return r;
}

static string& trimz(string& s)
{
	while ( s[0]=='0' )
		s.erase(0,1);
	return s;
}

static inline mpz_class sort_num(const bint& n)
{
	string s = n.get_str();
	std::sort(s.begin(), s.end());
	return mpz_class(trimz(s));
}

// e.g. 83 = 8^2 + 3^3 = 64 + 9 = 73
static inline bint sum_of_squares(bint n)
{
	bint r = 0;

	do {
		bint m = n % 10;
		r += m*m;
		n /= 10;
	} while ( n > 0 );

	return r;
}

static void add_to_chain(bool_map& chain, vector<bint> numbers)
{
	while ( !numbers.empty() ) {
		chain[numbers.back()] = true;
		numbers.pop_back();
	}
}

static bool is_chain89(bint n)
{
	vector<bint> l;

	for(;;) {
		n = sort_num(n);

		if ( chain1[n] ) {
			add_to_chain(chain1, l);
			return false;
		}
	
		if ( chain89[n] ) {
			add_to_chain(chain89, l);
			return true;
		}

		l.push_back(n);
		n = sum_of_squares(n);
	}
}

int main()
{
	/*
	printf("44=%s\n", reverse(sum_of_squares(44)).get_str().c_str());
	printf("32=%s\n", reverse(sum_of_squares(32)).get_str().c_str());
	return 0;

	printf("4312=%s\n", sort_num(4312).get_str().c_str());
	printf("2002=%s\n", sort_num(2002).get_str().c_str());
	return 0;
	*/

	chain1[1] = true;
	chain89[89] = true;

	bint count=0;
	const bint max("10000000");

	for ( bint n=2; n<max; ++n )
		if ( is_chain89(n) ) {
			++count;
			printf("%s -> 89, count=%s\n",
				n.get_str().c_str(),
				count.get_str().c_str());
		}

	printf("count=%s\n", count.get_str().c_str());
}

