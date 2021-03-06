#include "lectores.h"
#include "tipos.h"
#include "argumentos.h"
#include "listas.h"
#include "comun.h"
#include <string.h>

/*La función recibe un puntero a estructura de params_t*/
/*Abre todos los archivos que se encuentran en dicha estrucutura, los guarda en un stream y devuelve por
el nombre la cantidad de archivos abiertos. Retorna EOF si hubo un error*/
int abrir_archivos(params_t * param){
    size_t archivos_abiertos = 0;
    size_t i;
    
    if(param == NULL)
        return EOF;
    switch(param->archivo_salida->formato){
        case FMT_TXT:
            if((param->archivo_salida->stream = fopen(param->archivo_salida->nombre,"at")) != NULL)
                archivos_abiertos++;
            break;
        case FMT_BIN:
            if((param->archivo_salida->stream = fopen(param->archivo_salida->nombre,"ab")) != NULL)
                archivos_abiertos++;
            break;
    }
    if(param->archivo_entrada->nombre == NULL){
        param->archivo_entrada->stream = stdin;
        return ++archivos_abiertos;
    }
    for(i = 0; i < param->cant_archivos; i++){
        switch(param->archivo_entrada[i].formato){
            case FMT_TXT:
                if((param->archivo_entrada[i].stream = fopen(param->archivo_entrada[i].nombre,"rt")) != NULL)
                    archivos_abiertos++;
                break;
            case FMT_BIN:
                if((param->archivo_entrada[i].stream = fopen(param->archivo_entrada[i].nombre,"rb")) != NULL)
                    archivos_abiertos++;
                break;
        }
    }

    return archivos_abiertos;
}

/*Recibe un puntero a params_t, detecta los streams abiertos y los cierra*/
/*Devuelve por el nombre la cantidad de archivos cerrados, EOF si hubo un error*/
int cerrar_archivos(params_t * param){
    size_t archivos_cerrados = 0;
    size_t i;
    
    if(param == NULL)
        return EOF;
    if(fclose(param->archivo_salida->stream) != EOF)
        archivos_cerrados++;
    if(param->archivo_entrada->nombre == NULL)
        return archivos_cerrados;
    for(i = 0; i < param->cant_archivos; i++){
        if(fclose(param->archivo_entrada[i].stream) != EOF)
            archivos_cerrados++;
    }
    return archivos_cerrados;
}
/*La destruccion de las listas se realiza afuera de esta función, recibe una lista vacia*/
/*Recibe una lista vacía, una estructura archivo_t y un maximo de memoria disponible*/
/*Retorna por el nombre el estado de la operacion de carga de palabras, que es delegado a funciones
mas especificas*/
status_t cargar_lista_palabras(archivo_t archivo, lista_t * lista, size_t * cant_palabras){
    if(lista == NULL)
        return ST_ERROR_PTR_NULO;
    switch(archivo.formato){
        case FMT_TXT:
            if(archivo.nombre == NULL)
                return cargar_lista_palabras_stdin(lista, cant_palabras);
            return cargar_lista_palabras_txt(archivo.stream, lista, cant_palabras);
        case FMT_BIN:
            return cargar_lista_palabras_bin(archivo.stream, lista, cant_palabras);
        default:
            return ST_ERROR_FORMATO_ARCHIVO_INVALIDO;
    }
}
status_t cargar_lista_palabras_txt(FILE * stream, lista_t * lista, size_t * cant_palabras){
    char buffer[MAX_STR], *pch;
    palabra_t palabra;
    status_t st;

    while((fgets(buffer, MAX_STR, stream)) != NULL){
        pch = strtok(buffer, DELIMITADOR_COMENTARIO);
        palabra = strtol(buffer, &pch, 10);
        if (pch == NULL || (*pch != '\n' && *pch != '\0') || !palabra_es_valida(palabra))
            return ST_ERROR_PALABRA_NO_VALIDA;
        if((st = insertar_nodo_final(lista, (void*)palabra)) != ST_OK)
            return st;
        if(!--(*cant_palabras))
            return ST_MEMORIA_INSUFICIENTE;
    }
    if(ferror(stream))
        return ST_ERROR_LEER_PALABRA;
    return ST_OK;
}
status_t cargar_lista_palabras_bin(FILE * stream, lista_t * lista, size_t * cant_palabras){
    uchar high_byte, low_byte;
    palabra_t palabra, opcode;
    uint operando;
    status_t st;
    while((fread(&high_byte,1,1,stream) == 1)){
        if((fread(&low_byte,1,1,stream) != 1))
            return ST_ERROR_LEER_PALABRA;
        palabra = 0;
        /*Palabra en binario, con ceros rellenados a la izquierda*/
        palabra = ((palabra | high_byte) << BYTE_SHIFT) | low_byte;
        /*Reconstruyo la palabra para que en la memoria quede guardado con el mismo formato que txt*/
        /*Aplico convencion complemento a 2 para pasar de binario a formato textp*/
        opcode = get_opcode_bin(palabra);
        operando = get_operando_bin(palabra);
        palabra = opcode * OPCODE_OPERANDO_MULTIPLIER + (opcode >= 0 ? operando : -operando);
        if((st = insertar_nodo_final(lista, (void*)palabra)) != ST_OK)
            return st;
        
        if(!--(*cant_palabras))
            return ST_MEMORIA_INSUFICIENTE;
    }
    if(ferror(stream))
        return ST_ERROR_LEER_PALABRA;
    return ST_OK;
}
status_t cargar_lista_palabras_stdin(lista_t * lista, size_t * cant_palabras){
    char buffer[MAX_STR], *pch;
    palabra_t palabra;
    status_t st;
    size_t i = 0;
    
    fprintf(stdout, "%s\n", MSJ_BIENVENIDO_SIMPLETRON);
    
    while (i < *cant_palabras) {
        fprintf(stdout, "%02lu ? ", i);
        fgets(buffer, MAX_STR, stdin);

        palabra = strtol(buffer, &pch, 10);
        if(palabra == NUMERO_FIN_CARGA)
            break;
        /*Verificaion de que la palabra cumpla requisitos.....*/
        if (pch == NULL || (*pch != '\n' && *pch != '\0') || !palabra_es_valida(palabra)){
            return ST_ERROR_PALABRA_NO_VALIDA;
        }
        /*Lo guardo en la memoria*/
        if((st = insertar_nodo_final(lista, (void*)palabra)) != ST_OK)
            return st;
        i++;
    }
    return ST_OK;
}
int get_opcode_bin(palabra_t palabra){
    return palabra & MASK_MSB ? -((((~palabra) & MASK_OPCODE) >> OPCODE_SHIFT) +1) : palabra >> OPCODE_SHIFT;
}
uint get_operando_bin(palabra_t palabra){
    return palabra & MASK_OPERANDO;
}
