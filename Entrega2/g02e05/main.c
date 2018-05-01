#include <stdio.h>
#include <stdlib.h>
#include "calculos_estrella.h"
#include "errores.h"
#include "utilidades.h"

int main(void){

	espectral_t clase_estrella;
	status_t st;
	float temp_estrella;

	if((st = procesar_entrada_temp(&temp_estrella)) != ST_OK){
		imprimir_error(st);
		return EXIT_FAILURE;
	}
	if((st = convert_entrada_a_clase(temp_estrella, &clase_estrella)) != ST_OK){
		imprimir_error(st);
		return EXIT_FAILURE;
	}
	imprimir_color_estrella(clase_estrella);
	return EXIT_SUCCESS;
}