#include <stdio.h>
#include <gmpxx.h>

static inline const char* trimz(const char* s)
{
	while ( *s && *s=='0' ) ++s;
	return s;
}

static inline mpz_class reverse(const mpz_class& n)
{
	std::string s(n.get_str()), r(s);

	for ( int siz=s.size(), n=siz; n>0; --n )
		r[siz-n] = s[n-1];

	return mpz_class(trimz(r.c_str()));
}

static inline bool is_palin(const mpz_class& num)
{
	const char* s = trimz(num.get_str().c_str());
	int c=0, n=strlen(s), n2=n/2;

	for ( ; c < n2; ++c )
		if ( s[c] != s[n-1-c] ) return false;

	return true;
}

bool is_lychrel(const mpz_class& num)
{
	mpz_class i = num;

	for ( int n=0; n<50; ++n ) {
		i += reverse(i);
		if ( is_palin(i) ) return false;
	}

	return true;
}

int main()
{
	int count = 0;
	for ( mpz_class n=0; n<10000; n++ )
		if ( is_lychrel(n) )
			printf("%s is lychrel, count=%d\n", n.get_str().c_str(), ++count);
}
