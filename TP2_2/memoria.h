/*Prototipos y funciones primitivas para usar un TDA Vector (memoria del simpletron)*/
#ifndef MEMORIA__H
#define MEMORIA__H

#include "comun.h"
#include "tipos.h"
#include "memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Aviso al usuario sobre la existencia de este tipo*/
typedef struct vector vector_t;
/********************Primitivas****************/
/*Ver documentacion en .c*/
vector_t * crear_vector(size_t n);
bool_t vector_redimensionar(vector_t *v, size_t n);
void vector_destruir(vector_t ** v);
bool_t vector_guardar_int(vector_t * v, size_t i, int * dato);
void vector_iterar_int(vector_t * v, void (*func)(void *,void *), void * arg);
void imprimir_int(void* datos, void * stream);

#endif;
