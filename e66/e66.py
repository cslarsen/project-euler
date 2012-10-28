import math, sys

"""
Minimal solutions to Pell's equation
projecteuler.net problem 66.

Written by Christian Stigen Larsen
"""

def any_solution(D):
  """Return any trivial (a, b, k) solution for a^2 - Dy^2 = k
  Should have gcd(a, b) = 1
  """
  a = 8
  b = 1
  k = a**2 - D*b**2
  return (a, b, k)

def find_m(t, D):
  a, b, k = t

  _, m = min([(m**2-D, m) for m in xrange(1,abs(k)+1) if (a+b*m) % abs(k) == 0])

  # compose t with (m, 1, m**2-D)
  u = (a*m+D*b, a+b*m, m**2-D)
  u = (u[0]/k, u[1]/k, u[2]/k)

  return u, m

def solve(D):
  t = any_solution(D)

  # now find an m so that a+bm/k is integer
  # and abs(m^2-D / k) is minimal
  while t[2] != 1:
    t, m = find_m(t, D)

  return abs(t[0]), abs(t[1]), t[2]

xmax = 0
dmax = 1000
bestd = 0

for D in range(2, dmax+1):
  if int(math.sqrt(D))**2 == D:
    continue

  s = solve(D)
  if s:
    x, y, k = s

    if x > xmax:
      xmax = x
      bestd = D
      print "New xmax:", xmax

    res = x**2 - D*y**2
    print "%d^2 - %d*%d^2 = %d" % (x, D, y, x**2-D*y**2)
    if res != 1:
      print "Error"
      sys.exit(1)
  else:
    print "No solution found for", D

print "Largest x is", xmax, "for D =", dmax
print "Thus, the answer to prob 66 is D =", bestd
