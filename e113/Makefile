TARGETS = e113
CXXFLAGS = -O3 -W -Wall -lgmpxx -lgmp

run: all
	@echo "---"
	@bash -c "time ./$(TARGETS)"
	@echo "---"

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
