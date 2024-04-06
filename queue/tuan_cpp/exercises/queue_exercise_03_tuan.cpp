/*
  @author Nguyen Anh Tuan
  Question:
  Simulate a process of kitchen in a restaurant by following:
    a. Restaurant must ensure that customers who order food or drink first must be served first (First in First out).
    b. Each food or drink have a process that requires an amount of time to complete.
    c. Food or drink will be served when it is prepared. Otherwise, it’s still in the process.

	Note: kitchen can overheat if there are too many things to do.

  Done.
*/

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>
#include <exception>
#include<unistd.h>
#include <memory>

using namespace std;

// Declaration
template<class T>
class QueueNode;
template<class T>
class Queue;
class Product;
class Drink;
class Food;
class Ingredient;

template<class T>
using PerformCallBack = function<bool(const QueueNode<T>*)>;

template<class T>
class QueueNode {
public:
  T data;
  QueueNode<T>* next = nullptr;

  QueueNode() = default;
  QueueNode(T p): data{p} {};
  QueueNode(T p, QueueNode<T>* qn): data{p}, next{move(qn)} {};
  ~QueueNode() {
    delete this->next;

    this->next = nullptr;
  };
};

template<class T>
class Queue {
private:
  QueueNode<T>* __head = nullptr;
  QueueNode<T>* __tail = nullptr;
  size_t __size = 0;
  size_t __max_size = 10;

public:
  Queue() = default;
  Queue(size_t max_size): __max_size{max_size} {};
  ~Queue() {
    this->clear();
  };

  // dequeue
  void dequeue() {
    if(this->__head == nullptr) return;

    QueueNode<T>* ptr = this->__head;
    this->__head = this->__head->next;

    this->__size--;
  };

  // enqueue
  bool enqueue(T data) {
    try {
      if(this->__size == this->__max_size) throw runtime_error("Queue is full!!!");
      if(this->__head == nullptr) {
        this->__head = new QueueNode<T>(data);
        this->__tail = this->__head;
      } else {
        QueueNode<T>* new_node = new QueueNode<T>(data);
        this->__tail->next = new_node;
        this->__tail = new_node;
      };

      this->__size++;
      return true;
    } catch(const exception& e) {
      cout << "Enqueue error: ";
      cerr << e.what();
      return false;
    }
  };

  // getSize
  size_t getSize() { return this->__size; };

  void clear() {
    while(this->__head != nullptr) {
      delete this->__head;
      this->__head = this->__head;
    };

    this->__tail = nullptr;
    this->__size = 0;
  };

  // With lambda (or function)
  void perform(PerformCallBack<T> cb) {
    if(cb(this->__head)) this->dequeue();
  };

  // With pointer of function
  void perform(bool (*ptr)(const QueueNode<T>*)) {
    if((*ptr)(this->__head)) this->dequeue();
  };
};

class Ingredient {
public:
  string name = "";
  float preparationTime = 0;

  Ingredient() = default;
  Ingredient(string n, float pt): name{n}, preparationTime{pt} {};
};

class Product {
protected:
  Queue<Ingredient*> _igd;

public:
  string name = "";
  float price = 0.0;
  float calories = 0.0;
  string type = "";

  static bool make(const QueueNode<Ingredient*>* p);

  Product() = default;
  Product(string n, float p, float c, string t)
  : name{n}, price{p}, calories{c}, type{t} {};

  void addIngredients(initializer_list<Ingredient*> lst) {
    typename initializer_list<Ingredient*>::iterator ptr = lst.begin();

    while(ptr != lst.end()) {
      this->_igd.enqueue(*ptr);
      ptr++;
    }
  };

  void process() {
    cout << "Prepare: " << name << endl;
    while(this->_igd.getSize() > 0) {
      this->_igd.perform(&Product::make);
    };
    cout << "Done!!!\n\n";
  };

  virtual void print() {
    cout
      << "("
      << "Name: " << name << ", "
      << "Price: " << price << ", "
      << "Calories: " << calories << ", "
      << "Type: " << type << ")\n";
  };
};

class Drink : public Product {
public:
  Drink(): Product() {};
  Drink(string n, float p, float c): Product(n, p, c, "drink") {};
};

class Food : public Product {
public:
  Food(): Product() {};
  Food(string n, float p, float c): Product(n, p, c, "food") {};
};

// Define some static methods
bool Product::make(const QueueNode<Ingredient*>* ptr) {
  cout << "Prepare: " << ptr->data->name << " in " << ptr->data->preparationTime << "s...\n";
  sleep(ptr->data->preparationTime);
  return true;
};

class ProcessQueue : public Queue<Product*> {
public:
  ProcessQueue(): Queue() {};
  ProcessQueue(size_t max_size): Queue(max_size) {};
  PerformCallBack<Product*> cb = [](const QueueNode<Product*>* ptr) {
    ptr->data->process();
    return true;
  };

  // process
  void process() {
    while(this->getSize() > 0) {
      this->perform(cb);
    };
  };
};

int main() {
  // Declare ProcessQueue
  ProcessQueue pq = ProcessQueue(8);

  // Create ingredients
  // Ingredient for Pho
  Ingredient* ptr_phoNoodle = new Ingredient("Banh pho", 2);
  Ingredient* ptr_beef = new Ingredient("Thit bo", 1);
  Ingredient* ptr_onion = new Ingredient("Hanh tay", 2.5);
  Ingredient* ptr_phoSoup = new Ingredient("Nuoc leo pho", 1);

  // Ingredient for Hu tieu
  Ingredient* ptr_hutieuNoodle = new Ingredient("Banh hu tieu", 1);
  Ingredient* ptr_porkRibs = new Ingredient("Suon heo", 1.5);
  Ingredient* ptr_mincedMeat = new Ingredient("Thit heo bam", 2);
  Ingredient* ptr_hutieuSoup = new Ingredient("Nuoc leo hu tieu", 1);

  // Ingredient for Banh canh
  Ingredient* ptr_banhcanhNoodle = new Ingredient("Banh banh canh", 1.5);
  Ingredient* ptr_meat = new Ingredient("Thit heo", 1);
  Ingredient* ptr_pigTrotter = new Ingredient("Gio heo", 1.5);
  Ingredient* ptr_banhcanhSoup = new Ingredient("Nuoc leo banh canh", 1);

  // Ingredient for Bun thi nuong
  Ingredient* ptr_noodle = new Ingredient("Bun", 0.5);
  Ingredient* ptr_grilledMeat = new Ingredient("Thit heo nuong", 2);
  Ingredient* ptr_sweetNSourFishSoup = new Ingredient("Nuoc mam chua ngot", 0.5);

  // Ingredient for Tra tac
  Ingredient* ptr_clementine = new Ingredient("Qua tac", 0.5);

  // Ingredient for Nuoc cam
  Ingredient* ptr_orange = new Ingredient("Qua cam", 0.5);

  // General
  Ingredient* ptr_beanSprouts = new Ingredient("Gia do", 0.5);
  Ingredient* ptr_garlicChives = new Ingredient("La he", 1);
  Ingredient* ptr_warmWater = new Ingredient("Nuoc am", 2);
  Ingredient* ptr_sugar = new Ingredient("Duong", 1);
  Ingredient* ptr_ice = new Ingredient("Da lanh", 0.5);

  // Create menu
  // Pho
  Food* pho = new Food("Pho", 40000, 400);
  // Hu tieu
  Food* hutieu = new Food("Hu tieu", 35000, 325);
  // Hu tieu kho
  Food* hutieukho = new Food("Hu tieu kho", 35000, 325);
  // Banh canh
  Food* banhcanh = new Food("Banh canh", 30000, 350);
  // Bun thit nuong
  Food* bunthitnuong = new Food("Bun thit nuong", 25000, 255);
  // Tra tac
  Drink* tratac = new Drink("Tra tac", 10000, 50);
  // Nuoc cam
  Drink* nuoccam = new Drink("Nuoc cam", 15000, 70);

  // Add ingredients
  pho->addIngredients({ ptr_phoNoodle, ptr_beef, ptr_onion, ptr_phoSoup, ptr_beanSprouts });
  hutieu->addIngredients({ ptr_hutieuNoodle, ptr_porkRibs, ptr_mincedMeat, ptr_hutieuSoup, ptr_beanSprouts, ptr_garlicChives });
  hutieukho->addIngredients({ ptr_hutieuNoodle, ptr_porkRibs, ptr_mincedMeat, ptr_beanSprouts, ptr_garlicChives });
  banhcanh->addIngredients({ ptr_banhcanhNoodle, ptr_meat, ptr_pigTrotter, ptr_banhcanhSoup });
  bunthitnuong->addIngredients({ ptr_noodle, ptr_grilledMeat, ptr_sweetNSourFishSoup });
  tratac->addIngredients({ ptr_clementine, ptr_warmWater, ptr_sugar, ptr_ice });
  nuoccam->addIngredients({ ptr_orange, ptr_warmWater, ptr_sugar, ptr_ice });

  // Order
  pq.enqueue(pho);
  pq.enqueue(hutieukho);
  pq.enqueue(tratac);

  // Prepare
  pq.process();

  return 0;
}
