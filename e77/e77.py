#!/usr/bin/env python

"""
ProjectEuler.net Problem 77
Solved by Christian Stigen Larsen

Using a generating function known as the Euler Transform.

For an explanation, see:
http://math.stackexchange.com/questions/89240/prime-partition

For the function, see:
http://mathworld.wolfram.com/EulerTransform.html

For the number sequence, see:
http://oeis.org/A000607
"""

primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
    61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137,
    139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211,
    223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271]

def f(p, stop):
  for k in xrange(0, 1+stop/p):
    yield k*p, 1

def xsum(i,j):
  x1, c1 = i
  x2, c2 = j
  assert(x1==x2)
  return (x1, c1+c2)

def xmul(i,j):
  x1, c1 = i
  x2, c2 = j
  return (x1+x2, c1*c2)

def seqmul(s,t):
  r = []
  s = list(s) # Python's generators SUCK
  t = list(t)
  for i in s:
    for j in t:
      r.append(xmul(i,j))
  return simplify(r)

def cutoff(p, stop):
  return filter(lambda (x,c): x<=stop, p)

def simplify(p):
  r = []
  while len(p) > 0:
    s = p.pop()
    q = filter(lambda u: u[0]==s[0], p)
    p = filter(lambda u: u[0]!=s[0], p) # ORDER DEPENDENCY
    r.append(reduce(xsum, q, s))
  return sorted(r)

def prime_parts(n):
  global primes

  v = f(2,n)
  for p in filter(lambda x: x<n, primes)[1:]:
    v = cutoff(seqmul(v, f(p,n)), n)

  part = filter(lambda (x,c): x==n, v)[0][1]
  return part

def run(n):
  return prime_parts(n)

if __name__ == "__main__":
  TARGET = 5000
  best = 0
  n = 57 # from oeis.org table 
  while True:
    p = run(n)
    if p > best:
      print n, "has", p, "prime partitions"
      best = p
      if best > TARGET:
        break
    n += 1
