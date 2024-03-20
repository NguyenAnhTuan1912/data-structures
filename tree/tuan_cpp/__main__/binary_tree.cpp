/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của Binary Tree, mọi thay đổi về cấu trúc
  của Binary Tree sẽ được thay đổi trong này. 
*/

#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED

#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include <exception>

enum TraverseType {
  Empty,
  Inorder,
  Preorder,
  Postorder
};

template<class T>
class BTNode {
public:
  int key = 0;
  T* data = nullptr;
  BTNode<T>* left = nullptr;
  BTNode<T>* right = nullptr;

  BTNode() = default;
  BTNode(int key, T* data): key{key}, data{data} {};
  BTNode(int key, T* data, BTNode<T>* left, BTNode<T>* right)
  : key{key}, data{data}, left{move(left)}, right{move(right)} {};
};

template<class T>
using ConstBTNodeCallBack = std::function<void(const BTNode<T>*,  BTNode<T>*, int depth)>;

template<class T>
class BTree {
private:
  BTNode<T>* __root = nullptr;
  size_t __count = 0;
  int __depth = 0;
  size_t __leftCount = 0;
  size_t __rightCount = 0;

  // Static methods
  static void __traverseInorder(ConstBTNodeCallBack<T>& cb, BTNode<T>* curr, BTNode<T>* parentNode, int d);
  static void __traversePreorder(ConstBTNodeCallBack<T>& cb, BTNode<T>* curr, BTNode<T>* parentNode, int d);
  static void __traversePostorder(ConstBTNodeCallBack<T>& cb, BTNode<T>* curr, BTNode<T>* parentNode, int d);
  static BTNode<T>* __insert(int key, T*& data, BTNode<T>* curr, int& d, int& c);
  static bool __isChildrenCountBalance(BTree<T>* tree);
  static bool __isFullOfChildren(BTNode<T>* node);
  static int __getNumberOfDirectChildrenOfNode(BTNode<T>* node);

public:
  BTree() = default;
  BTree(int key, T* data) {
    this->__root = new BTNode<T>(key, data);
    this->__count++;
  };
  BTree(int key, T data) {
    this->__root = new BTNode<T>(key, new T(data));
    this->__count++;
  };

  // Static methods
  static bool isLeaf(const BTNode<T>* node);
  static bool isLeaf(BTNode<T>* node);

  // insertItem
  void insertItem(int key, T* data) {
    int d = 0, c = 0;

    if(this->__root == nullptr) {
      this->__root = this->__insert(key, data, this->__root, d, c);
      this->__count = c;
      return;
    };

    // If children count of tree is balance, add to left.
    if(this->__isChildrenCountBalance(this)) {
      c = this->__leftCount;
      this->__root->left = this->__insert(key, data, this->__root->left, ++d, c);
      this->__leftCount = c;
    } 
    // Add to right.
    else {
      c = this->__rightCount;
      this->__root->right = this->__insert(key, data, this->__root->right, ++d, c);
      this->__rightCount = c;
    };
    
    this->__count = this->__leftCount + this->__rightCount + 1;
    this->__depth = d > this->__depth ? d : this->__depth;
  };

  // traverse
  void traverse(ConstBTNodeCallBack<T>& cb, TraverseType traverseType = Inorder) {
    int d = 0;
    switch(traverseType) {
      case Preorder: {
        this->__traversePreorder(cb, this->__root, this->__root, d);
        break;
      };

      case Postorder: {
        this->__traversePostorder(cb, this->__root, this->__root, d);
        break;
      };

      case Inorder:
      default: {
        this->__traverseInorder(cb, this->__root, this->__root, d);
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
    
    ConstBTNodeCallBack<T> cb = [&](const BTNode<T>* node,  BTNode<T>* parent, int depth) {
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
      else if(node == parent->left) {
        N = maxOutputLength - output[index].size() - 1;
        
        if(output[index] == "") N = N < 0 ? 0 : N;
        else N = N < 0 ? 1 : N;

        subOutput = std::string(N, ' ');
        subOutput += keyStr;
        output[index] += subOutput;

        maxOutputLength = output[index].size() > maxOutputLength ? output[index].size() : maxOutputLength;
      }
      // Right
      else if(node == parent->right) {
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
bool BTree<T>::isLeaf(const BTNode<T>* node) {
  return (node->left == nullptr) && (node->right == nullptr);
};

template<class T>
bool BTree<T>::isLeaf(BTNode<T>* node) {
  return (node->left == nullptr) && (node->right == nullptr);
};

template<class T>
bool BTree<T>::__isChildrenCountBalance(BTree<T>* tree) {
  return (tree->__leftCount == tree->__rightCount);
};

template<class T>
int BTree<T>::__getNumberOfDirectChildrenOfNode(BTNode<T>* node) {
  int c = node->left != nullptr ? 1 : 0;
  c += (node->right != nullptr ? 1 : 0);
  return c;
};

template<class T>
bool BTree<T>::__isFullOfChildren(BTNode<T>* node) {
  return (node->left != nullptr) && (node->right != nullptr);
};

template<class T>
void BTree<T>::__traverseInorder(
  ConstBTNodeCallBack<T>& cb,
  BTNode<T>* curr,
  BTNode<T>* parentNode,
  int d
) {
  if(curr == nullptr) return;

  if(curr->left != nullptr) {
    BTree<T>::__traverseInorder(cb, curr->left, curr, d + 1);
  };

  // Execute callback
  cb(curr, parentNode, d);

  if(curr->right != nullptr) {
    BTree<T>::__traverseInorder(cb, curr->right, curr, d + 1);
  };
};

template<class T>
void BTree<T>::__traversePreorder(
  ConstBTNodeCallBack<T>& cb,
  BTNode<T>* curr,
  BTNode<T>* parentNode,
  int d
) {
  if(curr == nullptr) return;

  // Execute callback
  cb(curr, parentNode, d);

  if(curr->left != nullptr) {
    BTree<T>::__traversePreorder(cb, curr->left, curr, d + 1);
  };

  if(curr->right != nullptr) {
    BTree<T>::__traversePreorder(cb, curr->right, curr, d + 1);
  };
};

template<class T>
void BTree<T>::__traversePostorder(
  ConstBTNodeCallBack<T>& cb,
  BTNode<T>* curr,
  BTNode<T>* parentNode,
  int d
) {
  if(curr == nullptr) return;

  if(curr->left != nullptr) {
    BTree<T>::__traversePostorder(cb, curr->left, curr, d + 1);
  };

  if(curr->right != nullptr) {
    BTree<T>::__traversePostorder(cb, curr->right, curr, d + 1);
  };

  // Execute callback
  cb(curr, parentNode, d);
};

template<class T>
BTNode<T>* BTree<T>::__insert(int key, T*& data, BTNode<T>* curr, int& d, int& c) {
  try {
    if(curr == nullptr) {
      c++;
      return new BTNode<T>(key, data);
    };
    if(curr->key == key) throw std::runtime_error("Cannot add this Node, because this key is exist before!!!");

    // Add to left
    if(curr->left == nullptr) {
      curr->left = BTree<T>::__insert(key, data, curr->left, ++d, c);
      return curr;
    } 
    // Add to right
    else if(curr->right == nullptr) {
      curr->right = BTree<T>::__insert(key, data, curr->right, ++d, c);
      return curr;
    };

    // Traverse
    if(BTree<T>::__isFullOfChildren(curr)) {
      curr->left = BTree<T>::__insert(key, data, curr->left, ++d, c);
    } else {
      curr->right = BTree<T>::__insert(key, data, curr->right, ++d, c);
    };

    return curr;
  } catch(const std::exception& e) {
    std::cout << "Insert Error: ";
    std::cerr << e.what();
    return nullptr;
  };
};

#endif // BINARY_TREE_H_INCLUDED
