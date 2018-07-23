#include "errores.h"
#include "tipos.h"
#include "comun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimir_estado(status_t status){
    switch (status) {
        case ST_OK:
            fprintf(stdout, "%s\n", MSJ_ST_OK);
            break;
        case ST_ERROR_PTR_NULO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_PTR_NULO, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_MEMORIA:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_MEMORIA, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_ARCHIVO_NO_ENCONTRADO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_ARCHIVO_NO_ENCONTRADO, MSJ_OPCION_AYUDA);
            break;
            /*Mensajes de error de validaciones.c*/
        case ST_AYUDA:
            imprimir_ayuda();
            break;
        case ST_ERROR_MEMORIA_INGRESADA_INVALIDA:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_MEMORIA_INGRESADA_INVALIDA, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_FORMATO_ARCHIVO_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_FORMATO_ARCHIVO_INVALIDO, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_STDIN_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_STDIN_INVALIDO, MSJ_OPCION_AYUDA);
            break;
        /*Ejecutar codigo
        case ST_HALT:
            fprintf(stderr, "%s. %s\n", MSJ_ST_HALT, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_SEGMENTATION_FAULT:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_SEGMENTATION_FAULT, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_CAD_NO_LEIDA:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_CAD_NO_LEIDA, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_OPCODE_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_OPCODE_INVALIDO, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_MAX_INSTR_SUPERADO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_MAX_INSTR_SUPERADO, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_MAX_INGRESOS_SUPERADO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_MAX_INSTR_SUPERADO, MSJ_OPCION_AYUDA);
            break;
        */
        default:
            fprintf(stderr, "%s\n", MSJ_OPCION_AYUDA);
    }
}
void imprimir_ayuda(void){
    fprintf(stdout, "%s", MSJ_ST_AYUDA);
}
