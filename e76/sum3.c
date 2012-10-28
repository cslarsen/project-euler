#include <stdio.h>
#include <stdlib.h>

static inline int sum(const int* __restrict v, const int N)
{
  register int n, s=0;

  for ( n=0; n<N; ++n )
    s += (n+1)*v[n];

  return s;
}

// new version
/*
static inline int next(
  int* __restrict v,
  const int* __restrict max,
  const int N)
{
  register int n, carry = 1;

  ///
   // Tactic: To mitigate sum(),
   // calculate next iteration that
   // equals sum.
   //
   // To do this, start with v[0]=max[0],
   // which is first solution.
   //
   // Next, as long as v[n] is > 0, subtract
   // max[n+1] from v[n] and add 1 to v[n+1].
   //
   // So, when we have this [1, 1, 0], we need
   // next to sutract 1 from v[0] and 1 from v[1]
   // and have 3 that we now can put into v[2],
   // giving [0, 0, 1].  So we need to keep an
   // index on the current slot we want to fill,
   // and update accordingly.]
   ///
  for ( n=0; n<N; ++n ) {
    if ( v[n] > 0 ) {
    }

    v[n] += carry;
    if ( v[n] > max[n] ) {
      v[n] = 0;
      carry = 1;
    } else
      carry = 0;
  }

  return carry;
}
*/

static inline int next(
  int* __restrict v,
  const int* __restrict max,
  const int N)
{
  register int n, carry = 1;

  for ( n=0; n<N; ++n ) {
    v[n] += carry;
    if ( v[n] > max[n] ) {
      v[n] = 0;
      carry = 1;
    } else
      carry = 0;
  }

  return carry;
}

static void print(const int* __restrict v, const int N)
{
  register int n, m, p=0;

  for ( n=0; n<N; ++n )
    for ( m=0; m<v[n]; ++m ) {
      printf("%s%d", p? "+" : "", (n+1));
      p=1;
    }

  printf("\n");
}

static int count(const int n)
{
  int v[100] = {0};
  int m[100] = {0};

  register int i, c=0;

  for ( i=0; i<(n-1); ++i ) {
    v[i] = 0;
    m[i] = (n+1)/(i+1);
  }

  v[0] = n;
int last=0;
  do {
    if ( sum(v, n-1) == n ) {
      //print(v, n);
      ++c;
//      printf("last=%d\n", last);
      last=0;
    }
    ++last;
  } while ( !next(v, m, n-1) );

  return c;
}

int main()
{
  int n;
  for ( n=1; n<20; ++n )
    printf("%d -> %d\n", n, count(n));

//  count(10);
}
