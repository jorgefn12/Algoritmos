#ifndef DUMP__H
#define DUMP__H

#include "simpletron.h"
#include "memoria.h"
#include "argumentos.h"

#define DUMP_MSJ_REGISTROS "\nREGISTROS"
#define DUMP_MSJ_ACUMULADOR "acumulador"
#define DUMP_MSJ_PROGRAM_COUNTER "program counter"
#define DUMP_MSJ_INSTRUCCION "instruccion"
#define DUMP_MSJ_OPCODE "opcode"
#define DUMP_MSJ_OPERANDO "operando"
#define DUMP_MSJ_MEMORIA "\nMEMORIA"

void imprimir_dump(simpletron_t * simpletron, vector_t * memoria, params_t * param);
void imprimir_dump_txt(simpletron_t * simpletron, vector_t * memoria, FILE * stream);
void imprimir_dump_bin(simpletron_t * simpletron, vector_t * memoria, FILE * stream);

#endif