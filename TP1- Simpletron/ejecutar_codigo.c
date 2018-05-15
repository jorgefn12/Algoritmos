/*Prototipo para el codigo de ejecucion del simpletron*/



#include <stdio.h>
#include <stdlib.h>
/*
+1009 ; LEER en la posición de memoria 09
+1010 ; LEER en la posición de memoria 10
+2009 ; CARGAR la posición de memoria 09 al acumulador
+3010 ; SUMAR al acumulador la posición de memoria 10
+2111 ; GUARDAR el acumulador en la posición de memoria 11
+1111 ; ESCRIBIR por pantalla el contenido de la memoria 11
+4500 ; HALT
+0000 ; nop
+0000 ; nop
+0000 ; Variable A
+0000 ; Variable B
+0000 ; Resultado
*/

#define MAX_STR_PALABRA 6;

int main(void){
	char* codigo_lms[] = {"+1009","+1010","2009","+3010","+2111","+1111","+4500","+0000","+0000","+0000","+0000","+0000"};
	char* p;
	size_t program_counter;
	int opcode, operando;
	long acumulador = 0;

	for(program_counter=0; program_counter < 12; program_counter++){
		palabra = strtol(codigo_lms[program_counter],&p,10); /*traducir todo el codigo a long antes de iterar para evitar errores de formato char a long y long a char*/
		opcode = palabra / 100;
		operando = palabra % 100;

		switch(opcode){
			case LERR:
				printf("Ingrese una palabra: ");
				fgets(codigo_lms[operando], MAX_STR, stdin);
				break;			
			case ESCRIBIR:
				printf("Contenido de la posición %d\n", operando);
				break;
			case CARGAR:
				acumulador += strtol(codigo_lms[operando],&p,10);
				break;
			case GUARDAR:
				codigo_lms[operando] = acumulador;
				break;
			case PCARGAR:
			case PGUARDAR:
			case SUMAR:
				acumulador
			case RESTAR:
			case DIVIDIR:
			case MULTIPLICAR:
			case JMP:
			case JMPNEG:
			case JMPZERO:
			case JNZ:
			case DJNZ:
			case HALT:
			default:
		}

		printf("%li\n", strtol(codigo_lms[program_counter],&p,10));
	}




	return EXIT_SUCCESS;
}
