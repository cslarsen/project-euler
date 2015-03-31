s = ""
max = 1000000

for n in range(1,max+1):
	s += str(n)

def d(n):
	return int(s[n-1])

prod=1
for a in range(0,7):
	prod *= d(10**a)
print prod

