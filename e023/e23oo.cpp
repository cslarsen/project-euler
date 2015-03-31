#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int sum_divs[32768];
char summable[32768];
int abundants[32768];
int main(int argc, char *argv[]) {
  const int limit = (argc != 2) ? 12 : atoi(argv[1]);
  const int halflimit = limit / 2;
  // Step one: compute sum of divisors, minus one
  for (int i = 2; i <= halflimit; ++i) {
    for (int j = i + i; j <= limit; j += i) {
      sum_divs[j] += i;
    }
  }
  // Step two: compute a list of all abundant numbers
  int *afiller = &abundants[0];
  for (int n = 2; n <= limit; ++n) {
    if (sum_divs[n] + 1 > n) {
      *afiller++ = n;
    }
  }
  // Step 3: compute the summable numbers
  for (int *a = &abundants[0]; ; ++a) {
    int ab1 = *a;
    if (ab1 > halflimit) break;
    for (int *b = a; ; ++b) {
      int sum = ab1 + *b;
      if (sum > limit) break;
      summable[sum] = true;
    }
  }
  int sum = 0;
  for (int i = 1; i <= limit; ++i) {
    if (!summable[i]) {
      // printf("%d is not summable\n", i);
      sum += i;
    }
  }
  printf("Sum of unsummables is %d\n", sum);
}
