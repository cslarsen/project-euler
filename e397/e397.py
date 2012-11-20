import math

def y(x, k):
  return float(x*x)/k

def point(x,k):
  return float(x), y(x,k)

def angle(p):
  "Angle in degrees between point and origo"
  x,y = p
  return math.degrees(math.atan(float(y)/x))

def angle2(p1,p2):
  "Angle between two points"
  return abs(angle(p1) - angle(p2))

def good(p1,p2):
  try:
    a = abs(angle2(p1,p2))

    d=45
    if a==d or a==(180-d) or a==(360-d) or a==(270-d): return True

    #d=135
    #if a==d or a==(180-d) or a==(360-d) or a==(270-d): return True

    return False
  except Exception, e:
    return False


def F(K, X):
  count = 0
  for k in xrange(1,1+K):
    for a in xrange(-X,1+X):
      if a==0: continue

      for b in xrange(-X,1+X):
        #if b==0: continue

        for c in xrange(-X,1+X):
          #if c==0: continue
          A = point(a,k)
          B = point(b,k)
          C = point(c,k)

          if good(A,B) or good(B,C) or good(A,C):
            count += 1
            _min = min(A,B,C)
            _max = max(A,B,C)
            _mid = [A,B,C]
            _mid.remove(_min)
            _mid.remove(_max)
            _mid = _mid[0]
            print k,_min,_mid,_max

  return count

if __name__ == "__main__":
  assert(angle2((10,0), (10,10))==45)
  assert(angle2((1,0), (1,1))==45)
  assert(angle2((1,2), (1,1))!=45)
  #print F(1,10)
  F(10,100)
  #assert(F(1,10)==41)
  #assert(F(10,100)==12492)
