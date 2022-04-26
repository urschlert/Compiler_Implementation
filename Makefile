CC = g++
CFLAGS = -g -Wall -std=c++11
OBJS = main parser scanner testTree semantics

frontEnd: main.o parser.o scanner.o testTree.o semantics.o
	$(CC) $(CFLAGS) -o statSem main.o parser.o scanner.o testTree.o semantics.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f statSem main.o parser.o scanner.o testTree.o semantics.o
