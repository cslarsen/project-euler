#include <iostream>
using namespace std;
const unsigned int N = 12000;
unsigned int x = 0;

static void
fun(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
// given a/b and c/d, count mediant (a+c)/(b+d) and expand each side, if appropriate
{
  if ((b + d) <= N)
    {
      x++;
      fun(a, b, (a + c), (b + d));
      fun((a + c), (b + d), c, d);
    }
}

int
main()
{
  fun(1, 3, 1, 2);
  cout << x << endl;
  return 0;
}
