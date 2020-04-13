// ADT - Adjacency list
// Non-oriented and weightless graph

#include <stdio.h>
#include <stdlib.h>
#include "adj-list.h"

struct node {
	int adjacency;
	Node *next;
};

struct list {
	int numVertex;
	Node** list;
};

// Creates an empty graph
List* CreateGraph (int numVertex) {
	List* G = ((List*)malloc(sizeof(List)));
	
	G->numVertex = numVertex;
	G->list = ((Node**)malloc(sizeof(Node*)*numVertex));

	for (int i = 0; i < numVertex; i ++) {
		G->list[i] = ((Node*)malloc(sizeof(Node)));
		// Initializing empty list
		G->list[i]->adjacency = 0;
		G->list[i]->next = NULL;
	}
	return G;
}

// Add an edge in between two vertices, chosen by user
void AddEdge (List *G, int vertex1, int vertex2) {
	Node* aux_v1 = G->list[vertex1];
	Node* aux2_v1 = G->list[vertex1]->next;

	Node* aux_v2 = G->list[vertex2];
	Node* aux2_v2 = G->list[vertex2]->next;

	while (aux2_v1 != NULL) { // scrolls through the list
		if (aux2_v1->adjacency == vertex2) {
			return;
		}
		aux_v1 = aux2_v1;
		aux2_v1 = aux2_v1->next;
	}

	if (aux2_v1 == NULL) { // empty list
		aux_v1->next = ((Node*)malloc(sizeof(Node)));
		aux_v1->next->adjacency = vertex2;
		aux_v1->next->next = NULL;
	} else {
		aux_v1->next = (Node*)(malloc(sizeof(Node)));
		aux_v1->next->adjacency = vertex2;
		aux_v1->next->next = aux2_v1;
	}

	
	while (aux2_v2 != NULL) { // scrolls through the list
		if (aux2_v2->adjacency == vertex1) {
			return;
		}
		aux_v2 = aux2_v2;
		aux2_v2 = aux2_v2->next;
	}

	if (aux2_v2 == NULL) { // empty list
		aux_v2->next = ((Node*)malloc(sizeof(Node)));
		aux_v2->next->adjacency = vertex1;
		aux_v2->next->next = NULL;
	} else {
		aux_v2->next = (Node*)(malloc(sizeof(Node)));
		aux_v2->next->adjacency = vertex1;
		aux_v2->next->next = aux2_v2;
	}


}

// Remove an edge in between two vertices, chosen by user
void RemoveEdge (List *G, int vertex1, int vertex2) {
	Node* aux_v1 = G->list[vertex1];
	Node* aux2_v1 = G->list[vertex1]->next;

	Node* aux_v2 = G->list[vertex2];
	Node* aux2_v2 = G->list[vertex2]->next;

	while (aux2_v1 != NULL && aux2_v1->adjacency != vertex2) { // scrolls through the list until it finds vertex 2
		aux_v1 = aux2_v1;
		aux2_v1 = aux2_v1->next;
	}

	if (aux2_v1 != NULL) {
		aux_v1->next = aux2_v1->next;
		aux2_v1->next = NULL;
		free (aux2_v1);
	} else {
		return;
	}


	while (aux2_v2 != NULL && aux2_v2->adjacency != vertex1) { // scrolls through the list until it finds vertex 2
		aux_v2 = aux2_v2;
		aux2_v2 = aux2_v2->next;
	}

	if (aux2_v2 != NULL) {
		aux_v2->next = aux2_v2->next;
		aux2_v2->next = NULL;
		free (aux2_v2);
	} else {
		return;
	}
}

// Prints the entire graph represented by adjacency list
void PrintGraph (List *G) {
	Node* aux;

	for (int i = 0; i < G->numVertex; i++) {
		aux = G->list[i]->next;
		printf("%d: ", i);
		while (aux != NULL) {
			printf("%d ", aux->adjacency);
			aux = aux->next;
		}
		printf("\n");
	}
	printf("\n");
}

// Finishes the graph and releases allocated memory
void EndsGraph (List *G) {
	Node* aux;

	for (int i = 0; i < G->numVertex; i ++) { // removes all the edges
		aux = G->list[i]->next;
		while (aux != NULL) {
			RemoveEdge (G, i, aux->adjacency);
			aux = G->list[i]->next;
		}
	}

	for (int i = 0; i < G->numVertex; i++) {
		free (G->list[i]);
	}
	free (G->list);
	free (G);
	G = NULL;
}