#define POS_ARGV1 1
#define DEFAULT_MEMORIA 50

/*typedef de los operandos*/
typedef enum {
    OP_LEER = 10,
    OP_ESCRIBIR = 11
} opcode_t;

typedef enum {
    ST_OK,
    ST_HELP,
    ST_ERROR,
    /*Validacion cla*/
    ST_ERROR_CANT_ARG,
    ST_ERROR_FLAG_NO_RECONOCIDO,
    ST_ERROR_MEMORIA_INGRESADA_INVALIDA,
    ST_ERROR_FORMATO_ARCHIVO_INVALIDO

} status_t;


typedef long palabra_t;

typedef struct archivo {
    char* nombre_archivo;
    struct archivo* siguiente;
} archivos_s;

typedef struct {
    size_t largo;
    palabra_t *palabra;
    palabra_t acumulador;
    size_t program_counter;
} simpletron_s;
