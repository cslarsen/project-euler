PROGRAM = e80
CXX = g++
TARGETS = $(PROGRAM)
CXXFLAGS = -DNDEBUG -W -Wall -O3 -fomit-frame-pointer -lgmpxx -lgmp

run: all
	@echo --- `date`        | tee output
	@bash -c "time ./$(PROGRAM)" 2>&1 | tee -a output
	@echo --- `date`         | tee -a output

all: $(TARGETS)

clean:
	rm -f $(TARGETS) output
