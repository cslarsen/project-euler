TARGETS = e399
CXX = /usr/local-gcc/bin/g++
CXXFLAGS = -O3 -march=native -mtune=native --std=c++11 -W -Wall

run: all
	@bash -c "time ./$(TARGETS)"

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
