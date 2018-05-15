/*
CAMBIOS REALIZADOS

-validaciones de punteros
-cambié el prototipo de argumentos de archivos_t por archivos_t * en la función validar_argumentos

-en las validaciones por defecto de los archivos_i/archivo_f,
 se seteaba el default en tipo_archivo_i/tipo_archivo_f y no en el nombre del archivo

-break para salir del ciclo for en lugar de i = argc

-cambie MAX_STR en la funcion memcpy por strlen(arg[i+1]) + 1;

-cambie algunas validaciones para que cooncordara con lo que discutimos en el comedor

-agregué en main un procedimiento para visualizar los CLA al finalizar el programa

-agregué constantes STR_STDIN, STR_STDOUT para inicializar los nombres de los archivos en stdin/stdout

La función recibe argc y argv, y si todo salió bien devuelve la cantidad de memoria,
el nombre de los archivos y sus tipos, por los punteros que le pasaron.


FALTA:
Agregar la parte para validar el argumento -m que supongo que despues la agrega Alessandro

Me falta corregir que la función inicialice los nombres por defecto en los casos que lo necesite, 
por alguna razón me los está tomando mal.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POS_ARGV0 0
#define POS_ARGV1 1
#define POS_ARGV2 2
#define POS_ARGV3 3
#define POS_ARGV4 4
#define POS_ARGV5 5
#define POS_ARGV6 6
#define POS_ARGV7 7
#define POS_ARGV8 8
#define POS_ARGV9 9
#define POS_ARGV10 10

#define CLA_AYUDA "-h"
#define CLA_M "-m"
#define CLA_I "-i"
#define CLA_I_DEFAULT "-"
#define CLA_IF "-if"
#define CLA_IF_TXT "txt"
#define CLA_IF_BIN "bin"
#define CLA_O "-o"
#define CLA_OF "-of"

#define DEFAULT_M 50
#define MAX_STR 200
#define CANT_MAX_ARG 11
#define CANT_MIN_ARG 2

#define MSJ_MAS_AYUDA "Ingrese -h para mas ayuda"
#define MSJ_ERROR_IF_NO_VALIDO "El ingreso de archivo de entrada es invalido"
#define MSJ_ERROR_ARCHIVO_I_NO_INGRESADO "No se ingreso el archivo de entrada"
#define MSJ_ERROR_IF_NO_INGRESADO "No se ingreso el tipo de archivo de entrada"
#define MSJ_ERROR_OF_NO_VALIDO "El ingreso de archivo de salida es invalido"
#define MSJ_ERROR_OF_NO_INGRESADO "No se ingreso el tipo de archivo de salida"
#define MSJ_ERROR_CANT_ARG "La cantidad de argumentos ingresados no es valido"

#define STR_STDIN "stdin"
#define STR_STDOUT "stdout"

typedef enum {
    ST_OK,
    ST_ERROR_PTR_NULO,
    ST_ERROR_CANT_ARG,
    ST_HELP,
    ST_ERROR_ARCHIVO_I_NO_INGRESADO,
    ST_ERROR_IF_NO_VALIDO,
    ST_ERROR_IF_NO_INGRESADO,
    ST_ERROR_OF_NO_VALIDO,
    ST_ERROR_OF_NO_INGRESADO
} status_t;

typedef enum {
    TRUE, FALSE
} bool_t;

typedef enum {
    ARCHIVO_BIN,
    ARCHIVO_TXT,
    ARCHIVO_DEFAULT
} archivo_t;

/*En esta función se validan los argumentos pasados por la terminal*/
status_t validacion_cla(int argc, char **argv, int *m, char *archivo_i, archivo_t* tipo_archivo_i, char *archivo_f, archivo_t* tipo_archivo_f);
/*En procesar_linea se obtiene cada linea del lms*/
status_t procesar_linea(char *cadena);
void imprimir_errores(status_t status);

int main(int argc, char** argv) {
    status_t status;
    int memoria;
    char archivo_entrada[MAX_STR], archivo_salida[MAX_STR];
    archivo_t tipo_archivo_entrada, tipo_archivo_salida;

    if((status = validacion_cla(argc, argv, &memoria, archivo_entrada, &tipo_archivo_entrada, archivo_salida, &tipo_archivo_salida)) != ST_OK){
        imprimir_errores(status);

        printf("argc = %d\n", argc);
        printf("memoria = %d\n", memoria);
        printf("nombre archivo i = %s\n", archivo_entrada);
        printf("formato archivo i = %d\n", tipo_archivo_entrada);
        printf("nombre archivo f = %s\n", archivo_salida);
        printf("formato archivo f = %d\n", tipo_archivo_salida);

        return EXIT_FAILURE;
    }

    printf("argc = %d\n", argc);
    printf("memoria = %d\n", memoria);
    printf("nombre archivo i = %s\n", archivo_entrada);
    printf("formato archivo i = %d\n", tipo_archivo_entrada);
    printf("nombre archivo f = %s\n", archivo_salida);
    printf("formato archivo f = %d\n", tipo_archivo_salida);

    return EXIT_SUCCESS;
}

/*Esta funcion valida los argumentos pasados por la linea de comandos
 *El ingreso de argumentos en este caso no deben tener un orden especifico*/

status_t validacion_cla(int argc, char **argv, int *m, char *archivo_i, archivo_t * tipo_archivo_i, char *archivo_f, archivo_t * tipo_archivo_f){
    size_t i;
    char * p;
    bool_t encontrado = FALSE, encontrado_of = FALSE;

    if (argc > CANT_MAX_ARG || argc < CANT_MIN_ARG)
        return ST_ERROR_CANT_ARG;
    if(argv == NULL || m == NULL || archivo_i == NULL || tipo_archivo_i == NULL || archivo_f == NULL || tipo_archivo_f == NULL)
        return ST_ERROR_PTR_NULO;

    /*-----------------------------AYUDA-----------------------------
     * simpletron -h
     * Cuando se pide una ayuda solo se debe ingresar el comando de ayuda y nada mas*/
    if (argc == CANT_MIN_ARG && (strcmp(argv[POS_ARGV1], CLA_AYUDA)) == 0)
        return ST_HELP;

    /*-----------------------------MEMORIA-----------------------------
     * ./simpletron -m 23...
     * Si no se ingresa este argumento, por defecto sera de 50 palabras*/
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-m" en argv*/
        if (strcmp(argv[i], CLA_M) == 0) {
            *m = strtol(argv[i + 1], &p, 10);
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
            if ((strcmp(argv[i + 1], CLA_I_DEFAULT)) == 0) {
                archivo_i = STR_STDIN;
            } else {
                /*Guardo el nombre del archivo*/
                memcpy(archivo_i, argv[i + 1], strlen(argv[i+1]) + 1);
            }
            encontrado = TRUE;
            break;
        }
    }
    /*Si no se encontro el argumento -i*/
    if (encontrado != TRUE)
        return ST_ERROR_ARCHIVO_I_NO_INGRESADO;
    encontrado = FALSE;


    /*-----------------------------IF-----------------------------
     * Se obtiene si el tipo de archivo de entrada sera interpretado como bin o txt*/
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-if" en argv*/
        if (strcmp(argv[i], CLA_IF) == 0) {
            /*Se busca el tipo de archivo de entrada: txt, bin*/
            if ((strcmp(argv[i + 1], CLA_IF_BIN)) == 0) {
                *tipo_archivo_i = ARCHIVO_BIN;
            } else if ((strcmp(argv[i + 1], CLA_IF_TXT)) == 0) {
                *tipo_archivo_i = ARCHIVO_TXT;
            } else
                return ST_ERROR_IF_NO_VALIDO;
            encontrado = TRUE;
            break;
        }
    }

    if (encontrado != TRUE)
        /*Si no se encuentra el argumento "-if"*/
        return ST_ERROR_IF_NO_INGRESADO;
    encontrado = FALSE;

    /*-----------------------------O-----------------------------
     * No es obligatorio ingresar esta opcion */
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-o" en argv*/
        if ((strcmp(argv[i], CLA_O)) == 0) {
            /*Copio el nombre del archivo de salida*/
            memcpy(archivo_f, argv[i + 1], strlen(argv[i + 1]) + 1);
            encontrado = TRUE;
            break;
        }
    }

    /*Si no se encontro el argumento o se tomara como default stdout*/
    if (encontrado != TRUE)
        archivo_f = STR_STDOUT;


    /*-----------------------------OF-----------------------------
     * Se obtiene si el tipo de archivo de salida sera interpretado como bin o txt*/

    /*Si se ingreso -o, se debe ingresar -of*
    *si no se ingreso -o, se puede ingresar -of*/
    for (i = 0; i < argc; i++) {
        /*Se busca el argumento "-of" en argv*/
        if (strcmp(argv[i], CLA_OF) == 0) {
            /*Se busca el tipo de archivo de entrada: txt, bin*/
            if ((strcmp(argv[i + 1], CLA_IF_BIN)) == 0) {
                *tipo_archivo_f = ARCHIVO_BIN;
            } else if ((strcmp(argv[i + 1], CLA_IF_TXT)) == 0) {
                *tipo_archivo_f = ARCHIVO_TXT;
            } else
                return ST_ERROR_OF_NO_VALIDO;
            encontrado_of = TRUE;
            break;
        }
    }
    if(encontrado != TRUE && encontrado_of != TRUE)
        *tipo_archivo_f = ARCHIVO_TXT; /*por defecto se interpreta como txt, 
                                        sólamente si no se ingreso -o"*/

    else if (encontrado == TRUE && encontrado_of != TRUE)
        /*Si no se encuentra el argumento "-of" y sí se ingresa "-o"*/
        return ST_ERROR_OF_NO_INGRESADO;

    return ST_OK;
}



void imprimir_errores(status_t status) {
    if (status == ST_HELP)
        fprintf(stderr, "%s\n", "IMPRIMIENDO AYUDA");

    if (status == ST_ERROR_CANT_ARG)
        fprintf(stderr, "%s. %s\n", MSJ_ERROR_CANT_ARG, MSJ_MAS_AYUDA);
    
    if (status == ST_ERROR_ARCHIVO_I_NO_INGRESADO)
        fprintf(stderr, "%s. %s\n", MSJ_ERROR_ARCHIVO_I_NO_INGRESADO, MSJ_MAS_AYUDA);

    if (status == ST_ERROR_IF_NO_VALIDO)
        fprintf(stderr, "%s. %s\n", MSJ_ERROR_IF_NO_VALIDO, MSJ_MAS_AYUDA);

    if (status == ST_ERROR_IF_NO_INGRESADO)
        fprintf(stderr, "%s. %s\n", MSJ_ERROR_IF_NO_INGRESADO, MSJ_MAS_AYUDA);

    if (status == ST_ERROR_OF_NO_VALIDO)
        fprintf(stderr, "%s. %s\n", MSJ_ERROR_OF_NO_VALIDO, MSJ_MAS_AYUDA);

    if (status == ST_ERROR_OF_NO_INGRESADO)
        fprintf(stderr, "%s. %s\n", MSJ_ERROR_OF_NO_INGRESADO, MSJ_MAS_AYUDA);
}
