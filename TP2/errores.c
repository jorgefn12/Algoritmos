#include <stdio.h>
#include <string.h>
#include "main_header.h"
#include "errores.h"

void imprimir_mensaje_de_error(status_t status){
    switch(status){
        case ST_ERROR_CANT_ARG:
            fprintf(stderr,"%s",MSJ_ST_ERROR_CANT_ARG);
            break;
        default:
            puts("kajs");
    }
}
