"""
ProjectEuler.net Problem 86

By Christian Stigen Larsen
http://csl.name

Imagine a line from fly to the two spiders. So to routes there, and one via the
roof. For each combination of integers l,h,w < m, we want to find the shortest
of the three routes, and if it's an integer, count it.

For m=100, there are 2060 such (distinct) cuboids.
For m=99, the solution is 1975.

Flattened:

 Cuboid = L*W*H
 x = spider
 f = fly
                       L
                  +---------x
                  |         |
                H |         |
                  |         |
            +-----+---------+-----x
            |     |         |     |
          W |     | bottom  |     | W
       L    |     |         |     |
  +---------+-----f---------+-----+
  |         |  H  |         |  H
W |   top   |     |         |
  |         |     |         |
  x---------+     +---------+

Three routes:
   - sqrt((L+H)^2 + W^2)
   - sqrt((W+H)^2 + L^2)
   - H + sqrt(L^2 + W^2)
"""

from math import sqrt
import sys

def M(number):
    m = number
    count = 0

    sys.stdout.write("M(%d) ... " % number)
    sys.stdout.flush()

    for h in xrange(1, m+1):
        for w in xrange(h, m+1):
            for l in xrange(w, m+1):
                routes = [ sqrt((l+h)**2 + w**2),
                           sqrt((w+h)**2 + l**2),
                           h + sqrt(l**2 + w**2) ]
                smallest = min(routes)
                if int(smallest) == smallest:
                    count += 1

    sys.stdout.write("%d\n" % count)
    sys.stdout.flush()
    return count

def main():
    print("Tests")
    assert(M(99) == 1975)
    assert(M(100) == 2060)

    seq = []
    try:
        print("")
        for n in xrange(10**6):
            seq.append(M(n))
            if seq[-1] > 10**6:
                break
    except KeyboardInterrupt:
        print("")
        print(",".join(map(str, seq)))

if __name__ == "__main__":
    main()
