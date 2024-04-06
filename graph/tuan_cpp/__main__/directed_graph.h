#ifndef DIRECTED_GRAPH_H_INCLUDED
#define DIRECTED_GRAPH_H_INCLUDED

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

#include "vertex.h"
#include "directed_edge.h"

template<class T>
class DirectedGraph {
private:
  DirectedEdgeSet<T> __edges;
  std::map<std::string, VertexPointer<T>> __vertices;

  // Static Methods
  static void __depthFirstTraverse(
    ConstVertexCallBack<T>& cb, const std::vector<DirectedEdge<T>*> vecUE,
    std::stack<VertexPointer<T>>& S, std::map<std::string, std::string>& wasInSVertices);
  static void __breadthFirstTraverse(
    ConstVertexCallBack<T>& cb, const std::vector<DirectedEdge<T>*> vecUE,
    std::queue<VertexPointer<T>>& Q, std::map<std::string, std::string>& wasInQVertices);

  // Other Methods
  bool __isIn(std::string k) {
    return __vertices.find(k) != __vertices.end();
  }

public:
  DirectedGraph() = default;
  DirectedGraph(std::string k, T* v) {
    __vertices[k] = std::make_shared<Vertex<T>>(k , v);
  };
  DirectedGraph(std::string k, T v) {
    __vertices[k] = std::make_shared<Vertex<T>>(k , v);
  };

  const std::vector<DirectedEdge<T>*> getEdges() const {
    std::vector<DirectedEdge<T>*> v;

    for(auto& e : this->__edges) {
      v.push_back(e);
    };

    return v;
  };

  // Fundamental Operations

  // [MAIN OPERATION]
  // adjacent -> bool
  bool adjacent(std::string x, std::string y) {
    if(!this->__isIn(x) || !this->__isIn(y)) return false;

    for(auto& e : this->__edges) {
      if(e->check(x, y)) return true;
    };

    return false;
  };

  // [MAIN OPERATION]
  // getNeighbors -> std::vector<Vertext<T>*>
  std::vector<VertexPointer<T>> getNeighbors(std::string x) {
    if(!this->__isIn(x)) return {};

    std::vector<VertexPointer<T>> neighbors;
    for(auto& e : this->__edges) {
      if(e->first->getKey() == x) neighbors.push_back(e->second);
    };
    return neighbors;
  };

  // [MAIN OPERATION]
  // addVertex -> void
  VertexPointer<T> addVertex(std::string k, T data) {
    if(this->__isIn(k)) return nullptr;
    __vertices[k] = std::make_shared<Vertex<T>>(k, data);
    return __vertices[k];
  };

  // [MAIN OPERATION]
  // removeVertex -> void
  void removeVertex(std::string k) {
    // Check if vertex is in std::map
    typename std::map<std::string, VertexPointer<T>>::iterator itrV = __vertices.find(k);
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
  void addEdge(std::string x, std::string y, int z) {
    // If one of them isn't exist in graph, terminate operation
    if(!this->__isIn(x) || !this->__isIn(y)) return;

    typename std::map<std::string, VertexPointer<T>>::iterator itrXV = __vertices.find(x);
    typename std::map<std::string, VertexPointer<T>>::iterator itrYV = __vertices.find(y);

    __edges.insert(new DirectedEdge<T>(itrXV->second, itrYV->second, z));
  };

  void addEdge(VertexPointer<T>& vX, VertexPointer<T>& vY, int z) {
    if(!this->__isIn(vX->getKey()) || !this->__isIn(vY->getKey())) return;
    __edges.insert(new DirectedEdge<T>(vX, vY, z));
  };

  // [MAIN OPERATION]
  // removeEdge -> void
  void removeEdge(std::string x, std::string y) {
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
  const T* getVertexValue(std::string x) {
    if(!this->__isIn(x)) return nullptr;
    return __vertices[x]->getData();
  };

  // [MAIN OPERATION]
  // setVertexValue -> void
  void setVertexValue(std::string x, T value) {
    if(!this->__isIn(x)) return;
    __vertices[x]->setData(value);
  };

  // [MAIN OPERATION]
  // getEdgeValue -> int*
  int* getEdgeValue(std::string x, std::string y) {
    for(auto& e : this->__edges) {
      if(e->check(x, y)) return e->value;
    };
    return nullptr;
  };

  // [MAIN OPERATION]
  // setEdgeValue -> void
  void setEdgeValue(std::string x, std::string y, int z) {
    for(auto& e : this->__edges) {
      if(e->check(x, y) || e->check(y, x)) {
        e->value = new int(z);
        return;
      };
    };
  };

  // [MAIN OPERATION]
  // traverse -> void
  void traverse(std::string start, ConstVertexCallBack<T>& cb, GraphTraverseType traverseType = DepthFirst) {
    // If starting vertex isn't exist, stop the operation.
    if(__vertices.find(start) == __vertices.end()) return;

    switch (traverseType) {
      case DepthFirst: {
        std::stack<VertexPointer<T>> S;
        std::map<std::string, std::string> wasInSVertices;

        VertexPointer<T> v = __vertices[start];

        // At start Vertex to L and wasInSVertices
        S.push(v);
        wasInSVertices[v->getKey()] = v->getKey();
        return this->__depthFirstTraverse(cb, this->getEdges(), S, wasInSVertices);
      };
      
      case BreadthFirst: {
        std::queue<VertexPointer<T>> Q;
        std::map<std::string, std::string> wasInQVertices;

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
    std::cout << "  ";
    for(auto& v : __vertices) {
      std::cout << v.second->getKey() << " ";
    };
    std::cout << std::endl;

    for(auto& v : __vertices) {
      typename std::map<std::string, VertexPointer<T>>::iterator itr = this->__vertices.begin();

      std::cout << v.second->getKey() << " ";
      for(auto& v2 : __vertices) {
        if(__edges.find(new DirectedEdge<T>(v.second, v2.second, 0)) != __edges.end()) std::cout << "1 ";
        else std::cout << "0 ";
      }
      std::cout << std::endl;
    };
  };

  // presentList -> void
  void presentList() {
    for(auto& v : __vertices) {
      std::cout << v.second->getKey() << " -> ";
      for(auto& e : __edges) {
        if(e->first->is(v.second->getKey())) std::cout << e->second->getKey() << " ";
      };
      std::cout << std::endl;
    };
  };
};

//
// DEFINITION OF STATIC METHODS
//
template<class T>
void DirectedGraph<T>::__depthFirstTraverse(
  ConstVertexCallBack<T>& cb, const std::vector<DirectedEdge<T>*> vecUE,
  std::stack<VertexPointer<T>>& S, std::map<std::string, std::string>& wasInSVertices
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

    // Push vertex to std::stack L
    S.push(vPtr);
  };

  return DirectedGraph<T>::__depthFirstTraverse(cb, vecUE, S, wasInSVertices);
};

template<class T>
void DirectedGraph<T>::__breadthFirstTraverse(
  ConstVertexCallBack<T>& cb, const std::vector<DirectedEdge<T>*> vecUE,
  std::queue<VertexPointer<T>>& Q, std::map<std::string, std::string>& wasInQVertices
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

    // Push vertex to std::stack L
    Q.push(vPtr);
  };

  return DirectedGraph<T>::__breadthFirstTraverse(cb, vecUE, Q, wasInQVertices);
};

#endif // DIRECTED_GRAPH_H_INCLUDED