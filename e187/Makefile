TARGETS = e187
CXXFLAGS = -O3 -W -Wall -march=native -mtune=native

run: all
	@echo `date`
	@bash -c "time ./$(TARGETS)"
	@echo `date`

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
