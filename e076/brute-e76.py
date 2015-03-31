def bits(n, length):
  return ("%0" + str(length) + "d") % int(bin(n)[2:])

def a(n):
  "Return (unique) ways of summing n with at least two numbers."
  h = {}
  for num in xrange(2**(n-1)):
    s = "".join(sorted(bits(num, n)))
    h[s] = 1
  return len(h.keys())

#print a(100)

for n in range(1,10):
  print n, a(n)
