#include "stack.h"

#ifndef mgraph_h
#define mgraph_h

#define MAX 99

typedef struct graph Graph;

Graph* CreateGraph(int n_vertex, int dir);
int DFS_CheckCicle(Graph *G, Stack *s);
void EndsGraph (Graph* G);
void PrintGraph(Graph* G);
void AddEdge (Graph* G, int v1, int v2, int w);
void RemoveEdge(Graph* G, int v1, int v2);
void ShowAdj(Graph* G, int v);
int GimmeNumberOfVertices (Graph* G);
Graph* TransposeGraph (Graph* G);
void PrintTransposedGraph (Graph* G);
void DFSVisit (Graph* G, Stack *s, int u, int time, int ver, int *d, int*f, int *pi, int *color, int* cicle);
void CalculatesTime (Graph *G);
int StillNeedsToExecute (int* executed, int numVertex);
#endif /* mgraph_h */