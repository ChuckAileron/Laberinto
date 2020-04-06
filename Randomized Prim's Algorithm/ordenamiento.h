	/* FUNCIONES DE ORDENAMIENTO */

//Ordena las matrices de coordenadas de forma descendente
void OrdenaMatrizCoordenadas(int array[][2], int SIZE){
	int i, j, x, temp;
	int k=0;
	
	for(i = 0; i < SIZE*SIZE; i++){
		for(j = i+1; j < SIZE*SIZE; j++){
			if(array[i][k] < array[j][k]){
				for(x = 0; x < 2; x++) {
					temp = array[i][x];
					array[i][x] = array[j][x];
					array[j][x] = temp;
				}
			}
		}
	}
}
//Ordena las matrices de coordenadas de forma descendente
void OrdenaVecinos(int array[4][2]){
	int i, j, x, temp;
	int k=0;
	
	for(i = 0; i < 4; i++){
		for(j = i+1; j < 4; j++){
			if(array[i][k] < array[j][k]){
				for(x = 0; x < 2; x++) {
					temp = array[i][x];
					array[i][x] = array[j][x];
					array[j][x] = temp;
				}
			}
		}
	}
}