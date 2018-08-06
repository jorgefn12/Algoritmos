
#include "vectores.h"


/*****************************VECTORES.C********************************************************/
void VECTOR_destruir(vector_t ** vector){
    if(vector != NULL && *vector != NULL){
        if((*vector)->datos != NULL){
            free((*vector)->datos);
            (*vector)->datos = NULL;
        }
        free(*vector);
        *vector = NULL;
    }   
}
vct_retval_t VECTOR_crear(vector_t ** vector, size_t n){
    if(vector == NULL)
        return VCT_RV_ILLEGAL;
    if(n <= 0)
        return VCT_RV_INVALID_ARGS;
    if((*vector = (vector_t *)calloc(1, sizeof(vector_t))) == NULL)
        return VCT_RV_NOSPACE;
    if(((*vector)->datos = (int *)calloc(n, sizeof(int))) == NULL){
        VECTOR_destruir(vector);
        return VCT_RV_NOSPACE;
    }
    /*v->usado inicializado con calloc*/
    (*vector)->pedido = n;
    return VCT_RV_SUCCESS;
}
vct_retval_t VECTOR_redimensionar(vector_t * vector, size_t n){
    int * aux;
    
    if(vector == NULL)
        return VCT_RV_ILLEGAL;
    if(n <= 0)
        return VCT_RV_INVALID_ARGS;
    
    if(n == vector->pedido)
        return VCT_RV_SUCCESS;

    aux = (int*)realloc(vector->datos, n * sizeof(int));
    if(aux == NULL)
    	return VCT_RV_NOSPACE;
    vector->datos = aux;

    vector->pedido = n;
    if(vector->usado > vector->pedido)
        vector->usado = vector->pedido;

    return VCT_RV_SUCCESS;
}
vct_retval_t VECTOR_guardar_entero(vector_t * vector, size_t posicion, int dato){
    if(vector == NULL)
        return VCT_RV_ILLEGAL;
    if(posicion > vector->pedido || posicion < 1)
        return VCT_RV_INVALID_ARGS;
    
    (vector->datos)[posicion - 1] = dato;
    
    if(vector->usado < posicion)
        vector->usado = posicion;
    
    return VCT_RV_SUCCESS;  
}
int VECTOR_obtener_dato(vector_t * v, size_t i){
    return v->datos[i - 1];
}
int VECTOR_obtener_memoria_usada(vector_t * v){
    return v == NULL ? -1 : v->usado;
}
int VECTOR_obtener_memoria_pedida(vector_t * v){
    return v == NULL ? -1 : v->pedido;
}
