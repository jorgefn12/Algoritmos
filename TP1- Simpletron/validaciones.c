#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

/*Esta funcion valida los argumentos pasados por la linea de comandos
 *El ingreso de argumentos en este caso no deben tener un orden especifico*/

status_t validacion_cla(int argc, char **argv, size_t *m, char **archivo_i, archivo_t *tipo_archivo_i, char **archivo_f, archivo_t *tipo_archivo_f) {
    size_t i;
    char * p;
    long temp;
    bool_t encontrado = FALSE, encontrado_of = FALSE, cat = FALSE;

    /*Se verifica que la cantidad de argumentos ingresados sean correctas*/
    if (argc > CANT_MAX_ARG || argc < CANT_MIN_ARG)
        return ST_ERROR_CANT_ARG;
    /*Pido memoria para guardar los nombres de los archivos de entrada y salida*/
    *archivo_i = (char*) malloc(sizeof (char)*MAX_STR);
    *archivo_f = (char*) malloc(sizeof (char)*MAX_STR);
    /*Verifico que los punteros no sean nulos*/
    if (argv == NULL || m == NULL || archivo_i == NULL || tipo_archivo_i == NULL || archivo_f == NULL || tipo_archivo_f == NULL)
        return ST_ERROR_PTR_NULO;
    /*-----------------------------AYUDA-----------------------------
     * Forma de ejecutar: ./simpletron -h
     * Cuando se pide una ayuda solo se debe ingresar el comando de ayuda y nada mas*/
    if (argc == CANT_MIN_ARG && (strcmp(argv[POS_ARGV1], CLA_AYUDA)) == 0)
        return ST_HELP;


    /*-----------------------------CAT-----------------------------*/
    if (cat_ingresado(argv, &archivo_i) == ST_OK)
        cat = TRUE;


    /*-----------------------------MEMORIA-----------------------------
     * Forma de ejecutar: ./simpletron -m 23...
     * Si no se ingresa este argumento, por defecto sera de 50 palabras*/
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-m" en argv*/
        if (strcmp(argv[i], CLA_M) == 0) {
            temp = strtol(argv[i + 1], &p, 10);
            /* Se comprueba que sea un entero positivo*/
            if (temp < 0)
                return ST_ERROR_M_INVALIDO;
            if (*p != '\n' && *p != '\0')
                return ST_ERROR_M_INVALIDO;
            *m = temp;
            break;
        } else {
            /*Si no se encuentra se asigna 50 por default*/
            *m = DEFAULT_M;
        }
    }



    /*-----------------------------ARCHIVO I-----------------------------
     * Se obtiene el archivo pasado por linea de comandos*/
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-i" en argv*/
        if ((strcmp(argv[i], CLA_I)) == 0) {
            /*Caso en el que el usuario ingresa: cat archivo | m -i -[...]*/
            if ((strcmp(argv[i + 1], CLA_I_DEFAULT)) == 0 && cat == TRUE) {
                break;
            }                
            /*Si el usuario ingresa quiere ingresar palabras por stdin debe ingresar: "-i stdin"*/
            else if ((strcmp(argv[i + 1], STR_STDIN)) == 0) {
                *tipo_archivo_i = ARCHIVO_DEFAULT;
                memcpy(*archivo_i, STR_STDIN, strlen(STR_STDIN) + 1);
            } else {
                /*Si se ingreso el nombre del archivo de entrada lo guardo*/
                memcpy(*archivo_i, argv[i + 1], strlen(argv[i + 1]) + 1);
            }
            /*Se encontro el argumento -i*/
            encontrado = TRUE;
            break;
        }
    }


    /*Si no se encontro el argumento -i ni cat devuelvo un error, dado que el mismo es obligatorio*/
    if (encontrado != TRUE && cat != TRUE) {
        return ST_ERROR_ARCHIVO_I_NO_INGRESADO;
    }
    /*Reseteo la variable para usarla nuevamente*/
    encontrado = FALSE;


    /*-----------------------------IF-----------------------------
     * Se obtiene si el tipo de archivo de entrada sera interpretado como bin o txt*/
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-if" en argv*/
        if (strcmp(argv[i], CLA_IF) == 0) {
            /*Se busca el tipo de archivo de entrada: txt, bin*/
            if ((strcmp(argv[i + 1], CLA_IF_OPT_BIN)) == 0) {
                *tipo_archivo_i = ARCHIVO_BIN;
            } else if ((strcmp(argv[i + 1], CLA_IF_OPT_TXT)) == 0) {
                *tipo_archivo_i = ARCHIVO_TXT;
            } else {
                /*Si se ingreso un tipo de archivo distinto de txt o bin, devuelve un error*/
                return ST_ERROR_IF_NO_VALIDO;
            }
            encontrado = TRUE; /*Se encontro el argumento -if*/
            break;
        }
    }
    /*Si no se encuentra el argumento "-if"*/
    if (encontrado != TRUE)
        return ST_ERROR_IF_NO_INGRESADO;

    /*Reseteo la variable para usarla nuevamente*/
    encontrado = FALSE;


    /*-----------------------------O-----------------------------
     * No es obligatorio ingresar esta opcion */
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-o" en argv*/
        if ((strcmp(argv[i], CLA_O)) == 0) {
            /*Copio el nombre del archivo de salida que se supone que se ingresa luego del argumento -o*/
            memcpy(*archivo_f, argv[i + 1], strlen(argv[i + 1]) + 1);
            encontrado = TRUE; /*Se encontro el flag -o*/
            break;
        }
    }

    /*Si no se encontro el argumento -o se tomara como default stdout*/
    if (encontrado != TRUE) {
        *tipo_archivo_f = ARCHIVO_DEFAULT;
        memcpy(*archivo_f, STR_STDOUT, strlen(STR_STDOUT) + 1);
    }
    /*-----------------------------OF-----------------------------
     * Se obtiene si el tipo de archivo de salida sera interpretado como bin o txt*/
    /*Si se ingreso -o, se debe ingresar -of*
     *si no se ingreso -o, se puede ingresar -of o no*/
    for (i = 0; i < argc; i++) {
        /*Se busca el argumento "-of" en argv*/
        if (strcmp(argv[i], CLA_OF) == 0) {
            /*Se busca el tipo de archivo de entrada: txt, bin*/
            if ((strcmp(argv[i + 1], CLA_IF_OPT_BIN)) == 0) {
                *tipo_archivo_f = ARCHIVO_BIN;
            } else if ((strcmp(argv[i + 1], CLA_IF_OPT_TXT)) == 0) {
                *tipo_archivo_f = ARCHIVO_TXT;
            } else
                return ST_ERROR_OF_NO_VALIDO; /*El tipo de archivo de salida no es txt ni bin*/
            encontrado_of = TRUE;
            break;
        }
    }
    /*Si no se ingreso -o ni -of: la salida sera stdout en txt*/
    if (encontrado != TRUE && encontrado_of != TRUE)
        *tipo_archivo_f = ARCHIVO_DEFAULT;

        /*Si se ingreso -o y no se ingreso -of*/
    else if (encontrado == TRUE && encontrado_of != TRUE) {
        *tipo_archivo_f = ARCHIVO_TXT;
    }
    return ST_OK;
}

/*Si se ingresa cat, va seguido del nombre del archivo de entrada*/

/* PROCEDIMIENTO:
 * 1) identificar si se ingreso cat
 * 2) obtener el string siguiente a cat, ese es el nombre del archivo de entrada
 * 3) debe continuar con un |
 * 4) cuando se ingresa el archivo por cat, -i no es obligatorio
 */
status_t cat_ingresado(char **argv, char ***archivo_entrada) {
    if (strcmp(argv[POS_ARGV0], "cat") == 0 && (strcmp(argv[POS_ARGV2], "|") == 0)) {
        memcpy(*archivo_entrada, argv[POS_ARGV1], strlen(argv[POS_ARGV1] + 1));
    } else
        return ST_CAT_NO_INGRESADO;

    return ST_OK;
}
