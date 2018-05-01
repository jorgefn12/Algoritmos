#ifndef UTILIDADES__H
#define UTILIDADES__H 1
#include "procesamiento_de_estados.h"
#include <stdio.h>
#include <stdlib.h>

#define MSJ_INGRESO_FLOAT "Ingrese un número real"
#define MSJ_INGRESO_DOUBLE "Ingrese un número real"
#define MSJ_INGRESO_INT "Ingrese un número entero"
#define MSJ_INGRESO_INT_SUMA "Ingrese un número entero para sumar"
#define MSJ_INGRESO_UINT "Ingrese un número entero positivo"
#define MSJ_INGRESO_CHAR "Ingrese un carácter"
#define MSJ_INGRESO_CANT_FIL "Ingrese número de filas"
#define MSJ_INGRESO_CANT_COL "Ingrese número de columnas"

void limpiar_buffer();

status_t crear_matd_dinamic(double ***mat, size_t fil, size_t col);

void cargar_rnd_vctd(double v[], size_t n); /*Requiere inicializar semilla fuera de la función*/
void cargar_rnd_matd(double **mat, size_t fil, size_t col);
status_t cargar_stdin_vctd(double v[], size_t n);
status_t cargar_stdin_matd(double **mat, size_t fil, size_t col);

void imprimir_vctd(const double v[], size_t n);
void imprimir_matd(const double** mat, size_t fil, size_t col);

status_t procesar_entrada_int(int * entrada); /*Valida y guarda en [int*entrada] lo ingresado por stdin*/

#endif