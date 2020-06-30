#ifndef mgraph_h
#define mgraph_h

typedef struct graph Graph;

Graph* CreateGraph(int n_vertex, int dir);
void EndsGraph (Graph* G);
void AddEdge (Graph* G, int v1, int v2, int*** info);
int GimmeNumberOfVertices (Graph* G);
int djikstra (Graph* G, int origin, int destiny, int*** info);
void print (int*** info, int city);
void correctsInfo (Graph* G, int v1, int v2, int*** info);

#endif /* mgraph_h */