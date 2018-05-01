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
	int mult;
	
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
	if((st = crear_matd_dinamic(&MATRIZ, filas, columnas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	if((st = cargar_stdin_matd(MATRIZ, filas, columnas)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	puts(MSJ_INGRESO_INT_MULT);
	if((st = procesar_entrada_int(&mult)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	multip_int_a_matrizd(MATRIZ, filas, columnas, mult);
	imprimir_matd((const double **)MATRIZ, filas, columnas);
	return EXIT_SUCCESS;
}