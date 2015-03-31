TARGETS = e47
CXX = llvm-g++
CXXFLAGS = -O3 -ffast-math -fomit-frame-pointer -I. -Wall

all: $(TARGETS)

run: clean all
	time nice -9 ./e47

clean:
	rm -f $(TARGETS) *.gch
