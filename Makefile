CXX = g++ -std=c++11 -g -O2

all: heap

heap: tests.o
	$(CXX) tests.o -o heap

tests.o: tests.cpp
	$(CXX) -c tests.cpp

.PHONY: clean

clean:
	rm -rf *o heap
