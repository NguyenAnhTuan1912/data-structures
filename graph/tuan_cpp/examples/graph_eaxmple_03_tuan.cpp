/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Directed Graph
  (Similar with the second implementation of UDG)

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
#include <stack>
#include <queue>
#include <map>
#include <unordered_set>
#include <functional>
#include <iterator>
#include <memory>
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

public:
  Vertex() = default;
  Vertex(string k): __key{k} {};
  Vertex(string k, T* ptrD): __key{k}, __data{ptrD} {};
  Vertex(string k, T d): __key{k}, __data{new T(d)} {};

  const T* getData() const {
    const T* d = this->__data;
    return d;
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

  bool is(string x) {
    return this->__key == x;
  };
};

// Types
template<class T>
using VertexPointer = shared_ptr<Vertex<T>>;

template<class T>
class DirectedEdge {
public:
  int* value = nullptr;
  VertexPointer<T> first = nullptr;
  VertexPointer<T> second = nullptr;

  DirectedEdge(VertexPointer<T> f, VertexPointer<T> s, int v): first{f}, second{s} {
    this->value = new int(v < 0 ? 0 : v);
  };

  void print() {
    cout
      << this->first->getKey() << "-"
      << this->second->getKey();
  };

  bool check(string x, string y) {
    return this->first->is(x) && this->second->is(y);
  };

  bool operator==(const DirectedEdge<T>& ue) const {
    if(ue.first->getKey() == this->first->getKey() && ue.second->getKey() == this->second->getKey())
      return true;
    return false;
  }
};

template<class T>
class HashDE {
private:
  // Static Properties
  static const int firstSupportHashValue;
  static const int secondSupportHashValue;

public:
  size_t operator()(const DirectedEdge<T>& ue) const {
    size_t firstValue = (hash<std::string>()(ue.first->getKey()) / this->firstSupportHashValue);
    size_t secondValue = (hash<std::string>()(ue.second->getKey()) / this->secondSupportHashValue);
    return  firstValue + secondValue;
  }

  size_t operator()(const DirectedEdge<T>* ue) const {
    size_t firstValue = (hash<std::string>()(ue->first->getKey()) / this->firstSupportHashValue);
    size_t secondValue = (hash<std::string>()(ue->second->getKey()) / this->secondSupportHashValue);
    return  firstValue + secondValue;
  }
};

template<class T>
const int HashDE<T>::firstSupportHashValue = 2;

template<class T>
const int HashDE<T>::secondSupportHashValue = 3;

template<class T>
class KeyEqualDE {
public:
  bool operator()(const DirectedEdge<T>* lptrUE, const DirectedEdge<T>* rptrUE) const {
    if(lptrUE->first->getKey() == lptrUE->first->getKey() && lptrUE->second->getKey() == lptrUE->second->getKey())
      return true;
    return false;
  }
};

// Types
template<class T>
using DirectedEdgeSet = unordered_set<DirectedEdge<T>*, HashDE<T>, KeyEqualDE<T>>;

template<class T>
using ConstVertexCallBack = function<void(const VertexPointer<T> ptrV)>;

template<class T>
using ConstDirectedEdgeCallBack = function<void(const DirectedEdge<T>* ptrE)>;

template<class T>
class DirectedGraph {
private:
  DirectedEdgeSet<T> __edges;
  map<string, VertexPointer<T>> __vertices;

  // Static Methods
  static void __depthFirstTraverse(ConstVertexCallBack<T>& cb, const vector<DirectedEdge<T>*> vecUE, stack<VertexPointer<T>>& S, map<string, string>& wasInSVertices);
  static void __breadthFirstTraverse(ConstVertexCallBack<T>& cb, const vector<DirectedEdge<T>*> vecUE, queue<VertexPointer<T>>& Q, map<string, string>& wasInQVertices);

  // Other Methods
  bool __isIn(string k) {
    return __vertices.find(k) != __vertices.end();
  }

public:
  DirectedGraph() = default;
  DirectedGraph(string k, T* v) {
    __vertices[k] = make_shared<Vertex<T>>(k , v);
  };
  DirectedGraph(string k, T v) {
    __vertices[k] = make_shared<Vertex<T>>(k , v);
  };

  const vector<DirectedEdge<T>*> getEdges() const {
    vector<DirectedEdge<T>*> v;

    for(auto& e : this->__edges) {
      v.push_back(e);
    };

    return v;
  };

  // Fundamental Operations

  // [MAIN OPERATION]
  // adjacent -> bool
  bool adjacent(string x, string y) {
    if(!this->__isIn(x) || !this->__isIn(y)) return false;

    for(auto& e : this->__edges) {
      if(e->check(x, y)) return true;
    };

    return false;
  };

  // [MAIN OPERATION]
  // getNeighbors -> vector<Vertext<T>*>
  vector<VertexPointer<T>> getNeighbors(string x) {
    if(!this->__isIn(x)) return {};

    vector<VertexPointer<T>> neighbors;
    for(auto& e : this->__edges) {
      if(e->first->getKey() == x) neighbors.push_back(e->second);
    };
    return neighbors;
  };

  // [MAIN OPERATION]
  // addVertex -> void
  VertexPointer<T> addVertex(string k, T data) {
    if(this->__isIn(k)) return nullptr;
    __vertices[k] = make_shared<Vertex<T>>(k, data);
    return __vertices[k];
  };

  // [MAIN OPERATION]
  // removeVertex -> void
  void removeVertex(string k) {
    // Check if vertex is in map
    typename map<string, VertexPointer<T>>::iterator itrV = __vertices.find(k);
    if(itrV == __vertices.end()) return;
    
    auto itrE = __edges.begin();
    // Remove edges first
    while(itrE != __edges.end()) {
      if((*itrE)->first->getKey() == k || (*itrE)->second->getKey() == k) {
        delete *itrE;
        itrE = __edges.erase(itrE);
      } else itrE++;
    }
    
    // Remove vertex
    itrV->second.reset();
    __vertices.erase(itrV);
  };

  // [MAIN OPERATION]
  // addEdge -> void
  void addEdge(string x, string y, int z) {
    // If one of them isn't exist in graph, terminate operation
    if(!this->__isIn(x) || !this->__isIn(y)) return;

    typename map<string, VertexPointer<T>>::iterator itrXV = __vertices.find(x);
    typename map<string, VertexPointer<T>>::iterator itrYV = __vertices.find(y);

    __edges.insert(new DirectedEdge<T>(itrXV->second, itrYV->second, z));
  };

  void addEdge(VertexPointer<T>& vX, VertexPointer<T>& vY, int z) {
    if(!this->__isIn(vX->getKey()) || !this->__isIn(vY->getKey())) return;
    __edges.insert(new DirectedEdge<T>(vX, vY, z));
  };

  // [MAIN OPERATION]
  // removeEdge -> void
  void removeEdge(string x, string y) {
    if(!this->__isIn(x) || !this->__isIn(y)) return;

    // Iterate through __edges to find edges of x and y
    auto itrE = __edges.begin();
    // Remove edges first
    while(itrE != __edges.end()) {
      if((*itrE)->check(x, y) || (*itrE)->check(y, x)) 
      {
        delete *itrE;
        itrE = __edges.erase(itrE);
      } else itrE++;
    }
  };

  // [MAIN OPERATION]
  // getVertexValue -> T*
  const T* getVertexValue(string x) {
    if(!this->__isIn(x)) return nullptr;
    return __vertices[x]->getData();
  };

  // [MAIN OPERATION]
  // setVertexValue -> void
  void setVertexValue(string x, T value) {
    if(!this->__isIn(x)) return;
    __vertices[x]->setData(value);
  };

  // [MAIN OPERATION]
  // getEdgeValue -> int*
  int* getEdgeValue(string x, string y) {
    for(auto& e : this->__edges) {
      if(e->check(x, y)) return e->value;
    };
    return nullptr;
  };

  // [MAIN OPERATION]
  // setEdgeValue -> void
  void setEdgeValue(string x, string y, int z) {
    for(auto& e : this->__edges) {
      if(e->check(x, y) || e->check(y, x)) {
        e->value = new int(z);
        return;
      };
    };
  };

  // [MAIN OPERATION]
  // traverse -> void
  void traverse(string start, ConstVertexCallBack<T>& cb, GraphTraverseType traverseType = DepthFirst) {
    // If starting vertex isn't exist, stop the operation.
    if(__vertices.find(start) == __vertices.end()) return;

    switch (traverseType) {
      case DepthFirst: {
        stack<VertexPointer<T>> S;
        map<string, string> wasInSVertices;

        VertexPointer<T> v = __vertices[start];

        // At start Vertex to L and wasInSVertices
        S.push(v);
        wasInSVertices[v->getKey()] = v->getKey();
        return this->__depthFirstTraverse(cb, this->getEdges(), S, wasInSVertices);
      };
      
      case BreadthFirst: {
        queue<VertexPointer<T>> Q;
        map<string, string> wasInQVertices;

        VertexPointer<T> v = __vertices[start];

        // At start Vertex to L and wasInSVertices
        Q.push(v);
        wasInQVertices[v->getKey()] = v->getKey();
        return this->__breadthFirstTraverse(cb, this->getEdges(), Q, wasInQVertices);
      };
    };
  };

  // [MAIN OPERATION]
  // presentMatrix -> void
  void presentMatrix() {
    // Print 2 spaces
    cout << "  ";
    for(auto& v : __vertices) {
      cout << v.second->getKey() << " ";
    };
    cout << endl;

    for(auto& v : __vertices) {
      typename map<string, VertexPointer<T>>::iterator itr = this->__vertices.begin();

      cout << v.second->getKey() << " ";
      for(auto& v2 : __vertices) {
        if(__edges.find(new DirectedEdge<T>(v.second, v2.second, 0)) != __edges.end()) cout << "1 ";
        else cout << "0 ";
      }
      cout << endl;
    };
  };

  // presentList -> void
  void presentList() {
    for(auto& v : __vertices) {

      cout << v.second->getKey() << " -> ";
      for(auto& e : __edges) {
        if(e->first->is(v.second->getKey())) cout << e->second->getKey() << " ";
      };
      cout << endl;
    };
  };
};

//
// DEFINITION OF STATIC METHODS
//
template<class T>
void DirectedGraph<T>::__depthFirstTraverse(
  ConstVertexCallBack<T>& cb, const vector<DirectedEdge<T>*> vecUE,
  stack<VertexPointer<T>>& S, map<string, string>& wasInSVertices
) {
  if(S.size() == 0) return;

  // Get and pop the top item
  VertexPointer<T> v = S.top();
  S.pop();

  // Do something
  cb(v);
  
  for(auto& e : vecUE) {
    VertexPointer<T> vPtr;

    if(e->first->is(v->getKey())) vPtr = e->second;

    if(!vPtr) continue;

    if(wasInSVertices.find(vPtr->getKey()) != wasInSVertices.end()) {
      continue;
    };

    // Mark vertex is visited
    wasInSVertices[vPtr->getKey()] = vPtr->getKey();

    // Push vertex to stack L
    S.push(vPtr);
  };

  return DirectedGraph<T>::__depthFirstTraverse(cb, vecUE, S, wasInSVertices);
};

template<class T>
void DirectedGraph<T>::__breadthFirstTraverse(
  ConstVertexCallBack<T>& cb, const vector<DirectedEdge<T>*> vecUE,
  queue<VertexPointer<T>>& Q, map<string, string>& wasInQVertices
) {
  if(Q.size() == 0) return;

  // Get and pop the front (first) item
  VertexPointer<T> v = Q.front();
  Q.pop();

  // Do something
  cb(v);

  for(auto& e : vecUE) {
    VertexPointer<T> vPtr;

    if(e->first->is(v->getKey())) vPtr = e->second;

    if(!vPtr) continue;

    if(wasInQVertices.find(vPtr->getKey()) != wasInQVertices.end()) {
      continue;
    };

    // Mark vertex is visited
    wasInQVertices[vPtr->getKey()] = vPtr->getKey();

    // Push vertex to stack L
    Q.push(vPtr);
  };

  return DirectedGraph<T>::__breadthFirstTraverse(cb, vecUE, Q, wasInQVertices);
};

// Other functions
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

int main() {
  // Initialize DirectedGraph
  DirectedGraph<int> dGraph;

  // Add vertices
  VertexPointer<int> vA = dGraph.addVertex("A", 1);
  VertexPointer<int> vB = dGraph.addVertex("B", 21);
  VertexPointer<int> vC = dGraph.addVertex("C", 3);
  VertexPointer<int> vD = dGraph.addVertex("D", 8);
  VertexPointer<int> vE = dGraph.addVertex("E", 14);
  VertexPointer<int> vF = dGraph.addVertex("F", 2);
  VertexPointer<int> vG = dGraph.addVertex("G", 9);
  VertexPointer<int> vH = dGraph.addVertex("H", 33);

  // Add edges
  dGraph.addEdge(vA, vB, 2);
  dGraph.addEdge(vA, vD, 3);
  dGraph.addEdge(vA, vG, 5);
  dGraph.addEdge(vB, vA, 10);
  dGraph.addEdge(vB, vC, 1);
  dGraph.addEdge(vB, vE, 6);
  dGraph.addEdge(vC, vE, 5);
  dGraph.addEdge(vD, vF, 6);
  dGraph.addEdge(vE, vH, 7);
  dGraph.addEdge(vG, vH, 11);

  // Perform some operations
  cout << "Check adjacencies\n";
  printAdjacentCheckingResult(dGraph, vA, vB);
  printAdjacentCheckingResult(dGraph, vA, vD);
  printAdjacentCheckingResult(dGraph, vA, vG);
  printAdjacentCheckingResult(dGraph, vF, vD);
  printAdjacentCheckingResult(dGraph, vE, vH);
  printAdjacentCheckingResult(dGraph, vA, vC);
  printAdjacentCheckingResult(dGraph, vD, vC);
  printAdjacentCheckingResult(dGraph, vG, vH);
  printAdjacentCheckingResult(dGraph, vC, vE);
  printAdjacentCheckingResult(dGraph, vF, vG);
  cout << endl;

  cout << "Get values of some edges\n";
  printEdgeValueResult(dGraph, vA, vB);
  printEdgeValueResult(dGraph, vB, vA);
  printEdgeValueResult(dGraph, vD, vA);
  printEdgeValueResult(dGraph, vF, vD);
  printEdgeValueResult(dGraph, vD, vF);
  printEdgeValueResult(dGraph, vE, vH);
  printEdgeValueResult(dGraph, vA, vC);
  printEdgeValueResult(dGraph, vD, vC);
  printEdgeValueResult(dGraph, vG, vH);
  printEdgeValueResult(dGraph, vE, vC);
  printEdgeValueResult(dGraph, vF, vG);
  cout << endl;

  cout << "Neighbors of some vertices\n";
  printNeighborsOfvX(dGraph, vA);
  printNeighborsOfvX(dGraph, vB);
  printNeighborsOfvX(dGraph, vC);
  printNeighborsOfvX(dGraph, vD);
  printNeighborsOfvX(dGraph, vE);
  printNeighborsOfvX(dGraph, vF);
  printNeighborsOfvX(dGraph, vG);
  printNeighborsOfvX(dGraph, vH);
  cout << endl;

  cout << "Delete a vertex (vA)\n";
  dGraph.removeVertex(vA->getKey());
  printAdjacentCheckingResult(dGraph, vA, vB);
  printAdjacentCheckingResult(dGraph, vA, vD);
  printAdjacentCheckingResult(dGraph, vA, vG);
  cout << endl;

  dGraph.setVertexValue("B", 1233);
  cout << "New value of vB: " << *(dGraph.getVertexValue("B")) << endl;

  dGraph.setEdgeValue("E", "C", 999);
  printEdgeValueResult(dGraph, vC, vE);
  cout << endl;

  // Traverse
  printResultOfTraversal(dGraph, vB->getKey(), DepthFirst);
  printResultOfTraversal(dGraph, vB->getKey(), BreadthFirst);

  // Present
  cout << "Present Graph in Matrix\n";
  dGraph.presentMatrix();
  cout << endl;

  cout << "Present Graph in List\n";
  dGraph.presentList();
  cout << endl;

  return 0;
};