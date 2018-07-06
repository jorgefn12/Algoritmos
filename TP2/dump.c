
/***************************************DUMP.C***********************************************************/
/*Para poder imprimir los registros en hexadecimal, tuve que cambiar el tipo de palabra_t por un unsigned int*/

#include <stdio.h>
#include <stdlib.h>
#include "dump.h"
#include "ejecutar_codigo.h" /*Necesita una función para recorrer memorias simpletron que tengo implementado en ejecutar_codigo*/
#include "comun.h"
#include "tipos.h"

*Luego de ejecutar todos los simpletron, dump imprime los registros de cada simpletron por separado dentro
*de un unico archivo comun: "dump"
*/

status_t imprimir_dump(simpletron_s * simpletron, params_s * param){
    status_t status;
    
    switch(param->archivo_salida.formato){
        case(FMT_TXT):
            while(simpletron){
                status = imprimir_dump_txt(simpletron, param);
                if(status != ST_OK)
                    return status;
                simpletron = simpletron->sig;
            }
            break;
        case(FMT_BIN):
            while(simpletron){
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
    fprintf(archivo_salida, "%15s:    %02d\n", DUMP_MSJ_OPERANDO, simpletron->operando);
    fprintf(archivo_salida, "%s:\n", DUMP_MSJ_MEMORIA);

    for (i = 0, j = 0; i < simpletron->archivo->cant_palabras; i++) {
        if (!(i % 10))
            fprintf(archivo_salida, "\n%3ld:", j++ * 10);
        
        fprintf(archivo_salida, " %+05d", avanzar_lista_n (simpletron->archivo->memoria, i)->dato);
    }
    puts("\n");
    fclose(archivo_salida);
    return ST_OK;
}
status_t imprimir_dump_bin(simpletron_s* simpletron, params_s * param){
    FILE * archivo_salida;
    size_t i;
    
    if ((archivo_salida = fopen(param->archivo_salida.nombre, "a")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    for (i = 0; i < simpletron->archivo->cant_palabras; i++) {
        if ((fwrite(&(avanzar_lista_n (simpletron->archivo->memoria, i)->dato), sizeof (int), 1, archivo_salida)) != 1)
            return ST_ERROR_ESCRIBIR_BIN;
    }
    fclose(archivo_salida);
    return ST_OK;
}
