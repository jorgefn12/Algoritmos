#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "validaciones.h"

int main(int argc, char** argv) {
    status_t status;
    long memoria_pedida;
    
    status = validacion_cla(argc,argv,&memoria_pedida);
    return (EXIT_SUCCESS);
}
