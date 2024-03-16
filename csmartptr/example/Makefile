CC=cc
CXX=g++

INC=-I ../

CFLAGS=$(INC) -O2
CXXFLAGS=$(INC) -O2

main: main.o fd.o
	$(CXX) $(CXXFLAGS) $^ -o $@

fd.o: fd.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o main
