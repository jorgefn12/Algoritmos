CC=gcc
CFLAGS=-ansi -Wall -pedantic
OBJECTS=main.o

tp1: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o simpletron
	
main.o: main.c main_header.h
	$(CC) -c main.c
	
clean:
	rm -f *.o tp3

