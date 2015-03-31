def sumof(v):
  "[a,b,c...] -> 1*a + 2*b + 3*c + ..."
  return sum(map(lambda (f,n): f*n, zip(v,range(1,1+len(v)))))

def next(v):
  N = len(v)
  carry = 1
  for n in range(len(v)):
    v[n] += carry
    if v[n] > N/(n+1):
      v[n] = 0
      carry = 1
    else:
      carry = 0
  return v

def fmt(v):
  s = ""
  for n in reversed(range(len(v))):
    for i in range(v[n]):
      if len(s) > 0: s += "+"
      s += "%d" % (n+1)
  return "%d = %s" % (len(v), s)

def allof(v):
  while v[-1] == 0:
    if sumof(v) == len(v):
      yield v
    v = next(v)

def fmtall(v):
  "Return all sums that have at least two integers"
  for i in allof(v):
    yield fmt(v)

def count(n):
  c = 0
  for i in allof([0]*n):
    c += 1
  return c

#for i in fmtall([0]*6):
#  print i

#for i in fmtall([0]*6):
#  print i

for n in range(1,20):
  print n, count(n)

#print 100, count(100)
