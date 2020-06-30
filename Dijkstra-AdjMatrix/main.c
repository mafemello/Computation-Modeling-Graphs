/*
	Graphs - forth activity	
	Maria Fernanda Lucio de Mello
	nUSP: 11320860
*/

#include <stdio.h>
#include <stdlib.h>
#include "adj-matrix.h"

int main (void) {

	int cityNumber; // vertices
	int flyNumber; // edges
	int firstVertex, adjVertex, duration, price, origin, destiny;

	scanf ("%d %d", &cityNumber, &flyNumber);

	Graph *G = CreateGraph (cityNumber, 1);

	int ***info = (int***)calloc(2, sizeof(int**));
	for (int i = 0; i < cityNumber; i++) {
		info[i] = (int**)calloc(cityNumber, sizeof(int*));;
		for (int j = 0; j < flyNumber; j++) {
			info[i][j] = (int*)calloc(flyNumber, sizeof(int));
		}
	}
	for (int i = 0; i < flyNumber; i++) {
		scanf ("%d %d %d %d", &firstVertex, &adjVertex, &duration, &price);
		info[0][firstVertex][adjVertex] = duration;
		info[1][firstVertex][adjVertex] = price;
		AddEdge (G, firstVertex, adjVertex, info); // adds the edge and the costs
	}
		tratarInfo (G, firstVertex, adjVertex, info);



	scanf ("%d %d", &origin, &destiny); // she wants to know the fastest way and the costs
	//print (info, cityNumber, flyNumber);
	djikstra (G, origin, destiny, info, flyNumber);
	//EndsGraph (G);


	return 0;
}