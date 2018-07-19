#ifndef CARGA_H
#define CARGA_H

#define BUF_SIZE_BYTE 8
#define BYTE_OPCODE 0x7F00
#define BYTE_OPCODE_SHIFT 7
#define BYTE_OPERANDO 0xFF
#define BYTE_OPERANDO_SHIFT 0
#define BYTE_SHIFT 8
#define BYTE_MSB 0x8000
#endif /* CARGA_H */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "tipos.h"
#include "comun.h"
#include "carga.h"

archivo_s *crear_archivo(void) ;
simpletron_s *crear_simpletron(void) ;
status_t crear_nodo_simpletron(simpletron_s **simpletron, void *dato) ;
status_t crear_lista_memoria(palabra_s **p) ;
status_t crear_lista_memoria_nodo(palabra_s **nodo, int dato) ;
status_t cargar_simpletron(simpletron_s ** frente, params_s params) ;
status_t cargar_archivo(archivo_s *archivo, char *nombre_archivo, formato_t fmt, FILE *f);
status_t cargar_palabras_bin(FILE *archivo_entrada, archivo_s *archivo) ;

status_t cargar_palabras_txt(FILE *f, archivo_s *archivo);
status_t cargar_palabra_stdin(archivo_s *archivo, params_s params);
status_t palabra_valida(long palabra);
status_t palabra_valida_bin(uint16_t palabra);
status_t insertar_en_simpletron(simpletron_s **simpletron, archivo_s *archivo);
status_t insertar_palabra_al_principio_de_lista(palabra_s **p, int d);
status_t insertar_palabra_al_final_de_lista(palabra_s **frente, long dato);
char* strdup(const char *sc);
void imprimir_palabras_de_un_archivo(simpletron_s *simpletron);

#endif
