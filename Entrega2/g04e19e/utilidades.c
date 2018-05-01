#include "utilidades.h"
#include "procesamiento_de_estados.h"
#include <stdio.h>
#include <stdlib.h>

void limpiar_buffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

void cargar_rnd_vctd(double v[], size_t n){
	size_t i;
	for(i = 0; i < n; i++){
		v[i] = rand();
	}
}

status_t cargar_stdin_vctd(double v[], size_t n){
	size_t i;
	for(i = 0; i < n; i++){
		printf("%s %c%ld%c%ld%c ", MSJ_INGRESO_INT,'[',i+1,'/',n,']');
		if(scanf("%lf", &v[i]) != 1)
			return ST_ERR_ENTRADA_INVALIDA;
		limpiar_buffer();
	}
	return ST_OK;
}

status_t cargar_stdin_matd(double **mat, size_t fil, size_t col){
	size_t i,j;

	for(i = 0; i < fil; i++){
		for(j = 0; j < col; j++){
			printf("%s %s%ld%s%ld%c ", MSJ_INGRESO_INT,"[Fila:",i+1,"|Col:",j+1,']');
			if(scanf("%lf", &mat[i][j]) != 1)
				return ST_ERR_ENTRADA_INVALIDA;
			limpiar_buffer();
		}
	}
	return ST_OK;
}

status_t crear_matd_dinamic(double*** mat, size_t fil, size_t col){
	size_t i;

	if(mat == NULL)
		return ST_ERR_PTR_NULO;
	if((*mat = (double **)malloc(sizeof(double*) * fil)) == NULL)
		return ST_ERR_MEMORIA;
	for(i = 0; i < fil; i++){
		if(((*mat)[i] = (double *)malloc(sizeof(double) * col)) == NULL)
			return ST_ERR_MEMORIA;
	}
	return ST_OK;
}

void cargar_rnd_matd(double **mat, size_t fil, size_t col){
	size_t i, j;
	for(i = 0; i < fil; i++){
		for(j = 0; j < col; j++)
			mat[i][j] = rand(); 
	}
}

status_t procesar_entrada_int(int * entrada){
	if(entrada == NULL)
		return ST_ERR_PTR_NULO;
	if(scanf("%d", entrada) != 1)
		return ST_ERR_ENTRADA_INVALIDA;
	limpiar_buffer();
	return ST_OK;
}

void imprimir_vctd(const double v[], size_t n){
	size_t i;
	for(i = 0; i < n; i++){
		printf("%.2f ", v[i]);
	}
	putchar('\n');
}

void imprimir_matd(const double** mat, size_t fil, size_t col){
	size_t i, j;
	for(i = 0; i < fil; i++){
		for(j = 0; j < col; j++){
			printf("%.2f ", mat[i][j]);
		}
		putchar('\n');
	}
}