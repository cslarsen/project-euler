#!/usr/bin/env python

"""
ProjectEuler.net problem 96
Solved by Christian Stigen Larsen
"""

import sys, random

def getboxes(grid):
  "Return all 3x3 boxes from 9x9 grid"
  boxes = []
  for y in [0,3,6]:
    for x in [0,3,6]:
      boxes.append([
        grid[y][x:x+3],
        grid[y+1][x:x+3],
        grid[y+2][x:x+3]
      ])
  return boxes

def boxdigits(box):
  "Returns digits found in box"
  d = set()
  for y in range(0,3):
    for x in range(0,3):
      d.add(box[y][x])
  return d

def rowdigits(grid, y):
  "Get missing digits in given row"
  d = set()
  for x in xrange(0,9):
    d.add(grid[y][x])
  return d

def coldigits(grid, x):
  "Get missing digits in given column"
  d = set()
  for y in xrange(0,9):
    d.add(grid[y][x])
  return d

def cands(grid, x, y):
  "Return possible values at x,y"
  if grid[y][x]!=0: # already have value
    return set(grid[y][x])

  r = rowdigits(grid, y)
  c = coldigits(grid, x)

  # which box are we in?
  bx = x/3
  by = y/3
  # figure out which box we're in
  box = getboxes(grid)[int(x/3) + 3*int(y/3)]
  b = boxdigits(box)
  return set(range(0,10)) - r - c - b

def invert(digits):
  return set(range(0,10)) - digits

def solutions3x3(grid, box, boxx, boxy, onlyUnique=True):
  "Return values the we are forced to choose in 3x3 box"
  digits = boxdigits(box)

  """
  for first digit, see what candiadte digits
  can be in the row, and then in the column,
  then make a intersection of the two to get
  candidate digits for the first number
  """
  values = []
  # box with candidates 
  for y in range(0,3):
    for x in range(0,3):
      if box[y][x]!=0: continue # alreay have a solution
      rowd = rowdigits(grid, boxy+y)
      cold = coldigits(grid, boxx+x)
      cand = set(range(0,10)) - cold - rowd - digits

      # only one candidate left, we MUST use this value
      if onlyUnique==True and len(cand)==1:
        values.append((boxx+x,boxy+y,list(cand)[0]))
      elif onlyUnique==False:
        values.append((boxx+x,boxy+y,cand))
  return values

def solve(grid):
  # for each 3x3 box, get a solutio
  # if this is a global solution, return it
  # if not, get next solution
  boxes = getboxes(grid)

  # first row of boxes
  v = [] # forced values
  v += solutions3x3(grid, boxes[0], 0,0)
  v += solutions3x3(grid, boxes[1], 3,0)
  v += solutions3x3(grid, boxes[2], 6,0)

  # second row
  v += solutions3x3(grid, boxes[3], 0,3)
  v += solutions3x3(grid, boxes[4], 3,3)
  v += solutions3x3(grid, boxes[5], 6,3)

  # third  row
  v += solutions3x3(grid, boxes[6], 0,6)
  v += solutions3x3(grid, boxes[7], 3,6)
  v += solutions3x3(grid, boxes[8], 6,6)

  v = filter(lambda v: len(v)>0, v) # remove empty vals

  # update grid with new values
  for xyv in v:
    x,y,val = xyv
    grid[y][x] = val

  return grid

def candidates(grid):
  boxes = getboxes(grid)

  # first row of boxes
  v = [] # forced values
  v += solutions3x3(grid, boxes[0], 0,0, False)
  v += solutions3x3(grid, boxes[1], 3,0, False)
  v += solutions3x3(grid, boxes[2], 6,0, False)

  # second row
  v += solutions3x3(grid, boxes[3], 0,3, False)
  v += solutions3x3(grid, boxes[4], 3,3, False)
  v += solutions3x3(grid, boxes[5], 6,3, False)

  # third  row
  v += solutions3x3(grid, boxes[6], 0,6, False)
  v += solutions3x3(grid, boxes[7], 3,6, False)
  v += solutions3x3(grid, boxes[8], 6,6, False)

  v = filter(lambda v: len(v)>0, v) # remove empty vals

  return v

def read_grid():
  name = raw_input().strip()
  grid = []

  def number(x):
    "Convert char digit to integer"
    return ord(x) - ord('0')

  for n in xrange(0,9):
    grid.append(map(number, list(raw_input().strip())))

  return name, grid

def printgrid(grid):
  print "-"*25
  for y in xrange(0,9):
    print "|",
    for x in xrange(0,9):
      print grid[y][x],
      if (x % 3)==2:
        print "|",
    print
    if (y % 3)==2: print "-"*25

def zeroes(grid):
  z = 0
  for y in range(0,9):
    for x in range(0,9):
      if grid[y][x] == 0:
        z += 1
  return z

def random_cell(grid):
  "Return random empty cell"
  x = random.randrange(0,9)
  y = random.randrange(0,9)

  while grid[y][x]!=0:
    x = random.randrange(0,9)
    y = random.randrange(0,9)

  return x,y

def deduce_all(grid):
  "Deduce as many values as possible"
  grid = grid[:] # copy
  prev = zeroes(grid)+1
  while prev > zeroes(grid):
    prev = zeroes(grid)
    for y in range(0,9):
      for x in range(0,9):
        if grid[y][x]!=0: continue
        c = cands(grid, x, y)
        if len(c)==1:
          grid[y][x] = list(c)[0]
  return grid

if __name__ == "__main__":
  valsum = 0
  try:
    while True:
      name, grid = read_grid();
      #print name
      #printgrid(grid)

      g = grid

      prevz = zeroes(g)
      it = 0
      while it==0 or (zeroes(g)!=0 and prevz > zeroes(g)):
        prevz = zeroes(g)
        it += 1
        #print name, "iteration", it
        g = solve(g)
        if zeroes(g)==0:
          print "Missing values",name,":",zeroes(g)
        #printgrid(g)

      m = zeroes(g)
      if m == 0:
        val = grid[0][0]*100 + grid[0][1]*10 + grid[0][2]
        valsum += val
        print "%s: %d w/sum %d" % (name, val, valsum)

      if m > 0:
        continue
        print "STOP at", name
        printgrid(g)
        """
        At this point, run solve() but return possible values
        for each cell.  Now, for each cell, pick a possible
        value and see if that leads to a solution.
        """
       
      
        #break

  except EOFError, e:
    pass
