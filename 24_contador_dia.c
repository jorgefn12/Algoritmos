/*Se asume que el año empezó un domingo*/

#include <stdio.h>
#include <stdlib.h>

#define MSJ_INGRESO "Ingrese un número del día del año (1-366). Se devolverá el día de la semana correspondiente"
#define MSJ_ERR_INVALIDO "Valor ingresado inválido"
#define MSJ_ERR_RANGO "Valor ingresado fuera de rango"
#define MSJ_ERR_LECTURA "Error de lectura"
#define MIN_NUMERO_DIA 1
#define MAX_NUMERO_DIA 366

#define MSJ_LUNES "LUNES"
#define MSJ_MARTES "MARTES"
#define MSJ_MIERCOLES "MIÉRCOLES"
#define MSJ_JUEVES "JUEVES"
#define MSJ_VIERNES "VIERNES"
#define MSJ_SABADO "SABADO"
#define MSJ_DOMINGO "DOMINGO"

typedef enum{
	SABADO = 0,
	DOMINGO = 1,
	LUNES = 2,
	MARTES = 3,
	MIERCOLES = 4,
	JUEVES = 5,
	VIERNES = 6
	} dia_t;

int main(void){

	int numero_dia, orden_dia;
	int c;

	printf("%s\n", MSJ_INGRESO);
	if(scanf("%d", &numero_dia) != 1){
		printf("%s\n", MSJ_ERR_INVALIDO);
		return EXIT_FAILURE;
	}
	if(numero_dia < MIN_NUMERO_DIA || numero_dia > MAX_NUMERO_DIA){
		printf("%s\n", MSJ_ERR_RANGO);
		return EXIT_FAILURE;
	}
	while((c = getchar()) != '\n' && c != EOF);

	orden_dia = numero_dia % 7;

	switch (orden_dia){
		case SABADO:
			printf("%s\n", MSJ_SABADO);
			break;
		case DOMINGO:
			printf("%s\n", MSJ_DOMINGO);
			break;
		case LUNES:
			printf("%s\n", MSJ_LUNES);
			break;
		case MARTES:
			printf("%s\n", MSJ_MARTES);
			break;
		case MIERCOLES:
			printf("%s\n", MSJ_MIERCOLES);
			break;
		case JUEVES:
			printf("%s\n", MSJ_JUEVES);
			break;
		case VIERNES:
			printf("%s\n", MSJ_VIERNES);
			break;
		default:
			printf("%s\n", MSJ_ERR_LECTURA);
	}
	return EXIT_SUCCESS;
}












