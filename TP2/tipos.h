typedef long palabra_t;
typedef unsigned int uint;

typedef struct palabra{
    palabra_t palabra;
    palabras_s *sig;
}palabras_s;

typedef struct archivo{
    char* nombre_archivo;
    /*formato y tipo*/
    palabra_t *palabra;
}archivos_s;

typedef struct simpletron{
    archivos_s archivo;
    palabra_t acumulador;
    size_t program_counter;
    uint opcode;
    uint operando;
    struct simpletron *sig;
} simpletron_s;