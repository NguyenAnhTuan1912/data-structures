#ifndef UNDIRECTED_EDGE_H_INCLUDED
#define UNDIRECTED_EDGE_H_INCLUDED

#include <iostream>
#include <unordered_set>
#include <functional>

#include "vertex.h"

template<class T>
class UndirectedEdge {
public:
  int* value = nullptr;
  VertexPointer<T> first = nullptr;
  VertexPointer<T> second = nullptr;

  UndirectedEdge(VertexPointer<T> f, VertexPointer<T> s, int v): first{f}, second{s} {
    this->value = new int(v < 0 ? 0 : v);
  };

  void print() {
    std::cout
      << this->first->getKey() << "-"
      << this->second->getKey();
  };

  bool check(std::string x, std::string y) {
    return (this->first->is(x) && this->second->is(y)) || (this->first->is(y) && this->second->is(x));
  };

  bool operator==(const UndirectedEdge<T>& ue) const {
    if(
      (ue.first->getKey() == this->first->getKey() && ue.second->getKey() == this->second->getKey())
      || (ue.first->getKey() == this->second->getKey() && ue.second->getKey() == this->first->getKey())
    ) return true;
    return false;
  }
};

template<class T>
class HashUE {
public:
  size_t operator()(const UndirectedEdge<T>& ue) const {
    return std::hash<std::string>()(ue.first->getKey()) + std::hash<std::string>()(ue.second->getKey());
  }

  size_t operator()(const UndirectedEdge<T>* ue) const {
    return std::hash<std::string>()(ue->first->getKey()) + std::hash<std::string>()(ue->second->getKey());
  }
};

template<class T>
class KeyEqualUE {
public:
  bool operator()(const UndirectedEdge<T>* lptrUE, const UndirectedEdge<T>* rptrUE) const {
    if(
      (lptrUE->first->getKey() == lptrUE->first->getKey() && lptrUE->second->getKey() == lptrUE->second->getKey())
      || (lptrUE->first->getKey() == lptrUE->second->getKey() && lptrUE->second->getKey() == lptrUE->first->getKey())
    ) return true;
    return false;
  }
};

// Types
template<class T>
using UndirectedEdgeSet = std::unordered_set<UndirectedEdge<T>*, HashUE<T>, KeyEqualUE<T>>;

template<class T>
using ConstUndirectedEdgeCallBack = std::function<void(const UndirectedEdge<T>* ptrE)>;

#endif // UNDIRECTED_EDGE_H_INCLUDED