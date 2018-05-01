#ifndef MATEMATICA__H
#define MATEMATICA__H 1
#include <stdlib.h>
#include <stdio.h>

#define MSJ_ST_MATRIZ_INICIO "Matriz no verificada"
#define MSJ_ST_MATRIZ_POSITIVO "Matriz positiva"
#define MSJ_ST_MATRIZ_NO_NEGATIVO "Matriz no negativa"
#define MSJ_ST_MATRIZ_NEGATIVO "Matriz negativa"
#define MSJ_ST_MATRIZ_NO_POSITIVO "Matriz no positiva"
#define MSJ_ST_MATRIZ_CERO "Matriz no positiva y no negativa"
#define MSJ_ST_MATRIZ_INDEFINIDO "Matriz indefinida"

typedef enum{
	ST_MATRIZ_INICIO,
	ST_MATRIZ_POSITIVO,
	ST_MATRIZ_NO_NEGATIVO,
	ST_MATRIZ_NEGATIVO,
	ST_MATRIZ_NO_POSITIVO,
	ST_MATRIZ_CERO,
	ST_MATRIZ_INDEFINIDO
} status_matriz_t;

double calcular_traza(const double** mat, size_t n);
void sumar_int_a_matrizd(double** mat, size_t fil, size_t col, int suma);
void multip_int_a_matrizd(double** mat, size_t fil, size_t col, int mult);

/*Asume que las matrices están bien dimensionadas y validadas, fil y col pertenecen a mat 1*/
void trasponer_matrizd(double** mat1, size_t fil, size_t col,double** mat2);
void imprimir_positividad_matriz(double ** mat, size_t fil, size_t col);

#endif