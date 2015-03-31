"""
a0 = 1, b0 = 2
an = 2bn.1 + an.1
bn = 2an + bn.1

http://en.wikipedia.org/wiki/Special_right_triangles#Almost-isosceles_Pythagorean_triples

filter for eq sides

How this formula is deduced:
http://ajc.maths.uq.edu.au/pdf/11/ajc-v11-p263.pdf
"""

from math import sqrt

an = 1
bn = 2
n=0
while True:
  n += 1
  an = 2*bn + an
  bn = 2*an + bn

  # use an and find smallest pythagorean triplets
  print n, an, bn, sqrt(an**2 + (an+1)**2)

  # an = hypotenuse
  if an > 10000:
    break


"""
1 5 12
2 29 70
3 169 408
4 985 2378
5 5741 13860
6 33461 80782
"""
