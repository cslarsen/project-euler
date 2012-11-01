CXX = /usr/local-gcc/bin/c++ --std=c++11
TARGETS = sha1.o e400
CXXFLAGS = -W -Wall -O3 -fomit-frame-pointer -march=corei7 -msse4 #-lgmpxx -lgmp

run: all
	@echo --- `date`        | tee output
	@bash -c "time ./e400" 2>&1 | tee -a output
	@echo --- `date`         | tee -a output

all: $(TARGETS)

sha1.o: sha1.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

e400: e400.cpp sha1.o
	$(CXX) $(CXXFLAGS) sha1.o e400.cpp -o $@


clean:
	rm -f $(TARGETS)
