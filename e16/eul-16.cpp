#include <stdio.h>

// output of lisp (expt 2 1000)
char *s = "10715086071862673209484250490600018105614048117055336074437503883703510511249361224931983788156958581275946729175531468251871452856923140435984577574698574803934567774824230985421074605062371141877954182153046474983581941267398767559165543946077062914571196477686542167660429831652624386837205668069376";

int main() {
	long int sum = 0;
	while ( *s )
		sum += *s++ - '0';
	printf("sum = %ld\n", sum);
}
