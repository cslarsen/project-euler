"""
G.f.: 1+sum(n>=1, x^n/prod(k>=n ,1-x^k))
http://oeis.org/A000041
"""

import sys
from memoize import *

def p(k,n):
  #print "p(k=%d,n=%d)" % (k,n)
  if k>n:
    #print "0"
    return 0
  if k==n:
    #print "1"
    return 1
  r = p(k+1,n) + p(k,n-k)
  return r

def fastp(k,n):
  if k>n: return 0
  if k==n: return 1
  r=0
  return r + p(k,n-k)

def fastP(n):
  r=1
  for k in xrange(1,1+(n/2)):
    r += fastp(k,n-k)
  return r

def P(n):
  #print "P(%d)" % n
  r=1
  for k in xrange(1,1+(n/2)):
    r += p(k,n-k)
    #print ""
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
  "a(n) = (1/n) * Sum_{k=0, 1, ..., n-1} sigma(n-k)*a(k)"
  if n==0: return 1
  r = 0
  for k in xrange(0,n):
    r += sigma(n-k)*a(k)
  r /= n
  return r

def div(mod):
  n=1
  while True:
    q = a(n)
    if (q % mod)==0:
      #print n,q
      print "n",n,"is divisible by",mod
      break
    n += 1
    if (n%1000)==0:
      print n,
      sys.stdout.flush()

if __name__ == "__main__":
  for k in range(1,8):
    div(10**k)
