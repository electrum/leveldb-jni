LEVELDB=$(HOME)/src/leveldb-cpp
CFLAGS=-Wall -Werror -I$(LEVELDB)/include
LFLAGS=-L$(LEVELDB) -lleveldb

TARGETS=create dump

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

create: create.cpp Makefile
	g++ $(CFLAGS) $(LFLAGS) -o $@ $<

dump: dump.cpp Makefile
	g++ $(CFLAGS) $(LFLAGS) -o $@ $<
