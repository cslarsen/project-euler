#!/usr/bin/env python
# -*- encoding: utf-8 -*-

"""
Minimal solutions to Pell's equation
This is the solution to projecteuler.net problem 66.

Written by Christian Stigen Larsen

Solves any Pell equation using the Chakravala method.

This specific problem finds minimal solutions for a given D,
and prints D for the solution with the highest value of x.
"""

import math, sys

def scale_down(t, D):
  "Scale down solution to x^2-Dy^2 = k using Bhaskara's lemma"

  # Find m so that a+b*m is divisible by k and m^2-D is minimal
  a, b, k = t
  _, m = min([(m**2-D, m) for m in range(1, abs(k)+1) if (a+b*m) % k == 0])

  # Compose t with (m, 1, m**2-D)
  return ((a*m+D*b)/k, (a+b*m)/k, (m**2-D)/k), m

def solve(D):
  "Return minimal solution of Pell's equation: x^2 - Dy^2 = 1"
  t = (8, 1, 8**2-D) # Start w/any solution x^2-Dy^2=k and gcd(x,y)=1

  while t[2] != 1:
    t, m = scale_down(t, D)

  return t

def square(n):
  "True if n is a square number"
  return int(math.sqrt(n))**2 == n

MAX = 1000
(x, y, _), D = max((solve(D), D) for D in range(MAX+1) if not square(D))

print "Solution:", D
print ""
print "%d^2 -\n%d * %d^2 =\n%d" % (x, D, y, x**2-D*y**2)
