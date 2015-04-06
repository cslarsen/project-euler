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
    """Tests whether a number is a perfect square, i.e., its square root is
    integer."""

    # Optimization: By doing set((x*x % 0xF) for x in xrange(100000...)),
    # you'll see the last four bits are always in the set 0,1,4,9.  We use this
    # to filter away numbers that are clearly not perfect squares.
    #
    # Idea taken from John D. Cook at:
    # http://stackoverflow.com/questions/295579/fastest-way-to-determine-if-an-integers-square-root-is-an-integer

    if (n & 0x0F) not in set([0, 1, 4, 9]):
        return False
    else:
        return isinteger(sqrt(n))

def integer_least_route(w, h, l):
    """Tests if a cuboid's shortest corner-to-corner path is an integer."""
    #shortest_path = w*h*2 + h*h + w*w + l*l
    shortest_path = (w+h)**2 + l**2
    return perfect_square(shortest_path)

def check(w,h,l):
    return integer_least_route(w,h,l)

def Mf(m, verbose=False):
    """Faster version of M."""
    count = 0

    if verbose:
        write("Mf(%d) ... " % m)

    for h in xrange(1, m+1):
        for w in xrange(h, m+1):
            for l in xrange(w, m+1):
                if integer_least_route(w, h, l):
                    count += 1
    if verbose:
        write("%d\n" % count)
    return count

def nextm(l):
    """M(l) = M(l-1) + nextm(l)."""
    c = 0
    ll = l*l
    for h in range(1,l+1):
        for w in range(h, l+1):
            if perfect_square((w+h)**2 + ll):
                c += 1
    return c

def sanity_check(full=False):
    assert M(99) == 1975, "Got %d" % M(99)
    assert M(100) == 2060, "Got %d" % M(100)
    assert Mf(99) == 1975, "Got %d" % Mf(99)
    assert Mf(100) == 2060, "Got %d" % Mf(100)

def main(verify=False):
    sanity_check()

    count = 0
    for n in xrange(10**6):
        count += nextm(n)
        if count > 1000000:
            print("Answer: M(%d) > 10e6" % n)
            break

        if verify:
            assert(count == M(n))

        write("M(%d) = %d\n" % (n, count))

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass
