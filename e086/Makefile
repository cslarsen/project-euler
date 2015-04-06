CXXFLAGS = -O3 -mtune=native -march=native -fomit-frame-pointer -ffast-math -s
TARGETS := e86
PYTHON := pypy

default:
	@echo "make python # runs Python version"
	@echo "make c++    # runs C++ version"

python:
	time $(PYTHON) e86.py

c++: $(TARGETS)
	time ./e86

clean:
	rm -f *.pyc $(TARGETS)
