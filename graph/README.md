# Graph

## Concept
__[INSERT IMAGE HERE]__
Beside Tree, Graph is a complicated data structures, and it's used in multiple important solutions. Many Nodes link each others and construct a graph. In graph, Node is called __Vertex__ (__Vertices__ in plural form), and connection between them is called __Edge__. There are 2 types of graph: __Undirected__ and __Directed__, each type has its own properties.

What are __Vertex__ and __Edge__?
- __Vertex__: as I said, Vertex is Node, so Vertex has same operations with Node. How Node works is How Vertex works.
- __Edge__: Edge contains 2 pointers or references of 2 vertices and hold its own value. And depend on type of graph, it has a bit differences:
  - In __Undirected Graph__: edge doen't distinct 2 vertices at 2 heads, they are the same. For example: AB is BA. Graph differentiates edges by the total of hash result of each key of vertices. 
  - In __Directed Graph__: edge is called vector. It distincts 2 vertices at 2 heads, they are different. For example: AB isn't BA. Graph differentiates edges by the total of (hash result is divided with 2 different values respectively) of each key of vertices.
  
Graph contains a Set of Edges and a Map of Vertices. Each vertex points or refers to memory that contains data and edge points or refers to that vertex. That's all.

## Examples
1. Example with Undirected Graph (1st implementation)
   - By __Nguyen Anh Tuan__, [view more](/graph/tuan_cpp/examples/graph_example_01_tuan.cpp)
2. Example with Undirected Graph (2nd implementation)
   - By __Nguyen Anh Tuan__, [view more](/graph/tuan_cpp/examples/graph_example_02_tuan.cpp)
3. Example with Directed Graph
   - By __Nguyen Anh Tuan__, [view more](/graph/tuan_cpp/examples/graph_example_03_tuan.cpp)

## Exercises
Update later...