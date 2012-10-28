TARGET = e104-fast
CXXFLAGS = -W -Wall -fomit-frame-pointer -ffast-math -O3 -DNDEBUG -lgmpxx -lgmp

run: all
	@echo start `date`
	@bash -c 'time ./$(TARGET)'
	@echo stop `date`

all: $(TARGET)

clean:
	rm -f $(TARGET)
