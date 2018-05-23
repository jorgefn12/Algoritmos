#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

void imprimir_errores(status_t status) {
    switch (status) {
        case ST_ERROR_CANT_ARG:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_CANT_ARG, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_ARCHIVO_I_NO_INGRESADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_ARCHIVO_I_NO_INGRESADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_IF_NO_VALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_IF_NO_VALIDO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_IF_NO_INGRESADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_IF_NO_INGRESADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_OF_NO_VALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_OF_NO_VALIDO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_OF_NO_INGRESADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_OF_NO_INGRESADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_ARCHIVO_NO_ENCONTRADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_ARCHIVO_NO_ENCONTRADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_PTR_NULO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_PTR_NULO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_MEM:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_MEM, MSJ_MAS_AYUDA);
        case ST_HELP:
            imprimir_ayuda();
            break;
        case ST_ERROR_M_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_M_NO_VALIDO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_CAD_NO_ES_ENTERO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_CAD_NO_ES_ENTERO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_PALABRA_FUERA_DE_RANGO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_PALABRA_FUERA_DE_RANGO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_SEGMENTATION_FAULT:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_SEGMENTATION_FAULT, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_CAD_NO_LEIDA:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_CAD_NO_LEIDA, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_OPCODE_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_OPCODE_INVALIDO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_MAX_INSTR_SUPERADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_MAX_INSTR_SUPERADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_ESCRIBIR_BIN:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_ESCRIBIR_BIN, MSJ_MAS_AYUDA);
            break;
        default:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR, MSJ_MAS_AYUDA);
    }
}

void imprimir_ayuda() {
    fprintf(stderr, "%s\n", MSJ_AYUDA_TITULO);
    fprintf(stderr, "%s    %s\n\n", CLA_M, MSJ_AYUDA_M1);
    fprintf(stderr, "%s    %s\n\n", CLA_I, MSJ_AYUDA_I1);
    fprintf(stderr, "%s   %s\n", CLA_IF, MSJ_AYUDA_IF1);
    fprintf(stderr, "      %s\n\n", MSJ_AYUDA_IF2);
    fprintf(stderr, "%s    %s\n\n", CLA_O, MSJ_AYUDA_O1);
    fprintf(stderr, "%s   %s\n", CLA_OF, MSJ_AYUDA_OF1);
    fprintf(stderr, "      %s\n\n", MSJ_AYUDA_OF2);
}
