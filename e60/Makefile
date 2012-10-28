CXX = /usr/local/bin/gcc
TARGETS = e60
CXXFLAGS = -W -Wall -O3 -fomit-frame-pointer -march=core2 -msse4

run: all
	@echo --- start --- `date`        | tee output
	@bash -c "time ./$(TARGETS)" 2>&1 | tee -a output
	@echo --- stop --- `date`         | tee -a output

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
