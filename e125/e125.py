from sys import exit
from math import sqrt

def palindrome(n):
  rev = int("".join(reversed(str(n))))
  return rev - n == 0

MAX = 10**8
STOP = int((sqrt(2*MAX-1)+1)/2)
print "N:",MAX,"STOP:",STOP

print "Squares"
squares = [n*n for n in xrange(1,1+STOP)]

print "Square sums"
square_sums = []
isum = 0
for i in xrange(0,len(squares)):
  jsum = 0
  for j in xrange(0,i-1):
    n = isum - jsum
    if n<MAX and palindrome(n):
      square_sums.append(isum-jsum)
    jsum += squares[j]
  isum += squares[i]
pali = square_sums

# only unique solutions!
pali = set(pali)

print "Palindromes:",len(pali)
print "Their sum:", sum(pali)
print sorted(pali)
