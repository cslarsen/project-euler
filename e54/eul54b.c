#include <stdio.h>

enum suit_e { C = 'C', D = 'D', H = 'H', S = 'S' };

enum value_e {
	TWO=2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
	TEN='T', JACK='J', QUEEN='Q', KING='K', ACE='A'
};

typedef struct card {
	char value, suit;
} card; 

typedef card hand[6];

void parse(card* p, const char* s)
{
	while ( *s ) {
		*p++ = *(const card*)s;
		s += 3;
	}
}

void pr(card* p)
{
	for ( ; p->value > 0; ++p )
		printf("%c%c ", p->value, p->suit);
	printf("\n");
}

int main()
{
	hand h;
	char s[] = "2C 3C 4C 5D 8H 9C 8C 7C 6C 5C\r\n";
	s[16] = s[30] = '\0';
	parse(h, s);
	pr(h);
	parse(h, s+15);
	pr(h);
}

