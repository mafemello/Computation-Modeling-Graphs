// ADT - Adjacency list
// Non-oriented and weightless graph

#include <stdio.h>
#include <stdlib.h>
#include "adj-list.h"

#define MAX 10000

struct node {
	int adjacency;
	int duration;
	int price;
	int antecessor;
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
		G->list[i]->duration = 0;
		G->list[i]->price = 0;
		G->list[i]->antecessor = -1; 
		G->list[i]->next = NULL;
	}
	return G;
}

// Add an edge in between two vertices, chosen by user
void AddEdge (List *G, int vertex1, int vertex2, int duration, int price) {
	Node* aux_v1 = G->list[vertex1];
	Node* aux2_v1 = G->list[vertex1]->next;

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
		aux_v1->next->duration = duration;
		aux_v1->next->price = price;
		aux_v1->next->antecessor = vertex1;
		aux_v1->next->next = NULL;
	} else {
		aux_v1->next = (Node*)(malloc(sizeof(Node)));
		aux_v1->next->adjacency = vertex2;
		aux_v1->next->duration = duration;
		aux_v1->next->price = price;
		aux_v1->next->antecessor = vertex1;
		aux_v1->next->next = aux2_v1;
	}

}

// Remove an edge in between two vertices, chosen by user
void RemoveEdge (List *G, int vertex1, int vertex2) {
	Node* aux_v1 = G->list[vertex1];
	Node* aux2_v1 = G->list[vertex1]->next;

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

void dijkstra (List* G, int origin, int destiny) {
	int* dist = (int*)malloc(sizeof(int)*G->numVertex);
	int* antecessor = (int*)malloc(sizeof(int)*G->numVertex);
	int* filaInicial = (int*)malloc(sizeof(int)*G->numVertex);
	int* filaPrioridade = (int*)malloc(sizeof(int)*G->numVertex);
	for (int v = 0; v < G->numVertex; v++) {
		G->list[v]->duration = MAX;
		G->list[v]->price = MAX;
		G->list[v]->antecessor = -1;
	}
	dist[origin] = 0;
	filaInicial = NULL;

	// cria fila de prioridade com vertices do grafos
	for (int i = 0; i < G->numVertex; i++) {
		aux = G->list[i]->next;
		while (aux != NULL) {
			filaPrioridade[i] = aux[i];
			aux = G->list[i]->next;
		}
	}

	while (filaPrioridade != NULL) {
		
	}


}