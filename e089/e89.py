# -*- encoding: utf-8 -*-

"""ProjectEuler.net problem 89
Read and convert roman numerals.
--> Slow but sure solution.

By Christian Stigen Larsen, http://csl.sublevel3.org
Public domain, 2012

The only rule you need to know:
***Numerals must be arranged in descending order of size.***

The law:
Only I, X, and C can be used as the leading numeral in part of a subtractive
pair.
I can only be placed before V and X.
X can only be placed before L and C.
C can only be placed before D and M.

Try to display numbers using minimum number of letters.
"""

import sys
from itertools import permutations

values = {
  'I':    1,
  'V':    5,
  'X':   10,
  'L':   50,
  'C':  100,
  'D':  500,
  'M': 1000,
}

numerals = {
    1: 'I',
    5: 'V',
   10: 'X',
   50: 'L',
  100: 'C',
  500: 'D',
 1000: 'M',
}

def value(char):
  global values
  return values[char.upper()]

def from_string(s):
  """Convert roman numeral to integer.

  >>> from_string("MCMLXIV")
  1964
  >>> from_string("MCCCCCCVI")
  1606
  >>> from_string("MDCVI")
  1606
  """
  ret = 0
  s = s.translate(None, " ") # remove spaces
  num = list(reversed([value(c) for c in s]))
  prev = 0
  for v in num:
    if v >= prev:
      ret += v
      prev = v
    else:
      ret -= prev
      ret += (prev-v)
      prev = v

  return ret

def inverted(d):
  return dict(zip(d.values(), d.keys()))

def to_string_bad(n):
  # note: this does not produce tightest output
  # start with biggest values
  s = ""
  while n:
    for (v, c) in reversed(sorted(inverted(values).iteritems())):
      if v <= n:
        n -= v
        s += c
        break

  return s

"""
Tenker sånn:
1964 = 1000+900+60+4
og   = M    CM  LX IV
     = MCMLXIV

Problemet er dette:
10004 = 10000 = 10*1000, så så lenge vi har verdi som er 1000 eller over, så
kjør på
"""

def expand(n):
  "E.g. 1964 ==> [1000,900,60,4]"
  v = []
  exp = len(str(n))
  for ch in str(n):
    exp -= 1
    v.append(int(ch)*10**exp)
  return v

def to_char(n):
  "E.g. 1000 ==> M, 900 => CM, 60 => LX, 4 => IV"

  if n == 0:
    return ""

  NUMS = numerals.values()
  ret = []
  # Brute-force: Try all four-letter combos
  for a in NUMS:
    for b in NUMS:
      for c in NUMS:
        for d in NUMS:
          if n == from_string(d): ret.append(d)
          if n == from_string(c+d): ret.append(c+d)
          if n == from_string(b+c+d): ret.append(b+c+d)
          if n == from_string(a+b+c+d): ret.append(a+b+c+d)

  return min([(len(s), s) for s in ret])[1]

  raise Exception("ERROR: Couldn't translate to_char: " + str(n))

  #for a in numerals.values():
  #  num = from_string(a)
  #  if num == n:
  #    return a
  #  for b in numerals.values():
  #    num = from_string(a+b)
  #    if num == n:
  #      return a+b

def to_string(n):
  try:
    return "".join(map(to_char, expand(n)))
  except Exception, e:
    print "Error translating to string:", n
    print e
    sys.exit(0)

saved_bytes = 0
n = 0
with open("roman.txt") as f:
  for line in f.readlines():
    line = line.strip()
    num = from_string(line)
    if num == 0:
      print "Warning: 0 from", line
    new = to_string(num)
    if len(new) < len(line):
      saved_bytes += len(line)-len(new)
    n += 1
    print n, "Input:", line, "==>", num, "==>", new, "diff: ", len(line)-len(new)

print "Saved in total %d bytes" % saved_bytes
