#include "tipos.h"

#define CANT_MIN_ARG 1
/*Para el correcto funcionamiento del programa, la menor cantidad de argumentos ingresados
 es el caso de ./simpletron */
#define POS_ARGV1 1
#define DEFAULT_MEMORIA 50
#define DEFAULT_CANT_ARCHIVOS 1
#define DEFAULT_ARCHIVO_SALIDA "dump"
#define DEFAULT_ARCHIVO_ENTRADA "stdin"

/*FLAGS CLA*/
#define FLAG_CLA_AYUDA_CORTO "-h"
#define FLAG_CLA_AYUDA_LARGO "--help"
#define FLAG_CLA_MEMORIA_CORTO "-m"
#define FLAG_CLA_MEMORIA_LARGO "--memoria"
#define FLAG_CLA_FORMATO_CORTO "-f"
#define FLAG_CLA_FORMATO_LARGO "--formato"
#define FLAG_CLA_FORMATO_OPCION_BIN "bin"
#define FLAG_CLA_FORMATO_OPCION_TXT "txt"
#define FLAG_CLA_STDIN_CORTO "-"
#define FLAG_CLA_STDIN_LARGO "stdin"


status_t validacion_cla(int argc, char** argv, params_s *param);
char * get_name_lmsfile(char* name);
formato_t get_fmt_lmsfile(char* name);
