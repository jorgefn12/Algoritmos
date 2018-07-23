#ifndef LECTORES__H
#define LECTORES__H

#define MASK_OPERANDO 0x01FF
#define MASK_OPCODE 0xFE00
#define BYTE_SHIFT 8
#define OPCODE_SHIFT 9
#define MASK_MSB 0x8000
#define MASK_LSB 0x0001
#define DELIMITADOR_COMENTARIO ";"
int abrir_archivos(params_t * param);
int cerrar_archivos(params_t * param);
status_t cargar_lista_palabras(archivo_t archivo, lista_t * lista);
status_t cargar_lista_palabras_txt(FILE * stream, lista_t * lista);
status_t cargar_lista_palabras_bin(FILE * stream, lista_t * lista);
status_t cargar_lista_palabras_stdin(lista_t * lista);
int get_opcode_bin(int palabra);
uint get_operando_bin(int palabra);

#endif
