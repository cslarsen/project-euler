#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
projecteuler.net problem 78

p(5) = 7
"""

import math, sys

sys.setrecursionlimit(1000000)

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

n = 0
#n = 2554
#n = 2961
try:
  r = 9
  while r % 1000000 != 0:
    r = pn(n)
    for m in [6,5,4,3]:
      if r % (10**m) == 0:
        print n, r, "10^%d" % m
        break
    #while (pn(n) % 1000000) != 0:
    n += 1
  print "p(%d) = %d" % (n, pn(n))
except Exception, e:
  print "error at n =", n, pn(n-1)
  #print e
except KeyboardInterrupt, f:
  print ""
  print "interrupt at n =", n, pn(n)

#pr(0)
#pr(1)
#pr(2)
#pr(3)
#pr(4)
#pr(5)
