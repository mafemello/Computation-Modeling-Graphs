/*
	Graphs - third activity	
	Maria Fernanda Lucio de Mello
	nUSP: 11320860
*/

#include <stdlib.h>
#include <stdio.h>
#include "adj-matrix.h"
#include "stack.h"

int main (void) {
     
    int tasks, dependencies;
    scanf ("%d %d", &tasks, &dependencies);

    Graph *G = CreateGraph (tasks, 1);
    Stack *s = StackCreate();
    

    int before, after;
    for (int i = 0; i < dependencies; i ++) {
        scanf ("%d %d", &before, &after);
        AddEdge (G, before, after,1);
    }

    int cicle;
    cicle = DFS_CheckCicle(G, s);
    if (cicle == 1) {
        printf("-1\n");
    } else {
        CalculatesTime (G);
    }
    
    //stack_print(s); // topological list
    StackFree (&s);
    EndsGraph (G);
    
    return 0;
}
