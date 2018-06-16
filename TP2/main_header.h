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
    ST_ERROR_CANT_ARG,
    ST_ERROR_MEMORIA_INGRESADA_INVALIDA

} status_t;

typedef long palabra_t;

typedef struct {
    size_t largo;
    palabra_t *palabra;
    palabra_t acumulador;
    size_t program_counter;
} simpletron_s;

