#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_header.h"
#include "validaciones.h"


int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}


status_t validacion_cla(int argc, char** argv){
    /*Se verifica que la cantidad de argumentos ingresados sean correctas*/
    if (argc < CANT_MIN_ARG)
        return ST_ERROR_CANT_ARG;
    
    /*---------------------------------AYUDA---------------------------------*/
    /*Ejecucion: ./simpletron -h
     *           ./simpletron --help
     */
    if (argc == CANT_MIN_ARG && ((strcmp(argv[POS_ARGV1], FLAG_CLA_AYUDA_CORTO)) == 0 || (strcmp(argv[POS_ARGV1],FLAG_CLA_AYUDA_LARGO))==0))
        return ST_HELP;
    
    
    /*---------------------------------MEMORIA---------------------------------*/
    
    
    
    /*---------------------------------FORMATO---------------------------------*/
    
    
    /*---------------------------------ARCHIVOS---------------------------------*/
    
    return ST_OK;
}
