/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Hash Table với giải pháp đụng độ index
  Separate Chaining với value có kiểu dữ liệu là int. Với các phương thức:
  - insert
  - remove
  - get

  Hashtable này chỉ nhận vào key là int.

  Ấn build để nó hiện ra từng message của lỗi.
  Để thực thi và xem các ví dụ thì comment những chỗ code lỗi lại.
*/

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Bucket {
public:
  int key = -1;
  int* value = nullptr;

  Bucket() = default;
  Bucket(int k, int* v): key{k}, value{v} {};

  bool isEmpty() {
    return this->value == nullptr;
  };

  void reset() {
    this->key = -1;
    delete this->value;
    this->value = nullptr;
  };
};

using ConstBucketCallBack = function<void(int, int*)>;

// With Separate Chaining
class HashTable {
private:
  vector<vector<Bucket>> __data = vector<vector<Bucket>>(10);

  int __getIndexOfBucket(int key) {
    int index = this->hash(key);
    int j = 0;

    while(__data[index][j].key != key) {
      j++;
    };

    return j;
  };

public:
  HashTable() = default;
  HashTable(size_t s) {
    this->__data = vector<vector<Bucket>>(10);
  };

  // hash
  int hash(int key, bool hashOnly = false) {
    return key % __data.size();
  };

  // insert
  void insert(int key, int value) {
    int index = this->hash(key);
    __data[index].push_back(Bucket(key, new int(value)));
  };

  // remove
  void remove(int key) {
    if(__data.size() == 0) return;
    int index = this->hash(key);

    if(__data[index].size() == 0) return;

    int j = this->__getIndexOfBucket(key);

    if(__data[index][j].isEmpty()) return;

    __data[index].erase(__data[index].begin() + j);
  };

  // get
  int* get(int key) {
    int index = this->hash(key);

    if(__data[index].size() == 0) return nullptr;

    int j = this->__getIndexOfBucket(key);

    if(__data[index][j].isEmpty()) return nullptr;

    return __data[index][j].value;
  };

  // getSize
  size_t getSize() {
    return __data.size();
  };

  // forEach
  void forEach(ConstBucketCallBack cb) {
    vector<vector<Bucket>>::iterator itr = __data.begin();
    vector<vector<Bucket>>::iterator end_itr = __data.end();
    int c = 0;
    while(itr != end_itr) {
      if((*itr).size() == 0) {
        c++;
        itr++;
        continue;
      };

      vector<Bucket>::iterator sub_itr = (*itr).begin();
      vector<Bucket>::iterator sub_end_itr = (*itr).end();
      cout << "Bucket list [" << c << "]: \n";
      while(sub_itr != sub_end_itr) {
        cb(sub_itr->key, sub_itr->value);
        sub_itr++;
      };

      c++;
      itr++;
    };
  };
};

int main() {
  // Print value
  ConstBucketCallBack printValue = [](int k, int* v) {
    int value = (v == nullptr) ? 0 : *v;
    cout << "(K: " << k << ", V: " << value << ")\n";
  };

  // Declare a hash table
  HashTable ht;

  // Insert data
  cout << "Size: " << ht.getSize() << endl;
  ht.insert(0, 12);
  ht.insert(3, 2);
  ht.insert(100, -100);
  ht.insert(1, 8);
  ht.insert(12, 34);
  ht.insert(7, -19);
  ht.insert(6, 23);
  ht.insert(5, 22);

  // print
  cout << "Print table: \n";
  ht.forEach(printValue);
  cout << endl;

  // print element with key.
  cout << "Key: 3 => Value: " << *(ht.get(3)) << endl;
  cout << "Key: 100 => Value: " << *(ht.get(100)) << endl;
  cout << "Key: 12 => Value: " << *(ht.get(12)) << endl;
  cout << "Key: 7 => Value: " << *(ht.get(7)) << endl;
  cout << "Key: 6 => Value: " << *(ht.get(6)) << endl;

  // Delete key 0
  cout << endl;
  cout << "Remove value with key 0, 5, 6\n";
  ht.remove(0);
  ht.remove(5);
  ht.remove(6);
  cout << endl;

  // print
  cout << "Print table: \n";
  ht.forEach(printValue);
  cout << endl;

  // print element with key.
  cout << "Key: 0 => Value: " << (ht.get(0) == nullptr ? 0 : *(ht.get(0))) << endl;
  cout << "Key: 5 => Value: " << (ht.get(5) == nullptr ? 0 : *(ht.get(0))) << endl;
  cout << "Key: 6 => Value: " << (ht.get(6) == nullptr ? 0 : *(ht.get(0))) << endl;
  cout << "Key: 1 => Value: " << *(ht.get(1)) << endl;
  cout << "Key: 100 => Value: " << *(ht.get(100)) << endl;
  cout << "Key: 100 => Value: " << *(ht.get(100)) << endl;
  cout << "Key: 12 => Value: " << *(ht.get(12)) << endl;

  return 0;
};
