PROGRAM = e100
TARGETS = $(PROGRAM)
CXX = /usr/local-gcc/bin/g++
CXXFLAGS = -W -Wall -Ofast -march=corei7 -mtune=corei7 --std=c++11
LDFLAGS = -lgmpxx -lgmp

run: all
	@strip $(PROGRAM)
	@date
	@bash -c "time ./$(PROGRAM)"

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
