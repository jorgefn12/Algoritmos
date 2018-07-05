#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "validaciones.h"
#include "tipos.h"

int main(int argc, char** argv) {
    status_t status;
    params_s param;
    simpletron_s *simpletron=NULL;
    char *archivo1 = "asdasd", *archivo2 = "sddddd", *archivo3 = "sdatres";
    int i;
    
    status = validacion_cla(argc, argv, &param);
    if (status != ST_OK) {
        imprimir_mensaje_de_error(status);
        return EXIT_FAILURE;
    }

    /*Cargar en simpletron el nombre y formato guardados en param*/
    for(i=0;i<param.cant_archivos;i++)
        simpletron = crear_simpletron(&simpletron,param.archivo_entrada[i].nombre,param.archivo_entrada[i].formato);
        
    /*Imprimo simpletron*/
    while (simpletron != NULL) {
        /*
        if(simpletron->archivo->formato == FMT_BIN)
            puts("archivos binario");
*/
        if(simpletron->archivo->formato == FMT_TXT)
            cargar_palabras_txt(&simpletron);
        simpletron = simpletron->sig;
    }

    /*Cargar palabras*/

    return EXIT_SUCCESS;
}






/*------------------------------------------------------------------CARGA.C----------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tipos.h"
#include "comun.h"

archivo_s *crear_archivo(void) {
    archivo_s *ret_archivo;

    if ((ret_archivo = (archivo_s *) malloc(sizeof (archivo_s))) == NULL) {
        return NULL;
    }

    return ret_archivo;
}

simpletron_s *crear_simpletron(simpletron_s ** s, char *nombre_archivo_entrada, formato_t fmt) {
    simpletron_s *nuevo;

    /*Creo nodo*/
    if ((nuevo = (simpletron_s*) malloc(sizeof (simpletron_s))) == NULL)
        return NULL;

    /*Creo archivo*/
    nuevo->archivo = crear_archivo();
    if (nuevo->archivo == NULL)
        return NULL;

    /*Cargo el nombre del archivo*/
    nuevo->archivo->nombre = strdup(nombre_archivo_entrada);
    nuevo->archivo->formato = fmt;
    nuevo->sig = *s;
    *s = nuevo;
    return *s;
}

status_t cargar_palabras_txt(simpletron_s **simpletron) {
    FILE *archivo_entrada;
    char *linea, *pch;
    long dato;


    if ((archivo_entrada = fopen((*simpletron)->archivo->nombre, "r")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    printf("ARCHIVO: %s\n",(*simpletron)->archivo->nombre);
    
    if ((linea = (char*) malloc(sizeof (char)*MAX_STR)) == NULL)
        return ST_ERROR_MEMORIA;

    (*simpletron)->archivo->memoria = (palabra_s*) malloc(sizeof (palabra_s));
    while (!feof(archivo_entrada)) {
        if ((fgets(linea, MAX_STR, archivo_entrada)) != NULL) {
            pch = strtok(linea, ";");
            dato = strtol(linea, &pch, 10);

            /*Verificaion de que la palabra cumpla requisitos.....*/

            insertarUltimo(&(*simpletron)->archivo->memoria, dato);
        }
    }

    quitar(&(*simpletron)->archivo->memoria); /*PROBLEMA ENCONTRADO: para agregar a pdf*/
    imprimir((*simpletron)->archivo->memoria);
}

void insertarUltimo(palabra_s **frente, long dato) {
    palabra_s* nueva_palabra = NULL, *ultimo = NULL;

    /*Nuevo nodo*/
    if ((nueva_palabra = (palabra_s*) malloc(sizeof (palabra_s))) == NULL)
        return;

    /*Almacenamos el valor en el nuevo nodo*/
    nueva_palabra->dato = dato;

    /*Al ser el ultimo nodo de la lista, hacemos que apunte a NULL*/
    nueva_palabra->sig = NULL;

    /*Si el frente de la lista es NULL (No existe), entonces 
     * el nuevo nodo es el frente y terminamos la funcion*/
    if ((*frente)->sig == NULL) {
        (*frente)->sig = nueva_palabra;
        return;
    } else {
        /*Itero la lista hasta encontrar el ultimo*/
        /*Inicializamos un nodo "ultimo" que toma el valor del frente de la lista*/
        ultimo = (*frente);
        /*Utilizamos "ultimo->sig" para recorrer la lista hasta llegar al final*/
        while (ultimo->sig != NULL) {
            ultimo = ultimo->sig;
        }
        /*Apuntamos el ultimo elemento de la lista hacia el nuevo nodo*/
        ultimo->sig = nueva_palabra;
    }

    return;
}

void quitar(palabra_s **frente){
    palabra_s *ultimo, *temp;
    long dato;
    
    dato = (*frente)->dato;
    temp = (*frente);
    (*frente) = (*frente)->sig;
    
    if((*frente)==NULL)
        ultimo = NULL;
    
    free(temp);   
}

void imprimir(palabra_s *inicio) {
    while (inicio != NULL) {
        printf("dato guardado: %d\n", inicio->dato);
        inicio = inicio->sig;
    }
}

char* strdup(const char *sc) {
    char *s;

    if (sc == NULL)
        return NULL;

    s = (char*) calloc(1, sizeof (char*)*(strlen(sc) + 1));

    if (s)
        strcpy(s, sc);

    return s;
}














/*-------------------------------------------------------TIPOS.H----------------------------------------*/
typedef long palabra_t;
typedef unsigned int uint;

typedef enum {
    FMT_TXT,
    FMT_BIN
}formato_t;

typedef struct palabra{
    palabra_t dato;
    struct palabra * sig;
}palabra_s;

typedef struct archivo{
    char * nombre;
    formato_t formato;
    palabra_s *memoria;
}archivo_s;

typedef struct simpletron{
    archivo_s *archivo;
    palabra_t acumulador;
    size_t program_counter;
    uint opcode;
    uint operando;
    struct simpletron *sig;
} simpletron_s;

/*Para indicar que el archivo es stdin, se inicializa cant_archivos = 1, nombre = "stdin" y formato = FMT_TXT*/
typedef struct params{
    size_t cant_memoria;
    size_t cant_archivos;
    archivo_s archivo_salida;
    archivo_s * archivo_entrada; /* Por ahora estoy usando esta variable, cuando tengamos el resto del código agregamos los
                                  * nombres directamente a la estructura simpletron */
}params_s;

/*typedef de los operandos*/
typedef enum {
    OP_LEER = 10,
    OP_ESCRIBIR = 11
} opcode_t;

typedef enum {
    FALSE = 0,
    TRUE
} bool_t;

typedef enum {
    ST_OK,
    ST_AYUDA,
    ST_ERROR_PTR_NULO,
    ST_ERROR_ARCHIVO_NO_ENCONTRADO,
    ST_ERROR_MEMORIA,
    /*Validacion cla*/
    ST_ERROR_FLAG_NO_RECONOCIDO,
    ST_ERROR_MEMORIA_INGRESADA_INVALIDA,
    ST_ERROR_FORMATO_ARCHIVO_INVALIDO,
    ST_ERROR_STDIN_INVALIDO
} status_t;



status_t validacion_cla(int argc, char** argv, params_s *param);
char * get_name_lmsfile(char* name);
formato_t get_fmt_lmsfile(char* name);
/*CARGA*/
void cargar_nombre_de_archivo_en_estructura(simpletron_s *simpletron);
void imprimir_mensaje_de_error(status_t status);
archivo_s *crear_archivo(void);
simpletron_s *crear_simpletron(simpletron_s ** s,char *nombre_archivo_entrada,formato_t fmt);

status_t cargar_palabras_txt(simpletron_s **s);
void insertarUltimo(palabra_s **frente, long dato);
void imprimir(palabra_s *inicio);
void quitar(palabra_s **frente);
