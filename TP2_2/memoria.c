/*Definiciones TDA Vector y sus primitivas*/
/*El codigo esta funcionando, pero todavia no chequeé las si tiene fugas. No debería*/

#include "comun.h"
#include "tipos.h"
#include "memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector{
  size_t usado, pedido;
  void * datos;
} vector_t;

/******************Primitivas*******************/

/*Crea TDA vector de una dimension, retorna NULL si ocurre un error*/
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

/*Si n es mayor a la longitud del vector-> pide mas memoria. Si es menor-> libera la memoria de los ultimos elementos sobrantes
* Rellena la memoria solicitada que no está en uso con ceros.
*/
bool_t vector_redimensionar(vector_t *v, size_t n){
    void ** aux;
    size_t i;
    
    if(!v || n <= 0)
        return FALSE;
    
    if(n == v->pedido)
        return TRUE;
    
    if(n > v->pedido){
        aux = (void**)realloc(v->datos, n * sizeof(void*));
        if(!aux)
            return FALSE;
        v->datos = memset(aux[v->pedido], 0, n - (v->pedido) - 1);
        v->pedido = n;
        return TRUE;
    }
    
    if(n < v->pedido){
        aux = (void**)calloc(1, n * sizeof(void*));
        if(!aux)
            return FALSE;
        v->datos = memcpy(aux, v->datos, v->usado);
        v->pedido = n;
        if(v->usado > v->pedido)
            v->usado = v->pedido;
        return TRUE;
    }
}

/*Destruye vector de 1 dimension*/
void vector_destruir(vector_t ** v){
    if(v && *v){
        if((*v)->datos)
            free((*v)->datos);
        free(*v);
        *v = NULL;
    }
}
/*Guarda lo apuntado por dato en la posicion i+1 del TDA vector apuntado por v. Retorna booleano*/
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
 Esta funcion itera sobre un TDA Vector de tipo int
 */
void vector_iterar_int(vector_t * v, void (*func)(void *,void *), void * arg){
    size_t i;
    
    if(v && func){
        for(i = 0; i < v->pedido; i++){
            (*func)(&(((int*)v->datos)[i]), arg);
        }
    }
}

/*Imprime por stream (archivo ya abierto) el contenido de las direcciones apuntados por vector_int*
* Sólo trabajo con enteros.
*/
void imprimir_vector(void * vector_int, void* stream){
    fprintf(stream, "%i ", *(int*)vector_int);
}


/*Pedazo de codigo para probar funcionamiento
int main(int argc, char** argv) {
    vector_t * v;
    int temp = 99999;
    
    v = crear_vector(10);
    vector_guardar_int(v,5,&temp);
    vector_iterar_int(v,imprimir_vector, stdout);
    printf("\nmemoria usada: %d\n",v->usado);
    printf("memoria pedida: %d\n",v->pedido);
    vector_iterar_int(v,imprimir_vector, stdout);
    vector_destruir(&v);
    vector_iterar_int(v,imprimir_vector, stdout);
    
    return EXIT_SUCCESS;
}
*/
