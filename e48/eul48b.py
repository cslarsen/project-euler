#print str(reduce(lambda x,y:x+y, map(lambda x:x**x, range(1,1000))))[-10:]
#print str(reduce(lambda x,y:x**x+y**y, range(1,1000)))[-10:]
print str(sum(map(lambda x: x**x, range(1,1000))))[-10:]
