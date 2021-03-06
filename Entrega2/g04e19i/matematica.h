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
#define OPT_CNT_FILAS_1 1
#define OPT_CNT_FILAS_2 2
#define OPT_CNT_FILAS_3 3

typedef enum{
	ST_MATRIZ_INICIO,
	ST_MATRIZ_POSITIVO,
	ST_MATRIZ_NO_NEGATIVO,
	ST_MATRIZ_NEGATIVO,
	ST_MATRIZ_NO_POSITIVO,
	ST_MATRIZ_CERO,
	ST_MATRIZ_INDEFINIDO
} status_matriz_t;



/*Las funciones asumen que las matrices/vectores/numeros les llegan bien dimensionados y validados*/
double get_abs_d(double n);
double calcular_traza(const double** mat, size_t n);
void sumar_int_a_matrizd(double** mat, size_t fil, size_t col, int suma);
void multip_int_a_matrizd(double** mat, size_t fil, size_t col, int mult);
void trasponer_matrizd(const double** mat1, size_t fil1, size_t col1,double** mat2);
void imprimir_positividad_matriz(const double ** mat, size_t fil, size_t col);
double calc_determ_matd3x3(const double** mat, size_t fil);
void multiplicar_matdxmatd(const double** mat1, size_t fil1, size_t col1,const double** mat2, size_t col2, double** mat3);
double calc_max_elemento_matd(const double** mat, size_t fil, size_t col);

double get_norma1_matd(const double** mat, size_t fil, size_t col);


#endif