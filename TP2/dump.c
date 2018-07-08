

#include <stdio.h>
#include <stdlib.h>
#include "dump.h"
#include "ejecutar_codigo.h"
#include "comun.h"
#include "tipos.h"

/*Esta función recibe un puntero a estructura simpletron, e imprime sus registros y memoria de forma independiente en un mismo
*archivo dump. Dependiendo del tipo de formato de salida, esta función delega el procesamiento por texto o binario a otras
*funciones. Al finalizar retorna el estado de la función.
*/

status_t imprimir_dump(simpletron_s * simpletron, params_s * param){
    status_t status;
    
    switch(param->archivo_salida.formato){
        case(FMT_TXT):
            while(simpletron->sig){
                status = imprimir_dump_txt(simpletron, param);
                if(status != ST_OK)
                    return status;
                simpletron = simpletron->sig;
            }
            break;
        case(FMT_BIN):
            while(simpletron->sig){
                status = imprimir_dump_bin(simpletron, param);
                if(status != ST_OK)
                    return status;
                simpletron = simpletron->sig;
            }
            break;
    }
    return ST_OK;
}
status_t imprimir_dump_txt(simpletron_s* simpletron, params_s * param){
    size_t i,j;
    FILE * archivo_salida;
    
    if ((archivo_salida = fopen(param->archivo_salida.nombre, "a")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    fprintf(archivo_salida, "%s:\n", DUMP_MSJ_REGISTROS);
    fprintf(archivo_salida, "%15s: %5x\n", DUMP_MSJ_ACUMULADOR, simpletron->acumulador);
    fprintf(archivo_salida, "%15s:    %02ld\n", DUMP_MSJ_PROGRAM_COUNTER, simpletron->program_counter);
    fprintf(archivo_salida, "%15s: %+5d\n", DUMP_MSJ_INSTRUCCION, simpletron->instruccion);
    fprintf(archivo_salida, "%15s:    %02d\n", DUMP_MSJ_OPCODE, simpletron->opcode);
    fprintf(archivo_salida, "%15s:    %03d\n", DUMP_MSJ_OPERANDO, simpletron->operando);
    fprintf(archivo_salida, "%s:\n", DUMP_MSJ_MEMORIA);

    for (i = 0, j = 0; simpletron->archivo->memoria != NULL; i++) {
        if (!(i % 10))
            fprintf(archivo_salida, "\n%3ld:", j++ * 10);
        
        fprintf(archivo_salida, " %+05d", simpletron->archivo->memoria->dato);
        simpletron->archivo->memoria = avanzar_lista_n (simpletron->archivo->memoria, 1);
    }
    fclose(archivo_salida);
    return ST_OK;
}
status_t imprimir_dump_bin(simpletron_s* simpletron, params_s * param){
    FILE * archivo_salida;
    size_t i;
    
    if ((archivo_salida = fopen(param->archivo_salida.nombre, "a")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    for (i = 0; simpletron->archivo->memoria != NULL; i++) {
        if ((fwrite(&(avanzar_lista_n (simpletron->archivo->memoria, i)->dato), sizeof (int), 1, archivo_salida)) != 1)
            return ST_ERROR_ESCRIBIR_BIN;
    }
    fclose(archivo_salida);
    return ST_OK;
}
