#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum rank {
	hicard, pair, two_pairs, three_kind, straight, flush, house, four_kind, sflush, rflush
};

enum suit {
	clubs = 'C', diamonds = 'D', hearts = 'H', spades = 'S'
};

struct card {
	enum suit suit;
	int value;
};

struct score {
	enum rank rank;
	struct card topcard;
};

typedef card hand[5];

int cmp_value(const void* l, const void* r)
{
	return ((card*)l)->value - ((card*)r)->value;
}

int cmp_suit(const void* l, const void* r)
{
	if ( ((card*)l)->value != ((card*)r)->value )
		return 0;

	return ((card*)l)->suit - ((card*)r)->suit;
}

void sort(hand h)
{
	qsort(h, 5, sizeof(card), cmp_value);
	qsort(h, 5, sizeof(card), cmp_suit);
}

int values_in_sequence(hand h, int start)
{
	int c=1, max=0;

	for ( int x=start; x<4; ++x ) {
		if ( h[x].value == h[x+1].value )
			++c;
		else
			return c;
	}
	return c;
}

int num_of_seqs(hand h, int length)
{
	int p = 0;
	for ( int n=0; n<5-length+1; ++n )
		if ( values_in_sequence(h, n) == length )
			++p;
	return p;
}

int num_pairs(hand h)
{
	return num_of_seqs(h, 2);
}

int three_of_kind(hand h)
{
	return num_of_seqs(h, 3);
}

int four_of_kind(hand h)
{
	return num_of_seqs(h, 4);
}

int ishouse(hand h)
{
	if ( num_pairs(h)==2 )
		if ( three_of_kind(h) )
			return 1;
	return 0;
}

int isflush(hand h)
{
	return h[0].suit == h[1].suit
	  && h[2].suit == h[3].suit
	  && h[1].suit == h[2].suit
	  && h[3].suit == h[4].suit;
}

int isstraight(hand h)
{
	return 4+h[0].value == h[4].value
 	    && 3+h[1].value == h[4].value
	    && 2+h[2].value == h[4].value
	    && 1+h[3].value == h[4].value;
}

int straight_flush(hand h)
{
	return isflush(h) && isstraight(h);

}

int royal_flush(hand h)
{
	return h[0].value==10 && straight_flush(h);
}

// return card for highest pair
card gtc_pairs(hand h)
{
	card c;
	c.value = 0;
	c.suit = (suit)0;

	for ( int n=1; n<5; ++n )
		if ( h[n-1].value == h[n].value )
			c = h[n].value > c.value ? h[n] : c;
	return c;
}

// return card for highest pair
card gtc_threes(hand h)
{
	card c;
	c.value = 0;
	c.suit = (suit)0;

	for ( int n=2; n<5; ++n )
		if ( h[n-2].value == h[n-1].value && h[n-1].value == h[n].value )
			c = h[n].value > c.value ? h[n] : c;
	return c;
}

card gtc_fours(hand h)
{
	if ( h[4].value == h[3].value )
		return h[4];
	return h[3];
}

score getscore(hand h)
{
	score s;
	s.rank = hicard;
	s.topcard = h[4];

	// order dependency:
	if ( num_pairs(h)==1 ) {
		s.rank = pair;
		s.topcard = gtc_pairs(h);
	}

	if ( num_pairs(h)==2 ) {
		s.rank = two_pairs;
		s.topcard = gtc_pairs(h);
	}

	if ( three_of_kind(h) ) {
		s.rank = three_kind;
		s.topcard = gtc_threes(h);
	}

	if ( isstraight(h) ) {
		s.rank = straight;
		s.topcard = h[4];
	}

	if ( isflush(h) ) {
		s.rank = flush;
		s.topcard = h[4];
	}

	if ( ishouse(h) ) {
		s.rank = house;
		s.topcard = gtc_pairs(h);
		if ( gtc_threes(h).value > s.topcard.value )
			s.topcard = gtc_threes(h);
	}

	if ( four_of_kind(h) ) {
		s.rank = four_kind;
		s.topcard = gtc_fours(h);
	}

	if ( straight_flush(h) ) {
		s.rank = sflush;
		s.topcard = h[4];
	}

	if ( royal_flush(h) ) {
		s.rank = rflush;
		s.topcard = h[4];
	}

	return s;
}

// format "5H 5C 6S 7S KD", return offset
int read(hand h, const char* s)
{
	int n=0;
	for ( int c=0; c<5 && n<strlen(s); ++n ) {
		switch ( s[n] ) {
		case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			h[c].value = s[n] - '0';
			break;
		case 'T': // 10
			h[c].value = 10;
			break;

		case 'J': h[c].value = 11; break;
		case 'Q': h[c].value = 12; break;
		case 'K': h[c].value = 13; break;
		case 'A': h[c].value = 14; break;
		
		case 'S': case 'D': case 'H': case 'C':
			h[c].suit  = (suit)s[n];
			++c;
			break;

		case ' ':
			break;
		
		case '\r': case'\n':
			sort(h);
			return n;
			break;
		default:
			  fprintf(stderr, "invalid card value\n");
			  exit(1);
			  break;
		}
	}

	sort(h);
	return n;
}

const char* suitstr(suit s)
{
	switch (s) {
	case clubs:    return "clubs";
	case diamonds: return "diamonds";
	case hearts:   return "hearts";
	case spades:   return "spades";
	default:
		return "unknown";
	}
}

const char* rankstr(rank r)
{
	switch ( r ) {
	case hicard: return "high card";
	case pair: return "1 pair";
	case two_pairs:  return "2 pairs";
	case three_kind: return "3 of a kind";
	case straight: return "straight";
	case flush: return "flush";
	case house: return "house";
	case four_kind: return "4 of a kind";
	case sflush: return "straight flush";
	case rflush: return "royal straight flush";
	default: return "??";
	}
}

void print(hand h)
{
	for ( int n=0; n<5; ++n )
		printf("%d%c%s", h[n].value, suitstr(h[n].suit)[0],
			n+1<5 ? ", " : "");

}

int p1_wins(hand p1, hand p2)
{
	score l = getscore(p1);
	score r = getscore(p2);

	if ( l.rank == r.rank ) {
	
		if ( l.topcard.value > r.topcard.value )
			return 1;

		return 0;
	}
	return l.rank > r.rank;
}

int main()
{
	char s[1024];
	int wins=0;

	FILE *f = fopen("poker.txt", "rb");
	if ( !f ) { perror("poker.txt"); return 1; }

	while ( fgets(s, 1023, f) != NULL ) {
		hand h1, h2;
		int n = read(h1, s);
		read(h2, s+n+1);

		if ( p1_wins(h1, h2) ) {
			printf("p1 wins ");
			++wins;
		} else
			printf("        ");

		printf("p1=(");
		print(h1);
		score s1 = getscore(h1);
		printf(") %s (%d) -- ", rankstr(s1.rank), s1.topcard.value);

		printf("p2=(");
		print(h2);
		score s2 = getscore(h2);
		printf(") %s (%d)\n", rankstr(s2.rank), s2.topcard.value);
	}
	printf("p1 wins: %d\n", wins);
}
