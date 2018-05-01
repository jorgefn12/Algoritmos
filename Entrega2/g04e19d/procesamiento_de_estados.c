#include "procesamiento_de_estados.h"
#include <stdio.h>

void imprimir_estado(status_t st){

	switch(st){
		case ST_ERR_PTR_NULO:
			fprintf(stderr,"%s\n", MSJ_ERR_PTR_NULO);
			break;
		case ST_ERR_MEMORIA:
			fprintf(stderr,"%s\n", MSJ_ERR_MEMORIA);
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
		case ST_ERR_FORMATO_INVALIDO:
			fprintf(stderr,"%s\n", MSJ_ERR_FORMATO_INVALIDO);
			break;
		case ST_VALOR_NO_ENCONTRADO:
			printf("%s\n", MSJ_VALOR_NO_ENCONTRADO);
			break;
		default:
			fprintf(stderr,"%s\n", MSJ_ERR_GENERAL);
	}
}