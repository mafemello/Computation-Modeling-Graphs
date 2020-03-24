#include <stdio.h>
#include <stdlib.h>
#include "adj-matrix.h"

// Defining the structure that represents the graph
typedef struct graph {
	int n_vertex;
	int n_edge;
	int** adjacency;
} Graph;

// Creates an empty graph
Graph* CreateGraph (int num_vertex) {
	
	// Memory allocation
	Graph *G = ((Graph*) malloc(sizeof(Graph)));
	G->n_vertex = num_vertex;
	G->adjacency = ((int**) malloc(sizeof(int*)*num_vertex));
	
	// Initializing matrix
	for (int i = 0; i < num_vertex; i ++) {
		G->adjacency[i] = ((int*) malloc(sizeof(int)*num_vertex));
	}
	for (int i = 0; i < num_vertex; i ++) {
		for (int j = 0; j < num_vertex; j ++) {
			G->adjacency[i][j] = 0; // Empty matrix. There are no edges in between the vertices
		}
	}
}

// Add an edge in between two vertices, chosen by user
void AddEdge (Graph* G, int v, int w) {
	if (G->adjacency[v][w] == 0) {
		G->adjacency[v][w] = 1;
	}
}

// Remove an edge in between two vertices, chosen by user
void RemoveEdfe (Graph* G, int v, int w) {
	if (G->adjacency[v][w] == 1) {
		G->adjacency[v][w] = 0;
	}
}

// Prints the entire graph represented by adjacency matrix
void PrintGraph (Graph *G) {
	for (int v = 0; v < G->n_vertex; v ++) {
		for (int w = 0; w < G->n_vertex; w ++) {
			printf("%d ", G->adjacency[v][w]);
		}
		printf ("\n");
	}
}

// Finishes the graph and releases allocated memory
void EndsGraph (Graph *G) {
	for (int i = 0; i < G->n_vertex; i ++) {
		free (G->adjacency[i]);
	}
	free (G->adjacency);
	free (G);
}