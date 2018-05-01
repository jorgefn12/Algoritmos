#ifndef CALCULOS_ESTRELLA__H
#define CALCULOS_ESTRELLA__H 1
#include "errores.h"
#include "utilidades.h"
#include <stdio.h>

#define MAX_RANGO_CLASE_O 50000
#define MIN_RANGO_CLASE_O 28000
#define MIN_RANGO_CALSE_B 9600
#define MIN_RANGO_CLASE_A 7100
#define MIN_RANGO_CLASE_F 5700
#define MIN_RANGO_CALSE_G 4600
#define MIN_RANGO_CLASE_K 3200
#define MIN_RANGO_CLASE_M 1700
#define MSJ_PROGRAMA_ESTRELLA "El programa le devolverá el color de la estrella de acuerdo a su temperatura"
#define MSJ_INGRESO_TEMP "Ingrese un valor de temperatura en grados Kelvin [1700 - 50000]"
#define MSJ_COLOR_CLASE_O "Azul"
#define MSJ_COLOR_CLASE_B "Blanco azulado"
#define MSJ_COLOR_CLASE_A "Blanco"
#define MSJ_COLOR_CLASE_F "Blanco amarillento"
#define MSJ_COLOR_CLASE_G "Amarillo"
#define MSJ_COLOR_CLASE_K "Naranja"
#define MSJ_COLOR_CLASE_M "Rojo"

typedef enum{
	CLASE_O,
	CLASE_B,
	CLASE_A,
	CLASE_F,
	CLASE_G,
	CLASE_K,
	CLASE_M
} espectral_t;

status_t procesar_entrada_temp(float * temp);
status_t convert_entrada_a_clase(float temp, espectral_t * clase);
void imprimir_color_estrella(espectral_t clase);

#endif