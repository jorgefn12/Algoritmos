#include "tipos.h"
#include "comun.h"
#include "argumentos.h"
#include "dump.h"
#include "errores.h"
#include "lectores.h"
#include "lista.h"
#include "memoria.h"
#include "simpletron.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
    vector_t * v;
    int valores[] = {0,1,2,3,4,5,6,7,8,9};
    
    v = crear_vector(20); /*Crea vector de 20 elementos*/
    vector_redimensionar(v, 100); /*Redimensiona a 100 elementos*/
    vector_guardar_int(v, 5, &valores[5]); /* Guarda en la posicion v[4] el contenido de &valores[5] */
    /*
    vector_redimensionar(v, 99);
    En esta parte del codigo, el vector redimensiona pero pierde toda la informacion, sin importar
    si era más grande o más chico que el anterior vector.
    */
    vector_iterar_int(v,imprimir_int, stdout); /*Imprime todo el vector*/
    printf("\nmemoria usada: %d\n", v->usado);
    printf("memoria pedida: %d\n", v->pedido);
    vector_destruir(&v);
    
    return EXIT_SUCCESS;
}
