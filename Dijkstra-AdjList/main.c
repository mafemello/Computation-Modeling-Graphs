/*
	Graphs - forth activity	
	Maria Fernanda Lucio de Mello
	nUSP: 11320860
*/

#include <stdio.h>
#include <stdlib.h>
#include "adj-list.h"

int main (void) {

	int cityNumber; // vertices
	int flyNumber; // edges
	int firstVertex, adjVertex, duration, price, origin, destiny;

	scanf ("%d %d", &cityNumber, &flyNumber);

	List *G = CreateGraph (cityNumber);

	for (int i = 0; i < flyNumber; i++) {
		scanf ("%d %d %d %d", &firstVertex, &adjVertex, &duration, &price);
		AddEdge (G, firstVertex, adjVertex, duration, price); // adds the edge and the costs
	}
	scanf ("%d %d", &origin, &destiny); // she wants to know the fastest way and the costs

	djikstra (G, origin, destiny);


	return 0;
}