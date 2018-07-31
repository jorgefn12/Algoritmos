#include "errores.h"
#include "tipos.h"
#include "argumentos.h"
#include "simpletron.h"
#include "lectores.h"

void imprimir_estado(status_t status){
    switch (status) {
        case ST_OK:
            fprintf(stdout, "%s\n", MSJ_ST_OK);
            break;
        case ST_ERROR_PTR_NULO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_PTR_NULO, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_PALABRA_NO_VALIDA:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_PALABRA_NO_VALIDA, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_LEER_PALABRA:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_LEER_PALABRA, MSJ_OPCION_AYUDA);
            break;    
        case ST_ERROR_MEMORIA:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_MEMORIA, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_ARCHIVO_NO_ENCONTRADO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_ARCHIVO_NO_ENCONTRADO, MSJ_OPCION_AYUDA);
            break;
        case ST_MEMORIA_INSUFICIENTE:
            fprintf(stderr, "%s. %s\n", MSJ_ST_MEMORIA_INSUFICIENTE, MSJ_OPCION_AYUDA);
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
        /*Ejecutar codigo*/
        case ST_HALT:
            fprintf(stderr, "%s. %s\n", MSJ_ST_HALT, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_SEGMENTATION_FAULT:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_SEGMENTATION_FAULT, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_OPCODE_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_OPCODE_INVALIDO, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_OVERFLOW:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_OVERFLOW, MSJ_OPCION_AYUDA);
            break;
        default:
            fprintf(stderr, "%s\n", MSJ_OPCION_AYUDA);
    }
}
void imprimir_ayuda(void){
    fprintf(stdout,"%s\n",MSJ_AYUDA_PROTOTIPO);
    fprintf(stdout,"%s\n\n",MSJ_AYUDA_MEMORIA);
    fprintf(stdout,"%s\n\n",MSJ_AYUDA_FORMATO);
    fprintf(stdout,"%s\n\n",MSJ_AYUDA_ARCHIVOS);
}
void destructor(params_t * param, simpletron_t ** simpletron){
    cerrar_archivos(param);
    destruir_simpletron(simpletron, param);
    destruir_params(param);
}
