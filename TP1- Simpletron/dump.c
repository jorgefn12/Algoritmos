#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

status_t dump(archivo_t tipo_archivo_salida, char* nombre_archivo_salida, palabras_s palabra) {
    status_t status = ST_OK;

    switch (tipo_archivo_salida) {
        case ARCHIVO_TXT:
            status = imprimir_dump_por_stdout_o_txt(palabra, nombre_archivo_salida, tipo_archivo_salida);
            break;
        case ARCHIVO_BIN:
            if (strcmp(nombre_archivo_salida, STR_STDOUT) == 0) {
                memcpy(nombre_archivo_salida, NOMBRE_GENERICO_ARCHIVO_BIN, strlen(NOMBRE_GENERICO_ARCHIVO_BIN) + 1);
            }
            status = imprimir_dump_bin(palabra, nombre_archivo_salida, tipo_archivo_salida);
            break;
        case ARCHIVO_DEFAULT:
            /*No se ingreso -o ni -of*/
            status = imprimir_dump_por_stdout_o_txt(palabra, nombre_archivo_salida, tipo_archivo_salida);
            break;
        default:
            puts("default");
            break;
    }

    return status;
}

status_t imprimir_dump_por_stdout_o_txt(palabras_s palabra, char *nombre_archivo_salida, archivo_t tipo_archivo_salida) {
    int i, j;
    FILE *archivo_salida;

    if (tipo_archivo_salida == ARCHIVO_DEFAULT)
        archivo_salida = stdout;
    else if (tipo_archivo_salida == ARCHIVO_TXT) {
        archivo_salida = fopen(nombre_archivo_salida, "w+");
        if (archivo_salida == NULL) {
            return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
        }
    }

    fprintf(archivo_salida, "%s:\n", DUMP_MSJ_INICIO);
    fprintf(archivo_salida, "%15s: %5ld\n", DUMP_MSJ_ACUMULADOR, palabra.acumulador);
    fprintf(archivo_salida, "%15s:    %02d\n", DUMP_MSJ_PROGRAM_COUNTER, palabra.program_counter);
    fprintf(archivo_salida, "%15s: %+5d\n", DUMP_MSJ_INSTRUCCION, palabra.instruccion);
    fprintf(archivo_salida, "%15s:    %02d\n", DUMP_MSJ_OPCODE, palabra.opcode);
    fprintf(archivo_salida, "%15s:    %02d\n", DUMP_MSJ_OPERANDO, palabra.operando);
    fprintf(archivo_salida, "%s:\n", DUMP_MSJ_MEMORIA);


    for (i = 0; i < 10; i++)
        fprintf(archivo_salida, "%6d", i);
    /*
    fprintf(archivo_salida, "\n");
     */
    for (i = 0, j = 0; i < palabra.cantidad_memoria; i++) {
        if (i % 10 == 0) {
            fprintf(archivo_salida, "\n%2d", j * 10);
            j++;
        }
        fprintf(archivo_salida, " %+05d", palabra.memoria[i]);
    }
    puts("\n");

    if (tipo_archivo_salida == ARCHIVO_TXT)
        fclose(archivo_salida);
    return ST_OK;
}

status_t imprimir_dump_bin(palabras_s palabra, char *nombre_archivo_salida, archivo_t tipo_archivo_salida) {
    int i;
    FILE *archivo_salida;

    if ((archivo_salida = fopen(nombre_archivo_salida, "w")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    for (i = 0; i < palabra.cantidad_memoria; i++) {
        if ((fwrite(&(palabra.memoria[i]), sizeof (int), 1, archivo_salida)) != 1)
            return ST_ERROR_ESCRIBIR_BIN;
    }
    
    fclose(archivo_salida);
    return ST_OK;
}

