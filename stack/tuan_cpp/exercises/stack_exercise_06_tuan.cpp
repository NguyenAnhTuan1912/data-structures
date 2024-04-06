/*
  @author Nguyen Anh Tuan
  Question:
  Create a generic Stack has ADD feature that add a element at INDEX
  Example : [1=>2=>3] : stack.add(1, 99)
  1 - stack.pop()  [2=>3]
  2 - stack.push(99)  [99=>2=>3]
  3 - stack.push(1) [1=>99=>2=>3] value 99 now has been added at index 1st

  Done.
*/
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <exception>
#include <memory>
#include <functional>

using namespace std;

template<class T>
class StackNode {
public:
  T data;
  shared_ptr<StackNode> bottom = shared_ptr<StackNode>(nullptr);

  StackNode() = default;
  StackNode(T d): data{d} {};
  StackNode(T d, shared_ptr<StackNode> sn): data{d}, bottom{sn} {};
};

template<class T>
using ConstStackNodeCallBack = function<void(shared_ptr<StackNode<T>>&)>;

template<class T>
class Stack {
private:
  size_t __size = 0;
  size_t __max_size = 10;
  shared_ptr<StackNode<T>> __top = shared_ptr<StackNode<T>>(nullptr);

public:
  Stack(size_t max_size = 10): __max_size{max_size} {};
  Stack(initializer_list<T> lst, size_t max_size = 10) {
    typename initializer_list<T>::iterator itr = lst.begin();
    typename initializer_list<T>::iterator end_itr = lst.end();
    this->__max_size = max_size;

    while(itr != end_itr) {
      if(this->__size == this->__max_size) break;
      this->__top = shared_ptr<StackNode<T>>(new StackNode<T>(*itr, this->__top));
      this->__size++;
      itr++;
    }
  }

  // pop
  T pop() {
    try {
      if(this->__size == 0) throw runtime_error("Stack is empty!!!");
      shared_ptr<StackNode<T>> popped = shared_ptr<StackNode<T>>(this->__top);

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
  void push(T data) {
    try {
      if(this->__size == this->__max_size) throw runtime_error("Stack is full!!!");

      this->__top = shared_ptr<StackNode<T>>(new StackNode<T>(data, this->__top));
      this->__size++;
    } catch(const exception& e) {
      cout << "Push error: ";
      cerr << e.what();
    }
  }

  // forEach
  void forEach(ConstStackNodeCallBack<T> cb) {
    shared_ptr<StackNode<T>> ptr = this->__top;

    while(ptr != nullptr) {
      cb(ptr);
      ptr = ptr->bottom;
    }
  }

  // Exercise 6: insertAt method (ADD FEATURE)
  void insertAt(int index, int data) {
    if(index <= 0) {
      this->push(data);
      return;
    };
    if(index >= this->__size) index = this->__size;

    int c = 0, arr[index];

    while(c < index) {
      arr[c] = this->pop();
      c++;
    }

    // Add element
    this->push(data);

    c = index - 1;
    while(c >= 0) {
      this->push(arr[c]);
      c--;
    }
  }
};

int main() {
  // Print Lambda
  ConstStackNodeCallBack<int> printValue = [](const shared_ptr<StackNode<int>>& sn) {
    cout << sn->data << " ";
  };

  // Initialize a stack
  Stack<int> stk({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 20);

  // Print
  cout << "Print stk: \n";
  // stk: 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
  stk.forEach(printValue);
  cout << endl;

  // "Add" element at 3 with data = 9999
  // stk: 10, 9, 8, 9999, 6, 5, 3, 2, 1
  cout << "Add element at 3, data = 9999...\n";
  stk.insertAt(3, 9999);
  cout << "Add element at first, data = -100...\n";
  // "Add" element at first with data = -100
  // stk: -100 10, 9, 8, 9999, 6, 5, 3, 2, 1
  stk.insertAt(-23, -100);
  cout << "Add element at last, data = 47...\n";
  // "Add" element at last with data = 47
  // stk: -100 10, 9, 8, 9999, 6, 5, 3, 2, 1, 47
  stk.insertAt(10000, 47);
  cout << endl;

  // Print
  cout << "Print stk: \n";
  // stk: -100 10, 9, 8, 9999, 6, 5, 3, 2, 1, 47
  stk.forEach(printValue);
  cout << endl;

  return 0;
}
