#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
ProjectEuler.net Problem 78
Solved by Christian Stigen Larsen

This is the same as the number of partitions, which we have already solved.

http://oeis.org/A000041
"""

import math, sys
from memoize import *

sys.setrecursionlimit(1000000)

@memoize
def p(k, n):
  if k > n: return 0
  if k == n: return 1
  return p(k+1,n) + p(k,n-k)

@memoize
def P(n):
  r = 1
  for k in xrange(1, 1 + (n >> 1)):
    r += p(k, n - k)
  return r

@memoize
def sigma(n):
  "Sum of divisors of n; naive implementation"
  r=0
  for i in range(1,1+n):
    if (n%i)==0: r+= i
  return r

@memoize
def a(n):
  """
  Same as P(n) for http://oeis.org/A000041 using the formula:
  a(n) = (1/n) * Sum_{k=0, 1, ..., n-1} sigma(n-k)*a(k), where sigma(k) is the
  sum of divisors of k (A000203).
  """
  if n==0: return 1
  r = 0
  for k in xrange(0,n):
    r += sigma(n-k)*a(k)
  if r>0: r /= n
  return r


if __name__ == "__main__":
  try:
    DIV=10**6
    for n in xrange(2,DIV):
      if (n % 100)==0:
        print n,
        sys.stdout.flush()
      r=0
      for k in xrange(0,n):
        r += sigma(n-k)*a(k)
        r %= DIV
      if r==0:
        print "P(%d) is divisible by %d" % (n, DIV/10)
        break
  except KeyboardInterrupt, e:
    pass
