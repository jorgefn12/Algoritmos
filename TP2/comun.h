/*typedef de los operandos*/
typedef enum {
    OP_LEER = 10,
    OP_ESCRIBIR = 11
} opcode_t;

typedef enum {
    FALSE = 0,
    TRUE
} bool_t;

typedef enum {
    ST_OK,
    ST_HELP,
    ST_ERROR_PTR_NULO,
    ST_ERROR_ARCHIVO_NO_ENCONTRADO,
    ST_ERROR_MEMORIA,
    /*Validacion cla*/
    ST_ERROR_CANT_ARG,
    ST_ERROR_FLAG_NO_RECONOCIDO,
    ST_ERROR_MEMORIA_INGRESADA_INVALIDA,
    ST_ERROR_FORMATO_ARCHIVO_INVALIDO,
            ST_ERROR_STDIN_INVALIDO
} status_t;

