#ifndef ERRORES__H
#define ERRORES__H

#define MSJ_OPCION_AYUDA "Ingrese: .\\simpletron -h o .\\simpletron --help para mas informacion."
#define MSJ_ST_OK "La operación finalizó correctamente"
#define MSJ_ST_AYUDA "Leer documentación. Escribir función para mensaje de ayuda"
#define MSJ_ST_ERROR_PTR_NULO "Puntero nulo"
#define MSJ_ST_ERROR_MEMORIA "Ocurrio un error al pedir memoria"
#define MSJ_ST_ERROR_ARCHIVO_NO_ENCONTRADO "El archivo ingresado no se encuentra"
/*Validacion de argumentos*/
#define MSJ_ST_ERROR_MEMORIA_INGRESADA_INVALIDA "La memoria ingresada no es valida, la misma debe ser un entero positivo"
#define MSJ_ST_ERROR_FORMATO_ARCHIVO_INVALIDO "El formato de archivo de salida no es valido"
#define MSJ_ST_ERROR_STDIN_INVALIDO "stdin no valido"
void imprimir_estado(status_t status);
void imprimir_ayuda(void);

#endif
