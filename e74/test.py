import sys

def fact(n):
  "Returns factorial of n"
  if n <= 0:
    return 0
  return reduce(lambda a,b: a*b, range(2, 1+n), 1)

def digits(n):
  "Yields the digits in n"
  while n > 0:
    yield (n % 10)
    n /= 10

def sumfact(n):
  "Returns sum of factorials of n's digits"
  return sum(fact(i) for i in digits(n))

memo = {}
count_memo = {}

def chains(n, step=0):
  "Return number of iterative sumfact steps until we loop."
  if n in count_memo:
    return count_memo[n]

  m = sumfact(n)

  if m in memo:
    return step

  memo[n] = m
  c = chains(m, step+1)
  count_memo[n] = c
  return c

"""
How many chains, with a starting number below one million, contain exactly
sixty non-repeating terms?
"""
print chains(69)

#sys.exit(0)

count = 0
for n in xrange(1, 10**6):
  c = chains(n)
  if c == 60:
    print n, "has", c, "chains"
    count += 1

print "Count:", count
