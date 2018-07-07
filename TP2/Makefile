CC=gcc
CFLAGS=-ansi -Wall -pedantic
OBJECTS=main.o validaciones.o errores.o carga.o dump.o

tp1: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o simpletron
	
main.o: main.c comun.h tipos.h validaciones.h
	$(CC) -c main.c
validaciones.o: validaciones.c validaciones.h comun.h tipos.h
	$(CC) -c validaciones.c
errores.o: errores.c errores.h comun.h
	$(CC) -c errores.c
carga.o: carga.c tipos.h comun.h
	$(CC) -c carga.c
dump.o: dump.c tipos.h
	$(CC) -c dump.c
	
	
clean:
	rm -f *.o tp3

