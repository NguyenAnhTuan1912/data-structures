/*
  @author Nguyen Anh Tuan
  Quetions 3:
  Create a linked list class whose Nodes have a data part is integer type and it has print,
  insertLast, insertFirst methods. Declare a linked list instance, then add numbers of random
  int numbers and print its element’s data to console.

  Done.
*/

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

using namespace std;

class Node {
public:
  int data;
  Node* next = nullptr;

  Node() = default;
  Node(int d): data{d} {};
  Node(int d, Node* n): data{d}, next{n} {};
};

using InitializerPointList = initializer_list<int>;
using LListForEachCallBack = function<void(Node*, int index)>;

class LinkedList {
private:
  Node* __head;
  Node* __tail;
  size_t __size = 1;

  static LListForEachCallBack __printNodeData;

  void __forEach(LListForEachCallBack cb = NULL) {
    Node* ptr = this->__head;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->next;
      index++;
    };
  };

public:
  LinkedList() {
    this->__head = new Node();
    this->__tail = this->__head;
  };
  LinkedList(InitializerPointList lst) {
    InitializerPointList::iterator itr = lst.begin();
    InitializerPointList::iterator last_item_itr = lst.end();
    last_item_itr--;

    // Setup
    this->__head = new Node(*itr);
    this->__tail = this->__head;
    this->__size = lst.size();

    if(last_item_itr == itr) return;

    this->__tail = new Node(*last_item_itr);
    this->__head->next = this->__tail;
    Node* ptr = this->__head;

    itr++;

    while(itr != last_item_itr) {
      ptr->next = new Node(*itr, this->__tail);
      ptr = ptr->next;
      itr++;
    };
  };
  ~LinkedList() {
    this->clear();
  };

  // insertFirst
  void insertFirst(int data) {
    Node* new_node = new Node(data, this->__head);

    this->__head = new_node;

    this->__size++;
  };

  // insertLast
  void insertLast(int data) {
    Node* new_node = new Node(data);

    this->__tail->next = new_node;
    this->__tail = new_node;

    this->__size++;
  };

  void print() {
    if(this->__head == nullptr) {
      cout << "Empty list!!!\n";
      return;
    };
    cout << "Numbers of nodes: " << this->__size << endl;
    this->__forEach(this->__printNodeData);
  };

  void clear() {
    Node* ptr = this->__head;

    while(ptr != nullptr) {
      this->__head = this->__head->next;
      delete ptr;
      ptr = this->__head;
    };

    this->__size = 0;
  };
};

LListForEachCallBack LinkedList::__printNodeData = [](Node* n, int index) {
  cout << "Node[" << index << "]->data: " << n->data << endl;
};

int main() {
  // Declare a list
  LinkedList lst;

  lst.print();
  // Add items
  lst.insertFirst(-100);
  lst.insertLast(100);
  lst.insertLast(99);
  lst.insertFirst(-3);
  cout << endl;

  // Re-print (1)
  cout << "Print lst (1): \n";
  lst.print();

  // Delete items
  lst.clear();
  cout << endl;

  // Re-print (2)
  cout << "Print lst (2): \n";
  lst.print();
  return 0;
};
