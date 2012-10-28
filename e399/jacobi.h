// taken from
// https://github.com/gadial/ECC/blob/af3cd07e2537c289e9d05d2a7b1a2fe1d051efe9/primes.cpp

template<typename INT>
INT jacobi_symbol(INT a, INT b)
{
  if (a % b == 0)
    return 0;

  if (a == 1 || b == 1)
    return 1;

  if (a < 0)
    // (-a/b)=(a/b)*(-1)^(b-1 / 4)
    return jacobi_symbol(-a,b)*((b % 4 == 1)?(1):(-1));

  if (a > b)
    // (a/b) = (a % b / b)
    return jacobi_symbol(a % b, b);

  INT count = 0;
  while (a % 2 == 0){
      a /= 2;
      count += 1;
  }

  // (2^k/b)=(2/b)^k=[(-1)^(b^2-1 / 8)]^k
  if (a == 1)
    if (count % 2 == 0)
      return 1;
    else
      return ((b % 8 == 1 || b % 8 == 7)?(1):(-1));

  // (a/b)=(b/a)*(-1)^((a-1/4)(b-1/4)) - quadratic reciprocity
  INT temp = ((a % 4 == 1 || b % 4 == 1)?(1):(-1));

  if (count % 2 == 1 && (b % 8 == 3 || b % 8 == 5))
    temp *= -1;

  return temp*jacobi_symbol(b % a, a);
}
