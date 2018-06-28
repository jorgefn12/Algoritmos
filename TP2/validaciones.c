#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comun.h"
#include "validaciones.h"

status_t validacion_cla(int argc, char** argv, long *memoria_pedida) {
    size_t i;
    char *p;
    long temp;

    /*Se verifica que la cantidad de argumentos ingresados sean correctas*/
    if (argc < CANT_MIN_ARG)
        return ST_ERROR_CANT_ARG;
    
    /*Caso hipotetico: ./simpletron h */
    if(argc==CANT_MIN_ARG && ((strcmp(argv[POS_ARGV1],FLAG_CLA_AYUDA_CORTO))!=0 || (strcmp(argv[POS_ARGV1],FLAG_CLA_AYUDA_LARGO))!=0))
        return ST_ERROR_FLAG_NO_RECONOCIDO;

    
    /*---------------------------------AYUDA---------------------------------*/
    /*Ejecucion: ./simpletron -h
     *           ./simpletron --help
     */
    if (argc == CANT_MIN_ARG && ((strcmp(argv[POS_ARGV1], FLAG_CLA_AYUDA_CORTO)) == 0 || (strcmp(argv[POS_ARGV1], FLAG_CLA_AYUDA_LARGO)) == 0))
        return ST_HELP;

    
    /*---------------------------------MEMORIA---------------------------------*/
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-m" y "--memoria" en argv*/
        if (strcmp(argv[i], FLAG_CLA_MEMORIA_CORTO) == 0 || strcmp(argv[i], FLAG_CLA_MEMORIA_LARGO) == 0) {
            temp = strtol(argv[i + 1], &p, 10);
            
            /*En el caso de que el usuario ingrese caracter alfabetico o pida memoria con decimales*/
            if (temp <= 0 || p!=NULL)
                return ST_ERROR_MEMORIA_INGRESADA_INVALIDA;
            
            *memoria_pedida = temp;
            break;
        } else {
            /*Si no se encuentra se asigna 50 por default*/
            *memoria_pedida = DEFAULT_MEMORIA;
        }
    }


    /*---------------------------------FORMATO---------------------------------*/
    /*Hacemos un bool_t o un typedef con los tipos de archivos*/
    

    /*---------------------------------ARCHIVOS---------------------------------*/
    /*Crear funcion que valide que el archivo existe, antes de guardarlo en la lista*/
    /*Crear una funcion que obtenga el formato*/
    
    return ST_OK;
}
