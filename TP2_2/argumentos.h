#ifndef ARGUMENTOS__H
#define ARGUMETNOS__H

#define DEFAULT_MEMORIA 50
#define DEFAULT_CANT_ARCHIVOS 1
#define DEFAULT_ARCHIVO_SALIDA "dump"
#define DEFAULT_ARCHIVO_ENTRADA "stdin"  /*En el procesamiento no voy a usar esta macro, si el nombre queda en NULL se toma por stdin*/

#define FLAG_CLA_AYUDA_CORTO "-h"
#define FLAG_CLA_AYUDA_LARGO "--help"
#define FLAG_CLA_MEMORIA_CORTO "-m"
#define FLAG_CLA_MEMORIA_LARGO "--memoria"
#define FLAG_CLA_FORMATO_CORTO "-f"
#define FLAG_CLA_FORMATO_LARGO "--formato"
#define FLAG_CLA_FORMATO_OPCION_BIN "bin"
#define FLAG_CLA_FORMATO_OPCION_TXT "txt"
#define FLAG_CLA_STDIN_CORTO "-"  /*Esto se usa por consigna*/
#define FLAG_CLA_STDIN_LARGO "stdin"  /* No lo usaría, setearía en NULL el nombre */

status_t validacion_cla(int argc, char** argv, params_s *param);
char * get_name_lmsfile(char* name);
formato_t get_fmt_lmsfile(char* name);

#endif
