#ifndef CALCULOS_PROBABILIDAD__H
#define CALCULOS_PROBABILIDAD__H 1
#include "errores.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_INTENTOS_PROBABILIDAD 100
#define MAX_INTENTOS_MONEDAS 100
#define MAX_INTENTOS_DADOS 20

void imprimir_probabilidad1(size_t n);
void imprimir_probabilidad2(size_t n);
int probabilidad1();
int probabilidad2();
void tirar_monedas(size_t n);
void tirar_dados(size_t n);

#endif