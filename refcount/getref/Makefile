CC=gcc
CXX=g++

CFLAGS=-g -fsanitize=address

CXXFLAGS=-g


PROGRAMS=main shareptr

all: $(PROGRAMS)

main: main.o header.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $^

header.o: header.c
	$(CC) $(CFLAGS) -c -o $@ $^

shareptr: shareptr.o
	$(CXX) $(CXXFLAGS) -o $@ $^

shareptr.o: shareptr.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f *.o $(PROGRAMS)

.PHONY: all clean
