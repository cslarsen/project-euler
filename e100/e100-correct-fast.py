#!/usr/bin/env python

"""
Projecteuler.net problem 100
Solved by Christian Stigen Larsen

Sequence is:
a(n) = 3*a(n-1)+sqrt(8*a(n-1)^2+1)
"""

from math import sqrt

r = 1
while True:
  r = 3*r + int(sqrt(8*(r**2)+1))
  b = int(0.5*(sqrt(8*r*r+1) + 2*r + 1))
  print r,b,r+b
  if r+b > 10**12:
    break # correct answer b=756872327473
