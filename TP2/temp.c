/*-------------------------------------------------------MAIN-----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "validaciones.h"
#include "tipos.h"

int main(int argc, char** argv) {
    status_t status;
    params_s param;
    simpletron_s *simpletron = NULL;
    int i;

    status = validacion_cla(argc, argv, &param);
    if (status != ST_OK) {
        imprimir_mensaje_de_error(status);
        return EXIT_FAILURE;
    }

    /*Cargar en simpletron el nombre y formato guardados en param*/
    status = cargar_simpletron(&simpletron, param);

    puts("\nCARGA DE SIMPLETRON EXITOSA......");
    for (i = 0; i < param.cant_archivos; i++) {
        printf("\nARCHIVO: %s\n",simpletron->archivo->nombre);
        imprimir_palabras_de_un_archivo(simpletron);
        simpletron = simpletron->sig;
    }

    return EXIT_SUCCESS;
}
