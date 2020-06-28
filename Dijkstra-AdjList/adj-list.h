// ADT - Adjacency list
// Non-oriented and weightless graph

typedef struct list List;
typedef struct node Node;

// Creates an empty graph
List* CreateGraph (int n_vertex);

// Add an edge in between two vertices, chosen by user
void AddEdge (List *G, int vertex1, int vertex2, int duration, int price);

// Remove an edge in between two vertices, chosen by user
void RemoveEdge (List *G, int vertex1, int vertex2);

// Prints the entire graph represented by adjacency matrix
void PrintGraph (List *G);

// Finishes the graph and releases allocated memory
void EndsGraph (List *G);