#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/****************************COMUN.H********************************************************/
#define MAX_STR 200
typedef struct vector{
    size_t usado, pedido;
    void * datos;
} vector_t; /********ENCAPSULAR*************/
/****************************TIPOS.H********************************************************/
typedef enum{
    FALSE = 0,
    TRUE
}bool_t;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef enum{
    ST_OK,
    ST_AYUDA,
    ST_ERROR_STDIN_INVALIDO,
    ST_ERROR_PTR_NULO,
    ST_ERROR_ARCHIVO_NO_ENCONTRADO,
    ST_ERROR_MEMORIA,
    ST_ERROR_MEMORIA_INGRESADA_INVALIDA,
    ST_ERROR_FORMATO_ARCHIVO_INVALIDO,
    /*carga de archivo*/
    ST_ERROR_PALABRA_NO_VALIDA,
    ST_ERROR_LEER_PALABRA,
    /*status de ejecutar_codigo*/
    ST_HALT,
    ST_ERROR_SEGMENTATION_FAULT,
    ST_ERROR_OPCODE_INVALIDO,
    ST_ERROR_OVERFLOW
}status_t;
typedef enum{
    FMT_TXT,
    FMT_BIN        
}formato_t;
typedef struct archivo{
    char * nombre;
    formato_t formato;
    FILE * stream;
}archivo_t;
/****************************LISTAS.H********************************************************/
typedef struct nodo{
    struct nodo * sig;
    void * dato;
} nodo_t, * lista_t; /********ENCAPSULAR*************/
status_t crear_lista(lista_t * lista);
nodo_t * crear_nodo(void * dato);
bool_t lista_esta_vacia(lista_t lista);
status_t insertar_nodo_final(lista_t * lista, void * dato);
status_t insertar_nodo_ppio(lista_t * lista, void * dato);
void destruir_lista(lista_t * lista);
void imprimir_lista_int(lista_t lista);
bool_t guardar_lista_en_vector(lista_t lista, vector_t ** vector);
/***************************************MEMORIA.H***********************************************/

vector_t * crear_vector(size_t n);
bool_t vector_redimensionar(vector_t *v, size_t n);
void vector_destruir(vector_t ** v);
bool_t vector_guardar_int(vector_t * v, size_t i, int * dato);
void vector_iterar_int(vector_t * v, void (*func)(void *,void *), void * arg);
void imprimir_int(void* datos, void * stream);
int obtener_dato(vector_t * v, size_t i);
int obtener_usado(vector_t * v);
int obtener_pedido(vector_t * v);
/*************************************ARGUMENTOS.H*****************************************************/
#define DEFAULT_MEMORIA 50
#define DEFAULT_CANT_ARCHIVOS 1
#define FLAG_CLA_AYUDA_CORTO "-h"
#define FLAG_CLA_AYUDA_LARGO "--help"
#define FLAG_CLA_MEMORIA_CORTO "-m"
#define FLAG_CLA_MEMORIA_LARGO "--memoria"
#define FLAG_CLA_FORMATO_CORTO "-f"
#define FLAG_CLA_FORMATO_LARGO "--formato"
#define FLAG_CLA_STDIN_CORTO "-"
#define FLAG_CLA_FORMATO_OPCION_BIN "bin"
#define FLAG_CLA_FORMATO_OPCION_TXT "txt"
#define DEFAULT_ARCHIVO_SALIDA "dump"
#define DEFAULT_ARCHIVO_ENTRADA NULL
#define FMT_BIN_DELIMITER "b:"
#define FMT_TXT_DELIMITER "t:"
typedef struct param{
    size_t cant_memoria;
    size_t cant_archivos;
    archivo_t * archivo_salida;
    archivo_t * archivo_entrada;
}params_t;
status_t validacion_cla(int argc, char** argv, params_t *param);
char * get_name_lmsfile(char* name);
formato_t get_fmt_lmsfile(char* name);
void destruir_params(params_t * param);
/*********************************ERRORES.H****************************************************/
#define MSJ_OPCION_AYUDA "Ingrese: .\\simpletron -h o .\\simpletron --help para mas informacion."
#define MSJ_ST_OK "La operación finalizó correctamente"
#define MSJ_ST_AYUDA "Leer documentación. Escribir función para mensaje de ayuda"
#define MSJ_ST_ERROR_PTR_NULO "Puntero nulo"
#define MSJ_ST_ERROR_MEMORIA "Ocurrio un error al pedir memoria"
#define MSJ_ST_ERROR_ARCHIVO_NO_ENCONTRADO "El archivo ingresado no se encuentra"
/*Validacion de argumentos*/
#define MSJ_ST_ERROR_MEMORIA_INGRESADA_INVALIDA "La memoria ingresada no es valida, la misma debe ser un entero positivo"
#define MSJ_ST_ERROR_FORMATO_ARCHIVO_INVALIDO "El formato de archivo de salida no es valido"
#define MSJ_ST_ERROR_STDIN_INVALIDO "stdin no valido"
/*carga*/
#define MSJ_ST_ERROR_LEER_PALABRA "Ocurrio un error al leer palabra del archivo"
#define MSJ_ST_ERROR_PALABRA_NO_VALIDA "La palabra ingresada no es valida"
/*ejecucion*/
#define MSJ_ST_ERROR_SEGMENTATION_FAULT "Se intentó acceder a un área restringida de memoria"
#define MSJ_ST_ERROR_OPCODE_INVALIDO "Se trató de ejecutar una instrucción no especificada en el lenguaje"
#define MSJ_ST_ERROR_OVERFLOW "Se trató de operar con un rango de números no soportados por la máquina"
#define MSJ_ST_HALT "Finalizó la ejecución del archivo"
void imprimir_estado(status_t status);
void imprimir_ayuda(void); /***********ESCRIBIR FUNCION DE AYUDA**************************/
/********************************SIMPLETRON.H****************************************************/
#define MSJ_COMIENZO_EJECUCION "******** INICIO DE EJECUCION DEL SIMPLETRON *******"
#define MSJ_FIN_EJECUCION "********* FIN DE EJECUCION DEL SIMPLETRON *********"
#define MSJ_INGRESO_PALABRA "Ingrese una palabra: "
#define MSJ_IMPRIMIR_PALABRA "Contenido de la posición"

#define MIN_PALABRA -640511  /*Maximo alcanzable en formato texto que puede abarcar el formato binario*/
#define MAX_PALABRA 630511
#define OPCODE_OPERANDO_MULTIPLIER 10000
#define OPERANDO_MIN 0 /*xxxxxxx000000000*/
#define OPERANDO_MAX 511 /*xxxxxxx111111111*/
#define OPCODE_MIN 0 /*0000000xxxxxxxxx*/
#define OPCODE_MAX 127 /*1111111xxxxxxxxx*/
#define OPCODE_FIELD_MIN -64 /*1000000xxxxxxxxx*/
#define OPCODE_FIELD_MAX 63 /*0111111xxxxxxxxx*/
typedef int palabra_t;
typedef unsigned int uint_t;
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
typedef struct simpletron{ /********ENCAPSULAR????*************/
    palabra_t instruccion, acumulador;
    opcode_t opcode;
    uint operando;
    size_t program_counter;
    vector_t ** memoria; /*Se guarda una memororia por cada archivo*/
}simpletron_t;
typedef status_t (*pfx_lms)(simpletron_t *, vector_t *);
simpletron_t * crear_simpletron(params_t * param);
void destruir_simpletron(simpletron_t ** simpletron);
void imprimir_registros_simpletron(simpletron_t * simpletron, FILE * stream);
bool_t palabra_es_valida(palabra_t palabra);
status_t ejecutar_codigo(simpletron_t * simpletron, params_t * param);
status_t lms_leer(simpletron_t * simpletron, vector_t * memoria);
status_t lms_escribir(simpletron_t * simpletron, vector_t * memoria);
status_t lms_cargar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_guardar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_pcargar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_pguardar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_sumar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_restar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_dividir(simpletron_t * simpletron, vector_t * memoria);
status_t lms_multiplicar(simpletron_t * simpletron, vector_t * memoria);
status_t lms_jmp(simpletron_t * simpletron, vector_t * memoria);
status_t lms_jmpneg(simpletron_t * simpletron, vector_t * memoria);
status_t lms_jmpzero(simpletron_t * simpletron, vector_t * memoria);
status_t lms_jnz(simpletron_t * simpletron, vector_t * memoria);
status_t lms_djnz(simpletron_t * simpletron, vector_t * memoria);
status_t lms_halt(simpletron_t * simpletron, vector_t * memoria);
/*******************************LECTORES.H*****************************************************/
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
/**********************************************************************************************/

void debug(){
    static size_t i;
    
    printf("FUNCIONA %lu\n", i++);
}
int main(int argc, char** argv){
    /*MAIN PARA TESTEAR OPCODES Y OPERANDOS
    int palabra;
    int opcode;
    uint operando;
    uchar high_byte = 1, low_byte = 1;

    palabra = 0;
    palabra = ((palabra | high_byte) << BYTE_SHIFT) | low_byte;
    printf("palabra: %d\n",palabra);
    
    opcode = get_opcode_bin(palabra);
    operando = get_operando_bin(palabra);
    printf("opcode: %d\n",opcode);
    printf("operando: %d\n",operando);
    
    palabra = opcode * OPCODE_OPERANDO_MULTIPLIER + (opcode >= 0 ? operando : -operando);
    printf("palabra_final: %d\n",palabra);
    */
    /*MAIN PARA TESTEAR FUNCION DE ARGUMENTOS, APERTURA/CIERRE DE ARCHIVOS y SIMPLETRON*/
    simpletron_t * simply = NULL;
    status_t st;
    params_t argumentos;
    lista_t lista;
    size_t i;
    vector_t * v;
    
    validacion_cla(argc, argv, &argumentos);
    if(st == ST_OK){
        for(i=0;i<argumentos.cant_archivos;i++){
            printf("Archivo entrada %lu: %s [%d]\n", i+1, argumentos.archivo_entrada[i].nombre ? argumentos.archivo_entrada[i].nombre : "stdin(null)", argumentos.archivo_entrada[i].formato);
        }
        printf("Archivo salida: %s [%d]\n",argumentos.archivo_salida->nombre, argumentos.archivo_salida->formato);
        printf("Cantidad memoria: %ld\n", argumentos.cant_memoria);
        printf("Cantidad archivos entrada: %ld\n", argumentos.cant_archivos);
    }

    simply = crear_simpletron(&argumentos);
    imprimir_registros_simpletron(simply, stdout);

    printf("Cantidad archivos abiertos: %lu\n", abrir_archivos(&argumentos));
    
    for(i = 0; i < argumentos.cant_archivos; i++){
        crear_lista(&lista);
        cargar_lista_palabras(argumentos.archivo_entrada[i], &lista);
        puts("Imprimiendo lista");
        imprimir_lista_int(lista);
        guardar_lista_en_vector(lista, &simply->memoria[i]);
        vector_iterar_int(simply->memoria[i],imprimir_int, stdout);
        putchar('\n');
    }
    ejecutar_codigo(simply, &argumentos);
    printf("Cantidad archivos cerrados: %lu\n", cerrar_archivos(&argumentos));
    destruir_simpletron(&simply);
    destruir_params(&argumentos);
    
    /*MAIN PARA TESTEAR LISTAS
    lista_t lista;
    int valores[] = {0,1,2,3,4,5,6,7,8,9};
    crear_lista(&lista);
    insertar_nodo_final(&lista, valores[1]);
    insertar_nodo_final(&lista, valores[2]);
    insertar_nodo_final(&lista, valores[3]);
    insertar_nodo_final(&lista, valores[5]);
    insertar_nodo_final(&lista, valores[9]);
    insertar_nodo_ppio(&lista, valores[0]);
    imprimir_lista_int(lista);
    
    destruir_lista(&lista);
    */
    /*MAIN PARA TESTEAR VECTORES
    vector_t * v;
    params_t argumentos;
    status_t st;
    lista_t lista, * header;
    size_t i, j;
    
    header = &lista;
    validacion_cla(argc, argv, &argumentos);
    if(st == ST_OK){
        for(i=0;i<argumentos.cant_archivos;i++){
            printf("Archivo entrada %lu: %s [%d]\n", i+1, argumentos.archivo_entrada[i].nombre ? argumentos.archivo_entrada[i].nombre : "stdin(null)", argumentos.archivo_entrada[i].formato);
        }
        printf("Archivo salida: %s [%d]\n",argumentos.archivo_salida->nombre, argumentos.archivo_salida->formato);
        printf("Cantidad memoria: %ld\n", argumentos.cant_memoria);
        printf("Cantidad archivos entrada: %ld\n", argumentos.cant_archivos);
    }
    printf("Cantidad archivos abiertos: %lu\n", abrir_archivos(&argumentos));
    v = crear_vector(20);
    for(i = 0; i < argumentos.cant_archivos; i++){
        crear_lista(&lista);
        cargar_lista_palabras(argumentos.archivo_entrada[i], &lista);
        puts("Imprimiendo lista");
        imprimir_lista_int(lista);
        for(j = 0; (*header) != NULL; j++){
            vector_guardar_int(v, j+1, (int*)&(*header)->dato);
            (*header) = (*header)->sig;
        }

        destruir_lista(&lista);
    }
    vector_iterar_int(v,imprimir_int, stdout);
    printf("\nmemoria usada: %d\n", v->usado);
    printf("memoria pedida: %d\n", v->pedido);
    vector_destruir(&v);
    */
    /*VECTORES BASICO
    vector_t * v;
    int valores[] = {0,1,2,3,4,5,6,7,8,9};
    
    v = crear_vector(20);
    vector_redimensionar(v, 100);
    vector_guardar_int(v, 5, &valores[4]);
    
    vector_redimensionar(v, 150);
    vector_redimensionar(v, 10);
    vector_redimensionar(v, 100);
    vector_redimensionar(v, 60);
    vector_redimensionar(v, 15);
    
    printf("%d\n", obtener_dato(v, 5));
    printf("%d\n", obtener_usado(v));
    printf("%d\n", obtener_pedido(v));

    vector_iterar_int(v,imprimir_int, stdout);
    printf("\nmemoria usada: %d\n", v->usado);
    printf("memoria pedida: %d\n", v->pedido);
    vector_destruir(&v);
    */
    return EXIT_SUCCESS;
}

/*****************************LECTORES.C********************************************************/
int abrir_archivos(params_t * param){
    size_t archivos_abiertos = 0;
    size_t i;
    
    if(param == NULL)
        return EOF;
    switch(param->archivo_salida->formato){
        case FMT_TXT:
            if((param->archivo_salida->stream = fopen(param->archivo_salida->nombre,"at")) != NULL)
                archivos_abiertos++;
            break;
        case FMT_BIN:
            if((param->archivo_salida->stream = fopen(param->archivo_salida->nombre,"ab")) != NULL)
                archivos_abiertos++;
            break;
    }
    if(param->archivo_entrada->nombre == NULL){
        param->archivo_entrada->stream = stdin;
        return archivos_abiertos;
    }
    for(i = 0; i < param->cant_archivos; i++){
        switch(param->archivo_entrada[i].formato){
            case FMT_TXT:
                if((param->archivo_entrada[i].stream = fopen(param->archivo_entrada[i].nombre,"rt")) != NULL)
                    archivos_abiertos++;
                break;
            case FMT_BIN:
                if((param->archivo_entrada[i].stream = fopen(param->archivo_entrada[i].nombre,"rb")) != NULL)
                    archivos_abiertos++;
                break;
        }
    }

    return archivos_abiertos;
}
int cerrar_archivos(params_t * param){
    size_t archivos_cerrados = 0;
    size_t i;
    
    if(param == NULL)
        return EOF;
    if(fclose(param->archivo_salida->stream) != EOF)
        archivos_cerrados++;
    if(param->archivo_entrada->nombre == NULL)
        return archivos_cerrados;
    for(i = 0; i < param->cant_archivos; i++){
        if(fclose(param->archivo_entrada[i].stream) != EOF)
            archivos_cerrados++;
    }
    return archivos_cerrados;
}
/*La destruccion de las listas se realiza afuera de esta función, recibe una lista vacia*/
/*Revisar optimizacion/correccion de funciones de carga*/
status_t cargar_lista_palabras(archivo_t archivo, lista_t * lista){
    if(lista == NULL)
        return ST_ERROR_PTR_NULO;
    switch(archivo.formato){
        case FMT_TXT:
            if(archivo.nombre == NULL)
                return cargar_lista_palabras_stdin(lista);
            return cargar_lista_palabras_txt(archivo.stream, lista);
        case FMT_BIN:
            return cargar_lista_palabras_bin(archivo.stream, lista);
        default:
            return ST_ERROR_FORMATO_ARCHIVO_INVALIDO;
    }
}
status_t cargar_lista_palabras_txt(FILE * stream, lista_t * lista){
    char buffer[MAX_STR], *pch;
    int palabra;
    status_t st;

    while((fgets(buffer, MAX_STR, stream)) != NULL){
        pch = strtok(buffer, DELIMITADOR_COMENTARIO);
        palabra = strtol(buffer, &pch, 10);
        if(!palabra_es_valida(palabra))
            return ST_ERROR_PALABRA_NO_VALIDA;
        if((st = insertar_nodo_final(lista, (void*)palabra)) != ST_OK)
            return st;
    }
    if(ferror(stream))
        return ST_ERROR_LEER_PALABRA;
    return ST_OK;
}
status_t cargar_lista_palabras_bin(FILE * stream, lista_t * lista){
    uchar high_byte, low_byte;
    int palabra, opcode;
    uint operando;
    status_t st;
    while((fread(&high_byte,1,1,stream) == 1)){
        if((fread(&low_byte,1,1,stream) != 1))
            return ST_ERROR_LEER_PALABRA;
        palabra = 0;
        /*Palabra en binario, con ceros rellenados a la izquierda*/
        palabra = ((palabra | high_byte) << BYTE_SHIFT) | low_byte;
        /*Reconstruyo la palabra para que en la memoria quede guardado con el mismo formato que txt*/
        /*Aplico convencion complemento a 2 para pasar de binario a formato textp*/
        opcode = get_opcode_bin(palabra);
        operando = get_operando_bin(palabra);
        palabra = opcode * OPCODE_OPERANDO_MULTIPLIER + (opcode >= 0 ? operando : -operando);
        if((st = insertar_nodo_final(lista, (void*)palabra)) != ST_OK)
            return st;
    }
    if(ferror(stream))
        return ST_ERROR_LEER_PALABRA;
    return ST_OK;
}
status_t cargar_lista_palabras_stdin(lista_t * lista){
    
}
int get_opcode_bin(int palabra){
    return palabra & MASK_MSB ? -((((~palabra) & MASK_OPCODE) >> OPCODE_SHIFT) +1) : palabra >> OPCODE_SHIFT;
}
uint get_operando_bin(int palabra){
    return palabra & MASK_OPERANDO;
}
/******************************SIMPLETRON.C********************************************************/
pfx_lms instrucciones[] = {
    &lms_leer,
    &lms_escribir,
    &lms_cargar,
    &lms_guardar,
    &lms_pcargar,
    &lms_pguardar,
    &lms_sumar,
    &lms_restar,
    &lms_dividir,
    &lms_multiplicar,
    &lms_jmp,
    &lms_jmpneg,
    &lms_jmpzero,
    &lms_jnz,
    &lms_djnz,
    &lms_halt
};
palabra_t opcode_validos[] = {
    OP_LEER,
    OP_ESCRIBIR,
    OP_CARGAR,
    OP_GUARDAR,
    OP_PCARGAR,
    OP_PGUARDAR,
    OP_SUMAR,
    OP_RESTAR,
    OP_DIVIDIR,
    OP_MULTIPLICAR,
    OP_JMP,
    OP_JMPNEG,
    OP_JMPZERO,
    OP_JNZ,
    OP_DJNZ,
    OP_HALT
};
simpletron_t * crear_simpletron(params_t * param){
    simpletron_t * simpletron = NULL;
    if(param == NULL)
        return NULL;
    if((simpletron = (simpletron_t *)calloc(1, sizeof(simpletron_t))) == NULL)
        return NULL;
    if((simpletron->memoria = (vector_t **)calloc(1, sizeof(vector_t*) * param->cant_archivos)) == NULL){
        destruir_simpletron(&simpletron);
        return NULL;
    }
    return simpletron;
}
void destruir_simpletron(simpletron_t ** simpletron){
    if(simpletron && *simpletron){
        if((*simpletron)->memoria){
            free((*simpletron)->memoria);
            (*simpletron)->memoria = NULL;
        }
        free(*simpletron);
        *simpletron = NULL;
    }
}
void imprimir_registros_simpletron(simpletron_t * simpletron, FILE * stream){
    puts("Imprimiendo registros:");
    if(simpletron == NULL){
        puts("NULL");
        return;
    }
    fprintf(stream, "acumulador: %d\n",simpletron->acumulador);
    fprintf(stream, "instruccion: %d\n",simpletron->instruccion);
    fprintf(stream, "opcode: %d\n",simpletron->opcode);
    fprintf(stream, "operando: %d\n",simpletron->operando);
    fprintf(stream, "program_counter: %lu\n",simpletron->program_counter);
}
bool_t palabra_es_valida(palabra_t palabra){
    int operando, opcode;
    
    if (palabra > MAX_PALABRA || palabra < MIN_PALABRA)
        return FALSE;

    operando = palabra % OPCODE_OPERANDO_MULTIPLIER;
    if (operando < OPERANDO_MIN || operando > OPERANDO_MAX)
        return FALSE;

    opcode = palabra / OPCODE_OPERANDO_MULTIPLIER;
    if (opcode < OPCODE_FIELD_MIN || opcode > OPCODE_FIELD_MAX)
        return FALSE;

    return TRUE;
}
status_t ejecutar_codigo(simpletron_t * simpletron, params_t * param){
    size_t i,j;
    int memoria_usada, memoria_pedida, dato;
    status_t status;
    pfx_lms operacion;
    puts(MSJ_COMIENZO_EJECUCION);
    for(i = 0; i < param->cant_archivos; i++){
        puts("Comienza con los archivos");
        memoria_usada = obtener_usado(simpletron->memoria[i]);
        memoria_pedida = obtener_pedido(simpletron->memoria[i]);
        printf("\nMemoria usada: %d\n", memoria_usada);
        printf("Memoria pedida: %d\n", memoria_pedida);
        for(simpletron->program_counter = 0, simpletron->acumulador = 0; simpletron->program_counter < memoria_pedida; simpletron->program_counter++){
            /*Obtengo opcode y operandos*/
            dato = obtener_dato(simpletron->memoria[i], simpletron->program_counter + 1);
            simpletron->opcode = dato / OPCODE_OPERANDO_MULTIPLIER;
            simpletron->operando = dato % OPCODE_OPERANDO_MULTIPLIER;
            simpletron->instruccion = simpletron->opcode * OPCODE_OPERANDO_MULTIPLIER + simpletron->operando;
            /*Valida que operando pueda ser accdedido*/
            if(simpletron->operando > memoria_pedida - 1 || simpletron->operando < 0){
                fprintf(stdout,"%s\n",MSJ_ST_ERROR_SEGMENTATION_FAULT);
                fprintf(stdout,"%s\n",MSJ_FIN_EJECUCION);
                return ST_ERROR_SEGMENTATION_FAULT;
            }
            /*Valido que los opcode sean validos*/
            for(j = 0; simpletron->opcode != opcode_validos[j]; j++){
                if((j+1) == sizeof(opcode_validos)/sizeof(int)){
                    fprintf(stdout,"%s\n",MSJ_ST_ERROR_OPCODE_INVALIDO);
                    fprintf(stdout,"%s\n",MSJ_FIN_EJECUCION);
                    return ST_ERROR_OPCODE_INVALIDO;
                }
            }
            /*Ejecuta opcde*/
            operacion = instrucciones[j];
            status = (*operacion)(simpletron, simpletron->memoria[i]);
            if (status != ST_OK){
                if(status != ST_HALT){
                    fprintf(stdout,"%s\n", MSJ_FIN_EJECUCION);
                    return status;
                }
                break;
            }
        }
        puts("Fin de ejecución del archivo");
    }
    puts("Fin de ejecucion de todos los archivos");
    puts(MSJ_FIN_EJECUCION);

    return ST_OK;
}

status_t lms_leer(simpletron_t * simpletron, vector_t * memoria){
    char buffer[MAX_STR];
    long temp;
    char * pch;
    
    fprintf(stdout,"%s ",MSJ_INGRESO_PALABRA);
    if(fgets(buffer, MAX_STR, stdin) == NULL){
        fprintf(stdout, "%s\n", MSJ_ST_ERROR_LEER_PALABRA);
        return ST_ERROR_LEER_PALABRA;
    }
    if((temp = strtol(buffer, &pch, 10)) > MAX_PALABRA || temp < MIN_PALABRA || (*pch != '\n' && *pch != '\0' && *pch != EOF)){
        fprintf(stdout, "%s\n", MSJ_ST_ERROR_PALABRA_NO_VALIDA);
        return ST_ERROR_PALABRA_NO_VALIDA;
    }
    
    vector_guardar_int(memoria, simpletron->operando + 1, (int*)&temp);
    
    /*
    ((int*)memoria->datos)[simpletron->operando] = temp;
    */
    return ST_OK;
}
status_t lms_escribir(simpletron_t * simpletron, vector_t * memoria){
    fprintf(stdout,"%s %i: %i\n",MSJ_IMPRIMIR_PALABRA,simpletron->operando,obtener_dato(memoria, simpletron->operando + 1));
    /*
    fprintf(stdout,"%s %i: %i\n",MSJ_IMPRIMIR_PALABRA,simpletron->operando,((int*)memoria->datos)[simpletron->operando]);
    */
    return ST_OK;
}   
status_t lms_cargar(simpletron_t * simpletron, vector_t * memoria){
    simpletron->acumulador = obtener_dato(memoria, simpletron->operando + 1);
    return ST_OK;
}
status_t lms_guardar(simpletron_t * simpletron, vector_t * memoria){
    if(simpletron->acumulador < MIN_PALABRA || simpletron->acumulador > MAX_PALABRA){
        fprintf(stdout,"%s\n", MSJ_ST_ERROR_PALABRA_NO_VALIDA);
        return ST_ERROR_PALABRA_NO_VALIDA;
    }
    vector_guardar_int(memoria, simpletron->operando + 1, (int*)&simpletron->acumulador);
    /*
    ((int*)memoria->datos)[simpletron->operando] = simpletron->acumulador;
    */
    return ST_OK;
}
status_t lms_pcargar(simpletron_t * simpletron, vector_t * memoria){
    if(((int*)memoria->datos)[simpletron->operando] > memoria->pedido + 1 || ((int*)memoria->datos)[simpletron->operando] < 0){
        fprintf(stdout,"%s\n",MSJ_ST_ERROR_SEGMENTATION_FAULT);
        return ST_ERROR_SEGMENTATION_FAULT;
    }
    simpletron->acumulador = obtener_dato(memoria, obtener_dato(memoria, simpletron->operando + 1));
    /*
    simpletron->acumulador = ((int*)memoria->datos)[((int*)memoria->datos)[simpletron->operando]];
    */
    return ST_OK;
}
status_t lms_pguardar(simpletron_t * simpletron, vector_t * memoria){
    if(((int*)memoria->datos)[simpletron->operando] > memoria->pedido + 1 || ((int*)memoria->datos)[simpletron->operando] < 0){
        fprintf(stdout,"%s\n",MSJ_ST_ERROR_SEGMENTATION_FAULT);
        return ST_ERROR_SEGMENTATION_FAULT;
    }
    vector_guardar_int(memoria, obtener_dato(memoria, simpletron->operando + 1), (int*)&simpletron->acumulador);
    /*
    ((int*)memoria->datos)[((int*)memoria->datos)[simpletron->operando]] = simpletron->acumulador;
    */
    return ST_OK;
}
status_t lms_sumar(simpletron_t * simpletron, vector_t * memoria){
    palabra_t resultado;
    if((resultado = simpletron->acumulador + obtener_dato(memoria, simpletron->operando + 1)) > MAX_PALABRA || resultado < MIN_PALABRA){
        fprintf(stdout,MSJ_ST_ERROR_OVERFLOW);
        return ST_ERROR_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return ST_OK;
}
status_t lms_restar(simpletron_t * simpletron, vector_t * memoria){
    simpletron->acumulador -= obtener_dato(memoria, simpletron->operando + 1);
    return ST_OK;
}
status_t lms_dividir(simpletron_t * simpletron, vector_t * memoria){
    simpletron->acumulador /= obtener_dato(memoria, simpletron->operando + 1);
    return ST_OK;
}
status_t lms_multiplicar(simpletron_t * simpletron, vector_t * memoria){
    simpletron->acumulador *= obtener_dato(memoria, simpletron->operando + 1);
    return ST_OK;
}
status_t lms_jmp(simpletron_t * simpletron, vector_t * memoria){
    simpletron->program_counter = simpletron->operando -1;
    return ST_OK;
}
status_t lms_jmpneg(simpletron_t * simpletron, vector_t * memoria){
    if(simpletron->acumulador < 0)
        simpletron->program_counter = simpletron->operando -1;
    return ST_OK;
}
status_t lms_jmpzero(simpletron_t * simpletron, vector_t * memoria){
    if(!simpletron->acumulador)
        simpletron->program_counter = simpletron->operando -1;
    return ST_OK;
}
status_t lms_jnz(simpletron_t * simpletron, vector_t * memoria){
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando -1;
    return ST_OK;
}
status_t lms_djnz(simpletron_t * simpletron, vector_t * memoria){
    simpletron->acumulador--;
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando -1;
    return ST_OK;
}
status_t lms_halt(simpletron_t * simpletron, vector_t * memoria){
    return ST_HALT;
}
/*****************************ERRORES.C********************************************************/
void imprimir_estado(status_t status){
    switch (status) {
        case ST_OK:
            fprintf(stdout, "%s\n", MSJ_ST_OK);
            break;
        case ST_ERROR_PTR_NULO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_PTR_NULO, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_MEMORIA:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_MEMORIA, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_ARCHIVO_NO_ENCONTRADO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_ARCHIVO_NO_ENCONTRADO, MSJ_OPCION_AYUDA);
            break;
            /*Mensajes de error de validaciones.c*/
        case ST_AYUDA:
            imprimir_ayuda();
            break;
        case ST_ERROR_MEMORIA_INGRESADA_INVALIDA:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_MEMORIA_INGRESADA_INVALIDA, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_FORMATO_ARCHIVO_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_FORMATO_ARCHIVO_INVALIDO, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_STDIN_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_STDIN_INVALIDO, MSJ_OPCION_AYUDA);
            break;
        /*Ejecutar codigo*/
        case ST_HALT:
            fprintf(stderr, "%s. %s\n", MSJ_ST_HALT, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_SEGMENTATION_FAULT:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_SEGMENTATION_FAULT, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_OPCODE_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_OPCODE_INVALIDO, MSJ_OPCION_AYUDA);
            break;
        case ST_ERROR_OVERFLOW:
            fprintf(stderr, "%s. %s\n", MSJ_ST_ERROR_OVERFLOW, MSJ_OPCION_AYUDA);
            break;
        default:
            fprintf(stderr, "%s\n", MSJ_OPCION_AYUDA);
    }
}
void imprimir_ayuda(void){
    fprintf(stdout, "%s", MSJ_ST_AYUDA);
}
/*****************************ARGUMENTOS.C********************************************************/
status_t validacion_cla(int argc, char** argv, params_t *param) {
    size_t i = 1, j, cant_archivos;
    bool_t stdin_flag = FALSE;
    long temp;
    archivo_t * aux = NULL;
    char * pc = NULL;
    /*---------------------------------VALIDACIONES---------------------------------*/
    /*Valido que los nombres no apunten a NULL para usar funciones get()*/
    if (argv == NULL || param == NULL)
        return ST_ERROR_PTR_NULO;
    for(j = 1; j < argc; j++){
        if( argv[j] == NULL)
            return ST_ERROR_PTR_NULO;
    }
    /*-----------------------------DEFAULT-----------------------------*/
    param->cant_memoria = DEFAULT_MEMORIA;
    param->cant_archivos = DEFAULT_CANT_ARCHIVOS;
    if ((param->archivo_salida = (archivo_t*) malloc(sizeof (archivo_t))) == NULL)
        return ST_ERROR_MEMORIA;
    param->archivo_salida->formato = FMT_TXT;
    param->archivo_salida->nombre = DEFAULT_ARCHIVO_SALIDA;
    param->archivo_salida->stream = NULL;
    if ((param->archivo_entrada = (archivo_t*) malloc(sizeof (archivo_t))) == NULL){
        destruir_params(param);
        return ST_ERROR_MEMORIA;
    }
    param->archivo_entrada->formato = FMT_TXT;
    param->archivo_entrada->nombre = DEFAULT_ARCHIVO_ENTRADA;
    param->archivo_entrada->stream = NULL;

    /*Comienzo a recorrer argv[] hasta llegar a argv[argc]*/
    if(i == argc)
        return ST_OK;
    /*---------------------------------AYUDA---------------------------------*/
    /*Forma de ejecutar: ./simpletron -h o --help */
    if (argc == 2 && !strcmp(argv[i], FLAG_CLA_AYUDA_CORTO) || !strcmp(argv[i], FLAG_CLA_AYUDA_LARGO)){
        destruir_params(param);
        return ST_AYUDA;
    }
    /*---------------------------------MEMORIA---------------------------------*/
    if (!strcmp(argv[i], FLAG_CLA_MEMORIA_CORTO) || !strcmp(argv[i], FLAG_CLA_MEMORIA_LARGO)) {
        if(++i == argc){
            destruir_params(param);
            return ST_ERROR_MEMORIA_INGRESADA_INVALIDA;
        }
        temp = strtol(argv[i], &pc, 10);
        /*En el caso de que el usuario ingrese caracter alfabetico o pida memoria con decimales*/
        if (temp <= 0 || pc == NULL || (*pc != '\n' && *pc != '\0')){
            destruir_params(param);
            return ST_ERROR_MEMORIA_INGRESADA_INVALIDA;
        }
        param->cant_memoria = temp;
        
        if(++i == argc)
            return ST_OK;
    }

    /*---------------------------------FORMATO SALIDA---------------------------------*/
    /*Indica el formato de la salida. Si FMT es txt , el formato debe ser texto. Si*/
    /*FMT es bin, el formato debe ser binario. Por omisión, el formato es texto.*/
    /*Busco el flag de formato*/
    if (!strcmp(argv[i], FLAG_CLA_FORMATO_CORTO) || !strcmp(argv[i], FLAG_CLA_FORMATO_LARGO)) {
        if(++i == argc){
            destruir_params(param);
            return ST_ERROR_FORMATO_ARCHIVO_INVALIDO;
        }
        if(!strcmp(argv[i], FLAG_CLA_FORMATO_OPCION_BIN)){
            param->archivo_salida->formato = FMT_BIN;
        }
        else if(!strcmp(argv[i], FLAG_CLA_FORMATO_OPCION_TXT)){
            param->archivo_salida->formato = FMT_TXT;
        }
        else{
            destruir_params(param);
            return ST_ERROR_FORMATO_ARCHIVO_INVALIDO;
        }
        if(++i == argc)
            return ST_OK;
    }

    /*---------------------------------ARCHIVOS---------------------------------*/
    for (cant_archivos = 0; i < argc; i++){
        if ((aux = (archivo_t*) realloc(param->archivo_entrada, sizeof (archivo_t)*(++cant_archivos))) == NULL){
            destruir_params(param);
            return ST_ERROR_MEMORIA;
        }
        param->archivo_entrada = aux;
        param->archivo_entrada[cant_archivos - 1].nombre = get_name_lmsfile(argv[i]);
        param->archivo_entrada[cant_archivos - 1].formato = get_fmt_lmsfile(argv[i]);
        
        if(!stdin_flag && param->archivo_entrada[cant_archivos-1].nombre == NULL)
            stdin_flag = TRUE;
        /*
        if(!stdin_flag){
            if((param->archivo_entrada[cant_archivos - 1].stream = fopen(param->archivo_entrada[cant_archivos-1].nombre, "r")) == NULL){
                destruir_params(param);
                return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
            }
            fclose(pf);
        }
        */
    }

    if (stdin_flag && (cant_archivos != 1 || param->archivo_entrada->formato == FMT_BIN)){
        destruir_params(param);
        return ST_ERROR_STDIN_INVALIDO;
    }
    param->cant_archivos = cant_archivos;
    
    return ST_OK;
}
char * get_name_lmsfile(char* name){
    if(!strncmp(name,FMT_BIN_DELIMITER,2) || !strncmp(name,FMT_TXT_DELIMITER,2))
        return name + 2;
    if(!strcmp(name,FLAG_CLA_STDIN_CORTO))
        return NULL;
    return name;
}
formato_t get_fmt_lmsfile(char* name){
    return strncmp(name,FMT_BIN_DELIMITER,2) ? FMT_TXT : FMT_BIN;
}
void destruir_params(params_t * param){
    if(param == NULL)
        return;
    free(param->archivo_entrada);
    free(param->archivo_salida);
    param->archivo_entrada = NULL;
    param->archivo_salida = NULL;
}
/*****************************LISTAS.C********************************************************/

status_t crear_lista(lista_t * lista){
    if(!lista)
        return ST_ERROR_PTR_NULO;
    *lista = NULL;
    return ST_OK;
}
nodo_t * crear_nodo(void * dato){
    nodo_t * nodo = NULL;
    nodo = (nodo_t *)calloc(1,sizeof(nodo_t));
    if(!nodo)
        return NULL;
    nodo->dato = dato;
    nodo->sig = NULL;
    return nodo;
}
bool_t lista_esta_vacia(lista_t lista){
    return !lista;
}
status_t insertar_nodo_final(lista_t * lista, void * dato){
    if(!lista)
        return ST_ERROR_PTR_NULO;
    if(lista_esta_vacia(*lista)){
        *lista = crear_nodo(dato);
        if(!(*lista))
            return ST_ERROR_MEMORIA;
        return ST_OK;
    }
    return insertar_nodo_final(&(*lista)->sig, dato);
}
status_t insertar_nodo_ppio(lista_t * lista, void * dato){
    nodo_t * aux = NULL;
    
    if(!lista)
        return ST_ERROR_PTR_NULO;
    aux = crear_nodo(dato);
    if(!aux)
        return ST_ERROR_MEMORIA;
    aux->sig = *lista;
    *lista = aux;
    return ST_OK;
}
void destruir_lista(lista_t * lista){
    nodo_t * aux = NULL;

    if(!lista){
        return;
    }
    while(*lista){
        aux = (*lista)->sig;
        free(*lista);
        *lista = aux;
    }
}
void imprimir_lista_int(lista_t lista){
    while(lista){
        printf("%d ", (lista->dato));
        lista = lista->sig;
    }
    putchar('\n');
}
bool_t guardar_lista_en_vector(lista_t lista, vector_t ** vector){
    size_t i;

    if(vector == NULL)
        return FALSE;
    if((*vector = crear_vector(1)) == NULL)
        return FALSE;
    
    for(i = 1; lista != NULL; i++){
        
        if(!vector_redimensionar(*vector, i)){
            vector_destruir(vector);
            return FALSE;
        }
        if(!vector_guardar_int(*vector,i,(int*)&lista->dato)){
            vector_destruir(vector);
            return FALSE;
        }
        lista = lista->sig;
    }
    return TRUE;
}
/*****************************MEMORIA.C********************************************************/
/*Crea vector de 1 dimension*/
vector_t * crear_vector(size_t n){
    vector_t * v;
    
    if(n <= 0)
        return NULL;
    v = (vector_t *)calloc(1, sizeof(vector_t));
    if(!v)
        return NULL;
    v->datos = (void*)calloc(1,n * sizeof(void*));
    if(!v->datos){
        free(v);
        return NULL;
    }
    v->usado = 0;
    v->pedido = n;
    return v;
}
/*Si n es mayor a la longitud del vector, pide mas memoria. Si es menor, libera la memoria de los ultimos elementos sobrantes
*  Rellena la memoria solicitada que no está en uso con ceros.*/
bool_t vector_redimensionar(vector_t *v, size_t n){
    void * aux;
    size_t i;
    
    if(!v || n <= 0)
        return FALSE;
    
    if(n == v->pedido)
        return TRUE;
    
    aux = (void*)calloc(1, n * sizeof(void*));
    if(!aux)
        return FALSE;
    v->datos = memcpy(aux, v->datos, n > v->usado ? (v->usado) * sizeof(void*) : (n) * sizeof(void*));
    v->pedido = n;
    if(v->usado > v->pedido)
        v->usado = v->pedido;
    return TRUE;
}
/*Destruye vectores de 1 dimension*/
void vector_destruir(vector_t ** v){
    if(v && *v){
        if((*v)->datos){
            free((*v)->datos);
            (*v)->datos = NULL;
        }
        free(*v);
        *v = NULL;
    }
}
/*Guarda lo apuntado por dato en la posicion i-1 del TDA vector apuntado por v*/
/*Esta funcion trabaja con datos y vectores de enteros*/
bool_t vector_guardar_int(vector_t * v, size_t i, int * dato){
    if(!v || i > v->pedido || i < 1)
        return FALSE;
    ((int*)v->datos)[i-1]= *dato;
    if(v->usado < i)
        v->usado = i;
    /*
    printf("GUARDADO 2: %d\n",((int*)(v)->datos)[0]);
    printf("GUARDADO 2: %d\n",((int*)(v)->datos)[1]);
    printf("GUARDADO 2: %d\n",((int*)(v)->datos)[2]);
    */
    return TRUE;
}
/*No se puede iterar genericamente elementos que apunten a void*
 Para acceder a su contenido, el compilador necesita saber de qué tipo es.
 Por lo que se necesitan varias funciones de iteracion dependiendo del tipo.
 Esta funcion itera sobre un TDA Vector de tipo int*/
void vector_iterar_int(vector_t * v, void (*func)(void *,void *), void * arg){
    size_t i;
    
    if(v && func){
        for(i = 0; i < v->pedido; i++){      
            (*func)(&(((int*)v->datos)[i]), arg);
        }
    }
}
/*Imprime por stream (archivo ya abierto) el contenido de las direcciones apuntados por vector_int*
* Sólo trabajo con enteros.*/
void imprimir_int(void * dato, void* stream){
    fprintf(stream, "%i ", *(int*)dato);
}
/*Se DEBE validar el puntero antes de usar la funcion*/
int obtener_dato(vector_t * v, size_t i){
    return ((int*)(v->datos))[i - 1];
}
int obtener_usado(vector_t * v){
    return v == NULL ? EOF : v->usado;
}
int obtener_pedido(vector_t *v){
    return v == NULL ? EOF : v->pedido;
}
/******************************************************************************************************/
