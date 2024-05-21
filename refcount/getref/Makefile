CC=gcc
CXX=g++

CFLAGS=-g -fsanitize=address

CXXFLAGS=-g


PROGRAMS=main

all: $(PROGRAMS)

main: main.o header.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $^

header.o: header.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o $(PROGRAMS)

.PHONY: all clean
