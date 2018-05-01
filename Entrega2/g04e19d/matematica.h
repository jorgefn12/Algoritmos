#ifndef MATEMATICA__H
#define MATEMATICA__H 1
#include <stdlib.h>

double calcular_traza(const double** mat, size_t n);
void sumar_int_a_matrizd(double** mat, size_t fil, size_t col, int suma);
void multip_int_a_matrizd(double** mat, size_t fil, size_t col, int mult);

/*Asume que las matrices están bien dimensionadas y validadas, fil y col pertenecen a mat 1*/
void trasponer_matrizd(double** mat1, size_t fil, size_t col,double** mat2);


#endif