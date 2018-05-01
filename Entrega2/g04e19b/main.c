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
	int suma;
	
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
	puts(MSJ_INGRESO_INT_SUMA);
	if((st = procesar_entrada_int(&suma)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	sumar_int_a_matriz(MATRIZ, filas, columnas, suma);
	imprimir_matd((const double **)MATRIZ, filas, columnas);
	return EXIT_SUCCESS;
}