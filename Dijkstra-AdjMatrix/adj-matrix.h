#ifndef mgraph_h
#define mgraph_h

#define MAX 99

typedef struct graph Graph;

Graph* CreateGraph(int n_vertex, int dir);
void EndsGraph (Graph* G);
void AddEdge (Graph* G, int v1, int v2, int*** info);
int GimmeNumberOfVertices (Graph* G);
int djikstra (Graph* G, int origin, int destiny, int*** info, int flyNumber);

void print (int*** info, int city, int fly);
void tratarInfo (Graph* G, int v1, int v2, int*** info);


#endif /* mgraph_h */