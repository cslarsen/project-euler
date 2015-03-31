/*
 * The binary gcd algorithm using iteration.
 * Should be fairly fast.
 *
 * Put in the public domain by the author:
 *
 * Christian Stigen Larsen
 * http://csl.sublevel3.org
 */
uint32_t binary_gcd(uint32_t u, uint32_t v)
{
  int shl = 0;

  while ( u && v && u!=v ) {
    bool eu = !(u & 1);
    bool ev = !(v & 1);

    if ( eu && ev ) {
      ++shl;
      u >>= 1;
      v >>= 1;
    }
    else if ( eu && !ev ) u >>= 1;
    else if ( !eu && ev ) v >>= 1;
    else if ( u>=v ) u = (u-v)>>1;
    else {
      int tmp = u;
      u = (v-u)>>1;
      v = tmp;
    }
  }

  return !u? v<<shl : u<<shl;
}
