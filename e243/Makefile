TARGET = e243
CXXFLAGS = -W -Wall -O3 -march=native -mtune=native

run: all
	@echo Start: `date`
	@echo ---
	@bash -c 'time ./$(TARGET)'
	@echo ---
	@echo Stop: `date`

all: $(TARGET)

clean:
	rm -f $(TARGET)
