
def digsum(n):
	return sum([int(i) for i in str(n)])

max = 0
for a in range(2,100):
	for b in range(1,100):
		s = digsum(a**b)
		if ( s > max ):
			print "%d^%d digsum=%d" % (a, b, s)
			max = s
