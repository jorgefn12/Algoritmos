/*Prototipo para el codigo de ejecucion del simpletron
*Asume que le llegan cadenas que contienen numeros
*


Errores: me tira segmentation fault
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


#define MAX_STR 200
#define MIN_PALABRA -9999
#define MAX_PALABRA 9999
#define MAX_CANT_PALABRAS 12
#define MAX_INSTRICCIONES 200

void imprimir_registros(long acc, size_t program_counter, long instruccion, int opcode, int operando);


int main(void){
	char* codigo_lms[] = {"+1009","+1010","+2009","+3010","+2111","+1111","+4500","+0000","+0000","+0000","+0000","+0000"};
	long* codigo_lms_final;
	char* p;
	long instruccion;
	size_t program_counter, i;
	int opcode, operando;
	long acumulador = 0;

	/*Creo otro vector de longs para poder operar sobre las palabras */
	codigo_lms_final = (long*)malloc(sizeof(long)* (sizeof(codigo_lms)/sizeof(char*)));
	for(i = 0; i < MAX_CANT_PALABRAS; i++){
		codigo_lms_final[i] = strtol(codigo_lms[i], &p, 10);
	}


	for(program_counter = 0; program_counter < MAX_INSTRICCIONES; program_counter++){
		/*Valido que las palabras estén dentro del rango valido*/
		if ( (instruccion = codigo_lms_final[program_counter]) < MIN_PALABRA || instruccion > MAX_PALABRA){
			puts("Palabra fuera de rango");
			/*Hice esta función para chequear si los registros son los esperados,
			 No va en el programa final*/
			imprimir_registros(acumulador,program_counter,instruccion,opcode,operando);
			return EXIT_FAILURE;
		}
		operando = instruccion % 100;
		opcode = instruccion / 100;

		switch(opcode){
			case LEER:
				printf("Ingrese una palabra: ");
				if (fgets(codigo_lms[operando], MAX_STR, stdin) == NULL){
					puts("Valor no leido");
					imprimir_registros(acumulador,program_counter,instruccion,opcode,operando);
					return EXIT_FAILURE;
				}
				codigo_lms_final[operando] = strtol(codigo_lms[operando], &p, 10);
				break;

			case ESCRIBIR:
				printf("Contenido de la posición %lu : %i\n",program_counter, operando);
				break;
			case CARGAR:
				acumulador = codigo_lms_final[operando];
				break;
			case GUARDAR:
				if(acumulador < MIN_PALABRA || acumulador > MAX_PALABRA){
					puts("Acumulador fuera de rango para guardar");
					imprimir_registros(acumulador,program_counter,instruccion,opcode,operando);
					return EXIT_FAILURE;
				}
				codigo_lms_final[operando] = acumulador;
				break;
			case PCARGAR:
				puts("No todavía");
			case PGUARDAR:
				puts("No todavía");
			case SUMAR:
				acumulador += codigo_lms_final[operando];
				break;
			case RESTAR:
				acumulador -= codigo_lms_final[operando];
				break;
			case DIVIDIR:
				acumulador /= codigo_lms_final[operando];
				break;
			case MULTIPLICAR:
				acumulador *= codigo_lms_final[operando];
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
				puts("Terminó bien!!");
				imprimir_registros(acumulador,program_counter,instruccion,opcode,operando);
				return EXIT_SUCCESS;
			default:
				puts("Opcode inválido");
		}
	}
	puts("Se acabaron las instrucciones");
	imprimir_registros(acumulador,program_counter,instruccion,opcode,operando);
	return EXIT_FAILURE;
}


void imprimir_registros(long acc, size_t program_counter, long instruccion, int opcode, int operando){
	printf("acumulador: %li\n", acc);
	printf("program counter: %lu\n", program_counter);
	printf("instruccion: %li\n", instruccion);
	printf("opcode: %d\n", opcode);
	printf("operando: %d\n", operando);
}
