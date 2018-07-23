#ifndef SIMPLETRON__H
#define SIMPLETRON__H

#define MIN_PALABRA -9999999
#define MAX_PALABRA 9999999
#define OPCODE_OPERANDO_MULTIPLIER 10000
#define OPERANDO_MIN 0 /*xxxxxxx000000000*/
#define OPERANDO_MAX 511 /*xxxxxxx111111111*/
#define OPCODE_MIN 0 /*0000000xxxxxxxxx*/
#define OPCODE_MAX 127 /*1111111xxxxxxxxx*/
#define OPCODE_FIELD_MIN -64 /*1000000xxxxxxxxx*/
#define OPCODE_FIELD_MAX 63 /*0111111xxxxxxxxx*/
typedef int palabra_t;
typedef unsigned int uint_t;
typedef enum{
    OP_LEER = 10,
    OP_ESCRIBIR,
    OP_CARGAR = 20,
    OP_GUARDAR,
    OP_PCARGAR,
    OP_PGUARDAR,
    OP_SUMAR = 30,
    OP_RESTAR,
    OP_DIVIDIR,
    OP_MULTIPLICAR,
    OP_JMP = 40,
    OP_JMPNEG,
    OP_JMPZERO,
    OP_JNZ,
    OP_DJNZ,
    OP_HALT
}opcode_t;
typedef struct simpletron{ /********ENCAPSULAR luego de probar programa*************/
    palabra_t instruccion, acumulador;
    opcode_t opcode;
    uint operando;
    size_t program_counter;
    vector_t ** memoria; /*Se guarda una memororia por cada archivo*/
}simpletron_t;
simpletron_t * crear_simpletron(params_t * param);
void destruir_simpletron(simpletron_t ** simpletron);
void imprimir_registros_simpletron(simpletron_t * simpletron, FILE * stream);
bool_t palabra_es_valida(palabra_t palabra);

#endif
