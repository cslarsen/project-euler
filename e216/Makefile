CXXFLAGS = -O3 -march=core2 -mtune=core2 -fast -ffast-math -fomit-frame-pointer -finline-functions
TARGETS = miller-rabin.o mersenne-twister.o test-pi

all: $(TARGETS)

check: test-pi
	time nice -9 ./test-pi

test-pi: miller-rabin.o mersenne-twister.o

eul: miller-rabin.o mersenne-twister.o

clean:
	rm -f $(TARGETS)
