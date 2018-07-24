#ifndef MEMORIA__H
#define MEMORIA__H

#include "tipos.h"
#include <stdlib.h>

typedef struct vector vector_t;
vector_t * crear_vector(size_t n);
bool_t vector_redimensionar(vector_t *v, size_t n);
void vector_destruir(vector_t ** v);
bool_t vector_guardar_int(vector_t * v, size_t i, int * dato);
void vector_iterar_int(vector_t * v, void (*func)(void *,void *), void * arg);
void imprimir_int(void* datos, void * stream);
int obtener_dato(vector_t * v, size_t i);
int obtener_usado(vector_t * v);
int obtener_pedido(vector_t * v);

#endif