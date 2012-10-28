#!/usr/bin/env python

squares = [n**2 for n in xrange(0, sqrt(10**10))]

#n = 0
#while n**2 < 10**10:
#  squares.append(n**2)
#  n += 1

print len(squares)
