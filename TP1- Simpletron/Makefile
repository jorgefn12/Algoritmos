CC=gcc
CFLAGS=-ansi -Wall -pedantic
OBJECTS=cargar_estructura.o dump.o ejecutar_codigo.o imprimir.o main.o validaciones.o

tp1: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o tp1
	
main.o: main.c header.h
	$(CC) -c main.c
cargar_estructura.o: cargar_estructura.c header.h
	$(CC) -c cargar_estructura.c
dump.o: dump.c header.h
	$(CC) -c dump.c
ejecutar_codigo.o: ejecutar_codigo.c header.h
	$(CC) -c ejecutar_codigo.c
imprimir.o: imprimir.c header.h
	$(CC) -c imprimir.c
validaciones.o: validaciones.c header.h
	$(CC) -c validaciones.c
	
clean:
	rm -f *.o tp3

