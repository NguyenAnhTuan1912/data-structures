/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Undirected Graph
  (With another implementation)

  Basic operation:
  - bool adjacent(string x, string y);
  - vector<Vertex<T>*>* getNeighbors(string x);
  - Vertex<T>* addVertex(string k, T v);
  - void removeVertex(string k);
  - void addEdge(string x, string y, int z);
  - void addEdge(Vertex<T>*& vX, Vertex<T>*& vY, int z);
  - void removeEdge(string x, string y);
  - T* getVertexValue(string x);
  - void setVertexValue(string x, T value);
  - int* getEdgeValue(string x, string y);
  - void setEdgeValue(string x, string y, int z);

  Ấn build để nó hiện ra từng message của lỗi.
  Để thực thi và xem các ví dụ thì comment những chỗ code lỗi lại.
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>
#include <iterator>
#include <exception>

using namespace std;

enum GraphTraverseType {
  Empty,
  Matrix,
  List
};

template<class T>
class Vertex {
private:
  string __key = "";
  T* __data = nullptr;

public:
  Vertex() = default;
  Vertex(string k): __key{k} {};
  Vertex(string k, T* ptrD): __key{k}, __data{ptrD} {};
  Vertex(string k, T d): __key{k}, __data{new T(d)} {};

  T* getData() {
    return this->__data;
  };

  string getKey() {
    return this->__key;
  };

  void setData(T d) {
    this->__data = new T(d);
  };

  void setData(T* ptrD) {
    this->__data = ptrD;
  };

  bool is(string x) {
    return this->__key == x;
  };
};

template<class T>
class UndirectedEdge {
public:
  int* value = nullptr;
  Vertex<T>* first = nullptr;
  Vertex<T>* second = nullptr;

  UndirectedEdge(Vertex<T>* f, Vertex<T>* s, int v): first{f}, second{s} {
    this->value = new int(v < 0 ? 0 : v);
  };

  void print() {
    cout
      << this->first->getKey() << "-"
      << this->second->getKey();
  };

  bool check(string x, string y) {
    return (this->first->is(x) && this->second->is(y)) || (this->first->is(y) && this->second->is(x));
  };
};

template<class T>
class UndirectedGraph {
private:
  unordered_set<UndirectedEdge<T>*> __edges;
  unordered_set<string, Vertex<T>*> __vertices;

  UndirectedEdge<T>* __getEdge(string x, string y) {
    if(!this->adjacent(x, y)) return nullptr;
    typename vector<UndirectedEdge<T>*>::iterator itr = this->__edges.begin();

    while(itr != this->__edges.end()) {
      if((*itr)->check(x, y)) return *itr;
      itr++;
    };

    return nullptr;
  };

  typename vector<UndirectedEdge<T>*>::iterator __getEdgeIterator(string x, string y) {
    if(!this->adjacent(x, y)) return this->__edges.end();

    typename vector<UndirectedEdge<T>*>::iterator itr = this->__edges.begin();
    
    while(itr != this->__edges.end()) {
      if((*itr)->check(x, y)) return itr;
      itr++;
    };

    return this->__edges.end();
  };

public:
  UndirectedGraph() = default;
  UndirectedGraph(string k, T* v) {
    __vertices.insert(new Vertex<T>(k , v));
  };
  UndirectedGraph(string k, T v) {
    __vertices.insert(new Vertex<T>(k , v));
  };
  // Static methods

  // Fundamental Operations

  // [OPERATION]
  // adjacent -> bool
  bool adjacent(string x, string y) {
    return this->__vertices[x]->hasEdgeWith(y) && this->__vertices[y]->hasEdgeWith(x);
  };

  // [OPERATION]
  // getNeighbors -> vector<Vertext<T>*>
  vector<Vertex<T>*> getNeighbors(string x) {

  };

  // [OPERATION]
  // addVertex -> void
  Vertex<T>* addVertex(string k, T v) {
    // Add vertex to map
    if(this->__vertices[k] == nullptr) {
      this->__vertices[k] = new Vertex<T>(k, v);
      return this->__vertices[k];
    }
    return nullptr;
  };

  // [OPERATION]
  // removeVertex -> void
  void removeVertex(string k) {
    // Add vertex to map
    if(this->__vertices[k] != nullptr)
      delete this->__vertices[k];
      this->__vertices[k] = nullptr;
  };

  // [OPERATION]
  // addEdge -> void
  void addEdge(string x, string y, int z) {
    if(this->adjacent(x, y)) return;
    Vertex<T>* vX = this->__vertices[x];
    Vertex<T>* vY = this->__vertices[y];

    // Link between 2 vertices
    vX->addLinkedVertex(vY);
    vY->addLinkedVertex(vX);
    
    // Add edge
    this->__edges.push_back(new UndirectedEdge<T>(vX, vY, z));
  };

  void addEdge(Vertex<T>*& vX, Vertex<T>*& vY, int z) {
    if(this->adjacent(vX->getKey(), vY->getKey())) return;

    // Link between 2 vertices
    vX->addLinkedVertex(vY);
    vY->addLinkedVertex(vX);
    
    // Add edge
    this->__edges.push_back(new UndirectedEdge<T>(vX, vY, z));
  };

  // [OPERATION]
  // removeEdge -> void
  void removeEdge(string x, string y) {
    if(!this->adjacent(x, y)) return;
    Vertex<T>* vX = this->__vertices[x];
    Vertex<T>* vY = this->__vertices[y];

    // Remove edge
    this->__edges.erase(this->__getEdgeIterator(vX->getKey(), vY->getKey()));

    // Remove links
    vX->removeLinkedVertex(vY->getKey());
    vY->removeLinkedVertex(vX->getKey());
  };

  // [OPERATION]
  // getVertexValue -> T*
  T* getVertexValue(string x) {
    return this->__vertices[x]->getData();
  };

  // [OPERATION]
  // setVertexValue -> void
  void setVertexValue(string x, T value) {
    this->__vertices[x]->setData(x, value);
  };

  // [OPERATION]
  // getEdgeValue -> int*
  int* getEdgeValue(string x, string y) {
    UndirectedEdge<T>* e = this->__getEdge(x, y);
    return e ? e->value : nullptr;
  };

  // [OPERATION]
  // setEdgeValue -> void
  void setEdgeValue(string x, string y, int z) {
    this->__getEdge(x, y)->value = new int(z);
  };


};

// Other functions
template<class T>
void printAdjacentCheckingResult(UndirectedGraph<T>& g, Vertex<T>*& vX, Vertex<T>*& vY) {
  cout
    << "Is " << vX->getKey()
    << " adjacent with " << vY->getKey() << "? "
    << (g.adjacent(vX->getKey(), vY->getKey()) ? "Yes" : "No")
    << endl;
};

template<class T>
void printEdgeValueResult(UndirectedGraph<T>& g, Vertex<T>*& vX, Vertex<T>*& vY) {
  int* ptrEValue = g.getEdgeValue(vX->getKey(), vY->getKey());
  cout
    << "Value of edge["
    << vX->getKey() << "-"
    << vY->getKey() << "]: "
    << ( ptrEValue ? *ptrEValue : -1 )
    << endl;
};

template<class T>
void printNeighborsOfvX(UndirectedGraph<T>& g, Vertex<T>*& vX) {
  vector<Vertex<T>*>* neighbors = g.getNeighbors(vX->getKey());
  typename vector<Vertex<T>*>::iterator itr = neighbors->begin();
  cout << "Neighbors of " << vX->getKey() << ": \n";
  while(itr != neighbors->end()) {
    cout << (*itr)->getKey() << " ";
    itr++;
  };
  cout << endl;
};

int main() {
  // Initialize UndirectedGraph
  UndirectedGraph<int> udGraph;

  // Add vertices
  Vertex<int>* vA = udGraph.addVertex("A", 1);
  Vertex<int>* vB = udGraph.addVertex("B", 21);
  Vertex<int>* vC = udGraph.addVertex("C", 3);
  Vertex<int>* vD = udGraph.addVertex("D", 8);
  Vertex<int>* vE = udGraph.addVertex("E", 14);

  // Add edges
  udGraph.addEdge(vA, vB, 2);
  udGraph.addEdge(vA, vC, 3);
  udGraph.addEdge(vA, vD, 5);
  udGraph.addEdge(vA, vE, 1);
  udGraph.addEdge(vB, vC, 5);
  udGraph.addEdge(vB, vD, 6);
  udGraph.addEdge(vB, vE, 7);
  udGraph.addEdge(vC, vD, 6);
  udGraph.addEdge(vD, vE, 7);
  udGraph.addEdge(vE, vA, 11);

  // Perform some operations
  printAdjacentCheckingResult(udGraph, vA, vB);
  printEdgeValueResult(udGraph, vA, vB);
  printEdgeValueResult(udGraph, vB, vA);
  cout << endl;

  printAdjacentCheckingResult(udGraph, vA, vC);
  printEdgeValueResult(udGraph, vA, vC);
  printEdgeValueResult(udGraph, vC, vA);
  cout << endl;

  printAdjacentCheckingResult(udGraph, vB, vC);
  printEdgeValueResult(udGraph, vB, vC);
  printEdgeValueResult(udGraph, vC, vB);
  cout << endl;

  // Remove links and re-check
  cout << "Remove links between A and B...\n";
  udGraph.removeEdge(vA->getKey(), vB->getKey());

  printAdjacentCheckingResult(udGraph, vA, vB);
  printEdgeValueResult(udGraph, vA, vB);
  printEdgeValueResult(udGraph, vB, vA);
  cout << endl;

  cout << "Get neighbor of A...\n";
  printNeighborsOfvX(udGraph, vA);
  cout << endl;

  cout << "Get neighbor of B...\n";
  printNeighborsOfvX(udGraph, vB);
  cout << endl;

  cout << "Get neighbor of C...\n";
  printNeighborsOfvX(udGraph, vC);
  cout << endl;

  cout << "Get neighbor of D...\n";
  printNeighborsOfvX(udGraph, vD);
  cout << endl;

  cout << "Get neighbor of E...\n";
  printNeighborsOfvX(udGraph, vE);
  cout << endl;

  return 0;
};