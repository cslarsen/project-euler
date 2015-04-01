TARGETS = sha1.o e400.o e400
CXXFLAGS = --std=c++11 -W -Wall \
					 -DNDEBUG -O3 \
					 -fomit-frame-pointer \
					 -march=native -mtune=native \
					 -msse4 -lgmpxx -lgmp

run: all
	@echo --- `date`        | tee output
	@bash -c "time ./e400" 2>&1 | tee -a output
	@echo --- `date`         | tee -a output

all: $(TARGETS)

sha1.o: sha1.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

e400: e400.o sha1.o
	$(CXX) $(CXXFLAGS) sha1.o e400.o -o $@


clean:
	rm -f $(TARGETS)
