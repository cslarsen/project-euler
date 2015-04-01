"""
ProjectEuler.net Problem 86

By Christian Stigen Larsen
http://csl.name

See README.md for the description and strategy used.
"""

from math import sqrt
import sys

def M(number, verbose=False):
    """Probably correct, brute-force version which is slow."""
    m = number
    count = 0

    if verbose:
        sys.stdout.write("M(%d) ... " % number)
        sys.stdout.flush()

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
        sys.stdout.write("%d\n" % count)
        sys.stdout.flush()
    return count

def isinteger(n):
    return n == int(n)

def perfect_square(n):
    """True if number is a perfect square."""
    # Taken from
    # http://stackoverflow.com/questions/295579/fastest-way-to-determine-if-an-integers-square-root-is-an-integer
    if n & 0x0F in [0, 1, 4, 9]:
        return True
    else:
        return isinteger(sqrt(n))

def Mf(m, verbose=False):
    """Fast version of M."""
    count = 0

    if verbose:
        sys.stdout.write("Mf(%d) ... " % m)
        sys.stdout.flush()

    for h in xrange(1, m+1):
        hh = h*h

        for w in xrange(h, m+1):
            ww = w*w
            wh2 = w*h*2

            for l in xrange(w, m+1):
                ll = l*l
                lh2 = l*h*2

                # Comparing (ll+lh2+hh+ww) to (ww + wh2 + hh + ll) can be
                # simplified to comparing lh2 vs wh2:
                if lh2 >= wh2:
                    shortest = ll + lh2 + hh + ww
                else:
                    shortest = ww + wh2 + hh + ll

                # Further sqrt(ll + lh2 + hh + ww) vs (h + sqrt(ll + ww),
                # just check if h^2 is bigger than ll+lh2+hh+ww first
                if hh < shortest:
                    shortest = min(shortest, h + sqrt(ll + ww))

                if isinteger(shortest):
                    count += 1

    if verbose:
        sys.stdout.write("%d\n" % count)
        sys.stdout.flush()
    return count

def main(verify=False):
    assert(M(99) == Mf(99) == 1975)
    assert(M(100) == Mf(100) == 2060)

    seq = []
    try:
        print("")
        for n in xrange(10**6):
            r = Mf(n, verbose=True)
            seq.append(r)
            if verify:
                assert(r == M(n))
            if seq[-1] > 10**6:
                break
    except KeyboardInterrupt:
        print("")
        print(",".join(map(str, seq)))

if __name__ == "__main__":
    main()
