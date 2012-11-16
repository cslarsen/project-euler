PROGRAM = e98
CXX = /usr/local-gcc/bin/g++
CXXFLAGS = -O3 -W -Wall -march=native -mtune=native -Wno-unused
LDFLAGS = 

all: $(PROGRAM)
	@./e98.py
	@#bash -c "time nice -9 ./$(PROGRAM)" | tee output

clean:
	rm -f $(PROGRAM)
