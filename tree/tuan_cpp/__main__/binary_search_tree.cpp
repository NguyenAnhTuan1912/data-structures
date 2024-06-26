/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của Binary Search Tree, mọi thay đổi về cấu trúc
  của Binary Search Tree sẽ được thay đổi trong này.
*/

#ifndef BINARY_SEARCH_TREE_H_INCLUDED
#define BINARY_SEARCH_TREE_H_INCLUDED

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
class BSTNode {
public:
  int key = 0;
  T* data = nullptr;
  BSTNode<T>* left = nullptr;
  BSTNode<T>* right = nullptr;

  BSTNode() = default;
  BSTNode(int key, T* data): key{key}, data{data} {};
  BSTNode(int key, T* data, BSTNode<T>* left, BSTNode<T>* right)
  : key{key}, data{data}, left{move(left)}, right{move(right)} {};
};

template<class T>
using ConstBSTNodeCallBack = std::function<void(const BSTNode<T>*m, int parentKey, int depth)>;

template<class T>
class BSTree {
private:
  BSTNode<T>* __root = nullptr;
  size_t __count = 0;
  int __depth = 0;

  // Static methods
  static BSTNode<T>* __search(int key, BSTNode<T>* curr = nullptr);
  static BSTNode<T>* __delete(int key, BSTNode<T>* curr, int& c);
  static void __traverseInorder(ConstBSTNodeCallBack<T>& cb, BSTNode<T>* curr, int parentKey, int d);
  static void __traversePreorder(ConstBSTNodeCallBack<T>& cb, BSTNode<T>* curr, int parentKey, int d);
  static void __traversePostorder(ConstBSTNodeCallBack<T>& cb, BSTNode<T>* curr, int parentKey, int d);
  static BSTNode<T>* __insert(int key, T*& data, BSTNode<T>* curr, int& d, int& c);

public:
  BSTree() = default;
  BSTree(int key, T* data) {
    this->__root = new BSTNode<T>(key, data);
    this->__count++;
  };
  BSTree(int key, T data) {
    this->__root = new BSTNode<T>(key, new T(data));
    this->__count++;
  };

  // Static methods
  static bool isLeaf(const BSTNode<T>* curr);
  static bool isLeaf(BSTNode<T>* curr);

  // insertItem
  void insertItem(int key, T* data) {
    int d = 0, c = this->__count;

    this->__root = this->__insert(key, data, this->__root, ++d, c);

    this->__count = c;
    if(d > this->__depth) this->__depth = d;
  };

  // deleteItem
  void deleteItem(int key) {
    int c = this->__count;
    this->__delete(key, this->__root, c);
    this->__count = c;
  };

  // searchItem
  T* searchItem(int key, BSTNode<T>* curr = nullptr) {
    if(curr == nullptr) curr = this->__root;
    BSTNode<T>* result = this->__search(key, curr);
    if(result == nullptr) return nullptr;
    return result->data;
  };

  // traverse
  void traverse(ConstBSTNodeCallBack<T>& cb, TreeTraverseType TreeTraverseType = Inorder) {
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

  // print
  void print() {
    int D = this->__depth, maxOutputLength = 0;
    std::vector<std::string> output((D + 1) * 2 - 1);

    ConstBSTNodeCallBack<T> cb = [&](const BSTNode<T>* node, int parentKey, int depth) {
      int index = depth * 2, M = 0, N = 0;
      std::string dashes = "", spaces = "", subOutput = "", keyStr = std::to_string(node->key);

      // Root of subtree
      if(!this->isLeaf(node)) {
        // Generate "-" for left child
        if(node->left != nullptr) {
          if(output[index + 1] == "") {
            N = output[index + 2].size() - 1;
            M = maxOutputLength - N;
            M = M < 2 ? 2 : M;
          } else {
            N = maxOutputLength - output[index + 1].size() - 1;
            M = 2;
          };

          dashes = std::string(N, ' ');
          dashes += std::string(M, '-');

          output[index + 1] += dashes;

          maxOutputLength = output[index + 1].size() > maxOutputLength ? output[index + 1].size() : maxOutputLength;
        }

        // Add key string
        N = maxOutputLength - output[index].size() - 1;

        subOutput = std::string(N, ' ');
        subOutput += keyStr;

        output[index] += subOutput;

        maxOutputLength = output[index].size() > maxOutputLength ? output[index].size() : maxOutputLength;

        // Generate "-" for right child
        N = 0, M = 0;
        if(node->right != nullptr) {
          if(output[index + 1] == "") {
            N = maxOutputLength - 1;
            M = std::to_string(node->right->key).size() + 1;
          } else {
            N = maxOutputLength - output[index + 1].size() - (keyStr.size());
            N = N < 0 ? 0 : N;
            M = keyStr.size() + 1;
          };

          dashes = std::string(N, ' ');
          dashes += std::string(M, '-');

          output[index + 1] += dashes;

          maxOutputLength = output[index + 1].size() > maxOutputLength ? output[index + 1].size() : maxOutputLength;
        }
      }
      // Left
      else if(node->key < parentKey) {
        N = maxOutputLength - output[index].size() - 1;

        if(output[index] == "") N = N < 0 ? 0 : N;
        else N = N < 0 ? 1 : N;

        subOutput = std::string(N, ' ');
        subOutput += keyStr;

        output[index] += subOutput;

        maxOutputLength = output[index].size() > maxOutputLength ? output[index].size() : maxOutputLength;
      }
      // Right
      else if(node->key > parentKey) {
        N = maxOutputLength - 1;

        if(output[index] != "") {
          N = maxOutputLength - output[index].size() - 1;
        };

        subOutput = std::string(N, ' ');
        subOutput += keyStr;

        output[index] += subOutput;

        maxOutputLength = output[index].size() > maxOutputLength ? output[index].size() : maxOutputLength;
      };
    };

    this->traverse(cb, Inorder);

    // Last update dashes for right child of root
    std::string rightKey = std::to_string(this->__root->right->key);

    int M = output[2].size() - output[1].size() - (rightKey.size() - 1);

    if(M > 0) {
      output[1] += std::string(M, '-');
      // Add more space
      output[0] = std::string(M / 2, ' ') + output[0];
    }

    typename std::vector<std::string>::iterator itr = output.begin();

    while(itr != output.end()) {
      std::cout << *itr << std::endl;
      itr++;
    };
  };
};

// Define static method
template<class T>
bool BSTree<T>::isLeaf(const BSTNode<T>* curr) {
  return (curr->left == nullptr) && (curr->right == nullptr);
};

template<class T>
bool BSTree<T>::isLeaf(BSTNode<T>* curr) {
  return (curr->left == nullptr) && (curr->right == nullptr);
};

template<class T>
void BSTree<T>::__traverseInorder(
  ConstBSTNodeCallBack<T>& cb,
  BSTNode<T>* curr,
  int parentKey,
  int d
) {
  if(curr == nullptr) return;

  if(curr->left != nullptr) {
    BSTree<T>::__traverseInorder(cb, curr->left, curr->key, d + 1);
  };

  // Execute callback
  cb(curr, parentKey, d);

  if(curr->right != nullptr) {
    BSTree<T>::__traverseInorder(cb, curr->right, curr->key, d + 1);
  };
};

template<class T>
void BSTree<T>::__traversePreorder(
  ConstBSTNodeCallBack<T>& cb,
  BSTNode<T>* curr,
  int parentKey,
  int d
) {
  if(curr == nullptr) return;

  // Execute callback
  cb(curr, parentKey, d);

  if(curr->left != nullptr) {
    BSTree<T>::__traversePreorder(cb, curr->left, curr->key, d + 1);
  };

  if(curr->right != nullptr) {
    BSTree<T>::__traversePreorder(cb, curr->right, curr->key, d + 1);
  };
};

template<class T>
void BSTree<T>::__traversePostorder(
  ConstBSTNodeCallBack<T>& cb,
  BSTNode<T>* curr,
  int parentKey,
  int d
) {
  if(curr == nullptr) return;

  if(curr->left != nullptr) {
    BSTree<T>::__traversePostorder(cb, curr->left, curr->key, d + 1);
  };

  if(curr->right != nullptr) {
    BSTree<T>::__traversePostorder(cb, curr->right, curr->key, d + 1);
  };

  // Execute callback
  cb(curr, parentKey, d);
};

template<class T>
BSTNode<T>* BSTree<T>::__search(int key, BSTNode<T>* curr) {
  if(curr == nullptr) return nullptr;
  if(curr->key == key) return curr;

  bool isLeft = (key < curr->key);

  if(isLeft) {
    return BSTree<T>::__search(key, curr->left);
  }

  return BSTree<T>::__search(key, curr->right);
};

template<class T>
BSTNode<T>* BSTree<T>::__insert(int key, T*& data, BSTNode<T>* curr, int& d, int& c) {
  try {
    if(curr == nullptr) {
      c++;
      return new BSTNode<T>(key, data);
    };
    if(curr->key == key) throw std::runtime_error("Cannot add this Node, because this key is exist before!!!");

    bool isLeft = (key < curr->key);

    // Assign to left
    if(isLeft && curr->left == nullptr) {
      curr->left = BSTree<T>::__insert(key, data, curr->left, ++d, c);
      return curr;
    };

    // Assign to right
    if(!isLeft && curr->right == nullptr) {
      curr->right = BSTree<T>::__insert(key, data, curr->right, ++d, c);
      return curr;
    };

    // Pass through left
    if(isLeft) curr->left = BSTree<T>::__insert(key, data, curr->left, ++d, c);
    else curr->right = BSTree<T>::__insert(key, data, curr->right, ++d, c);

    return curr;
  } catch(const std::exception& e) {
    std::cout << "Insert Error: ";
    std::cerr << e.what();
    return nullptr;
  };
};

template<class T>
BSTNode<T>* BSTree<T>::__delete(int key, BSTNode<T>* curr, int& c) {
  if(curr == nullptr) return nullptr;

  // Search
  if (key < curr->key) {
    curr->left = BSTree<T>::__delete(key, curr->left, c);
    return curr;
  } else if(key > curr->key) {
    curr->right = BSTree<T>::__delete(key, curr->right, c);
    return curr;
  };

  // If Node is leaf Node
  if(BSTree<T>::isLeaf(curr)) {
    delete curr;
    c--;
    return nullptr;
  };

  // Match
  // If Node has one child
  // Left
  if(curr->left == nullptr) {
    BSTNode<T>* temp = curr;
    temp = curr->right;
    delete curr;
    c--;
    return curr;
  }
  // Right
  else if(curr->right == nullptr) {
    BSTNode<T>* temp = curr;
    temp = curr->left;
    delete curr;
    c--;
    return curr;
  };

  // If Node has both
  BSTNode<T>* ptrLeft = curr->left;
  BSTNode<T>* ptrRight = curr->right;


  while(ptrLeft->right != nullptr || ptrRight->left != nullptr) {
    if(ptrLeft->right != nullptr) {
      ptrLeft = ptrLeft->right;
    };

    if(ptrRight->left != nullptr) {
      ptrRight = ptrRight->left;
    };
  };

  if(BSTree<T>::isLeaf(ptrLeft)) {
    ptrLeft->right = curr->right;

    delete curr;
    c--;

    return ptrLeft;
  }

  ptrRight->left = curr->left;

  delete curr;
  c--;

  return ptrRight;
};

#endif // BINARY_SEARCH_TREE_H_INCLUDED
