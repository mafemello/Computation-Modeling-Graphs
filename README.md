# Computation-Modeling-Graphs
Working with graphs :)

  - Adjacency Matrix
    Adjacency matrix is a square matrix used to represent a finite graph. The elements of the matrix indicate whether pairs of vertices are adjacent or not in the graph. 
    Memory (storage) cost = O(n²).
    Searching cost = O(1). Constant.
    It means that it is a useful representation for dense graphs with many edges and good for searching.
    
  - Adjacency List
    Adjacency list is a collection of unordered lists used to represent a finite graph. Each list describes the set of neighbors of a vertex in the graph. In non-directed graphs, each edge is represented twice.
    Memory (storage) cost = O(n + m). Linear.
    Searching cost = O(di). di = vertex degree.
    It means it is a good representation for sparse graphs. The downside is the searching time to determine whether a particular edge exists or not.
    
  - Fleury's Algorithm
    Eulerian Path is a path in graph that visits every edge exactly once. Eulerian Circuit is an Eulerian Path which starts and ends on the same vertex. Fleury's algorithm aims to find a Eulerian Circuit in a graph.
    

