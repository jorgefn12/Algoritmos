/* CAMBIOS TODAVIA NO REALIZADOS EN MAIN.C

Agregar prototipo de imprimir_ayuda

Acumulador inicializado a 0, 

Agregar "int opcode", "int operando", "int instruccion" en la estructura de palabras_s

Cambiar nombre de la variable "memoria" asociada al CLA por "cant_memoria" para no confundirla con la memoria del simpletron

Agregar "int* memoria_int" y modificar "char** memoria" por "char** memoria_char" en la estructura palabra_s
para poder trabajar con la memoria segun la necesitemos en char o int

*/
#include <stdio.h>
#include <stdlib.h>

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

#define INIT_INSTRUCCIONES 0
#define MAX_STR 200
#define MIN_PALABRA -9999
#define MAX_PALABRA 9999
#define MAX_INSTRICCIONES 200

#define MSJ_ERROR_CAD_NO_ES_ENTERO "La cadena contiene carácteres no numericos"
#define MSJ_ERROR_PALABRA_FUERA_DE_RANGO "La palabra excede el rango admitido por Simpletron [-9999;+9999]"
#define MSJ_ERROR_SEGMENTATION_FAULT "Se intentó acceder a memoria que Simpletron no solicitó"
#define MSJ_ERROR_CAD_NO_LEIDA "No pudo leer el valor ingresado"
#define MSJ_ERROR_OPCODE_INVALIDO "El código de instrucción no es válido"
#define MSJ_ERROR_MAX_INSTR_SUPERADO "La cantidad de instrucciones operadas alcanzó el máximo admitido"

#define MSJ_COMIENZO_EJECUCION "******** INICIO DE EJECUCION DEL SIMPLETRON *******"
#define MSJ_FIN_EJECUCION "********* FIN DE EJECUCION DEL SIMPLETRON *********"
#define MSJ_INGRESO_PALABRA "Ingrese una palabra: "
#define MSJ_IMPRIMIR_PALABRA "Contenido de la posición"


/* Funciones para visualizar registros y memoria
void imprimir_registros(long acc, size_t program_counter, long instruccion, int opcode, int operando);
void imprimir_memoria(int* memoria, size_t elementos);
*/

int main(void){
	char* codigo_lms[] = {"+1009","+1010","+2009","+3010","+2111","+1111","+4500","+0000","+0000","+0000","+0000","+0000"};
	char aux[MAX_STR]; /*Aca guardo todo lo que ingresa el usuario*/
	int temp; /*Guardo enteros para validar antes de guardarlos en memoria*/
	int* codigo_lms_int; /*Aca se transforma el vector de cadenas en vector de enteros*/
	int cantidad_palabras; /*Guarda la cantidad maxima de palabras que contiene la memoria*/
	char* p; /*Puntero auxiliar*/
	int instruccion;
	size_t program_counter, i;
	int opcode, operando;
	long acumulador = 0;

/*Se crea el vector de enteroos*/
	cantidad_palabras = sizeof(codigo_lms)/sizeof(char*);
	codigo_lms_int = (int*)malloc(sizeof(int)* cantidad_palabras);
/*Valida que todos los enteros estén dentro del rango aceptado*/
	for(i = 0; i < cantidad_palabras; i++){
		codigo_lms_int[i] = strtol(codigo_lms[i], &p, 10);
		if(*p != '\n' && *p != '\0' && *p != EOF){
			puts(MSJ_ERROR_CAD_NO_ES_ENTERO);
			return EXIT_FAILURE;
		}
		if(codigo_lms_int[i] < MIN_PALABRA || codigo_lms_int[i] > MAX_PALABRA){
			puts(MSJ_ERROR_PALABRA_FUERA_DE_RANGO);
			return EXIT_FAILURE;
		}
	}
/*Comienza ejecución*/
	puts(MSJ_COMIENZO_EJECUCION);
	for(program_counter = 0; program_counter < MAX_INSTRICCIONES; program_counter++){
		instruccion = codigo_lms_int[program_counter];
		operando = instruccion % 100;
		opcode = instruccion / 100;

		if(operando > cantidad_palabras || operando < INIT_INSTRUCCIONES){
			puts(MSJ_ERROR_SEGMENTATION_FAULT);
			puts(MSJ_FIN_EJECUCION);
			return EXIT_FAILURE;
		}

		switch(opcode){
			case LEER:
				printf(MSJ_INGRESO_PALABRA);
				if (fgets(aux, MAX_STR, stdin) == NULL){
					puts(MSJ_ERROR_CAD_NO_LEIDA);
					puts(MSJ_FIN_EJECUCION);
					return EXIT_FAILURE;
				}
				if( (temp = strtol(aux, &p, 10)) < MIN_PALABRA || temp > MAX_PALABRA){
					puts(MSJ_ERROR_PALABRA_FUERA_DE_RANGO);
					puts(MSJ_FIN_EJECUCION);
					return EXIT_FAILURE;
				}
				if(*p != '\n' && *p != '\0' && *p != EOF){
					puts(MSJ_ERROR_CAD_NO_ES_ENTERO);
					puts(MSJ_FIN_EJECUCION);
					return EXIT_FAILURE;
				}

				codigo_lms_int[operando] = temp;
				break;
			case ESCRIBIR:
				printf("%s %i: %i\n",MSJ_IMPRIMIR_PALABRA,operando,codigo_lms_int[operando]);
				break;
			case CARGAR:
				acumulador = codigo_lms_int[operando];
				break;
			case GUARDAR:
				if(acumulador < MIN_PALABRA || acumulador > MAX_PALABRA){
					puts(MSJ_ERROR_PALABRA_FUERA_DE_RANGO);
					puts(MSJ_FIN_EJECUCION);
					return EXIT_FAILURE;
				}
				codigo_lms_int[operando] = acumulador;
				break;
			case PCARGAR:
				if(codigo_lms_int[operando] > cantidad_palabras || codigo_lms_int[operando] < INIT_INSTRUCCIONES){
					puts(MSJ_ERROR_SEGMENTATION_FAULT);
					puts(MSJ_FIN_EJECUCION);
					return EXIT_FAILURE;
				}
				acumulador = codigo_lms_int[codigo_lms_int[operando]];
				break;
			case PGUARDAR:
				if(codigo_lms_int[operando] > cantidad_palabras || codigo_lms_int[operando] < INIT_INSTRUCCIONES){
					puts(MSJ_ERROR_SEGMENTATION_FAULT);
					puts(MSJ_FIN_EJECUCION);
					return EXIT_FAILURE;
				}
				codigo_lms_int[codigo_lms_int[operando]] = acumulador;
				break;
			case SUMAR:
				acumulador += codigo_lms_int[operando];
				break;
			case RESTAR:
				acumulador -= codigo_lms_int[operando];
				break;
			case DIVIDIR:
				acumulador /= codigo_lms_int[operando];
				break;
			case MULTIPLICAR:
				acumulador *= codigo_lms_int[operando];
				break;
			case JMP:
				program_counter = operando;
				break;
			case JMPNEG:
				if (acumulador < 0)
					program_counter = operando;
				break;
			case JMPZERO:
				if (!acumulador)
					program_counter = operando;
				break;
			case JNZ:
				if(acumulador)
					program_counter = operando;
				break;
			case DJNZ:
				acumulador--;
				if(acumulador)
					program_counter = operando;
				break;
			case HALT:
				puts(MSJ_FIN_EJECUCION);
				return EXIT_SUCCESS;
			default:
				puts(MSJ_ERROR_OPCODE_INVALIDO);
				puts(MSJ_FIN_EJECUCION);
				return EXIT_FAILURE;
		}
	}
	puts(MSJ_ERROR_MAX_INSTR_SUPERADO);
	puts(MSJ_FIN_EJECUCION);
	return EXIT_FAILURE;
}


/*
	imprimir_registros(acumulador,program_counter,instruccion,opcode,operando);
	imprimir_memoria(codigo_lms_int, cantidad_palabras);

void imprimir_registros(long acc, size_t program_counter, long instruccion, int opcode, int operando){
	printf("acumulador: %li\n", acc);
	printf("program counter: %lu\n", program_counter);
	printf("instruccion: %li\n", instruccion);
	printf("opcode: %d\n", opcode);
	printf("operando: %d\n", operando);
}

void imprimir_memoria(int* memoria, size_t elementos){
	size_t i;
	printf("Memoria: ");
	for(i = 0; i < elementos; i++)
		printf("%d ", memoria[i]);
	putchar('\n');
}
*/
