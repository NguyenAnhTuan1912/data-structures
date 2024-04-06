#include <iostream>

#include "graph.h"
#include "directed_graph.h"
#include "undirected_graph.h"

using namespace std;

namespace UDG_Utils {

template<class T>
void printAdjacentCheckingResult(UndirectedGraph<T>& g, VertexPointer<T>& vX, VertexPointer<T>& vY) {
  if((vX || vY) == false) {
    cout << "This edge isn't exist\n";
    return;
  }

  cout
    << "Is " << vX->getKey()
    << " adjacent with " << vY->getKey() << "? "
    << (g.adjacent(vX->getKey(), vY->getKey()) ? "Yes" : "No")
    << endl;
};

template<class T>
void printEdgeValueResult(UndirectedGraph<T>& g, VertexPointer<T>& vX, VertexPointer<T>& vY) {
  int* ptrEValue = g.getEdgeValue(vX->getKey(), vY->getKey());
  cout
    << "Value of edge["
    << vX->getKey() << "-"
    << vY->getKey() << "]: "
    << ( ptrEValue ? *ptrEValue : -1 )
    << endl;
};

template<class T>
void printNeighborsOfvX(UndirectedGraph<T>& g, VertexPointer<T>& vX) {
  vector<VertexPointer<T>> neighbors = g.getNeighbors(vX->getKey());
  typename vector<VertexPointer<T>>::iterator itr = neighbors.begin();
  cout << "Neighbors of " << vX->getKey() << ": \n";
  while(itr != neighbors.end()) {
    cout << (*itr)->getKey() << " ";
    itr++;
  };
  cout << endl;
};

template<class T>
void printResultOfTraversal(UndirectedGraph<T>& g, string start, GraphTraverseType traverseType) {
  ConstVertexCallBack<T> cb = [](const VertexPointer<T> ptrV) {
    cout << ptrV->getKey() << " ";
  };

  if(traverseType == DepthFirst) cout << "Depth First Traverse\n";
  else cout << "Breadth First Traverse\n";
  cout << "Start from " << start << endl;
  g.traverse(start, cb, traverseType);
  cout << endl << endl;
};

};

namespace DG_Utils {

template<class T>
void printAdjacentCheckingResult(DirectedGraph<T>& g, VertexPointer<T>& vX, VertexPointer<T>& vY) {
  if((vX || vY) == false) {
    cout << "This edge isn't exist\n";
    return;
  }

  cout
    << "Is " << vX->getKey()
    << " adjacent with " << vY->getKey() << "? "
    << (g.adjacent(vX->getKey(), vY->getKey()) ? "Yes" : "No")
    << endl;
};

template<class T>
void printEdgeValueResult(DirectedGraph<T>& g, VertexPointer<T>& vX, VertexPointer<T>& vY) {
  int* ptrEValue = g.getEdgeValue(vX->getKey(), vY->getKey());
  cout
    << "Value of edge["
    << vX->getKey() << "-"
    << vY->getKey() << "]: "
    << ( ptrEValue ? *ptrEValue : -1 )
    << endl;
};

template<class T>
void printNeighborsOfvX(DirectedGraph<T>& g, VertexPointer<T>& vX) {
  vector<VertexPointer<T>> neighbors = g.getNeighbors(vX->getKey());
  typename vector<VertexPointer<T>>::iterator itr = neighbors.begin();
  cout << "Neighbors of " << vX->getKey() << ": \n";
  while(itr != neighbors.end()) {
    cout << (*itr)->getKey() << " ";
    itr++;
  };
  cout << endl;
};

template<class T>
void printResultOfTraversal(DirectedGraph<T>& g, string start, GraphTraverseType traverseType) {
  ConstVertexCallBack<T> cb = [](const VertexPointer<T> ptrV) {
    cout << ptrV->getKey() << " ";
  };

  if(traverseType == DepthFirst) cout << "Depth First Traverse\n";
  else cout << "Breadth First Traverse\n";
  cout << "Start from " << start << endl;
  g.traverse(start, cb, traverseType);
  cout << endl << endl;
};

};

template<class T>
void runFirstDemo(DirectedGraph<T>& graph) {
  // Add vertices
  VertexPointer<int> vA = graph.addVertex("A", 1);
  VertexPointer<int> vB = graph.addVertex("B", 21);
  VertexPointer<int> vC = graph.addVertex("C", 3);
  VertexPointer<int> vD = graph.addVertex("D", 8);
  VertexPointer<int> vE = graph.addVertex("E", 14);
  VertexPointer<int> vF = graph.addVertex("F", 2);
  VertexPointer<int> vG = graph.addVertex("G", 9);
  VertexPointer<int> vH = graph.addVertex("H", 33);

  // Add edges
  graph.addEdge(vA, vB, 2);
  graph.addEdge(vA, vD, 3);
  graph.addEdge(vA, vG, 5);
  graph.addEdge(vB, vA, 10);
  graph.addEdge(vB, vC, 1);
  graph.addEdge(vB, vE, 6);
  graph.addEdge(vC, vE, 5);
  graph.addEdge(vD, vF, 6);
  graph.addEdge(vE, vH, 7);
  graph.addEdge(vG, vH, 11);

  // Perform some operations
  cout << "Check adjacencies\n";
  DG_Utils::printAdjacentCheckingResult(graph, vA, vB);
  DG_Utils::printAdjacentCheckingResult(graph, vA, vD);
  DG_Utils::printAdjacentCheckingResult(graph, vA, vG);
  DG_Utils::printAdjacentCheckingResult(graph, vF, vD);
  DG_Utils::printAdjacentCheckingResult(graph, vE, vH);
  DG_Utils::printAdjacentCheckingResult(graph, vA, vC);
  DG_Utils::printAdjacentCheckingResult(graph, vD, vC);
  DG_Utils::printAdjacentCheckingResult(graph, vG, vH);
  DG_Utils::printAdjacentCheckingResult(graph, vC, vE);
  DG_Utils::printAdjacentCheckingResult(graph, vF, vG);
  cout << endl;

  cout << "Get values of some edges\n";
  DG_Utils::printEdgeValueResult(graph, vA, vB);
  DG_Utils::printEdgeValueResult(graph, vB, vA);
  DG_Utils::printEdgeValueResult(graph, vD, vA);
  DG_Utils::printEdgeValueResult(graph, vF, vD);
  DG_Utils::printEdgeValueResult(graph, vD, vF);
  DG_Utils::printEdgeValueResult(graph, vE, vH);
  DG_Utils::printEdgeValueResult(graph, vA, vC);
  DG_Utils::printEdgeValueResult(graph, vD, vC);
  DG_Utils::printEdgeValueResult(graph, vG, vH);
  DG_Utils::printEdgeValueResult(graph, vE, vC);
  DG_Utils::printEdgeValueResult(graph, vF, vG);
  cout << endl;

  cout << "Neighbors of some vertices\n";
  DG_Utils::printNeighborsOfvX(graph, vA);
  DG_Utils::printNeighborsOfvX(graph, vB);
  DG_Utils::printNeighborsOfvX(graph, vC);
  DG_Utils::printNeighborsOfvX(graph, vD);
  DG_Utils::printNeighborsOfvX(graph, vE);
  DG_Utils::printNeighborsOfvX(graph, vF);
  DG_Utils::printNeighborsOfvX(graph, vG);
  DG_Utils::printNeighborsOfvX(graph, vH);
  cout << endl;

  cout << "Delete a vertex (vA)\n";
  graph.removeVertex(vA->getKey());
  DG_Utils::printAdjacentCheckingResult(graph, vA, vB);
  DG_Utils::printAdjacentCheckingResult(graph, vA, vD);
  DG_Utils::printAdjacentCheckingResult(graph, vA, vG);
  cout << endl;

  graph.setVertexValue("B", 1233);
  cout << "New value of vB: " << *(graph.getVertexValue("B")) << endl;

  graph.setEdgeValue("E", "C", 999);
  DG_Utils::printEdgeValueResult(graph, vC, vE);
  cout << endl;

  // Traverse
  DG_Utils::printResultOfTraversal(graph, vB->getKey(), DepthFirst);
  DG_Utils::printResultOfTraversal(graph, vB->getKey(), BreadthFirst);

  // Present
  cout << "Present Graph in Matrix\n";
  graph.presentMatrix();
  cout << endl;

  cout << "Present Graph in List\n";
  graph.presentList();
  cout << endl;
};

template<class T>
void runSecondDemo(UndirectedGraph<T>& graph) {
  // Add vertices
  VertexPointer<int> vA = graph.addVertex("A", 1);
  VertexPointer<int> vB = graph.addVertex("B", 21);
  VertexPointer<int> vC = graph.addVertex("C", 3);
  VertexPointer<int> vD = graph.addVertex("D", 8);
  VertexPointer<int> vE = graph.addVertex("E", 14);
  VertexPointer<int> vF = graph.addVertex("F", 2);
  VertexPointer<int> vG = graph.addVertex("G", 9);
  VertexPointer<int> vH = graph.addVertex("H", 33);

  // Add edges
  graph.addEdge(vA, vB, 2);
  graph.addEdge(vA, vD, 3);
  graph.addEdge(vA, vG, 5);
  graph.addEdge(vB, vA, 10);
  graph.addEdge(vB, vC, 1);
  graph.addEdge(vB, vE, 6);
  graph.addEdge(vC, vE, 5);
  graph.addEdge(vD, vF, 6);
  graph.addEdge(vE, vH, 7);
  graph.addEdge(vG, vH, 11);

  // Perform some operations
  cout << "Check adjacencies\n";
  UDG_Utils::printAdjacentCheckingResult(graph, vA, vB);
  UDG_Utils::printAdjacentCheckingResult(graph, vA, vD);
  UDG_Utils::printAdjacentCheckingResult(graph, vA, vG);
  UDG_Utils::printAdjacentCheckingResult(graph, vF, vD);
  UDG_Utils::printAdjacentCheckingResult(graph, vE, vH);
  UDG_Utils::printAdjacentCheckingResult(graph, vA, vC);
  UDG_Utils::printAdjacentCheckingResult(graph, vD, vC);
  UDG_Utils::printAdjacentCheckingResult(graph, vG, vH);
  UDG_Utils::printAdjacentCheckingResult(graph, vC, vE);
  UDG_Utils::printAdjacentCheckingResult(graph, vF, vG);
  cout << endl;

  cout << "Get values of some edges\n";
  UDG_Utils::printEdgeValueResult(graph, vA, vB);
  UDG_Utils::printEdgeValueResult(graph, vB, vA);
  UDG_Utils::printEdgeValueResult(graph, vD, vA);
  UDG_Utils::printEdgeValueResult(graph, vF, vD);
  UDG_Utils::printEdgeValueResult(graph, vD, vF);
  UDG_Utils::printEdgeValueResult(graph, vE, vH);
  UDG_Utils::printEdgeValueResult(graph, vA, vC);
  UDG_Utils::printEdgeValueResult(graph, vD, vC);
  UDG_Utils::printEdgeValueResult(graph, vG, vH);
  UDG_Utils::printEdgeValueResult(graph, vE, vC);
  UDG_Utils::printEdgeValueResult(graph, vF, vG);
  cout << endl;

  cout << "Neighbors of some vertices\n";
  UDG_Utils::printNeighborsOfvX(graph, vA);
  UDG_Utils::printNeighborsOfvX(graph, vB);
  UDG_Utils::printNeighborsOfvX(graph, vC);
  UDG_Utils::printNeighborsOfvX(graph, vD);
  UDG_Utils::printNeighborsOfvX(graph, vE);
  UDG_Utils::printNeighborsOfvX(graph, vF);
  UDG_Utils::printNeighborsOfvX(graph, vG);
  UDG_Utils::printNeighborsOfvX(graph, vH);
  cout << endl;

  cout << "Delete a vertex (vA)\n";
  graph.removeVertex(vA->getKey());
  UDG_Utils::printAdjacentCheckingResult(graph, vA, vB);
  UDG_Utils::printAdjacentCheckingResult(graph, vA, vD);
  UDG_Utils::printAdjacentCheckingResult(graph, vA, vG);
  cout << endl;

  graph.setVertexValue("B", 1233);
  cout << "New value of vB: " << *(graph.getVertexValue("B")) << endl;

  graph.setEdgeValue("E", "C", 999);
  UDG_Utils::printEdgeValueResult(graph, vC, vE);
  cout << endl;

  // Traverse
  UDG_Utils::printResultOfTraversal(graph, vB->getKey(), DepthFirst);
  UDG_Utils::printResultOfTraversal(graph, vB->getKey(), BreadthFirst);

  // Present
  cout << "Present Graph in Matrix\n";
  graph.presentMatrix();
  cout << endl;

  cout << "Present Graph in List\n";
  graph.presentList();
  cout << endl;
};

int main() {
  DirectedGraph<int> graph;
  UndirectedGraph<int> ugraph;

  cout << "Demo with Directed Graph\n";
  runFirstDemo(graph);
  cout << endl;

  cout << "Demo with Undirected Graph\n";
  runSecondDemo(ugraph);
  cout << endl;

  return 0;
}