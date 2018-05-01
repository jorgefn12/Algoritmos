#include "procesamiento_de_estados.h"
#include "utilidades.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
	int* v;
	status_t st;
	int columnas;
	int posicion;

	puts(MSJ_INGRESO_CANT_COL);
	if((st = procesar_entrada_int(&columnas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	if(columnas < 1){
		imprimir_estado(ST_ERR_FORMATO_INVALIDO);
		return EXIT_FAILURE;
	}
	if((st = crear_vcti_dinamic(&v, columnas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	if((st = cargar_stdin_vcti(v, columnas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}

	if((posicion = busqueda_binaria_vectord((const int*)v,columnas,10,1,3)) < 0){
		imprimir_estado(ST_VALOR_NO_ENCONTRADO);
		return EXIT_FAILURE;
	}
	printf("%d\n", posicion);	

	return EXIT_SUCCESS;
}