#!/usr/bin/env python
# -*- encoding: iso-8859-1 -*-

import math

nodes_memo = {}
nodes_memo[0] = 0
nodes_memo[1] = 1
def nodes(k):
  """Returns number of nods in Fibonacci tree of order k.

  This is the same as Fib(k+2) - 1
  """
  global nodes_memo

  if k in nodes_memo:
    return nodes_memo[k]

  if ((k-1) in nodes_memo) and ((k-2) in nodes_memo):
    r = nodes_memo[k-1] + nodes_memo[k-2]
    nodes_memo[k] = r
    return r

  a=1
  b=2
  for n in xrange(2, 1+k):
    nodes_memo[n] = b
    t = b
    b = a+b+1
    a = t

  return a

N_memo = {}
def N(k):
  """Memoized nimsum of Fibonacci tree of order k.

  Taking k=0, 1, ... forms the sequence A114375:
  http://oeis.org/A114375
  """
  global N_memo

  if k==0: return 0
  if k==1: return 1

  if k in N_memo:
    return N_memo[k]

  "From A11473 we have some handy formulas:"
  if (k % 3) == 0: # a(3n) = 4*floor((n+1)/2)
    n = k/3
    res = 4*((n+1)/2)
  elif ((k-2) % 3)==0: # a(3n+2)=2n+2
    n = (k-2)/3
    res = 2*n+2
  elif ((k-1) % 6)==0: # a(6n+1)=1
    res = 1
  else:
    # calculate recursively:
    res = 1 + (N(k-1) ^ N(k-2))

  N_memo[k] = res
  return N_memo[k]

ID = 0
FOUND = 0
def msum(k, n, refresh = False):
  global ID
  global FOUND

  if refresh == True:
    FOUND = False
    ID = 0

  if k == 0:
    print "k=0"
    return 0

  print "id",ID,"n",n
  ID += 1
  if (ID-1) == n:
    FOUND = True
    print "found"
    return 0

  if k == 1:
    print "k=1"
    return 1

  if FOUND == True:
    print "found N"
    r = 1 + (N(k-2) ^ N(k-1))
    print "found N r"
    return r

  print "up"
  r = 1 + (msum(k-2,n) ^ msum(k-1,n))
  print "r=", r
  return r

def main():
  print msum(4,3,True)

  #for k in xrange(1,11):
  #  size = nodes(k)
  #  wins = 0
  #  for n in xrange(2,size):
  #    s = msum(k, n, True)
  #    if s == 1:
  #      wins += 1
  #  print k, wins

if __name__ == "__main__":
  main()
