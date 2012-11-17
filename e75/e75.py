import sys
import math
from fractions import gcd

def triple():
  for m in range(1,1300):
    for n in range(1,m):
      if gcd(m,n)!=1 and ((m-n) & 1)!=1:
        continue
      yield m*m-n*n, 2*m*n, m*m+n*n
  yield 0,0,0

MAX = 1500000
found = {}
seen = set()
t = triple()

while True:
  x,y,z = t.next()

  if x+y+z > MAX:
    continue

  if x==0 and y==0 and z==0:
    break

  k=1
  while True:
    a = x*k
    b = y*k
    c = z*k

    k += 1
    L=a+b+c
    if L > MAX:
      break

    T = tuple(sorted((a,b,c)))
    if not T in seen:
      seen.add(T)
      if not L in found: found[L] = 0
      found[L] += 1

count = sum(1 for k in found if found[k]==1)

print "12 ->", found[12]
print "24 ->", found[24]
print "30 ->", found[30]
print "36 ->", found[36]
print "40 ->", found[40]
print "48 ->", found[48]
print "120 ->", found[120]

print "Answer:", count
