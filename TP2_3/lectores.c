
#include "lectores.h"
#include "tipos.h"
#include "argumentos.h"
#include "vectores.h"
#include "comun.h"
#include "simpletron.h"
#include <string.h>
/*****************************LECTORES.C********************************************************/
/*Trabajo con un archivo ya abierto.
 *Utiliza su formato y su FILE * stream ya abierto.
 *Lo lee, y guarda las palabras en la memoria pasada como argumento. */
status_t abrir_archivos(params_t * param){
    size_t i,j;
    
    if(param == NULL)
        return ST_ERROR_PTR_NULO;
    switch(param->archivo_salida->formato){
        case FMT_TXT:
            if((param->archivo_salida->stream = fopen(param->archivo_salida->nombre,"at")) == NULL)
                return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
            break;
        case FMT_BIN:
            if((param->archivo_salida->stream = fopen(param->archivo_salida->nombre,"ab")) == NULL)
                return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
            break;
    }
    if(param->archivo_entrada->nombre == NULL){
        param->archivo_entrada->stream = stdin;
        return ST_OK;
    }
    for(i = 0; i < param->cant_archivos; i++){
        switch(param->archivo_entrada[i].formato){
            case FMT_TXT:
                if((param->archivo_entrada[i].stream = fopen(param->archivo_entrada[i].nombre,"rt")) == NULL){
                	for(j = 0; j < i; j++){
                		fclose(param->archivo_entrada[j].stream);
                	}
                	fclose(param->archivo_salida->stream);

                    return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
                }
                break;
            case FMT_BIN:
                if((param->archivo_entrada[i].stream = fopen(param->archivo_entrada[i].nombre,"rb")) == NULL){
                	for(j = 0; j < i; j++){
                		fclose(param->archivo_entrada[j].stream);
                	}
                	fclose(param->archivo_salida->stream);

                    return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
                }
                break;
        }
    }
    return ST_OK;
}

void cerrar_archivos(params_t * param){
    size_t i;
    
    fclose(param->archivo_salida->stream);
    if(param->archivo_entrada->nombre == NULL)
        return;
    for(i = 0; i < param->cant_archivos; i++)
        fclose(param->archivo_entrada[i].stream);
}

status_t leer_archivo(vector_t ** memoria, archivo_t * archivo, size_t cantidad){
    if(memoria == NULL || archivo == NULL)
        return ST_ERROR_PTR_NULO;
    switch(archivo->formato){
        case FMT_TXT:
            if(archivo->nombre == NULL)
                return leer_archivo_stdin(memoria,cantidad);
            return leer_archivo_txt(memoria,archivo->stream,cantidad);
        case FMT_BIN:
            return leer_archivo_bin(memoria,archivo->stream,cantidad);
        default:
            return ST_ERROR_FORMATO_ARCHIVO_INVALIDO;
    }
}
/*Tratar de usar crecimiento proporcional para los arreglos de TDA vector*/
status_t leer_archivo_txt(vector_t ** memoria, FILE * stream, size_t cantidad){
    char buffer[MAX_STR], *pch;
    palabra_t palabra;
    size_t i;
    
    if(VECTOR_crear(memoria,1) != VCT_RV_SUCCESS)
        return ST_ERROR_VECTOR;
    for(i = 0; fgets(buffer, MAX_STR, stream) != NULL && i < cantidad; i++){
        pch = strtok(buffer, DELIMITADOR_COMENTARIO);
        palabra = strtol(buffer, &pch, 10);
        /*Se valida que el numero pueda ser representado en 16bits y que los opcodes y operandos sean adecuados*/
        if (pch == NULL || (*pch != '\n' && *pch != '\0') || !palabra_es_valida(palabra))
            return ST_ERROR_PALABRA_NO_VALIDA;
        palabra = cambiar_fmt_palabra(palabra,FMT_TXT);
        
        if(VECTOR_redimensionar(*memoria, i + 1) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
        if(VECTOR_guardar_entero(*memoria, i + 1, palabra) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
    }
    
    if(ferror(stream))
        return ST_ERROR_LEER_PALABRA;
    if(i == cantidad)
        return ST_ERROR_MEMORIA_INSUFICIENTE;
    return ST_OK;
}
/*Esta función asume que el sistema en el que se usa el programa, representa números signados usando
 la convención de complemento a 2 */
status_t leer_archivo_bin(vector_t ** memoria, FILE * stream, size_t cantidad){
    uchar high_byte, low_byte;
    palabra_t palabra;
    size_t i;
    
    if(VECTOR_crear(memoria,1) != VCT_RV_SUCCESS)
        return ST_ERROR_VECTOR;
    for(i = 0; fread(&high_byte, BYTE_SIZE, BYTE_CANT_HIGHT_LOW,stream) == 1 && i < cantidad; i++){
        if((fread(&low_byte,BYTE_SIZE, BYTE_CANT_HIGHT_LOW,stream) != 1))
            return ST_ERROR_LEER_PALABRA;
        palabra = 0;
        /*Palabra en binario, con ceros rellenados a la izquierda*/
        palabra = ((palabra | high_byte) << BYTE_SHIFT) | low_byte;
        
        if(VECTOR_redimensionar(*memoria, i + 1) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
        if(VECTOR_guardar_entero(*memoria, i + 1, palabra) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
    }
    if(ferror(stream))
        return ST_ERROR_LEER_PALABRA;
    
    return ST_OK;
}
status_t leer_archivo_stdin(vector_t ** memoria, size_t cantidad){
    char buffer[MAX_STR], *pch;
    palabra_t palabra;
    size_t i;
    
    fprintf(stdout, "%s\n", MSJ_BIENVENIDO_SIMPLETRON);
    
    if(VECTOR_crear(memoria,1) != VCT_RV_SUCCESS)
        return ST_ERROR_VECTOR;
    for(i = 0; i < cantidad; i++){
        fprintf(stdout, "%02lu ? ", i);
        
        if(fgets(buffer, MAX_STR, stdin) == NULL)
            return ST_ERROR_LEER_PALABRA;
        
        palabra = strtol(buffer, &pch, 10);
        
        if(palabra == NUMERO_FIN_CARGA)
            break;
        /*Se valida que el numero pueda ser representado en 16bits y que los opcodes y operandos sean adecuados*/
        if (pch == NULL || (*pch != '\n' && *pch != '\0') || !palabra_es_valida(palabra))
            return ST_ERROR_PALABRA_NO_VALIDA;
        
        palabra = cambiar_fmt_palabra(palabra,FMT_TXT);
        
        if(VECTOR_redimensionar(*memoria, i + 1) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
        if(VECTOR_guardar_entero(*memoria, i + 1, palabra) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
    }
    if(i == cantidad)
        return ST_ERROR_MEMORIA_INSUFICIENTE;
    
    return ST_OK;
}
