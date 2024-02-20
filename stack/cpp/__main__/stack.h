/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của Stack, mọi thay đổi về cấu trúc
  của Stack sẽ được thay đổi trong này.
*/

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>
#include <exception>

template<class T>
class StackNode {
public:
  T data;
  StackNode* bottom = nullptr;

  StackNode() = default;
  StackNode(T d): data{d} {};
  StackNode(T d, StackNode* sn): data{d}, bottom{sn} {};
};

template<class T>
using StackForEachCallBack = std::function<void(const StackNode<T>* sn)>;

template<class T>
class Stack {
private:
  StackNode<T>* __top = nullptr;
  size_t __size = 0;
  size_t __max = 100;

  void __forEach(StackForEachCallBack<T> cb) {
    StackNode<T>* ptr = this->__top;
    while(ptr != nullptr) {
      cb(ptr);
      ptr = ptr->bottom;
    };
  };

public:
  Stack(size_t max_size = 100): __max{max_size} {};
  Stack(std::initializer_list<T> lst, size_t max_size = 100) {
    typename std::initializer_list<T>::iterator itr = lst.begin();
    typename std::initializer_list<T>::iterator itr_end = lst.end();
    this->__max = max_size;

    while(itr != itr_end) {
      if(this->__size >= this->__max) break;
      StackNode<T>* new_node = new StackNode<T>(*itr, this->__top);
      this->__top = new_node;

      this->__size++;
      itr++;
    };
  };
  ~Stack() {
    this->clear();
  };

  // pop
  void pop() {
    if(this->__top == nullptr) return;

    StackNode<T>* ptr = this->__top;
    this->__top = this->__top->bottom;

    delete ptr;

    this->__size--;
  };

  // push
  void push(T data) {
    if(this->__size >= this->__max) throw std::runtime_error("Maximum size of stack is reached.");

    StackNode<T>* new_node = new StackNode<T>(data, this->__top);
    this->__top = new_node;

    this->__size++;
  };

  // getSize
  size_t getSize() { return this->__size; };

  // print
  void print(StackForEachCallBack<T> cb) {
    this->__forEach(cb);
  };

  // clear
  void clear() {
    while(this->__top != nullptr) this->pop();
  };
};

#endif // STACK_H_INCLUDED
