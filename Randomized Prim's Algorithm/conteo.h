	/* FUNCIONES DE CONTEO */

//Cuenta las eldas disponibles en la matriz de coordenadas
int CuentaCoordenadas(int caso, int array[][2], int n){
	int i;
	int cont = 0;
	
	//Caso para celdasFrontera / celdasAgregadas
	if(caso == 1){
		for (i = 0; i < n; i++){
			if ((array[i][0] != -1) && (array[i][1] != -1))
				cont++;
		}
	}
	//Caso para vecinos
	if(caso == 2){
		for (i = 0; i < n; i++){
			if ((array[i][0] != -2) && (array[i][1] != -2))
				cont++;
		}
	}
	if (cont > 0)
		return cont;
	else
		return 0;
}
