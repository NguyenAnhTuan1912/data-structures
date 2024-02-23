/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Hash Table (Open Addressing),
  nhưng key bây giờ sẽ là char hoặc string. Và có check key trùng nhau

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
  string key = "";
  int* value = nullptr;

  Bucket() = default;
  Bucket(string k, int* v): key{k}, value{v} {};

  bool isEmpty() {
    return this->value == nullptr;
  };

  void reset() {
    this->key = "";
    delete this->value;
    this->value = nullptr;
  };
};

using ConstBucketCallBack = function<void(string, int*)>;

// With Open Addressing
class HashTable {
private:
  vector<Bucket> __data = vector<Bucket>(10);

  int __getIndex(string key) {
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
  int hash(string key, bool hashOnly = false) {
    int index = -1;
    int i = 0;

    while(key[i] != '\0') {
      index += key[i];
      i++;
    };

    // Hash
    index %= __data.size();

    if(hashOnly) return index;

    while(!(__data[index].isEmpty()) && index < __data.size() - 1) {
      // Jump 1 slots
      index += 1;
    };
    return index;
  };

  // insert
  void insert(string key, int value) {
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
  void remove(string key) {
    if(__data.size() == 0) return;
    int index = this->__getIndex(key);
    __data[index].reset();
  };

  // get
  int* get(string key) {
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

    string key;

    while(itr != end_itr) {
      key = (itr->key == "") ? "" : itr->key;
      cb(key, itr->value);
      itr++;
    };
  };
};

int main() {
  // Print value
  ConstBucketCallBack printValue = [](string k, int* v) {
    int value = (v == nullptr) ? 0 : *v;
    cout << "(K: " << k << ", V: " << value << ")\n";
  };

  // Declare a hash table
  HashTable ht;

  // Insert data
  cout << "Size: " << ht.getSize() << endl;
  cout << "Add data...\n";
  ht.insert("hello", 12);
  ht.insert("A", 2);
  ht.insert("B", -100);
  ht.insert("emp01", 8);
  ht.insert("k", 1200);
  ht.insert("hello_1", -2);

  // Insert data with existed key
  ht.insert("A", -22);
  ht.insert("B", -2);
  ht.insert("emp01", 120);
  ht.insert("k", 1080);
  cout << endl;

  // print
  cout << "Print table: \n";
  ht.forEach(printValue);
  cout << endl;

  // print element with key.
  cout << "Key: A => Value: " << (ht.get("A") == nullptr ? 0 : *(ht.get("A"))) << endl;
  cout << "Key: emp01 => Value: " << (ht.get("emp01") == nullptr ? 0 : *(ht.get("emp01"))) << endl;

  // Delete key 0
  cout << endl;
  cout << "Remove value with key B\n";
  ht.remove("B");
  cout << endl;

  // print
  cout << "Print table: \n";
  ht.forEach(printValue);
  cout << endl;

  // print element with key.
  cout << "Key: B => Value: " << (ht.get("B") == nullptr ? 0 : *(ht.get("B"))) << endl;
  cout << "Key: hello => Value: " << (ht.get("hello") == nullptr ? 0 : *(ht.get("hello"))) << endl;
  cout << "Key: k => Value: " << (ht.get("k") == nullptr ? 0 : *(ht.get("k"))) << endl;

  return 0;
};
