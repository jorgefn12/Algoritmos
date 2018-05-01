#include "procesamiento_de_estados.h"
#include "utilidades.h"
#include "matematica.h"
#include <stdio.h>
#include <stdlib.h>


int main(void){
	double **MATRIZ;
	status_t st;
	int filas;
	int columnas;

	puts(MSJ_INGRESO_CANT_FIL);
	if((st = procesar_entrada_int(&filas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	puts(MSJ_INGRESO_CANT_COL);
	if((st = procesar_entrada_int(&columnas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	if(filas != columnas || filas < 1){
		imprimir_estado(ST_ERR_FORMATO_INVALIDO);
		return EXIT_FAILURE;
	}
	if((st = crear_matd_dinamic(&MATRIZ, filas, columnas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	if((st = cargar_stdin_matd(MATRIZ, filas, columnas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	printf("%.2f\n", calcular_traza((const double **)MATRIZ, filas));

	return EXIT_SUCCESS;
}