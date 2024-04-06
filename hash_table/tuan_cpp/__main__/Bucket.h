#ifndef BUCKET_H_INCLUDED
#define BUCKET_H_INCLUDED

template<class T>
class Bucket {
public:
  std::string key = "";
  T* value = nullptr;

  Bucket() = default;
  Bucket(std::string k, T* v): key{k}, value{v} {};

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
using ConstBucketCallBack = std::function<void(std::string, T*)>;

#endif // BUCKET_H_INCLUDED
