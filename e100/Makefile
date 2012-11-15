PROGRAM = e100
TARGETS = $(PROGRAM)
CXX = /usr/local-gcc/bin/g++
CXXFLAGS = --std=c++11 -W -Wall -DNDEBUG -Ofast -march=corei7 -mtune=corei7 -fopenmp
LDFLAGS =

run: all
	@strip $(PROGRAM)
	@date
	@bash -c "time ./$(PROGRAM) 4 10000000000"

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
