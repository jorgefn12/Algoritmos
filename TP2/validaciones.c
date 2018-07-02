/*MODIFICACIONES
*Varias correcciones, la función debería estar funcionando correctamente
*Se eliminan validaciones de CANT_ARG_MIN, porque el mínimo es 1 (./simpletron)
*/


/*
La función recorre argv y va validando los argumentos por orden este orden de precedencia m->f->archivos
-h necesita estar como unico argumento, sino devuelve error.
Ninguno es obligatorio, todos tienen valores por default
Si se invoca un flag (-m, -f), el siguiente argumento se toma como su opcion asignada

Si no encuentra un argumento, inmediatamente chequea por el siguiente hasta alcanzar el final de argv, si encuentra una
incoherencia en el orden, retorna error o no se comporta segun lo esperado
./simpletron -f bin -m 20, detecta -f y espera encontrar archivos. Busca -m y 20 como archivos.
./simpletron dadd -f txt, busca dadd, -f y txt como archivos
./simpletron -m 20 b:hola , cumple el orden de precedencia. Almacena cant_mem = 20 y busca b:hola como archivo binario
./simpletron -f bin -   cumple el orden. OK
./simpletron b:stdin     ,intenta tomar como archivo de entrada a stdin en formato binario, por ahora lo tomé como error.
./simpletron t:stdin ó ./simpletron -           toman a stdin como archivo de entrada en formato de texto
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comun.h"
#include "validaciones.h"

status_t validacion_cla(int argc, char** argv, params_s *param) {
    size_t i = 0, j, cant_archivos;
    bool_t stdin_flag = FALSE;
    long temp;
    char * pc;
    FILE *pf;
    /*---------------------------------VALIDACIONES---------------------------------*/
    /*Valido que los nombres no apunten a NULL para usar funciones get()*/
    if (argv == NULL || param == NULL)
        return ST_ERROR_PTR_NULO;
    for(j = 1; j < argc; j++){
        if( argv[j] == NULL)
            return ST_ERROR_PTR_NULO;
    }
    /*Caso hipotetico: ./simpletron h ----> En este caso se debería tomar h como un archivo de entrada?
    *                                       porque esta validacion estaría considerando ./simpletron t:archivo como error
    *
    *if (argc == CANT_MIN_ARG + 1 && ((strcmp(argv[POS_ARGV1], FLAG_CLA_AYUDA_CORTO)) != 0 || (strcmp(argv[POS_ARGV1], FLAG_CLA_AYUDA_LARGO)) != 0))
    *    return ST_ERROR_FLAG_NO_RECONOCIDO;
    */

    /*-----------------------------DEFAULT-----------------------------*/
    param->cant_memoria = DEFAULT_MEMORIA;
    param->cant_archivos = DEFAULT_CANT_ARCHIVOS;
    param->archivo_salida.formato = FMT_TXT;
    param->archivo_salida.nombre = DEFAULT_ARCHIVO_SALIDA;
    if ((param->archivo_entrada = (archivo_s*) malloc(sizeof (archivo_s))) == NULL)
        return ST_ERROR_MEMORIA;
    param->archivo_entrada->formato = FMT_TXT;
    param->archivo_entrada->nombre = DEFAULT_ARCHIVO_ENTRADA;

    /*Comienzo a recorrer argv[] hasta llegar a argv[argc]*/
    if(++i >= argc)
        return ST_OK;
    /*---------------------------------AYUDA---------------------------------*/
    /*Forma de ejecutar: ./simpletron -h o --help */
    if (argc == 2 && (strcmp(argv[i], FLAG_CLA_AYUDA_CORTO) == 0 || strcmp(argv[i], FLAG_CLA_AYUDA_LARGO) == 0))
        return ST_HELP;
    
    /*---------------------------------MEMORIA---------------------------------*/
    if (strcmp(argv[i], FLAG_CLA_MEMORIA_CORTO) == 0 || strcmp(argv[i], FLAG_CLA_MEMORIA_LARGO) == 0) {
        if(++i >= argc)
            return ST_ERROR_MEMORIA_INGRESADA_INVALIDA;
        
        temp = strtol(argv[i], &pc, 10);
        /*En el caso de que el usuario ingrese caracter alfabetico o pida memoria con decimales*/
        if (temp <= 0 || pc == NULL || (*pc != '\n' && *pc != '\0'))
            return ST_ERROR_MEMORIA_INGRESADA_INVALIDA;
        param->cant_memoria = temp;
        
        if(++i >= argc)
            return ST_OK;
    }

    /*---------------------------------FORMATO SALIDA---------------------------------*/
    /*Hacemos un bool_t o un typedef con los tipos de archivos*/
    /*Indica el formato de la salida. Si FMT es txt , el formato debe ser texto. Si*/
    /*FMT es bin, el formato debe ser binario. Por omisión, el formato es texto.*/
    /*Busco el flag de formato*/
    if (strcmp(argv[i], FLAG_CLA_FORMATO_CORTO) == 0 || strcmp(argv[i], FLAG_CLA_FORMATO_LARGO) == 0) {
        if(++i >= argc)
            ST_ERROR_FORMATO_ARCHIVO_INVALIDO;
            
        if (strcmp(argv[i], FLAG_CLA_FORMATO_OPCION_BIN) == 0) {
            param->archivo_salida.formato = FMT_BIN;
        } else if (strcmp(argv[i], FLAG_CLA_FORMATO_OPCION_TXT) == 0) {
            param->archivo_salida.formato = FMT_TXT;
        } else
            return ST_ERROR_FORMATO_ARCHIVO_INVALIDO;
        
        if(++i >= argc)
            return ST_OK;
    }

    /*---------------------------------ARCHIVOS---------------------------------*/
    for (cant_archivos = 0; i < argc; i++) {
        if ((param->archivo_entrada = (archivo_s*) realloc(param->archivo_entrada, sizeof (archivo_s)*(++cant_archivos))) == NULL)
            return ST_ERROR_MEMORIA;
        param->archivo_entrada[cant_archivos - 1].nombre = get_name_lmsfile(argv[i]);
        param->archivo_entrada[cant_archivos - 1].formato = get_fmt_lmsfile(argv[i]);
        
        if(!stdin_flag && strcmp(param->archivo_entrada[cant_archivos-1].nombre, FLAG_CLA_STDIN_LARGO) == 0 && param->archivo_entrada[cant_archivos-1].formato == FMT_TXT)
            stdin_flag = TRUE;
        
        if(!stdin_flag && (pf = fopen(param->archivo_entrada[cant_archivos-1].nombre, "r")) == NULL)
            return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
        fclose(pf);
    }

    if (stdin_flag && (cant_archivos != 1 || param->archivo_entrada->formato == FMT_BIN))
        return ST_ERROR_STDIN_INVALIDO;
    param->cant_archivos = cant_archivos;
    
    return ST_OK;
}

char * get_name_lmsfile(char* name){
    if(!strncmp(name,"b:",2) || !strncmp(name,"t:",2))
        return name + 2;
    return name;

formato_t get_fmt_lmsfile(char* name){
    return strncmp(name,"b:",2) ? FMT_TXT : FMT_BIN;
}
