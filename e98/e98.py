#!/usr/bin/env python

from math import sqrt
from itertools import permutations

pairs = [
     ['SIGN', 'SING'],
   ['EARN', 'NEAR'],
  ['EARTH', 'HEART'],
  ['LEAST', 'STEAL'],
  ['PHASE', 'SHAPE'],
   ['SHUT', 'THUS'],
 ['CREDIT', 'DIRECT'],
   ['MALE', 'MEAL'],
 ['CREATION', 'REACTION'],
    ['ACT', 'CAT'],
   ['CARE', 'RACE'],
   ['HATE', 'HEAT'],
    ['EAT', 'TEA'],
   ['FORM', 'FROM'],
  ['THROW', 'WORTH'],
  ['SHEET', 'THESE'],
     ['NO', 'ON'],
    ['DOG', 'GOD'],
   ['NOTE', 'TONE'],
   ['DEAL', 'LEAD'],
 ['CENTRE', 'RECENT'],
   ['FILE', 'LIFE'],
 ['INTRODUCE', 'REDUCTION'],
  ['QUIET', 'QUITE'],
 ['FORMER', 'REFORM'],
   ['ITEM', 'TIME'],
   ['RATE', 'TEAR'],
    ['HOW', 'WHO'],
  ['SHOUT', 'SOUTH'],
   ['MEAN', 'NAME'],
  ['BOARD', 'BROAD'],
    ['ITS', 'SIT'],
   ['SURE', 'USER'],
  ['ARISE', 'RAISE'],
 ['COURSE', 'SOURCE'],
 ['IGNORE', 'REGION'],
  ['NIGHT', 'THING'],
   ['EAST', 'SEAT'],
 ['EXCEPT', 'EXPECT'],
    ['NOW', 'OWN'],
     ['POST', 'SPOT'],
     ['SPOT', 'STOP'],
     ['POST', 'STOP'],
 ['DANGER', 'GARDEN']
]

def issquare(n):
  s = int(sqrt(n))
  return s*s == n

def number(s, values):
  n = 0
  for c in s:
    n *= 10
    n += values[c]
  return n

def getvals(s):
  r = {}
  for c in s:
    r[c] = 0
  return r

best = 0

for words in pairs:
  w1 = words[0]
  w2 = words[1]
  vals = getvals(w1)

  print best,w1,w2

  for p in permutations(range(0,10), len(w1)):
    v = dict(zip(vals.keys(), p))

    if v[w1[0]]==0 or v[w2[0]]==0:
      continue # do not allow leading zeroes

    n1 = number(w1,v)
    n2 = number(w2,v)

    if issquare(n1) and issquare(n2):
      print w1,n1,w2,n2
      if n1>best: best = n1
      if n2>best: best = n2
