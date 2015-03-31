def fac(n):
	ret = 1
	for a in range(2,n+1):
		ret *= a
	return ret

def sof(n):
	s = str(n)
	sum = 0
	for a in s:
		sum = sum + fac(int(a))
	return sum

sum = 0
for n in range(3,10**5):
	ss = sof(n)
	if ss == n:
		sum = sum + n
		print n, sum
