# Computation-Modeling-Graphs
Working with graphs :)

  ## Adjacency Matrix
   
   Adjacency matrix is a square matrix used to represent a finite graph. The elements of the matrix indicate whether pairs of vertices are adjacent or not in the graph. 
   
   Memory (storage) cost = O(n²). 
   
   Searching cost = O(1). Constant. 
 
   It means that it is a useful representation for dense graphs with many edges and good for searching. 
    
  ## Adjacency List
 
 Adjacency list is a collection of unordered lists used to represent a finite graph. Each list describes the set of neighbors of a vertex in the graph. In non-directed graphs, each edge is represented twice. 
 
 Memory (storage) cost = O(n + m). Linear. 
 
 Searching cost = O(di). di = vertex degree. 
 
 It means it is a good representation for sparse graphs. The downside is the searching time to determine whether a particular edge exists or not. 
    
  ## Fleury's Algorithm
 
 Eulerian Path is a path in graph that visits every edge exactly once. Eulerian Circuit is an Eulerian Path which starts and ends on the same vertex. Fleury's algorithm aims to find a Eulerian Circuit in a graph. 
    
 ## Graph Coloring

  Four Color Theorem: given any separation of a plane into contiguous regions, producing a figure called a map, no more than four colors are required to color the regions of the map so that no two adjacent regions have the same color. Adjacent means that two regions share a common boundary (edge) curve segment, not merely a corner where three or more regions meet. <br>
  Planar graph: vertices can be arranged in the plane and you can trace all the edges no crossings between them
  
  ##### Welsh Powell Graph Coloring Algorithm
  
  1. Find the degree of each vertex
  2. List the vertices in order of descending degrees.
  3. Colour the first vertex with color 1.
  4. Move down the list and color all the vertices not connected to the coloured vertex, with the same color.
  5. Repeat step 4 on all uncolored vertices with a new color, in descending order of degrees until all the vertices are coloured.
 
 It is O(n²) in the worst case.

