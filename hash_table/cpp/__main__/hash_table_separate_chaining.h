/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của Hash table (separate chaining), mọi thay đổi về cấu trúc
  của Hash table (separate chaining) sẽ được thay đổi trong này.
*/

#ifndef HASH_TABLE_SEPARATE_CHAINING_H_INCLUDED
#define HASH_TABLE_SEPARATE_CHAINING_H_INCLUDED

#include <iostream>
#include <vector>
#include <functional>

#include "Bucket.h"

template<class T>
class HashTable {
private:
  std::vector<std::vector<Bucket<T>>> __data = std::vector<std::vector<Bucket<T>>>(10);

  int __getIndexOfBucket(int index, std::string key) {
    int j = 0;

    while(__data[index][j].key != key && j < __data[index].size() - 1) {
      j++;
    };

    return j;
  };

public:
  HashTable() = default;
  HashTable(size_t s) {
    this->__data = std::vector<std::vector<Bucket<T>>>(10);
  };

  // hash
  int hash(std::string key, bool hashOnly = false) {
    int i = 0, index = 0;

    while(key[i] != '\0') {
      index += key[i];
      i++;
    };

    return index % __data.size();
  };

  // insert
  void insert(std::string key, T value) {
    // Check key
    if(!this->isBucketEmpty(key)) {
      std::cout << "The key " << key << " existed!!\n";
      return;
    };

    int index = this->hash(key);
    __data[index].push_back(Bucket<T>(key, new T(value)));
  };

  // remove
  void remove(std::string key) {
    if(__data.size() == 0) return;
    int index = this->hash(key);

    if(__data[index].size() == 0) return;

    int j = this->__getIndexOfBucket(index, key);

    if(__data[index][j].isEmpty()) return;

    __data[index].erase(__data[index].begin() + j);
  };

  // get
  T* get(std::string key) {
    int index = this->hash(key);

    if(__data[index].size() == 0) return nullptr;

    int j = this->__getIndexOfBucket(index, key);

    if(__data[index][j].isEmpty()) return nullptr;

    return __data[index][j].value;
  };

  // isBucketEmpty
  bool isBucketEmpty(std::string key) {
    int index = this->hash(key);

    if(__data[index].size() == 0) return true;

    int j = this->__getIndexOfBucket(index, key);

    return __data[index][j].key != key;
  };

  // getSize
  size_t getSize() {
    return __data.size();
  };

  // forEach
  void forEach(ConstBucketCallBack<T> cb) {
    typename std::vector<std::vector<Bucket<T>>>::iterator itr = __data.begin();
    typename std::vector<std::vector<Bucket<T>>>::iterator end_itr = __data.end();
    int c = 0;
    while(itr != end_itr) {
      if((*itr).size() == 0) {
        c++;
        itr++;
        continue;
      };

      typename std::vector<Bucket<T>>::iterator sub_itr = (*itr).begin();
      typename std::vector<Bucket<T>>::iterator sub_end_itr = (*itr).end();
      std::cout << "Bucket list [" << c << "]: \n";
      while(sub_itr != sub_end_itr) {
        cb(sub_itr->key, sub_itr->value);
        sub_itr++;
      };
      std::cout << "\n";

      c++;
      itr++;
    };
  };
};

#endif // HASH_TABLE_SEPARATE_CHAINING_H_INCLUDED
