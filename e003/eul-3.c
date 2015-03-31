#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
	int64_t number = 317584931803;
	int64_t divisor = 2;

	while (number > 1) {
		if (0 == (number % divisor)) {
			number /= divisor;
			divisor--;
		}
		divisor++;
	}

	printf("%d\n", divisor);
  return 0;
}
