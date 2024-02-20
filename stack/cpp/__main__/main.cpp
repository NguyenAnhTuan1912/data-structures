#include <iostream>
#include <exception>

#include "stack.h"

using namespace std;

int main() {
  // Print
  StackForEachCallBack<int> printInt = [](const StackNode<int>* sn) { cout << sn->data << " "; };

  Stack<int> s = {10, 20, -2, 3, 5, 8, 11, 201, 30, 99, -39, -32, -41};

  try {
    // print
    cout << "Size of stack: " << s.getSize() << endl;
    cout << "Print stack: \n"; s.print(printInt);
    cout << endl << endl;

    // pop more
    cout << "Pop 6 times\n";
    s.pop(); s.pop(); s.pop(); s.pop(); s.pop(); s.pop();
    cout << endl;

    // print
    cout << "Size of stack: " << s.getSize() << endl;
    cout << "Print stack: \n"; s.print(printInt);
    cout << endl;

    // push more
    cout << "Push 3 items\n";
    s.push(9998);
    s.push(9999);
    s.push(10000);
    cout << endl;

    // print
    cout << "Size of stack: " << s.getSize() << endl;
    cout << "Print stack: \n"; s.print(printInt);
    cout << endl << endl;

    // clear all
    cout << "CLEAR ALL!!!\n";
    s.clear();
    cout << endl;

    // print
    cout << "Size of stack: " << s.getSize() << endl;
    cout << "Print stack: \n"; s.print(printInt);
    cout << endl;

    // push until error
    cout << "Push until error\n";
    int i = 0;
    while(true) {
      s.push(i);
      i += 105;
    };
    cout << endl;

    // print
    cout << "Size of stack: " << s.getSize() << endl;
    cout << "Print stack: \n"; s.print(printInt);
    cout << endl;

    return 0;
  } catch(const exception& e) {
    cout << "Size of stack: " << s.getSize();
    cout << endl << endl;
    cerr << e.what();
    cout << endl;

    return 1;
  };
};
