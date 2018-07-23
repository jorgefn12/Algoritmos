/*Definiciones TDA Lista y sus primitivas*/
#include "lista.h"
#include "tipos.h"
#include "comun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

status_t crear_lista(lista_t * lista){
    if(!lista)
        return ST_ERROR_PTR_NULO;
    *lista = NULL;
    return ST_OK;
}
nodo_t * crear_nodo(void * dato){
    nodo_t * nodo = NULL;
    nodo = (nodo_t *)calloc(1,sizeof(nodo_t));
    if(!nodo)
        return NULL;
    nodo->dato = dato;
    nodo->sig = NULL;
    return nodo;
}
bool_t lista_esta_vacia(lista_t lista){
    return !lista;
}
status_t insertar_nodo_final(lista_t * lista, void * dato){
    if(!lista)
        return ST_ERROR_PTR_NULO;
    if(lista_esta_vacia(*lista)){
        *lista = crear_nodo(dato);
        if(!(*lista))
            return ST_ERROR_MEMORIA;
        return ST_OK;
    }
    return insertar_nodo_final(&(*lista)->sig, dato);
}
status_t insertar_nodo_ppio(lista_t * lista, void * dato){
    nodo_t * aux = NULL;
    
    if(!lista)
        return ST_ERROR_PTR_NULO;
    aux = crear_nodo(dato);
    if(!aux)
        return ST_ERROR_MEMORIA;
    aux->sig = *lista;
    *lista = aux;
    return ST_OK;
}
void destruir_lista(lista_t * lista){
    nodo_t * aux = NULL;

    if(!lista){
        return;
    }
    while(*lista){
        aux = (*lista)->sig;
        free(*lista);
        *lista = aux;
    }
}
void imprimir_lista_int(lista_t lista){
    while(lista){
        printf("%d ", (lista->dato));
        lista = lista->sig;
    }
    putchar('\n');
}
bool_t guardar_lista_en_vector(lista_t lista, vector_t * vector){
    vector_t * aux;
    size_t i;
    if(vector == NULL)
        return FALSE;
    if((aux = crear_vector(1)) == NULL)
        return FALSE;
    *vector = *aux;
    for(i = 1; lista != NULL; i++){

        if(!vector_redimensionar(vector, i)){
            vector_destruir(&vector);
            return FALSE;
        }
        if(!vector_guardar_int(vector,i,lista->dato)){
            vector_destruir(&vector);
            return FALSE;
        }        
        lista = lista->sig;
    }
    return TRUE;
}
