TARGETS = e160
CXXFLAGS = -W -Wall -O3

run: all
	@echo -- `date`
	@bash -c "time ./$(TARGETS)"
	@echo -- `date`

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

