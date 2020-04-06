	/* FUNCIONES DE IMPRESION */

//Imprime la matriz de adyacencia del laberinto
void ImprimeGrafoAdyacencia(int SIZE, int grafoLaberinto[SIZE*SIZE][SIZE*SIZE]){
	int i, j;
	
	for(i = 0; i < SIZE*SIZE; i++){
		for(j = 0; j < SIZE*SIZE; j++){
			printf("%d ", grafoLaberinto[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
//Imprime la matriz de celdas agregadas
void ImprimeMatriz(int SIZE, int matriz[SIZE][SIZE], int celdasAgregadas[][2]){
	int i, j;
	
	printf("Matriz Agregados\n");
	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
	printf("\nCoordenadas Agregadas\n");
	for(i = 0; i < SIZE*SIZE; i++){
		if((celdasAgregadas[i][0] != -1) && (celdasAgregadas[i][1] != -1))
			printf("(%d, %d)\n", celdasAgregadas[i][0], celdasAgregadas[i][1]);
	}
	printf("\n");
}
//Imprime las celdas frontera
void ImprimeCeldaFrontera(int SIZE, int celdasFrontera[][2]){
	int i;
	
	printf("celdasFrontera\n");
	for(i=0; i<SIZE*SIZE; i++){
		if((celdasFrontera[i][0] != -1) && (celdasFrontera[i][1] != -1))
			printf("(%d, %d)\n", celdasFrontera[i][0], celdasFrontera[i][1]);
	}
	printf("\n");
}
//Imprime los vecinos alrededor de unas coordenadas (x, y)
void ImprimeVecinos(int arrayVecinos[][2], int x, int y){
	int i;
	
	printf("\nVecinos de (%d, %d)\n", x, y);
	printf("-------------------\n");
	for(i=0; i<4; i++)
		printf("(%d, %d)\n", arrayVecinos[i][0], arrayVecinos[i][1]);
	printf("\n");
}