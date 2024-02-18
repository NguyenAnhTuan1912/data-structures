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
  Node* prev = nullptr;

  Node() = default;
  Node(int d): data{d} {};
  Node(int d, Node* p, Node* n): data{d}, prev{p}, next{n} {};
};

using InitializerPointList = initializer_list<int>;
using LListForEachCallBack = function<void(Node*, int index)>;

class DoublyLinkedList {
private:
  Node* __head = nullptr;
  Node* __tail = nullptr;
  size_t __size = 1;

  static LListForEachCallBack __printNodeData;

  void __forEachFromHead(LListForEachCallBack cb = NULL) {
    Node* ptr = this->__head;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->next;
      index++;
    };
  };

  void __forEachFromTail(LListForEachCallBack cb = NULL) {
    Node* ptr = this->__tail;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->prev;
      index++;
    };
  };

public:
  DoublyLinkedList() = default;
  DoublyLinkedList(InitializerPointList lst) {
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
    this->__tail->prev = this->__head;
    Node* ptr = this->__head;

    itr++;

    while(itr != last_item_itr) {
      ptr->next = new Node(*itr, ptr, this->__tail);
      this->__tail->prev = ptr->next;
      ptr = ptr->next;
      itr++;
    };
  };
  ~DoublyLinkedList() {
    this->clear();
  };

  Node* getAt(int n) {
    if(this->__head == nullptr) return nullptr;
    Node* ptr = this->__head;
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
  void insertFirst(int data) {
    if(this->__head == nullptr) {
      this->__head = new Node(data);
      this->__tail = this->__head;

      this->__size++;
      return;
    };

    Node* new_node = new Node(data, nullptr, this->__head);

    this->__head->prev = new_node;
    this->__head = new_node;

    this->__size++;
  };

  // insertLast
  void insertLast(int data) {
    if(this->__tail == nullptr) {
      this->__tail = new Node(data);
      this->__head = this->__tail;

      this->__size++;
      return;
    };

    Node* new_node = new Node(data, this->__tail, nullptr);

    this->__tail->next = new_node;
    this->__tail = new_node;

    this->__size++;
  };

  // insertAt
  void insertAt(int data, int n) {
    if(this->__head == nullptr) return;
    if(n <= 0) {
      this->insertFirst(data);
      return;
    };
    if(n >= this->__size) {
      this->insertLast(data);
      return;
    };

    Node* ptr = this->getAt(n);
    Node* new_node = new Node(data, ptr->prev, ptr);

    ptr->prev->next = new_node;
    ptr->prev = new_node;

    this->__size++;
  };

  // insertOrderBy
  void insertOrderBy(int data, bool isIncrease = true) {
    if(this->__head == nullptr) {
      this->insertFirst(data);
      return;
    };

    Node* ptr = this->__head;

    while(ptr != nullptr) {
      if(isIncrease && ptr->data > data) break;
      if(!isIncrease && ptr->data <= data) break;

      ptr = ptr->next;
    };

    if(ptr == nullptr) {
      this->insertLast(data);
      return;
    } else if(ptr == this->__head) {
      this->insertFirst(data);
      return;
    };

    Node* new_node = new Node(data, ptr->prev, ptr);

    ptr->prev->next = new_node;
    ptr->prev = new_node;

    this->__size++;
  };

  // removeFirst
  void removeFirst() {
    if(this->__head == nullptr) return;

    Node* ptr = this->__head;

    this->__head = this->__head->next;
    this->__head->prev = nullptr;

    delete ptr;

    this->__size--;
  };

  // removeLast
  void removeLast() {
    if(this->__tail == nullptr) return;

    Node* ptr = this->__tail;

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

    Node* ptr = this->getAt(n);

    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;

    delete ptr;

    this->__size--;
  };

  void printFromHead() {
    if(this->__head == nullptr) {
      cout << "Empty list!!!\n";
      return;
    };
    cout << "Numbers of nodes: " << this->__size << endl;
    this->__forEachFromHead(this->__printNodeData);
  };

  void printFromTail() {
    if(this->__tail == nullptr) {
      cout << "Empty list!!!\n";
      return;
    };
    cout << "Numbers of nodes: " << this->__size << endl;
    this->__forEachFromTail(this->__printNodeData);
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

LListForEachCallBack DoublyLinkedList::__printNodeData = [](Node* n, int index) {
  cout << n->data << " ";
};

int main() {
  // Declare
  DoublyLinkedList lst;

  // Add Nodes
  // -1 0
  lst.insertFirst(-1);
  // -1 0 5
  lst.insertLast(5);


  // -1 0 5 100
  lst.insertAt(100, 3);
  // -1 -5 0 5 100
  lst.insertAt(-5, 1);
  // 99 -1 -5 0 5 100
  lst.insertAt(99, -100);

  // Get Nodes
  cout << "Get Nodes at random indexes: \n";
  // 0
  cout << "Get at [3]: " << lst.getAt(3)->data << endl;
  // 99
  cout << "Get at [0]: " << lst.getAt(0)->data << endl;
  // -1
  cout << "Get at [1]: " << lst.getAt(1)->data << endl;
  // -5
  cout << "Get at [2]: " << lst.getAt(2)->data << endl;
  cout << endl;

  // Print from head
  lst.printFromHead();
  cout << endl;

  // Print from tail
  lst.printFromTail();
  cout << endl;

  // Remove all
  lst.clear();

  // Add Nodes
  lst.insertOrderBy(4);
  lst.insertOrderBy(-1);
  lst.insertOrderBy(99);
  lst.insertOrderBy(-199);
  lst.insertOrderBy(300);
  lst.insertOrderBy(5);
  lst.insertOrderBy(2);
  lst.insertOrderBy(12);
  lst.insertOrderBy(19);
  lst.insertOrderBy(-20);
  lst.insertOrderBy(-11);
  lst.insertOrderBy(47);

  // Print from head
  // -199 -20 -11 -1 2 4 5 12 19 47 99 300
  lst.printFromHead();
  cout << endl;

  // Print from tail
  // 300 99 47 19 12 5 4 2 -1 -11 -20 -199
  lst.printFromTail();
  cout << endl;

  // Remove first and last
  // -20 -11 -1 2 4 5 12 19 47 99 300
  // Correspond with removeFirst()
  lst.removeAt(-100);
  // -20 -11 -1 2 4 5 12 19 47 99
  // Correspond with removeLast()
  lst.removeAt(9999);
  // -20 -11 -1 2 5 12 19 47 99
  // Remove 4
  lst.removeAt(4);
  // Remove 47
  lst.removeAt(7);

  // Print from head
  lst.printFromHead();
  cout << endl;

  // Print from tail
  lst.printFromTail();
  cout << endl;

  return 0;
};
