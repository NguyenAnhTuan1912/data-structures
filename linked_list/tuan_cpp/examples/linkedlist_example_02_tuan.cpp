/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Doubly Linked List:
  - Node
  - DoublyLinkedList

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
  Node<T>* __prev = nullptr;

public:
  Node() = default;
  Node(T data): __data{data} {};
  Node(T data, Node<T>* prev, Node<T>* next): __data{data}, __next{next}, __prev{prev} {};

  void setNext(Node<T>* ptr_node) { this->__next = ptr_node; };
  void setPrev(Node<T>* ptr_node) { this->__prev = ptr_node; };
  void setData(T data) { this->__data = data; };
  Node<T>* getNext() { return this->__next; };
  Node<T>* getPrev() { return this->__prev; };
  T getData() { return this->__data; };
};

// Install DoublyLinkedList
template<class T>
class DoublyLinkedList {
private:
  Node<T>* __head;
  Node<T>* __tail;

public:
  DoublyLinkedList() {
    this->__head = new Node<T>();
    this->__tail = this->__head;
  };
  DoublyLinkedList(initializer_list<T> lst) {
    typename initializer_list<T>::iterator itr = lst.begin();
    typename initializer_list<T>::iterator last_item_itr = lst.end();
    last_item_itr--;

    // Setup
    this->__head = new Node<T>(*itr);
    this->__tail = this->__head;

    if(last_item_itr == itr) return;

    this->__tail = new Node<T>(*last_item_itr);

    this->__head->setNext(this->__tail);
    this->__tail->setPrev(this->__head);

    Node<T>* ptr = this->__head;
    itr++;

    while(itr != last_item_itr) {
      Node<T>* ptr_node = new Node<T>(*itr, ptr, this->__tail);
      ptr->setNext(ptr_node);
      this->__tail->setPrev(ptr_node);
      ptr = ptr->getNext();
      itr++;
    }
  };

  void PrintFromHead() {
    Node<T>* ptr = this->__head;
    while(ptr != nullptr) {
      cout << ptr->getData() << " ";
      ptr = ptr->getNext();
    };
  };

  void PrintFromTail() {
    Node<T>* ptr = this->__tail;
    while(ptr != nullptr) {
      cout << ptr->getData() << " ";
      ptr = ptr->getPrev();
    };
  };
};

int main() {
  // Note: run with C++14 (in tuan's computer)
  cout << "C++ version: " << __cplusplus <<endl;

  cout << endl;

  DoublyLinkedList<int> lst = { 22, 13, -4, 5, 70, 81, 1240, 203 };

  cout << "Print from head: \n";
  lst.PrintFromHead();

  cout << endl;

  cout << "Print from tail: \n";
  lst.PrintFromTail();

  return 0;
};
