/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Ternary Tree

  Ấn build để nó hiện ra từng message của lỗi.
  Để thực thi và xem các ví dụ thì comment những chỗ code lỗi lại.
*/

#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include <exception>

using namespace std;

enum TraverseType {
  Empty,
  Inorder,
  Preorder,
  Postorder
};

template<class T>
class TTNode {
public:
  int key = 0;
  T* data = nullptr;
  TTNode<T>* left = nullptr;
  TTNode<T>* mid = nullptr;
  TTNode<T>* right = nullptr;

  TTNode() = default;
  TTNode(int key, T* data): key{key}, data{data} {};
  TTNode(int key, T* data, TTNode<T>* left, TTNode<T>* mid, TTNode<T>* right)
  : key{key}, data{data}, left{move(left)}, mid{move(mid)}, right{move(right)} {};
};

template<class T>
using ConstBSTNodeCallBack = function<void(const TTNode<T>*m, int parentKey, int depth)>;

template<class T>
class TTree {
private:
  TTNode<T>* __root = nullptr;
  size_t __count = 0;
  int __depth = 0;

  // Static methods
  static TTNode<T>* __search(int key, TTNode<T>* curr = nullptr);
  static TTNode<T>* __delete(int key, TTNode<T>* curr, int& c);
  static void __traverseInorder(ConstBSTNodeCallBack<T>& cb, TTNode<T>* curr, int parentKey, int d);
  static void __traversePreorder(ConstBSTNodeCallBack<T>& cb, TTNode<T>* curr, int parentKey, int d);
  static void __traversePostorder(ConstBSTNodeCallBack<T>& cb, TTNode<T>* curr, int parentKey, int d);
  static void __insert(int key, T*& data, TTNode<T>* curr, int& d, int& c);

public:
  TTree() = default;
  TTree(int key, T* data) {
    this->__root = new TTNode<T>(key, data);
    this->__count++;
  };
  TTree(int key, T data) {
    this->__root = new TTNode<T>(key, new T(data));
    this->__count++;
  };

  // Static methods
  static bool isLeaf(const TTNode<T>* curr);
  static bool isLeaf(TTNode<T>* curr);

  // insertItem

  // deleteItem

  // searchItem

  // getDepth

  // traverse
};

int main() {
  return 0;
};
