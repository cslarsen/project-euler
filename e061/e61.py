#!/usr/bin/env python

"""
ProjectEuler.net Problem 61
Solved by Christian Stigen Larsen
"""

# 4-digit number in range 45--140
def tri(n):
  return n*(n+1)/2

# 32--99
def sq(n):
  return n*n

# 26--81
def penta(n):
  return n*(3*n-1)/2

# 23--70
def hexa(n):
  return n*(2*n-1)

# 15--45
def hepta(n):
  return n*(5*n-3)

# 19--58
def octa(n):
  return n*(3*n-2)

c = 0
for t in xrange(45, 140+1):
  for s in xrange(32, 99+1):
    for p in xrange(26, 81+1):
      for hx in xrange(23, 70+1):
        for hp in xrange(15, 45+1):
          for oc in xrange(19, 58+1):
            c = c+1

print c
