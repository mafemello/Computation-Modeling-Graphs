#include <stdio.h>
#include <stdlib.h>
#include "adj-matrix.h"

int main (void) {

	int num_vertex;
	int num_edge;
	int v1, v2;
	Graph *G;

	printf ("How many vertices are there in your graph?\n");
	scanf ("%d", &num_vertex);
	CreateGraph (num_vertex);

	printf ("Do you want to add an edge in between which vertices?\n");
	scanf ("%d %d", &v1, &v2);
	AddEdge (G, v1, v2);

	printf ("Let's print the current graph!\n");
	PrintGraph (G);

	return 0;
}