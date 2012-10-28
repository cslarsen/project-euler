TARGETS = e49
CXX = g++
CXXFLAGS = -O6 -ffast-math -fomit-frame-pointer -I. -Wall

run: all
	time nice -9 ./$(TARGETS)

all: $(TARGETS)

clean:
	rm -f $(TARGETS) *.gch
