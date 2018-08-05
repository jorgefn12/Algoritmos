#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Aclarar que opcode_t se utiliza solamente cuando se esta seguro que se guarda codigos de ejecucion y no informarción
 *Es decir, solamente en la fase de ejecutar_codigo*/
/****************************COMUN.H********************************************************/
#define MAX_STR 200
#define NUMERO_FIN_CARGA -99999999
#define MIN_PALABRA_TXT -640511  /*Maximo alcanzable en formato texto que puede abarcar el formato binario*/
#define MAX_PALABRA_TXT 630511
#define MIN_PALABRA_BIN 0
#define MAX_PALABRA_BIN 65535 /*1111111111111111*/
#define MIN_PALABRA_BIN_SIGNED -32768
#define MAX_PALABRA_BIN_SIGNED 32767
#define OPCODE_OPERANDO_MULTIPLIER 10000
#define OPERANDO_MIN 0 /*xxxxxxx000000000*/
#define OPERANDO_MAX 511 /*xxxxxxx111111111*/
#define OPCODE_MIN 0 /*0000000xxxxxxxxx*/
#define OPCODE_MAX 127 /*1111111xxxxxxxxx*/
#define OPCODE_FIELD_MIN -64 /*1000000xxxxxxxxx*/
#define OPCODE_FIELD_MAX 63 /*0111111xxxxxxxxx*/
/****************************TIPOS.H********************************************************/
typedef enum{
    FALSE = 0,
    TRUE
}bool_t;
typedef unsigned char uchar;
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
    ST_MEMORIA_INSUFICIENTE,
    /*status de ejecutar_codigo*/
    ST_ERROR_VECTOR
}status_t;
typedef enum{
    VCT_RV_SUCCESS = 0,
    VCT_RV_ILLEGAL = 1,
    VCT_RV_NOSPACE = 2,
    VCT_RV_ERROR = 3,
    VCT_RV_NOTIMPLEMENTED = 4,
    VCT_RV_MISSING_ARGS = 5,
    VCT_RV_INVALID_ARGS = 6
} vct_retval_t;
typedef enum{
    RV_SUCCESS = 0,
    RV_ILLEGAL = 1,
    RV_NOSPACE = 2,
    RV_ERROR = 3,
    RV_NOTIMPLEMENTED = 4,
    RV_MISSING_ARGS = 5,
    RV_INVALID_ARGS = 6
} retval_t;
typedef enum{
    SMP_RV_SUCCESS = 0,
    SMP_RV_SEGMENTATION_FAULT = 1,
    SMP_RV_PALABRA_NO_LEIDA = 2,
    SMP_RV_ERROR = 3,
    SMP_RV_PALABRA_FORMATO_INVALIDO = 4, /*La palabra en formato txt es invalida*/
    SMP_RV_PALABRA_FUERA_DE_RANGO = 5,
    SMP_RV_PALABRA_NO_ES_ENTERO = 6,
    SMP_RV_OVERFLOW = 7,
    SMP_RV_OPCODE_INVALIDO = 8,
    SMP_RV_ERROR_MEMORIA = 9,
    SMP_RV_ILLEGAL = 10,
    SMP_RV_HALT = 11
} simply_retval_t;
typedef enum{
    FMT_TXT,
    FMT_BIN        
}formato_t;
typedef struct archivo{
    char * nombre;
    formato_t formato;
    FILE * stream;
}archivo_t;
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
/*****************************VECTORES.H********************************************************/
typedef struct vector{
    size_t usado, pedido;
    int * datos;
} vector_t;
void VECTOR_destruir(vector_t ** vector);
vct_retval_t VECTOR_crear(vector_t ** vector, size_t n);
vct_retval_t VECTOR_redimensionar(vector_t * vector, size_t n);
vct_retval_t VECTOR_guardar_entero(vector_t * vector, size_t posicion, int dato);
int VECTOR_obtener_dato(vector_t * v, size_t i);
int VECTOR_obtener_memoria_usada(vector_t * v);
int VECTOR_obtener_memoria_pedida(vector_t * v);
/********************************SIMPLETRON.H****************************************************/
#define MSJ_BIENVENIDO_SIMPLETRON "*** ¡Bienvenido a la Simpletron!         ***\n*** Por favor, ingrese su programa una   ***\n*** instrucción (o dato) a la vez. Yo    ***\n*** escribiré la ubicacíón y un signo de ***\n*** pregunta (?). Luego usted ingrese la ***\n*** palabra para esa ubicación. Ingrese  ***\n*** -99999999 para finalizar:            ***"
#define MSJ_COMIENZO_EJECUCION "******** INICIO DE EJECUCION DEL SIMPLETRON *******"
#define MSJ_FIN_EJECUCION "********* FIN DE EJECUCION DEL SIMPLETRON *********"
#define MSJ_INGRESO_PALABRA "Ingrese una palabra: "
#define MSJ_IMPRIMIR_PALABRA "Contenido de la posición"

typedef int palabra_t;
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
typedef struct simpletron{
    palabra_t instruccion, acumulador, operando;
    opcode_t opcode;
    size_t program_counter;
    vector_t * memoria;
}simpletron_t;
typedef simply_retval_t (*pfx_lms)(simpletron_t *);
bool_t palabra_es_valida(palabra_t palabra);
simpletron_t * SIMPLETRON_crear(void);
void SIMPLETRON_destruir(simpletron_t ** simply);
simply_retval_t SIMPLETRON_ejecutar(simpletron_t * simpletron);
simply_retval_t lms_leer(simpletron_t * simpletron);
simply_retval_t lms_escribir(simpletron_t * simpletron);
simply_retval_t lms_cargar(simpletron_t * simpletron);
/*Validar el acumulador con los diferentes flags en lugar de validar antes de guardar*/
simply_retval_t lms_guardar(simpletron_t * simpletron);
simply_retval_t lms_pcargar(simpletron_t * simpletron);
simply_retval_t lms_pguardar(simpletron_t * simpletron);
simply_retval_t lms_sumar(simpletron_t * simpletron);
simply_retval_t lms_restar(simpletron_t * simpletron);
simply_retval_t lms_dividir(simpletron_t * simpletron);
simply_retval_t lms_multiplicar(simpletron_t * simpletron);
simply_retval_t lms_jmp(simpletron_t * simpletron);
simply_retval_t lms_jmpneg(simpletron_t * simpletron);
simply_retval_t lms_jmpzero(simpletron_t * simpletron);
simply_retval_t lms_jnz(simpletron_t * simpletron);
simply_retval_t lms_djnz(simpletron_t * simpletron);
simply_retval_t lms_halt(simpletron_t * simpletron);
/*******************************LECTORES.H*****************************************************/
#define MASK_PALABRA 0xFFFF
#define MASK_OPERANDO 0x01FF
#define MASK_OPCODE 0xFE00
#define BYTE_SHIFT 8
#define OPCODE_SHIFT 9
#define MASK_MSB 0x8000
#define MASK_LSB 0x0001

#define DELIMITADOR_COMENTARIO ";"
int abrir_archivos(params_t * param);
int cerrar_archivos(params_t * param);
status_t leer_archivo(vector_t ** memoria, archivo_t * archivo, size_t cantidad);
status_t leer_archivo_txt(vector_t ** memoria, FILE * stream, size_t cantidad);
status_t leer_archivo_bin(vector_t ** memoria, FILE * stream, size_t cantidad);
status_t leer_archivo_stdin(vector_t ** memoria, size_t cantidad);
/*Acomodar en la biblioteca correcta*/
/*******************************LISTAS.H*****************************************************/
typedef struct nodo {
  struct nodo * siguiente;
  void * dato;
} nodo_t, * lista_t;

bool_t LISTA_esta_vacia(lista_t);
retval_t LISTA_crear(lista_t *);
retval_t LISTA_crear_nodo(nodo_t ** , void *);
retval_t LISTA_destruir_nodo(nodo_t **, retval_t (*destructor_dato)(void *));
retval_t LISTA_destruir(lista_t *, retval_t (*destructor_dato)(void *));
retval_t LISTA_insertar_al_ppio(lista_t *, void *);
retval_t LISTA_insertar_al_final(lista_t *, void *);
retval_t LISTA_insertar_decreciente(lista_t *, void *, int (*cmp)(void *, void *));

void * LISTA_buscar(nodo_t *, void *, int (*cmp)(void *, void *));
retval_t LISTA_imprimir(lista_t, FILE *, retval_t (*impresor)(void *, FILE *));
retval_t LISTA_recorrer(lista_t, retval_t (*pf)(void *, void *), void *);
retval_t LISTA_aplicar(lista_t, retval_t (*pf)(void*));
retval_t imprimir_entero(void * dato, void * stream){
    if(dato == NULL || stream == NULL)
        return RV_ILLEGAL;
    fprintf((FILE*)stream, "%d ", *(int*)dato);
    return RV_SUCCESS;
}
retval_t square_entero(void * dato){
    if(dato == NULL)
        return RV_ILLEGAL;
    *(int*)dato = *(int*)dato * *(int*)dato;
    return RV_SUCCESS;
}
/*****************************DUMP.H**************************************************/
#define DUMP_MSJ_REGISTROS "\nREGISTROS"
#define DUMP_MSJ_ACUMULADOR "acumulador"
#define DUMP_MSJ_PROGRAM_COUNTER "program counter"
#define DUMP_MSJ_INSTRUCCION "instruccion"
#define DUMP_MSJ_OPCODE "opcode"
#define DUMP_MSJ_OPERANDO "operando"
#define DUMP_MSJ_MEMORIA "\nMEMORIA"
void imprimir_dump(simpletron_t * simpletron, archivo_t * archivo_salida);
void imprimir_dump_txt(simpletron_t * simpletron, FILE * stream);
void imprimir_dump_bin(simpletron_t * simpletron, FILE * stream);
/************************************************************************************************/
void debug(void){
    static size_t i;
    printf("Funciona %lu\n", i++);
}
palabra_t formar_palabra_bin(uchar high_byte, uchar low_byte);
palabra_t get_opcode(palabra_t palabra, formato_t formato);
palabra_t get_operando(palabra_t palabra, formato_t formato);
palabra_t aplicar_signo(palabra_t palabra, palabra_t BIT_FIELD, palabra_t MSB);
palabra_t quitar_signo_palabra(palabra_t palabra, palabra_t BIT_FIELD);
void imprimir_palabra_txt(palabra_t palabra, formato_t formato);
palabra_t cambiar_fmt_palabra(palabra_t palabra, formato_t destino);

int main(int argc, char** argv) {
    params_t argumentos;
    size_t i;
    simpletron_t * simply;
    lista_t lista = NULL;
    
    validacion_cla(argc,argv, &argumentos);
    abrir_archivos(&argumentos);
    for(i = 0; i < argumentos.cant_archivos; i++){
        simply = SIMPLETRON_crear();
        leer_archivo(&simply->memoria, &argumentos.archivo_entrada[i], argumentos.cant_memoria);
        LISTA_insertar_al_final(&lista,simply);
    }
    LISTA_aplicar(lista, (retval_t (*)(void*))SIMPLETRON_ejecutar);
    LISTA_recorrer(lista, (retval_t (*)(void*,void*))imprimir_dump, argumentos.archivo_salida);
    LISTA_destruir(&lista, (retval_t (*)(void*))SIMPLETRON_destruir);
    cerrar_archivos(&argumentos);
    destruir_params(&argumentos);

    /*MAIN PARA TESTEAR PRIMITIVAS DE LISTAS
    int datos[] = {0,1,2,3,4,5,6,7,8,9};
    lista_t lista = NULL;
    size_t i;
    
    for(i = 0; i < 10; i++){
        LISTA_insertar_al_final(&lista,&datos[i]);
    }
    LISTA_aplicar(lista, square_entero);
    LISTA_recorrer(lista, imprimir_entero, stdout);
    */
    /*MAIN PARA TESTEAR ARGUMENTOS, CARGA DE MEMORIA Y EJECUCION
    
    status_t st;
    params_t argumentos;
    size_t i,j;
    simpletron_t * simply;
    lista_t lista = NULL;
    
    st = validacion_cla(argc, argv, &argumentos);
    if(st == ST_OK){
        for(i=0;i<argumentos.cant_archivos;i++){
            printf("Archivo entrada %lu: %s [%d]\n", i+1, argumentos.archivo_entrada[i].nombre ? argumentos.archivo_entrada[i].nombre : "stdin(null)", argumentos.archivo_entrada[i].formato);
        }
        printf("Archivo salida: %s [%d]\n",argumentos.archivo_salida->nombre, argumentos.archivo_salida->formato);
        printf("Cantidad memoria: %ld\n", argumentos.cant_memoria);
        printf("Cantidad archivos entrada: %ld\n", argumentos.cant_archivos);
    }
    printf("Cantidad archivos abiertos: %lu\n", abrir_archivos(&argumentos));
    
    
    for(i = 0; i < argumentos.cant_archivos; i++){
        simply = SIMPLETRON_crear();
        leer_archivo(&simply->memoria,&argumentos.archivo_entrada[i], argumentos.cant_memoria);

        printf("Usado: %d\n", VECTOR_obtener_memoria_usada(simply->memoria));
        printf("Pedido: %d\n", VECTOR_obtener_memoria_pedida(simply->memoria));
        printf("VECTOR: ");
        for(j = 0; j < simply->memoria->pedido; j++){
            printf("%d ", VECTOR_obtener_dato(simply->memoria, j + 1));
        }
        putchar('\n');
        LISTA_insertar_al_final(&lista,simply);
    }
    LISTA_aplicar(lista, (retval_t (*)(void*))SIMPLETRON_ejecutar);
    
    printf("ACC: %d\n", simply->acumulador);
    printf("OPCODE: %d\n", simply->opcode);
    printf("OPERANDO: %d\n", simply->operando);
    printf("INSTRUCCION: %d\n", simply->instruccion);
    printf("PROGCOUNTER: %d\n", simply->program_counter);
    printf("VECTOR: ");
    for(i = 0; i < simply->memoria->pedido; i++){
        printf("%d ", VECTOR_obtener_dato(simply->memoria, i + 1));
    }
    
    LISTA_recorrer(lista, (retval_t (*)(void*,void*))imprimir_dump, argumentos.archivo_salida);
    */
    /*MAIN PARA TESTEAR VECTORES
    vector_t * pvector;
    size_t i;
    
    VECTOR_crear(&pvector, 1);
    VECTOR_redimensionar(pvector, 10);
    VECTOR_guardar_entero(pvector, 5, 7);
    VECTOR_redimensionar(pvector, 40); 
    for(i = 0; i < pvector->pedido; i++){
        printf("%d ", pvector->datos[i]);
    }
    */
    /* MAIN PARA TESTEAR OPERACIONES CON PALABRAS BINARIAS
    uchar number = 0xFF;
    int palabra, operando, opcode;
    uchar high_byte = number, low_byte = number;

    palabra = formar_palabra_bin(high_byte, low_byte);
    opcode = get_opcode(palabra, FMT_BIN);
    operando = get_operando(palabra, FMT_BIN);
    printf("opcode TXT: %d\n",opcode);
    printf("operando TXT: %d\n",operando);
    printf("palabra TXT: %d\n",palabra);
    
    imprimir_palabra_txt(palabra, FMT_BIN);
    palabra = cambiar_fmt_palabra(palabra, FMT_BIN);
    imprimir_palabra_txt(palabra, FMT_TXT);
    palabra = cambiar_fmt_palabra(palabra, FMT_TXT);
    imprimir_palabra_txt(palabra, FMT_BIN);
    palabra = cambiar_fmt_palabra(palabra, FMT_BIN);
    imprimir_palabra_txt(palabra, FMT_TXT);
    */
    return EXIT_SUCCESS;
}

/*OPCODE SIGNADO usando complemento a 2, ELIMINAR FUNCION*/
void imprimir_palabra_txt(palabra_t palabra, formato_t formato){
    palabra_t opcode,operando;
    
    switch(formato){
        case FMT_TXT:
            printf("%d\n", palabra);
            break;
        case FMT_BIN:
            opcode = aplicar_signo(get_opcode(palabra, FMT_BIN), MASK_OPCODE >> OPCODE_SHIFT, MASK_MSB >> OPCODE_SHIFT);
            operando = get_operando(palabra,FMT_BIN);
            palabra = opcode * OPCODE_OPERANDO_MULTIPLIER + (opcode >= 0 ? operando : -operando);
            printf("%d\n", palabra);
            break;
    }
}   /*TESTEADO*/
palabra_t formar_palabra_bin(uchar high_byte, uchar low_byte){
    return (( (int)0 | high_byte) << BYTE_SHIFT) | low_byte;
}   /*TESTEADO*/
/*Me dan la representacion binaria de los op desplazados a la derecha. Por esto, siempre los toma positivos
 Si quisiera representarlos con signo, necesito hacer complemento a 2 manualmente*/
palabra_t get_opcode(palabra_t palabra, formato_t formato){
    /*Para código más legible, se escribe != FMT_TXT. Siendo FMT_TXT = 0*/
    /*El opcode que se obtiene con el modo texto sólo se utiliza para impresion, no para guardar en memoria
     ya que si llegara a ser negativo, incluiría 1s en las posiciones más significativas de un tipo entero, 
     cuyos campos son invalidos para la representación de una palabra*/
    return formato != FMT_TXT ? (palabra & MASK_OPCODE) >> OPCODE_SHIFT : palabra / OPCODE_OPERANDO_MULTIPLIER;
}   /*TESTEADO*/
palabra_t get_operando(palabra_t palabra, formato_t formato){
    if(palabra < 0)
        palabra = -palabra;
    return formato != FMT_TXT ? palabra & MASK_OPERANDO : palabra % OPCODE_OPERANDO_MULTIPLIER;
}   /*TESTEADO*/
/*Se usa para cambiar de opcode binario a opcode texto si el MSB esta activo*/
palabra_t aplicar_signo(palabra_t palabra, palabra_t BIT_FIELD ,palabra_t MSB){
    /*Se puede mejoror si en lugar de complementar dos veces, se llenan de 1s en los bits por delante del opcode*/
    /*
    return palabra & MSB ? -(((~palabra) & BIT_FIELD) + 1) : palabra;
    */
    return palabra & MSB ? palabra | (~BIT_FIELD) : palabra;
    
} /*TESTEADO*/
/*Para pasar de texto a binario si el opcode fuera negativo*/
palabra_t quitar_signo_palabra(palabra_t palabra, palabra_t BIT_FIELD){
    return palabra & BIT_FIELD;
}   /*TESTEADO*/
/*Se asume que las palabras estan validadas y llenadas con ceros a la izquierda*/
palabra_t cambiar_fmt_palabra(palabra_t palabra, formato_t actual){
    palabra_t operando;
    palabra_t opcode;
    
    opcode = get_opcode(palabra, actual);
    operando = get_operando(palabra, actual);
    
    switch(actual){
        case FMT_BIN: /*La palabra estaba almacenada en un entero con el formato binario y se quiere pasar al formato texto*/
            opcode = aplicar_signo(opcode, MASK_OPCODE >> OPCODE_SHIFT, MASK_MSB >> OPCODE_SHIFT);
            return opcode * OPCODE_OPERANDO_MULTIPLIER + (opcode >= 0 ? operando : -operando);
        case FMT_TXT:
            /*Si el opcode fuera negativo, necesito eliminar los 1s delanteros*/
            opcode = quitar_signo_palabra(opcode, MASK_OPCODE >> OPCODE_SHIFT);
            return (( (int) 0 | opcode) << OPCODE_SHIFT) | operando;
        default:
            return palabra;
    }
}   /*TESTEAD*/
/*****************************DUMP.C********************************************************/
void imprimir_dump(simpletron_t * simpletron, archivo_t * archivo_salida){
    switch(archivo_salida->formato){
        case FMT_TXT:
            imprimir_dump_txt(simpletron, archivo_salida->stream);
            return;
        case FMT_BIN:
            imprimir_dump_bin(simpletron, archivo_salida->stream);
            return;
    }
}
void imprimir_dump_txt(simpletron_t * simpletron, FILE * stream){
    size_t i, j, memoria_pedida;
    palabra_t instruccion_txt, opcode_txt, operando_txt;
    
    instruccion_txt = cambiar_fmt_palabra(simpletron->instruccion, FMT_BIN);
    opcode_txt = get_opcode(instruccion_txt, FMT_TXT);
    operando_txt = get_operando(instruccion_txt, FMT_TXT);
    memoria_pedida = VECTOR_obtener_memoria_pedida(simpletron->memoria);
    
    fprintf(stream, "\n%s:\n", DUMP_MSJ_REGISTROS);
    fprintf(stream, "%15s:     %04X\n", DUMP_MSJ_ACUMULADOR, simpletron->acumulador);
    fprintf(stream, "%15s:%9ld\n", DUMP_MSJ_PROGRAM_COUNTER, simpletron->program_counter);
    fprintf(stream, "%15s: %+08d\n", DUMP_MSJ_INSTRUCCION, instruccion_txt);
    fprintf(stream, "%15s:%9d\n", DUMP_MSJ_OPCODE, opcode_txt);
    fprintf(stream, "%15s:      %03d\n", DUMP_MSJ_OPERANDO, operando_txt);
    fprintf(stream, "%s:", DUMP_MSJ_MEMORIA);

    for (i = 0, j = 0; i < memoria_pedida; i++){
        if (!(i % 8))
            fprintf(stream, "\n%02lx0:", j++);

        fprintf(stream, " %04X", VECTOR_obtener_dato(simpletron->memoria, i + 1));
    }
}
void imprimir_dump_bin(simpletron_t * simpletron, FILE * stream){
    size_t i, memoria_pedida;
    palabra_t palabra;
    
    memoria_pedida = VECTOR_obtener_memoria_pedida(simpletron->memoria);

    for (i = 0; i < memoria_pedida; i++){
        palabra = VECTOR_obtener_dato(simpletron->memoria, i + 1);
        fwrite(&palabra,sizeof(palabra_t),1,stream);
    }
}
/******************************LISTAS.C**********************************************************/
/*TRATAR DE VALIDAR FUNCIONES DE LISTA QUE RECIBEN FUNCIONES COMO ARGUMETO*/
bool_t LISTA_esta_vacia(lista_t lista) {
    return lista == NULL;
}
retval_t LISTA_crear(lista_t * plista) {
    if(plista == NULL)
        return RV_ILLEGAL;

    *plista = NULL;

    return RV_SUCCESS;
}
retval_t LISTA_crear_nodo(nodo_t ** pnodo, void * dato) {
    if(pnodo == NULL)
        return RV_ILLEGAL;

    if((*pnodo = (nodo_t *)calloc(1, sizeof(nodo_t))) == NULL)
        return RV_NOSPACE;

    (*pnodo)->siguiente = NULL;
    (*pnodo)->dato = dato;

    return RV_SUCCESS;
}
retval_t LISTA_destruir_nodo(nodo_t ** pnodo, retval_t (*destructor_dato)(void *)) {
    void * dato;

    if(pnodo == NULL)
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*pnodo))
        return RV_SUCCESS;

    dato = (*pnodo)->dato;

    (*pnodo)->siguiente = NULL;
    (*pnodo)->dato = NULL;
    free(*pnodo);
    *pnodo = NULL;

    return (destructor_dato != NULL) ? (*destructor_dato)(&dato) : RV_SUCCESS;
}
retval_t LISTA_destruir_primero(lista_t * plista, retval_t (*destructor_dato)(void *)) {
    nodo_t * primero;

    if(plista == NULL)
        return RV_ILLEGAL;

    if(*plista == NULL)/* es equivalente a LISTA_esta_vacia(*plista) */
        return RV_SUCCESS;

    primero = *plista;
    *plista = (*plista)->siguiente;

    return LISTA_destruir_nodo(&primero, destructor_dato);
}
retval_t LISTA_destruir(lista_t * plista, retval_t (*destructor_dato)(void *)) {
    nodo_t * siguiente;
    if(plista == NULL)
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*plista))
        return RV_SUCCESS;

    siguiente = (*plista)->siguiente;

    LISTA_destruir_nodo(plista, destructor_dato );
    return LISTA_destruir(&siguiente, destructor_dato);
}
retval_t LISTA_insertar_al_ppio(lista_t * plista, void * dato) {
    nodo_t * nuevo;
    retval_t rv;

    if(plista == NULL)
        return RV_ILLEGAL;

    if((rv = LISTA_crear_nodo(&nuevo, dato)) != RV_SUCCESS)
        return rv;

    nuevo->siguiente = *plista;
    *plista = nuevo;

    return RV_SUCCESS;
}
retval_t LISTA_insertar_al_final(lista_t * plista, void * dato) {
    if(plista == NULL)
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*plista))
        return LISTA_insertar_al_ppio(plista, dato);

    return LISTA_insertar_al_final(&((*plista)->siguiente), dato);
}
retval_t LISTA_insertar_decreciente(lista_t * plista, void * dato, int (*cmp)(void *, void *)) {
    retval_t rv;
    nodo_t * nuevo;

    if(plista == NULL)
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*plista) || (*cmp)( (*plista)->dato, dato) < 0 ) {
        if((rv = LISTA_crear_nodo(&nuevo, dato)) != RV_SUCCESS)
            return rv;

        nuevo->siguiente = *plista;
        *plista = nuevo;

        return RV_SUCCESS;
    }

    return LISTA_insertar_decreciente(&((*plista)->siguiente), dato, cmp);
}
void * LISTA_buscar(lista_t pnodo, void * t, int (*es_igual)(void *, void *)) {
    if(pnodo == NULL)
        return NULL;

    if((*es_igual)(t, pnodo->dato))
        return pnodo->dato;

    return LISTA_buscar(pnodo->siguiente, t, es_igual);
}
retval_t LISTA_imprimir(lista_t pnodo, FILE * ofile, retval_t (*impresor)(void *, FILE *)) {
    if(pnodo == NULL)
        return RV_SUCCESS;

    (*impresor)(pnodo->dato, ofile);
    LISTA_imprimir(pnodo->siguiente, ofile, impresor);

    return RV_SUCCESS;
}
retval_t LISTA_recorrer(lista_t pnodo, retval_t (*funcion)(void *, void *), void * argumento) {
    if(pnodo == NULL)
        return RV_SUCCESS;

    (*funcion)(pnodo->dato, argumento);
    return LISTA_recorrer(pnodo->siguiente, funcion, argumento);
}
retval_t LISTA_aplicar(lista_t pnodo, retval_t (*funcion)(void*)){
    if(pnodo == NULL)
        return RV_SUCCESS;
    
    (*funcion)(pnodo->dato);
    return LISTA_aplicar(pnodo->siguiente, funcion);
}
/*****************************LECTORES.C********************************************************/
/*Trabajo con un archivo ya abierto.
 *Utiliza su formato y su FILE * stream ya abierto.
 *Lo lee, y guarda las palabras en la memoria pasada como argumento. */
int abrir_archivos(params_t * param){
    size_t archivos_abiertos = 0;
    size_t i;
    
    if(param == NULL)
        return -1;
    switch(param->archivo_salida->formato){
        case FMT_TXT:
            if((param->archivo_salida->stream = fopen(param->archivo_salida->nombre,"w+t")) != NULL)
                archivos_abiertos++;
            break;
        case FMT_BIN:
            if((param->archivo_salida->stream = fopen(param->archivo_salida->nombre,"w+b")) != NULL)
                archivos_abiertos++;
            break;
    }
    if(param->archivo_entrada->nombre == NULL){
        param->archivo_entrada->stream = stdin;
        return ++archivos_abiertos;
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
        return -1;
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
status_t leer_archivo(vector_t ** memoria, archivo_t * archivo, size_t cantidad){
    if(memoria == NULL || archivo == NULL)
        return ST_ERROR_PTR_NULO;
    switch(archivo->formato){
        case FMT_TXT:
            if(archivo->nombre == NULL)
                return leer_archivo_stdin(memoria,cantidad);
            return leer_archivo_txt(memoria,archivo->stream,cantidad);
        case FMT_BIN:
            return leer_archivo_bin(memoria,archivo->stream,cantidad);
        default:
            return ST_ERROR_FORMATO_ARCHIVO_INVALIDO;
    }
}
/*Tratar de usar crecimiento proporcional para los arreglos de TDA vector*/
status_t leer_archivo_txt(vector_t ** memoria, FILE * stream, size_t cantidad){
    char buffer[MAX_STR], *pch;
    palabra_t palabra;
    size_t i;
    
    if(VECTOR_crear(memoria,1) != VCT_RV_SUCCESS)
        return ST_ERROR_VECTOR;
    for(i = 0; fgets(buffer, MAX_STR, stream) != NULL && i < cantidad; i++){
        pch = strtok(buffer, DELIMITADOR_COMENTARIO);
        palabra = strtol(buffer, &pch, 10);
        /*Se valida que el numero pueda ser representado en 16bits y que los opcodes y operandos sean adecuados*/
        if (pch == NULL || (*pch != '\n' && *pch != '\0') || !palabra_es_valida(palabra))
            return ST_ERROR_PALABRA_NO_VALIDA;
        palabra = cambiar_fmt_palabra(palabra,FMT_TXT);
        
        if(VECTOR_redimensionar(*memoria, i + 1) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
        if(VECTOR_guardar_entero(*memoria, i + 1, palabra) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
    }
    
    if(ferror(stream))
        return ST_ERROR_LEER_PALABRA;
    if(i == cantidad)
        return ST_MEMORIA_INSUFICIENTE;
    return ST_OK;
}
/*Esta función asume que el sistema en el que se usa el programa, representa números signados usando
 la convención de complemento a 2 */
status_t leer_archivo_bin(vector_t ** memoria, FILE * stream, size_t cantidad){
    uchar high_byte, low_byte;
    palabra_t palabra;
    size_t i;
    
    if(VECTOR_crear(memoria,1) != VCT_RV_SUCCESS)
        return ST_ERROR_VECTOR;
    for(i = 0; fread(&high_byte,1,1,stream) == 1 && i < cantidad; i++){
        if((fread(&low_byte,1,1,stream) != 1))
            return ST_ERROR_LEER_PALABRA;
        palabra = 0;
        /*Palabra en binario, con ceros rellenados a la izquierda*/
        palabra = ((palabra | high_byte) << BYTE_SHIFT) | low_byte;
        
        if(VECTOR_redimensionar(*memoria, i + 1) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
        if(VECTOR_guardar_entero(*memoria, i + 1, palabra) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
    }
    if(ferror(stream))
        return ST_ERROR_LEER_PALABRA;
    
    return ST_OK;
}
status_t leer_archivo_stdin(vector_t ** memoria, size_t cantidad){
    char buffer[MAX_STR], *pch;
    palabra_t palabra;
    size_t i;
    
    fprintf(stdout, "%s\n", MSJ_BIENVENIDO_SIMPLETRON);
    
    if(VECTOR_crear(memoria,1) != VCT_RV_SUCCESS)
        return ST_ERROR_VECTOR;
    for(i = 0; i < cantidad; i++){
        fprintf(stdout, "%02lu ? ", i);
        
        if(fgets(buffer, MAX_STR, stdin) == NULL)
            return ST_ERROR_LEER_PALABRA;
        
        palabra = strtol(buffer, &pch, 10);
        
        if(palabra == NUMERO_FIN_CARGA)
            break;
        /*Se valida que el numero pueda ser representado en 16bits y que los opcodes y operandos sean adecuados*/
        if (pch == NULL || (*pch != '\n' && *pch != '\0') || !palabra_es_valida(palabra))
            return ST_ERROR_PALABRA_NO_VALIDA;
        
        palabra = cambiar_fmt_palabra(palabra,FMT_TXT);
        
        if(VECTOR_redimensionar(*memoria, i + 1) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
        if(VECTOR_guardar_entero(*memoria, i + 1, palabra) != VCT_RV_SUCCESS)
            return ST_ERROR_VECTOR;
    }
    if(i == cantidad)
        return ST_MEMORIA_INSUFICIENTE;
    
    return ST_OK;
}
/*****************************VECTORES.C********************************************************/
/*Chequear si destruye vectores que piden memoria y estan llenos de ceros*/
/*Debería destruirlos porque calloc rellena el contenido del puntero con ceros. Si el puntero tiene memoria
 asociada, su valor va a ser distinto de NULL */
void VECTOR_destruir(vector_t ** vector){
    if(vector != NULL && *vector != NULL){
        if((*vector)->datos != NULL){
            free((*vector)->datos);
            (*vector)->datos = NULL;
        }
        free(*vector);
        *vector = NULL;
    }   
}
vct_retval_t VECTOR_crear(vector_t ** vector, size_t n){
    if(vector == NULL)
        return VCT_RV_ILLEGAL;
    if(n <= 0)
        return VCT_RV_INVALID_ARGS;
    if((*vector = (vector_t *)calloc(1, sizeof(vector_t))) == NULL)
        return VCT_RV_NOSPACE;
    if(((*vector)->datos = (int *)calloc(n, sizeof(int))) == NULL){
        VECTOR_destruir(vector);
        return VCT_RV_NOSPACE;
    }
    /*v->usado inicializado con calloc*/
    (*vector)->pedido = n;
    return VCT_RV_SUCCESS;
}
vct_retval_t VECTOR_redimensionar(vector_t * vector, size_t n){
    int * aux;
    
    if(vector == NULL)
        return VCT_RV_ILLEGAL;
    if(n <= 0)
        return VCT_RV_INVALID_ARGS;
    
    if(n == vector->pedido)
        return VCT_RV_SUCCESS;

    aux = (int*)calloc(n, sizeof(int));
    if(aux == NULL)
        return VCT_RV_NOSPACE;
    memcpy(aux, vector->datos, n > vector->usado ? (vector->usado) * sizeof(int) : (n) * sizeof(int));
    free(vector->datos);
    vector->datos = (int *)calloc(n, sizeof(int));
    if(vector->datos == NULL){
    	free(aux);
        return VCT_RV_NOSPACE;
    }
    memcpy(vector->datos, aux, n > vector->usado ? (vector->usado) * sizeof(int) : (n) * sizeof(int));
    free(aux);

    vector->pedido = n;
    if(vector->usado > vector->pedido)
        vector->usado = vector->pedido;
    return VCT_RV_SUCCESS;
}
vct_retval_t VECTOR_guardar_entero(vector_t * vector, size_t posicion, int dato){
    if(vector == NULL)
        return VCT_RV_ILLEGAL;
    if(posicion > vector->pedido || posicion < 1)
        return VCT_RV_INVALID_ARGS;
    
    (vector->datos)[posicion - 1] = dato;
    
    if(vector->usado < posicion)
        vector->usado = posicion;
    
    return VCT_RV_SUCCESS;  
}
int VECTOR_obtener_dato(vector_t * v, size_t i){
    return v->datos[i - 1];
}
int VECTOR_obtener_memoria_usada(vector_t * v){
    return v == NULL ? -1 : v->usado;
}
int VECTOR_obtener_memoria_pedida(vector_t * v){
    return v == NULL ? -1 : v->pedido;
}
/*********************************SIMPLETRON.C*************************************************/
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
bool_t palabra_es_valida(palabra_t palabra){
    palabra_t operando;
    palabra_t opcode;
    
    if (palabra > MAX_PALABRA_TXT || palabra < MIN_PALABRA_TXT)
        return FALSE;
    operando = palabra < 0 ? -palabra % OPCODE_OPERANDO_MULTIPLIER : palabra % OPCODE_OPERANDO_MULTIPLIER;
    if (operando < OPERANDO_MIN || operando > OPERANDO_MAX)
        return FALSE;
    opcode = palabra / OPCODE_OPERANDO_MULTIPLIER;
    if (opcode < OPCODE_FIELD_MIN || opcode > OPCODE_FIELD_MAX)
        return FALSE;
    
    return TRUE;
} /*TESTEADO*/
/*NULL si no hubo memmoria. Todas las variables y punteros inicializados con calloc*/
simpletron_t * SIMPLETRON_crear(void){
    return (simpletron_t *)calloc(1,sizeof(simpletron_t));
}
void SIMPLETRON_destruir(simpletron_t ** simply){
    if(simply != NULL && *simply != NULL){
        if((*simply)->memoria != NULL){
            VECTOR_destruir(&(*simply)->memoria);  
        }
        free(*simply);
        *simply = NULL;
    }
}
simply_retval_t SIMPLETRON_ejecutar(simpletron_t * simply){
    size_t i;
    int memoria_pedida;
    simply_retval_t status;
    pfx_lms operacion;
    
    if(simply == NULL || simply->memoria == NULL)
        return SMP_RV_ILLEGAL;
    
    memoria_pedida = VECTOR_obtener_memoria_pedida(simply->memoria);
    fprintf(stdout, "%s\n", MSJ_COMIENZO_EJECUCION);
    for(; simply->program_counter < memoria_pedida; simply->program_counter++){
        /*Obtengo opcode y operandos*/
        simply->instruccion = VECTOR_obtener_dato(simply->memoria, simply->program_counter + 1);
        simply->opcode = get_opcode(simply->instruccion, FMT_BIN);
        simply->operando = get_operando(simply->instruccion, FMT_BIN);
        /*Valida que operando pueda ser accdedido*/
        if(simply->operando > memoria_pedida - 1 || simply->operando < 0){
            fprintf(stdout,"%s\n",MSJ_FIN_EJECUCION);
            return SMP_RV_SEGMENTATION_FAULT;
        }
        /*Valido que los opcode sean validos*/  
        for(i = 0; simply->opcode != opcode_validos[i] && i < sizeof(opcode_validos)/sizeof(opcode_validos[0]) ; i++){
        }
        if(i == sizeof(opcode_validos)/sizeof(opcode_validos[0])){
            fprintf(stdout,"%s\n",MSJ_FIN_EJECUCION);
            return SMP_RV_OPCODE_INVALIDO;
        }
        /*Ejecuta opcde*/
        operacion = instrucciones[i];
        status = (*operacion)(simply);
        if (status != SMP_RV_SUCCESS){
            if(status != SMP_RV_HALT){
                fprintf(stdout,"%s\n", MSJ_FIN_EJECUCION);
                return status;
            }
            break;
        }
    }
    fprintf(stdout, "%s\n", MSJ_FIN_EJECUCION);
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_leer(simpletron_t * simpletron){
    char buffer[MAX_STR];
    palabra_t palabra;
    char * pch;
    
    fprintf(stdout,"%s ",MSJ_INGRESO_PALABRA);
    if(fgets(buffer, MAX_STR, stdin) == NULL){
        return SMP_RV_PALABRA_NO_LEIDA;
    }
    palabra = strtol(buffer, &pch, 10);
    /*Se valida que el numero pueda ser representado en 16bits con signo*/
    if (pch == NULL || (*pch != '\n' && *pch != '\0'))
        return SMP_RV_PALABRA_NO_ES_ENTERO;
    if(palabra > MAX_PALABRA_BIN_SIGNED || palabra < MIN_PALABRA_BIN_SIGNED)
        return SMP_RV_PALABRA_FUERA_DE_RANGO;
    
    palabra = quitar_signo_palabra(palabra, MASK_PALABRA);
    
    VECTOR_guardar_entero(simpletron->memoria, simpletron->operando + 1, palabra);
    
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_escribir(simpletron_t * simpletron){
    palabra_t palabra;

    palabra = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    palabra = aplicar_signo(palabra, MASK_PALABRA, MASK_MSB);
    
    fprintf(stdout,"%s %i: %i\n", MSJ_IMPRIMIR_PALABRA, simpletron->operando, palabra);
    return SMP_RV_SUCCESS;
} 
simply_retval_t lms_cargar(simpletron_t * simpletron){
    simpletron->acumulador = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_guardar(simpletron_t * simpletron){
    VECTOR_guardar_entero(simpletron->memoria, simpletron->operando + 1, simpletron->acumulador);
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_pcargar(simpletron_t * simpletron){
    palabra_t puntero;
    /*Las funciones de TDA Vector empiezan a contar desde 1*/
    puntero = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1) + 1;
    if(puntero > VECTOR_obtener_memoria_pedida(simpletron->memoria) || puntero < 1){
        return SMP_RV_SEGMENTATION_FAULT;
    }
    simpletron->acumulador = VECTOR_obtener_dato(simpletron->memoria, puntero);

    return SMP_RV_SUCCESS;
}
simply_retval_t lms_pguardar(simpletron_t * simpletron){
    palabra_t puntero;
    /*Las funciones de TDA Vector empiezan a contar desde 1*/
    puntero = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1) + 1;
    if(puntero > VECTOR_obtener_memoria_pedida(simpletron->memoria) || puntero < 1){
        return SMP_RV_SEGMENTATION_FAULT;
    }
    VECTOR_guardar_entero(simpletron->memoria, puntero, simpletron->acumulador);
    
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_sumar(simpletron_t * simpletron){
    palabra_t resultado;
    
    resultado = simpletron->acumulador + VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_restar(simpletron_t * simpletron){
    palabra_t resultado;
    /*Si dejo que el programa reste normalmente, me llena de ceros a la izquierda
     Resto a nivel de bit, en el campo de la palabra*/
    resultado = simpletron->acumulador - VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    
    resultado = quitar_signo_palabra(resultado, MASK_PALABRA);

    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_dividir(simpletron_t * simpletron){
    palabra_t resultado;
    
    resultado = simpletron->acumulador / VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_multiplicar(simpletron_t * simpletron){
    palabra_t resultado;
    
    resultado = simpletron->acumulador * VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jmp(simpletron_t * simpletron){
    simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jmpneg(simpletron_t * simpletron){
    if(simpletron->acumulador & MASK_MSB)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jmpzero(simpletron_t * simpletron){
    if(!simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jnz(simpletron_t * simpletron){
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_djnz(simpletron_t * simpletron){
    simpletron->acumulador--;
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_halt(simpletron_t * simpletron){
    return SMP_RV_HALT;
}
/*******************************ARGUMENTOS.C********************************************/
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
    if (argc == 2 && (!strcmp(argv[i], FLAG_CLA_AYUDA_CORTO) || !strcmp(argv[i], FLAG_CLA_AYUDA_LARGO))){
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
/*********************************************************************************************/
