/*MODIFICACIONES
 * Se agregan nuevas constantes
 * Se modifica CLA_AYUDA por CLA_H y CLA_HELP
 * Se modifica el proceso de validacion de cla para que admita argumentos en un orden especifico 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "validaciones.h"

typedef enum {
    ST_OK,
    ST_HELP,
    ST_ERROR_CANT_ARG,
    ST_ERROR_STDIN_INVALIDO,
    ST_ERROR_PTR_NULO,
    ST_ERROR_ARCHIVO_NO_ENCONTRADO,
    ST_ERROR_MEM,
    ST_ERROR_M_INVALIDO
} status_t;
typedef int palabra_t;

typedef enum {
    FMT_TXT,
    FMT_BIN
}formato_t;

typedef struct palabra{
    palabra_t dato;
    struct palabra * sig;
}palabra_s;

typedef enum{
    FALSE = 0,
    TRUE
}bool_t;

typedef struct archivo{
    char * nombre;
    formato_t formato;
    palabra_s memoria;
}archivo_s;

/*Para indicar que el archivo es stdin, se inicializa cant_archivos = 1, nombre = "stdin" y formato = FMT_TXT*/
typedef struct params{
    size_t cant_memoria;
    size_t cant_archivos;
    archivo_s archivo_salida;
    archivo_s * archivo_entrada;
}params_s;

/*Se trabajan con CLA de orden especifico, ningun argumento es obligatorio*/
/*El orden es el siguiente: ./run [-h] [-m N] [-f FMT] [-|[ARCHIVO1 [ARCHIVO2 ...]]]*/
status_t validacion_cla(int argc, char **argv, params_s *param);


int main(void){
    return EXIT_SUCCESS;
}

status_t validacion_cla(int argc, char **argv, params_s *param){
    size_t i, cant_archivos;
    bool_t stdin_flag = FALSE;
    long temp;
    char * pc;
    FILE *pf;
    void * pv;
    /*----------------------------VALIDACIONES-----------------------------
     */

    if(argv == NULL || param == NULL)
        return ST_ERROR_PTR_NULO;
    if(argc < CANT_MIN_ARG || argc > CANT_MAX_ARG)
        return ST_ERROR_CANT_ARG;
    
    /*-----------------------------DEFAULT-----------------------------
     */
    param->cant_memoria = 50;
    param->cant_archivos = 1;
    param->archivo_salida.formato = FMT_TXT;
    param->archivo_salida.nombre = "dump.txt";
    if( (param->archivo_entrada = (archivo_s*)malloc(sizeof(archivo_s))) == NULL )
        return ST_ERROR_MEM;
    param->archivo_entrada->formato = FMT_TXT;
    param->archivo_entrada->nombre = "stdin";
    
    
    i = 1;
    /*-----------------------------AYUDA-----------------------------
     * Forma de ejecutar: ./simpletron -h o --help */
    if(argc == 2 && (strcmp(argv[i], CLA_H) || strcmp(argv[i], CLA_HELP)))
        return ST_HELP;
    
    /*-----------------------------MEMORIA-----------------------------
     * Forma de ejecutar: ./simpletron -m 23...
     * Si no se ingresa este argumento, por defecto sera de 50 palabras*/
    
    if( strcmp(argv[i], CLA_M) == 0 || stcmp(argv[i], CLA_MEMORIA) == 0){
        temp = strtol(argv[i+1], &pc, 10);
        if (temp < 0)
            return ST_ERROR_M_INVALIDO;
        if (*pc != '\n' && *p != '\0')
            return ST_ERROR_M_INVALIDO;
        *m = temp;
        if (i += 2 >= argc) 
            return ST_OK;
    }
    if( strcmp(argv[i], CLA_F) == 0 || stcmp(argv[i], CLA_FORMATO) == 0){
        if( strcmp(argv[i+1], CLA_F_OPT_BIN) == 0){
            param->archivo_salida.formato = FMT_BIN;
            if (i += 2 >= argc) 
                return ST_OK;
        }
        else if ( strcmp(argv[i+1], CLA_F_OPT_TXT) == 0){
            param->archivo_salida.formato = FMT_TXT;
            if (i += 2 >= argc) 
                return ST_OK;
        }
        else
            return ST_ERROR_F_INVALIDO;
    }
    /*---------------------------------FORMATO---------------------------------*/
    
    for (cant_archivos = 0; i < argc; i++){
        if ((param->archivo_entrada = (archivo_s*) realloc(param->archivo_entrada, sizeof (archivo_s)*(++cant_archivos))) == NULL)
            return ST_ERROR_MEM;
        param->archivo_entrada[cant_archivos-1].nombre = get_name_lmsfile(argv[i]);
        param->archivo_entrada[cant_archivos-1].formato = get_fmt_lmsfile(argv[i]);
        if ((pf = fopen(param->archivo_entrada[cant_archivos-1].nombre, "r")) == NULL)
            return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
        fclose(pf);
        
        if(!stdin_flag && strcmp(param->archivo_entrada[cant_archivos-1].nombre,"stdin") == 0 && param->archivo_entrada[cant_archivos-1].formato == FMT_TXT)
            stdin_flag = TRUE;
    }
    
    if(stdin_flag && cant_archivos != 1)
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
