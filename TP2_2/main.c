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
    
    
    
    
    
    
    
    /*******************************************************************/
    /*
    MAIN PARA IMPRIMIR LISTAS. Ej:  ./main -m 60 -f txt suma.txt maximo.txt b:nulo.sac 
    simpletron_t * simply = NULL;
    status_t st;
    params_t argumentos;
    lista_t lista;
    size_t i;
    
    validacion_cla(argc, argv, &argumentos);
    if(st == ST_OK){
        for(i=0;i<argumentos.cant_archivos;i++){
            printf("Archivo entrada %lu: %s [%d]\n", i+1, argumentos.archivo_entrada[i].nombre ? argumentos.archivo_entrada[i].nombre : "stdin(null)", argumentos.archivo_entrada[i].formato);
        }
        printf("Archivo salida: %s [%d]\n",argumentos.archivo_salida->nombre, argumentos.archivo_salida->formato);
        printf("Cantidad memoria: %ld\n", argumentos.cant_memoria);
        printf("Cantidad archivos entrada: %ld\n", argumentos.cant_archivos);
    }
    simply = crear_simpletron(&argumentos);
    imprimir_registros_simpletron(simply, stdout);
    

    printf("Cantidad archivos abiertos: %lu\n", abrir_archivos(&argumentos));
    
    for(i = 0; i < argumentos.cant_archivos; i++){
        crear_lista(&lista);
        cargar_lista_palabras(argumentos.archivo_entrada[i], &lista);
        puts("Imprimiendo lista");
        imprimir_lista_int(lista);
        
    }
    printf("Cantidad archivos cerrados: %lu\n", cerrar_archivos(&argumentos));
    destruir_simpletron(&simply);
    
    return EXIT_SUCCESS;
    */
    /*******************************************************************/
    return EXIT_SUCCESS;
}
