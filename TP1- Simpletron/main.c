#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(int argc, char** argv) {
    status_t status;
    char archivo_entrada[MAX_STR], archivo_salida[MAX_STR];
    archivo_t tipo_archivo_entrada, tipo_archivo_salida;
    palabras_s palabra;

    palabra.program_counter = 0;
    palabra.acumulador = 0;

    status = validacion_cla(argc, argv, &palabra.cantidad_memoria, archivo_entrada, &tipo_archivo_entrada, archivo_salida, &tipo_archivo_salida);
    if (status != ST_OK) {
        imprimir_errores(status);
        return EXIT_FAILURE;
    }

    printf("nombre archivo f = %s\n", archivo_salida);

    status = leer_archivo(archivo_entrada, tipo_archivo_entrada, &palabra);
    if (status != ST_OK)
        imprimir_errores(status);
    else {
/*
        status = ejecutar_codigo(&palabra);
        if (status != ST_OK)
            imprimir_errores(status);
        else
*/
            status = dump(tipo_archivo_salida, archivo_salida, palabra);
        if (status != ST_OK)
            imprimir_errores(status);
    }
    free(palabra.memoria);

    return EXIT_SUCCESS;
}

