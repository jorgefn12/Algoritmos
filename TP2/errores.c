#include <stdio.h>
#include <string.h>
#include "comun.h"
#include "errores.h"
#include "tipos.h"

void imprimir_mensaje_de_error(status_t status) {
    switch (status) {
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

            /*Mensajes de error de carga.c*/
        case ST_ERROR_CREAR_SIMPLETRON:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_CREAR_SIMPLETRON, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_LEER_PALABRA:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_CREAR_SIMPLETRON, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_PALABRA_NO_VALIDA:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_PALABRA_NO_VALIDA, MSJ_OPCION_AYUDA);
            break;
        default:
            fprintf(stderr, "%s\n", MSJ_OPCION_AYUDA);
    }
}

void imprimir_ayuda() {

}
