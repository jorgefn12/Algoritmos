#include "matematica.h"
#include "procesamiento_de_estados.h"
#include <stdlib.h>
#include <stdio.h>

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

void trasponer_matrizd(const double** mat1, size_t fil1, size_t col1,double** mat2){
	size_t i,j;

	for(i = 0; i < fil1; i++){
		for(j = 0; j < col1; j++){
			mat2[j][i] = mat1[i][j];
		}
	}
}

void imprimir_positividad_matriz(const double ** mat, size_t fil, size_t col){
	status_matriz_t st_matriz;
	size_t i, j;

	st_matriz = ST_MATRIZ_INICIO;
	for(i = 0; i < fil; i++){
		for(j = 0; j < col; j++){
			switch(st_matriz){
				case ST_MATRIZ_INICIO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_POSITIVO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_NEGATIVO;
					else
						st_matriz = ST_MATRIZ_CERO;
					break;
				case ST_MATRIZ_POSITIVO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_POSITIVO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_INDEFINIDO;
					else
						st_matriz = ST_MATRIZ_NO_NEGATIVO;
					break;
				case ST_MATRIZ_NO_NEGATIVO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_NO_NEGATIVO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_INDEFINIDO;
					else
						st_matriz = ST_MATRIZ_NO_NEGATIVO;
					break;
				case ST_MATRIZ_NEGATIVO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_INDEFINIDO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_NEGATIVO;
					else
						st_matriz = ST_MATRIZ_NO_POSITIVO;
					break;
				case ST_MATRIZ_NO_POSITIVO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_INDEFINIDO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_NO_POSITIVO;
					else
						st_matriz = ST_MATRIZ_NO_POSITIVO;
					break;
				case ST_MATRIZ_CERO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_NO_NEGATIVO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_NO_POSITIVO;
					else
						st_matriz = ST_MATRIZ_CERO;
					break;
				case ST_MATRIZ_INDEFINIDO:
					puts(MSJ_ST_MATRIZ_INDEFINIDO);
					return;
				default:
					fprintf(stderr,"%s\n",MSJ_ERR_GENERAL);
					return;
			}
		}
	}
	switch(st_matriz){
		case ST_MATRIZ_INICIO:
			puts(MSJ_ST_MATRIZ_INICIO);
			break;
		case ST_MATRIZ_POSITIVO:
			puts(MSJ_ST_MATRIZ_POSITIVO);
			break;
		case ST_MATRIZ_NO_NEGATIVO:
			puts(MSJ_ST_MATRIZ_NO_NEGATIVO);
			break;
		case ST_MATRIZ_NEGATIVO:
			puts(MSJ_ST_MATRIZ_NEGATIVO);
			break;
		case ST_MATRIZ_NO_POSITIVO:
			puts(MSJ_ST_MATRIZ_NO_POSITIVO);
			break;
		case ST_MATRIZ_CERO:
			puts(MSJ_ST_MATRIZ_CERO);
			break;
		case ST_MATRIZ_INDEFINIDO:
			puts(MSJ_ST_MATRIZ_INDEFINIDO);
			break;
		default:
			fprintf(stderr,"%s\n",MSJ_ERR_GENERAL);
	}
}

double calc_determ_matd3x3(const double** mat, size_t fil){
	double determ;

	switch(fil){
		case OPT_CNT_FILAS_1:
			determ = mat[0][0];
			break;
		case OPT_CNT_FILAS_2:
			determ =  mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];
			break;
		case OPT_CNT_FILAS_3:
			determ = mat[0][0]*mat[1][1]*mat[2][2]+mat[0][1]*mat[1][2]*mat[2][0]+mat[0][2]*mat[1][0]*mat[2][1]-mat[0][2]*mat[1][1]*mat[2][0]-mat[0][1]*mat[1][0]*mat[2][2]-mat[0][0]*mat[2][1]*mat[1][2];
			break;
	}
	return determ;
}

void multiplicar_matdxmatd(const double** mat1, size_t fil1, size_t col1,const double** mat2, size_t col2, double** mat3){
	size_t i,j,r;

	for(i = 0; i < fil1; i++){
		for(j = 0; j < col2; j++){
			for(r = 0, mat3[i][j] = 0; r < fil1; r++){
				mat3[i][j] += mat1[i][r] * mat2[r][j];
			}
		}
	}
}

double calc_max_elemento_matd(const double** mat, size_t fil, size_t col){
	size_t i,j;
	double max_elemento;

	for(i = 0, max_elemento = mat[0][0]; i < fil; i++){
		for(j = 1; j< col; j++){
			if(max_elemento < mat[i][j])
				max_elemento = mat[i][j];
		}
	}
	return max_elemento;
}

double get_abs_d(double n){
	return (n > 0) ? n : -n;
}

double get_norma1_matd(const double** mat, size_t fil, size_t col){
	size_t i,j;
	double sum_col;
	double norma1;

	for(j = 0, norma1 = get_abs_d(mat[0][0]); j < col; j++){
		for(i = 0, sum_col = 0 ; i < fil; i++){
			sum_col += get_abs_d(mat[i][j]);
		}
		if(norma1 < sum_col)
			norma1 = sum_col;
	}
	return norma1;
}