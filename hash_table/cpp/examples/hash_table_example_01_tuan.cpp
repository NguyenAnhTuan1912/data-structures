/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Hash Table với giải pháp đụng độ index
  Open Addressing với value có kiểu dữ liệu là int. Với các phương thức:
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
    delete this->value;
    this->key = -1;
    this->value = nullptr;
  };
};

using ConstBucketCallBack = function<void(int, int*)>;

// With Open Addressing
class HashTable {
private:
  vector<Bucket> __data = vector<Bucket>(10);

  int __getIndex(int key) {
    int index = this->hash(key, true);
    while(__data[index].key != key && index < __data.size() - 1) {
      index++;
    };
    return index;
  };

public:
  HashTable() = default;
  HashTable(size_t s) {
    this->__data = vector<Bucket>(s);
  };

  // hash
  int hash(int key, bool hashOnly = false) {
    int index = key % __data.size();

    if(hashOnly) return index;

    while(!(__data[index].isEmpty()) && index < __data.size() - 1) {
      // Jump 1 slots
      index += 1;
    };
    return index;
  };

  // insert
  void insert(int key, int value) {
    // Check key
    if(!this->isBucketEmpty(key)) {
      cout << "The key " << key << " existed!!\n";
      return;
    };

    int index = this->hash(key);

    __data[index].key = key;
    __data[index].value = new int(value);
  };

  // remove
  void remove(int key) {
    if(__data.size() == 0) return;
    int index = this->__getIndex(key);
    __data[index].reset();
  };

  // get
  int* get(int key) {
    int index = this->__getIndex(key);
    return __data[index].value;
  };

  // isBucketEmpty
  bool isBucketEmpty(string key) {
    int index = this->__getIndex(key);
    return __data[index].key != key;
  };

  // getSize
  size_t getSize() {
    return __data.size();
  };

  // forEach
  void forEach(ConstBucketCallBack cb) {
    vector<Bucket>::iterator itr = __data.begin();
    vector<Bucket>::iterator end_itr = __data.end();

    while(itr != end_itr) {
      cb(itr->key, itr->value);
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
  ht.insert(0, 12);
  ht.insert(3, 2);
  ht.insert(100, -100);
  ht.insert(1, 8);

  // print
  cout << "Print table: \n";
  cout << "Size: " << ht.getSize() << endl;
  ht.forEach(printValue);
  cout << endl;

  // print element with key.
  cout << "Key: 3 => Value: " << *(ht.get(3)) << endl;
  cout << "Key: 100 => Value: " << *(ht.get(100)) << endl;

  // Delete key 0
  cout << endl;
  cout << "Remove value with key 0\n";
  ht.remove(0);
  cout << endl;

  // print
  cout << "Print table: \n";
  ht.forEach(printValue);
  cout << endl;

  // print element with key.
  cout << "Key: 0 => Value: " << (ht.get(0) == nullptr ? 0 : *(ht.get(0))) << endl;
  cout << "Key: 1 => Value: " << *(ht.get(1)) << endl;
  cout << "Key: 100 => Value: " << *(ht.get(100)) << endl;

  return 0;
};
