/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Undirected Graph

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
#include <map>
#include <stack>
#include <queue>
#include <functional>
#include <iterator>
#include <exception>

using namespace std;

enum GraphPresentType {
  Matrix,
  List
};

enum GraphTraverseType {
  BreadthFirst,
  DepthFirst
};

template<class T>
class Vertex {
private:
  string __key = "";
  T* __data = nullptr;
  map<string, Vertex<T>*> __linkedVertices;
  // vector<Vertex*> __linkedVertices;

public:
  Vertex() = default;
  Vertex(string k): __key{k} {};
  Vertex(string k, T* ptrD): __key{k}, __data{ptrD} {};
  Vertex(string k, T d): __key{k}, __data{new T(d)} {};

  T* getData() const {
    return this->__data;
  };

  string getKey() const {
    return this->__key;
  };

  void setData(T d) {
    if(this->__data != nullptr) delete this->__data;
    this->__data = new T(d);
  };

  void setData(T* ptrD) {
    if(this->__data != nullptr) delete this->__data;
    this->__data = ptrD;
  };

  map<string, Vertex<T>*>& getLinkedVertices() {
    return this->__linkedVertices;
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

  bool hasEdgeWith(string y) const {
    return this->__linkedVertices.find(y) != this->__linkedVertices.end();
  };

  bool hasEdgeWith(Vertex<T>* yV) const {
    return this->__linkedVertices[yV->getKey()] != nullptr;
  };

  bool is(string x) const {
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

  void print() const {
    cout
      << this->first->getKey() << "-"
      << this->second->getKey();
  };

  bool check(string x, string y) const {
    return (this->first->is(x) && this->second->is(y)) || (this->first->is(y) && this->second->is(x));
  };
};

// Types
template<class T>
using ConstVertexCallBack = function<void(const Vertex<T>* ptrV)>;

template<class T>
using ConstUndirectedEdgeCallBack = function<void(const UndirectedEdge<T>* ptrE)>;

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

  // Static Methods
  static void __iterateEdges(UndirectedGraph<T>& g, ConstUndirectedEdgeCallBack<T>& cb);
  static void __depthFirstTraverse(ConstVertexCallBack<T>& cb, stack<Vertex<T>*>& S, map<string, string>& wasInSVertices);
  static void __breadthFirstTraverse(ConstVertexCallBack<T>& cb, queue<Vertex<T>*>& Q, map<string, string>& wasInQVertices);

public:
  UndirectedGraph() = default;
  UndirectedGraph(string k, T* v) {
    __vertices[k] = new Vertex<T>(k , v);
  };
  UndirectedGraph(string k, T v) {
    __vertices[k] = new Vertex<T>(k , v);
  };

  // Fundamental Operations

  // [OPERATION]
  vector<UndirectedEdge<T>*>& getEdges() {
    return this->__edges;
  };

  map<string, Vertex<T>*>& getVertices() {
    return this->__vertices;
  };

  // [MAIN OPERATION]
  // adjacent -> bool
  bool adjacent(string x, string y) {
    return this->__vertices[x]->hasEdgeWith(y) && this->__vertices[y]->hasEdgeWith(x);
  };

  // [MAIN OPERATION]
  // getNeighbors -> vector<Vertext<T>*>
  vector<Vertex<T>*>* getNeighbors(string x) {
    if(this->__edges.size() == 0 || this->__vertices.size() == 0) return nullptr;

    vector<Vertex<T>*>* result = new vector<Vertex<T>*>();
    typename vector<UndirectedEdge<T>*>::iterator itrE = this->__edges.begin();

    ConstUndirectedEdgeCallBack<T> cb = [&](const UndirectedEdge<T>* ptrE) {
      if(ptrE->first->getKey() == x) result->push_back(ptrE->second);
      if(ptrE->second->getKey() == x) result->push_back(ptrE->first);
    };

    UndirectedGraph<T>::__iterateEdges(*this, cb);

    return result;
  };

  // [MAIN OPERATION]
  // addVertex -> void
  Vertex<T>* addVertex(string k, T v) {
    // Add vertex to map
    if(this->__vertices[k] == nullptr) {
      this->__vertices[k] = new Vertex<T>(k, v);
      return this->__vertices[k];
    }
    return nullptr;
  };

  // [MAIN OPERATION]
  // removeVertex -> void
  void removeVertex(string k) {
    // Add vertex to map
    if(this->__vertices[k] == nullptr) return;

    // Define a lambda to delete edges in a vertex (adjacencies)
    ConstUndirectedEdgeCallBack<T> cb = [&](const UndirectedEdge<T>* ptrE) {
      if(ptrE->first->getKey() == k) {
        this->removeEdge(k, ptrE->second->getKey());
        return;
      };

      if(ptrE->second->getKey() == k) {
        this->removeEdge(k, ptrE->first->getKey());
        return;
      };
    };
    
    // Delete all edges of vertex `k` first
    UndirectedGraph<T>::__iterateEdges(*this, cb);

    // Remove vertex `k`
    delete this->__vertices[k];
    this->__vertices.erase(k);

  };

  // [MAIN OPERATION]
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

  // [MAIN OPERATION]
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

  // [MAIN OPERATION]
  // getVertexValue -> T*
  T* getVertexValue(string x) {
    return this->__vertices[x]->getData();
  };

  // [MAIN OPERATION]
  // setVertexValue -> void
  void setVertexValue(string x, T value) {
    this->__vertices[x]->setData(x, value);
  };

  // [MAIN OPERATION]
  // getEdgeValue -> int*
  int* getEdgeValue(string x, string y) {
    UndirectedEdge<T>* e = this->__getEdge(x, y);
    return e ? e->value : nullptr;
  };

  // [MAIN OPERATION]
  // setEdgeValue -> void
  void setEdgeValue(string x, string y, int z) {
    this->__getEdge(x, y)->value = new int(z);
  };

  // [MAIN OPERATION]
  // traverse -> void
  void traverse(string start, ConstVertexCallBack<T>& cb, GraphTraverseType traverseType = DepthFirst) {
    // If starting vertex isn't exist, stop the operation.
    if(this->__vertices.find(start) == this->__vertices.end()) return;

    switch (traverseType) {
      case DepthFirst: {
        stack<Vertex<T>*> S;
        map<string, string> wasInSVertices;

        Vertex<T>* v = this->__vertices[start];

        // At start Vertex to L and wasInSVertices
        S.push(v);
        wasInSVertices[v->getKey()] = v->getKey();

        return this->__depthFirstTraverse(cb, S, wasInSVertices);
      };
      
      case BreadthFirst: {
        queue<Vertex<T>*> Q;
        map<string, string> wasInQVertices;

        Vertex<T>* v = this->__vertices[start];

        // At start Vertex to L and wasInSVertices
        Q.push(v);
        wasInQVertices[v->getKey()] = v->getKey();

        return this->__breadthFirstTraverse(cb, Q, wasInQVertices);
      };
    };
  };

  // [MAIN OPERATION]
  // presentMatrix -> void
  void presentMatrix() {
    typename map<string, Vertex<T>*>::iterator itr = this->__vertices.begin();

    // Print 2 spaces
    cout << "  ";
    while(itr != this->__vertices.end()) {
      cout << itr->second->getKey() << " ";
      itr++;
    };
    cout << endl;

    itr = this->__vertices.begin();

    while(itr != this->__vertices.end()) {
      typename map<string, Vertex<T>*>::iterator temp = this->__vertices.begin();
      
      cout << itr->second->getKey() << " ";
      while(temp != this->__vertices.end()) {
        if(itr->second->hasEdgeWith(temp->second->getKey())) cout << "1 ";
        else cout << "0 ";
        temp++;
      };
      cout << endl;

      itr++;
    };
  };

  // presentList -> void
  void presentList() {
    typename map<string, Vertex<T>*>::iterator itr = this->__vertices.begin();

    while(itr != this->__vertices.end()) {
      typename map<string, Vertex<T>*>::iterator temp = this->__vertices.begin();
      
      cout << itr->second->getKey() << " -> ";
      while(temp != this->__vertices.end()) {
        if(itr->second->hasEdgeWith(temp->second->getKey())) cout << temp->second->getKey() << " ";
        temp++;
      };
      cout << endl;

      itr++;
    };
  };
};

//
// DEFINITION OF STATIC METHODS
//
template<class T>
void UndirectedGraph<T>::__iterateEdges(UndirectedGraph<T>& g, ConstUndirectedEdgeCallBack<T>& cb) {
  if(g.getEdges().size() == 0) return;

  typename vector<UndirectedEdge<T>*>::iterator itrE = g.getEdges().begin();

  while(itrE != g.getEdges().end()) {
    cb(*itrE);
    itrE++;
  };
};

template<class T>
void UndirectedGraph<T>::__depthFirstTraverse(ConstVertexCallBack<T>& cb, stack<Vertex<T>*>& S, map<string, string>& wasInSVertices) {
  if(S.size() == 0) return;

  // Get and pop the top item
  Vertex<T>* v = S.top();
  S.pop();

  // Do something
  cb(v);

  // Get all of its adjacencies
  typename map<string, Vertex<T>*>::iterator itr = v->getLinkedVertices().begin();

  while(itr != v->getLinkedVertices().end()) {
    if(wasInSVertices.find(itr->second->getKey()) != wasInSVertices.end()) {
      itr++;
      continue;
    };

    // Mark vertex is visited
    wasInSVertices[itr->second->getKey()] = itr->second->getKey();

    // Push vertex to stack L
    S.push(itr->second);
    itr++;
  };

  return UndirectedGraph<T>::__depthFirstTraverse(cb, S, wasInSVertices);
};

template<class T>
void UndirectedGraph<T>::__breadthFirstTraverse(ConstVertexCallBack<T>& cb, queue<Vertex<T>*>& Q, map<string, string>& wasInQVertices) {
  if(Q.size() == 0) return;

  // Get and pop the front (first) item
  Vertex<T>* v = Q.front();
  Q.pop();

  // Do something
  cb(v);

  // Get all of its adjacencies
  typename map<string, Vertex<T>*>::iterator itr = v->getLinkedVertices().begin();

  while(itr != v->getLinkedVertices().end()) {
    if(wasInQVertices.find(itr->second->getKey()) != wasInQVertices.end()) {
      itr++;
      continue;
    };

    // Mark vertex is visited
    wasInQVertices[itr->second->getKey()] = itr->second->getKey();

    // Push vertex to stack L
    Q.push(itr->second);
    itr++;
  };

  return UndirectedGraph<T>::__breadthFirstTraverse(cb, Q, wasInQVertices);
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

template<class T>
void printNeigborsOfEachVertexInGraph(UndirectedGraph<T>& g) {
  typename map<string, Vertex<T>*>::iterator itr = g.getVertices().begin();

  while(itr != g.getVertices().end()) {
    cout << "Get neighbor of " << itr->second->getKey() << "...\n";
    printNeighborsOfvX(g, itr->second);
    cout << endl;
    itr++;
  };
};

template<class T>
void printResultOfTraversal(UndirectedGraph<T>& g, string start, GraphTraverseType traverseType) {
  ConstVertexCallBack<T> cb = [](const Vertex<T>* ptrV) {
    cout << ptrV->getKey() << " ";
  };

  if(traverseType == DepthFirst) cout << "Depth First Traverse\n";
  else cout << "Breadth First Traverse\n";
  cout << "Start from " << start << endl;
  g.traverse(start, cb, traverseType);
  cout << endl << endl;
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

  printNeigborsOfEachVertexInGraph(udGraph);

  // Remove C
  cout << "Remove C from graph...\n";
  udGraph.removeVertex(vC->getKey());
  cout << endl;

  printNeigborsOfEachVertexInGraph(udGraph);

  // Traverse
  printResultOfTraversal(udGraph, vA->getKey(), DepthFirst);
  printResultOfTraversal(udGraph, vA->getKey(), BreadthFirst);

  // Present
  cout << "Present Graph in Matrix\n";
  udGraph.presentMatrix();
  cout << endl;

  cout << "Present Graph in List\n";
  udGraph.presentList();
  cout << endl;

  return 0;
};