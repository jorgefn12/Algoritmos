#ifndef LISTAS__H
#define LISTAS__H

#include "tipos.h"
#include "memoria.h"

typedef struct nodo nodo_t, * lista_t;
status_t crear_lista(lista_t * lista);
nodo_t * crear_nodo(void * dato);
bool_t lista_esta_vacia(lista_t lista);
status_t insertar_nodo_final(lista_t * lista, void * dato);
status_t insertar_nodo_ppio(lista_t * lista, void * dato);
void destruir_lista(lista_t * lista);
void imprimir_lista_int(lista_t lista);
bool_t guardar_lista_en_vector(lista_t lista, vector_t ** vector);

#endif