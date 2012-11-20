"""
ProjectEuler.net Problem 91
Solved by Christian Stigen Larsen
"""

from math import sqrt
import sys

print "Slow, but sure-fire solution"

s = 50

tot = ((s+1)**4)-(s+1)**2
print "Total points:", tot
print "Unique triangles:", tot/2

squares = []
for i in range(2,(s+2)*(s+2)):
  squares.append(i*i)

def square(n):
  return n in squares

def coords(maxx, maxy):
  for x in range(0,maxx+1):
    for y in range(0,maxy+1):
      yield x,y

def right(p,q):
  "Does the triangel have a 90 degree angle?"
  a,b=p
  c,d=q
  PP = a*a+b*b
  QQ = c*c+d*d
  PQ = (a-c)**2 + (b-d)**2
  points = [PP,QQ,PQ]
  hypo = max(points)
  points.remove(hypo)
  return sum(points) == hypo

o=0,0
c=0
for q in coords(s,s):
  for p in coords(s,s):
    if q==p or q==(0,0) or p==(0,0): continue
    if right(p,q):
      c+=1
      #print o,p,q

print c/2
