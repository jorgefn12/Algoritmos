typedef long palabra_t;
typedef unsigned int uint;

typedef enum {
    FMT_TXT,
    FMT_BIN
}formato_t;

typedef struct palabra{
    palabra_t dato;
    struct palabra * sig;
}palabra_s;

typedef struct archivo{
    char * nombre;
    formato_t formato;
    palabra_s memoria;
}archivo_s;

typedef struct simpletron{
    archivo_s archivo;
    palabra_t acumulador;
    size_t program_counter;
    uint opcode;
    uint operando;
    struct simpletron *sig;
} simpletron_s;

/*Para indicar que el archivo es stdin, se inicializa cant_archivos = 1, nombre = "stdin" y formato = FMT_TXT*/
typedef struct params{
    size_t cant_memoria;
    size_t cant_archivos;
    archivo_s archivo_salida;
    archivo_s * archivo_entrada; /* Por ahora estoy usando esta variable, cuando tengamos el resto del código agregamos los
                                  * nombres directamente a la estructura simpletron */
}params_s;




