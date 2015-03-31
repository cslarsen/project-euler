"""
ProjectEuler.net problem 90
Solved by Christian Stigen Larsen
"""

from math import sqrt

# square numbers
squares = [(0,1), (0,4), (0,9), (1,6), (2,5), (3,6), (4,9), (6,4), (8,1)]

# two dice; left and right
l = [x for x,y in squares]
r = [y for x,y in squares]
print squares

# numbers REQUIRED on each die
reql = list(set(l))
reqr = list(set(r))

print reql
print reqr

