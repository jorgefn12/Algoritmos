#include <stdlib.h>
#include <stdio.h>
#include "tipos.h"

void destruir_simpletron(simpletron_s **simpletron) {
    simpletron_s *aux = *simpletron;

    while (*simpletron != NULL) {
        eliminar_archivo(&((*simpletron)->archivo));
        *simpletron = (*simpletron)->sig;
    }

    free(aux);
    aux = NULL;
}

status_t eliminar_archivo(archivo_s **archivo) {
    status_t status;
    
    free((*archivo)->nombre);
    (*archivo)->nombre = NULL;

    /*Destruir memoria*/
    status = destruir_lista(&(*archivo)->memoria, &destructor_lista);

    free(*archivo);
    *archivo = NULL;
    
    return status;
}

status_t destruir_lista(palabra_s **p, void (*destructor_lista)(void*)) {
    palabra_s *siguiente;

    if (!p)
        return ST_ERROR_PTR_NULO;

    if (lista_vacia(*p))
        return ST_OK;

    siguiente = (*p)->sig;
    lista_destruir_nodo(p, destructor_lista);

    return destruir_lista(&siguiente, destructor_lista);
}

bool_t lista_vacia(palabra_s *p) {
    return p == NULL;
}

status_t lista_destruir_nodo(palabra_s **pnodo, void(*destructor_lista)(void*)) {
    if (!pnodo)
        return ST_ERROR_PTR_NULO;
    if (!(*pnodo))
        return ST_OK; /*ya esta destruido*/

    if (destructor_lista != NULL)
        (*destructor_lista)(&(*pnodo)->dato);

    (*pnodo)->dato = 0;
    (*pnodo)->sig = NULL;
    free(*pnodo);
    *pnodo = NULL;
    return ST_OK;

}

void destructor_lista(void* dato) {
    free(dato);
    dato = NULL;
}
