// ADT - Adjacency list
// Non-oriented and weightless graph

#include <stdio.h>
#include <stdlib.h>
#include "adj-list.h"

int main (void) {

	int v, w;
	int num_vertex;
	int num_edge;
	int num_op;
	int operation;
	int *v1 = ((int*) malloc(sizeof(int)));
	int *v2 = ((int*) malloc(sizeof(int)));
	List *G;


//	printf ("How many vertices and edges are there in the graph?\n");
	scanf ("%d %d", &num_vertex, &num_edge);
	
// Creates the graph and 
	G = CreateGraph (num_vertex);

//	printf ("Now choose which vertices these %d edges connect: \n", num_edge);
	for (int i = 0; i < num_edge; i++) {
		scanf ("%d", &v1[i]);
		scanf ("%d", &v2[i]);
		AddEdge (G, v1[i], v2[i]);
	}

//	printf("How many operations are going to be executed?\n");
	scanf ("%d", &num_op);

	for (int i = 0; i < num_op; i ++) {
		scanf ("%d", &operation);

		switch (operation) {
			case 1: // Add edges
//				printf ("You want to add new edges. Between which vertices?\n");
				scanf ("%d %d", &v, &w);
				AddEdge (G, v, w);
				break;

			case 2: // Remove edge
//				printf ("You want to remove edges. Between which vertices?\n");
				scanf ("%d %d", &v, &w);
				RemoveEdge (G, v, w);
				break;

			case 3: // Print matrix
//			printf ("Ok, let's print the matrix.\n");
			PrintGraph (G);
			break;
		}
	}

	EndsGraph (G);
	return 0;
}








