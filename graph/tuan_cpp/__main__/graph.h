#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>

enum GraphPresentType {
  Matrix,
  List
};

enum GraphTraverseType {
  BreadthFirst,
  DepthFirst
};

#include "directed_graph.h"
#include "undirected_graph.h"

#endif // GRAPH_H_INCLUDED