/*
  @author Nguyen Anh Tuan
  Quetions 9:
  Create an int (number) linked list class has insertByOrder method.
  Declare a linked list and add numbers of random numbers with insertByOrder.

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

  // insertOrderBy
  void insertOrderBy(int data, bool isIncrease = true) {
    if(this->__head == nullptr) {
      // Perform insert here
      return;
    };

    Node* ptr = this->__head;
    Node* before = nullptr;

    while(ptr != nullptr) {
      if(isIncrease && ptr->data > data) break;
      if(!isIncrease && ptr->data <= data) break;

      before = ptr;
      ptr = ptr->next;
    };

    Node* new_node = new Node(data, ptr);
    if(before != nullptr) before->next = new_node;

    if(ptr == nullptr) this->__tail = new_node;
    else if(ptr == this->__head) this->__head = new_node;
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
  // Declare a list
  LinkedList lst;

  // Add items
  lst.insertOrderBy(-5);
  lst.insertOrderBy(1);
  lst.insertOrderBy(10);
  lst.insertOrderBy(-10);
  lst.insertOrderBy(5);
  lst.insertOrderBy(100);
  lst.insertOrderBy(25);
  lst.insertOrderBy(30);
  lst.insertOrderBy(-1);
  lst.insertOrderBy(10);

  // Print
  cout << "Print lst: \n";
  lst.print();
  cout << endl;
  return 0;
};
