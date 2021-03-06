#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

/*
Esta función se encarga de seleccionar dónde y de qué forma se debe leer el archivo de entrada
para la carga de memoria y delega dichas tareas a otras funciones.
Recibe como argumentos un archivo_t que indica el formato de entrada, una cadena con el nombre
del archivo y un puntero a la estructura del simpletron.
Retorna por el nombre el estado de la función.
 */
status_t leer_archivo(char *nombre_archivo_entrada, const archivo_t tipo_archivo_entrada, palabras_s *palabra) {
    status_t status;

    switch (tipo_archivo_entrada) {
            /*Si se ingreso -if bin*/
        case ARCHIVO_BIN:
            /*ENTRADA stdin*/
            if (strcmp(nombre_archivo_entrada, STR_STDIN) == 0) {
                return ST_ERROR_I_BIN_IF_NO_VALIDO;
            }

            /*ENTRADA archivo*/
            status = cargar_estructura_bin(palabra, nombre_archivo_entrada);

            break;
            /*Si se ingreso -if txt*/
        case ARCHIVO_TXT:
            /*ENTRADA stdin*/
            if (strcmp(nombre_archivo_entrada, STR_STDIN) == 0) {
                status = cargar_estructura_stdin(palabra);
                break;
            } else
                /*ENTRADA archivo*/
                status = cargar_estructura_txt(&palabra, nombre_archivo_entrada);
            break;
        default:
            status = ST_ERROR_ARCHIVO_NO_ENCONTRADO;
    }

    return status;
}

/*
Esta función carga la memoria del simpletron desde un archivo con formato de texto.
La función recibe un puntero doble a estructura (simpletron) y una cadena con el nombre del 
archivo de entrada.
Retorna por el nombre el estado de la función.
 */
status_t cargar_estructura_txt(palabras_s** palabra, char *nombre_archivo_entrada) {
    char * pch, *linea;
    FILE * archivo_entrada;
    int i = 0, j;

    /*Compruebo si el archivo existe*/
    if ((archivo_entrada = fopen(nombre_archivo_entrada, "r")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    linea = (char*) malloc(sizeof (char)*MAX_STR);
    if (linea == NULL)
        return ST_ERROR_MEM;

    if (((*palabra)->memoria = (int*) malloc(sizeof (int))) == NULL)
        return ST_ERROR_MEM;

    /*Obtengo una linea a la vez del archivo*/
    while (!feof(archivo_entrada) && (i < (*palabra)->cantidad_memoria)) {
        if ((fgets(linea, MAX_STR, archivo_entrada)) != NULL) {
            /*Descarto los comentarios*/
            pch = strtok(linea, INICIO_COMENTARIO);

            /*Guardo la palabra en la estructura*/
            (*palabra)->memoria[i] = strtol(linea, &pch, 10);
            i += 1;
            /*Pido memoria para agregar luego una palabra mas*/
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
    return ST_OK;
}

/*
Esta función carga la memoria del simpletron desde un archivo con formato binario.
La función recibe un puntero  a estructura (simpletron) y una cadena con el nombre del 
archivo de entrada.
Retorna por el nombre el estado de la función.
 */
status_t cargar_estructura_bin(palabras_s* palabra, char* nombre_archivo_entrada) {
    /*El archivo esta compuesto por enteros*/
    int i = 0, j;
    FILE * archivo_entrada_bin;

    /*Compruebo si dicho archivo binario pasado por la terminal existe*/
    if ((archivo_entrada_bin = fopen(nombre_archivo_entrada, "rb")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    if ((palabra->memoria = (int*) malloc(sizeof (int))) == NULL)
        return ST_ERROR_MEM;

    while (!feof(archivo_entrada_bin) && (i < palabra->cantidad_memoria)) {
        /*Pido memoria en el vector para guardar una palabra mas*/
        if ((palabra->memoria = (int*) realloc(palabra->memoria, sizeof (int)*(i + 1))) == NULL)
            return ST_ERROR_MEM;
        /*Guardo la palabra leida en la estructura*/
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

/*
Esta función carga la memoria del simpletron desde stdin con formato de texto.
La función recibe un puntero  a estructura (simpletron).
Retorna por el nombre el estado de la función.
 */
status_t cargar_estructura_stdin(palabras_s *palabras) {
    char *palabra_ingresada, *pch;
    int i = 0, aux;

    if ((palabra_ingresada = (char*) malloc(sizeof (char)*MAX_STR)) == NULL)
        return ST_ERROR_MEM;
    if ((palabras->memoria = (int*) malloc(sizeof (int))) == NULL)
        return ST_ERROR_MEM;

    printf("%s\n",MSJ_BIENVENIDO_SIMPLETRON);
    printf("%02d ? ", i);
    fgets(palabra_ingresada, MAX_STR, stdin);

    while (i < palabras->cantidad_memoria) {
        if ((strcmp(palabra_ingresada, FINALIZAR_CARGA)) != 0) {
            /*Pido memoria para guardar una palabra*/
            aux = strtol(palabra_ingresada, &pch, 10);
            /*Valido que contenga solamente un entero*/
            if (strlen(pch) == 1) {
                palabras->memoria[i] = aux;
                i++;
                /*Pido memoria para guardar una palabra*/
                if ((palabras->memoria = (int*) realloc(palabras->memoria, sizeof (int)*(i + 1))) == NULL)
                    return ST_ERROR_MEM;
            }
                /*Si no fue entero, ingresa nuevamente*/
            else {
                fprintf(stdout, "%s\n", MSJ_ERROR_INGRESO_PALABRA);
            }
            /*Pido al usario que ingrese otra palabra*/
            printf("%02d ? ", i);
            fgets(palabra_ingresada, MAX_STR, stdin);
        } else
            break;
    }

    /*Relleno el resto del vector con ceros*/
    for (; i < palabras->cantidad_memoria; i++) {
        if ((palabras->memoria = (int*) realloc(palabras->memoria, sizeof (int)*(i + 1))) == NULL)
            return ST_ERROR_MEM;
        palabras->memoria[i] = 0;
    }

    /*Se libera la memoria pedida para la variable auxiliar*/
    free(palabra_ingresada);

    return ST_OK;
}
