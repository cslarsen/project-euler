#!/usr/bin/env python
"""
ProjectEuler problem 62
by Christian Stigen Larsen

Runs in 0.2 secs

---
Problem 62
30 January 2004

The cube, 41063625 (345^3), can be permuted to produce two other cubes:
56623104 (384^3) and 66430125 (405^3). In fact, 41063625 is the smallest
cube which has exactly three permutations of its digits which are also cube.

Find the smallest cube for which exactly five permutations of its digits are
cube.
"""

MAXBASE = 100000

# Find all cubes below MAXBASE

cubes = []
rev_cube = {} # lookup base from cube

for base in xrange(0, MAXBASE):
  cubes.append(base**3)
  rev_cube[base**3] = base

# For all cubes, find all permutations that are also cube.
# This should give len(perms[sorted_digits(345**3)]) == 3

perms = {}

def sorted_digits(n):
  return "".join(sorted(str(n)))

for cube in cubes:
  n = sorted_digits(cube)

  if n in perms:
    perms[n].append(cube)
  else:
    perms[n] = [cube]

# Count permutations, store in a hash with the base

MAX_NUM_PERMS = 0

bases = {}

for k in perms.keys():
  l = len(perms[k])

  if l == 0:
    continue

  first_cube = perms[k][0]
  base = rev_cube[first_cube]
  bases[base] = l

# bases now contains a base and number of permutations
# print the lowest value for each permutation:

MAX = 0
for b in sorted(bases.keys()):
  if bases[b] > MAX:
    MAX = bases[b]
    print b, "has", bases[b], "permutations",
    # Print the smallest cube that fits this
    print "with smallest cube", min(perms[sorted_digits(b**3)])
