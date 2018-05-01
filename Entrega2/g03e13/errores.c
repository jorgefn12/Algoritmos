#include "errores.h"
#include <stdio.h>

void imprimir_error(status_t st){

	switch(st){
		case ST_ERR_PTR_NULO:
			fprintf(stderr,"%s\n", MSJ_ERR_PTR_NULO);
			break;
		case ST_ERR_ENTRADA_INVALIDA:
			fprintf(stderr,"%s\n", MSJ_ERR_ENTRADA_INVALIDA);
			break;
		case ST_ERR_RANGO_INVALIDO:
			fprintf(stderr,"%s\n", MSJ_ERR_RANGO_INVALIDO);
			break;
		case ST_ERR_LECTURA_TEMP:
			fprintf(stderr,"%s\n", MSJ_ERR_LECTURA_TEMP);
			break;
		case ST_ERR_LECTURA_CLASE:
			fprintf(stderr,"%s\n", MSJ_ERR_LECTURA_CLASE);
			break;
		case ST_ERR_LECTURA_DADO:
			fprintf(stderr,"%s\n", MSJ_ERR_LECTURA_DADO);
			break;
		default:
			fprintf(stderr,"%s\n", MSJ_ERR_GENERAL);
	}
}