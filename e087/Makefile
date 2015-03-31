TARGETS = e87
CXXFLAGS = -W -Wall -O3 -lgmpxx -lgmp

run: all
	@echo -- `date`
	@bash -c "time ./$(TARGETS)"
	@echo -- `date`

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

