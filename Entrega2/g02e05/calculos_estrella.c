#include "calculos_estrella.h"
#include "errores.h"
#include "utilidades.h"
#include <stdio.h>

status_t procesar_entrada_temp(float * temp){

	float entrada;

	if(!temp)
		return ST_ERR_PTR_NULO;
	puts(MSJ_PROGRAMA_ESTRELLA);
	puts(MSJ_INGRESO_TEMP);
	if(scanf("%f", &entrada) != 1)
		return ST_ERR_ENTRADA_INVALIDA;
	limpiar_buffer();
	if(entrada > MAX_RANGO_CLASE_O || entrada < MIN_RANGO_CLASE_M)
		return ST_ERR_RANGO_INVALIDO;
	*temp = entrada;
	return ST_OK;
}

status_t convert_entrada_a_clase(float temp, espectral_t * clase){

	if(!clase)
		return ST_ERR_PTR_NULO;
	if(temp <= MAX_RANGO_CLASE_O && temp >= MIN_RANGO_CLASE_O)
		*clase = CLASE_O;
	else if(temp < MIN_RANGO_CLASE_O && temp >= MIN_RANGO_CALSE_B)
		*clase = CLASE_B;
	else if(temp < MIN_RANGO_CALSE_B && temp >= MIN_RANGO_CLASE_A)
		*clase = CLASE_A;
	else if(temp < MIN_RANGO_CLASE_A && temp >= MIN_RANGO_CLASE_F)
		*clase = CLASE_F;
	else if(temp < MIN_RANGO_CLASE_F && temp >= MIN_RANGO_CALSE_G)
		*clase = CLASE_G;
	else if(temp < MIN_RANGO_CALSE_G && temp >= MIN_RANGO_CLASE_K)
		*clase = CLASE_K;
	else if(temp < MIN_RANGO_CLASE_K && temp >= MIN_RANGO_CLASE_M)
		*clase = CLASE_M;
	else
		return ST_ERR_LECTURA_TEMP;
	return ST_OK;
}

void imprimir_color_estrella(espectral_t clase){

	switch(clase){
		case CLASE_O:
			puts(MSJ_COLOR_CLASE_O);
			break;
		case CLASE_B:
			puts(MSJ_COLOR_CLASE_B);
			break;
		case CLASE_A:
			puts(MSJ_COLOR_CLASE_A);
			break;
		case CLASE_F:
			puts(MSJ_COLOR_CLASE_F);
			break;
		case CLASE_G:
			puts(MSJ_COLOR_CLASE_G);
			break;
		case CLASE_K:
			puts(MSJ_COLOR_CLASE_K);
			break;
		case CLASE_M:
			puts(MSJ_COLOR_CLASE_M);
			break;
		default:
			fprintf(stderr, "%s\n", MSJ_ERR_LECTURA_CLASE);
	}
}