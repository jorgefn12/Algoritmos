#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comun.h"
#include "validaciones.h"

status_t validacion_cla(int argc, char** argv, params_s *param) {
    size_t i, cant_archivos;
    bool_t stdin_flag = FALSE;
    long temp;
    char * pc;
    FILE *pf;
    void * pv;

    /*---------------------------------VALIDACIONES---------------------------------*/
    if (argv == NULL || param == NULL)
        return ST_ERROR_PTR_NULO;

    /*Se verifica que la cantidad de argumentos ingresados sean correctas*/
    if (argc < CANT_MIN_ARG)
        return ST_ERROR_CANT_ARG;

    /*Caso hipotetico: ./simpletron h */
    if (argc == CANT_MIN_ARG && ((strcmp(argv[POS_ARGV1], FLAG_CLA_AYUDA_CORTO)) != 0 || (strcmp(argv[POS_ARGV1], FLAG_CLA_AYUDA_LARGO)) != 0))
        return ST_ERROR_FLAG_NO_RECONOCIDO;


    /*-----------------------------DEFAULT-----------------------------*/
    param->cant_memoria = DEFAULT_MEMORIA;
    param->cant_archivos = DEFAULT_CANT_ARCHIVOS;
    param->archivo_salida.formato = FMT_TXT;
    param->archivo_salida.nombre = DEFAULT_ARCHIVO_SALIDA;
    if ((param->archivo_entrada = (archivo_s*) malloc(sizeof (archivo_s))) == NULL)
        return ST_ERROR_MEMORIA;
    param->archivo_entrada->formato = FMT_TXT;
    param->archivo_entrada->nombre = DEFAULT_ARCHIVO_ENTRADA;


    /*---------------------------------AYUDA---------------------------------*/
    /*Forma de ejecutar: ./simpletron -h o --help */
    if (argc == 2 && (strcmp(argv[i], FLAG_CLA_AYUDA_CORTO) || strcmp(argv[i], FLAG_CLA_AYUDA_LARGO)))
        return ST_HELP;


    /*---------------------------------MEMORIA---------------------------------*/
    if (strcmp(argv[i], FLAG_CLA_MEMORIA_CORTO) == 0 || strcmp(argv[i], FLAG_CLA_MEMORIA_LARGO) == 0) {
        temp = strtol(argv[i + 1], &pc, 10);
        /*En el caso de que el usuario ingrese caracter alfabetico o pida memoria con decimales*/
        if (temp <= 0 || pc != NULL)
            return ST_ERROR_MEMORIA_INGRESADA_INVALIDA;
        if (*pc != '\n' && *pc != '\0')
            return ST_ERROR_MEMORIA_INGRESADA_INVALIDA;
        param->cant_memoria = temp;
        if (i += 2 >= argc)
            return ST_OK;
    }

    /*---------------------------------FORMATO SALIDA---------------------------------*/
    /*Hacemos un bool_t o un typedef con los tipos de archivos*/
    /*Indica el formato de la salida. Si FMT es txt , el formato debe ser texto. Si
❋▼❚ FMT es bin, el formato debe ser binario. Por omisión, el formato es texto.*/
    /*Busco el flag de formato*/
    if (strcmp(argv[i], FLAG_CLA_FORMATO_CORTO) == 0 || strcmp(argv[i], FLAG_CLA_MEMORIA_LARGO) == 0) {
        if (strcmp(argv[i + 1], FLAG_CLA_FORMATO_OPCION_BIN) == 0) {
            param->archivo_salida.formato = FMT_BIN;
            if (i += 2 >= argc)
                return ST_OK;
        } else if (strcmp(argv[i + 1], FLAG_CLA_FORMATO_OPCION_TXT) == 0) {
            param->archivo_salida.formato = FMT_TXT;
            if (i += 2 >= argc)
                return ST_OK;
        } else
            return ST_ERROR_FORMATO_ARCHIVO_INVALIDO;
    }



    /*---------------------------------ARCHIVOS---------------------------------*/
    for (cant_archivos = 0; i < argc; i++) {
        if ((param->archivo_entrada = (archivo_s*) realloc(param->archivo_entrada, sizeof (archivo_s)*(++cant_archivos))) == NULL)
            return ST_ERROR_MEMORIA;
        param->archivo_entrada[cant_archivos - 1].nombre = get_name_lmsfile(argv[i]);
        param->archivo_entrada[cant_archivos - 1].formato = get_fmt_lmsfile(argv[i]);
        if ((pf = fopen(param->archivo_entrada[cant_archivos - 1].nombre, "r")) == NULL)
            return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
        fclose(pf);

        if (!stdin_flag && strcmp(param->archivo_entrada[cant_archivos - 1].nombre, "stdin") == 0 && param->archivo_entrada[cant_archivos - 1].formato == FMT_TXT)
            stdin_flag = TRUE;
    }

    if (stdin_flag && cant_archivos != 1)
        return ST_ERROR_STDIN_INVALIDO;
    param->cant_archivos = cant_archivos;


    return ST_OK;
}

char * get_name_lmsfile(char* name){
    if(strcmp(name, CLA_STDIN) == 0)
        return "stdin";
    if(strncmp(name,"b:",2) == 0 || strncmp(name,"t:",2) == 0)
        return name + 2;
    return name;
}

formato_t get_fmt_lmsfile(char* name){
    return (!strncmp(name,"b:",2)) ? FMT_BIN : FMT_TXT;
}