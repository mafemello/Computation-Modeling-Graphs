#include <stdio.h>
#include <stdlib.h>
#include "adj-matrix.h"


#define WHITE 0
#define GRAY 1
#define BLACK 2

#define INFINITE 9999

// Defining the structure that represents the graph
struct graph {
    int dir; // if it is directed
    int n_vertex;  
    int** adjacency; // Double pointer that represents the entire matrix

};

Graph* CreateGraph(int n_vertex, int dir) {
    
    // Memory allocation
    Graph* G = (Graph*) malloc(sizeof(Graph));    
    G->n_vertex = n_vertex;
    G->dir = dir;
    G->adjacency = (int **) malloc(sizeof(int *) * n_vertex);
    
    // Initializing matrix
    for (int i = 0; i < n_vertex; i++) {
        G->adjacency[i] = (int *) malloc(sizeof(int) * n_vertex);
    }
    for (int i = 0; i < n_vertex; i++) {
        for (int j = 0; j < n_vertex; j++) {
            G->adjacency[i][j] = 0; // Empty matrix. There are no edges in between the vertices.
        }
    }
    return G;
}

// Add an edge in between two vertices, chosen by user
/*
    v1: origin vertex
    v2: destination vertex
    w: weight
*/
void AddEdge (Graph* G, int v1, int v2, int*** info) {
    G->adjacency[v1][v2] = info[0][v1][v2];
    if (!G->dir) G->adjacency[v2][v1] = info[0][v1][v2]; // If the graph is not directed
}

// Function returns the number of vertices in the graph
int GimmeNumberOfVertices (Graph* G) {
    return G->n_vertex;
}

// Finishes the graph and releases allocated memory
void EndsGraph (Graph* G) {
    for (int i = 0; i < G->n_vertex; i++) free(G->adjacency[i]);
    free(G->adjacency);
    free(G);
}

void invertVector (int* inverted, int* original, int size) {
    for (int i = 0; i < size; i++) {
        inverted[size-i-1] = original[i];
    }
}

void tratarInfo (Graph* G, int v1, int v2, int*** info) {
    if (G->adjacency[v1][v2] !=  info[0][v1][v2]) {
        G->adjacency[v1][v2] = 0;
        info[1][v1][v2] = 0;
    } 
}

void print (int*** info, int city, int fly){

    for (int i = 0; i < city; i++) {
        for (int j = 0; j < city; j++)
            printf("preço da aresta [%d][%d]: %d\n", i, j, info[1][i][j]);
    }   

}
 
int djikstra (Graph* G, int origin, int destiny, int*** info, int flyNumber) {
    
    Graph *aux = CreateGraph(G->n_vertex, 1);

    int vert, k, newPath, min;
    int totalPrice = 0;
    int* pathWeigth = (int*)malloc(sizeof(int)*G->n_vertex); // L
    int* previous = (int*)malloc(sizeof(int)*G->n_vertex); //A
    int* visited = (int*)malloc(sizeof(int)*G->n_vertex); //M
    int* caminho = (int*)malloc(sizeof(int)*G->n_vertex);

    for (int v = 0; v < G->n_vertex; v++) {
        visited[v] = 0; // ainda nao visitado
        previous[v] = -1; // caminho mais curto entre origem e destino
        pathWeigth[v] = INFINITE; // peso INFINITEimo 
    }

    vert = origin;
    pathWeigth[vert] = 0;
    
    // nao terminou caminho existente
    while (vert != destiny && vert != -1) { 
        for (int i = 0; i < G->n_vertex; i++) { // percore vertices adj a origem
            if (G->adjacency[vert][i] != 0 && visited[i] == 0) { //aresta existe e nao foi visitada
                newPath = pathWeigth[vert] + G->adjacency[vert][i];
                if (newPath < pathWeigth[i]) {
                    pathWeigth[i] = newPath;
                    previous[i] = vert;
                }
            }
        }
        visited[vert] = 1; // toda lista de adj de vert ja foi visitada
        min = INFINITE;
        vert = -1; // invalido
        for (int i = 0; i < G->n_vertex; i++) {
            if (visited[i] == 0 && pathWeigth[i] < min) { // escolhe vertice cuja aresta possui o menor peso
                min = pathWeigth[i]; // atualiza minimo
                vert = i; // atualiza vert
            }
        }
    } // fim do while

    // listar caminho mais curto entre origem e destino
    if (vert == destiny) { // encontrou um caminho
        //printf("caminho mais curto entre %4d e %4d tem comprimento %4d: \n", origin, destiny, pathWeigth[destiny]);
        caminho[0] = destiny;
        k = 1;
        while (vert != origin) {
            caminho[k] = previous[vert];
            vert = previous[vert];
            k++;
        }


        int resp = 0;
        int *aux = (int*)malloc(sizeof(int)*G->n_vertex);
        invertVector (aux, caminho, k);
        for (int i = 0; i <= k-1; i++) {
            if (G->adjacency[aux[i]][aux[i+1]] !=  info[0][aux[i]][aux[i+1]]) {
                G->adjacency[aux[i]][aux[i+1]] = 0;
                info[1][aux[i]][aux[i+1]] = 0;
            } 
            printf("%d ", aux[i]);
            //printf("aux[%d]: %d\n", i, aux[i]);
            //printf ("preco aqui [%d][%d]: %d\n",aux[i],aux[i+1] , info[1][aux[i]][aux[i+1]]);
            totalPrice += info[1][aux[i]][aux[i+1]];
        }


        // // // 0 1 3
        // int *aux = (int*)malloc(sizeof(int)*G->n_vertex);
        // for (int i = k-1; i >= 0; i--) {
        //     printf("%d ", caminho[i]);
        //     printf("caminho[%d]: %d\n", i, caminho[i]);
        //     totalPrice = info[1][caminho[i+1]][caminho[i]];
        // }       

        // invertVector (aux, caminho, k);
        // for (int i = 0; i <= k-1; i++) {
        //     resp += totalPrice;
        //     printf("%d ", aux[i]);
        //     printf("aux[%d]: %d\n", i, aux[i]);
        //     printf("totalPrice: %d\n",info[1][aux[i]][aux[i+1]] );
        //     printf("resp: %d\n", resp);
        // }


        // for (int i = k; i >= 0; i--) {
        //     printf("%d ", caminho[i]);
        //     printf("caminho[%d]: %d\n", i, caminho[i]);
        //     totalPrice += info[1][caminho[i+1]][caminho[i]];
        // } 


        printf("\n%d %d\n", pathWeigth[destiny], totalPrice);



    }

    free (pathWeigth);
    free (previous);
    free (visited);
    free (caminho);







}