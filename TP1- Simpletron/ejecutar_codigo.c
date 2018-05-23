#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

status_t ejecutar_codigo(palabras_s * palabra) {
    char aux[MAX_STR]; /*Cadena auxiliar en donde se valida lo que ingresa el usuario*/
    long temp; /*Guardo enteros para validar antes de guardarlos en memoria*/
    char* p; /*Puntero auxiliar*/
    size_t i;

    /*Valida que los enteros estén dentro del rango*/
    for (i = 0; i < palabra->cantidad_memoria; i++) {
        if (palabra->memoria[i] < MIN_PALABRA || palabra->memoria[i] > MAX_PALABRA) {
            return ST_ERROR_PALABRA_FUERA_DE_RANGO;
        }
    }

    /*Comienza ejecución*/
    puts(MSJ_COMIENZO_EJECUCION);
    for (palabra->program_counter = 0; palabra->program_counter < MAX_INSTRICCIONES; palabra->program_counter++) {
        palabra->instruccion = palabra->memoria[palabra->program_counter];
        palabra->operando = palabra->instruccion % 100;
        palabra->opcode = palabra->instruccion / 100;
        /*valida que el operando pueda ser accedido*/
        if (palabra->operando > palabra->cantidad_memoria || palabra->operando < INIT_INSTRUCCIONES) {
            puts(MSJ_FIN_EJECUCION);
            return ST_ERROR_SEGMENTATION_FAULT;
        }

        switch (palabra->opcode) {
            case LEER:
                printf(MSJ_INGRESO_PALABRA);
                if (fgets(aux, MAX_STR, stdin) == NULL) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_CAD_NO_LEIDA;
                }
                if ((temp = strtol(aux, &p, 10)) < MIN_PALABRA || temp > MAX_PALABRA) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_PALABRA_FUERA_DE_RANGO;
                }
                if (*p != '\n' && *p != '\0' && *p != EOF) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_CAD_NO_ES_ENTERO;
                }
                palabra->memoria[palabra->operando] = temp;
                break;
            case ESCRIBIR:
                printf("%s %i: %i\n", MSJ_IMPRIMIR_PALABRA, palabra->operando, palabra->memoria[palabra->operando]);
                break;
            case CARGAR:
                palabra->acumulador = palabra->memoria[palabra->operando];
                break;
            case GUARDAR:
                if (palabra->acumulador < MIN_PALABRA || palabra->acumulador > MAX_PALABRA) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_PALABRA_FUERA_DE_RANGO;
                }
                palabra->memoria[palabra->operando] = palabra->acumulador;
                break;
            case PCARGAR:
                if (palabra->memoria[palabra->operando] > palabra->cantidad_memoria || palabra->memoria[palabra->operando] < INIT_INSTRUCCIONES) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_SEGMENTATION_FAULT;
                }
                palabra->acumulador = palabra->memoria[palabra->memoria[palabra->operando]];
                break;
            case PGUARDAR:
                if (palabra->memoria[palabra->operando] > palabra->cantidad_memoria || palabra->memoria[palabra->operando] < INIT_INSTRUCCIONES) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_SEGMENTATION_FAULT;
                }
                palabra->memoria[palabra->memoria[palabra->operando]] = palabra->acumulador;
                break;
            case SUMAR:
                palabra->acumulador += palabra->memoria[palabra->operando];
                break;
            case RESTAR:
                palabra->acumulador -= palabra->memoria[palabra->operando];
                break;
            case DIVIDIR:
                palabra->acumulador /= palabra->memoria[palabra->operando];
                break;
            case MULTIPLICAR:
                palabra->acumulador *= palabra->memoria[palabra->operando];
                break;
            case JMP:
                palabra->program_counter = palabra->operando - 1;
                break;
            case JMPNEG:
                if (palabra->acumulador < 0) {
                    palabra->program_counter = palabra->operando - 1;
                }
                break;
            case JMPZERO:
                if (!palabra->acumulador)
                    palabra->program_counter = palabra->operando - 1;
                break;
            case JNZ:
                if (palabra->acumulador)
                    palabra->program_counter = palabra->operando - 1;
                break;
            case DJNZ:
                palabra->acumulador--;
                if (palabra->acumulador)
                    palabra->program_counter = palabra->operando - 1;
                break;
            case HALT:
                puts(MSJ_FIN_EJECUCION);
                return ST_OK;
            default:
                puts(MSJ_FIN_EJECUCION);
                return ST_ERROR_OPCODE_INVALIDO;
        }
    }
    puts(MSJ_FIN_EJECUCION);
    return ST_ERROR_MAX_INSTR_SUPERADO;
}