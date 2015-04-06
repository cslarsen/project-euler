TARGETS := e357
CXXFLAGS = -O3 -s -W -Wall -mtune=native -march=native
PYTHON := pypy

c++: $(TARGETS)
	time ./e357

python:
	time $(PYTHON) e357.py

clean:
	rm -f *.pyc $(TARGETS)
