/*
  @author Nguyen Anh Tuan
  Quetions 7:
  Create an int (number) linked list class has required methods, removeLast,
  removeFirst and removeAt. Declare a linked list instance and add numbers of
  random numbers and perform all of its methods.

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

  // removeFirst
  void removeFirst() {
    if(this->__head == nullptr) return;

    Node* ptr = this->__head;
    this->__head = this->__head->next;
    ptr->next = nullptr;

    delete ptr;

    this->__size--;
  };

  // removeLast
  void removeLast() {
    if(this->__head == nullptr) return;

    Node* ptr = this->__head;
    Node* before = nullptr;

    while(ptr != this->__tail) {
      before = ptr;
      ptr = ptr->next;
    };

    this->__tail = before;
    this->__tail->next = nullptr;

    delete ptr;

    this->__size--;
  };

  // removeAt
  void removeAt(int n) {
    if(this->__head == nullptr) return;

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
      this->__tail = before;
      this->__tail->next = nullptr;
    }
    // At Head
    else if(ptr == this->__head) {
      this->__head = this->__head->next;
      ptr->next = nullptr;
    }
    // At between Tail and Head
    else if(ptr != this->__head && ptr != this->__tail) {
      before->next = ptr->next;
      ptr->next = nullptr;
    };

    delete ptr;
    this->__size--;
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
  lst.insertFirst(-100);
  lst.insertLast(100);
  lst.insertLast(99);
  lst.insertFirst(-3);

  // Output: -3 -100 0 100 99
  lst.print();
  cout << endl;

  // Remove first and last
  cout << "Remove first and last respectively: \n";
  // -100 0 100 99
  lst.removeFirst();
  // -100 0 100
  lst.removeLast();
  cout << "Done!\n\n";

  // Re-print (1)
  cout << "Print lst (1): \n";
  // Output: -100 0 100
  lst.print();
  cout << endl;

  // Add items
  // -100 0 100 5
  lst.insertAt(5, 3);
  // -100 0 100 5 47
  lst.insertAt(47, 100);
  // 1280 -100 0 100 5 47
  lst.insertAt(1280, -1000);
  cout << endl;

  // Re-print (2)
  cout << "Print lst (2): \n";
  // Output: 1280 -100 0 100 5 47
  lst.print();
  cout << endl;

  // Remove at
  // 1280 -100 0 5 47
  lst.removeAt(3);
  // -100 0 5 47
  lst.removeAt(-10);
  // -100 0 5
  lst.removeAt(300);
  cout << endl;

  // Re-print (3)
  // Output: -100 0 5
  cout << "Print lst (3): \n";
  lst.print();
  cout << endl;

  return 0;
};
