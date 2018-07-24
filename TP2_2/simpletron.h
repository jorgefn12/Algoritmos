#ifndef SIMPLETRON__H
#define SIMPLETRON__H

#include "tipos.h"
#include "memoria.h"
#include "argumentos.h"
#include <stdlib.h>

#define MSJ_BIENVENIDO_SIMPLETRON "*** ¡Bienvenido a la Simpletron!         ***\n*** Por favor, ingrese su programa una   ***\n*** instrucción (o dato) a la vez. Yo    ***\n*** escribiré la ubicacíón y un signo de ***\n*** pregunta (?). Luego usted ingrese la ***\n*** palabra para esa ubicación. Ingrese  ***\n*** -99999999 para finalizar:            ***"
#define MSJ_COMIENZO_EJECUCION "******** INICIO DE EJECUCION DEL SIMPLETRON *******"
#define MSJ_COMIENZO_ARCHIVO "Ejecutando un nuevo archivo"
#define MSJ_FIN_ARCHIVO "Fin de ejecución del archivo"
#define MSJ_FIN_EJECUCION "********* FIN DE EJECUCION DEL SIMPLETRON *********"
#define MSJ_INGRESO_PALABRA "Ingrese una palabra: "
#define MSJ_IMPRIMIR_PALABRA "Contenido de la posición"

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
typedef struct simpletron{
    palabra_t instruccion, acumulador;
    opcode_t opcode;
    uint operando;
    size_t program_counter;
    vector_t ** memoria; /*Se guarda una memororia por cada archivo*/
}simpletron_t;
typedef status_t (*pfx_lms)(simpletron_t *, vector_t *);
bool_t crear_simpletron(params_t * param, simpletron_t ** simpletron);
void destruir_simpletron(simpletron_t ** simpletron, params_t * param);
bool_t palabra_es_valida(palabra_t palabra);
status_t ejecutar_codigo(simpletron_t * simpletron, params_t * param);
status_t lms_leer(simpletron_t * simpletron, vector_t * memoria);
status_t lms_escribir(simpletron_t * simpletron, vector_t * memoria);
status_t lms_cargar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_guardar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_pcargar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_pguardar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_sumar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_restar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_dividir(simpletron_t * simpletron, vector_t * memoria);
status_t lms_multiplicar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_jmp(simpletron_t * simpletron, vector_t * memoria);
status_t lms_jmpneg(simpletron_t * simpletron, vector_t * memoria);
status_t lms_jmpzero(simpletron_t * simpletron, vector_t * memoria);
status_t lms_jnz(simpletron_t * simpletron, vector_t * memoria);
status_t lms_djnz(simpletron_t * simpletron, vector_t * memoria);
status_t lms_halt(simpletron_t * simpletron, vector_t * memoria);

#endif