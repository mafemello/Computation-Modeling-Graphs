#include <stdio.h>
#include <stdlib.h>
#include "adj-matrix.h"
#include "stack.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2


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
            G->adjacency[i][j] = -1; // Empty matrix. There are no edges in between the vertices.
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
void AddEdge (Graph* G, int v1, int v2, int w) {
    G->adjacency[v1][v2] = w;
    if (!G->dir) G->adjacency[v2][v1] = w; // If the graph is not directed
}

// Function that prints the adjacencies of a vertex
void ShowAdj(Graph* G, int v) {
    
    for (int i = 0; i < G->n_vertex; i++) {
        if (G->adjacency[v][i] >= 0)
            printf("%d ", i); 
    }
    printf("\n");
}

// Remove an edge in between two vertices, chosen by user
/*
    v1: origin vertex
    v2: destination vertex
    w: weight
*/
void RemoveEdge(Graph* G, int v1, int v2) {
    G->adjacency[v1][v2] = -1;
    if (!G->dir) G->adjacency[v2][v1] = -1; // If the graph is not directed
}

// Function returns the number of vertices in the graph
int GimmeNumberOfVertices (Graph* G) {
    return G->n_vertex;
}

// Prints the entire graph represented by adjacency matrix
void PrintGraph(Graph* G) {
    for (int i = 0; i < G->n_vertex; i++) {
        for (int j = 0; j < G->n_vertex; j++) {
            if (G->adjacency[i][j] < 0) printf(". ");
            else printf("%d ", G->adjacency[i][j]);
        }
        printf("\n");
    }
}

// Returns the transposed graph
Graph* TransposeGraph (Graph* G) {
    Graph* t = CreateGraph(G->n_vertex, G->dir); // Create the new graph
    
    for (int i = 0; i < t->n_vertex; i++)
        for (int j = 0; j < t->n_vertex; j++)
            t->adjacency[j][i] = G->adjacency[i][j]; // transposition
    
    return t;
}

// Prints the transposed graph
void PrintTransposedGraph (Graph* G) {
    Graph* t = TransposeGraph(G);
    
    PrintGraph(t);
    EndsGraph(t);
}

// Finishes the graph and releases allocated memory
void EndsGraph (Graph* G) {
    for (int i = 0; i < G->n_vertex; i++) free(G->adjacency[i]);
    free(G->adjacency);
    free(G);
}

// Auxiliar function that performs the DFS to find cicles
void DFSVisit (Graph* G, Stack *s, int u, int time, int ver, int *d, int*f, int *pi, int *color, int* cicle) {
    
    // vertex is discovered 
    color[u] = GRAY; //cinza
    d[u] = time++;

    for (int v = 0; v < ver; v++) { // DFS algorithm
        if (G->adjacency[u][v] != -1) {
            if (color[v] == GRAY) { // if means there is a cicle
                *cicle = 1;
            }
            if (color[v] == WHITE) { // call dfs visit again to discover the next vertex
                pi[v] = u;
                DFSVisit (G, s, v, time, ver, d, f, pi, color, cicle);
            }
        }
    }
    color[u] = BLACK; // vertex processed
    f[u] = time++;
    StackPush(s,u); // topological list
}

// This function is used to check if there is a cicle in the graph
int DFS_CheckCicle(Graph *G, Stack *s) {
    int time;
    int ver = G->n_vertex;
    int *d = (int*) malloc(sizeof(int)*(ver)); // vertex discovery time
    int *f = (int*) malloc(sizeof(int)*(ver)); // processing time
    int *pi = (int*) malloc(sizeof(int)*(ver)); // predecessor 
    int *color = (int*) malloc(sizeof(int)*(ver));
    /*  COLOR
        white = at the begining
        gray = vertex discovered
        black = vertex processed
    */

    int cicle = 0; // flag to show the cicle

    for (int i = 0; i < ver; i++) { // initializes all vertices with white
        color[i] = WHITE;  
        pi[i] = -1; //predecessor
    }

    time = 0;
    for (int i = 0; i < ver; i++)
        if (color[i] == WHITE) DFSVisit (G, s, i, time, ver, d, f, pi, color, &cicle);
   
    return cicle;
}

// Auxiliar function to check if there are unprocessed vertices
int StillNeedsToExecute (int* executed, int numVertex) {
    for (int i = 0; i < numVertex; i++) {
        if (executed[i] == 0) {
            return 1;
        }
    }
    return 0;
}

// Function that calculates the execution time
void CalculatesTime (Graph *G) {
    Graph* dependencies;
    dependencies = TransposeGraph(G); // transposed graph = dependency matrix of each vertex
    
    int* executed = calloc(G->n_vertex, sizeof(int));
    int* temporarilySaved = calloc(G->n_vertex, sizeof(int));
    int ReadyToSave; // flag
    int counter = 0;

    // While still having unprocessed vertex
    while (StillNeedsToExecute(executed, G->n_vertex)) {
        for (int i = 0; i < G->n_vertex; i++) {
            ReadyToSave = 1; 
            for (int j = 0; j < G->n_vertex; j++) {
                if (dependencies->adjacency[i][j] == 1) { // has dependency
                    // checks if the dependency has already been executed
                    if (executed[j] == 0) { // if it wasn't
                        ReadyToSave = 0; // not ready to save, so it begins again
                    } 
                }
            }
            if (ReadyToSave == 1) { // if it is ready
                temporarilySaved[i] = 1; // save it on the array
            }
        }
        counter++; // one unit of time == processed the parallel tasks
        for (int i = 0; i < G->n_vertex; i++) {
            if (temporarilySaved[i] == 1) { // now you can run this task
                executed[i] = 1; 
            }
        }
        for (int i = 0; i < G->n_vertex; i ++) {
            temporarilySaved[i] = 0; // null to next iteration
        }
    }
        
    printf("%d\n", counter); // answer

}
