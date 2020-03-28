// ADT - Adjacency Matrix

typedef struct graph Graph;

// Creates an empty graph
Graph* CreateGraph (int n_vertex);

// Add an edge in between two vertices, chosen by user
void AddEdge (Graph *G, int vertex1, int vertex2);

// Remove an edge in between two vertices, chosen by user
void RemoveEdge (Graph *G, int vertex1, int vertex2);

// Prints the entire graph represented by adjacency matrix
void PrintGraph (Graph *G);

// Finishes the graph and releases allocated memory
void EndsGraph (Graph **G);