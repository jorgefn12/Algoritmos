#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

status_t leer_archivo(char *nombre_archivo_entrada, const archivo_t tipo_archivo_entrada, palabras_s *palabra) {
    status_t status;

    switch (tipo_archivo_entrada) {
        case ARCHIVO_BIN:
            /*ENTRADA stdin*/
            if (strcmp(nombre_archivo_entrada, STR_STDIN) == 0) {
                /*
                                status = cargar_estructura_stdin(palabra, &palabra->program_counter);
                 */
                break;
            }

            /*ENTRADA archivo*/
            status = cargar_estructura_bin(palabra, nombre_archivo_entrada);

            break;
        case ARCHIVO_TXT:
            /*ENTRADA stdin*/
            if (strcmp(nombre_archivo_entrada, STR_STDIN) == 0) {
                status = cargar_estructura_stdin(palabra);
                break;
            } else
                status = cargar_estructura_txt(&palabra, nombre_archivo_entrada);
            break;
        default:
            status = ST_ERROR_ARCHIVO_NO_ENCONTRADO;
    }

    return status;
}

status_t cargar_estructura_txt(palabras_s** palabra, char *nombre_archivo_entrada) {
    char * pch, *linea;
    status_t status = ST_OK;
    FILE * archivo_entrada;
    int i = 0, j;

    linea = (char*) malloc(sizeof (char)*MAX_STR);
    if (linea == NULL)
        return ST_ERROR_MEM;

    if ((archivo_entrada = fopen(nombre_archivo_entrada, "r")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    if (((*palabra)->memoria = (int*) malloc(sizeof (int))) == NULL)
        return ST_ERROR_MEM;

    while (!feof(archivo_entrada) && (i < (*palabra)->cantidad_memoria)) {
        if ((fgets(linea, MAX_STR, archivo_entrada)) != NULL) {
            /*Descarto los comentarios*/
            pch = strtok(linea, INICIO_COMENTARIO);

            /*Guardo la palabra en la estructura*/
            (*palabra)->memoria[i] = strtol(linea, &pch, 10);
            i += 1; /*Poner uno en define?*/
            if (((*palabra)->memoria = (int*) realloc((*palabra)->memoria, sizeof (int)*(i + 1))) == NULL)
                return ST_ERROR_MEM;
        }
    }

    /*Cargo el resto de la memoria pedida con ceros*/
    for (j = i; j < (*palabra)->cantidad_memoria; j++) {
        if (((*palabra)->memoria = (int*) realloc((*palabra)->memoria, sizeof (int)*(j + 1))) == NULL)
            return ST_ERROR_PTR_NULO;
        (*palabra)->memoria[j] = 0;
    }

    fclose(archivo_entrada);
    free(linea);
    return status;
}

status_t cargar_estructura_bin(palabras_s* palabra, char* nombre_archivo_entrada) {
    /*El archivo esta compuesto por enteros*/
    int i = 0, j;
    FILE * archivo_entrada_bin;

    if((palabra->memoria = (int*) malloc(sizeof (int)))==NULL)
        return ST_ERROR_MEM;

    if ((archivo_entrada_bin = fopen(nombre_archivo_entrada, "rb")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    while (!feof(archivo_entrada_bin) && (i < palabra->cantidad_memoria)) {
        if((palabra->memoria = (int*) realloc(palabra->memoria, sizeof (int)*(i + 1)))==NULL)
            return ST_ERROR_MEM;
        if ((fread(&palabra->memoria[i], sizeof (int), 1, archivo_entrada_bin)) == 1)
            i++;
    }

    /*Cargo el resto de la memoria pedida con ceros*/
    for (j = i; j < palabra->cantidad_memoria; j++) {
        if ((palabra->memoria = (int*) realloc(palabra->memoria, sizeof (int)*(j + 1))) == NULL)
            return ST_ERROR_PTR_NULO;
        palabra->memoria[j] = 0;
    }

    fclose(archivo_entrada_bin);
    return ST_OK;
}

status_t cargar_estructura_stdin(palabras_s *palabras) {
    char *palabra_ingresada, *pch;
    int i = 0, aux;

    if ((palabra_ingresada = (char*) malloc(sizeof (char)*MAX_STR)) == NULL)
        return ST_ERROR_MEM;
    if ((palabras->memoria = (int*) malloc(sizeof (int))) == NULL)
        return ST_ERROR_MEM;

    printf("%s ", MSJ_INGRESO_PALABRA);
    fgets(palabra_ingresada, MAX_STR, stdin);

    while (i < palabras->cantidad_memoria) {
        if ((strcmp(palabra_ingresada, FINALIZAR_CARGA)) != 0) {
            /*Pido memoria para guardar una palabra*/
            aux = strtol(palabra_ingresada, &pch, 10);

            if (strlen(pch) == 1) {
                palabras->memoria[i] = aux;
                i++;
                if ((palabras->memoria = (int*) realloc(palabras->memoria, sizeof (int)*(i + 1))) == NULL)
                    return ST_ERROR_MEM;

                printf("%s ", MSJ_INGRESO_PALABRA);
                fgets(palabra_ingresada, MAX_STR, stdin);
            } else {
                fprintf(stdout, "%s\n", MSJ_ERROR_INGRESO_PALABRA);
                printf("%s ", MSJ_INGRESO_PALABRA);
                fgets(palabra_ingresada, MAX_STR, stdin);
            }
        } else
            break;
    }

    for (; i < palabras->cantidad_memoria; i++) {
        if ((palabras->memoria = (int*) realloc(palabras->memoria, sizeof (int)*(i + 1))) == NULL)
            return ST_ERROR_MEM;
        palabras->memoria[i] = 0;
    }

    free(palabra_ingresada);

    return ST_OK;
}
