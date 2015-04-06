"""
ProjectEuler.net problem 90
Solved by Christian Stigen Larsen
"""

from math import sqrt

# square numbers
squares = [(0,1), (0,4), (0,9), (1,6), (2,5), (3,6), (4,9), (6,4), (8,1)]

# Which numbers do we *have* to use
l = set([x for (x,y) in squares])
r = set([y for (x,y) in squares])
u = l.union(r)
print("Numbers we must use: %s" % u)
# Note that 6 and 9 are interchangeable, but we may use an arrangement that
# uses both

# So we have 9 numbers we can choose from

def tostr(die):
    s = "".join(map(str, die))
    s = s.replace("6", "x")
    s = s.replace("9", "x")
    return s

def good(d1, d2):
    d1 = tostr(d1)
    d2 = tostr(d2)

    for s in [x*x for x in range(1,10)]:
        s = "%02d" % s
        s = s.replace("6", "x")
        s = s.replace("9", "x")
        a,b = s

        if (a in d1) and (b in d2):
            continue
        elif (a in d2) and (b in d1):
            continue
        else:
            return False
    return True

assert(good([0,5,6,7,8,9], [1,2,3,4,6,7]))
assert(not good([1,5,6,7,8,9], [1,2,3,4,6,7]))

# binom(9,6) = 84, so there are 84 ways to create each die
# giving 84*84 = 7056 possible die combinations; binom(9,3) == binom(9,6)

# create a die by selecting three numbers to take away
def dies():
    u = set([0,1,2,3,4,5,6,7,8,9])#l.union(r)
    for a in u:
        for b in u:
            for c in u:
                for d in u:
                    if a==b or b==c or a==c or a==d or b==d or c==d:
                        continue
                    #u = l.union(r)
                    uu = u.copy()
                    uu.remove(a)
                    uu.remove(b)
                    uu.remove(c)
                    uu.remove(d)
                    yield uu

print("OK, I did it the slow brute-force way... but it worked!")

seen = set()
c = 0
for d1 in dies():
    for d2 in dies():
        d1 = sorted(d1)
        d2 = sorted(d2)
        if good(d1, d2):
            d1s = "".join(sorted("".join(map(str, d1))))
            d2s = "".join(sorted("".join(map(str, d2))))
            ds = min(d1s,d2s) + "-" + max(d1s,d2s)
            if ds not in seen:
                c += 1
                print("d1=%s d2=%s count=%d" % ("".join(map(str,d1)), "".join(map(str,d2)), c))
                seen.update([ds])
print(c)
print(l.union(r))
