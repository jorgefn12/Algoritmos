#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(int argc, char** argv) {
    status_t status;
    char *archivo_entrada;
    char *archivo_salida;
    archivo_t tipo_archivo_entrada, tipo_archivo_salida;
    palabras_s palabra;

    /*Inicializo algunas variables*/
    palabra.program_counter = 0;
    palabra.acumulador = 0;
    /*1) Validacion de argumentos pasados por la terminal*/
    status = validacion_cla(argc, argv, &palabra.cantidad_memoria, &archivo_entrada, &tipo_archivo_entrada, &archivo_salida, &tipo_archivo_salida);
    if (status != ST_OK) {
        imprimir_errores(status);
        return EXIT_FAILURE;
    }

    /*2) Cargar estructura*/
    status = leer_archivo(archivo_entrada, tipo_archivo_entrada, &palabra);
    if (status != ST_OK) {
        imprimir_errores(status);
        return EXIT_FAILURE;
    }
    /*3) Ejecutar codigo*/
    status = ejecutar_codigo(&palabra);
    if (status != ST_OK){
        imprimir_errores(status);
        dump(tipo_archivo_salida, archivo_salida, palabra);
        free(palabra.memoria);
        free(archivo_entrada);
        free(archivo_salida);
        return EXIT_FAILURE;
    }
    status = dump(tipo_archivo_salida, archivo_salida, palabra);
    if (status != ST_OK)
        imprimir_errores(status);

    free(palabra.memoria);
    free(archivo_entrada);
    free(archivo_salida);
    return EXIT_SUCCESS;
}

