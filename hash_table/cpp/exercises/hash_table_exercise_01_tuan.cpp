/*
  @author Nguyen Anh Tuan
  Quetions 1:
  Create a generic HashTable to store the data of devices with Open Addressing Resolution.

  Done.
*/

#include <iostream>
#include <vector>
#include <functional>
#include <math.h>

#include "Device.h"

using namespace std;

bool isPrime(int n) {
  int limit = sqrt(n);
  cout << "Limit: " << limit << endl;
  for(int i = 2; i < limit; i++) {
    if(n % i == 0) return false;
  };
  return true;
};

template<class T>
class Bucket {
public:
  string key = "";
  T* value = nullptr;

  Bucket() = default;
  Bucket(string k, T* d): key{k}, value{d} {};

  bool isEmpty() {
    return this->value == nullptr;
  };

  void reset() {
    delete this->value;
    this->key = "";
    this->value = nullptr;
  };
};

template<class T>
using ConstBucketCallBack = function<void(string, T*)>;

template<class T>
class HashTable {
private:
  vector<Bucket<T>> __data = vector<Bucket<T>>(11);

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
    this->__data = vector<Bucket<T>>(s);
  };

  // hash
  int hash(string key, bool hashOnly = false) {
    int index = 0;
    int i = 0;

    while(key[i] != '\0') {
      index += key[i];
      i++;
    };

    // Hash
    index %= __data.size();

    if(hashOnly) return index;

    while(!(__data[index].isEmpty())) {
      // Jump 1 slots
      index += 1;
    };

    cout << "Hash - key: " << key << ", index: " << index << endl;

    size_t old_size = __data.size();
    if(index >= __data.size()) {
        size_t new_size = __data.size() * 2;
        while(!isPrime(new_size)) {
          new_size++;
        };
      __data.resize(new_size);
    };

    return index;
  };

  // insert
  void insert(string key, T value) {
    // Check key
    if(!this->isBucketEmpty(key)) {
      cout << "The key " << key << " existed!!\n";
      return;
    };

    int index = this->hash(key);

    __data[index].key = key;
    __data[index].value = new T(value);
  };

  // remove
  void remove(string key) {
    if(__data.size() == 0) return;
    int index = this->__getIndex(key);
    __data[index].reset();
  };

  // get
  T* get(string key) {
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
  void forEach(ConstBucketCallBack<T> cb) {
    typename vector<Bucket<T>>::iterator itr = __data.begin();
    typename vector<Bucket<T>>::iterator end_itr = __data.end();

    while(itr != end_itr) {
      cb(itr->key, itr->value);
      itr++;
    };
  };
};

int main() {
  // Print value
  ConstBucketCallBack<Device> printDevice = [](string k, Device* v) {
    if(v == nullptr) {
        cout << "(K: " << k << ", V: )\n";
      return;
    };
    cout << "(K: " << k << ", V: "; v->print(); cout << ")\n";
  };
  ConstBucketCallBack<string> printSentence = [](string k, string* v) {
    string value = (v == nullptr) ? "" : *v;
    cout << "(K: " << k << ", V: " << value << ")\n";
  };

  // Declare a hash table
  HashTable<Device> device_ht;
  HashTable<string> sentence_ht;

  cout << "INITIAL SIZE: \n";
  cout << "Size: " << device_ht.getSize() << endl;
  cout << "Size: " << sentence_ht.getSize() << endl;
  cout << endl;

  // Add items
  cout << "Add some items...\n";
  device_ht.insert("ap_01", {"iPhone 12 pro", "Apple", 999.99});
  device_ht.insert("ap_02", {"Macbook pro", "Apple", 1999.99});
  device_ht.insert("gg_01", {"Pixel", "Google", 649.50});
  device_ht.insert("nv_01", {"Nvidia Geforce GTX 1080", "Nvidia", 229.99});
  device_ht.insert("sdg", {"Error01", "Unknown", 0});
  device_ht.insert("xvdfg", {"Error02", "Unknown", 0});
  device_ht.insert("zxvas", {"Error03", "Unknown", 0});
  device_ht.insert("gg_02", {"Google Wifi", "Google", 299.79});
  device_ht.insert("ss_01", {"Samsung Galaxy Note 10", "Samsung", 248.90});

  sentence_ht.insert("0", "Hello");
  sentence_ht.insert("1", "Day la bai tap ve");
  sentence_ht.insert("2", "HashTable");
  sentence_ht.insert("1", "Key nay bi trung roi");
  sentence_ht.insert("34", "cannot read");
  sentence_ht.insert("3", "Co cac phuong thuc nhu la: ");
  sentence_ht.insert("2", "Key ney bi trung tiep");
  sentence_ht.insert("40", "cannot readdf");
  sentence_ht.insert("4", "insert, delete, get");
  sentence_ht.insert("5", "HashTable nay nhan key-value la int-string");
  sentence_ht.insert("asdfh", "Don't know");
  sentence_ht.insert("ash", "I'm virus");
  sentence_ht.insert("asdad", "Delete me if you can");
  sentence_ht.insert("87fjhs", "You can't see me");
  sentence_ht.insert("lkj4", "DELETEEEEEE");
  cout << endl;

  // print
  cout << "Print devices: \n";
  cout << "Size: " << device_ht.getSize() << endl;
  device_ht.forEach(printDevice);
  cout << endl;

  cout << "Print sentence: \n";
  cout << "Size: " << sentence_ht.getSize() << endl;
  sentence_ht.forEach(printSentence);
  cout << endl;

  // Remove items
  cout << "Remove some items...\n";
  device_ht.remove("sdg");
  device_ht.remove("xvdfg");
  device_ht.remove("zxvas");

  sentence_ht.remove("34");
  sentence_ht.remove("40");
  sentence_ht.remove("asdfh");
  sentence_ht.remove("ash");
  sentence_ht.remove("asdad");
  sentence_ht.remove("87fjhs");
  sentence_ht.remove("lkj4");
  cout << endl;

  // print
  cout << "Print devices: \n";
  cout << "Size: " << device_ht.getSize() << endl;
  device_ht.forEach(printDevice);
  cout << endl;

  cout << "Print sentence: \n";
  cout << "Size: " << sentence_ht.getSize() << endl;
  sentence_ht.forEach(printSentence);
  cout << endl;

  // Get with key
  Device* d_get_01 = device_ht.get("ap_02");
  Device* d_get_02 = device_ht.get("nv_01");
  Device* d_get_03 = device_ht.get("ss_01");
  string* s_get_01 = sentence_ht.get("0");
  string* s_get_02 = sentence_ht.get("2");

  cout << "Get data in device_ht with key \"ap_02\": ";
  if(d_get_01 == nullptr) cout << "Empty\n";
  else { d_get_01->print(); cout << endl; };

  cout << "Get data in device_ht with key \"nv_01\": ";
  if(d_get_02 == nullptr) cout << "Empty\n";
  else { d_get_02->print(); cout << endl; };

  cout << "Get data in device_ht with key \"ss_01\": ";
  if(d_get_03 == nullptr) cout << "Empty\n";
  else { d_get_03->print(); cout << endl; };

  cout << "Get data in sentence_ht with key \"0\": ";
  if(s_get_01 == nullptr) cout << "Empty\n";
  else cout << *s_get_01 << endl;

  cout << "Get data in sentence_ht with key \"2\": ";
  if(s_get_01 == nullptr) cout << "Empty\n";
  else cout << *s_get_02 << endl;

  return 0;
};
