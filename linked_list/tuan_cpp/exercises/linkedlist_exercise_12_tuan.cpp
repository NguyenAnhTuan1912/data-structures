/*
  @author Nguyen Anh Tuan
  Quetions 11:
  Create a generic doubly linked list class has the same methods as the generic
  singly linked list class in Question 11 and 2 two classes Point and Person.
  Use generic doubly linked list class to declare 2 doubly linked lists and do tasks like Question 11.

  Done.
*/
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

using namespace std;

class Point {
public:
  int x = 0;
  int y = 0;

  Point() = default;
  Point(int x, int y): x{x}, y{y} {};
  explicit Point(int n): x{n}, y{n} {};

  void print() {
    cout << "(" << x << "; " << y << ")\n";
  };
};

class Person {
public:
  string name = "";
  int age = 0;

  Person() = default;
  Person(string n, int a): name{n}, age{a} {};

  void print() {
    cout << name << ", " << age << "\n";
  };
};

template<class T>
class Node {
public:
  T data;
  Node* next = nullptr;
  Node* prev = nullptr;

  Node() = default;
  Node(T d): data{d} {};
  Node(T d, Node* p, Node* n): data{d}, prev{p}, next{n} {};
};

template<class T>
using CompareFn = function<bool(T&, T&)>;

template<class T>
using LListForEachCallBack = function<void(Node<T>*, int index)>;

template<class T>
class DoublyLinkedList {
private:
  Node<T>* __head = nullptr;
  Node<T>* __tail = nullptr;
  size_t __size = 1;

  void __forEachFromHead(LListForEachCallBack<T> cb = NULL) {
    if(this->__head == nullptr) return;

    Node<T>* ptr = this->__head;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->next;
      index++;
    };
  };

  void __forEachFromTail(LListForEachCallBack<T> cb = NULL) {
    if(this->__tail == nullptr) return;

    Node<T>* ptr = this->__tail;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->prev;
      index++;
    };
  };

public:
  DoublyLinkedList() = default;
  DoublyLinkedList(initializer_list<T> lst) {
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
    this->__tail->prev = this->__head;
    Node<T>* ptr = this->__head;

    itr++;

    while(itr != last_item_itr) {
      ptr->next = new Node<T>(*itr, ptr, this->__tail);
      this->__tail->prev = ptr->next;
      ptr = ptr->next;
      itr++;
    };
  };
  ~DoublyLinkedList() {
    this->clear();
  };

  Node<T>* getAt(int n) {
    if(this->__head == nullptr) return nullptr;
    Node<T>* ptr = this->__head;
    bool canStartFromHead = true;

    if(n < 0) n = 0;
    if(n >= this->__size) n = this->__size;

    if(n > (this->__size / 2)) {
      ptr = this->__tail;
      canStartFromHead = false;
      n = this->__size - n - 1;
    };

    int c = 0;

    while(c < n) {
      if(canStartFromHead) ptr = ptr->next;
      else ptr = ptr->prev;
      c++;
    };

    return ptr;
  };

  // insertFirst
  void insertFirst(T data) {
    if(this->__head == nullptr) {
      this->__head = new Node<T>(data);
      this->__tail = this->__head;

      this->__size++;

      return;
    };

    Node<T>* new_node = new Node<T>(data, nullptr, this->__head);

    this->__head->prev = new_node;
    this->__head = new_node;

    this->__size++;
  };

  // insertLast
  void insertLast(T data) {
    if(this->__head == nullptr) {
      this->__head = new Node<T>(data);
      this->__tail = this->__head;

      this->__size++;

      return;
    };

    Node<T>* new_node = new Node<T>(data, this->__tail, nullptr);

    this->__tail->next = new_node;
    this->__tail = new_node;

    this->__size++;
  };

  // insertAt
  void insertAt(T data, int n) {
    if(this->__head == nullptr) return;
    if(n <= 0) {
      this->insertFirst(data);
      return;
    };
    if(n >= this->__size) {
      this->insertLast(data);
      return;
    };

    Node<T>* ptr = this->getAt(n);
    Node<T>* new_node = new Node<T>(data, ptr->prev, ptr);

    ptr->prev->next = new_node;
    ptr->prev = new_node;

    this->__size++;
  };

  // insertOrderBy
  void insertOrderBy(T data, CompareFn<T> compare) {
    if(this->__head == nullptr) {
      this->insertFirst(data);
      return;
    };

    Node<T>* ptr = this->__head;

    while(ptr != nullptr) {
      if(compare(ptr->data, data)) break;

      ptr = ptr->next;
    };

    if(ptr == nullptr) {
      this->insertLast(data);
      return;
    } else if(ptr == this->__head) {
      this->insertFirst(data);
      return;
    };

    Node<T>* new_node = new Node<T>(data, ptr->prev, ptr);

    ptr->prev->next = new_node;
    ptr->prev = new_node;

    this->__size++;
  };

  // removeFirst
  void removeFirst() {
    if(this->__head == nullptr) return;

    Node<T>* ptr = this->__head;

    this->__head = this->__head->next;
    this->__head->prev = nullptr;

    delete ptr;

    this->__size--;
  };

  // removeLast
  void removeLast() {
    if(this->__tail == nullptr) return;

    Node<T>* ptr = this->__tail;

    this->__tail = this->__tail->prev;
    this->__tail->next = nullptr;

    delete ptr;

    this->__size--;
  };

  // removeAt
  void removeAt(int n) {
    if(this->__head == nullptr) return;
    if(n <= 0) {
      this->removeFirst();
      return;
    };
    if(n >= this->__size) {
      this->removeLast();
      return;
    };

    Node<T>* ptr = this->getAt(n);

    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;

    delete ptr;

    this->__size--;
  };

  void printFromHead(LListForEachCallBack<T> cb) {
    if(this->__head == nullptr) {
      cout << "Empty list!!!\n";
      return;
    };
    cout << "Size: " << this->__size << endl;
    this->__forEachFromHead(cb);
  };

  void printFromTail(LListForEachCallBack<T> cb) {
    if(this->__tail == nullptr) {
      cout << "Empty list!!!\n";
      return;
    };
    cout << "Size: " << this->__size << endl;
    this->__forEachFromTail(cb);
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
  // Create lambdas
  CompareFn<Point> insertPointIncreasingly = [](Point& curr, Point& data) { return curr.x >= data.x; };
  CompareFn<Person> insertPersonIncreasinglyByAge = [](Person& curr, Person& data) { return curr.age >= data.age; };

  LListForEachCallBack<Point> printPoint = [](Node<Point>* n, int index) {
    n->data.print();
  };
  LListForEachCallBack<Person> printPerson = [](Node<Person>* n, int index) {
    n->data.print();
  };

  // Declare
  DoublyLinkedList<Point> points;
  DoublyLinkedList<Person> people;

  // Add Nodes
  points.insertFirst({ 1, 2 });
  points.insertFirst({ -4, 3 });
  points.insertLast({ 10, -9 });
  points.insertLast({ 3, 4 });
  points.insertOrderBy({ -10, 3 }, insertPointIncreasingly);
  points.insertOrderBy({ 8, 11 }, insertPointIncreasingly);

  people.insertFirst({ "Carl", 40 });
  people.insertFirst({ "Sweet", 45 });
  people.insertLast({ "Woozie", 42 });
  people.insertLast({ "Katalina", 38 });
  people.insertOrderBy({ "Tuan", 21 }, insertPersonIncreasinglyByAge);
  people.insertOrderBy({ "A", 11 }, insertPersonIncreasinglyByAge);

  // Print list.
  cout << "Print points: \n";
  points.printFromHead(printPoint);
  cout << endl;
  cout << "Print people: \n";
  people.printFromHead(printPerson);
  cout << endl;

  // Get Nodes
  cout << "Get 4 points randomly: \n";
  cout << "Get point at 1: "; (points.getAt(1))->data.print();
  cout << "Get point at -10: "; (points.getAt(-10))->data.print();
  cout << "Get point at 4: "; (points.getAt(4))->data.print();
  cout << "Get point at 5: "; (points.getAt(5))->data.print();
  cout << endl;
  cout << "Get 4 people randomly: \n";
  cout << "Get person at -99: "; (people.getAt(-99))->data.print();
  cout << "Get person at 1: "; (people.getAt(1))->data.print();
  cout << "Get person at 0: "; (people.getAt(0))->data.print();
  cout << "Get person at 3: "; (people.getAt(3))->data.print();
  cout << endl;

  // Remove Nodes
  points.removeFirst();
  points.removeLast();
  points.removeAt(3);

  people.removeFirst();
  people.removeLast();
  people.removeAt(1);

  // Print list.
  cout << "Print points: \n";
  points.printFromHead(printPoint);
  cout << endl;
  cout << "Print people: \n";
  people.printFromHead(printPerson);
  cout << endl;

  return 0;
};
