#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "tipos.h"
#include "memoria.h"
#include "listas.h"
#include "argumentos.h"
#include "errores.h"
#include "simpletron.h"
#include "lectores.h"
#include "dump.h"

int main(int argc, char** argv){
    simpletron_t * simply = NULL;
    status_t st;
    params_t argumentos;
    lista_t lista;
    size_t i;

    if((st = validacion_cla(argc, argv, &argumentos)) != ST_OK){
    	imprimir_estado(st);
    	return EXIT_FAILURE;
    }
    if(!crear_simpletron(&argumentos,&simply)){
    	destruir_params(&argumentos);
    	return EXIT_FAILURE;
    }
    if(abrir_archivos(&argumentos) != argumentos.cant_archivos + 1){
    	fprintf(stderr, "%s\n", MSJ_ST_ERROR_ARCHIVO_NO_ENCONTRADO);
    	destruir_simpletron(&simply, &argumentos);
        destruir_params(&argumentos);
    	return EXIT_FAILURE;
    }
    for(i = 0; i < argumentos.cant_archivos; i++){
        crear_lista(&lista);
        if((st = cargar_lista_palabras(argumentos.archivo_entrada[i], &lista, &argumentos.cant_memoria) != ST_OK)){
            imprimir_estado(st);
            destructor(&argumentos, &simply);
            return EXIT_FAILURE;
        }
        if(!guardar_lista_en_vector(lista, &simply->memoria[i])){
            fprintf(stderr, "%s\n", MSJ_ST_ERROR_GUARDAR_LISTA);
            destructor(&argumentos, &simply);
            return EXIT_FAILURE;
        }
        destruir_lista(&lista);
    }
    if((st = ejecutar_codigo(simply, &argumentos) != ST_OK)){
        imprimir_estado(st);
        destructor(&argumentos, &simply);
        return EXIT_FAILURE;
    }

    cerrar_archivos(&argumentos);
    destruir_simpletron(&simply, &argumentos);
    destruir_params(&argumentos);
    
    return EXIT_SUCCESS;
}
