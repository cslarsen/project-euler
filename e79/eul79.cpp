#include <stdio.h>
#include <string.h>
#include <string>

//                                ans: 73162890
// sort|uniq -c|sort -r, then by hand: 7314562890
// remove unneeded:                    73162890

int num[] = {
319, 680, 180, 690, 129, 620, 762, 689, 762, 318,
368, 710, 720, 710, 629, 168, 160, 689, 716, 731,
736, 729, 316, 729, 729, 710, 769, 290, 719, 680, 
318, 389, 162, 289, 162, 718, 729, 319, 790, 680, 
890, 362, 319, 760, 316, 729, 380, 319, 728, 716
};

int code_fits_item(int code, int login_num)
{
	char scode[32], slogin[4];

	int login = num[login_num];
	sprintf(scode, "%6.6d", code);
	sprintf(slogin, "%d", login);

	int pos[3];
	pos[0] = pos[1] = pos[2] = -1;
	int len = strlen(scode);

	for ( int p=0; p<3; ++p )
	for ( int n=0; n<len; ++n )
		if ( scode[n] == slogin[p] ) {
			pos[p] = n;
			break;
		}

	if ( pos[0]==-1 || pos[1]==-1 || pos[2]==-1 )
		return 0;

	return pos[0]<pos[1] && pos[1]<pos[2];
}

int code_ok(int code)
{
	for ( int i=0; i<sizeof(num)/sizeof(int); ++i )
		if ( !code_fits_item(code, i) )
			return 0;
	return 1;
}

int main()
{
/*
	for ( int n=0; n<999999999; ++n )
		if ( code_ok(n) ) {
			printf("code: %d\n", n);
			return 0;
		}
*/
	using namespace std;
	string code;

	for ( int n=0; n < sizeof(num)/sizeof(int); ++n ) {
		char p[4];
		sprintf(p, "%3.3d", num[n]);
		for ( int i=2; i>=0; --i ) {
		
			size_t f = code.find(p[i]);	
			if ( f == string::npos ) {
				code.push_back(p[i]);
				continue;
			}
			

		}
	}
	printf("%s\n", code.c_str());
}
