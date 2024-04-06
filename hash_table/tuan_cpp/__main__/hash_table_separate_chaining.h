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

  // TO DO: dùng để lấy hashed index.
  //
  // Note: vì table nó không còn lưu theo từng bucket nữa, mà nó sẽ lưu theo từng
  // list bucket, nên mình cần phải biết được index của bucket trong list.
  // Nhận vào key là std::string để lấy ra hashed index của bucket có
  // bucket.key = key.
  // Các bước thực hiện:
  // 1. Khởi tạo index = 0.
  // 2. Bắt đầu vòng lặp while
  //   2.0. Nếu như bucket.key = key hoặc hashed index = table size - 1, thì dừng lại.
  //   2.1. Tăng hashed index lên 1, quay lại bước 2.0.
  // 3. Trả về index.
  int __getIndexOfBucket(int index, std::string key) {
    int index = 0;

    while(__data[index][index].key != key && j < __data[index].size() - 1) {
      index++;
    };

    return index;
  };

public:
  HashTable() = default;
  HashTable(size_t s) {
    this->__data = std::vector<std::vector<Bucket<T>>>(10);
  };

  // TO DO: tạo một hashed index.
  //
  // Nhận vào một key là std::string để hash.
  //
  // Note: với separate chaining thì mọi thứ dễ dàng và chính xác hơn. Nên dùng
  // approach này.
  //
  // Các bước thực hiện:
  // 1. Khởi tạo một biến đếm và total = 0.
  // 2. Bắt đầu vòng lặp while
  //   2.0. Nếu như i = key.size() nghĩa là lặp xong chuỗi key.
  //   2.1. Tăng total lên với giá trị bằng với kí tự hiện tại.
  //   2.2. Tăng biến đếm lên 1, quay lại bước 2.0.
  // 3. Trả về hashed index với phép tính dư giữa total và size của table.
  int hash(std::string key, bool hashOnly = false) {
    int i = 0, total = 0;

    while(key[i] != '\0') {
      total += key[i];
      i++;
    };

    return total % __data.size();
  };

  // TO DO: thêm một bucket (chứa data) mới vào trong table.
  //
  // Nhận vào một key là std::string và có value là T. Một bucket sẽ được tạo
  // từ key và value.
  // Note: trong table, thì bucket đã tồn tại, nhưng dữ liệu của nó thì trống.
  // Các bước thực hiện:
  // 1. Kiểm tra xem bucket cuối trong list này trống hay không, nếu không trống thì thông báo và dừng
  // việc thêm. Còn trống thì tới bước tiếp theo.
  // 2. Hash key.
  // 3. Tạo một bucket mới và push bucket này vào cuối list.
  void insert(std::string key, T value) {
    // Check key
    if(!this->isBucketEmpty(key)) {
      std::cout << "The key " << key << " existed!!\n";
      return;
    };

    int index = this->hash(key);
    __data[index].push_back(Bucket<T>(key, new T(value)));
  };

  // TO DO: remove bucket ra khỏi list.
  //
  // Nhận vào key là std::string của bucket cần xóa.
  // Các bước thực hiện:
  // 1. Nếu như table rỗng thì dừng lại.
  // 2. Hash key.
  // 3. Kiểm tra xem list có rỗng hay không thì dừng lại.
  // 4. Lấy index của bucket trong list.
  // 5. Nếu như bucket đó rỗng thì dừng lại.
  // 6. Xóa bucket đó ra khỏi list.
  void remove(std::string key) {
    if(__data.size() == 0) return;
    int index = this->hash(key);

    if(__data[index].size() == 0) return;

    int j = this->__getIndexOfBucket(index, key);

    if(__data[index][j].isEmpty()) return;

    __data[index].erase(__data[index].begin() + j);
  };

  // TO DO: lấy dữ liệu trong bucket.
  //
  // Nhận vào key là std::string của bucket cần lấy dữ liệu.
  // Các bước thực hiện:
  // 1. Nếu như table rỗng thì dừng lại.
  // 2. Hash key.
  // 3. Kiểm tra xem list có rỗng hay không thì dừng lại.
  // 4. Lấy index của bucket trong list.
  // 5. Nếu như bucket đó rỗng thì dừng lại.
  // 6. Trả về value của bucket, nếu như bucket đó rỗng hoặc không tồn tại thì trả về `nullptr`.
  T* get(std::string key) {
    int index = this->hash(key);

    if(__data[index].size() == 0) return nullptr;

    int j = this->__getIndexOfBucket(index, key);

    if(__data[index][j].isEmpty()) return nullptr;

    return __data[index][j].value;
  };

  // TO DO: kiểm tra xem bucket có data hay chưa.
  //
  // Nhận vào key là std::string của bucket cần check.
  // Các bước thực hiện:
  // 1. Lấy hashed index từ key.
  // 2. Nếu list rỗng thì trả về true.
  // 3. Lấy ra index của bucket với key và hashed index.
  // 4. Kiểm tra xem bucket.key có bằng với key hay không, trả về kết quả đó.
  bool isBucketEmpty(std::string key) {
    int index = this->hash(key);

    if(__data[index].size() == 0) return true;

    int j = this->__getIndexOfBucket(index, key);

    return __data[index][j].key != key;
  };

  // TO DO: trả về size của table.
  //
  // Note: size này không phải ánh được việc có bao nhiêu dữ liệu đã được lưu,
  // nó cho biết trong table đã có bao nhiêu list bucket.
  size_t getSize() {
    return __data.size();
  };

  // TO DO:
  //
  // Nhận vào một callback để tùy chỉnh việc thao tác với dữ liệu.
  // Với việc table chứa các list bucket, thì phải lặp tới từng list đó và
  // sau đó là lặp từng list đó thì mới có thể lấy được dữ liệu.
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
