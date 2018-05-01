#include "calculos_cilindro.h"
#include "errores.h"
#include "utilidades.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){

	float radio_cilindro, altura_cilindro;
	status_t st;

	if((st = procesar_entrada_cilindro(&radio_cilindro, &altura_cilindro)) != ST_OK){
		imprimir_error(st);
		return EXIT_FAILURE;
	} 
	imprimir_medidas_cilindro(radio_cilindro, altura_cilindro);
	return EXIT_SUCCESS;
}