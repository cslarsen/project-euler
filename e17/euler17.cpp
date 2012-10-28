#include <stdio.h>

static const char* Num[] = {
	"",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	"ten",
	"eleven",
	"twelve",
	"thirteen",
	"fourteen",
	"fifteen",
	"sixteen",
	"seventeen",
	"eighteen",
	"nineteen"
};

static const char* Tens[] = {
	"",
	"",
	"twenty",
	"thirty",
	"forty",
	"fifty",
	"sixty",
	"seventy",
	"eighty",
	"ninety"
};

void pr(int n)
{
	if ( n < 20 ) {
		printf("%s", Num[n]);
		return;
	}

	if ( n < 100 ) {
		printf("%s", Tens[n / 10]);
		pr(n - 10*(n/10));
		return;
	}

	if ( n < 1000 ) {
		printf("%s", Num[n/100]);
		printf("hundred");
		if ( n%100 != 0 )
			printf("and");
		pr(n - 100*(n/100));
		return;
	}

	if ( n == 1000 ) {
		printf("onethousand");
		return;
	}
	
}

int main() {
	for ( int n=1; n<=1000; ++n ) {
//		printf("%d ");
		pr(n);
//		printf("\n");
	}
}
