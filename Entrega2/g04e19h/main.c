#include "procesamiento_de_estados.h"
#include "utilidades.h"
#include "matematica.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
	double **matriz1;
	status_t st;
	int filas1;
	int columnas1;

	puts(MSJ_INGRESO_CANT_FIL);
	if((st = procesar_entrada_int(&filas1)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	puts(MSJ_INGRESO_CANT_COL);
	if((st = procesar_entrada_int(&columnas1)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	if(filas1 < 1 || columnas1 < 1){
		imprimir_estado(ST_ERR_FORMATO_INVALIDO);
		return EXIT_FAILURE;
	}
	if((st = crear_matd_dinamic(&matriz1, filas1, columnas1)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	if((st = cargar_stdin_matd(matriz1, filas1, columnas1)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}

	printf("%.2f\n", calc_max_elemento_matd((const double**)matriz1, filas1, columnas1));
	
	return EXIT_SUCCESS;
}