PROGRAM = e68
TARGETS = $(PROGRAM)
CXXFLAGS = -W -Wall -O3 -fomit-frame-pointer --std=c++11 -march=native -mtune=native

run: all
	@echo --- `date` | tee output
	@bash -c "time ./$(PROGRAM)" 2>&1 | tee -a output
	@echo --- `date` | tee -a output

all: $(TARGETS)

clean:
	rm -f $(TARGETS) output
