CXX = /usr/local-gcc/bin/g++
CXXFLAGS = -O3 -W -Wall -march=native -mtune=native -fopenmp
LDFLAGS = -lgmpxx -lgmp

all: e94
	bash -c "time nice -9 ./e94 333333334" | tee output

clean:
	rm -f e94
