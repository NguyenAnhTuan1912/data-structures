/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của nexted list:
  - Node
  - nextedList

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

// Install nextedList
template<class T>
class nextedList {
private:
  Node<T> __head;
  Node<T> __tail;

public:
  nextedList() {
    this->__head.setNext(this->__tail);
  };
  nextedList(initializer_list<T> lst) {
    typename initializer_list<T>::iterator itr = lst.begin();
    typename initializer_list<T>::iterator near_end_itr = lst.end();
    near_end_itr--;

    this->__tail = Node<T>(*near_end_itr);
    this->__head = Node<T>(*itr, &this->__tail);
    Node<T>* ptr = &this->__head;
    itr++;

    while(itr != near_end_itr) {
      Node<T>* ptr_node = new Node<T>(*itr, &this->__tail);
      ptr->setNext(ptr_node);
      ptr = ptr->getNext();
      itr++;
    }
  };
};

int main() {
  // Note: run with C++14 (in tuan's computer)
  cout << "C++ version: " << __cplusplus <<endl;
  return 0;
};
