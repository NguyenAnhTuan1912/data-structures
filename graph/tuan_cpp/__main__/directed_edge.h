#ifndef DIRECTED_EDGE_H_INCLUDED
#define DIRECTED_EDGE_H_INCLUDED

#include <iostream>
#include <unordered_set>
#include <functional>

#include "vertex.h"

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
    std::cout
      << this->first->getKey() << "-"
      << this->second->getKey();
  };

  bool check(std::string x, std::string y) {
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
    size_t firstValue = (std::hash<std::string>()(ue.first->getKey()) / this->firstSupportHashValue);
    size_t secondValue = (std::hash<std::string>()(ue.second->getKey()) / this->secondSupportHashValue);
    return  firstValue + secondValue;
  }

  size_t operator()(const DirectedEdge<T>* ue) const {
    size_t firstValue = (std::hash<std::string>()(ue->first->getKey()) / this->firstSupportHashValue);
    size_t secondValue = (std::hash<std::string>()(ue->second->getKey()) / this->secondSupportHashValue);
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
using DirectedEdgeSet = std::unordered_set<DirectedEdge<T>*, HashDE<T>, KeyEqualDE<T>>;

template<class T>
using ConstDirectedEdgeCallBack = std::function<void(const DirectedEdge<T>* ptrE)>;

#endif // DIRECTED_EDGE_H_INCLUDED