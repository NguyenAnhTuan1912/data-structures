/*
  @author Nguyen Anh Tuan
  Question:
  Create a generic Queue to control the sequence of processes
  (callbacks, instances of class are recommended). Add perform
  method to perform the first Node’s task, then dequeue.

  Done.
*/

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

using namespace std;

class Task {
public:
  string name = "";
  int times = 0;
  int attemps = 0;

  Task(string n, int t = 0): name{n}, times{t} {};

  void perform() {
    cout << "Perform task: " << name << " in " << attemps << " attemps.\n";
    attemps++;
  };

  bool isDone() {
    return attemps >= times;
  };
};

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
using ForEachCallBack = function<void(const QueueNode<T>* sn)>;
template<class T>
using PerformCallBack = function<bool(const QueueNode<T>* sn)>;
template<class T>
using PerformNonConstCallBack = function<bool(QueueNode<T>* sn)>;

template<class T>
class Queue {
private:
  QueueNode<T>* __head = nullptr;
  QueueNode<T>* __tail = nullptr;
  size_t __size = 0;

  void __forEach(ForEachCallBack<T> cb) {
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
  void print(ForEachCallBack<T> cb) {
    this->__forEach(cb);
  };

  // clear
  void clear() {
    while(this->__head != nullptr) this->dequeue();
  };

  // perform
  void perform(PerformCallBack<T> cb) {
    if(cb(this->__head)) this->dequeue();
  };
  void perform(PerformNonConstCallBack<T> cb) {
    if(cb(this->__head)) this->dequeue();
  };
};

int main() {
  // Create a queue to save numbers to use later.
  Queue<int> number_queue = {1, 10, 5, -10, -2, -3, -7, 54, 12, 32};

  // Create a queue to save lambda
  Queue<Task> task_queue = {{"Save data", 5}, {"Load data", 3}};

  // initialize some vars
  int
    pos_sum = 0,
    neg_sum = 0,
    perform_number_queue_times = 0,
    perform_task_queue_times = 0;

  PerformCallBack<int> calcSum = [&](const QueueNode<int>* qn) {
    if(qn->data >= 0) {
      pos_sum += qn->data;
      if(pos_sum % 2 != 0) {
        return false;
      };
    } else {
      neg_sum += qn->data;
      if(neg_sum % 2 != 0) {
        return false;
      };
    };

    return true;
  };

  PerformNonConstCallBack<Task> performTask = [](QueueNode<Task>* qn) {
    qn->data.perform();
    return qn->data.isDone();
  };

  while(number_queue.getSize() != 0) {
    number_queue.perform(calcSum);
    perform_number_queue_times++;
  };

  cout << "Sum of positive number: " << pos_sum << endl;
  cout << "Sum of negative number: " << neg_sum << endl;
  cout << "Iterate number queue times: " << perform_number_queue_times << endl;

  cout << endl;

  while(task_queue.getSize() != 0) {
    task_queue.perform(performTask);
    perform_task_queue_times++;
  };
  cout << endl;

  cout << "Iterate task queue times: " << perform_task_queue_times << endl;

  return 0;
};
