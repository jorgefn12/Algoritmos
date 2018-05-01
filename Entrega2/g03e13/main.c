#include "calculos_probabilidad.h"
#include "errores.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

	srand(time(NULL));
	imprimir_probabilidad1(MAX_INTENTOS_PROBABILIDAD);
	imprimir_probabilidad2(MAX_INTENTOS_PROBABILIDAD);
	tirar_monedas(MAX_INTENTOS_MONEDAS);
	tirar_dados(MAX_INTENTOS_DADOS);

	return EXIT_SUCCESS;
}