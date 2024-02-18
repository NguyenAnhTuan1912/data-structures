/*
  @author Nguyen Anh Tuan
  Quetions 8:
  Create an int (number) linked list class has getAt method.
  Initialize a linked list and perform getAt method.

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

  // getAt
  Node* getAt(int n) {
    Node* ptr = this->__head;

    if(n < 0) n = 0;
    if(n >= this->__size) n = this->__size - 1;

    int c = 0;

    while(c < n) {
      ptr = ptr->next;
      c++;
    };

    return ptr;
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
  cout << n->data << " ";
};

int main() {
  // Initialize a list
  LinkedList lst = { 11, 12, 9, -7, 3, -91 };

  // Get Node at -1
  // Output: Node at [-1]: 11
  cout << "Node at [-1]: " << (lst.getAt(-1))->data << endl;

  // Get Node at 9999
  // Output: Node at [9999]: -91
  cout << "Node at [9999]: " << (lst.getAt(9999))->data << endl;

  // Get Node at 3
  // Output: Node at [3]: -7
  cout << "Node at [3]: " << (lst.getAt(3))->data << endl;

  // Get Node at 4
  // Output: Node at [4]: 3
  cout << "Node at [4]: " << (lst.getAt(4))->data << endl;

  // Get Node at 1
  // Output: Node at [1]: 12
  cout << "Node at [1]: " << (lst.getAt(1))->data << endl;

  return 0;
};
