"""
ProjectEuler.net Problem 86

By Christian Stigen Larsen
http://csl.name

See README.md for the description and strategy used.
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
