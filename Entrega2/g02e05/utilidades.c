#include "utilidades.h"
#include <stdio.h>

void limpiar_buffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}