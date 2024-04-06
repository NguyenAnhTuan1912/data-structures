/*
  @author Nguyen Anh Tuan
  Quetions 2:
  Create a linked list class whose Nodes have a data part is Point
  (Point is a class that has 2 private properties indicating for coordinate)
  and it has a print method. Initialize a linked list instance and print its element’s data to console.

  Done.
*/

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

using namespace std;

class Point {
public:
  int x;
  int y;

  Point() = default;
  Point(int x, int y): x{x}, y{y} {};
  explicit Point(int n): x{n}, y{n} {};

  void print() {
    cout << "(" << x << "; " << y << ")\n";
  };
};

class Node {
public:
  Point data;
  Node* next = nullptr;

  Node() = default;
  Node(Point p): data{p} {};
  Node(Point p, Node* n): data{p}, next{n} {};
};

using InitializerPointList = initializer_list<Point>;
using LListForEachCallBack = function<void(Node*)>;

class LinkedList {
private:
  Node* __head;
  Node* __tail;

  static LListForEachCallBack __printNodeData;

  void __forEach(LListForEachCallBack Cb = NULL) {
    Node* ptr = this->__head;

    while(ptr != nullptr) {
      if(Cb != NULL) Cb(ptr);
      ptr = ptr->next;
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

  void print() {
    if(this->__head == nullptr) {
      cout << "Empty list!!!\n";
      return;
    };
    this->__forEach(this->__printNodeData);
  };

  void clear() {
    Node* ptr = this->__head;

    while(ptr != nullptr) {
      this->__head = this->__head->next;
      delete ptr;
      ptr = this->__head;
    };
  };
};

LListForEachCallBack LinkedList::__printNodeData = [](Node* n) {
  n->data.print();
};

int main() {
  // Initialize a list
  LinkedList lst = { {1 , 2}, {3, 4}, {-10, 5}, {5, 10} };

  cout << "Print list: \n";
  lst.print();
  cout << endl;

  cout << "Delete list and re-print: \n";
  lst.clear();
  lst.print();
  cout << endl;

  return 0;
};
