/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của Ternary Tree, mọi thay đổi về cấu trúc
  của Ternary Tree sẽ được thay đổi trong này.
*/

#ifndef TERNARY_TREE_H_INCLUDED
#define TERNARY_TREE_H_INCLUDED

#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include <exception>

enum TreeTraverseType {
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
  TTNode(int key, T* data): key{key}, data{std::move(data)} {};
  TTNode(int key, T* data, TTNode<T>* left, TTNode<T>* mid, TTNode<T>* right)
  : key{key}, data{data}, left{std::move(left)}, mid{std::move(mid)}, right{std::move(right)} {};
};

template<class T>
using ConstTTNodeCallBack = std::function<void(const TTNode<T>*m, int parentKey, int depth)>;

template<class T>
class TTree {
private:
  TTNode<T>* __root = nullptr;
  size_t __count = 0;
  int __depth = 0;
  size_t __leftCount = 0;
  size_t __midCount = 0;
  size_t __rightCount = 0;

  // Static methods
  // These methods are fundamental operations.
  static void __traverseInorder(ConstTTNodeCallBack<T>& cb, TTNode<T>* curr, int parentKey, int d);
  static void __traversePreorder(ConstTTNodeCallBack<T>& cb, TTNode<T>* curr, int parentKey, int d);
  static void __traversePostorder(ConstTTNodeCallBack<T>& cb, TTNode<T>* curr, int parentKey, int d);
  static TTNode<T>* __insert(int key, T*& data, TTNode<T>* curr, int& d, int& c);
  static bool __isFullOfChildren(TTNode<T>* node);
  static bool __getDepthFromCurrentNode(TTNode<T>* node);
  static bool __isChildrenCountBalance(TTree<T>* tree);
  static int __getNumberOfDirectChildrenOfNode(TTNode<T>* node);

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
    int d = 0, c = 0;
    
    if(this->__root == nullptr) {
      this->__root = this->__insert(key, data, this->__root, d, c);
      this->__count = c;
      return;
    };

    // If tree is balance, add to left first.
    if(this->__isChildrenCountBalance(this)) {
      c = this->__leftCount;
      this->__root->left = this->__insert(key, data, this->__root->left, ++d, c);
      this->__leftCount = c;
    }
    // Add to mid
    else if(!this->__isChildrenCountBalance(this) && this->__midCount == this->__rightCount) {
      c = this->__midCount;
      this->__root->mid = this->__insert(key, data, this->__root->mid, ++d, c);
      this->__midCount = c;
    }
    // Add to right
    else {
      c = this->__rightCount;
      this->__root->right = this->__insert(key, data, this->__root->right, ++d, c);
      this->__rightCount = c;
    };
    
    this->__depth = d > this->__depth ? d : this->__depth;
    this->__count = this->__leftCount + this->__rightCount + this->__midCount + 1;
  };

  // traverse
  void traverse(ConstTTNodeCallBack<T>& cb, TreeTraverseType TreeTraverseType = Inorder) {
    int d = 0;
    switch(TreeTraverseType) {
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

template<class T>
bool TTree<T>::__isChildrenCountBalance(TTree<T>* tree) {
  return (tree->__leftCount == tree->__midCount) && (tree->__leftCount == tree->__rightCount);
};

template<class T>
int TTree<T>::__getNumberOfDirectChildrenOfNode(TTNode<T>* node) {
  int c = node->left != nullptr ? 1 : 0;
  c += (node->mid != nullptr ? 1 : 0);
  c += (node->right != nullptr ? 1 : 0);
  return c;
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
    TTree<T>::__traverseInorder(cb, curr->left, curr->key, d + 1);
  };

  // Execute callback
  cb(curr, parentKey, d);

  if(curr->mid != nullptr) {
    TTree<T>::__traversePreorder(cb, curr->mid, curr->key, d + 1);
  };

  if(curr->right != nullptr) {
    TTree<T>::__traverseInorder(cb, curr->right, curr->key, d + 1);
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
    TTree<T>::__traversePreorder(cb, curr->left, curr->key, d + 1);
  };

  if(curr->mid != nullptr) {
    TTree<T>::__traversePreorder(cb, curr->mid, curr->key, d + 1);
  };

  if(curr->right != nullptr) {
    TTree<T>::__traversePreorder(cb, curr->right, curr->key, d + 1);
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
    TTree<T>::__traversePostorder(cb, curr->left, curr->key, d + 1);
  };

  if(curr->mid != nullptr) {
    TTree<T>::__traversePreorder(cb, curr->mid, curr->key, d + 1);
  };

  if(curr->right != nullptr) {
    TTree<T>::__traversePostorder(cb, curr->right, curr->key, d + 1);
  };

  // Execute callback
  cb(curr, parentKey, d);
};

template<class T>
TTNode<T>* TTree<T>::__insert(int key, T*& data, TTNode<T>* curr, int& d, int& c) {
  try {
    if(curr == nullptr) {
      c++;
      return new TTNode<T>(key, data);
    };
    if(curr->key == key) throw std::runtime_error("Cannot add this Node, because this key is exist before!!!");
    
    if(curr->left == nullptr) {
      curr->left = TTree<T>::__insert(key, data, curr->left, ++d, c);
      return curr;
    }
    else if(curr->mid == nullptr) {
      curr->mid = TTree<T>::__insert(key, data, curr->mid, ++d, c);
      return curr;
    }
    else if(curr->right == nullptr) {
      curr->right = TTree<T>::__insert(key, data, curr->right, ++d, c);
      return curr;
    };

    // Traverse
    int
      nChildrenOfLeftChild = TTree<T>::__getNumberOfDirectChildrenOfNode(curr->left),
      nChildrenOfMidChild = TTree<T>::__getNumberOfDirectChildrenOfNode(curr->mid),
      nChildrenOfRightChild = TTree<T>::__getNumberOfDirectChildrenOfNode(curr->right);
   
    // To left
    if(TTree<T>::__isFullOfChildren(curr)
        || ((nChildrenOfLeftChild == nChildrenOfMidChild) && (nChildrenOfLeftChild == nChildrenOfRightChild))
    ) {
      curr->left = TTree<T>::__insert(key, data, curr->left, ++d, c);
    }
    // To mid
    else if(nChildrenOfLeftChild > nChildrenOfMidChild) {
      curr->mid = TTree<T>::__insert(key, data, curr->mid, ++d, c);
    }
    // To right
    else {
      curr->right = TTree<T>::__insert(key, data, curr->right, ++d, c);
    };

    return curr;
  } catch(const std::exception& e) {
    std::cout << "Insert Error: ";
    std::cerr << e.what();
    return nullptr;
  };
};

#endif // TERNARY_TREE_H_INCLUDED
