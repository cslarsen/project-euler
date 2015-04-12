CXXFLAGS := -O3 -W -Wall -mtune=native -march=native -ffast-math
PYTHON := pypy
TARGETS := e387

c++: $(TARGETS)
	time -p ./e387

python:
	time -p $(PYTHON) e387.py

clean:
	rm -f $(TARGETS) *.pyc
