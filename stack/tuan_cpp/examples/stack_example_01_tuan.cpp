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

template<class T>
class StackNode {
public:
  T data;
  StackNode* bottom = nullptr;

  StackNode() = default;
  StackNode(T d): data{d} {};
  StackNode(T d, StackNode* sn): data{d}, bottom{sn} {};
};

template<class T>
using StackForEachCallBack = function<void(const StackNode<T>* sn)>;

template<class T>
class Stack {
private:
  StackNode<T>* __top = nullptr;
  size_t __size = 0;
  size_t __max = 100;

  void __forEach(StackForEachCallBack<T> cb) {
    StackNode<T>* ptr = this->__top;
    while(ptr != nullptr) {
      cb(ptr);
      ptr = ptr->bottom;
    };
  };

public:
  Stack(size_t max_size = 100): __max{max_size} {};
  Stack(initializer_list<T> lst, size_t max_size = 100) {
    typename initializer_list<T>::iterator itr = lst.begin();
    typename initializer_list<T>::iterator itr_end = lst.end();
    this->__max = max_size;

    while(itr != itr_end) {
      if(this->__size >= this->__max) break;
      StackNode<T>* new_node = new StackNode<T>(*itr, this->__top);
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

    StackNode<T>* ptr = this->__top;
    this->__top = this->__top->bottom;

    delete ptr;

    this->__size--;
  };

  // push
  void push(T data) {
    if(this->__size >= this->__max) throw runtime_error("Maximum size of stack is reached.");

    StackNode<T>* new_node = new StackNode<T>(data, this->__top);
    this->__top = new_node;

    this->__size++;
  };

  // getSize
  size_t getSize() { return this->__size; };

  // print
  void print(StackForEachCallBack<T> cb) {
    this->__forEach(cb);
  };

  // clear
  void clear() {
    while(this->__top != nullptr) this->pop();
  };
};

int main() {
  try {
    // print
    StackForEachCallBack<int> printInt = [](const StackNode<int>* sn) {
      cout << sn->data << " ";
    };

    Stack<int> s({ 10, 30, -1, 45, 100 }, 8);

    cout << "Print s: \n"; s.print(printInt);
    cout << endl << endl;

    // pop
    s.pop();

    cout << "Size of s after pop: " << s.getSize() << endl;
    cout << "Print s: \n"; s.print(printInt);

    cout << endl << endl;

    // clear
    cout << "Clear all\n";
    s.clear();
    cout << "Size of s after clear: " << s.getSize() << endl << endl;

    // push
    s.push(23);

    cout << "Size of s after push: " << s.getSize() << endl;
    cout << "Print s: \n"; s.print(printInt);
    cout << endl << endl;

    // error
    s.push(40);
    cout << "Print s: \n"; s.print(printInt);
    cout << endl;

    return 0;
  } catch(const exception& e) {
    cout << endl << endl;
    cerr << e.what();
    cout << endl;
    return 1;
  };
};
