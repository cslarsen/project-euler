"""
ProjectEuler.net problem 65
"""

import sys
from fractions import Fraction as frac

def sq2(n):
  "Estimate square root of two by continued fractions"
  # Format: [1;(2)]
  base = 1
  repeater = 2
  def helper(n):
    if n==0: return repeater
    return repeater + frac(1, helper(n-1))
  return base + frac(1, helper(n-1))

k = 1
def e(n):
  "Estimate e by continued fractions"
  # Format: [2; 1,2,1, 1,4,1, 1,6,1, ..., 1,2k,1 ...]
  base = 2

  def repeater():
    k=1
    while True:
      yield 1
      yield 2*k
      k+=1
      yield 1

  R = repeater()

  def helper(n, depth=1):
    if n==0: return R.next()
    return R.next() + frac(1, helper(n-1, depth+1))

  if n==0: return base
  return base + frac(1, helper(n-1))

def digital_sum(n):
  return sum(int(c) for c in str(n))

last = 0
for n in range(1,10):
  last = sq2(n)
  print last

num = last.numerator
print num, "==>", digital_sum(num)

print ""
print "e:"

last = 0
for n in range(1,100):
  last = e(n)
  print last

num = last.numerator
print num, "==>", digital_sum(num)
