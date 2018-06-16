#define CANT_MIN_ARG 2 
/*Para el correcto funcionamiento del programa, la menor cantidad de argumentos ingresados
 es el caso de ./simpletron --help*/

/*FLAGS CLA*/
#define FLAG_CLA_AYUDA_CORTO "-h"
#define FLAG_CLA_AYUDA_LARGO "--help"
#define FLAG_CLA_MEMORIA_CORTO "-m"
#define FLAG_CLA_MEMORIA_LARGO "--memoria"
#define FLAG_CLA_FORMATO_CORTO "-f"
#define FLAG_CLA_FORMATO_LARGO "--formato"

status_t validacion_cla(int argc, char** argv, long *memoria_pedida);
