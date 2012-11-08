#!/usr/bin/env python

def show(l):
  for key in l.keys():
    print "%4.4s %s" % (key, l[key])

sum4 = {}
for a in range(1,5):
  for b in range(1,5):
    for c in range(1,5):
      for d in range(1,5):
        for e in range(1,5):
          for f in range(1,5):
            for g in range(1,5):
              for h in range(1,5):
                for i in range(1,5):
                  s = a+b+c+d+e+f+g+h+i
                  if not s in sum4: sum4[s] = 0
                  sum4[s] += 1

freq4 = {}
for s in sum4.keys():
  freq = sum4[s]
  if not freq in freq4: freq4[freq] = []
  freq4[freq].append(s)

#print "Sum->freq for Peter"
#show(sum4)
#print ""
#print "Freq->sum for Peter"
#show(freq4)

sum6 = {}
for a in range(1,7):
  for b in range(1,7):
    for c in range(1,7):
      for d in range(1,7):
        for e in range(1,7):
          for f in range(1,7):
            s = a+b+c+d+e+f
            if not s in sum6: sum6[s] = 0
            sum6[s] += 1

freq6 = {}
for s in sum6.keys():
  freq = sum6[s]
  if not freq in freq6: freq6[freq] = []
  freq6[freq].append(s)

#print ""
#print "---"
#print ""
#print "Sum->freq for Colin"
#show(sum6)
#print ""
#print "Freq->sum for Colin"
#show(freq6)

#print ""
#print "Number of possible rolls for Peter, 4^9 =", 4**9
#print sum([k*len(v) for k, v in zip(freq4.keys(), freq4.values())])
pgames = 4**9

#print "Number of possible rolls for colin"
cgames = 6**6
#print cgames

#print "Total number of non-unique games:"
games = cgames*pgames
#print games

#print "Now, for each combination of sums, count how many Peter wins"
wins = 0
for psum in sum4:
  count = sum4[psum]
  #print "sum of", psum, "is reached", count, "times for PETER"
  # for each of Colin's games, how many games will this win?
  SKIP = False
  for csum in sum6:
    count6 = sum6[csum]
    #print "sum of", csum, "is reached", count6, "times for Colin"
    gcount = count6*count
    #print "  there are", gcount, "such games"
    # will peter win these games?
    #print "  WILL Peter win these games?",
    if psum > csum:
      #print "YES"
      wins += gcount
    else:
      SKIP = True
      break
  if SKIP:
    continue

print "Out of", games, "games, Peter will win", wins, "of them"
prob = float(wins)/float(games)
print "His probability of winning is thus", prob
print "Rounded to 7 decimals: %.7f" % prob
print "(Expected solution:    0.5731441)"
