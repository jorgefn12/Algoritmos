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
#define CLA_IF_OPT_TXT "txt"
#define CLA_IF_OPT_BIN "bin"
#define CLA_O "-o"
#define CLA_OF "-of"

#define INICIO_COMENTARIO ";"

#define DEFAULT_M 50
#define MAX_STR 200
#define CANT_MAX_ARG 11
#define CANT_MIN_ARG 2
#define CANT_MAX_M 200

#define MSJ_AYUDA_M1 "OPCION |N|: Simpletron tiene una memoria de N palabras. Si no se da el argumento, por omisión tendrá 50 palabras. El maximo es de 200 palabras"
#define MSJ_AYUDA_I1 "OPCION |ARCHIVO|: El programa se leerá del archivo pasado como opción, en caso contrario, de stdin."
#define MSJ_AYUDA_IF1 "OPCION |BIN|: El archivo de entrada se entenderá como una secuencia binaria de enteros que representan las palabras que forman el programa."
#define MSJ_AYUDA_IF2 "OPCION |TXT|: El archivo de entrada se interpretará como secuencia de números, cada uno en una única línea."
#define MSJ_AYUDA_O1 "OPCION |ARCHIVO|: El dump se hará en el archivo pasado como opción, si no pasa el argumento, el volcado se hará por stdout."
#define MSJ_AYUDA_OF1 "OPCION |BIN|: El volcado se hará en binario guardando cada elemento de la estructura del Simpletron, además de la memoria."
#define MSJ_AYUDA_OF2 "OPCION |TXT|: El volcado se hará en formato de texto imprimiendo los registros y la memoria."

#define MSJ_MAS_AYUDA "Ingrese -h para mas ayuda"
#define MSJ_ERROR "Ocurrio un error"
#define MSJ_ERROR_M_NO_VALIDO "El valor de memoria asignado es invalido"
#define MSJ_ERROR_IF_NO_VALIDO "El ingreso de archivo de entrada es invalido"
#define MSJ_ERROR_ARCHIVO_I_NO_INGRESADO "No se ingreso el archivo de entrada"
#define MSJ_ERROR_IF_NO_INGRESADO "No se ingreso el tipo de archivo de entrada"
#define MSJ_ERROR_OF_NO_VALIDO "El ingreso de archivo de salida es invalido"
#define MSJ_ERROR_OF_NO_INGRESADO "No se ingreso el tipo de archivo de salida"
#define MSJ_ERROR_CANT_ARG "La cantidad de argumentos ingresados no es valido"
#define MSJ_ERROR_ARCHIVO_NO_ENCONTRADO "El archivo no existe u ocurrio un error al abrirlo"
#define MSJ_ERROR_PTR_NULO "Puntero nulo"
#define MSJ_ERROR_MEM "Error de memoria"

typedef enum {
    ST_OK,
    ST_HELP,
    ST_ERROR_CANT_ARG,
    ST_ERROR_M_INVALIDO,
    ST_ERROR_PTR_NULO,
    ST_ERROR_ARCHIVO_I_NO_INGRESADO,
    ST_ERROR_IF_NO_VALIDO,
    ST_ERROR_IF_NO_INGRESADO,
    ST_ERROR_OF_NO_VALIDO,
    ST_ERROR_OF_NO_INGRESADO,
    ST_ERROR_ARCHIVO_NO_ENCONTRADO,
    ST_ERROR_MEM
} status_t;

typedef enum {
    TRUE, FALSE
} bool_t;

typedef enum {
    ARCHIVO_BIN,
    ARCHIVO_TXT,
    ARCHIVO_DEFAULT
} archivo_t;

typedef struct {
    char ** memoria;
    /*opcode, operando*/
    long acumulador;
    int program_counter;
} palabras_s;

/*En esta función se validan los argumentos pasados por la terminal*/
status_t validacion_cla(int argc, char **argv, int *m, char *archivo_i, archivo_t *tipo_archivo_i, char *archivo_f, archivo_t *tipo_archivo_f);
/*En procesar_linea se obtiene cada linea del lms*/
status_t procesar_linea(char *linea, palabras_s *palabra, int *n);
void imprimir_errores(status_t status);
void imprimir_ayuda(void);
status_t leer_archivo(const char *nombre_archivo_entrada, const archivo_t tipo_archivo_entrada);

int main(int argc, char** argv) {
    status_t status;
    int memoria;
    char archivo_entrada[MAX_STR], archivo_salida[MAX_STR];
    archivo_t tipo_archivo_entrada, tipo_archivo_salida;

    if ((status = validacion_cla(argc, argv, &memoria, archivo_entrada, &tipo_archivo_entrada, archivo_salida, &tipo_archivo_salida)) != ST_OK) {
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

    status = leer_archivo(archivo_entrada, tipo_archivo_entrada);
    if (status != ST_OK)
        imprimir_errores(status);

    return EXIT_SUCCESS;
}

/*Esta funcion valida los argumentos pasados por la linea de comandos
 *El ingreso de argumentos en este caso no deben tener un orden especifico*/
status_t validacion_cla(int argc, char **argv, int *m, char *archivo_i, archivo_t *tipo_archivo_i, char *archivo_f, archivo_t *tipo_archivo_f) {
    size_t i;
    char * p;
    bool_t encontrado = FALSE, encontrado_of = FALSE;

    if (argc > CANT_MAX_ARG || argc < CANT_MIN_ARG)
        return ST_ERROR_CANT_ARG;

    if (argv == NULL || m == NULL || archivo_i == NULL || tipo_archivo_i == NULL || archivo_f == NULL || tipo_archivo_f == NULL)
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
            /* Se comprueba que sea un entero positivo menor al maximo*/
            if (*m > CANT_MAX_M || *m < 0) {
                return ST_ERROR_M_INVALIDO;
            } 
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
                *tipo_archivo_i = ARCHIVO_DEFAULT;
                /*archivo_i = STR_STDIN;*/
            } else {
                /*Guardo el nombre del archivo*/
                memcpy(archivo_i, argv[i + 1], strlen(argv[i + 1]) + 1);
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
            if ((strcmp(argv[i + 1], CLA_IF_OPT_BIN)) == 0) {
                *tipo_archivo_i = ARCHIVO_BIN;
            } else if ((strcmp(argv[i + 1], CLA_IF_OPT_TXT)) == 0) {
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

    /*Si no se encontro el argumento o se tomara como default stdin*/
    if (encontrado != TRUE) {
        *tipo_archivo_f = ARCHIVO_DEFAULT;
        /*archivo_f = STR_STDOUT;*/
    }

    /*-----------------------------OF-----------------------------
     * Se obtiene si el tipo de archivo de salida sera interpretado como bin o txt*/
    /*Si se ingreso -o, se debe ingresar -of*
     *si no se ingreso -o, se puede ingresar -of*/
    for (i = 0; i < argc; i++) {
        /*Se busca el argumento "-of" en argv*/
        if (strcmp(argv[i], CLA_OF) == 0) {
            /*Se busca el tipo de archivo de entrada: txt, bin*/
            if ((strcmp(argv[i + 1], CLA_IF_OPT_BIN)) == 0) {
                *tipo_archivo_f = ARCHIVO_BIN;
            } else if ((strcmp(argv[i + 1], CLA_IF_OPT_TXT)) == 0) {
                *tipo_archivo_f = ARCHIVO_TXT;
            } else
                return ST_ERROR_OF_NO_VALIDO;
            encontrado_of = TRUE;
            break;
        }
    }
    if (encontrado != TRUE && encontrado_of != TRUE)
        *tipo_archivo_f = ARCHIVO_TXT; /*por defecto se interpreta como txt, 
                                        sólamente si no se ingreso -o"*/

    else if (encontrado == TRUE && encontrado_of != TRUE)
        /*Si no se encuentra el argumento "-of" y sí se ingresa "-o"*/
        return ST_ERROR_OF_NO_INGRESADO;

    return ST_OK;
}

void imprimir_errores(status_t status) {
    switch (status) {
        case ST_HELP:
            imprimir_ayuda();
            break;
        case ST_ERROR_CANT_ARG:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_CANT_ARG, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_M_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_M_NO_VALIDO, MSJ_MAS_AYUDA);
            break;    
        case ST_ERROR_ARCHIVO_I_NO_INGRESADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_ARCHIVO_I_NO_INGRESADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_IF_NO_VALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_IF_NO_VALIDO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_IF_NO_INGRESADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_IF_NO_INGRESADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_OF_NO_VALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_OF_NO_VALIDO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_OF_NO_INGRESADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_OF_NO_INGRESADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_ARCHIVO_NO_ENCONTRADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_ARCHIVO_NO_ENCONTRADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_PTR_NULO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_PTR_NULO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_MEM:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_MEM, MSJ_MAS_AYUDA);
        default:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR, MSJ_MAS_AYUDA);
    }
}

void imprimir_ayuda(){
    fprintf(stderr, "%s    %s\n\n", CLA_M, MSJ_AYUDA_M1);
    fprintf(stderr, "%s    %s\n\n", CLA_I, MSJ_AYUDA_I1);
    fprintf(stderr, "%s   %s\n", CLA_IF, MSJ_AYUDA_IF1);
    fprintf(stderr, "      %s\n\n", MSJ_AYUDA_IF2);
    fprintf(stderr, "%s    %s\n\n", CLA_O, MSJ_AYUDA_O1);
    fprintf(stderr, "%s   %s\n", CLA_OF, MSJ_AYUDA_OF1);
    fprintf(stderr, "      %s\n\n", MSJ_AYUDA_OF2);
}

status_t leer_archivo(const char *nombre_archivo_entrada, const archivo_t tipo_archivo_entrada) {
    FILE *archivo_entrada;
    char *linea;
    status_t status;
    palabras_s palabra;
    size_t i;

    switch (tipo_archivo_entrada) {
        case ARCHIVO_BIN:
            if ((archivo_entrada = fopen(nombre_archivo_entrada, "rb")) == NULL)
                return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
            break;
        case ARCHIVO_TXT:
            if ((archivo_entrada = fopen(nombre_archivo_entrada, "r")) == NULL)
                return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
            break;
        case ARCHIVO_DEFAULT:
            /*DISCUTIR; como manejar la entrada de datos*/
            break;
        default:
            return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
    }

    linea = (char*) malloc(sizeof (char)*MAX_STR);
    if (linea == NULL)
        return ST_ERROR_PTR_NULO;

    palabra.program_counter = 0;
    if((palabra.memoria = (char**)malloc(sizeof(char*)))==NULL)
        return ST_ERROR_MEM;
    
    while (!feof(archivo_entrada) && status == ST_OK) {
        if ((fgets(linea, MAX_STR, archivo_entrada)) != NULL) {
            status = procesar_linea(linea, &palabra, &palabra.program_counter);
        }
    }


    printf("program_counter:%d\n", palabra.program_counter);
        for (i = 0; i < palabra.program_counter; i++)
            printf("%s\n", palabra.memoria[i]);

    return ST_OK;
}

status_t procesar_linea(char *linea, palabras_s* palabra, int *n) {
    char * pch;

    pch = strtok(linea, INICIO_COMENTARIO);

    if ((palabra->memoria = (char**) realloc(palabra->memoria,sizeof (char*)*(*n + 1))) == NULL)
        return ST_ERROR_MEM;
    if ((palabra->memoria[*n] = (char*) malloc(sizeof (char)*MAX_STR)) == NULL)
        return ST_ERROR_MEM;
    memcpy(palabra->memoria[*n], linea, strlen(linea) + 1);
    *n += 1; /*Poner uno en define?*/

    
    return ST_OK;
}
