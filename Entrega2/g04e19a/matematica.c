#include "matematica.h"
#include <stdlib.h>

double calcular_traza(const double** mat, size_t n){
	size_t i;
	double traza;

	for(i = 0; i < n; i++)
		traza += mat[i][i];
	return traza;
}