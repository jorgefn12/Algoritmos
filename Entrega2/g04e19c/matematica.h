#ifndef MATEMATICA__H
#define MATEMATICA__H 1
#include <stdlib.h>

double calcular_traza(const double** mat, size_t n);
void sumar_int_a_matrizd(double** mat, size_t fil, size_t col, int suma);
void multip_int_a_matrizd(double** mat, size_t fil, size_t col, int mult);

#endif