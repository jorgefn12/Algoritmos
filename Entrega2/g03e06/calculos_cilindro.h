#ifndef CALCULOS_CILINDRO__H
#define CALCULOS_CILINDRO__H 1
#include "errores.h"
#include "utilidades.h"
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.1415
#endif

#define MIN_RANGO_RADIO 0
#define MIN_RANGO_ALTURA 0
#define MSJ_PROGRAMA_CILINDRO "El programa le devolverá las medidas en metros de un cilindro de acuerdo a su radio y altura"
#define MSJ_INGRESO_RADIO "Ingrese un valor de radio en metros [mayor a  0]"
#define MSJ_INGRESO_ALTURA "Ingrese un valor de altura en metros [mayor a  0]"
#define MSJ_DIAMETRO_CILINDRO "Diámetro"
#define MSJ_CIRCUNFERENCIA_CILINDRO "Cincunferencia"
#define MSJ_BASE_CILINDRO "Base"
#define MSJ_VOLUMEN_CILINDRO "Volumen"

status_t procesar_entrada_cilindro(float * radio_cilindro, float * altura_cilindro);
void imprimir_medidas_cilindro(float radio_cilindro, float altura_cilindro);
float cilindro_diametro(float radio, float altura);
float cilindro_circunferencia(float radio, float altura);
float cilindro_base(float radio, float altura);
float cilindro_volumen(float radio, float altura);

#endif
