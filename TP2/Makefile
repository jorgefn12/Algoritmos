CC=gcc
CFLAGS=-ansi -Wall -pedantic
OBJECTS=main.o validaciones.o

tp1: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o simpletron
	
main.o: main.c main_header.h
	$(CC) -c main.c
validaciones.o: validaciones.c validaciones.h main_header.h
	$(CC) -c validaciones.c
	
clean:
	rm -f *.o tp3

