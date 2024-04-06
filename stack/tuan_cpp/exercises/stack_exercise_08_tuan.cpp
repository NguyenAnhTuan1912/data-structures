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
#include <stdlib.h>
#include <conio.h>
#include <cmath>

#define KEY_ESC 27
#define KEY_u 117
#define KEY_r 114
#define KEY_i 105
#define KEY_e 101

using namespace std;

enum StringAction {
  Append,
  Erase,
  EMPTY
};

// State change of string
class StringChange {
public:
  int atIndex = 0;
  int amount = 0;
  string data = "";
  StringAction action = EMPTY;
};

class StringState {
public:
  string* curr = nullptr;
  string prev = "";
};

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

  size_t getSize() {
    return this->__size;
  }

  void clear() {
    this->__top = shared_ptr<StackNode<T>>(nullptr);
    this->__size = 0;
  }
};

class StringHistoryStack {
private:
  Stack<StringChange> __undo_stack;
  Stack<StringChange> __redo_stack;
  StringState __target;

public:
  StringHistoryStack(string* t, int s = 10) {
    this->__undo_stack = Stack<StringChange>(s);
    this->__redo_stack = Stack<StringChange>(s);
    this->__target.curr = t;
  };

  // redo
  void redo() {
    // Get state
    StringChange change = this->__redo_stack.pop();
    // Do action here
    if(change.action == Erase) {
      *(this->__target.curr) = this->__target.curr->erase(change.atIndex, this->__target.curr->size());
    }

    if(change.action == Append) {
      this->__target.curr->insert(change.atIndex, change.data);
    }

    // Push to undo
    this->__undo_stack.push(change);
  }

  // undo
  void undo() {
    // Get state
    StringChange change = this->__undo_stack.pop();

    // Save current state
    this->__target.prev = *(this->__target.curr);

    // Do action here
    // Reverse action
    if(change.action == Append) {
      *(this->__target.curr) = this->__target.curr->erase(change.atIndex, this->__target.curr->size());
    }

    if(change.action == Erase) {
      this->__target.curr->insert(change.atIndex, change.data);
    }

    // Push to redo
    this->__redo_stack.push(change);
  }

  // startObserve
  /**
   * Use this method to start tracing the change of state of target, then
   * generate the state of change for undo, redo action.
   */
  void startObserve() {
    this->__target.prev = *(this->__target.curr);
  }

  // endObserve
  /**
   * Use this method to end tracing the change of state of target, then
   * calculate change of targe.
   */
  void endObserve(int atIndex, string changeData) {
    int
      N = this->__target.prev.size(),
      M = this->__target.curr->size(),
      amount = abs(M - N);

    // Nothing change
    if(N == M) return;

    StringChange change;
    change.amount = amount;

    // String is substracted
    if(N > M) {
      change.action = Erase;
      change.data = changeData;
      change.atIndex = atIndex;
    }

    // String is appended
    if(N < M) {
      change.action = Append;
      change.data = changeData;
      change.atIndex = atIndex;
    }

    this->__undo_stack.push(change);
    // Clear redo stack
    this->__redo_stack.clear();
  }

  bool canUndo() {
    return (this->__undo_stack.getSize() > 0);
  }

  bool canRedo() {
    return (this->__redo_stack.getSize() > 0);
  }
};

int main() {
  // Print Lambda
  ConstStackNodeCallBack<int> printValue = [](const shared_ptr<StackNode<int>>& sn) {
    cout << sn->data << " ";
  };

  // Apply for string
  string* data = new string("");
  string input = "";
  int key = 0;

  // Initialize StringHistoryStack
  StringHistoryStack stringHistoryStack(data, 20);

  while(true) {
    system("cls");

    // Choose options
    cout << "Options:\n";
    cout << "i - input string\n";
    if(data->size() > 0) cout << "e - erase string\n";
    if(stringHistoryStack.canUndo()) cout << "u - undo\n";
    if(stringHistoryStack.canRedo()) cout << "r - redo\n";
    cout << "=====\n";
    cout << "esc - exit\n";
    cout << "Press any (except above keys) key to continue\n";

    key = getch();
    // Check option
    if(key == KEY_ESC) break;

    system("cls");

    switch(key) {
      case KEY_i: {
        // Start observe
        stringHistoryStack.startObserve();
        int N = data->size();

        cout << "Nhap chuoi: \n";
        cout << *(data);
        getline(cin, input);
        data->append(input);

        system("cls");

        // End observe
        stringHistoryStack.endObserve(N, input);

        break;
      };

      case KEY_e: {
        // Start observe
        stringHistoryStack.startObserve();
        int s = 0, l = 0, N = data->size();
        string erased = "";

        cout << "Xoa chuoi: \n";
        cout << *(data) << endl;
        cout << "Bat dau - So ki tu muon xoa: "; cin >> s; cin >> l;

        if(s < 0) s = 0;
        if(s >= N) s = N - 2;
        if(l < s) l = s + 1;
        if(l >= N) l = N - 1;

        erased = data->substr(s, l);
        *data = data->erase(s, l);

        // system("cls");

        // End observe
        stringHistoryStack.endObserve(s, erased);
        break;
      };

      case KEY_u: {
        stringHistoryStack.undo();
        break;
      };

      case KEY_r: {
        stringHistoryStack.redo();
        break;
      };
      default: break;
    };

    cout << "Text: \n";
    cout << *data;
    cout << "\n\n=====\n";
    cout << "Press any (except above keys) key to continue\n";

    // Check option
    key = getch();
  };

  return 0;
}
