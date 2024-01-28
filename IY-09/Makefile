# This is a Demo Makefile

CC=g++
CFLAGS=-c -Wall
LFLAGS=-lm

all: main

main: main.o
	$(CC) $(LFLAGS) main.o -o main
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

clean:
	rm -f *.o main
