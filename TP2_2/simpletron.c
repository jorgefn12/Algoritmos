/*Definiciones de TDA Simpletron, tipos que maneja y funciones de ejecucion*/
#include "simpletron.h"
#include "tipos.h"
#include "comun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

simpletron_t * crear_simpletron(params_t * param){
    simpletron_t * simpletron = NULL;
    if(param == NULL)
        return NULL;
    if((simpletron = (simpletron_t *)malloc( sizeof(simpletron_t))) == NULL)
        return NULL;
    if((simpletron->memoria = (vector_t **)calloc(1, sizeof(vector_t*) * param->cant_archivos)) == NULL){
        destruir_simpletron(&simpletron);
        return NULL;
    }
    return simpletron;
}
void destruir_simpletron(simpletron_t ** simpletron){
    if(simpletron && *simpletron){
        if((*simpletron)->memoria){
            free((*simpletron)->memoria);
            (*simpletron)->memoria = NULL;
        }
        free(*simpletron);
        *simpletron = NULL;
    }
}
void imprimir_registros_simpletron(simpletron_t * simpletron, FILE * stream){
    puts("Imprimiendo registros:");
    if(simpletron == NULL){
        puts("NULL");
        return;
    }
    fprintf(stream, "acumulador: %d\n",simpletron->acumulador);
    fprintf(stream, "instruccion: %d\n",simpletron->instruccion);
    fprintf(stream, "opcode: %d\n",simpletron->opcode);
    fprintf(stream, "operando: %d\n",simpletron->operando);
    fprintf(stream, "program_counter: %lu\n",simpletron->program_counter);
}
bool_t palabra_es_valida(palabra_t palabra){
    int operando, opcode;
    
    if (palabra > MAX_PALABRA || palabra < MIN_PALABRA)
        return FALSE;

    operando = palabra % OPCODE_OPERANDO_MULTIPLIER;
    if (operando < OPERANDO_MIN || operando > OPERANDO_MAX)
        return FALSE;

    opcode = palabra / OPCODE_OPERANDO_MULTIPLIER;
    if (opcode < OPCODE_FIELD_MIN || opcode > OPCODE_FIELD_MAX)
        return FALSE;

    return TRUE;
}
