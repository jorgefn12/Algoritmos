#include "procesamiento_de_estados.h"
#include "utilidades.h"
#include "matematica.h"
#include <stdio.h>
#include <stdlib.h>


int main(void){
	double **MATRIZ1;
	double **MATRIZ2;
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
	if(filas < 1 || columnas < 1){
		imprimir_estado(ST_ERR_FORMATO_INVALIDO);
		return EXIT_FAILURE;
	}
	if((st = crear_matd_dinamic(&MATRIZ1, filas, columnas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	if((st = cargar_stdin_matd(MATRIZ1, filas, columnas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}


	if((st = crear_matd_dinamic(&MATRIZ2, columnas, filas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	trasponer_matrizd(MATRIZ1, filas, columnas,MATRIZ2);

	imprimir_matd((const double **)MATRIZ2, columnas, filas);

	return EXIT_SUCCESS;
}