/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Stack

  Ấn build để nó hiện ra từng message của lỗi.
  Để thực thi và xem các ví dụ thì comment những chỗ code lỗi lại.
*/

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>
#include <exception>

using namespace std;

class StackNode {
public:
  int data;
  StackNode* bottom = nullptr;

  StackNode() = default;
  StackNode(int d): data{d} {};
  StackNode(int d, StackNode* sn): data{d}, bottom{sn} {};
};

using StackForEachCallBack = function<void(const StackNode* sn)>;

class Stack {
private:
  StackNode* __top = nullptr;
  size_t __size = 0;
  size_t __max = 100;

  void __forEach(StackForEachCallBack cb) {
    StackNode* ptr = this->__top;
    while(ptr != nullptr) {
      cb(ptr);
      ptr = ptr->bottom;
    };
  };

public:
  Stack(size_t max_size = 100): __max{max_size} {};
  Stack(initializer_list<int> lst, size_t max_size = 100) {
    typename initializer_list<int>::iterator itr = lst.begin();
    typename initializer_list<int>::iterator itr_end = lst.end();
    this->__max = max_size;

    while(itr != itr_end) {
      if(this->__size >= this->__max) break;
      StackNode* new_node = new StackNode(*itr, this->__top);
      this->__top = new_node;

      this->__size++;
      itr++;
    };
  };
  ~Stack() {
    this->clear();
  };

  // pop
  void pop() {
    if(this->__top == nullptr) return;

    StackNode* ptr = this->__top;
    this->__top = this->__top->bottom;

    delete ptr;

    this->__size--;
  };

  // push
  void push(int data) {
    if(this->__size >= this->__max) throw runtime_error("Maximum size of stack is reached.");

    StackNode* new_node = new StackNode(data, this->__top);
    this->__top = new_node;

    this->__size++;
  };

  // getSize
  size_t getSize() { return this->__size; };

  // print
  void print(StackForEachCallBack cb) {
    this->__forEach(cb);
  };

  // clear
  void clear() {
    while(this->__top != nullptr) this->pop();
  };
};

void performInfiniteWhileLoop(Stack& s) {
  int i = 1;

  // Infinite While Loop
  while(true) {
    s.push(0);
    cout << "Print [" << i << "] times.\n";
    i++;
  };
  s.clear();
};

void performInfiniteForLoop(Stack& s) {
  // Infinite For Loop
  for(int i = 1;; i++) {
    s.push(0);
    cout << "Print [" << i << "] times.\n";
  };
  s.clear();
};

void performRecursively(Stack& s, int i = 1) {
  s.push(0);
  cout << "Print [" << i << "] times.\n";
  performRecursively(s, ++i);
};

void performWhileLoopWithLimitTime(Stack& s) {
  int i = 1;

  // Infinite While Loop
  while(i < 1000) {
    s.push(0);
    cout << "Print [" << i << "] times.\n";
    i++;
  };
  s.clear();
};

void performForLoopWithLimitTime(Stack& s) {
  // Infinite For Loop
  for(int i = 1; i < 1000; i++) {
    s.push(0);
    cout << "Print [" << i << "] times.\n";
  };
  s.clear();
};

int main() {
  Stack loop_controller;
  try {

    // Perform loop
    // Use only one loop at the time!!!
    // performInfiniteWhileLoop(loop_controller);
    // performInfiniteForLoop(loop_controller);
    performRecursively(loop_controller);
    // performWhileLoopWithLimitTime(loop_controller);
    // performForLoopWithLimitTime(loop_controller);

    return 0;
  } catch(const exception& e) {
    cout << "Stack's size: " << loop_controller.getSize() << endl;
    cout << endl << endl;
    cerr << e.what();
    cout << endl;
    return 1;
  };
};
