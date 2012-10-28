TARGETS = e204
CXXFLAGS = -O3 -W -Wall

run: all
	@echo ---
	@bash -c "time ./$(TARGETS)"
	@echo ---

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
