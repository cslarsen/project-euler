"""
1 + 1/(2 + 1/(2 + 1/2)) 

1 + 1/2 = 3/2 = 1.5
1 + 1/(2 + 1/2) = 7/5 = 1.4
1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...

The next three expansions are 99/70, 239/169, and 577/408, but the eighth expansion, 1393/985, is the first example where the number of digits in the numerator exceeds the number of digits in the denominator.

In the first one-thousand expansions, how many fractions contain a numerator with more digits than denominator?
"""

number = 0

def root2(steps):
  "Calculate continued fraction expansion for the square root of two."
  global number

  num = 3
  den = 2

  for n in range(steps):
    tmp = num+den
    num += den*2
    den = tmp

    if len(str(num)) > len(str(den)):
      number += 1

  return (num, den)

root2(1000)
print number
