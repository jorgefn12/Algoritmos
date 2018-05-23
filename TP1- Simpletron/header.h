#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define POS_ARGV0 0
#define POS_ARGV1 1
#define POS_ARGV2 2
#define POS_ARGV3 3
#define POS_ARGV4 4
#define POS_ARGV5 5
#define POS_ARGV6 6
#define POS_ARGV7 7
#define POS_ARGV8 8
#define POS_ARGV9 9
#define POS_ARGV10 10

#define DEFAULT_M 50
#define CANT_MAX_ARG 11
#define CANT_MIN_ARG 2
#define INIT_INSTRUCCIONES 0
#define MIN_PALABRA -9999
#define MAX_PALABRA 9999
#define MAX_INSTRICCIONES 200
#define MAX_STR 200
#define CANT_MAX_M 200

/*ARGUMENTOS*/
#define CLA_AYUDA "-h"
#define CLA_M "-m"
#define CLA_I "-i"
#define CLA_I_DEFAULT "-"
#define CLA_IF "-if"
#define CLA_IF_OPT_TXT "txt"
#define CLA_IF_OPT_BIN "bin"
#define CLA_O "-o"
#define CLA_OF "-of"

#define INICIO_COMENTARIO ";"
#define STR_STDIN "stdin"
#define STR_STDOUT "stdout"
#define FINALIZAR_CARGA "-99999\n"
#define NOMBRE_GENERICO_ARCHIVO_BIN "dump"

/*constantes de ejecutar_codigo*/
#define LEER 10
#define ESCRIBIR 11
#define CARGAR 20
#define GUARDAR 21
#define PCARGAR 22
#define PGUARDAR 23
#define SUMAR 30
#define RESTAR 31
#define DIVIDIR 32
#define MULTIPLICAR 33
#define JMP 40
#define JMPNEG 41
#define JMPZERO 42
#define JNZ 43
#define DJNZ 44
#define HALT 45

/*MENSAJES DE AYUDA*/
#define MSJ_AYUDA_TITULO "------------------------------AYUDA------------------------------"
#define MSJ_AYUDA_M1 "OPCION |N|: Simpletron tiene una memoria de N palabras. Si no se da el argumento, por omisión tendrá 50 palabras. El maximo es de 200 palabras"
#define MSJ_AYUDA_I1 "OPCION |ARCHIVO|: El programa se leerá del archivo pasado como opción, en caso contrario, de stdin."
#define MSJ_AYUDA_IF1 "OPCION |BIN|: El archivo de entrada se entenderá como una secuencia binaria de enteros que representan las palabras que forman el programa."
#define MSJ_AYUDA_IF2 "OPCION |TXT|: El archivo de entrada se interpretará como secuencia de números, cada uno en una única línea."
#define MSJ_AYUDA_O1 "OPCION |ARCHIVO|: El dump se hará en el archivo pasado como opción, si no pasa el argumento, el volcado se hará por stdout."
#define MSJ_AYUDA_OF1 "OPCION |BIN|: El volcado se hará en binario guardando cada elemento de la estructura del Simpletron, además de la memoria."
#define MSJ_AYUDA_OF2 "OPCION |TXT|: El volcado se hará en formato de texto imprimiendo los registros y la memoria."

/*MENSAJES DE ERRORES*/
#define MSJ_MAS_AYUDA "Ingrese -h para mas ayuda"
#define MSJ_ERROR "Ocurrio un error"
#define MSJ_ERROR_IF_NO_VALIDO "El ingreso de archivo de entrada es invalido"
#define MSJ_ERROR_ARCHIVO_I_NO_INGRESADO "No se ingreso el archivo de entrada"
#define MSJ_ERROR_IF_NO_INGRESADO "No se ingreso el tipo de archivo de entrada"
#define MSJ_ERROR_OF_NO_VALIDO "El ingreso de archivo de salida es invalido"
#define MSJ_ERROR_OF_NO_INGRESADO "No se ingreso el tipo de archivo de salida"
#define MSJ_ERROR_CANT_ARG "La cantidad de argumentos ingresados no es valido"
#define MSJ_ERROR_ARCHIVO_NO_ENCONTRADO "El archivo no existe u ocurrio un error al abrirlo"
#define MSJ_ERROR_PTR_NULO "Puntero nulo"
#define MSJ_ERROR_MEM "Error de memoria"
#define MSJ_INGRESO_PALABRA "Ingrese una palabra: "
#define MSJ_ERROR_M_NO_VALIDO "El valor de memoria asignado es invalido"
#define MSJ_ERROR_ESCRIBIR_BIN "Error al escribir el archivo bin"
#define MSJ_ERROR_CAD_NO_ES_ENTERO "La cadena contiene carácteres no numericos"
#define MSJ_ERROR_PALABRA_FUERA_DE_RANGO "La palabra excede el rango admitido por Simpletron [-9999;+9999]"
#define MSJ_ERROR_SEGMENTATION_FAULT "Se intentó acceder a memoria que Simpletron no solicitó"
#define MSJ_ERROR_CAD_NO_LEIDA "No pudo leer el valor ingresado"
#define MSJ_ERROR_OPCODE_INVALIDO "El código de instrucción no es válido"
#define MSJ_ERROR_MAX_INSTR_SUPERADO "La cantidad de instrucciones operadas alcanzó el máximo admitido"
#define MSJ_ERROR_INGRESO_PALABRA "Error. La palabra debe ser un entero sin caracteres alfabeticos. Vuelva a ingresar la palabra"

/*EJECUCION CODIGO*/
#define MSJ_COMIENZO_EJECUCION "******** INICIO DE EJECUCION DEL SIMPLETRON *******"
#define MSJ_FIN_EJECUCION "********* FIN DE EJECUCION DEL SIMPLETRON *********"
#define MSJ_INGRESO_PALABRA "Ingrese una palabra: "
#define MSJ_IMPRIMIR_PALABRA "Contenido de la posición"

/*DUMP*/
#define DUMP_MSJ_INICIO "\nREGISTROS:"
#define DUMP_MSJ_ACUMULADOR "acumulador"
#define DUMP_MSJ_PROGRAM_COUNTER "program counter"
#define DUMP_MSJ_INSTRUCCION "instruccion"
#define DUMP_MSJ_OPCODE "opcodo"
#define DUMP_MSJ_OPERANDO "operando"
#define DUMP_MSJ_MEMORIA "\nMEMORIA"

typedef enum {
    ST_OK,
    ST_HELP,
    ST_ERROR_CANT_ARG,
    ST_ERROR_PTR_NULO,
    ST_ERROR_ARCHIVO_I_NO_INGRESADO,
    ST_ERROR_IF_NO_VALIDO,
    ST_ERROR_IF_NO_INGRESADO,
    ST_ERROR_OF_NO_VALIDO,
    ST_ERROR_OF_NO_INGRESADO,
    ST_ERROR_ARCHIVO_NO_ENCONTRADO,
    ST_ERROR_MEM,
    ST_ERROR_M_INVALIDO,
    /*status de ejecutar_codigo*/
    ST_ERROR_CAD_NO_ES_ENTERO,
    ST_ERROR_PALABRA_FUERA_DE_RANGO,
    ST_ERROR_SEGMENTATION_FAULT,
    ST_ERROR_CAD_NO_LEIDA,
    ST_ERROR_OPCODE_INVALIDO,
    ST_ERROR_MAX_INSTR_SUPERADO,
    ST_ERROR_ESCRIBIR_BIN
} status_t;

typedef enum {
    TRUE, FALSE
} bool_t;

typedef enum {
    ARCHIVO_BIN,
    ARCHIVO_TXT,
    ARCHIVO_DEFAULT
} archivo_t;

typedef struct {
    int * memoria;
    /*opcode, operando*/
    long acumulador;
    int program_counter;
    size_t cantidad_memoria;
    int opcode;
    int operando;
    int instruccion; /*memoria[program_counter]*/
} palabras_s;

/*Validacion*/
status_t validacion_cla(int argc, char **argv, size_t *m, char *archivo_i, archivo_t *tipo_archivo_i, char *archivo_f, archivo_t *tipo_archivo_f);
/*Carga de estructura*/
status_t leer_archivo(char *nombre_archivo_entrada, const archivo_t tipo_archivo_entrada, palabras_s *palabra);
status_t cargar_estructura_txt(palabras_s** palabra, char *nombre_archivo_entrada);
status_t cargar_estructura_bin(palabras_s* palabra, char* nombre_archivo_entrada);
status_t cargar_estructura_stdin(palabras_s *palabras);
/*Imprimir*/
void imprimir_ayuda();
void imprimir_errores(status_t status);
status_t imprimir_dump_por_stdout_o_txt(palabras_s palabra, char *nombre_archivo_salida, archivo_t tipo_archivo_salida);
status_t dump(archivo_t tipo_archivo_salida, char* nombre_archivo_salida, palabras_s palabra);
status_t imprimir_dump_bin(palabras_s palabra, char *nombre_archivo_salida, archivo_t tipo_archivo_salida);
/*Acumulador*/
status_t ejecutar_codigo(palabras_s * palabra);