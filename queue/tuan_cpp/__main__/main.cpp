#include <iostream>

#include "queue.h"

using namespace std;

int main() {
  // Create some lambda
  ConstQueueNodeCallBack<int> printInt = [](const QueueNode<int>* qn) {
    cout << qn->data << " ";
  };

  // Initialize new queue
  Queue<int> q = {1, 2, 3, 4, 5};

  // print
  cout << "print q: \n";
  q.forEach(printInt);
  cout << endl << endl;

  // dequeue 2 first nodes: 1 and 2
  cout << "Dequeue 2 first nodes...\n";
  q.dequeue();
  q.dequeue();
  // print
  cout << "print q: \n";
  q.forEach(printInt);
  cout << endl << endl;

  // get
  // remove 3 from queue
  cout << "Get first node...\n";
  QueueNode<int>* qn = q.get();
  cout << "Node: " << qn->data << endl;
  // print
  cout << "print q: \n";
  q.forEach(printInt);
  cout << endl;

  // delete got node
  // REMEMBER DELETE
  delete qn;
  cout << endl;

  // clear
  cout << "CLEAR ALL!!!\n";
  q.clear();
  cout << endl;

  // enqueue more nodes
  cout << "Enqueue more nodes...\n";
  q.enqueue(100);
  q.enqueue(-20);
  q.enqueue(8);
  // print
  cout << "print q: \n";
  q.forEach(printInt);
  cout << endl;

  return 0;
};
