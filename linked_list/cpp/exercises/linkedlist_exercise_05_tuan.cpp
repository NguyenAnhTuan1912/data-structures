/*
  @author Nguyen Anh Tuan
  Quetions 5:
  Create a generic linked list class has print, insertLast, insertFirst methods.
  Initialize a number type linked list instance and add numbers of random Points
  to a declared Point type linked list instance that are generated from generic
  linked list class and print their element’s data to console.

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

template<class T>
class Node {
public:
  T data;
  Node* next = nullptr;

  Node() = default;
  Node(T d): data{d} {};
  Node(T d, Node* n): data{d}, next{n} {};
};

template<class T>
using LListForEachCallBack = function<void(Node<T>*, int index)>;

template<class T>
class LinkedList {
private:
  Node<T>* __head;
  Node<T>* __tail;
  size_t __size = 1;

  void __forEach(LListForEachCallBack<T> cb = NULL) {
    Node<T>* ptr = this->__head;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->next;
      index++;
    };
  };

public:
  LinkedList() {
    this->__head = new Node<T>();
    this->__tail = this->__head;
  };
  LinkedList(initializer_list<T> lst) {
    typename initializer_list<T>::iterator itr = lst.begin();
    typename initializer_list<T>::iterator last_item_itr = lst.end();
    last_item_itr--;

    // Setup
    this->__head = new Node<T>(*itr);
    this->__tail = this->__head;
    this->__size = lst.size();

    if(last_item_itr == itr) return;

    this->__tail = new Node<T>(*last_item_itr);
    this->__head->next = this->__tail;
    Node<T>* ptr = this->__head;

    itr++;

    while(itr != last_item_itr) {
      ptr->next = new Node<T>(*itr, this->__tail);
      ptr = ptr->next;
      itr++;
    };
  };
  ~LinkedList() {
    this->clear();
  };

  // insertFirst
  void insertFirst(T data) {
    Node<T>* new_node = new Node<T>(data, this->__head);

    this->__head = new_node;

    this->__size++;
  };

  // insertLast
  void insertLast(T data) {
    Node<T>* new_node = new Node<T>(data);

    this->__tail->next = new_node;
    this->__tail = new_node;

    this->__size++;
  };

  void print(LListForEachCallBack<T> Cb) {
    if(this->__head == nullptr) {
      cout << "Empty list!!!\n";
      return;
    };
    cout << "Numbers of nodes: " << this->__size << endl;
    this->__forEach(Cb);
  };

  void clear() {
    Node<T>* ptr = this->__head;

    while(ptr != nullptr) {
      this->__head = this->__head->next;
      delete ptr;
      ptr = this->__head;
    };

    this->__size = 0;
  };
};

int main() {
  // Create 2 lambdas
  LListForEachCallBack<Point>printPointNodeData = [](Node<Point>* n, int index) {
    n->data.print();
  };

  LListForEachCallBack<int> printNumberNodeData = [](Node<int>* n, int index) {
    cout << n->data << " ";
  };

  // Initialize 2 lists
  LinkedList<Point> point_lst;
  LinkedList<int> number_lst;

  point_lst.print(printPointNodeData);
  number_lst.print(printNumberNodeData);

  cout << endl;

  // Add items
  point_lst.insertFirst({ 1, 2 });
  point_lst.insertLast({ 4, 2 });
  point_lst.insertLast({ 1, -2 });
  point_lst.insertFirst({ -10, 4 });

  number_lst.insertLast(23);
  number_lst.insertLast(12);
  number_lst.insertFirst(-20);
  cout << "=====\n";

  // Re-print (1)
  cout << "Print point_lst (1): \n";
  point_lst.print(printPointNodeData);
  cout << endl;

  cout << "Print number_lst (1): \n";
  number_lst.print(printNumberNodeData);
  cout << endl;

  // Delete items
  point_lst.clear();
  cout << "=====\n";

  // Re-print (2)
  cout << "Print point_lst (2): \n";
  point_lst.print(printPointNodeData);
  cout << endl;

  cout << "Print number_lst (2): \n";
  number_lst.print(printNumberNodeData);
  cout << endl;

  return 0;
};
