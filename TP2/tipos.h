/*Agregué cant_palabras a archivo_s*/

#ifndef TIPOS__h
#define TIPOS__h

typedef int palabra_t;
typedef unsigned int uint;

typedef enum {
    FMT_TXT,
    FMT_BIN
} formato_t;

typedef struct palabra {
    palabra_t dato;
    struct palabra * sig;
} palabra_s;

typedef struct archivo {
    char * nombre;
    formato_t formato;
    palabra_s *memoria;
    size_t cant_palabras;
} archivo_s;

typedef struct simpletron{
    archivo_s * archivo;
    palabra_t acumulador;
    int instruccion;
    opcode_t opcode;
    uint operando;
    size_t program_counter;
    struct simpletron *sig;
} simpletron_s;

/*Para indicar que el archivo es stdin, se inicializa cant_archivos = 1, nombre = "stdin" y formato = FMT_TXT*/
typedef struct params {
    size_t cant_memoria;
    size_t cant_archivos;
    archivo_s archivo_salida;
    archivo_s * archivo_entrada; /* Por ahora estoy usando esta variable, cuando tengamos el resto del código agregamos los
                                  * nombres directamente a la estructura simpletron */
} params_s;

/*typedef de los operandos*/
typedef enum{
    OP_LEER = 10,
    OP_ESCRIBIR,
    OP_CARGAR = 20,
    OP_GUARDAR,
    OP_PCARGAR,
    OP_PGUARDAR,
    OP_SUMAR = 30,
    OP_RESTAR,
    OP_DIVIDIR,
    OP_MULTIPLICAR,
    OP_JMP = 40,
    OP_JMPNEG,
    OP_JMPZERO,
    OP_JNZ,
    OP_DJNZ,
    OP_HALT
}opcode_t;

typedef enum {
    FALSE = 0,
    TRUE
} bool_t;

typedef enum{
    ST_OK,
    ST_AYUDA,
    ST_ERROR_CANT_ARG,
    ST_ERROR_STDIN_INVALIDO,
    ST_ERROR_PTR_NULO,
    ST_ERROR_ARCHIVO_NO_ENCONTRADO,
    ST_ERROR_MEMORIA,
    ST_ERROR_MEMORIA_INGRESADA_INVALIDA,
    ST_ERROR_FORMATO_ARCHIVO_INVALIDO,
    ST_ERROR_NODO_VACIO,
    /*carga de archivo*/
    ST_ERROR_PALABRA_NO_VALIDA,
    ST_ERROR_LEER_PALABRA,
    ST_ERROR_CREAR_SIMPLETRON,
    /*status de ejecutar_codigo*/
    ST_HALT,
    ST_ERROR_CAD_NO_ES_ENTERO,
    ST_ERROR_PALABRA_FUERA_DE_RANGO,
    ST_ERROR_SEGMENTATION_FAULT,
    ST_ERROR_CAD_NO_LEIDA,
    ST_ERROR_OPCODE_INVALIDO,
    ST_ERROR_MAX_INSTR_SUPERADO,
    ST_ERROR_ESCRIBIR_BIN,
    ST_ERROR_MAX_INGRESOS_SUPERADO
}status_t;

status_t validacion_cla(int argc, char** argv, params_s *param);
char * get_name_lmsfile(char* name);
formato_t get_fmt_lmsfile(char* name);
void imprimir_ayuda();
/*CARGA*/
void cargar_nombre_de_archivo_en_estructura(simpletron_s *simpletron);
void imprimir_mensaje_de_error(status_t status);
archivo_s *crear_archivo(void);

status_t cargar_simpletron(simpletron_s ** frente,params_s params);
status_t cargar_palabras_txt(FILE *f, archivo_s *archivo);
status_t cargar_palabras_bin(simpletron_s **s);
status_t insertar_palabra_al_final_de_lista(palabra_s **frente, long dato);
void imprimir_palabras_de_un_archivo(simpletron_s *simpletron);
status_t palabra_valida(long palabra);
status_t insertar_en_simpletron(simpletron_s **simpletron, archivo_s *archivo);

status_t cargar_archivo(archivo_s *archivo, char *nombre_archivo, formato_t fmt, FILE *f);
status_t insertar_en_simpletron(simpletron_s **simpletron, archivo_s *archivo);
status_t crear_nodo_simpletron(simpletron_s **simpletron,void *dato);
status_t crear_lista_memoria(palabra_s **p);
status_t crear_lista_memoria_nodo(palabra_s **nodo, int dato);
status_t insertar_palabra_al_principio_de_lista(palabra_s **p,int d);

typedef status_t (*pfx_lms) (simpletron_s*, palabra_s*, palabra_s*); /*Puntero a función con el formato de funciones simpletron*/

        
#endif
