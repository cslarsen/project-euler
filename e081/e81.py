W = 80
H = 80

MAP = [
  [131, 673, 234, 103, 18],
  [201, 96, 342, 965, 150],
  [630, 803, 746, 422, 111],
  [537, 699, 497, 121, 956],
  [805, 732, 524, 37, 331],
]

BIGGEST = 999999999999999999
smallest = BIGGEST

def path(x=0, y=0, acc=0):
  global smallest, BIGGEST

  if x>=W or y>=H:
    return BIGGEST

  acc += MAP[y][x]

  if x==(W-1) and y==(H-1):
    if acc < smallest:
      smallest = acc
      print "New min sum", acc
    return acc

  if acc >= smallest:
    return BIGGEST # backtrack

  s1 = path(x+1, y, acc)
  s2 = path(x, y+1, acc)

  if s1 < s2:
    return s1
  else:
    return s2

def read(name):
  global W, H
  W = 0
  H = 0
  m = []

  with open(name) as f:
    for line in f.readlines():
      line = line.strip()
      l = [int(n) for n in line.split(",")]
      W = len(l)
      H += 1
      m.append(l)

  return m
  
MAP = read("matrix.txt")
sol = path()
print smallest
