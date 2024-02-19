/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của DoublyLinkedList, mọi thay đổi về cấu trúc
  của DoublyLinkedList sẽ được thay đổi trong này.
*/
#ifndef DOUBLY_LINKED_LIST_H_INCLUDED
#define DOUBLY_LINKED_LIST_H_INCLUDED
#pragma once

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

template<class T>
class DoubleNode {
public:
  T data;
  DoubleNode* next = nullptr;
  DoubleNode* prev = nullptr;

  DoubleNode() = default;
  DoubleNode(T d): data{d} {};
  DoubleNode(T d, DoubleNode* p, DoubleNode* n): data{d}, prev{p}, next{n} {};
};

template<class T>
using CompareFn = std::function<bool(T&, T&)>;

template<class T>
using DoublyLListForEachCallBack = std::function<void(DoubleNode<T>*, int index)>;

template<class T>
class DoublyLinkedList {
private:
  DoubleNode<T>* __head = nullptr;
  DoubleNode<T>* __tail = nullptr;
  size_t __size = 0;

  void __forEachFromHead(DoublyLListForEachCallBack<T> cb = NULL) {
    if(this->__head == nullptr) return;

    DoubleNode<T>* ptr = this->__head;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->next;
      index++;
    };
  };

  void __forEachFromTail(DoublyLListForEachCallBack<T> cb = NULL) {
    if(this->__tail == nullptr) return;

    DoubleNode<T>* ptr = this->__tail;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->prev;
      index++;
    };
  };

public:
  DoublyLinkedList() = default;
  DoublyLinkedList(std::initializer_list<T> lst) {
    typename std::initializer_list<T>::iterator itr = lst.begin();
    typename std::initializer_list<T>::iterator last_item_itr = lst.end();
    last_item_itr--;

    // Setup
    this->__head = new DoubleNode<T>(*itr);
    this->__tail = this->__head;
    this->__size = lst.size();

    if(last_item_itr == itr) return;

    this->__tail = new DoubleNode<T>(*last_item_itr);
    this->__head->next = this->__tail;
    this->__tail->prev = this->__head;
    DoubleNode<T>* ptr = this->__head;

    itr++;

    while(itr != last_item_itr) {
      ptr->next = new DoubleNode<T>(*itr, ptr, this->__tail);
      this->__tail->prev = ptr->next;
      ptr = ptr->next;
      itr++;
    };
  };
  ~DoublyLinkedList() {
    this->clear();
  };

  DoubleNode<T>* getAt(int n) {
    if(this->__head == nullptr) return nullptr;
    DoubleNode<T>* ptr = this->__head;
    bool canStartFromHead = true;

    if(n <= 0) return this->__head;
    if(n >= this->__size) return this->__tail;

    if(n > (this->__size / 2)) {
      ptr = this->__tail;
      canStartFromHead = false;
      n = this->__size - n - 1;
    };

    int c = 0;

    while(c < n) {
      if(canStartFromHead) ptr = ptr->next;
      else ptr = ptr->prev;
      c++;
    };

    return ptr;
  };

  // insertFirst
  void insertFirst(T data) {
    if(this->__head == nullptr) {
      this->__head = new DoubleNode<T>(data);
      this->__tail = this->__head;

      this->__size++;

      return;
    };

    DoubleNode<T>* new_node = new DoubleNode<T>(data, nullptr, this->__head);

    this->__head->prev = new_node;
    this->__head = new_node;

    this->__size++;
  };

  // insertLast
  void insertLast(T data) {
    if(this->__head == nullptr) {
      this->__head = new DoubleNode<T>(data);
      this->__tail = this->__head;

      this->__size++;

      return;
    };

    DoubleNode<T>* new_node = new DoubleNode<T>(data, this->__tail, nullptr);

    this->__tail->next = new_node;
    this->__tail = new_node;

    this->__size++;
  };

  // insertAt
  void insertAt(T data, int n) {
    if(n <= 0 || this->__head == nullptr) {
      this->insertFirst(data);
      return;
    };
    if(n >= this->__size) {
      this->insertLast(data);
      return;
    };

    DoubleNode<T>* ptr = this->getAt(n);
    DoubleNode<T>* new_node = new DoubleNode<T>(data, ptr->prev, ptr);

    ptr->prev->next = new_node;
    ptr->prev = new_node;

    this->__size++;
  };

  // insertOrderBy
  void insertOrderBy(T data, CompareFn<T> compare) {
    if(this->__head == nullptr) {
      this->insertFirst(data);
      return;
    };

    DoubleNode<T>* ptr = this->__head;

    while(ptr != nullptr) {
      if(compare(ptr->data, data)) break;

      ptr = ptr->next;
    };

    if(ptr == nullptr) {
      this->insertLast(data);
      return;
    } else if(ptr == this->__head) {
      this->insertFirst(data);
      return;
    };

    DoubleNode<T>* new_node = new DoubleNode<T>(data, ptr->prev, ptr);

    ptr->prev->next = new_node;
    ptr->prev = new_node;

    this->__size++;
  };

  // removeFirst
  void removeFirst() {
    if(this->__head == nullptr) return;

    DoubleNode<T>* ptr = this->__head;

    ptr = this->__head->next;
    ptr->prev = nullptr;
    this->__head->next = nullptr;

    delete this->__head;

    this->__head = ptr;

    this->__size--;
  };

  // removeLast
  void removeLast() {
    if(this->__tail == nullptr) return;

    DoubleNode<T>* ptr = this->__tail;

    ptr = this->__tail->prev;
    this->__tail->prev = nullptr;
    ptr->next = nullptr;

    delete this->__tail;

    this->__tail = ptr;

    this->__size--;
  };

  // removeAt
  void removeAt(int n) {
    if(this->__head == nullptr) return;
    if(n <= 0) {
      this->removeFirst();
      return;
    };
    if(n >= this->__size) {
      this->removeLast();
      return;
    };

    DoubleNode<T>* ptr = this->getAt(n);

    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;

    delete ptr;

    this->__size--;
  };

  void printFromHead(DoublyLListForEachCallBack<T> cb) {
    if(this->__head == nullptr) {
      std::cout << "Empty list!!!\n";
      return;
    };
    std::cout << "Size: " << this->__size << std::endl;
    this->__forEachFromHead(cb);
  };

  void printFromTail(DoublyLListForEachCallBack<T> cb) {
    if(this->__tail == nullptr) {
      std::cout << "Empty list!!!\n";
      return;
    };
    std::cout << "Size: " << this->__size << std::endl;
    this->__forEachFromTail(cb);
  };

  void clear() {
    DoubleNode<T>* ptr = this->__head;

    while(ptr != nullptr) {
      this->__head = this->__head->next;
      delete ptr;
      ptr = this->__head;
    };

    this->__size = 0;
  };
};

#endif // DOUBLY_LINKED_LIST_H_INCLUDED
