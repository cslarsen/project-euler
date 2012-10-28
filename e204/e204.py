#!/usr/bin/env python

"""
ProjectEuler.net Problem 204
Solved by Christian Stigen Larsen

Find x so that x^2 = 1_2_3_4_5_6_7_8_9_0 where _ is an arbitrary digit.

math.sqrt(1020304050607080900) == 1010101010.1010101
so the answer should be right after that.
"""

from math import *
import re, sys

MIN = 1020304050607080900
MAX = 1929394959697989990

x = int(sqrt(1020304050607080900))

pattern = re.compile("1.2.3.4.5.6.7.8.9.0");
def accepted(n):
  return pattern.match(str(n))

n = 0
while not accepted(x):
  if (n % 1000000) == 0:
    print x, x*x
    sys.stdout.flush()
  n += 1
  x += 1

print x, "squared is", x*x
