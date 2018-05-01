#include "calculos_cilindro.h"
#include "errores.h"
#include "utilidades.h"
#include <stdio.h>

status_t procesar_entrada_cilindro(float * radio_cilindro, float * altura_cilindro){
	float radio, altura;

	if(!radio_cilindro || !altura_cilindro)
		return ST_ERR_PTR_NULO;
	puts(MSJ_PROGRAMA_CILINDRO);
	puts(MSJ_INGRESO_RADIO);
	if(scanf("%f", &radio) != 1)
		return ST_ERR_ENTRADA_INVALIDA;
	limpiar_buffer();
	if(radio <= MIN_RANGO_RADIO)
		return ST_ERR_RANGO_INVALIDO;
	puts(MSJ_INGRESO_ALTURA);
	if(scanf("%f", &altura) != 1)
		return ST_ERR_ENTRADA_INVALIDA;
	limpiar_buffer();
	if(altura <= MIN_RANGO_ALTURA)
		return ST_ERR_RANGO_INVALIDO;
	*radio_cilindro = radio;
	*altura_cilindro = altura;
	return ST_OK;
}


void imprimir_medidas_cilindro(float radio_cilindro, float altura_cilindro){
	printf("%s = %.2f\n", MSJ_DIAMETRO_CILINDRO, cilindro_diametro(radio_cilindro,altura_cilindro));
	printf("%s = %.2f\n", MSJ_CIRCUNFERENCIA_CILINDRO, cilindro_circunferencia(radio_cilindro,altura_cilindro));
	printf("%s = %.2f\n", MSJ_BASE_CILINDRO, cilindro_base(radio_cilindro,altura_cilindro));
	printf("%s = %.2f\n", MSJ_VOLUMEN_CILINDRO, cilindro_volumen(radio_cilindro,altura_cilindro));
}


float cilindro_diametro(float radio, float altura){
	return radio * 2;
}


float cilindro_circunferencia(float radio, float altura){
	return 2 * M_PI * radio;
}


float cilindro_base(float radio, float altura){
	return M_PI * radio * radio;
}


float cilindro_volumen(float radio, float altura){
	return M_PI * radio * radio * altura;
}