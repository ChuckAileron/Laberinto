	/* FUNCIONES DE INICIALIZACION */

//Inicia Grafo
void IniciaGrafo(int SIZE, int grafoLaberinto[SIZE*SIZE][SIZE*SIZE]){
	int i, j;
	
    for(i = 0; i < SIZE*SIZE; i++){
		for(j = 0; j < SIZE*SIZE; j++){
			grafoLaberinto[i][j] = 0;
		}
	}
}
//Inicia matrices
void IniciaMatriz(int SIZE, int matriz[SIZE][SIZE], int celdasFrontera[][2], int celdasAgregadas[][2]){
	int i, j;
	
    for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++)
			matriz[i][j] = 0;
	}
	for(i = 0; i < (SIZE*SIZE); i++){
		for(j = 0; j < 2; j++){
			celdasAgregadas[i][j] = -1;
			celdasFrontera[i][j] = -1;
		}
	}
}
//Inicia la lista de vecinos con -1
void IniciaVecinos(int array[4][2]){
	int i, j;
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 2; j++){
			array[i][j] = -2;
		}
	}
}