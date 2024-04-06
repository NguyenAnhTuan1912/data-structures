/*
  @author Nguyen Anh Tuan
  Question:
  Create a Stack has method print (Stack has HeadNode, Size and MaxSize and Constructor
  that auto push() element when initializing stack and Print method). Nodes have data
  (Integer Type) and NextNode. Initialize 1 stack has 5 elements and print that 5 elements.

  Done.
*/
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <exception>
#include <memory>
#include <functional>

using namespace std;

class StackNode {
public:
  int data = 0;
  shared_ptr<StackNode> bottom = shared_ptr<StackNode>(nullptr);

  StackNode() = default;
  StackNode(int d): data{d} {};
  StackNode(int d, shared_ptr<StackNode> sn): data{d}, bottom{sn} {};
};

using ConstStackNodeCallBack = function<void(shared_ptr<StackNode>&)>;

class Stack {
private:
  size_t __size = 0;
  size_t __max_size = 10;
  shared_ptr<StackNode> __top = shared_ptr<StackNode>(nullptr);

public:
  Stack(size_t max_size = 10): __max_size{max_size} {};
  Stack(initializer_list<int> lst, size_t max_size = 10) {
    typename initializer_list<int>::iterator itr = lst.begin();
    typename initializer_list<int>::iterator end_itr = lst.end();
    this->__max_size = max_size;

    while(itr != end_itr) {
      if(this->__size == this->__max_size) break;
      this->__top = shared_ptr<StackNode>(new StackNode(*itr, this->__top));
      this->__size++;
      itr++;
    }
  }

  // pop
  int pop() {
    try {
      if(this->__size == 0) throw runtime_error("Stack is empty!!!");
      shared_ptr<StackNode> popped = shared_ptr<StackNode>(this->__top);

      this->__top = this->__top->bottom;
      this->__size--;

      return popped->data;
    } catch(const exception& e) {
      cout << "Pop error: ";
      cerr << e.what();
      return 0;
    }
  }
  // push
  void push(int data) {
    try {
      if(this->__size == this->__max_size) throw runtime_error("Stack is full!!!");

      this->__top = shared_ptr<StackNode>(new StackNode(data, this->__top));
      this->__size++;
    } catch(const exception& e) {
      cout << "Push error: ";
      cerr << e.what();
    }
  }

  // forEach
  void forEach(ConstStackNodeCallBack cb) {
    shared_ptr<StackNode> ptr = this->__top;

    while(ptr != nullptr) {
      cb(ptr);
      ptr = ptr->bottom;
    }
  }
};

int main() {
  // Print Lambda
  ConstStackNodeCallBack printValue = [](const shared_ptr<StackNode>& sn) {
    cout << sn->data << " ";
  };

  // Initialize a stack
  Stack stk({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 8);

  // Print
  cout << "Print stk: \n";
  stk.forEach(printValue);
  cout << endl;

  // Push
  cout << "Push some data to stk...\n";
  stk.push(999);
  cout << endl << endl;

  // Pop
  cout << "Error when try to push some data, so pop something first...\n";
  cout << "Popped data: " << stk.pop() << endl;
  cout << "Popped data: " << stk.pop() << endl;
  cout << "Popped data: " << stk.pop() << endl;
  cout << "Popped data: " << stk.pop() << endl;
  cout << endl;

  // Print
  cout << "Print remain of stk: \n";
  stk.forEach(printValue);
  cout << endl << endl;

  // Push again
  cout << "Push some data to stk...\n";
  stk.push(-99);
  stk.push(101);
  stk.push(23);
  stk.push(3);
  cout << endl;

  // Print
  cout << "Print stk: \n";
  stk.forEach(printValue);
  cout << endl;

  return 0;
}
