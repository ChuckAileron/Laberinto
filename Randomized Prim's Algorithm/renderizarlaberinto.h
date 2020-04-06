/* VARIABLES GLOBALES */

int set_fila[1][2];
int set_columna[1][3];

	/* RENDERIZACION DEL LABERINTO EN ASCII */

//Construye una lista con la conexiones o no-conexiones de fila y retorna la columna  en que quedo
int Construye_Sets_Fila(int SIZE, int grafoLaberinto[SIZE*SIZE][SIZE*SIZE], int x){
	int i, j, k, a;
	int cont_elementos_fila = 0;
	
	set_fila[0][0] = 0;
	set_fila[0][1] = 0;
	
	a = 0;
	k = 0;
	for(i = x; i < SIZE*SIZE; i++){
		for(j = 0; j < SIZE*SIZE; j++){
			if (i < j){
				if (cont_elementos_fila < SIZE-1){
					set_fila[0][a] = grafoLaberinto[i][j];
					cont_elementos_fila++;
					a++;
					k = j;
					break;
				}
				else if (cont_elementos_fila == SIZE-2){
					goto FULL;
				}
				else
					continue;
			}
		}
	}
	FULL: return k;
}
//Construye una lista con la conexiones o no-conexiones de una columna y retorna la fila en que quedo
int Construye_Sets_Columna(int SIZE, int grafoLaberinto[SIZE*SIZE][SIZE*SIZE], int x){
	int i, j, k, a;
	int cont_elementos_columna = 0;
	
	set_columna[0][0] = 0;
	set_columna[0][1] = 0;
	set_columna[0][2] = 0;
	
	a = 0;
	k = 0;
	for(i = x; i < SIZE*SIZE; i++){
		for(j = 0; j < SIZE*SIZE; j++){
			if (j == i + SIZE){ //Si la columna esta SIZE posiciones de la fila
				if (cont_elementos_columna < SIZE){
					set_columna[0][a] = grafoLaberinto[i][j];
					cont_elementos_columna++;
					a++;
					k = i;
					break;
				}
				else if (cont_elementos_columna == SIZE-1){
					goto FULL;
				}
				else
					continue;
			}
		}
	}
	FULL: return k;
}
//Renderiza horizontalmente
void Dibujo_Horizontal_Laberinto(int SIZE){
	int i;
	
	printf("\u2502"); //Muro izquierdo
	printf("  "); //Dos espacios
	for(i = 0; i < SIZE-1; i++){		
		if(set_fila[0][i] == 1)
			printf(" "); //Un espacio
		else
			printf("\u2502"); //Barrera
		printf("  "); //Dos espacios
	}
	printf("\u2502"); //Muro derecho
	printf("\n");
}
//Renderiza verticalmente
void Dibujo_Vertical_Laberinto(int SIZE){
	int i, j;
	
	printf("\u2502"); //Muro izquierdo
	for(i = 0; i < SIZE; i++){
		//Primera celda
		if(i == 0){
			if((set_columna[0][i] == 1) && (set_fila[0][i] == 0))
				printf("  +"); //Dos espacios
			if((set_columna[0][i] == 1) && (set_fila[0][i] == 1))
				printf("  "); //Tres espacios

			if((set_columna[0][i] == 0) && (set_fila[0][i] == 0))
				printf("\u2500\u2500+"); //Barrera
			if((set_columna[0][i] == 0) && (set_fila[0][i] == 1))
				printf("\u2500\u2500+"); //Barrera	
		}
		
		//Celdas intermedias	OJO QUE ACA HAY ERROR
		if((i < SIZE-1) && (i != 0)){
			if((set_columna[0][i] == 1) && (set_columna[0][i-1] == 1) && (set_fila[0][i] == 1))
				printf("  "); //Dos espacios
			if((set_columna[0][i] == 1) && (set_columna[0][i-1] == 1) && (set_fila[0][i] == 0))
				printf("  +"); //Dos espacios
			if((set_columna[0][i] == 1) && (set_columna[0][i-1] == 0) && (set_fila[0][i] == 1))
				printf("  "); //Dos espacios
			if((set_columna[0][i] == 1) && (set_columna[0][i-1] == 0) && (set_fila[0][i] == 0))
				printf("  +"); //Dos espacios
			
			if((set_columna[0][i] == 0) && (set_columna[0][i-1] == 1) && (set_fila[0][i-1] == 1))
				printf("+\u2500\u2500+"); //Barrera
			if((set_columna[0][i] == 0) && (set_columna[0][i-1] == 1) && (set_fila[0][i-1] == 0))
				printf("\u2500\u2500+"); //Barrera
			if((set_columna[0][i] == 0) && (set_columna[0][i-1] == 0) && (set_fila[0][i-1] == 1))
				printf("\u2500\u2500+"); //Barrera
			if((set_columna[0][i] == 0) && (set_columna[0][i-1] == 0) && (set_fila[0][i-1] == 0))
				printf("\u2500\u2500+"); //Barrera
		}
		
		//Ultima celda
		if(i == SIZE-1){
			if((set_columna[0][i] == 1) && (set_columna[0][i-1] == 1) && (set_fila[0][i-1] == 1))
				printf("+  "); //Dos espacios
			if((set_columna[0][i] == 1) && (set_columna[0][i-1] == 1) && (set_fila[0][i-1] == 0))
				printf("  "); //Dos espacios
			if((set_columna[0][i] == 1) && (set_columna[0][i-1] == 0) && (set_fila[0][i-1] == 1))
				printf("  "); //Dos espacios
			if((set_columna[0][i] == 1) && (set_columna[0][i-1] == 0) && (set_fila[0][i-1] == 0))
				printf("  "); //Dos espacios

			if((set_columna[0][i] == 0) && (set_columna[0][i-1] == 1) && (set_fila[0][i-1] == 1))
				printf("+\u2500\u2500"); //Barrera
			if((set_columna[0][i] == 0) && (set_columna[0][i-1] == 1) && (set_fila[0][i-1] == 0))
				printf("\u2500\u2500"); //Barrera
			if((set_columna[0][i] == 0) && (set_columna[0][i-1] == 0) && (set_fila[0][i-1] == 1))
				printf("\u2500\u2500"); //Barrera
			if((set_columna[0][i] == 0) && (set_columna[0][i-1] == 0) && (set_fila[0][i-1] == 0))
				printf("\u2500\u2500"); //Barrera
			
		}
	}
	printf("\u2502"); //Muro derecho
	printf("\n");
}
void Dibuja_Bordes_Sup_Inf(char opcion, int SIZE){
	int i;
	
	if (opcion == 's'){
		printf("\u250C"); //Borde superior izquierdo
		for(i = 0; i < SIZE-1; i++)
			printf("\u2500\u2500\u2500");
		printf("\u2500\u2500");
		printf("\u2510\n"); //Borde superior derecho
	}
	if (opcion == 'i'){
		printf("\u2514"); //Borde inferior izquierdo
		for(i = 0; i < SIZE-1; i++)
			printf("\u2500\u2500\u2500");
		printf("\u2500\u2500");
		printf("\u2518\n"); //Borde inferior derecho
	}
}
//Funcion principal para renderizar el laberinto
void Dibuja_Laberinto(int SIZE, int grafoLaberinto[SIZE*SIZE][SIZE*SIZE]){
	int i, j;
	int pos_fila, pos_columna;
	
	i = 0;
	j = 0;
	pos_fila = 0;
	pos_columna = 0;
	
	Dibuja_Bordes_Sup_Inf('s', SIZE);
	
	while (i < SIZE){
		pos_fila = Construye_Sets_Fila(SIZE, grafoLaberinto, pos_fila) + 1;
		Dibujo_Horizontal_Laberinto(SIZE);
		i++;
		
		if(j == SIZE-1)
			continue;
		else{
			pos_columna = Construye_Sets_Columna(SIZE, grafoLaberinto, pos_columna) + 1;
			Dibujo_Vertical_Laberinto(SIZE);
			j++;
		}
	}
	Dibuja_Bordes_Sup_Inf('i', SIZE);
}