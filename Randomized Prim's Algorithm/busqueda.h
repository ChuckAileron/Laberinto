	/* FUNCIONES DE BUSQUEDA */

//Dada una coordenada (x, y), busca la posicion de la celda en el grafo de adyacencia
int Busca_Posicion_Elemento_Grafo_con_respecto_Celda_en_Matriz(int x, int y, int SIZE){
	int i, j;
	int pos = 0;
	
	//printf("Estoy buscando la posicion del elemento del grafo\n");
	//printf("x = %d\ty= %d\n", x, y);
	
	if ((x == 0) && (y == 0)){
		//printf("SI encontre la pos elemento y es 0\n\n");
		return 0;
	}
	if ((i == SIZE) && (y == SIZE)){
		//printf("SI encontre la pos elemento y es %d\n\n", SIZE*SIZE);
		return SIZE*SIZE;
	}
	
	for (i = 0; i < SIZE; i++){
		for (j = 0; j < SIZE; j++){
			if((i == x) && (j == y)){
				//printf("SI encontre la pos elemento y es %d\n\n", pos);
				return pos;
			}
			else
				pos++;
    	}
	}
	//printf("NO encontre la pos elemento, entonces pos = -1\n\n");
	return -1;
}
//Dada una celda frontera cF, busca la posicion de fila en que se encuentra en celdasFrontera
int Busca_Posicion_fila_cF_en_celdasFrontera(int cF[1][2], int celdasFrontera[][2], int SIZE){
	int i;
	
	for(i = 0; i < SIZE*SIZE; i++){
		if((cF[0][0] == celdasFrontera[i][0]) && (cF[0][1] == celdasFrontera[i][1]))
			return i;
	}
	return 0;
}
//Dada una coordenada (x,y) verifica si ya fue marcada como celda frontera
int Busca_Coordenada_en_celdasFrontera(int x, int y, int celdasFrontera[][2], int SIZE){
	int i;
	
	for(i = 0; i < SIZE*SIZE; i++){
		if((x == celdasFrontera[i][0]) && (y == celdasFrontera[i][1]))
			return 1;
	}
	return 0;
}