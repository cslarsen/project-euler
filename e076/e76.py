"""
ProjectEuler.net problem 76
How many ways can we write 100 as a sum?
1+1+1+1+ ... +1 = 100
2+1+1+ ... +1 = 100

Using at least two digits:

99 + 1
98 + 2

etc

0->0
1->0
2->1
3->2
4->4
5->6
6->10
"""

import math
from fractions import Fraction as Fr

def fact(n):
  if n<2: return 1
  if n==2: return 2
  return reduce(lambda a,b: a*b, range(2,n+1))

def sums2(n):
  if n<2: return 0
  if n==2: return 1
  if n==3: return 2
  if n==4: return 4
  
  k = 2
  return fact(n-1)/(k*fact(n-k-1))

def sums(n):
  if n==0: return
  if n==1: yield [1]
  if n==2:
    yield [2]
    yield [1,1] # 1+1

  for i in range(n):
    for c in sums(i):
      yield sorted([n-i] + c)

def unique(n):
  return sorted(set(["+".join(map(str, S)) for S in sums(n)]))

def non_unique(n):
  return sorted(["+".join(map(str, S)) for S in sums(n)])

def count(n):
  return len(unique(n))

def n_take_k(n, k):
  return fact(n)/(fact(k)*fact(n-k))

"""
Note:
n_take_k(n-1, 2) is the same as (n-1)*(n-2)/2
or
n_take_k(n, 2) is the same as n*(n-1)/2
"""

def fibo(n):
  if n<=3: return n
  return fibo(n-1)+fibo(n-2)

#print count(100)
#sys.exit(0)

for n in range(1,15):
  # non-unique sums: 2**(n-1)
  combos = 2**(n-1) # same as len(non_unique(n))
  ucombos = count(n)
  print n, "==>", count(n), combos, n*(n-1)/2, 2**(n-2), n_take_k(n-1, n-3), fibo(n), sums2(n)
