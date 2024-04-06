#include <iostream>

#include "doubly_linked_list.h"
#include "linked_list.h"

using namespace std;

class Point {
public:
  int x = 0;
  int y = 0;

  Point() = default;
  Point(int x, int y): x{x}, y{y} {};
  explicit Point(int n): x{n}, y{n} {};

  void print() {
    cout << "(" << x << "; " << y << ")\n";
  };
};

class Person {
public:
  string name = "";
  int age = 0;

  Person() = default;
  Person(string n, int a): name{n}, age{a} {};

  void print() {
    cout << name << ", " << age << "\n";
  };
};

int main() {
  // Compare functions
  CompareFn<Point> lListInsertIncreasingly = [](Point& curr, Point& data) { return curr.x >= data.x; };
  CompareFn<Person> doublyLListInsertPersonIncreasinglyByAge = [](Person& curr, Person& data) { return curr.age >= data.age; };

  // Print
  ConstSinglyLLNodeCallBack<Point> printPoint = [](SinglyLLNode<Point>* n, int index) {
    n->data.print();
  };
  ConstDoublyLLNodeCallBack<Person> printPerson = [](DoublyLLNode<Person>* n, int index) {
    n->data.print();
  };

  // Declare list
  LinkedList<Point> points;
  DoublyLinkedList<Person> people;

  // Add Nodes
  points.insertFirst({ 1, 2 });
  points.insertFirst({ -4, 3 });
  points.insertLast({ 10, -9 });
  points.insertLast({ 3, 4 });
  points.insertOrderBy({ -10, 3 }, lListInsertIncreasingly);
  points.insertOrderBy({ 8, 11 }, lListInsertIncreasingly);

  people.insertFirst({ "Carl", 40 });
  people.insertFirst({ "Sweet", 45 });
  people.insertLast({ "Woozie", 42 });
  people.insertLast({ "Katalina", 38 });
  people.insertOrderBy({ "Tuan", 21 }, doublyLListInsertPersonIncreasinglyByAge);
  people.insertOrderBy({ "A", 11 }, doublyLListInsertPersonIncreasinglyByAge);

  // Print list.
  cout << "Print points: \n";
  points.forEach(printPoint);
  cout << endl;
  cout << "Print people: \n";
  people.forEach(printPerson);
  cout << endl;

  // Get Nodes
  cout << "Get 4 points randomly: \n";
  cout << "Get point at 1: "; (points.getAt(1))->data.print();
  cout << "Get point at -10: "; (points.getAt(-10))->data.print();
  cout << "Get point at 4: "; (points.getAt(4))->data.print();
  cout << "Get point at 5: "; (points.getAt(5))->data.print();
  cout << endl;
  cout << "Get 4 people randomly: \n";
  cout << "Get person at -99: "; (people.getAt(-99))->data.print();
  cout << "Get person at 1: "; (people.getAt(1))->data.print();
  cout << "Get person at 0: "; (people.getAt(0))->data.print();
  cout << "Get person at 3: "; (people.getAt(3))->data.print();
  cout << endl;

  // Remove Nodes
  points.removeFirst();
  points.removeLast();
  points.removeAt(3);

  people.removeFirst();
  people.removeLast();
  people.removeAt(1);

  // Print list.
  cout << "Print points: \n";
  points.forEach(printPoint);
  cout << endl;
  cout << "Print people: \n";
  people.forEach(printPerson);
  cout << endl;

  // Clear
  cout << "ClEAR ALL !!!\n\n";
  points.clear();
  people.clear();
  cout << endl;

  // Add Nodes
  cout << "Add some nodes...\n";
  points.insertAt({ 1, 2 }, 0);
  points.insertAt({ -4, 3 }, -10);
  points.insertAt({ 10, -9 }, 2);
  points.insertAt({ 3, 4 }, 999);
  points.insertOrderBy({ -10, 3 }, lListInsertIncreasingly);
  points.insertOrderBy({ 8, 11 }, lListInsertIncreasingly);

  people.insertAt({ "Carl", 40 }, 0);
  people.insertAt({ "Sweet", 45 }, -10);
  people.insertAt({ "Woozie", 42 }, 2);
  people.insertAt({ "Katalina", 38 }, 999);
  people.insertOrderBy({ "Tuan", 21 }, doublyLListInsertPersonIncreasinglyByAge);
  people.insertOrderBy({ "A", 11 }, doublyLListInsertPersonIncreasinglyByAge);
  cout << endl;

  // Print list.
  cout << "Print points: \n";
  points.forEach(printPoint);
  cout << endl;
  cout << "Print people (from head): \n";
  people.forEach(printPerson);
  cout << endl;
  cout << "Print people (from tail): \n";
  people.forEach(printPerson, false);
  cout << endl;

  return 0;
};
