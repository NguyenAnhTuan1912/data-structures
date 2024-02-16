/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Circular Linked List (based on Singly Linked List):
  - Node
  - CircularLinkedList

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

// Install CircularLinkedList
template<class T>
class CircularLinkedList {
private:
  Node<T> __first;

public:
  CircularLinkedList() = default;
  CircularLinkedList(initializer_list<T> lst) {
    typename initializer_list<T>::iterator itr = lst.begin();

    this->__first = Node<T>(*itr);
    Node<T>* ptr = &this->__first;
    itr++;

    while(itr != lst.end()) {
      Node<T>* ptr_node = new Node<T>(*itr, &this->__first);
      ptr->setNext(ptr_node);
      ptr = ptr->getNext();
      itr++;
    }
  };

  void Print(int times = 1) {
    Node<T>* ptr = &this->__first;
    int c = 0;

    // Print first
    cout << ptr->getData() << " ";
    ptr = ptr->getNext();

    while(ptr != &this->__first || c < times) {
      cout << ptr->getData() << " ";
      ptr = ptr->getNext();

      if(ptr == &this->__first) c++;
    };
  };
};

int main() {
  // Note: run with C++14 (in tuan's computer)
  cout << "C++ version: " << __cplusplus <<endl;

  cout << endl;

  CircularLinkedList<int> lst = { 1, 2, 3 };

  cout << "Print 1 times: \n";
  lst.Print();
  cout << endl;

  cout << "Print 2 times: \n";
  lst.Print(2);
  cout << endl;

  cout << "Print 3 times: \n";
  lst.Print(3);
  cout << endl;

  return 0;
};
