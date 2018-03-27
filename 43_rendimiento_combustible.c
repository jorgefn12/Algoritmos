#include <stdio.h>
#include <stdlib.h>

#define MSJ_INGRESO_KM "Ingrese los kilometros recorridos (-1 para terminar):"
#define MSJ_ERR_INVALIDO "Valor ingresado inválido"
#define MSJ_INGRESO_PRECIO "Ingrese el precio del combustible por litro:"
#define MSJ_INGRESO_MONTO "Ingrese el monto total utilizado en esta compra:"
#define MSJ_RENDIMIENTO "Rendimiento (l/100km) de este tanque >>"

#define MSJ_PROM_REND "Rendimiento promedio (l/100km) >>"
#define MSJ_MEJOR_REND "Mejor rendimiento (l/100km) >>"
#define MSJ_PEOR_REND "Peor rendimiento (l/100km) >>"
#define MSJ_KM_TOTAL "Distancia total recorrida (km) >>"
#define MSJ_COMB_TOTAL "Combustible total consumidos (l) >>"
#define MSJ_MONTO_TOTAL "Costo total de su vehiculo ($) >>"

int main(void){
	int i;
	float km_recorridos, km_total = 0;
	float precio_litro_comb;
	float monto_comprado, monto_total = 0;
	float comb_consumidos, comb_consumidos_total = 0;
	float rend, total_rend = 0, prom_rend, mejor_rend = 0, peor_rend = 0;
	int aux = 0;

	for( i = 1; km_recorridos == -1; i++){

		while(aux != 1 || km_recorridos <= 0){
			printf("%s\n", MSJ_INGRESO_KM);
			aux = scanf("%f\n", &km_recorridos);
			if(aux != 1 || km_recorridos <= 0){
				printf("%s\n", MSJ_ERR_INVALIDO);
			}
			else if(km_recorridos == -1){
				break;
			}
		}
		if(km_recorridos == -1){
			break;
		}

		while(aux != 1 || precio_litro_comb <= 0){
			printf("%s\n", MSJ_INGRESO_PRECIO);
			aux = scanf("%f\n", &precio_litro_comb);
			if(aux != 1 || precio_litro_comb <= 0){
				printf("%s\n", MSJ_ERR_INVALIDO);
			}
		}
		while(aux != 1 || monto_comprado <= 0){
			printf("%s\n", MSJ_INGRESO_MONTO);
			aux = scanf("%f\n", &monto_comprado);
			if(aux != 1 || monto_comprado <= 0){
				printf("%s\n", MSJ_ERR_INVALIDO);
			}
		}
		rend = monto_comprado / precio_litro_comb / km_recorridos * 100;
		printf("%s %f\n", MSJ_RENDIMIENTO, rend);

		total_rend += rend;
		if (mejor_rend < rend){
			mejor_rend = rend;
		}
		else if(peor_rend > rend){
			peor_rend = rend;
		}

		km_total += km_recorridos;

		comb_consumidos = monto_comprado / precio_litro_comb;
		comb_consumidos_total += comb_consumidos;

		monto_total += monto_comprado;
	}

	prom_rend = total_rend / i;

	printf("%s %f\n", MSJ_PROM_REND, prom_rend);
	printf("\t%s %f\n", MSJ_MEJOR_REND, mejor_rend);
	printf("\t%s %f\n", MSJ_PEOR_REND, peor_rend);
	printf("%s %f\n", MSJ_KM_TOTAL, km_total);
	printf("%s %f\n", MSJ_COMB_TOTAL, comb_consumidos_total);
	printf("%s %f\n", MSJ_MONTO_TOTAL, monto_total);

	return EXIT_SUCCESS;
}
	






















