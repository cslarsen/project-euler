TARGETS = e61
CXXFLAGS = -O3 -W -Wall -Wno-unused-function

run: all
	@echo ---
	@bash -c "time ./$(TARGETS)"
	@echo ---

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
