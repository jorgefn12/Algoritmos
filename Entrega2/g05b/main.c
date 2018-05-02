#include <stdio.h>
#include <stdlib.h>

int main(void){
	int matriz[3][4] = {{ 1, 2, 3, 4}, { 5, 6, 7, 8}, { 9,10,11,12}};
	int * ptr;
	int (*ptr2vector)[4];
	int fila, col;
	size_t i,j;

	ptr = *matriz;
	ptr2vector = *matriz;

	fila = sizeof(matriz)/sizeof(*matriz);
	col = sizeof(*matriz)/sizeof(**matriz);

	for (i = 0; i < fila * col; i++){
		printf("%d ",(int) *(ptr+i) );
	}
	putchar('\n');

	for (i = 0; i < fila; i++){
		for(j = 0; j < col; j++){
			printf("%d ", *((*(ptr2vector+i))+j));
		}
	}
	putchar('\n');


	return EXIT_SUCCESS;
}