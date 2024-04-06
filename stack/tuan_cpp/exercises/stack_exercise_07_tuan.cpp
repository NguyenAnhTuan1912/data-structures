/*
  @author Nguyen Anh Tuan
  Question:
  Similar to exercise 4,5. Create a generic Stack has SWAP feature that using a element at INDEX1 and INDEX2

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

  // Exercise 7: swap method
  void swap(int indexA, int indexB) {
    if(indexA == indexB) return;

    indexA = indexA <= 0 ? 0 : indexA >= this->__size ? this->__size - 1 : indexA;
    indexB = indexB <= 0 ? 0 : indexB >= this->__size ? this->__size - 1 : indexB;

    int c = 0;
    shared_ptr<StackNode<T>> ptr = this->__top, ptrA, ptrB;
    T data;

    while(c < this->__size) {
      if(c == indexA) {
        ptrA = ptr;
      }

      if(c == indexB) {
        ptrB = ptr;
      }

      ptr = ptr->bottom;
      c++;
    }

    // Swap
    data = move(ptrA->data);
    ptrA->data = move(ptrB->data);
    ptrB->data = move(data);
  }
};

int main() {
  // Print Lambda
  ConstStackNodeCallBack<int> printValue = [](const shared_ptr<StackNode<int>>& sn) {
    cout << sn->data << " ";
  };

  // Initialize a stack
  Stack<int> stk({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10);

  // Print
  cout << "Print stk: \n";
  // stk: 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
  stk.forEach(printValue);
  cout << endl;

  // Swap 3 and 7
  // stk: 10 9 8 3 6 5 4 7 2 1
  stk.swap(3, 7);
  // Swap 1 and 1000
  // stk: 10 1 8 3 6 5 4 7 2 9
  stk.swap(1, 1000);

  // Print
  cout << "Print stk: \n";
  stk.forEach(printValue);
  cout << endl;

  return 0;
}
