#include "procesamiento_de_estados.h"
#include "utilidades.h"
#include "tiempo.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
	int segundos;
	int hh;
	int mm;
	int ss;
	status_t st;

	printf("%s %s\n",MSJ_INGRESO_UINT,MSJ_SEC_UNITS);
	if((st = procesar_entrada_uint(&segundos)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	if((st = cnv_seg_to_hhmmss(segundos, &hh, &mm, &ss)) != ST_OK){
		imprimir_estado(st);
		return EXIT_FAILURE;
	}
	printf("%d%s%d%s%d%s\n",hh,MSJ_HOURS_UNITS,mm,MSJ_MIN_UNITS,ss,MSJ_SEC_UNITS);
	return EXIT_SUCCESS;
}