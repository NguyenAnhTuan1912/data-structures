/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Undirected Graph

  Ấn build để nó hiện ra từng message của lỗi.
  Để thực thi và xem các ví dụ thì comment những chỗ code lỗi lại.
*/

#include <iostream>
#include <vector>
#include <map>
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
  map<string, Vertex*> __linkedVertices;
  // vector<Vertex*> __linkedVertices;

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

  void addLinkedVertex(Vertex<T>& v) {
    if(this->__linkedVertices[v.__key] == nullptr)
      this->__linkedVertices[v.__key] = &v;
    // this->__linkedVertices.push_back(&v);
  };

  void addLinkedVertex(Vertex<T>* v) {
    if(this->__linkedVertices[v->__key] == nullptr)
      this->__linkedVertices[v->__key] = v;
    // this->__linkedVertices.push_back(v);
  };

  void removeLinkedVertex(string y) {
    if(this->__linkedVertices[y] != nullptr)
      this->__linkedVertices.erase(y);
  };

  bool hasEdgeWith(string y) {
    return this->__linkedVertices[y] != nullptr;
  };

  bool hasEdgeWith(Vertex<T>* yV) {
    return this->__linkedVertices[yV->getKey()] != nullptr;
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
  vector<UndirectedEdge<T>*> __edges;
  map<string, Vertex<T>*> __vertices;

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

  // Fundamental Operations
  // adjacent -> bool
  bool adjacent(string x, string y) {
    return this->__vertices[x]->hasEdgeWith(y) && this->__vertices[y]->hasEdgeWith(x);
  };

  // getNeighbors -> vector<Vertext<T>*>
  vector<Vertex<T>*> getNeighbors(string x) {

  };

  // addVertex -> void
  Vertex<T>* addVertex(string k, T v) {
    // Add vertex to map
    if(this->__vertices[k] == nullptr) {
      this->__vertices[k] = new Vertex<T>(k, v);
      return this->__vertices[k];
    }
    return nullptr;
  };

  // removeVertex -> void
  void removeVertex(string k) {
    // Add vertex to map
    if(this->__vertices[k] != nullptr)
      delete this->__vertices[k];
      this->__vertices[k] = nullptr;
  };

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

  void removeEdge(Vertex<T>* vX,  Vertex<T>* vY) {
    if(!this->adjacent(vX->getKey(), vY->getKey())) return;

    // Remove edge
    this->__edges.erase(this->__getEdgeIterator(vX->getKey(), vY->getKey()));

    // Remove links
    vX->removeLinkedVertex(vY->getKey());
    vY->removeLinkedVertex(vX->getKey());
  };

  // getVertexValue -> T*
  T* getVertexValue(string x) {
    return this->__vertices[x]->getData();
  };

  // setVertexValue -> void
  void setVertexValue(string x, T value) {
    this->__vertices[x]->setData(x, value);
  };

  // getEdgeValue -> int*
  int* getEdgeValue(string x, string y) {
    UndirectedEdge<T>* e = this->__getEdge(x, y);
    return e ? e->value : nullptr;
  };

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

int main() {
  // Initialize UndirectedGraph
  UndirectedGraph<int> udGraph;

  // Add vertices
  Vertex<int>* vA = udGraph.addVertex("A", 1);
  Vertex<int>* vB = udGraph.addVertex("B", 21);
  Vertex<int>* vC = udGraph.addVertex("C", 3);

  // Add edges
  udGraph.addEdge(vA, vB, 2);
  udGraph.addEdge(vA, vC, 10);

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
  udGraph.removeEdge(vA, vB);

  printAdjacentCheckingResult(udGraph, vA, vB);
  printEdgeValueResult(udGraph, vA, vB);
  printEdgeValueResult(udGraph, vB, vA);
  cout << endl;

  return 0;
};