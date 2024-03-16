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
using ConstTTNodeCallBack = function<void(const TTNode<T>*m, int parentKey, int depth)>;

template<class T>
class TTree {
private:
  TTNode<T>* __root = nullptr;
  size_t __count = 0;
  int __depth = 0;

  // Static methods
  // These methods are fundamental operations.
  static void __traverseInorder(ConstTTNodeCallBack<T>& cb, TTNode<T>* curr, int parentKey, int d);
  static void __traversePreorder(ConstTTNodeCallBack<T>& cb, TTNode<T>* curr, int parentKey, int d);
  static void __traversePostorder(ConstTTNodeCallBack<T>& cb, TTNode<T>* curr, int parentKey, int d);
  static void __insert(int key, T*& data, TTNode<T>* curr, int& d, int& c);
  static bool __isFullOfChildren(TTNode<T>* node);

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
  static bool isLeaf(const TTNode<T>* node);
  static bool isLeaf(TTNode<T>* node);

  // insertItem
  void insertItem(int key, T* data) {
    int d = 0, c = this->__count;

    if(this->__root != nullptr) this->__insert(key, data, this->__root, ++d, c);
    else {
      this->__root = new TTNode<T>(key, data);
      c++;
    };

    this->__count = c;
    if(d > this->__depth) this->__depth = d;
  };

  // traverse
  void traverse(ConstTTNodeCallBack<T>& cb, TraverseType traverseType = Inorder) {
    int d = 0;
    switch(traverseType) {
      case Preorder: {
        this->__traversePreorder(cb, this->__root, this->__root->key, d);
        break;
      };

      case Postorder: {
        this->__traversePostorder(cb, this->__root, this->__root->key, d);
        break;
      };

      case Inorder:
      default: {
        this->__traverseInorder(cb, this->__root, this->__root->key, d);
        break;
      };
    };
  };

  // getDepth
  int getDepth() {
    if(this->__root == nullptr) return 0;
    return this->__depth;
  };
};

// Define static method
template<class T>
bool TTree<T>::isLeaf(const TTNode<T>* node) {
  return (node->left == nullptr) && (node->right == nullptr) && (node->mid == nullptr);
};

template<class T>
bool TTree<T>::isLeaf(TTNode<T>* node) {
  return (node->left == nullptr) && (node->right == nullptr) && (node->mid == nullptr);
};

template<class T>
bool TTree<T>::__isFullOfChildren(TTNode<T>* node) {
  return (node->left != nullptr) && (node->right != nullptr) && (node->mid != nullptr);
};

/*
  Left -> Root -> Mid -> Right
*/
template<class T>
void TTree<T>::__traverseInorder(
  ConstTTNodeCallBack<T>& cb,
  TTNode<T>* curr,
  int parentKey,
  int d
) {
  if(curr == nullptr) return;

  if(curr->left != nullptr) {
    __traverseInorder(cb, curr->left, curr->key, d + 1);
  };

  // Execute callback
  cb(curr, parentKey, d);

  if(curr->mid != nullptr) {
    __traversePreorder(cb, curr->mid, curr->key, d + 1);
  };

  if(curr->right != nullptr) {
    __traverseInorder(cb, curr->right, curr->key, d + 1);
  };
};

/*
  Root -> Left -> Mid -> Right
*/
template<class T>
void TTree<T>::__traversePreorder(
  ConstTTNodeCallBack<T>& cb,
  TTNode<T>* curr,
  int parentKey,
  int d
) {
  if(curr == nullptr) return;

  // Execute callback
  cb(curr, parentKey, d);

  if(curr->left != nullptr) {
    __traversePreorder(cb, curr->left, curr->key, d + 1);
  };

  if(curr->mid != nullptr) {
    __traversePreorder(cb, curr->mid, curr->key, d + 1);
  };

  if(curr->right != nullptr) {
    __traversePreorder(cb, curr->right, curr->key, d + 1);
  };
};

/*
  Left -> Mid -> Right -> Root
*/
template<class T>
void TTree<T>::__traversePostorder(
  ConstTTNodeCallBack<T>& cb,
  TTNode<T>* curr,
  int parentKey,
  int d
) {
  if(curr == nullptr) return;

  if(curr->left != nullptr) {
    __traversePostorder(cb, curr->left, curr->key, d + 1);
  };

  if(curr->mid != nullptr) {
    __traversePreorder(cb, curr->mid, curr->key, d + 1);
  };

  if(curr->right != nullptr) {
    __traversePostorder(cb, curr->right, curr->key, d + 1);
  };

  // Execute callback
  cb(curr, parentKey, d);
};

template<class T>
void TTree<T>::__insert(int key, T*& data, TTNode<T>* curr, int& d, int& c) {
  try {
    if(curr == nullptr) {
      d--;
      return;
    };
    if(curr->key == key) throw runtime_error("Cannot add this Node, because this key is exist before!!!");

    bool isLeft = (key < curr->key);

    // Assign to left
    if(isLeft && curr->left == nullptr) {
      curr->left = new TTNode<T>(key, data);
      c++;
      return;
    }
    // Assign to right
    else if(!isLeft && curr->right == nullptr) {
      curr->right = new TTNode<T>(key, data);
      c++;
      return;
    }
    // Assign to mid
    else if(curr->mid == nullptr) {
      curr->mid = new TTNode<T>(key, data);
      c++;
      return;
    };

    bool isRight = (key > curr->key);

    isLeft = isLeft && (key < curr->mid->key);
    isRight = isRight && (key > curr->mid->key);

    // Pass through left
    if(isLeft) TTree<T>::__insert(key, data, curr->left, ++d, c);
    else if(isRight) TTree<T>::__insert(key, data, curr->right, ++d, c);
    else TTree<T>::__insert(key, data, curr->mid, ++d, c);

    return;
  } catch(const exception& e) {
    cout << "Insert Error: ";
    cerr << e.what();
  };
};

int main() {
  // Lambda
  ConstTTNodeCallBack<string> printStrValue = [](const TTNode<string>* node, int parentKey, int depth) {
    cout << *(node->data) << endl;
  };

  ConstTTNodeCallBack<int> printIntValue = [](const TTNode<int>* node, int parentKey, int depth) {
    cout << *(node->data) << " ";
  };

  // Declare Ternary Tree
  TTree<string> tree;
  TTree<int> tree02 = TTree<int>(30, new int(30));

  // Insert
  tree.insertItem(30, new string("Hello"));
  tree.insertItem(10, new string("Day"));
  tree.insertItem(20, new string("Cay Tam Phan"));
  tree.insertItem(15, new string("La"));

  tree02.insertItem(10, new int(10));
  tree02.insertItem(20, new int(20));
  tree02.insertItem(50, new int(50));
  tree02.insertItem(5, new int(5));
  tree02.insertItem(6, new int(6));
  tree02.insertItem(15, new int(15));
  tree02.insertItem(16, new int(16));
  tree02.insertItem(17, new int(17));
  tree02.insertItem(21, new int(21));

  // Traverse
  cout << "Traverse tree (Inorder)\n";
  tree.traverse(printStrValue);
  cout << endl;
  cout << "Traverse tree (Preorder)\n";
  tree.traverse(printStrValue, Preorder);
  cout << endl;
  cout << "Traverse tree (Postorder)\n";
  tree.traverse(printStrValue, Postorder);
  cout << endl;

  // Get depth
  cout << "Depth of tree: " << tree.getDepth() << endl;

  cout << endl;

  // Traverse
  cout << "Traverse tree02 (Inorder)\n";
  tree02.traverse(printIntValue);
  cout << endl;
  cout << "Traverse tree02 (Preorder)\n";
  tree02.traverse(printIntValue, Preorder);
  cout << endl;
  cout << "Traverse tree02 (Postorder)\n";
  tree02.traverse(printIntValue, Postorder);
  cout << endl;
  
  cout << endl;

  // Get depth
  cout << "Depth of tree: " << tree02.getDepth() << endl;

  return 0;
};
