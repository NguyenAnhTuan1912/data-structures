/*
  @author Nguyen Anh Tuan
  Question:
  Create a generic Stack has pop, push, getSize, isEmpty and getTop.
  Initializer 3 stack of People, Animals and Vehicle (each stack has
  arbitrary numbers of items). Perform all methods of Stack.

  Done.
*/

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>
#include <exception>

using namespace std;

class Person {
public:
  string name = "";
  int age = 0;

  Person() = default;
  Person(string n, int a): name{n}, age{a} {};

  void print() const {
    cout << "(" << name << ", " << age << ")\n";
  };
};

class Animal {
public:
  string name = "";
  string breed = "";
  int age = 0;

  Animal() = default;
  Animal(string n, int a, string b): name{n}, age{a}, breed{b} {};

  void print() const {
    cout << "(" << name << ", " << breed << ", " << age << ")\n";
  };
};

class Vehicle {
public:
  string name = "";
  string color = "";
  float speed = 0;

  Vehicle() = default;
  Vehicle(string n, float s, string c): name{n}, speed{s}, color{c} {};

  void print() const {
    cout << "(" << name << ", " << color << ", " << speed << ")\n";
  };
};

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
    StackForEachCallBack<Person> printPerson = [](const StackNode<Person>* sn) {
      sn->data.print();
    };
    StackForEachCallBack<Animal> printAnimal = [](const StackNode<Animal>* sn) {
      sn->data.print();
    };
    StackForEachCallBack<Vehicle> printVehicle = [](const StackNode<Vehicle>* sn) {
      sn->data.print();
    };

    Stack<Person> people({{"Jason", 21}, {"Michael", 22}, {"Jake", 23}}, 5);
    Stack<Animal> animals({{"Len", 3, "cat"}, {"Kiki", 1, "dog"}}, 3);
    Stack<Vehicle> vehicles({{"Kia", 130.45, "white"}, {"Lamborghini", 270, "yellow"}}, 2);

    // print
    cout << "Print people: \n";
    people.print(printPerson);
    cout << endl;
    cout << "Print animals: \n";
    animals.print(printAnimal);
    cout << endl;
    cout << "Print vehicles: \n";
    vehicles.print(printVehicle);
    cout << endl;

    // push
    cout << "Push more item to people, animals and vehicles...\n";
    people.push({"Fionna", 25});
    animals.push({"Pooh", 8, "bear"});
    cout << endl;

    // print    cout << "Print people: \n";
    people.print(printPerson);
    cout << endl;
    cout << "Print animals: \n";
    animals.print(printAnimal);
    cout << endl;
    cout << "Print vehicles: \n";
    vehicles.print(printVehicle);
    cout << endl;

    // get size
    cout << "Size of people: " << people.getSize() << endl;
    cout << "Size of animals: " << animals.getSize() << endl;
    cout << "Size of vehicles: " << vehicles.getSize() << endl;

    // pop
    cout << "Pop top item of people, animals and vehicles...\n";
    people.pop();
    animals.pop();
    vehicles.pop();
    cout << endl;

    // print
    cout << "Print people: \n";
    people.print(printPerson);
    cout << endl;
    cout << "Print animals: \n";
    animals.print(printAnimal);
    cout << endl;
    cout << "Print vehicles: \n";
    vehicles.print(printVehicle);
    cout << endl;

    // clear
    cout << "CLEAR ALL!!!\n";
    people.clear();
    animals.clear();
    vehicles.clear();
    cout << endl;

    // get size
    cout << "Size of people: " << people.getSize() << endl;
    cout << "Size of animals: " << animals.getSize() << endl;
    cout << "Size of vehicles: " << vehicles.getSize() << endl;
    cout << endl;

    // push more
    people.push({"Franklin", 30});
    vehicles.push({"Koenigsegg One:1", 417, "red and black"});
    vehicles.push({"Nissan Skyline R34", 278.2, "blue"});

    // print
    cout << "Print people: \n";
    people.print(printPerson);
    cout << endl;
    cout << "Print animals: \n";
    animals.print(printAnimal);
    cout << endl;
    cout << "Print vehicles: \n";
    vehicles.print(printVehicle);
    cout << endl;

    // error
    vehicles.push({"Ferrari 458 Italia", 312.78, "red"});

    return 0;
  } catch(const exception& e) {
    cout << endl << endl;
    cerr << e.what();
    cout << endl;
    return 1;
  };
};
