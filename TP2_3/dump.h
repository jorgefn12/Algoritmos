#ifndef DUMP__H
#define DUMP__H

#include "simpletron.h"
#include "idiomas.h"

#define MASK_LOW_BYTE 0xFF
#define MASK_HIGH_BYTE 0xFF00

void imprimir_dump(simpletron_t * simpletron, archivo_t * archivo_salida);
void imprimir_dump_txt(simpletron_t * simpletron, FILE * stream);
void imprimir_dump_bin(simpletron_t * simpletron, FILE * stream);

#endif
