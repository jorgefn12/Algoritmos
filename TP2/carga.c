#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tipos.h"
#include "comun.h"

archivo_s *crear_archivo(void) {
    archivo_s *archivo;

    if ((archivo = (archivo_s *) malloc(sizeof (archivo_s))) == NULL)
        return NULL;

    archivo->memoria = NULL;
    archivo->nombre = NULL;

    return archivo;
}

simpletron_s *crear_simpletron(void) {
    simpletron_s *simpletron = NULL;

    if ((simpletron = (simpletron_s*) malloc(sizeof (simpletron_s))) == NULL)
        return NULL;

    simpletron->acumulador = 0;
    simpletron->archivo = NULL;
    simpletron->opcode = 0;
    simpletron->operando = 0;
    simpletron->sig = NULL;

    return simpletron;
}

status_t crear_nodo_simpletron(simpletron_s **simpletron, void *dato) {
    if (simpletron == NULL)
        return ST_ERROR_PTR_NULO;

    if ((*simpletron = (simpletron_s*) calloc(1, sizeof (simpletron_s))) == NULL) {
        return ST_ERROR_MEMORIA;
    }

    (*simpletron)->sig = NULL;
    (*simpletron)->archivo = dato;

    return ST_OK;
}

status_t crear_lista_memoria(palabra_s **p) {
    if (!p)
        return ST_ERROR_PTR_NULO;
    *p = NULL;
    return ST_OK;
}

status_t crear_lista_memoria_nodo(palabra_s **nodo, int dato) {
    puts("crear lista memoria nodo");
    if (!nodo)
        return ST_ERROR_PTR_NULO;

    if (((*nodo) = (palabra_s*) calloc(1, sizeof (palabra_s))) == NULL)
        return ST_ERROR_MEMORIA;

    (*nodo)->sig = NULL;
    (*nodo)->dato = dato;

    return ST_OK;
}

status_t cargar_simpletron(simpletron_s ** frente, params_s params) {
    archivo_s *archivo = NULL;
    int i;
    FILE *f = NULL;

    archivo = crear_archivo();
    if (archivo == NULL)
        return ST_ERROR_PTR_NULO;

    /*Creo lista*/
    *frente = crear_simpletron();

    for (i = 0; i < params.cant_archivos; i++) {
        /*ABRO ARCHIVO*/
        if (params.archivo_entrada->formato == FMT_BIN) {
            if ((f = fopen(params.archivo_entrada[i].nombre, "rb")) == NULL)
                return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
        } else {
            if ((f = fopen(params.archivo_entrada[i].nombre, "r")) == NULL)
                return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
        }

        /*Lo guardo en archivo*/
        cargar_archivo(archivo, params.archivo_entrada[i].nombre, params.archivo_entrada[i].formato, f);
        insertar_en_simpletron(frente, archivo);
        archivo = crear_archivo();
    }


    fclose(f);
    return ST_OK;
}

status_t cargar_archivo(archivo_s *archivo, char *nombre_archivo, formato_t fmt, FILE *f) {
    status_t status;

    archivo->nombre = strdup(nombre_archivo);
    archivo->formato = fmt;
    if (archivo->formato == FMT_TXT) {
        status = cargar_palabras_txt(f, archivo);
    }

    return status;
}

status_t cargar_palabras_bin(simpletron_s **simpletron) {
    FILE *archivo_entrada;
    long dato;

    if ((archivo_entrada = fopen((*simpletron)->archivo->nombre, "rb")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    printf("ARCHIVO: %s\n", (*simpletron)->archivo->nombre);

    (*simpletron)->archivo->memoria = (palabra_s*) malloc(sizeof (palabra_s));
    while (!feof(archivo_entrada)) {
        if ((fread(&dato, sizeof (BUF_SIZE_BIN), 1, archivo_entrada)) == 1) {
            insertar_palabra_al_final_de_lista(&(*simpletron)->archivo->memoria, dato);
        } else
            return ST_ERROR_LEER_PALABRA;
    }

}

status_t cargar_palabras_txt(FILE *f, archivo_s *archivo) {
    char *linea, *pch;
    long dato;
    status_t status;
    size_t cant_palabras;

    if ((linea = (char*) malloc(sizeof (char)*MAX_STR)) == NULL)
        return ST_ERROR_MEMORIA;

    while (!feof(f)) {
        if ((fgets(linea, MAX_STR, f)) != NULL) {
            pch = strtok(linea, ";");
            dato = strtol(linea, &pch, 10);

            /*Verificaion de que la palabra cumpla requisitos.....*/
            status = palabra_valida(dato);
            if (status != ST_OK) {
                return status;
            }

            /*Lo guardo en la memoria*/
            if (archivo->memoria == NULL) {
                if ((archivo->memoria = (palabra_s*) malloc(sizeof (palabra_s))) == NULL)
                    return ST_ERROR_MEMORIA;

                status = crear_lista_memoria(&(archivo)->memoria);

                if ((status = crear_lista_memoria_nodo(&(archivo)->memoria, dato)) != ST_OK)
                    return ST_ERROR_MEMORIA;
            } else {
                status = insertar_palabra_al_final_de_lista(&(archivo)->memoria, dato);
            }
            cant_palabras++;
        }
    }
    archivo->cant_palabras = cant_palabras;

    return ST_OK;
}

status_t cargar_palabra_stdin(archivo_s *archivo, params_s params) {
    char *linea, *pch;
    long dato;
    status_t status;
    size_t i = 0;

    if ((linea = (char*) malloc(sizeof (char)*MAX_STR)) == NULL)
        return ST_ERROR_MEMORIA;

    fgets(linea, MAX_STR, stdin);

    while (i < params.cant_memoria) {
        if (strcmp(linea, STR_FIN_CARGA) == 0) {
            dato = strtol(linea, &pch, 10);

            /*Verificaion de que la palabra cumpla requisitos.....*/
            if (pch == NULL || (*pch != '\n' && *pch != '\0'))
                return ST_ERROR_PALABRA_NO_VALIDA;
            status = palabra_valida(dato);
            if (status != ST_OK) {
                return status;
            }

            /*Lo guardo en la memoria*/
            if (archivo->memoria == NULL) {
                if ((archivo->memoria = (palabra_s*) malloc(sizeof (palabra_s))) == NULL)
                    return ST_ERROR_MEMORIA;

                status = crear_lista_memoria(&(archivo)->memoria);

                if ((status = crear_lista_memoria_nodo(&(archivo)->memoria, dato)) != ST_OK)
                    return ST_ERROR_MEMORIA;
            } else {
                status = insertar_palabra_al_final_de_lista(&(archivo)->memoria, dato);
            }
        }
        i++;
    }

    return ST_OK;
}

status_t palabra_valida(long palabra) {
    int operando, opcode;
    
    if (palabra > MAX_PALABRA || palabra < MIN_PALABRA)
        return ST_ERROR_PALABRA_NO_VALIDA;

    operando = palabra%OPCODE_OPERANDO;
    if(operando<OPERANDO_MIN || operando>OPERANDO_MAX)
        return ST_ERROR_PALABRA_NO_VALIDA;
        
    opcode = palabra/OPCODE_OPERANDO;
    if(opcode<OPCODE_MIN || opcode>OPCODE_MAX)
        return ST_ERROR_PALABRA_NO_VALIDA;
    
    return ST_OK;
}

status_t insertar_en_simpletron(simpletron_s **simpletron, archivo_s *archivo) {
    simpletron_s *temp;
    status_t status;

    if (simpletron == NULL || archivo == NULL)
        return ST_ERROR_PTR_NULO;

    if ((status = crear_nodo_simpletron(&temp, archivo)) != ST_OK) {
        return status;
    }

    temp->sig = *simpletron;
    *simpletron = temp;

    return ST_OK;
}

status_t insertar_palabra_al_principio_de_lista(palabra_s **p, int d) {
    status_t status;
    palabra_s *temp;

    if (!p)
        return ST_ERROR_PTR_NULO;

    if ((status = crear_lista_memoria_nodo(&temp, d)) != ST_OK)
        return status;

    temp->sig = *p;
    *p = temp;
    return ST_OK;
}

status_t insertar_palabra_al_final_de_lista(palabra_s **frente, long dato) {
    palabra_s* nueva_palabra = NULL, *ultimo = NULL;

    /*Nuevo nodo*/
    if ((nueva_palabra = (palabra_s*) malloc(sizeof (palabra_s))) == NULL)
        return ST_ERROR_MEMORIA;

    /*Almacenamos el valor en el nuevo nodo*/
    nueva_palabra->dato = dato;

    /*Al ser el ultimo nodo de la lista, hacemos que apunte a NULL*/
    nueva_palabra->sig = NULL;

    /*Si el frente de la lista es NULL (No existe), entonces 
     * el nuevo nodo es el frente y terminamos la funcion*/
    if ((*frente)->sig == NULL) {
        (*frente)->sig = nueva_palabra;
        return ST_OK;
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

    return ST_OK;
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

void imprimir_palabras_de_un_archivo(simpletron_s *simpletron) {
    while (simpletron->archivo->memoria != NULL) {
        printf("Dato guardado: %d\n", simpletron->archivo->memoria->dato);
        simpletron->archivo->memoria = simpletron->archivo->memoria->sig;
    }
}
