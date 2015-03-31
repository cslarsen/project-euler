"""
2a+b <= 10**9
2a+a+1 <= 10**9
3a
"""
from math import sqrt

S=0

def area(a,b,c):
  return 0.25*sqrt((a+b-c)*(a-b+c)*(-a+b+c)*(a+b+c))

def good(a,b,c):
  a = area(a,b,c)
  return int(a) == a

for a in xrange(2,(10**9)/3):
  if 2*a >= 10**9:
    print "bailout",S
    break
  for b in [a-1,a+1]:
    if b==a:
      continue
    if not (b+1==a or b-1==a):
      continue
    c = a+a+b
    if c > 10**9:
      continue
    A = area(a,a,b)
    if A == int(A):
      S += c
      print a,a,b,"area",int(A),"circ",c, "sum",S
    # a+a+b <= 10**9
