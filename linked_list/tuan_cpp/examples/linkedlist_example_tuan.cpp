/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Singly Linked List:
  - Node
  - LinkedList

  Ấn build để nó hiện ra từng message của lỗi.
  Để thực thi và xem các ví dụ thì comment những chỗ code lỗi lại.
*/

#include <iostream>
#include <initializer_list>
#include <iterator>

using namespace std;

// Install Node
template<class T>
class Node {
private:
  T __data;
  Node<T>* __next = nullptr;

public:
  Node() = default;
  Node(T data): __data{data} {};
  Node(T data, Node<T>* next): __data{data}, __next{next} {};

  void setNext(Node<T>* ptr_node) { this->__next = ptr_node; };
  void setData(T data) { this->__data = data; };
  Node<T>* getNext() { return this->__next; };
  T getData() { return this->__data; };
};

// Install LinkedList
template<class T>
class LinkedList {
private:
  Node<T>* __head;
  Node<T>* __tail;

public:
  LinkedList() {
    this->__head = new Node<T>();
    this->__tail = this->__head;
  };
  LinkedList(initializer_list<T> lst) {
    typename initializer_list<T>::iterator itr = lst.begin();
    typename initializer_list<T>::iterator last_item_itr = lst.end();
    last_item_itr--;

    // Setup
    this->__head = new Node<T>(*itr);
    this->__tail = this->__head;

    if(last_item_itr == itr) return;

    this->__tail = new Node<T>(*last_item_itr);
    this->__head->setNext(this->__tail);
    Node<T>* ptr = this->__head;

    itr++;

    while(itr != last_item_itr) {
      Node<T>* ptr_node = new Node<T>(*itr, this->__tail);
      ptr->setNext(ptr_node);
      ptr = ptr->getNext();
      itr++;
    }
  };

  void Print() {
    Node<T>* ptr = this->__head;
    while(ptr != nullptr) {
      cout << ptr->getData() << " ";
      ptr = ptr->getNext();
    };
  };
};

int main() {
  // Note: run with C++14 (in tuan's computer)
  cout << "C++ version: " << __cplusplus <<endl;

  cout << endl;

  LinkedList<int> lst = { 100, 20, 22, -10, -2, 34, 45 };
  lst.Print();

  return 0;
};
