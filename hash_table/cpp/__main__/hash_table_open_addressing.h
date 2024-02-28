/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của Hash table (open addressing), mọi thay đổi về cấu trúc
  của Hash table (open addressing) sẽ được thay đổi trong này.
*/


#ifndef HASH_TABLE_OPEN_ADDRESSING_H_INCLUDED
#define HASH_TABLE_OPEN_ADDRESSING_H_INCLUDED

#include <iostream>
#include <vector>
#include <functional>
#include <math.h>

#include "Bucket.h"

bool isPrime(int n) {
  int limit = std::sqrt(n);
  for(int i = 2; i < limit; i++) {
    if(n % i == 0) return false;
  };
  return true;
};

template<class T>
class HashTable {
private:
  std::vector<Bucket<T>> __data = std::vector<Bucket<T>>(11);

  int __getIndex(std::string key) {
    int index = this->hash(key, true);
    while(__data[index].key != key && index < __data.size() - 1) {
      index++;
    };

    return index;
  };

public:
  HashTable() = default;
  HashTable(size_t s) {
    this->__data = std::vector<Bucket<T>>(s);
  };

  // hash
  int hash(std::string key, bool hashOnly = false) {
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
  void insert(std::string key, T value) {
    // Check key
    if(!this->isBucketEmpty(key)) {
      std::cout << "The key " << key << " existed!!\n";
      return;
    };

    int index = this->hash(key);

    __data[index].key = key;
    __data[index].value = new T(value);
  };

  // remove
  void remove(std::string key) {
    if(__data.size() == 0) return;
    int index = this->__getIndex(key);
    __data[index].reset();
  };

  // get
  T* get(std::string key) {
    int index = this->__getIndex(key);
    return __data[index].value;
  };

  // isBucketEmpty
  bool isBucketEmpty(std::string key) {
    int index = this->__getIndex(key);
    return __data[index].key != key;
  };

  // getSize
  size_t getSize() {
    return __data.size();
  };

  // forEach
  void forEach(ConstBucketCallBack<T> cb) {
    typename std::vector<Bucket<T>>::iterator itr = __data.begin();
    typename std::vector<Bucket<T>>::iterator end_itr = __data.end();

    while(itr != end_itr) {
      cb(itr->key, itr->value);
      itr++;
    };
  };
};

#endif // HASH_TABLE_OPEN_ADDRESSING_H_INCLUDED
