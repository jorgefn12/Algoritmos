/*
Tira un montón de errores, los estoy corrigiendo.
Quizas también falte cambiarle el tipo a algunas cosas
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_INSTRUCCIONES 0
#define MAX_INSTRICCIONES 5000
#define MAX_STR 200
#define MAX_INGRESOS 5
/*MENSAJES DE AYUDA*/
#define MSJ_AYUDA_TITULO "------------------------------AYUDA------------------------------"
#define MSJ_AYUDA_M1 "OPCION |N|: Simpletron tiene una memoria de N palabras. Si no se da el argumento, por omisión tendrá 50 palabras. El maximo es de 200 palabras"
#define MSJ_AYUDA_I1 "OPCION |ARCHIVO|: El programa se leerá del archivo pasado como opción, en caso contrario, de stdin."
#define MSJ_AYUDA_IF1 "OPCION |BIN|: El archivo de entrada se entenderá como una secuencia binaria de enteros que representan las palabras que forman el programa."
#define MSJ_AYUDA_IF2 "OPCION |TXT|: El archivo de entrada se interpretará como secuencia de números, cada uno en una única línea."
#define MSJ_AYUDA_O1 "OPCION |ARCHIVO|: El dump se hará en el archivo pasado como opción, si no pasa el argumento, el volcado se hará por stdout."
#define MSJ_AYUDA_OF1 "OPCION |BIN|: El volcado se hará en binario guardando cada elemento de la estructura del Simpletron, además de la memoria."
#define MSJ_AYUDA_OF2 "OPCION |TXT|: El volcado se hará en formato de texto imprimiendo los registros y la memoria."
#define MSJ_BIENVENIDO_SIMPLETRON "*** ¡Bienvenido a la Simpletron!         ***\n*** Por favor, ingrese su programa una   ***\n*** instrucción (o dato) a la vez. Yo    ***\n*** escribiré la ubicacíón y un signo de ***\n*** pregunta (?). Luego usted ingrese la ***\n*** palabra para esa ubicación. Ingrese  ***\n*** -99999 para finalizar:               ***"
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
#define MSJ_ERROR_CAD_INVALIDA "La cadena no es valida"
#define MSJ_ERROR_PALABRA_FUERA_DE_RANGO "La palabra excede el rango admitido por Simpletron [-9999;+9999]"
#define MSJ_ERROR_SEGMENTATION_FAULT "Se intentó acceder a memoria que Simpletron no solicitó"
#define MSJ_ERROR_CAD_NO_LEIDA "No pudo leer el valor ingresado"
#define MSJ_ERROR_OPCODE_INVALIDO "El código de instrucción no es válido"
#define MSJ_ERROR_MAX_INSTR_SUPERADO "La cantidad de instrucciones operadas alcanzó el máximo admitido"
#define MSJ_ERROR_MAX_INGRESOS_SUPERADO "La cantidad de ingresos alcanzó el máximo admitido"
#define MSJ_ERROR_INGRESO_PALABRA "Error. La palabra debe ser un entero sin caracteres alfabeticos. Vuelva a ingresar la palabra"
#define MSJ_ERROR_I_BIN_IF_NO_VALIDO "No es valido el ingreso de palabras por pantalla en modo binario"
/*EJECUCION CODIGO*/
#define MSJ_COMIENZO_EJECUCION "******** INICIO DE EJECUCION DEL SIMPLETRON *******"
#define MSJ_FIN_EJECUCION "********* FIN DE EJECUCION DEL SIMPLETRON *********"
#define MSJ_INGRESO_PALABRA "Ingrese una palabra: "
#define MSJ_NUEVO_INGRESO "Ingrese nuevamente."
#define MSJ_IMPRIMIR_PALABRA "Contenido de la posición"




#define CLA_H "-h"
#define CLA_HELP "--help"
#define CLA_M "-m"
#define CLA_MEMORIA "--memoria"
#define CLA_F "-f"
#define CLA_FORMATO "--formato"
#define CLA_F_OPT_BIN "bin"
#define CLA_F_OPT_TXT "txt"
#define CLA_STDIN "-"

typedef unsigned int uint;

typedef enum{
    ST_OK,
    ST_HELP,
    ST_ERROR_CANT_ARG,
    ST_ERROR_STDIN_INVALIDO,
    ST_ERROR_PTR_NULO,
    ST_ERROR_ARCHIVO_NO_ENCONTRADO,
    ST_ERROR_MEM,
    ST_ERROR_M_INVALIDO,
    ST_ERROR_F_INVALIDO,
    /*status de ejecutar_codigo*/
    ST_ERROR_CAD_NO_ES_ENTERO,
    ST_ERROR_PALABRA_FUERA_DE_RANGO,
    ST_ERROR_SEGMENTATION_FAULT,
    ST_ERROR_CAD_NO_LEIDA,
    ST_ERROR_OPCODE_INVALIDO,
    ST_ERROR_MAX_INSTR_SUPERADO,
    ST_ERROR_ESCRIBIR_BIN,
    ST_ERROR_MAX_INGRESOS_SUPERADO
}status_t;


typedef long palabra_t;

typedef enum {
    FMT_TXT,
    FMT_BIN
}formato_t;

typedef struct palabra{
    palabra_t dato;
    struct palabra * sig;
}palabra_s;

typedef enum{
    FALSE = 0,
    TRUE
}bool_t;

typedef struct archivo{
    char * nombre;
    formato_t formato;
    palabra_s * memoria;
    size_t cant_palabras;
}archivo_s;

/*Para indicar que el archivo es stdin, se inicializa cant_archivos = 1, nombre = "stdin" y formato = FMT_TXT*/
typedef struct params{
    size_t cant_memoria;
    size_t cant_archivos;
    archivo_s archivo_salida;
    archivo_s * archivo_entrada;
}params_s;

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
int opcode_validos[] = {
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

typedef struct simpletron{
    archivo_s archivo;
    palabra_t acumulador;
    int instruccion;
    opcode_t opcode;
    uint operando;
    size_t program_counter;
    struct simpletron *sig;
} simpletron_s;

typedef status_t * (*pfx) (void *, void *, void *);



/*Se trabajan con CLA de orden especifico, ningun argumento es obligatorio*/
/*El orden es el siguiente: ./run [-h] [-m N] [-f FMT] [-|[ARCHIVO1 [ARCHIVO2 ...]]]*/
status_t validacion_cla(int argc, char **argv, params_s *param);
char * get_name_lmsfile(char* name);
formato_t get_fmt_lmsfile(char* name);
bool_t argc_reached(size_t i, int argc);
void imprimir_error(status_t st);
pfx seleccionar_operacion (opcode_t op);
/*
void debug(void){
    static size_t i = 0;
    printf("FUNKA %ld\n",++i);
}
*/

int main(int argc, char ** argv){
    params_s argumentos;
    status_t status;
    size_t i;
    
    status = validacion_cla(argc, argv, &argumentos);
    for(i=0;i<argumentos.cant_archivos;i++){
        printf("Archivo entrada %lu: %s [%d]\n", i+1, argumentos.archivo_entrada[i].nombre, argumentos.archivo_entrada[i].formato);
    }
    printf("Archivo salida: %s [%d]\n",argumentos.archivo_salida.nombre, argumentos.archivo_salida.formato);
    printf("Cantidad memoria: %ld\n", argumentos.cant_memoria);
    printf("Cantidad archivos: %ld\n", argumentos.cant_archivos);
    imprimir_error(status);
    return EXIT_SUCCESS;
}

void imprimir_error(status_t st){
    switch(st){
        case(ST_OK):
            puts("OK");
            break;
        case(ST_HELP):
            puts("HELP");
            break;
        case(ST_ERROR_CANT_ARG):
            puts("ERROR_CANT_ARG");
            break;
        case(ST_ERROR_STDIN_INVALIDO):
            puts("ERROR_STDIN_INVALIDO");
            break;
        case(ST_ERROR_PTR_NULO):
            puts("ERROR_PTR_NULO");
            break;
        case(ST_ERROR_ARCHIVO_NO_ENCONTRADO):
            puts("ERROR_ARCHIVO_NO_ENCONTRADO");
            break;
        case(ST_ERROR_MEM):
            puts("ERROR_MEM");
            break;
        case(ST_ERROR_M_INVALIDO):
            puts("ERROR_M_INVALIDO");
            break;
        case(ST_ERROR_F_INVALIDO):
            puts("ERROR_F_INVALIDO");
            break;
        default:
            puts("ERROR");
    }
}

status_t validacion_cla(int argc, char **argv, params_s *param){
    size_t i = 0, j, cant_archivos;
    bool_t stdin_flag = FALSE;
    long temp;
    char *pc;
    FILE *pf;
    /*----------------------------VALIDACIONES-----------------------------
     Valido que los nombres no apunten a NULL para usar funciones get()
     */
    if(argv == NULL || param == NULL)
        return ST_ERROR_PTR_NULO;
    for(j = 1; j < argc; j++){
        if( argv[j] == NULL)
            return ST_ERROR_PTR_NULO;
    }
    /*-----------------------------DEFAULT-----------------------------
     */
    param->cant_memoria = 50;
    param->cant_archivos = 1;
    param->archivo_salida.formato = FMT_TXT;
    param->archivo_salida.nombre = "dump";
    if( (param->archivo_entrada = (archivo_s*)malloc(sizeof(archivo_s))) == NULL )
        return ST_ERROR_MEM;
    param->archivo_entrada->formato = FMT_TXT;
    param->archivo_entrada->nombre = "stdin";

    if(++i >= argc)
        return ST_OK;
    /*-----------------------------AYUDA-----------------------------
     * Forma de ejecutar: ./simpletron -h o --help */
    if(argc == 2 && (strcmp(argv[i], CLA_H) == 0 || strcmp(argv[i], CLA_HELP) == 0))
        return ST_HELP;
    
    /*-----------------------------MEMORIA-----------------------------*/
    if( strcmp(argv[i], CLA_M) == 0 || strcmp(argv[i], CLA_MEMORIA) == 0){
        if(++i >= argc)
            return ST_ERROR_M_INVALIDO;
  
        temp = strtol(argv[i], &pc, 10);
        if (temp <= 0 || pc == NULL || (*pc != '\n' && *pc != '\0'))
            return ST_ERROR_M_INVALIDO;
        param->cant_memoria = temp;
        
        if(++i >= argc)
            return ST_OK;
    }
    /*----------------------------FORMATO SALIDA---------------------------------*/
    if( strcmp(argv[i], CLA_F) == 0 || strcmp(argv[i], CLA_FORMATO) == 0){
        if(++i >= argc)
            return ST_ERROR_F_INVALIDO;
        
        if( strcmp(argv[i], CLA_F_OPT_BIN) == 0){
            param->archivo_salida.formato = FMT_BIN;
        }
        else if ( strcmp(argv[i], CLA_F_OPT_TXT) == 0){
            param->archivo_salida.formato = FMT_TXT;
        }
        else
            return ST_ERROR_F_INVALIDO;
        
        if(++i >= argc)
            return ST_OK;
    }
    /*-------------------ARCHIVOS Y FORMATOS DE ENTRADA---------------------------------*/
    for (cant_archivos = 0; i < argc; i++){
        if ((param->archivo_entrada = (archivo_s*) realloc(param->archivo_entrada, sizeof (archivo_s)*(++cant_archivos))) == NULL)
            return ST_ERROR_MEM;
        param->archivo_entrada[cant_archivos-1].nombre = get_name_lmsfile(argv[i]);
        param->archivo_entrada[cant_archivos-1].formato = get_fmt_lmsfile(argv[i]);
        
        if(!stdin_flag && strcmp(param->archivo_entrada[cant_archivos-1].nombre,"stdin") == 0)
            stdin_flag = TRUE;
        
        if(!stdin_flag){
            if((pf = fopen(param->archivo_entrada[cant_archivos-1].nombre, "r")) == NULL)
                return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
            fclose(pf);
        }
    }
    
    /*No se acepta ingreso por stdin si se incluyen archivos o formato binario*/
    if(stdin_flag && (cant_archivos != 1 || param->archivo_entrada->formato == FMT_BIN))
        return ST_ERROR_STDIN_INVALIDO;
    param->cant_archivos = cant_archivos;
    return ST_OK;
}

char * get_name_lmsfile(char* name){
    if(strncmp(name,"b:",2) == 0 || strncmp(name,"t:",2) == 0)
        return name + 2;
    if(strcmp(name,"-") == 0)
        return "stdin";
    return name;
}

formato_t get_fmt_lmsfile(char* name){
    return strncmp(name,"b:",2) ? FMT_TXT : FMT_BIN;
}

/*Asume que le llegan bloques de memoria validados de acuerdo al rango (correccion del tp1)*/
status_t ejecutar_codigo(simpletron_s * simpletron, params_s * params){
    palabra_s * nodo_inicial;
    palabra_s * nodo_actual;
    
    fprintf(stdout,"%s\n",MSJ_COMIENZO_EJECUCION);
    /*El ciclo se detiene hasta que se acabe la lista de simpletron (NULL)*/
    while(simpletron){
        size_t i;
        status_t status;
        /*Guarda registros para no perder referencia de la posicion de la lista*/
        nodo_inicial = simpletron->archivo.memoria;
        nodo_actual = simpletron->archivo.memoria;
        
        /*Recorre la lista de palabras dentro de la memoria de cada simpletron hasta que se acaben las palabras (NULL)*/
        for(simpletron->program_counter = 0, simpletron->acumulador = 0; nodo_actual; simpletron->program_counter++){
            /*Obteniene opcode y operando de la linea correspondiente*/
            simpletron->instruccion = nodo_actual->dato;
            simpletron->opcode = simpletron->instruccion / 100;
            simpletron->operando = simpletron->instruccion % 100;
            
            /*Valida que operando pueda ser accdedido*/
            if(simpletron->operando > simpletron->archivo.cant_palabras || simpletron->operando < 0){
                fprintf(stdout,"%s\n",MSJ_FIN_EJECUCION);
                return ST_ERROR_SEGMENTATION_FAULT;
            }
            /*Valido que los opcode sean validos*/
            for(i = 0; simpletron->opcode != opcode_validos[i]; i++){
                if((i+1) == sizeof(opcode_validos)/sizeof(int))
                    return ST_ERROR_OPCODE_INVALIDO;
            }
            /*Ejecuta opcde*/
            status = seleccionar_operacion(simpletron->opcode)(simpletron,nodo_inicial,nodo_actual);
            if(status != ST_OK)
                fprintf(stdout,"%s\n", MSJ_FIN_EJECUCION);
                return status == ST_HALT ? ST_OK : status;
            
            /*Avanza lista*/
            nodo_actual = saltar_lista(nodo_inicial, nodo_actual, simpletron->program_counter, simpletron->program_counter + 1);
        }
        /*Avanza al siguiente simpletron en la lista*/
        simpletron = simpletron->sig;
    }
}

/*Asume que le llegan opcodes validados*/
pfx seleccionar_operacion (opcode_t op){
    switch(op){
        case(OP_LEER):
            return lms_leer;
        case(OP_ESCRIBIR):
            return lms_escribir;
        case(OP_CARGAR):
            return lms_cargar;
        case(OP_GUARDAR):
            return lms_guardar;
        case(OP_PCARGAR):
            return lms_pcargar;
        case(OP_PGUARDAR):
            return lms_pguardar;
        case(OP_SUMAR):
            return lms_sumar;
        case(OP_RESTAR):
            return lms_restar;
        case(OP_DIVIDIR):
            return lms_dividir;
        case(OP_MULTIPLICAR):
            return lms_multiplicar;
        case(OP_JMP):
            return lms_jmp;
        case(OP_JMPNEG):
            return lms_jmpneg;
        case(OP_JMPZERO):
            return lms_jmpzero;
        case(OP_JNZ):
            return lms_jnz;
        case(OP_DJNZ):
            return lms_djnz;
        case(OP_HALT):
            return lms_halt;
    }
}

void * saltar_lista (void * nodo_inicial, void * nodo_actual, size_t desde,size_t hasta){
    /*Validacion*/
    if(!nodo_inicial || !nodo_actual || desde < 0 || hasta < 0)
        return NULL;
    /*Condicionales*/
    if(desde == hasta){
        return nodo_actual;
    }
    if(desde < hasta){
        return avanzar_lista_n (nodo_actual, hasta - desde);
    }
    return avanzar_lista_n (nodo_inicial, hasta);
}

void * avanzar_lista_n (void * nodo, size_t n){
    if(!nodo || n < 0)
        return NULL;
    return n ? avanzar_lista_n (nodo->sig, n-1) : nodo;    
}

/*Creo que se estan haciendo validaciones demás, chequeo bien cuando juntemos todo*/
/*La validación extra sería: validar que al saltar linea, me devuelva NULL*/
status_t lms_leer(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    char aux[MAX_STR];
    size_t i;
    
    for(i = 0; i < MAX_INGRESOS; i++){
        fprintf(stdout,"%s ",MSJ_INGRESO_PALABRA);
        if(fgets(aux, MAX_STR, stdin) == NULL){
            fprintf(stdout, "%s %s\n", MSJ_NUEVO_INGRESO, MSJ_ERROR_CAD_NO_LEIDA);
        }
        else if((temp = strtol(aux, &p, 10)) > MAX_PALABRA || temp < MIN_PALABRA || (*p != '\n' && *p != '\0' && *p != EOF)){
            fprintf(stdout, "%s %s\n", MSJ_NUEVO_INGRESO, MSJ_ERROR_CAD_INVALIDA);
        }
        break;
    }
    if(i == MAX_INGRESOS){
        fprintf(stdout,"%s\n",MSJ_FIN_EJECUCION);
        return ST_ERROR_MAX_INGRESOS_SUPERADO;
    }
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    nodo_actual->dato = temp;
    return ST_OK;
}

status_t lms_escribir(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    fprintf(stdout,"%s %i: %i\n",MSJ_IMPRIMIR_PALABRA,simpletron->operando,nodo_actual->dato);
    return ST_OK;
}   

status_t lms_cargar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador = nodo_actual->dato;
    return ST_OK;
}

status_t lms_guardar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    /*VALIDAR EN OTRA PARTE QUE EL ACUMULADOR NO SUPERE RANGOS*/
    nodo_actual->dato = simpletron->acumulador;
    return ST_OK;
}

status_t lms_pcargar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    /*Valido que el puntero pueda ser accedido*/
    if(nodo_actual->dato > simpletron->archivo.cant_palabras || nodo_actual->dato < 0){
        fprintf(stdout,"%s\n", MSJ_FIN_EJECUCION);
        return ST_ERROR_SEGMENTATION_FAULT;
    }
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->operando,nodo_actual->dato)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador = nodo_actual->dato;
    return ST_OK;
}

status_t lms_pguardar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    /*Valido que el puntero pueda ser accedido*/
    if(nodo_actual->dato > simpletron->archivo.cant_palabras || nodo_actual->dato < 0){
        fprintf(stdout,"%s\n", MSJ_FIN_EJECUCION);
        return ST_ERROR_SEGMENTATION_FAULT;
    }
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->operando,nodo_actual->dato)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    nodo_actual->dato = simpletron->acumulador;
    return ST_OK;
}

status_t lms_sumar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador += nodo_actual->dato;
    return ST_OK;
}

status_t lms_restar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador -= nodo_actual->dato;
    return ST_OK;
}

status_t lms_dividir(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador /= nodo_actual->dato;
    return ST_OK;
}

status_t lms_multiplicar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador *= nodo_actual->dato;
    return ST_OK;
}

status_t lms_jmp(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    simpletron->program_counter = simpletron->operando - 1;
    return ST_OK;
}

status_t lms_jmpneg(){
    if(simpletron->acumulador < 0)
        simpletron->program_counter = simpletron->operando - 1;
    return ST_OK;
}

status_t lms_jmpzero(){
    if(!simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return ST_OK;
}

status_t lms_jnz(){
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return ST_OK;
}

status_t lms_djnz(){
    simpletron->acumulador--;
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando;
    return ST_OK;
}

status_t lms_halt(){
    return ST_HALT;
}
