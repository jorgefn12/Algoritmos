#include "procesamiento_de_estados.h"
#include "utilidades.h"
#include "matematica.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
	double **matriz1;
	double **matriz2;
	double **matriz3;
	status_t st;
	int filas1, filas2;
	int columnas1, columnas2;

	/*CREAR MATRIZ A POR STDIN*/
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

	/*CREAR MATRIZ B POR STDIN*/
	puts(MSJ_INGRESO_CANT_FIL);
	if((st = procesar_entrada_int(&filas2)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	puts(MSJ_INGRESO_CANT_COL);
	if((st = procesar_entrada_int(&columnas2)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	if(filas2 < 1 || columnas2 < 1){
		imprimir_estado(ST_ERR_FORMATO_INVALIDO);
		return EXIT_FAILURE;
	}
	if(columnas1 != filas2){
		imprimir_estado(ST_ERR_DIMENSION_MISMATCH);
		return EXIT_FAILURE;
	}
	if((st = crear_matd_dinamic(&matriz2, filas2, columnas2)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	if((st = cargar_stdin_matd(matriz2, filas2, columnas2)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}

	/*CREAR MATRIZ C*/
	if((st = crear_matd_dinamic(&matriz3, filas1, columnas2)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}

	multiplicar_matdxmatd((const double**)matriz1, filas1, columnas1,(const double**)matriz2, columnas2, matriz3);
	imprimir_matd((const double **)matriz3, filas1, columnas2);
	
	return EXIT_SUCCESS;
}