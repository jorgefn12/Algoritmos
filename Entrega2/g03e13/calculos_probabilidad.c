#include "calculos_probabilidad.h"
#include "errores.h"
#include <stdio.h>
#include <stdlib.h>

void imprimir_probabilidad1(size_t n){
	size_t i;

	for(i = 0; i < n; i++){
		printf("%d ", probabilidad1());
	}
	putchar('\n');

}

void imprimir_probabilidad2(size_t n){
	size_t i;

	for(i = 0; i < n; i++){
		printf("%d ", probabilidad2());
	}
	putchar('\n');
}

int probabilidad1(){
	return (rand() % 10) < 2 ? 0 : 1;
}

int probabilidad2(){
	int irand, irand100;

	irand = rand();
	irand100 = (irand % 10 * 10) + (irand / 10 ) % 10;
	if(irand100 < 10)
		return 3;
	else if(irand100 < 35)
		return 9;
	else
		return 5;
}

void tirar_monedas(size_t n){
	size_t i;

	for(i = 0; i < n; i++)
		printf("%s ", (rand() % 10) < 5 ? "Cara":"Ceca" );
	putchar('\n');
}

void tirar_dados(size_t n){
	size_t i;
	int irand10;

	for(i = 0; i < n; i++){
		for(irand10 = rand() % 10; irand10 < 6; irand10 = rand() % 10)
		switch(irand10){
			case 0:
				printf("|     |\n|  *  |\n|     |\n\n");
				break;
			case 1:
				printf("|    *|\n|     |\n|*    |\n\n");
				break;
			case 2:
				printf("|*    |\n|  *  |\n|    *|\n\n");
				break;
			case 3:
				printf("|*   *|\n|     |\n|*   *|\n\n");
				break;
			case 4:
				printf("|*   *|\n|  *  |\n|*   *|\n\n");
				break;
			case 5:
				printf("|*   *|\n|*   *|\n|*   *|\n\n");
				break;
			default:
				fprintf(stderr, MSJ_ERR_LECTURA_DADO);
		}
	}
}