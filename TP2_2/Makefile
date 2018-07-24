CC=gcc
CFLAGS=-ansi -Wall -pedantic
OBJECTS=main.o argumentos.o dump.o errores.o lectores.o listas.o memoria.o simpletron.o

tp: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o simpletron
	
main.o: main.c comun.h tipos.h memoria.h listas.h argumentos.h errores.h simpletron.h lectores.h dump.h
	$(CC) -c main.c
argumentos.o: argumentos.c argumentos.h tipos.h
	$(CC) -c argumentos.c
dump.o: dump.c dump.h simpletron.h memoria.h argumentos.h
	$(CC) -c dump.c
errores.o: errores.c tipos.h errores.h argumentos.h simpletron.h lectores.h
	$(CC) -c errores.c
lectores.o: lectores.c tipos.h lectores.h argumentos.h listas.h comun.h
	$(CC) -c lectores.c
listas.o: listas.c listas.h tipos.h	
	$(CC) -c listas.c
memoria.o: memoria.c memoria.h tipos.h
	$(CC) -c memoria.c
simpletron.o: simpletron.c memoria.h tipos.h simpletron.h argumentos.h comun.h errores.h dump.h
	$(CC) -c simpletron.c
clean:
	rm -f *.o tp

