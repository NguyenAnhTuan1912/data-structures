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

  // TO DO: dùng để lấy hashed index.
  //
  // Nhận vào key là std::string để lấy ra hashed index của bucket có
  // bucket.key = key.
  // Các bước thực hiện:
  // 1. Lấy hashed index từ hash với hashOnly = true.
  // 2. Bắt đầu vòng lặp while
  //   2.0. Nếu như bucket.key = key hoặc hashed index = table size - 1, thì dừng lại.
  //   2.1. Tăng hashed index lên 1, quay lại bước 2.0.
  // 3. Trả về hashed index.
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

  // TO DO: tạo một hashed index.
  //
  // Nhận vào một key là std::string và hasOnly dùng để cho biết là hàm này
  // chỉ hash hay hash -> kiểm tra dữ liệu -> hash tiếp?
  //
  // Note: với open addressing approach thì mình cũng khá thiếu chính xác,
  // cân nhắc khi sử dụng approach này.
  //
  // Các bước thực hiện:
  // 1. Lặp từng char của key, sau đó tính tổng của char.
  // 2. Hash, lấy phần dư của tổng key với số phần tử trong vector.
  // 3. Nếu như hashOnly = true, thì mình sẽ trả về hashed index.
  // 4. Bắt đầu vòng lặp while với việc check dữ liệu tại hashed index.
  //   4.0. Nếu như phần từ tại hashed index là empty thì dừng vòng lặp, không
  //   thì tới bước tiếp theo.
  //   4.1. Nhảy hashed index lên 1 bước. Quay lại bước 4.0.
  // 5. Sau khi kết thúc bước 4, mình có được index để lưu dữ liệu mới, tại đây
  // thì mình có thể trả về hashed index luôn. Nhưng vì OA approach, nên mình phải
  // resize lại table.
  // 6. Trả về hashed index.
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

  // TO DO: thêm một bucket (chứa data) mới vào trong table.
  //
  // Nhận vào một key là std::string và có value là T. Một bucket sẽ được tạo
  // từ key và value.
  // Note: trong table, thì bucket đã tồn tại, nhưng dữ liệu của nó thì trống.
  // Các bước thực hiện:
  // 1. Kiểm tra xem bucket này trồng hay không, nếu không trống thì thông báo và dừng
  // việc thêm. Còn trống thì tới bước tiếp theo.
  // 2. Hash key.
  // 3. Assign key và tạo value cho bucket.
  //
  // Nghĩa là khi bucket đã tồn tại dữ liệu thì sẽ nhảy sang một bucket khác.
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

  // TO DO: remove dữ liệu ra khỏi bucket (KHÔNG XÓA BUCKET)
  //
  // Nhận vào key là std::string của bucket cần xóa.
  // Các bước thực hiện:
  // 1. Nếu như table rỗng thì dừng lại.
  // 2. Lấy hashed index từ key.
  // 3. Reset dữ liệu của bucket tương ứng.
  void remove(std::string key) {
    if(__data.size() == 0) return;
    int index = this->__getIndex(key);
    __data[index].reset();
  };

  // TO DO: lấy dữ liệu trong bucket.
  //
  // Nhận vào key là std::string của bucket cần lấy dữ liệu.
  // Các bước thực hiện:
  // 1. Lấy hashed index từ key.
  // 2. Trả về value của bucket tương ứng. Nếu như value rỗng thì nó trả về `nullptr`.
  T* get(std::string key) {
    int index = this->__getIndex(key);
    return __data[index].value;
  };

  // TO DO: kiểm tra xem bucket có data hay chưa.
  //
  // Nhận vào key là std::string của bucket cần check.
  // Các bước thực hiện:
  // 1. Lấy hashed index từ key.
  // 2. Kiểm tra key và bucket.key xem có giống nhau hay không.
  bool isBucketEmpty(std::string key) {
    int index = this->__getIndex(key);
    return __data[index].key != key;
  };

  // TO DO: trả về size của table.
  //
  // Note: size này không phải ánh được việc có bao nhiêu dữ liệu đã được lưu,
  // nó cho biết trong table đã có bao nhiêu bucket.
  size_t getSize() {
    return __data.size();
  };

  // TO DO:
  //
  // Nhận vào một callback để tùy chỉnh việc thao tác với dữ liệu.
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
