#include <stdio.h>
#include <string.h>
#include "comun.h"
#include "errores.h"

void imprimir_mensaje_de_error(status_t status){
    switch(status){
        case ST_ERROR_CANT_ARG:
            fprintf(stderr,"%s. %s\n",MSJ_ST_ERROR_CANT_ARG,MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_FLAG_NO_RECONOCIDO:
            fprintf(stderr,"%s. %s\n",MSJ_ST_ERROR_FLAG_NO_RECONOCIDO,MSJ_OPCION_AYUDA);
            break;
        default:
            puts("kajs");
    }
}