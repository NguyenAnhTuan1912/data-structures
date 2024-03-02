/*
  @author Nguyen Anh Tuan
  Question:
  Create a generic stack implementation (STACK<T>) and an undo-redo stack (UndoRedoStack)..
  The STACK<T> class consists of methods for basic stack operations such as push, pop, add,
  delete, and swap. It utilizes a linked list data structure implemented through the NODE<T> class.
  The UndoRedoStack class utilizes the STACK<T> class to maintain a stack of stack states, enabling
  undo and redo functionalities. It supports operations like push, pop, add, delete, and swap on
  the stack, maintaining a history of states for undo and redo purposes.

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

  // getTop
  T getTop() {
    return this->__top->data;
  };

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

  void deleteAt(int index) {
    if(index <= 0) {
      this->pop();
      return;
    };
    if(index >= this->__size) index = this->__size - 1;

    int c = 0, arr[index], popped;

    while(c <= index) {
      popped = this->pop();
      if(c < index) arr[c] = popped;
      c++;
    }

    c = index - 1;
    while(c >= 0) {
      this->push(arr[c]);
      c--;
    }
  }

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

template<class T>
class HistoryStack {
private:
  Stack<T> __history_stack;

public:
  HistoryStack(int s = 10) {
    this->__history_stack = Stack<T>(s);
  };

  // redo
  void redo() {

  }

  // undo
  void undo() {

  }

  // getCurrent
  T getCurrent() {
    this->__history_stack->getTop();
  }
};

int main() {
  // Print Lambda
  ConstStackNodeCallBack<int> printValue = [](const shared_ptr<StackNode<int>>& sn) {
    cout << sn->data << " ";
  };

  return 0;
}
