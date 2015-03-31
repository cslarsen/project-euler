print str(reduce(lambda x,y:x+y, map(lambda x:x**x, range(1,1000))))[-10:]
