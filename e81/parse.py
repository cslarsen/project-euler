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

lines = []
for y in MAP:
  lines.append("{" + ", ".join(str(x) for x in y) + "}")

print "#include <stdint.h>"
print ""
print "uint32_t map[80][80] = {"
print ",\n".join(lines)
print "};"
