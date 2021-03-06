#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "tipos.h"
#include "comun.h"
#include "carga.h"
/*Función para crear un nodo de la estructura archivo_s. Si hubo algún error retorna NULL por el nombre, de lo contrario,
* un puntero a dicho nodo
*/
archivo_s *crear_archivo(void) {
    archivo_s *archivo;

    if ((archivo = (archivo_s *) malloc(sizeof (archivo_s))) == NULL)
        return NULL;

    archivo->memoria = NULL;
    archivo->nombre = NULL;

    return archivo;
}
/*
*Función para crear una estrucutra simpletron e inicializar sus componentes. Retorna NULL si hubo un error, de lo contrario, un puntero a
*dicha estructura.
*/
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

/*Función para crear un nodo de la estructura simpletron_s. Recibe un puntero doble a estructura simpletron_s y un dato.
Al finalizar, guarda el puntero hacia el nodo, en el puntero pasado por argumento y retorna por el nombre el estado de la
operacion
*/
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

/*Función para crear un nodo de la estructura palabra_s. Recibe un puntero doble a estructura palabra_s y un dato.
Al finalizar, guarda el puntero hacia el nodo, en el puntero pasado por argumento y retorna por el nombre el estado de la
operacion
*/
status_t crear_lista_memoria_nodo(palabra_s **nodo, int dato) {
    if (!nodo)
        return ST_ERROR_PTR_NULO;

    if (((*nodo) = (palabra_s*) calloc(1, sizeof (palabra_s))) == NULL)
        return ST_ERROR_MEMORIA;

    (*nodo)->sig = NULL;
    (*nodo)->dato = dato;

    return ST_OK;
}


/*Función para realizar la carga de palabras en la memoria de cada simpletron
recibe un puntero doble a simpletron_s y una estrucutra params_s. De acuerdo a la configuración elegida mediante
CLA, delega su procesamiento a otras funciones. Al finalizar exitosamente, guarda todas las palabras de cada archivo en
la estructura simpletron. Devuelve por el nombre el estado de la operacion
*/
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
    if(archivo->formato == FMT_BIN){
        status = cargar_palabras_bin();
    }

    return status;
}

status_t cargar_palabras_bin(FILE *archivo_entrada, archivo_s *archivo) {
    uint16_t temp, temp2, dato;
    status_t status;
    
    while (!feof(archivo_entrada)) {
        /*Obtengo los primeros ocho bits*/
        if ((fread(&temp, sizeof (BUF_SIZE_BYTE), 1, archivo_entrada)) == 1) {
            /*Obtengo los siguientes ocho bits*/
            if ((fread(&temp2, sizeof (BUF_SIZE_BYTE), 1, archivo_entrada)) == 1) {
                temp2 = (temp2 & BYTE_MSB);
                temp2 = temp2 << BYTE_SHIFT;
                dato = temp2 & temp;

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
        } else
            return ST_ERROR_LEER_PALABRA;
    }

    return ST_OK;
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
    free(linea);
    
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

    free(linea);
    
    return ST_OK;
}

status_t palabra_valida(long palabra) {
    int operando, opcode;

    if (palabra > MAX_PALABRA || palabra < MIN_PALABRA)
        return ST_ERROR_PALABRA_NO_VALIDA;

    operando = palabra % OPCODE_OPERANDO;
    if (operando < OPERANDO_MIN || operando > OPERANDO_MAX)
        return ST_ERROR_PALABRA_NO_VALIDA;

    opcode = palabra / OPCODE_OPERANDO;
    if (opcode < OPCODE_MIN || opcode > OPCODE_MAX)
        return ST_ERROR_PALABRA_NO_VALIDA;

    return ST_OK;
}

status_t palabra_valida_bin(uint16_t palabra) {
    uint16_t operando, opcode;

    /*Obtengo el opcode*/
    opcode = palabra;
    opcode &= ~BYTE_OPERANDO; /*Pongo en cero los bits del operando*/
    opcode = opcode>>BYTE_OPCODE_SHIFT; /*Desplazo los bits ocho posiciones*/
    if (opcode < OPCODE_MIN || opcode > OPCODE_MAX)
        return ST_ERROR_PALABRA_NO_VALIDA;

    /*Obtengo el operando*/
    operando = palabra;
    operando &= ~BYTE_OPCODE;

    if (operando < OPERANDO_MIN || operando > OPERANDO_MAX)
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

    (*simpletron)->sig = NULL;
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

