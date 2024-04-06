/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Queue

  Ấn build để nó hiện ra từng message của lỗi.
  Để thực thi và xem các ví dụ thì comment những chỗ code lỗi lại.
*/

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

using namespace std;

template<class T>
class QueueNode {
public:
  T data;
  QueueNode* next = nullptr;

  QueueNode() = default;
  QueueNode(T d): data{d} {};
  QueueNode(T d, QueueNode* sn): data{d}, next{sn} {};
};

template<class T>
using QueueForEachCallBack = function<void(const QueueNode<T>* sn)>;

template<class T>
class Queue {
private:
  QueueNode<T>* __head = nullptr;
  QueueNode<T>* __tail = nullptr;
  size_t __size = 0;

  void __forEach(QueueForEachCallBack<T> cb) {
    QueueNode<T>* ptr = this->__head;
    while(ptr != nullptr) {
      cb(ptr);
      ptr = ptr->next;
    };
  };

public:
  Queue() = default;
  Queue(initializer_list<T> lst) {
    typename initializer_list<T>::iterator itr = lst.begin();
    typename initializer_list<T>::iterator last_item_itr = lst.end();
    this->__size = lst.size();
    last_item_itr--;

    this->__head = new QueueNode<T>(*itr);
    this->__tail = this->__head;

    if(itr == last_item_itr) return;

    QueueNode<T>* ptr = this->__head;
    this->__tail = new QueueNode<T>(*last_item_itr);
    this->__head->next = this->__tail;

    itr++;

    while(itr != last_item_itr) {
      QueueNode<T>* new_node = new QueueNode<T>(*itr, this->__tail);
      ptr->next = new_node;
      ptr = new_node;
      itr++;
    };
  };
  ~Queue() {
    this->clear();
  };

  // dequeue
  void dequeue() {
    if(this->__head == nullptr) return;

    QueueNode<T>* ptr = this->__head;
    this->__head = this->__head->next;

    delete ptr;

    this->__size--;
  };

  // enqueue
  void enqueue(T data) {
    if(this->__head == nullptr) {
      this->__head = new QueueNode<T>(data);
      this->__tail = this->__head;
    } else {
      QueueNode<T>* new_node = new QueueNode<T>(data);
      this->__tail->next = new_node;
      this->__tail = new_node;
    };

    this->__size++;
  };

  // getSize
  size_t getSize() { return this->__size; };

  // print
  void print(QueueForEachCallBack<T> cb) {
    this->__forEach(cb);
  };

  // clear
  void clear() {
    while(this->__head != nullptr) this->dequeue();
  };
};

int main() {
  // print
  QueueForEachCallBack<int> printInt = [](const QueueNode<int>* qn) {
    cout << qn->data << " ";
  };

  Queue<int> q({ 10, 30, -1, 45, 100 });

  cout << "Print q: \n"; q.print(printInt);
  cout << endl << endl;

  // dequeue
  q.dequeue();

  cout << "Size of q after dequeue: " << q.getSize() << endl;
  cout << "Print q: \n"; q.print(printInt);

  cout << endl << endl;

  // clear
  cout << "Clear all\n";
  q.clear();
  cout << "Size of q after clear: " << q.getSize() << endl << endl;

  // push
  q.enqueue(30);
  q.enqueue(100);
  q.enqueue(-2);
  q.dequeue();
  q.enqueue(4);
  q.dequeue();
  q.enqueue(5);

  cout << "Size of q after enqueue: " << q.getSize() << endl;
  cout << "Print q: \n"; q.print(printInt);
  cout << endl << endl;
  return 0;
};
