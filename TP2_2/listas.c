#include "listas.h"
#include "tipos.h"
/*Deficinicion de TDA LISTA*/
typedef struct nodo{
    struct nodo * sig;
    void * dato;
} nodo_t, * lista_t; 

/*Primitivas de TDA LISTA*/

/*Inicializa un puntero a lista*/
status_t crear_lista(lista_t * lista){
    if(!lista)
        return ST_ERROR_PTR_NULO;
    *lista = NULL;
    return ST_OK;
}
/*Crea un nuevo nodo y lo devuelve por el nombre*/
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
        fprintf(stdout,"%d ", (int)(lista->dato));
        lista = lista->sig;
    }
    putchar('\n');
}

/*Recibe un TDA LISTA y un Puntero doble a TDA VECTOR*/
/*Retorna por el nombre un booleano indicando el resultado de la operacion de guardado*/
/*Utiliza el metodo de insercion al final*/
bool_t guardar_lista_en_vector(lista_t lista, vector_t ** vector){
    size_t i;

    if(vector == NULL)
        return FALSE;
    if((*vector = crear_vector(1)) == NULL)
        return FALSE;
    
    for(i = 1; lista != NULL; i++){
        
        if(!vector_redimensionar(*vector, i)){
            vector_destruir(vector);
            return FALSE;
        }
        if(!vector_guardar_int(*vector,i,(int*)&lista->dato)){
            vector_destruir(vector);
            return FALSE;
        }
        lista = lista->sig;
    }
    return TRUE;
}
