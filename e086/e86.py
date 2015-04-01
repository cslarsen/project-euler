"""
ProjectEuler.net Problem 86

By Christian Stigen Larsen
http://csl.name

See README.md for the description and strategy used.
"""

from math import sqrt
import sys

def write(s):
    sys.stdout.write(s)
    sys.stdout.flush()

def M(number, verbose=False):
    """Probably correct, brute-force version which is slow."""
    m = number
    count = 0

    if verbose:
        write("M(%d) ... " % number)

    for h in xrange(1, m+1):
        for w in xrange(h, m+1):
            for l in xrange(w, m+1):
                routes = [ sqrt((l+h)**2 + w**2),
                           sqrt((w+h)**2 + l**2),
                           h + sqrt(l**2 + w**2) ]
                shortest = min(routes)
                if int(shortest) == shortest:
                    count += 1

    if verbose:
        write("%d\n" % count)
    return count

def isinteger(n):
    return n == int(n)

def perfect_square(n):
    """True if number is a perfect square."""
    # Taken from
    # http://stackoverflow.com/questions/295579/fastest-way-to-determine-if-an-integers-square-root-is-an-integer
    if not (n & 0x0F) in [0, 1, 4, 9]:
        return False
    return isinteger(sqrt(n))

def Mf(m, verbose=False):
    """Fast version of M."""
    count = 0

    if verbose:
        write("Mf(%d) ... " % m)

    for h in xrange(1, m+1):
        hh = h*h

        for w in xrange(h, m+1):
            ww = w*w
            wh2 = w*h*2

            for l in xrange(w, m+1):
                ll = l*l
                lh2 = l*h*2

                shortest = min(lh2, wh2) + hh + ww + ll
                if perfect_square(shortest):
                    count += 1
    if verbose:
        write("%d\n" % count)
    return count

def main(verify=False):
    assert M(99) == 1975, "Got %d" % M(99)
    assert M(100) == 2060, "Got %d" % M(100)

    assert Mf(99) == 1975, "Got %d" % Mf(99)
    assert Mf(100) == 2060, "Got %d" % Mf(100)

    for n in xrange(10**6):
        r = Mf(n)
        if r > 10**6:
            break
        if verify:
            assert(r == M(n))
        write("%d " % r)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass
