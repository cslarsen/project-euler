#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
ProjectEuler.net Problem 78
Solved by Christian Stigen Larsen

This is the same as the number of partitions, which we have already solved.

"""

import math, sys

sys.setrecursionlimit(1000000)

memo = {} # memoization
def p(k, n):
  if k > n:
    memo[(k,n)]=0
    return 0

  if k == n:
    memo[(k,n)]=1
    return 1

  # memoization
  if (k,n) in memo: return memo[(k,n)]
  memo[(k,n)] = p(k+1, n) + p(k, n-k)
  return memo[(k,n)]

def P(n):
  r = 1
  for k in xrange(1, 1 + (n >> 1)):
    r += p(k, n - k)
  return r

def pn(n):
  "Number of ways to divide n coins into piles"
  return P(n)
  if n<=1: return 1
  if n==2: return 2
  return 2**(n-1)

def pr(n):
  print "p(%d) = %d" % (n, pn(n))

#for i in xrange(1, 20):
#  print i, pn(i)
#sys.exit(0)

"""
Vi har P(n) = sum(p(k, n-k) for k=1 til ceil(n/2))
Eller P(n) = p(1,n-1) + p(2,n-2) + ... + p(1+n/2, n - (1+n/2))

Så, hintet er, er 2300 delelig med hundre?
Hva med 2377 + 8833 ? Ja, fordi 77+33=100, så når
man tar 2377+8833 så får man ???00 i slutten, altså delelig med 100!

Så for å se om et tall er delelig med 10^6, så ta og se om

p(a,b) mod 10^6 + p(c,d) mod 10^6 + ... = 0

"""
if __name__ == "__main__":
  try:
    DIV=1000000
    for n in xrange(2,DIV):
      r = 1
      print n,
      sys.stdout.flush()
      for k in xrange(1, 1+(n/2)):
        r += p(k, n-k)
        r %= DIV
      if r==0:
        print "P(%d) is divisible by %d" % (n, DIV)
        break
  except KeyboardInterrupt, e:
    pass
