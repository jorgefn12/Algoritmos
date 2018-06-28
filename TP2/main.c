#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "validaciones.h"

int main(int argc, char** argv) {
    status_t status;
    long memoria_pedida;
    
    
    status = validacion_cla(argc,argv,&memoria_pedida);
    if(status!=ST_OK)
        imprimir_mensaje_de_error(status);
    
    return (EXIT_SUCCESS);
}
