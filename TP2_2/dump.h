#ifndef DUMP__H
#define DUMP__H

#define DUMP_MSJ_REGISTROS "\nREGISTROS:"
#define DUMP_MSJ_ACUMULADOR "acumulador"
#define DUMP_MSJ_PROGRAM_COUNTER "program counter"
#define DUMP_MSJ_INSTRUCCION "instruccion"
#define DUMP_MSJ_OPCODE "opcodo"
#define DUMP_MSJ_OPERANDO "operando"
#define DUMP_MSJ_MEMORIA "\nMEMORIA"

status_t imprimir_dump(simpletron_s * simpletron, params_s * param);
status_t imprimir_dump_txt(simpletron_s* simpletron, params_s * param);
status_t imprimir_dump_bin(simpletron_s* simpletron, params_s * param);

#endif
