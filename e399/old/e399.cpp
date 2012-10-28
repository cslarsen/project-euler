#include <iostream>
#include <inttypes.h>

using namespace std;

#define ZEROES 1000000U;

void show(uint64_t n, uint64_t b)
{
  cout << "F_" << n << "=" << b << endl;
}

int main()
{
  uint64_t a=0, b=1;
  uint64_t n=0;

  show(n++, 0);
  show(n++, 1);

  for ( ; n<10; ++n ) {
    uint64_t tmp = b;
    b += a;
    b %= ZEROES;
    a = tmp;

    show(n, b);
  }
}
