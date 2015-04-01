#!/usr/bin/env python

"""
ProjectEuler.net problem 76
By Christian Stigen Larsen, 2012

WHAT

Find the number of ways a number can be written as the sum of at least two
positive integers.

BACKGROUND

Any number n can be written as 1+...+1 with n-1 plus signs.  This gives
2^(n-1) non-unique combinations.  One of the solution will be simply 0+n, so
that the number of ways to write n as the sum of at least two positive
integers would be 2^(n-1) - 1.

However, we are interested in unique combinations so that 1+2 and 2+1 are
considered equal.

This is called a partition, see

https://secure.wikimedia.org/wikipedia/en/wiki/Partition_(number_theory)

NUMBERS

The first numbers are

1 0
2 1
3 2
4 4
5 6
6 10
7 14
8 21
9 29
10 41
11 55
12 76
13 100
...

which can be written as the sequence 

0, 1, 2, 4, 6, 10, 14, 21, 29, 41, 55, 76, 100, ...

For instance, the number 5 can be written as the sum of positive integers in
exactly 6 ways.

The sequence above can be found in the sequence http://oeis.org/A000065
(warning, that link contains the answer we seek!)
"""

memo = {} # memoization
def p(k, n):
  if k > n: return 0
  if k == n: return 1

  # memoization
  if (k,n) in memo: return memo[(k,n)]
  memo[(k,n)] = p(k+1, n) + p(k, n-k)
  return memo[(k,n)]

def P(n):
  r = 1
  for k in xrange(1, 1 + (n >> 1)):
    r += p(k, n - k)
  return r

def count(n):
  """Return number of (unique) ways to write n as the sum of at least two
  positive integers.
  """
  return P(n)-1

def main(stop=20, start=1):
  for n in xrange(start, 1+stop):
    print n, "->", count(n)
  n = 100
  print n, "->", count(n)

if __name__ == "__main__":
  main()
