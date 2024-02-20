/*
  @author Nguyen Anh Tuan
  Question:
  Create a generic Queue has dequeue, enqueue, getSize, isEmpty.
  Initializer 2 queue of Drinks and Foods (each queue has arbitrary
  numbers of items). Perform all methods of Stack.

  Done.
*/

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

using namespace std;

class Supply {
public:
  string name = "";
  float price = 0.0;
  string type = "";

  Supply() = default;
  Supply(string n, float p, string t): name{n}, price{p}, type{t} {};

  void print() const {
    cout << name << ", " << price << endl;
  };
};

class Drink: public Supply {
public:
  Drink(): Supply() {};
  Drink(string n, float p): Supply(n, p, "drink") {};
};

class Food: public Supply {
public:
  Food(): Supply() {};
  Food(string n, float p): Supply(n, p, "food") {};
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
  QueueForEachCallBack<Drink> printDrink = [](const QueueNode<Drink>* qn) {
    qn->data.print();
  };
  QueueForEachCallBack<Food> printFood = [](const QueueNode<Food>* qn) {
    qn->data.print();
  };

  Queue<Drink> drink_queue = {{"Chivas", 12.24}, {"Coca", 1.0}, {"Coke", 1.2}};
  Queue<Food> food_queue = {{"Hotdog", 5}, {"Classic Pizza", 13.1}, {"Spagetti", 7.8}, {"Hot pot", 8.2}};

  // Print
  cout << "Print drink_queue: \n"; drink_queue.print(printDrink);
  cout << endl;
  cout << "Print food_queue: \n"; food_queue.print(printFood);
  cout << endl;

  // dequeue
  cout << "Dequeue items...\n";
  drink_queue.dequeue();
  drink_queue.dequeue();
  food_queue.dequeue();
  cout << endl;

  cout << "Size of drink_queue after dequeue: " << drink_queue.getSize() << endl;
  cout << "Size of food_queue after dequeue: " << food_queue.getSize() << endl;
  // Print
  cout << "Print drink_queue: \n"; drink_queue.print(printDrink);
  cout << endl;
  cout << "Print food_queue: \n"; food_queue.print(printFood);
  cout << endl;

  // clear
  cout << "Clear all\n";
  drink_queue.clear();
  food_queue.clear();

  cout << "Size of drink_queue after dequeue: " << drink_queue.getSize() << endl;
  cout << "Size of food_queue after dequeue: " << food_queue.getSize() << endl;

  cout << endl;

  // dequeue more
  cout << "Enqueue items...\n";
  drink_queue.enqueue({"Pepsi Vani", 2.25});
  drink_queue.enqueue({"Cafe", 1.0});
  drink_queue.enqueue({"Hot Cacao", 0.75});

  food_queue.enqueue({"Pho", 3});
  food_queue.enqueue({"Hu tieu", 2.2});
  food_queue.enqueue({"Vietnamese Bread", 1.2});
  food_queue.enqueue({"Bread", 1});
  cout << endl;

  // Print
  cout << "Print drink_queue: \n"; drink_queue.print(printDrink);
  cout << endl;
  cout << "Print food_queue: \n"; food_queue.print(printFood);
  cout << endl;
  return 0;
};
