#include "dump.h"
#include "simpletron.h"
#include "memoria.h"
#include "argumentos.h"

void imprimir_dump(simpletron_t * simpletron, vector_t * memoria, params_t * param){
    switch(param->archivo_salida->formato){
        case FMT_TXT:
            imprimir_dump_txt(simpletron, memoria, param->archivo_salida->stream);
        case FMT_BIN:
            imprimir_dump_bin(simpletron, memoria, param->archivo_salida->stream);
    }
}
void imprimir_dump_txt(simpletron_t * simpletron, vector_t * memoria, FILE * stream){
    size_t i,j;
    
    fprintf(stream, "\n%s:\n", DUMP_MSJ_REGISTROS);
    fprintf(stream, "%15s:   %5X\n", DUMP_MSJ_ACUMULADOR, simpletron->acumulador);
    fprintf(stream, "%15s:       %01ld\n", DUMP_MSJ_PROGRAM_COUNTER, simpletron->program_counter);
    fprintf(stream, "%15s: %+5d\n", DUMP_MSJ_INSTRUCCION, simpletron->instruccion);
    fprintf(stream, "%15s:   %5d\n", DUMP_MSJ_OPCODE, simpletron->opcode);
    fprintf(stream, "%15s:     %03d\n", DUMP_MSJ_OPERANDO, simpletron->operando);
    fprintf(stream, "%s:\n", DUMP_MSJ_MEMORIA);
    
    for (i = 0, j = 0; i < obtener_pedido(memoria); i++){
        if (!(i % 10))
            fprintf(stream, "\n%3ld:", j++ * 10);
        
        fprintf(stream, " %05X", obtener_dato(memoria, i + 1));
    }
    putchar('\n');
}
void imprimir_dump_bin(simpletron_t * simpletron, vector_t * memoria, FILE * stream){
    size_t i;
    palabra_t palabra;
    
    for (i = 0; i < obtener_pedido(memoria); i++){
        palabra = obtener_dato(memoria,i+1);
        fwrite(&palabra,sizeof(int),1,stream);
    }
}