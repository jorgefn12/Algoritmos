CC=gcc
CFLAGS=-ansi -Wall -pedantic
OBJECTS=main.o validaciones.o errores.o

tp1: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o simpletron
	
main.o: main.c comun.h
	$(CC) -c main.c
validaciones.o: validaciones.c validaciones.h comun.h tipos.h
	$(CC) -c validaciones.c
errores.o: errores.c errores.h comun.h
	$(CC) -c errores.c
	
clean:
	rm -f *.o tp3

