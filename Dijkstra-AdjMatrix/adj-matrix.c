#include <stdio.h>
#include <stdlib.h>
#include "adj-matrix.h"

#define INFINITE 9999

// Defining the structure that represents the graph
struct graph {
    int dir; // If it is directed
    int n_vertex;  
    int** adjacency; // Double pointer that represents the entire matrix

};

// Creates the graph
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
    info: weight
        info[0][v1][v2] ==> keeps the duration of the fly (between the two vertices)
        info[1][v1][v2] ==> keeps the price of the fly (between the two vertices)
*/
void AddEdge (Graph* G, int v1, int v2, int*** info) {
    G->adjacency[v1][v2] = info[0][v1][v2]; // matrix keeps the duration (that is on the triple pointer)
    if (!G->dir) G->adjacency[v2][v1] = info[0][v1][v2]; // If the graph is not directed
}

// Function returns the number of vertices in the graph
int GimmeNumberOfVertices (Graph* G) {
    return G->n_vertex;
}

// Finishes the graph and releases allocated memory
void EndsGraph (Graph* G) {
    for (int i = 0; i < G->n_vertex; i++) {
        free(G->adjacency[i]);
    } 
    free(G->adjacency);
    free(G);
}

// Auxiliar function to invert de path vector to print it correctly :)
void invertVector (int* inverted, int* original, int size) {
    for (int i = 0; i < size; i++) {
        inverted[size-i-1] = original[i];
    }
}

// Auxiliar function that sets to 0 the price if there are no edges in between two vertices
void correctsInfo (Graph* G, int v1, int v2, int*** info) {
    if (G->adjacency[v1][v2] !=  info[0][v1][v2]) { 
        G->adjacency[v1][v2] = 0; // sets duration to 0
        info[1][v1][v2] = 0; // sets price to 0
    } 
}

// Auxiliar function to verify if the prices are correctly kept
void print (int*** info, int city){
    for (int i = 0; i < city; i++) {
        for (int j = 0; j < city; j++)
            printf("preço da aresta [%d][%d]: %d\n", i, j, info[1][i][j]);
    }   
}
 
// Djikstra function to find the path with the shortest duration
/*
    - Graph* G ==> graph
    - int origin ==> source vertex
    - int destiny ==> destiny vertex
    - int*** info ==> triple pointer that keeps duration and price of an edge
            info[0][v1][v2] --> duration (between vertices 1 and 2)
            info[1][v1][v2] --> price (between vertices 1 and 2)

*/
int djikstra (Graph* G, int origin, int destiny, int*** info) {
    
    int vert, k, newPath, min;
    int totalPrice = 0;
    int* pathWeigth = (int*)malloc(sizeof(int)*G->n_vertex); 
    int* previous = (int*)malloc(sizeof(int)*G->n_vertex); 
    int* visited = (int*)malloc(sizeof(int)*G->n_vertex); 
    int* finalPath = (int*)malloc(sizeof(int)*G->n_vertex);

    for (int v = 0; v < G->n_vertex; v++) {
        visited[v] = 0; // not visited yet
        previous[v] = -1; // shortest path between origin and destiny
        pathWeigth[v] = INFINITE; 
    }

    vert = origin;
    pathWeigth[vert] = 0; 
    
    // haven't finished existing path
    while (vert != destiny && vert != -1) { 
        for (int i = 0; i < G->n_vertex; i++) { // walks through adj vertices  
            if (G->adjacency[vert][i] != 0 && visited[i] == 0) { // edge exists and yet not visited
                newPath = pathWeigth[vert] + G->adjacency[vert][i];
                if (newPath < pathWeigth[i]) {
                    pathWeigth[i] = newPath;
                    previous[i] = vert;
                }
            }
        }
        visited[vert] = 1; // the entire adj matrix have been visited
        min = INFINITE;
        vert = -1; // invalid
        for (int i = 0; i < G->n_vertex; i++) {
            if (visited[i] == 0 && pathWeigth[i] < min) { // picks vertex of which it's edge has the lowest weight
                min = pathWeigth[i]; // update minimum
                vert = i; // update vert
            }
        }
    } // while

    // list the shortest path between origin and desntiny
    if (vert == destiny) { // found the path
        finalPath[0] = destiny;
        k = 1;
        while (vert != origin) { 
            finalPath[k] = previous[vert]; // saves the path
            vert = previous[vert];
            k++;
        }

        int *aux = (int*)malloc(sizeof(int)*G->n_vertex); 
        invertVector (aux, finalPath, k); // invert the vector path to print it correctly
        for (int i = 0; i <= k-1; i++) {
            // corrects info (if there is no edge in between two vertices, then price = 0)
            if (G->adjacency[aux[i]][aux[i+1]] !=  info[0][aux[i]][aux[i+1]]) {
                G->adjacency[aux[i]][aux[i+1]] = 0;
                info[1][aux[i]][aux[i+1]] = 0;
            } 
            printf("%d ", aux[i]); // path
            totalPrice += info[1][aux[i]][aux[i+1]]; // adds the price
        }

        totalPrice = totalPrice - info[1][aux[k-1]][0]; // Subtracts last edge caused by for loop (that is not included in the path)
        
        printf("\n%d %d\n", pathWeigth[destiny], totalPrice); // Prints duration and price
        free (aux);
    }
    free (pathWeigth);
    free (previous);
    free (visited);
    free (finalPath);
}