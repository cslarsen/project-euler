#for n in range(1,1000):
print sum(map(lambda x: x**x % 10**10, range(1,1001)))
print sum(map(lambda x: x**x % 10**10, range(1,1001))) % 10**10
