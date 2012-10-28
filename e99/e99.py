# -*- encoding: utf-8 -*-

import math, sys

def size(base, exp, comparison_base=10):
  return exp*math.log(base)/math.log(comparison_base)

lineno = 0
biggest = 0

if __name__ == "__main__":
  with open("base_exp.txt") as f:
    for line in f.readlines():
      line = line.strip()
      lineno += 1
      base, expo = map(float, line.split(","))
      s = size(base, expo)
      if s > biggest:
        biggest = s
        print "%d^%d is ca. 10^%f on line %d" % (base, expo, s, lineno)
