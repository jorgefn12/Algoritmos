#ifndef TIPOS__H
#define TIPOS__H

typedef enum{
    FALSE = 0,
    TRUE
}bool_t;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef enum{
    ST_OK,
    ST_AYUDA,
    ST_ERROR_CANT_ARG,
    ST_ERROR_STDIN_INVALIDO,
    ST_ERROR_PTR_NULO,
    ST_ERROR_ARCHIVO_NO_ENCONTRADO,
    ST_ERROR_MEMORIA,
    ST_ERROR_MEMORIA_INGRESADA_INVALIDA,
    ST_ERROR_FORMATO_ARCHIVO_INVALIDO,
    ST_ERROR_NODO_VACIO,
    /*carga de archivo*/
    ST_ERROR_PALABRA_NO_VALIDA,
    ST_ERROR_LEER_PALABRA,
    ST_ERROR_CREAR_SIMPLETRON,
    /*status de ejecutar_codigo*/
    ST_HALT,
    ST_ERROR_SEGMENTATION_FAULT,
    ST_ERROR_CAD_NO_LEIDA,
    ST_ERROR_OPCODE_INVALIDO,
    ST_ERROR_MAX_INSTR_SUPERADO,
    ST_ERROR_ESCRIBIR_BIN,
    ST_ERROR_MAX_INGRESOS_SUPERADO
}status_t;
typedef enum{
    FMT_TXT,
    FMT_BIN        
}formato_t;
typedef struct archivo{
    char * nombre;
    formato_t formato;
    FILE * stream;
}archivo_t;

#endif
