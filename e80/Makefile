CXX = c++
TARGETS = e80
CXXFLAGS = -W -Wall -O3 -fomit-frame-pointer -march=core2 -msse4

run: all
	@echo --- `date`        | tee output
	@bash -c "time ./$(TARGETS)" 2>&1 | tee -a output
	@echo --- `date`         | tee -a output

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
