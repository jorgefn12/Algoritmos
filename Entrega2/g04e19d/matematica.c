#include "matematica.h"
#include <stdlib.h>

double calcular_traza(const double** mat, size_t n){
	size_t i;
	double traza;

	for(i = 0; i < n; i++)
		traza += mat[i][i];
	return traza;
}

void sumar_int_a_matrizd(double** mat, size_t fil, size_t col, int suma){
	size_t i, j;

	for(i = 0; i < fil; i++){
		for(j = 0; j < col; j++)
			mat[i][j] += suma;
	}
}

void multip_int_a_matrizd(double** mat, size_t fil, size_t col, int mult){
	size_t i, j;

	for(i = 0; i < fil; i++){
		for(j = 0; j < col; j++)
			mat[i][j] *= mult;
	}
}

void trasponer_matrizd(double** mat1, size_t fil, size_t col,double** mat2){
	size_t i,j;

	for(i = 0; i < fil; i++){
		for(j = 0; j < col; j++){
			mat2[j][i] = mat1[i][j];
		}
	}
}