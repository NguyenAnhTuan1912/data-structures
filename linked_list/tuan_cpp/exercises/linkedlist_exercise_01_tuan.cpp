/*
  @author Nguyen Anh Tuan
  Quetions 1:
  Create a linked list class whose Nodes have a data part is integer type and it has a print method.
  Initialize 5 linked list instances and print their element’s data to console.

  Done.
*/

#include <iostream>
#include <initializer_list>
#include <iterator>

using namespace std;

// Install Node
class Node {
private:
  int __data;
  Node* __next = nullptr;

public:
  Node() = default;
  Node(int data): __data{data} {};
  Node(int data, Node* next): __data{data}, __next{next} {};

  void setNext(Node* ptr_node) { this->__next = ptr_node; };
  void setData(int data) { this->__data = data; };
  Node* getNext() { return this->__next; };
  int getData() { return this->__data; };
};

// Install LinkedList
class LinkedList {
private:
  Node* __head;
  Node* __tail;

public:
  LinkedList() {
    this->__head = new Node();
    this->__tail = this->__head;
  };
  LinkedList(initializer_list<int> lst) {
    typename initializer_list<int>::iterator itr = lst.begin();
    typename initializer_list<int>::iterator last_item_itr = lst.end();
    last_item_itr--;

    // Setup
    this->__head = new Node(*itr);
    this->__tail = this->__head;

    if(last_item_itr == itr) return;

    this->__tail = new Node(*last_item_itr);
    this->__head->setNext(this->__tail);
    Node* ptr = this->__head;

    itr++;

    while(itr != last_item_itr) {
      Node* ptr_node = new Node(*itr, this->__tail);
      ptr->setNext(ptr_node);
      ptr = ptr->getNext();
      itr++;
    }
  };
  ~LinkedList() {
    this->clear();
  };

  void print() {
    Node* ptr = this->__head;

    if(ptr == nullptr) {
      cout << "Empty list!!!\n";
      return;
    };

    while(ptr != nullptr) {
      cout << ptr->getData() << " ";
      ptr = ptr->getNext();
    };
  };

  void clear() {
    Node* ptr = this->__head;

    while(ptr != nullptr) {
      this->__head = this->__head->getNext();
      delete ptr;
      ptr = this->__head;
    };
  };
};

int main() {
  // Note: run with C++14 (in tuan's computer)
  cout << "C++ version: " << __cplusplus <<endl;

  cout << endl;

  LinkedList lst_01 = { 100, 20, 22, -10, -2, 34, 45 };
  LinkedList lst_02 = { 1 };
  LinkedList lst_03 = { -1, -2 };
  LinkedList lst_04 = { 99, 199, 299 };
  LinkedList lst_05 = { 5, 10, 15, 20, 25 };

  cout << "Print lst_01: \n";
  lst_01.print();
  cout << endl;

  cout << "Print lst_02: \n";
  lst_02.print();
  cout << endl;

  cout << "Print lst_03: \n";
  lst_03.print();
  cout << endl;

  cout << "Print lst_04: \n";
  lst_04.print();
  cout << endl;

  cout << "Print lst_05: \n";
  lst_05.print();
  cout << endl;

  cout <<endl;

  cout << "Delete all data\n";
  lst_01.clear();
  lst_02.clear();
  lst_03.clear();
  lst_04.clear();
  lst_05.clear();
  cout << endl;

  cout << "Print lst_01: \n";
  lst_01.print();
  cout << endl;

  cout << "Print lst_02: \n";
  lst_02.print();
  cout << endl;

  cout << "Print lst_03: \n";
  lst_03.print();
  cout << endl;

  cout << "Print lst_04: \n";
  lst_04.print();
  cout << endl;

  cout << "Print lst_05: \n";
  lst_05.print();
  cout << endl;

  return 0;
};
