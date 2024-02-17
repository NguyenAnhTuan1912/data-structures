
/*
  @author Nguyen Anh Tuan
  Quetions 6:
  Create an int (number) linked list class has print, insertLast,
  insertFirst, insertAt. Initialize a linked list instance to perform all of its methods.

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
  size_t __size = 0;

  static LListForEachCallBack __printNodeData;

  void __forEach(LListForEachCallBack Cb = NULL) {
    Node* ptr = this->__head;
    int index = 0;

    while(ptr != nullptr) {
      if(Cb != NULL) Cb(ptr, index);
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

  // insertAt
  void insertAt(int data, int n) {
    Node* new_node = new Node(data);
    Node* ptr = this->__head;
    Node* before = nullptr;

    if(n < 0) n = 0;
    if(n >= this->__size) n = this->__size - 1;

    int c = 0;

    while(c < n) {
      before = ptr;
      ptr = ptr->next;
      c++;
    };

    // At Tail
    if(ptr == this->__tail) {
      this->__tail->next = new_node;
      this->__tail = new_node;
    }
    // At Head
    else if(ptr == this->__head) {
      new_node->next = this->__head;
      this->__head = new_node;
    }
    // At between Tail and Head
    else if(ptr != this->__head && ptr != this->__tail) {
      before->next = new_node;
      new_node->next = ptr;
    };

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
  cout << n->data << " ";
};

int main() {
  // Initialize a list
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
  // Output: -3 -100 0 100 99
  lst.print();
  cout << endl;

  // Add items
  // -3 -100 0 5 100 99
  lst.insertAt(5, 3);
  // -3 -100 0 5 100 99 47
  lst.insertAt(47, 100);
  // 1280 -3 -100 0 5 100 99 47
  lst.insertAt(1280, -1000);
  cout << endl;

  // Re-print (2)
  cout << "Print lst (2): \n";
  lst.print();
  cout << endl;

  // Remove all
  lst.clear();

  // Add items
  lst.insertAt(5, 0);
  lst.insertFirst(10);
  lst.insertAt(-55, 1);
  cout << endl;

  // Re-print (3)
  cout << "Print lst (3): \n";
  lst.print();
  cout << endl;

  return 0;
};
