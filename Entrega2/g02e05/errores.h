#ifndef ERRORES__H
#define ERRORES__H 1
#include <stdio.h>

#define MSJ_ERR_PTR_NULO "Puntero nulo, memoria no accesible."
#define MSJ_ERR_ENTRADA_INVALIDA  "Entrada inválida."
#define MSJ_ERR_RANGO_INVALIDO "Fuera de rango."
#define MSJ_ERR_LECTURA_TEMP "Error de lectura (temperatura)."
#define MSJ_ERR_LECTURA_CLASE "Error de lectura (clase)."
#define MSJ_ERR_GENERAL "Error."

typedef enum{
	ST_ERR_PTR_NULO,
	ST_ERR_ENTRADA_INVALIDA,
	ST_ERR_RANGO_INVALIDO,
	ST_ERR_LECTURA_TEMP,
	ST_ERR_LECTURA_CLASE,
	ST_OK
} status_t;

void imprimir_error(status_t st);

#endif