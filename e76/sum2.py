"""
projecteuler.net problem 76

It is possible to write five as a sum in exactly six different ways:

  4 + 1
  3 + 2
  3 + 1 + 1
  2 + 2 + 1
  2 + 1 + 1 + 1
  1 + 1 + 1 + 1 + 1

  How many different ways can one hundred be written as a sum of at least
  two positive integers?
"""

import math

def sum2(n):
  "Return number of ways to write n as sum of two numbers"
  if n<=0: return 0
  return int(math.floor(n/2))

def sum2n(n):
  "Return number of ways to write n as sum of two or more numbers"
  if n<=2: return 1
  return sum2n(n-1)*sum2(n)

def log2(n):
  if n<=1: return 0
  return int(math.log(n)/math.log(2))

def a(n):
  r = 0
  for i in range(1,n+1):
    r += log2(i)
  return r

def oracle(n):
  "Known ways of summing n with at least two positive integers"
  if n<2: return 0
  if n==2: return 1
  if n==3: return 2
  if n==4: return 3
  if n==5: return 6
  if n==6: return 9
  return -1

def test(n):
  print n, "->", sum2n(n), a(n), oracle(n)

for n in range(1,11):
  test(n)
