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

typedef enum {
    ST_OK,
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
status_t validacion_cla(int argc, char **argv, int *m, char *archivo_i, archivo_t tipo_archivo_i, char *archivo_f, archivo_t tipo_archivo_f);
/*En procesar_linea se obtiene cada linea del lms*/
status_t procesar_linea(char *cadena);
void imprimir_errores(status_t status);

int main(int argc, char** argv) {
    status_t status;
    
    printf("argc = %d\n", argc);
    return EXIT_SUCCESS;
}

/*Esta funcion valida los argumentos pasados por la linea de comandos
 *El ingreso de argumentos en este caso no deben tener un orden especifico*/
status_t validacion_cla(int argc, char **argv, int *m, char *archivo_i, archivo_t tipo_archivo_i, char *archivo_f, archivo_t tipo_archivo_f) {
    size_t i;
    char * p;
    bool_t encontrado = FALSE, encontrado_of = FALSE;

    if (argc > CANT_MAX_ARG || argc<CANT_MIN_ARG)
        return ST_ERROR_CANT_ARG;

    /*-----------------------------AYUDA-----------------------------
     * simpletron -h
     * Cuando se pide una ayuda solo se debe ingresar el comando de ayuda y nada mas*/
    if (argc == CANT_MIN_ARG && (strcmp(argv[POS_ARGV1], CLA_AYUDA)) == 0)
        return ST_HELP;

    /*-----------------------------MEMORIA-----------------------------
     * ./simpletron -m 23...
     * Si no se ingresa este argumento, por defecto sera de 50 palabras*/
    for (i = 0; i < argc; i++) {
        /*Se busca el argumento "-m" en argv*/
        if (strcmp(argv[i], CLA_M) == 0) {
            *m = strtol(argv[i + 1], &p, 10);
            i = argc;
        } else {
            /*Si no se encuentra se asigna 50 por default*/
            *m = DEFAULT_M;
        }
    }

    /*-----------------------------ARCHIVO I-----------------------------
     * Se obtiene el archivo pasado por linea de comandos*/
    for (i = 0; i < argc; i++) {
        /*Se busca el argumento "-i" en argv*/
        if ((strcmp(argv[i], CLA_I)) == 0) {
            if ((strcmp(argv[i + 1], CLA_I_DEFAULT)) == 0) {
                tipo_archivo_i = ARCHIVO_DEFAULT;
            } else {
                /*Guardo el nombre del archivo*/
                memcpy(archivo_i, argv[i + 1], MAX_STR);
            }
            encontrado = TRUE;
            i = argc;
        }
    }
    /*Si no se encontro el argumento -i*/
    if (encontrado != TRUE)
        return ST_ERROR_ARCHIVO_I_NO_INGRESADO;
    encontrado = FALSE;


    /*-----------------------------IF-----------------------------
     * Se obtiene si el tipo de archivo de entrada sera interpretado como bin o txt*/
    for (i = 0; i < argc; i++) {
        /*Se busca el argumento "-if" en argv*/
        if (strcmp(argv[i], CLA_IF) == 0) {
            /*Se busca el tipo de archivo de entrada: txt, bin*/
            if ((strcmp(argv[i + 1], CLA_IF_BIN)) == 0) {
                tipo_archivo_i = ARCHIVO_BIN;
            } else if ((strcmp(argv[i + 1], CLA_IF_TXT)) == 0) {
                tipo_archivo_i = ARCHIVO_TXT;
            } else
                return ST_ERROR_IF_NO_VALIDO;
            encontrado = TRUE;
            i = argc;
        }
    }

    if (encontrado != TRUE)
        /*Si no se encuentra el argumento "-if"*/
        return ST_ERROR_IF_NO_INGRESADO;
    encontrado = FALSE;

    /*-----------------------------O-----------------------------
     * No es obligatorio ingresar esta opcion */
    for (i = 0; i < argc; i++) {
        /*Se busca el argumento "-o" en argv*/
        if ((strcmp(argv[i], CLA_O)) == 0) {
            /*Copio el nombre del archivo de salida*/
            memcpy(archivo_f, argv[i + 1], MAX_STR);
            encontrado = TRUE;
            i = argc;
        }
    }

    /*Si no se encontro el argumento o se tomara como default stdin*/
    if (encontrado != TRUE)
        tipo_archivo_f = ARCHIVO_DEFAULT;


    /*-----------------------------OF-----------------------------
     * Se obtiene si el tipo de archivo de salida sera interpretado como bin o txt*/
    if (encontrado == TRUE) { /*Si no se ingreso -o, no se debe ingresar -of*/
        for (i = 0; i < argc; i++) {
            /*Se busca el argumento "-of" en argv*/
            if (strcmp(argv[i], CLA_OF) == 0) {
                /*Se busca el tipo de archivo de entrada: txt, bin*/
                if ((strcmp(argv[i + 1], CLA_IF_BIN)) == 0) {
                    tipo_archivo_f = ARCHIVO_BIN;
                } else if ((strcmp(argv[i + 1], CLA_IF_TXT)) == 0) {
                    tipo_archivo_f = ARCHIVO_TXT;
                } else
                    return ST_ERROR_OF_NO_VALIDO;
                encontrado_of = TRUE;
                i = argc;
            }
        }
    }

    if (encontrado_of != TRUE)
        /*Si no se encuentra el argumento "-of"*/
        return ST_ERROR_OF_NO_INGRESADO;

    return ST_OK;
}

void imprimir_errores(status_t status) {
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
