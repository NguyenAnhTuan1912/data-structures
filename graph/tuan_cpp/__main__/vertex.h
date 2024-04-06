#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include <iostream>
#include <memory>
#include <functional>

template<class T>
class Vertex {
private:
  std::string __key = "";
  T* __data = nullptr;

public:
  Vertex() = default;
  Vertex(std::string k): __key{k} {};
  Vertex(std::string k, T* ptrD): __key{k}, __data{ptrD} {};
  Vertex(std::string k, T d): __key{k}, __data{new T(d)} {};

  const T* getData() const {
    const T* d = this->__data;
    return d;
  };

  std::string getKey() const {
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

  bool is(std::string x) {
    return this->__key == x;
  };
};

// Types
template<class T>
using VertexPointer = std::shared_ptr<Vertex<T>>;

template<class T>
using ConstVertexCallBack = std::function<void(const VertexPointer<T> ptrV)>;

#endif // VERTEX_H_INCLUDED