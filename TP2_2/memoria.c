#include "memoria.h"
#include "tipos.h"
#include <stdlib.h>
#include <string.h>
/*Definicion de TDA VECTOR*/
typedef struct vector{
    size_t usado, pedido;
    void * datos;
} vector_t;

/*Primiticas de TDA VECTOR*/


/*Crea vector de 1 dimension con n cantidad de elementos. Devuelve su puntero por el nombre
*/
vector_t * crear_vector(size_t n){
    vector_t * v;
    
    if(n <= 0)
        return NULL;
    v = (vector_t *)calloc(1, sizeof(vector_t));
    if(!v)
        return NULL;
    v->datos = (void*)calloc(1,n * sizeof(void*));
    if(!v->datos){
        free(v);
        return NULL;
    }
    v->usado = 0;
    v->pedido = n;
    return v;
}
/*Si n es mayor a la longitud del vector, pide mas memoria. Si es menor, libera la memoria de los ultimos elementos sobrantes
*  Rellena la memoria solicitada que no está en uso con ceros.*/
bool_t vector_redimensionar(vector_t *v, size_t n){
    void * aux;
    
    if(!v || n <= 0)
        return FALSE;
    
    if(n == v->pedido)
        return TRUE;

    aux = (void*)calloc(1, n * sizeof(void*));
    if(!aux)
        return FALSE;
    memcpy(aux, v->datos, n > v->usado ? (v->usado) * sizeof(void*) : (n) * sizeof(void*));
    free(v->datos);
    v->datos = (void*)calloc(1, n * sizeof(void*));
    if(!v->datos){
    	free(aux);
        return FALSE;
    }
    memcpy(v->datos, aux, n > v->usado ? (v->usado) * sizeof(void*) : (n) * sizeof(void*));
    free(aux);

    v->pedido = n;
    if(v->usado > v->pedido)
        v->usado = v->pedido;
    return TRUE;
}
/*Destruye vectores de 1 dimension*/
void vector_destruir(vector_t ** v){
    if(v && *v){
        if((*v)->datos){
            free((*v)->datos);
            (*v)->datos = NULL;
        }
        free(*v);
        *v = NULL;
    }
}
/*Guarda lo apuntado por dato en la posicion i-1 del TDA vector apuntado por v*/
/*Esta funcion trabaja con datos y vectores de enteros*/
bool_t vector_guardar_int(vector_t * v, size_t i, int * dato){
    if(!v || i > v->pedido || i < 1)
        return FALSE;
    ((int*)v->datos)[i-1]= *dato;
    if(v->usado < i)
        v->usado = i;

    return TRUE;
}
/*No se puede iterar genericamente elementos que apunten a void*
 Para acceder a su contenido, el compilador necesita saber de qué tipo es.
 Por lo que se necesitan varias funciones de iteracion dependiendo del tipo.
 Esta funcion itera sobre un TDA Vector de tipo int*/
void vector_iterar_int(vector_t * v, void (*func)(void *,void *), void * arg){
    size_t i;
    
    if(v && func){
        for(i = 0; i < v->pedido; i++){      
            (*func)(&(((int*)v->datos)[i]), arg);
        }
    }
}
/*Imprime por stream (archivo ya abierto) el contenido de las direcciones apuntados por vector_int*
* Sólo trabajo con enteros.*/
void imprimir_int(void * dato, void* stream){
    fprintf(stream, "%i ", *(int*)dato);
}
/*Se debe validar el puntero antes de usar las funciones obtener*/
/*Obtienen información de la estructura del vector*/
int obtener_dato(vector_t * v, size_t i){
    return ((int*)(v->datos))[i - 1];
}
int obtener_usado(vector_t * v){
    return v == NULL ? EOF : v->usado;
}
int obtener_pedido(vector_t *v){
    return v == NULL ? EOF : v->pedido;
}
