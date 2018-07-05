#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "validaciones.h"

int main(int argc, char** argv) {
    params_s argumentos;
    status_t status;
    size_t i;
    
    /*Código para chequear que los nombres y formatos se guardan bien. [0] = FMT_TXT; [1] = FMT_BIN
    status = validacion_cla(argc, argv, &argumentos);
    for(i=0;i<argumentos.cant_archivos;i++){
        printf("Archivo entrada %lu: %s [%d]\n", i+1, argumentos.archivo_entrada[i].nombre, argumentos.archivo_entrada[i].formato);
    }
    printf("Archivo salida: %s [%d]\n",argumentos.archivo_salida.nombre, argumentos.archivo_salida.formato);
    printf("Cantidad memoria: %ld\n", argumentos.cant_memoria);
    printf("Cantidad archivos: %ld\n", argumentos.cant_archivos);
    */
    if(status!=ST_OK)
        imprimir_mensaje_de_error(status);
    
    return (EXIT_SUCCESS);
}
