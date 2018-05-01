#ifndef PROCESAMIENTO_DE_ESTADOS__H
#define PROCESAMIENTO_DE_ESTADOS__H 1
#include <stdio.h>

#define MSJ_ERR_PTR_NULO "Puntero nulo"
#define MSJ_ERR_MEMORIA "Memoría no disponible"
#define MSJ_ERR_ENTRADA_INVALIDA  "Entrada inválida."
#define MSJ_ERR_RANGO_INVALIDO "Fuera de rango."
#define MSJ_ERR_LECTURA_TEMP "Error de lectura (temperatura estrella)."
#define MSJ_ERR_LECTURA_CLASE "Error de lectura (clase de estrella)."
#define MSJ_ERR_LECTURA_DADO "Error de lectura (dado)."
#define MSJ_ERR_FORMATO_INVALIDO "Formato inválido"
#define MSJ_ERR_GENERAL "Error."
#define MSJ_VALOR_NO_ENCONTRADO "Valor no encontrado."

typedef enum{
	ST_ERR_PTR_NULO = -20,
	ST_ERR_MEMORIA,
	ST_ERR_ENTRADA_INVALIDA,
	ST_ERR_RANGO_INVALIDO,
	ST_ERR_LECTURA_TEMP,
	ST_ERR_LECTURA_CLASE,
	ST_ERR_LECTURA_DADO,
	ST_ERR_FORMATO_INVALIDO,
	ST_ERR_GENERAL,
	ST_VALOR_NO_ENCONTRADO = -1,
	ST_OK = 0
} status_t;

void imprimir_estado(status_t st);

#endif