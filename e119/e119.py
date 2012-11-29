#!/usr/bin/env python

def digsum(n):
  r = 0
  for c in str(n):
    r += ord(c) - ord('0')
  return r

def good(n):
  d = digsum(n)
  a = d
  if a==1: return False
  if (n % d) != 0: return False

  #while n>1:
  #  if (n % d) != 0: return False
  #  n /= d
  #return True

  while True:
    a *= d
    if a>n: return False
    if a==n: return True

if __name__ == "__main__":
  assert(digsum(123)==6)
  assert(digsum(512)==8)
  assert(good(512)==True)
  assert(good(123)==False)
  assert(good(614656)==True)
  assert(good(614655)==False)
  assert(good(614657)==False)

  n = 0
  a = 10
  while n<32:
    a += 1
    if good(a):
      n += 1
      print "a(%d) = %d" % (n, a)
