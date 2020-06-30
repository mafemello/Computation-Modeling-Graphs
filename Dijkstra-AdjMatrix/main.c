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

	/*
		The triple pointer info is responsible to keep duration and price in between two vertex.
		It's the duration and price of and edge.
			info[0][v1][v2] --> duration (between vertices 1 and 2)
            info[1][v1][v2] --> price (between vertices 1 and 2)
	*/
	// Memory allocation 
	int ***info = (int***)calloc(2, sizeof(int**));
	for (int i = 0; i < 2; i++) {
		info[i] = (int**)calloc(cityNumber, sizeof(int*));;
		for (int j = 0; j < cityNumber; j++) {
			info[i][j] = (int*)calloc(cityNumber, sizeof(int));
		}
	}
	// receiving data
	for (int i = 0; i < flyNumber; i++) {
		scanf ("%d %d %d %d", &firstVertex, &adjVertex, &duration, &price);
		info[0][firstVertex][adjVertex] = duration;
		info[1][firstVertex][adjVertex] = price;
		AddEdge (G, firstVertex, adjVertex, info); // adds the edge and the costs
		// the matrix is going to keep the duration, only
		// G->adjacency[v][w] = info[0][v][w];
	}
	
	// Auxiliar function that sets to 0 the price if there are no edges in between two vertices
	correctsInfo (G, firstVertex, adjVertex, info);
	scanf ("%d %d", &origin, &destiny); // he fastest way and the costs between these two vertices
	//print (info, cityNumber); // just an auxiliar function to check if everything is okay :)
	
	djikstra (G, origin, destiny, info); // calculates shortest path, print the path and it's costs.
	EndsGraph (G); // realeses allocated memory



	return 0;
}