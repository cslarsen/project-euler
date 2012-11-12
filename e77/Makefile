PROGRAM = e77
CXX = /usr/local-gcc/bin/g++
TARGETS = $(PROGRAM)
CXXFLAGS = -O3 -march=corei7 -W -Wall

run: all
	@echo --- `date` | tee output
	@bash -c "time ./$(PROGRAM)" 2>&1 | tee -a output
	@echo --- `date` | tee -a output

all: $(TARGETS)

clean:
	rm -f $(TARGETS) output
