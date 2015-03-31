TARGETS = e85
CXXFLAGS = -O3 -W -Wall

run: all
	@bash -c "time ./$(TARGETS)"

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
