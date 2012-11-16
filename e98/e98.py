#!/usr/bin/env python

from math import sqrt
from words import words

anagrams = {}
values = {"A": [2], "C": [1], "R": [9], "E": [6]}
squares = [i*i for i in range(1,1000)]

def freq(s):
  s = s.upper()
  f = {}
  for c in s:
    if not c in f: f[c] = 0
    f[c] += 1
  return f

def issquare(n):
  s = int(sqrt(n))
  return s*s == n

def sort(s):
  return "".join(sorted(s))

def anagram(a, b):
  return sort(a) == sort(b)

def removekey(d, key):
  r = dict(d)
  del r[key]
  return r

def init():
  global words
  global anagrams
  global values

  for w in words:
    if not sort(w) in anagrams:
      anagrams[sort(w)] = []
    anagrams[sort(w)].append(w)

  # remove non-anagrams
  rem = []
  for k in anagrams:
    if len(anagrams[k]) <= 1:
      rem.append(k)
  for k in rem:
    anagrams = removekey(anagrams, k)

  # insert possible values
  for c in ["B", "D", "F", "G", "H", "I", "J", "K",
            "L", "M", "N", "O", "P", "Q", "S", "T",
            "U", "V", "W", "X", "Y", "Z"]:
    values[c] = [0,3,4,5,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26]

  # remove 0 as possibility for these
  for c in ["B", "D", "F", "G", "H", "I", "L", "M",
            "N", "O", "P", "Q", "S", "T", "U", "W"]:
    values[c].remove(0)

def unknowns(s):
  "Returns unknown letters"
  global values
  return [c for c in s if len(values[c])>1]

def number(s, values = values):
  n = 0
  for c in s:
    n *= 10
    n += values[c][0]
  return n

def find(s, values=values):
  # for words with ONE unknown, list up
  # all possible values
  u = unknowns(s)[0]
  ucand = [] # candidate numbers for u
  for v in values[u]:
    w = dict(values) # make a copy
    del(w[u])
    w[u] = [v]
    if issquare(number(s,w)):
      ucand.append(v)
  return u, ucand

def unknown_words(count_unknown_letters):
  "Returns all words with n unknown letters"
  r = []
  for k in anagrams:
    for w in anagrams[k]:
      if len(unknowns(w))==count_unknown_letters:
        r.append(w)
  return r

def words_with_letters(letters):
  "Return all words that have these letters"
  r = []
  for k in anagrams:
    for w in anagrams[k]:
      found = True
      for l in letters:
        if not l in w:
          found = False
          break
      if found:
        r.append(w)
  return r

def words_with_any_of(letters):
  "Return all words that have ANY of these letters"
  r = []
  for k in anagrams:
    for w in anagrams[k]:
      for l in letters:
        if l in w:
          r.append(w)
          break
  return r

def find_squares():
  global anagrams
  for k in anagrams:
    for w in anagrams[k]:
      if len(unknowns(w))==0:
        n = number(w)
        if not issquare(n):
          break
        print "square:",w,n

init()

# print possibilitis
charcands = {}
for w in unknown_words(1):
  ch, vals = find(w)
  if len(vals)>0:
    if not ch in charcands: charcands[ch] = []
    charcands[ch] += vals

# now set these new possibilities for each char
for ch in charcands:
  values[ch] = charcands[ch]

# run again and see if we can find any more
values["T"] = [15]
charcands = {}
for w in unknown_words(1):
  ch, vals = find(w)
  if len(vals)>0:
    if not ch in charcands: charcands[ch] = []
    charcands[ch] += vals

print charcands

# look at heart, try setting value of T to any of 
# 15, 24, 5 and see if it is square
#for n in [15,24,5]:
#  v = dict(values)
#  v["T"] = n
##  print find("HEART", v)

print "Squares"
print find_squares()
