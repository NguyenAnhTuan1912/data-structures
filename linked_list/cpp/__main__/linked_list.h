/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của LinkedList, mọi thay đổi về cấu trúc
  của LinkedList sẽ được thay đổi trong này.
*/
#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED
#pragma once

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

template<class T>
class Node {
public:
  T data;
  Node* next = nullptr;

  Node() = default;
  Node(T d): data{d} {};
  Node(T d, Node* n): data{d}, next{n} {};
};

template<class T>
using CompareFn = std::function<bool(T&, T&)>;

template<class T>
using LListForEachCallBack = std::function<void(Node<T>*, int index)>;

template<class T>
class LinkedList {
private:
  Node<T>* __head = nullptr;
  Node<T>* __tail = nullptr;
  size_t __size = 0;

  void __forEach(LListForEachCallBack<T> cb = NULL) {
    Node<T>* ptr = this->__head;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->next;
      index++;
    };
  };

public:
  LinkedList() = default;
  LinkedList(std::initializer_list<T> lst) {
    typename std::initializer_list<T>::iterator itr = lst.begin();
    typename std::initializer_list<T>::iterator last_item_itr = lst.end();
    last_item_itr--;

    // Setup
    this->__head = new Node<T>(*itr);
    this->__tail = this->__head;
    this->__size = lst.size();

    if(itr == last_item_itr) return;

    this->__tail = new Node<T>(*last_item_itr);
    this->__head->next = this->__tail;

    Node<T>* ptr = this->__head;

    itr++;

    // Assign
    while(itr != last_item_itr) {
      ptr->next = new Node<T>(*itr, this->__tail);
      ptr = ptr->next;
      itr++;
    };
  };
  ~LinkedList() {
    this->clear();
  };

  // getAt
  Node<T>* getAt(int n) {
    if(this->__head == nullptr) return nullptr;

    if(n <= 0) return this->__head;
    if(n >= this->__size) return this->__tail;

    Node<T>* ptr = this->__head;
    int c = 0;

    while(c < n) {
      ptr = ptr->next;
      c++;
    };

    return ptr;
  };

  // insertFirst
  void insertFirst(T data) {
    if(this->__head == nullptr) {
      this->__head = new Node<T>(data);
      this->__tail = this->__head;

      this->__size++;

      return;
    };

    this->__head = new Node<T>(data, this->__head);

    this->__size++;
  };

  // insertLast
  void insertLast(T data) {
    if(this->__head == nullptr) {
      this->__head = new Node<T>(data);
      this->__tail = this->__head;

      this->__size++;

      return;
    };

    Node<T>* new_node = new Node<T>(data);
    this->__tail->next = new_node;
    this->__tail = new_node;

    this->__size++;
  };

  // insertAt
  void insertAt(T data, int n) {
    if(this->__head == nullptr || n < 0) {
      this->insertFirst(data);
      return;
    };

    if(this->__head == nullptr || n >= this->__size) {
      this->insertLast(data);
      return;
    };

    Node<T>* before = this->getAt(n - 1);
    before->next = new Node<T>(data, before->next);

    this->__size++;
  };

  // insertOrderBy
  void insertOrderBy(T data, CompareFn<T> compare) {
    if(this->__head == nullptr) {
      this->insertLast(data);
      return;
    };

    Node<T>* ptr = this->__head;
    Node<T>* before = nullptr;

    while(ptr != nullptr) {
      if(compare(ptr->data, data)) break;

      before = ptr;
      ptr = ptr->next;
    };

    if(ptr == nullptr) {
      this->insertLast(data);
      return;
    } else if(ptr == this->__head) {
      this->insertFirst(data);
      return;
    };

    Node<T>* new_node = new Node<T>(data, ptr);
    if(before != nullptr) before->next = new_node;

    this->__size++;
  };

  // removeFirst
  void removeFirst() {
    if(this->__head == nullptr) return;

    Node<T>* ptr = this->__head;
    this->__head = this->__head->next;
    ptr->next = nullptr;

    delete ptr;

    this->__size--;
  };

  // removeLast
  void removeLast() {
    if(this->__head == nullptr) return;

    Node<T>* before = this->getAt(this->__size - 2);
    before->next = nullptr;

    delete this->__tail;

    this->__tail = before;

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

    Node<T>* before = this->getAt(n - 1);
    Node<T>* ptr = before->next;

    before->next = ptr->next;
    ptr->next = nullptr;

    delete ptr;

    this->__size--;
  };

  void print(LListForEachCallBack<T> cb) {
    if(this->__head == nullptr) {
      std::cout << "Empty list!!!\n";
      return;
    };
    std::cout << "Size: " << this->__size << std::endl;
    this->__forEach(cb);
  };

  void clear() {
    Node<T>* ptr = this->__head;

    while(ptr != nullptr) {
      this->__head = this->__head->next;
      delete ptr;
      ptr = this->__head;
    };

    this->__size = 0;
  };
};

#endif // LINKED_LIST_H_INCLUDED
