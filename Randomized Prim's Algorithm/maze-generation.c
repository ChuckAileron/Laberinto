/*
Pseudocodigo:
1. Escoger una celda de inicio random del laberinto
2. Añadir la celda de inicio a la (por ahora vacía) lista celdasAgregadas
3. Marcar las celdas vecinas a la celda de inicio y añadirlas a la lista celdasFrontera
4. Mientras celdasFrontera no sea solo ceros (es decir, existan celdas frontera):
	a) Elegir aleatoriamente una celda frontera (cF) de celdasFrontera
	b) Elegir aleatoriamente una celda ya agregada en laberinto (cI) adyacente a cF
	c) Añadir cF a la lista de celdasAgregadas
	d) Marcar todas las celdas vecinas a cF aun sin marcar como frontera y agregarlas a la lista celdasFrontera
	e) Añadir la coordenada de adyacencia entre cF y cI a grafoLaberinto
	f) Eliminar cF de la lista celdasFrontera
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "imprimir.h"
#include "inicio.h"
#include "renderizarlaberinto.h"
#include "ordenamiento.h"
#include "busqueda.h"
#include "conteo.h"

#define SIZE 24


	/* VARIABLES GLOBALES */

int cant_celdasFrontera = 1;
int matriz[SIZE][SIZE];
int grafoLaberinto[SIZE*SIZE][SIZE*SIZE];
int celdasAgregadas[SIZE*SIZE][2];
int celdasFrontera[SIZE*SIZE][2];
int set_fila[1][2];
int set_columna[1][3];
int vecinos[4][2];
int vecinos_de_cF[4][2];
int adyacentes_a_celdas_agregadas[4][2];
int cI_Elegido[1][2];


	/* FUNCIONES DE MARCADO */

//Revisa los muros vecinos marcandolos en la lista y los agrega a la matriz celdasFrontera
void MarcaVecinos(int caso, int x, int y, int matriz[SIZE][SIZE], int celdasFrontera[][2]){
	int i;
	IniciaVecinos(vecinos);
	IniciaVecinos(adyacentes_a_celdas_agregadas);

	//Caso 1: Buscar vecinos de celda frontera elegida
	if (caso == 1){
		//Arriba
		if ((y > 0) && (matriz[x][y-1] == 0)){
			vecinos[0][0] = x;
			vecinos[0][1] = y-1;
			if (Busca_Coordenada_en_celdasFrontera(x, y-1, celdasFrontera, SIZE) == 0){
				celdasFrontera[(SIZE*SIZE)-4][0] = x;
				celdasFrontera[(SIZE*SIZE)-4][1] = y-1;
			}
		}
		//Abajo
		if ((y < (SIZE-1)) && (matriz[x][y+1] == 0)){
			vecinos[1][0] = x;
			vecinos[1][1] = y+1;
			if (Busca_Coordenada_en_celdasFrontera(x, y+1, celdasFrontera, SIZE) == 0){
				celdasFrontera[(SIZE*SIZE)-3][0] = x;
				celdasFrontera[(SIZE*SIZE)-3][1] = y+1;
			}
		}
		//Izquierda
		if ((x > 0) && (matriz[x-1][y] == 0)){
			vecinos[2][0] = x-1;
			vecinos[2][1] = y;
			if (Busca_Coordenada_en_celdasFrontera(x-1, y, celdasFrontera, SIZE) == 0){
				celdasFrontera[(SIZE*SIZE)-2][0] = x-1;
				celdasFrontera[(SIZE*SIZE)-2][1] = y;
			}
		}
		//Derecha
		if ((x < (SIZE-1)) && (matriz[x+1][y] == 0)){
			vecinos[3][0] = x+1;
			vecinos[3][1] = y;
			if (Busca_Coordenada_en_celdasFrontera(x+1, y, celdasFrontera, SIZE) == 0){
				celdasFrontera[SIZE*SIZE-1][0] = x+1;
				celdasFrontera[SIZE*SIZE-1][1] = y;
			}
		}
	}
	//Caso 2: Buscar vecinos de celda frontera que incluyan celdas agregadas
	if (caso == 2){
		//Arriba
		if ((y > 0) && (matriz[x][y-1] == 1)){
			adyacentes_a_celdas_agregadas[0][0] = x;
			adyacentes_a_celdas_agregadas[0][1] = y-1;
		}
		//Abajo
		if ((y < (SIZE-1)) && (matriz[x][y+1] == 1)){
			adyacentes_a_celdas_agregadas[1][0] = x;
			adyacentes_a_celdas_agregadas[1][1] = y+1;
		}
		//Izquierda
		if ((x > 0) && (matriz[x-1][y] == 1)){
			adyacentes_a_celdas_agregadas[2][0] = x-1;
			adyacentes_a_celdas_agregadas[2][1] = y;
		}
		//Derecha
		if ((x < (SIZE-1)) && (matriz[x+1][y] == 1)){
			adyacentes_a_celdas_agregadas[3][0] = x+1;
			adyacentes_a_celdas_agregadas[3][1] = y;
		}
	}
	OrdenaVecinos(vecinos);
	OrdenaVecinos(adyacentes_a_celdas_agregadas);
	OrdenaMatrizCoordenadas(celdasFrontera, SIZE);
}
//Busca vecinos de cF que coincidan con celdas ya agregadas
void Vecino_Coincide_en_celdasAgregadas(int celdasAgregadas[][2]){
	int i, j, aux, random;

	j = 0;
	OrdenaVecinos(vecinos);
	IniciaVecinos(vecinos_de_cF);
	
	for(i = 0; i < SIZE*SIZE; i++){
		//Primer vecino (arriba)
		if((adyacentes_a_celdas_agregadas[0][0] == celdasAgregadas[i][0]) && (adyacentes_a_celdas_agregadas[0][1] == celdasAgregadas[i][1])){
			vecinos_de_cF[j][0] = adyacentes_a_celdas_agregadas[0][0];
			vecinos_de_cF[j][1] = adyacentes_a_celdas_agregadas[0][1];
			j++;
		}
		//Segundo vecino (abajo)
		if((vecinos[1][0] == celdasAgregadas[i][0]) && (vecinos[1][1] == celdasAgregadas[i][1])){
			vecinos_de_cF[j][0] = adyacentes_a_celdas_agregadas[1][0];
			vecinos_de_cF[j][1] = adyacentes_a_celdas_agregadas[1][1];
			j++;
		}
		//Tercero vecino (izquierda)
		if((vecinos[2][0] == celdasAgregadas[i][0]) && (vecinos[2][1] == celdasAgregadas[i][1])){
			vecinos_de_cF[j][0] = adyacentes_a_celdas_agregadas[2][0];
			vecinos_de_cF[j][1] = adyacentes_a_celdas_agregadas[2][1];
			j++;
		}
		//Cuarto vecino (derecha)
		if((vecinos[3][0] == celdasAgregadas[i][0]) && (vecinos[3][1] == celdasAgregadas[i][1])){
			vecinos_de_cF[j][0] = adyacentes_a_celdas_agregadas[3][0];
			vecinos_de_cF[j][1] = adyacentes_a_celdas_agregadas[3][1];
			j++;
		}
	}
	OrdenaVecinos(vecinos_de_cF);
	aux = CuentaCoordenadas(2, vecinos_de_cF, 4);
	random = (rand() % (int)aux);
	
	cI_Elegido[0][0] = vecinos_de_cF[random][0];
	cI_Elegido[0][1] = vecinos_de_cF[random][1];
}


	/* FUNCION CONSTRUCCION DE LABERINTO */

//Construye aleatoriamente el grafo laberinto por medio del algoritmo de Prim
void ConstruirLaberinto(int matriz[SIZE][SIZE], int celdasFrontera[][2], int celdasAgregadas[][2]){
	int i;
	int aux, random;
	int posicionCeldaVecina;
	int cF[1][2]; //Celda Frontera
	int cI[1][2]; //Celda in-Labyrinth
	int grafo_cF, grafo_cI, pos_cF;
	
	//Buscar una celda frontera aleatoria
	aux = CuentaCoordenadas(1, celdasFrontera, SIZE*SIZE); //Cuenta las celdas en frontera para acotar la busqueda random
	random = (rand() % (int)aux);
	
	if (aux == 1){ //Si queda solo una celda frontera
		cF[0][0] = celdasFrontera[0][0];
		cF[0][1] = celdasFrontera[0][1];
	}
	else{ //Si quedan mas de una celda frontera
		random = (rand() % (int)aux);
		cF[0][0] = celdasFrontera[random][0];
		cF[0][1] = celdasFrontera[random][1];
	}
	
	//Buscar una celda en laberinto adyacente a la celda frontera anterior (cF)
	aux = CuentaCoordenadas(1, celdasAgregadas, SIZE*SIZE); //Cuenta las celdas ya agregadas para acotar la busqueda random
	if (aux == 1){ //Si existe solo una celda agregada
		cI[0][0] = celdasAgregadas[0][0];
		cI[0][1] = celdasAgregadas[0][1];
		
		//Agrega cF a celdasAgregadas
		matriz[cF[0][0]][cF[0][1]] = 1;
		celdasAgregadas[(SIZE*SIZE)-1][0] = cF[0][0];
		celdasAgregadas[(SIZE*SIZE)-1][1] = cF[0][1];
		OrdenaMatrizCoordenadas(celdasAgregadas, SIZE); //Ordena celdasAgregadas
		
		//Marca los vecinos de cF y los agrega a celdasFrontera
		MarcaVecinos(1, cF[0][0], cF[0][1], matriz, celdasFrontera);
		
		//Agrega la coordenada de adyacencia de cF y cI a grafoLaberinto		
		grafo_cF = Busca_Posicion_Elemento_Grafo_con_respecto_Celda_en_Matriz(cF[0][0], cF[0][1], SIZE);
		grafo_cI = Busca_Posicion_Elemento_Grafo_con_respecto_Celda_en_Matriz(cI[0][0], cI[0][1], SIZE);		
		grafoLaberinto[grafo_cF][grafo_cI] = 1;
		grafoLaberinto[grafo_cI][grafo_cF] = 1;		

		//Elimina cF de celdasFronteras
		pos_cF = Busca_Posicion_fila_cF_en_celdasFrontera(cF, celdasFrontera, SIZE);
		celdasFrontera[pos_cF][0] = -1;
		celdasFrontera[pos_cF][1] = -1;
		OrdenaMatrizCoordenadas(celdasFrontera, SIZE);
	}
	else{ //Si existen mas de una celda agregada
		//Marca los vecinos de cF y los agrega a celdasFrontera
		MarcaVecinos(1, cF[0][0], cF[0][1], matriz, celdasFrontera);
		MarcaVecinos(2, cF[0][0], cF[0][1], matriz, celdasFrontera);
		
		//Busca aleatoriamente una celda agregada adyacente a un vecino de cF
		Vecino_Coincide_en_celdasAgregadas(celdasAgregadas);
		cI[0][0] = cI_Elegido[0][0];
		cI[0][1] = cI_Elegido[0][1];
			
		//Agrega cF a celdasAgregadas
		matriz[cF[0][0]][cF[0][1]] = 1;
		celdasAgregadas[(SIZE*SIZE)-1][0] = cF[0][0];
		celdasAgregadas[(SIZE*SIZE)-1][1] = cF[0][1];
		OrdenaMatrizCoordenadas(celdasAgregadas, SIZE); //Ordena celdasAgregadas
		
		//Agrega la coordenada de adyacencia de cF y cI a grafoLaberinto
		grafo_cF = Busca_Posicion_Elemento_Grafo_con_respecto_Celda_en_Matriz(cF[0][0], cF[0][1], SIZE);
		grafo_cI = Busca_Posicion_Elemento_Grafo_con_respecto_Celda_en_Matriz(cI[0][0], cI[0][1], SIZE);
		grafoLaberinto[grafo_cF][grafo_cI] = 1;
		grafoLaberinto[grafo_cI][grafo_cF] = 1;
		
		//Elimina cF de celdasFronteras
		pos_cF = Busca_Posicion_fila_cF_en_celdasFrontera(cF, celdasFrontera, SIZE);
		celdasFrontera[pos_cF][0] = -1;
		celdasFrontera[pos_cF][1] = -1;
		OrdenaMatrizCoordenadas(celdasFrontera, SIZE);
	}
	cant_celdasFrontera = CuentaCoordenadas(1, celdasFrontera, SIZE*SIZE); //Verifica si quedan celdas frontera
}


	/* FUNCION PRINCIPAL*/

int main(int argc, char* argv[]){
	int x, y;
	
	IniciaMatriz(SIZE, matriz, celdasFrontera, celdasAgregadas);
	IniciaVecinos(vecinos_de_cF);
	IniciaGrafo(SIZE, grafoLaberinto);
	
	//Celda inicial aleatoria
	srand(time(NULL));
	x = (rand() % (int)SIZE);
	y = (rand() % (int)SIZE);
	
	//Agrega el camino al final del arreglo
	celdasAgregadas[(SIZE*SIZE)-1][0] = x;
	celdasAgregadas[(SIZE*SIZE)-1][1] = y;
	matriz[x][y] = 1;
	
	OrdenaMatrizCoordenadas(celdasAgregadas, SIZE); //Ordena celdasAgregadas
	MarcaVecinos(1, x, y, matriz, celdasFrontera); //Busca los vecinos y los agrega a celdasFronteras
	
	while (cant_celdasFrontera > 0){
		ConstruirLaberinto(matriz, celdasFrontera, celdasAgregadas); //Avanza en la construccion del laberinto
	}
	
	//ImprimeGrafoAdyacencia(SIZE, grafoLaberinto);
	Dibuja_Laberinto(SIZE, grafoLaberinto);
	return 0;
}