TARGET = e74
CXXFLAGS = -W -Wall -O3

run: all
	@echo start `date`
	@bash -c 'time ./$(TARGET)'
	@echo stop `date`

all: $(TARGET)
	strip $(TARGET)

clean:
	rm -f $(TARGET)
