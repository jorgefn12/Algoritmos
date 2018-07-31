#ifndef ERRORES_H
#define ERRORES_H

#include "tipos.h"
#include "argumentos.h"
#include "simpletron.h"

#define MSJ_AYUDA_PROTOTIPO "Prototipo de ejecucion: .\\simpletron -m N -f FMT [Archivo1 Archivo2 Archivo3...]"
#define MSJ_AYUDA_MEMORIA "MEMORIA:\n -m N:\t -m es el flag indicador de memoria y N debe ser un numero entero. No es obligatorio su ingreso. En caso de no ingresarse N sera 50"
#define MSJ_AYUDA_FORMATO "FORMATO:\n-f FMT:\t -f es el flag indicador del formato de salida donde FMT debe ser TXT o BIN. No es obligatorio su ingreso. Por default sera TXT"
#define MSJ_AYUDA_ARCHIVOS "ARCHIVOS:\n Los nombres de archivo de entrada deberan estar antecedidos por 't:' o 'b:' si el archivo debera leerse como un archivo de texto o un archivo binario respectivamente. En caso de omiterse esta especificacion, el archivo sera leido como un archivo de texto. En caso de que no se ingresen nombres de archivos, la entrada de datos sera por stdin"
#define MSJ_OPCION_AYUDA "Ingrese: .\\simpletron -h o .\\simpletron --help para mas informacion."
#define MSJ_ST_OK "La operación finalizó correctamente"
#define MSJ_ST_ERROR_PTR_NULO "Puntero nulo"
#define MSJ_ST_ERROR_MEMORIA "Ocurrio un error al pedir memoria"
#define MSJ_ST_ERROR_ARCHIVO_NO_ENCONTRADO "El archivo ingresado no se encuentra"
/*Validacion de argumentos*/
#define MSJ_ST_ERROR_MEMORIA_INGRESADA_INVALIDA "La memoria ingresada no es valida, la misma debe ser un entero positivo"
#define MSJ_ST_ERROR_FORMATO_ARCHIVO_INVALIDO "El formato de archivo de salida no es valido"
#define MSJ_ST_ERROR_STDIN_INVALIDO "stdin no valido"
/*carga*/
#define MSJ_ST_ERROR_LEER_PALABRA "Ocurrio un error al leer palabra del archivo"
#define MSJ_ST_ERROR_PALABRA_NO_VALIDA "La palabra ingresada no es valida"
#define MSJ_ST_ERROR_GUARDAR_LISTA "Ocurrió un error al procesar los datos"
#define MSJ_ST_MEMORIA_INSUFICIENTE "Se superó la memoria solicitada para el simpletron"
/*ejecucion*/
#define MSJ_ST_ERROR_SEGMENTATION_FAULT "Se intentó acceder a un área restringida de memoria"
#define MSJ_ST_ERROR_OPCODE_INVALIDO "Se trató de ejecutar una instrucción no especificada en el lenguaje"
#define MSJ_ST_ERROR_OVERFLOW "Se trató de operar con un rango de números no soportados por la máquina"
#define MSJ_ST_HALT "Finalizó la ejecución del archivo"
void imprimir_estado(status_t status);
void imprimir_ayuda(void);
void destructor(params_t * param, simpletron_t ** simpletron);

#endif
