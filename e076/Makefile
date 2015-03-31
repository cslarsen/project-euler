ARCH = corei7
CXXFLAGS = -O4 -fomit-frame-pointer -march=$(ARCH) -mtune=$(ARCH) -ffast-math -fast -fwhole-program -fstrict-aliasing -momit-leaf-frame-pointer -fno-tree-pre -falign-loops
CFLAGS = $(CXXFLAGS)
CC = cc
TARGETS = sum3

all: $(TARGETS)

run: all
	./sum3

clean:
	rm -f $(TARGETS)
