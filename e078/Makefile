PROGRAM = e78
CXXFLAGS = --std=c++11 -W -Wall -O3 -fomit-frame-pointer -march=native -mtune=native
LDFLAGS = -lgmpxx -lgmp

all: $(PROGRAM)
	@bash -c "time ./$(PROGRAM)"

clean:
	rm -f $(PROGRAM) *.pyc
