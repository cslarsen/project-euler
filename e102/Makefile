TARGETS = e102
CXXFLAGS = -O3 -W -Wall

run: all
	@echo --- `date`
	@bash -c "time ./$(TARGETS)"
	@echo --- `date`

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
