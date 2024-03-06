/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Binary Search Tree

  Ấn build để nó hiện ra từng message của lỗi.
  Để thực thi và xem các ví dụ thì comment những chỗ code lỗi lại.
*/

#include <iostream>
#include <exception>

using namespace std;

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
class BSTree {
private:
  BSTNode<T>* __root = nullptr;
  size_t __count = 0;
  int __depth = 0;

  static BSTNode<T>* __search(int key, BSTNode<T>* curr = nullptr);

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
  static bool isLeaf(BSTNode<T>* curr);

  // insertItem
  void insertItem(int key, T* data, BSTNode<T>* curr = nullptr) {
    try {
      if(curr == nullptr) curr = this->__root;
      if(curr->key == key) throw runtime_error("Cannot add this Node, because this key is exist before!!!");

      bool isLeft = (key < curr->key);

      // Assign to left
      if(isLeft && curr->left == nullptr) {
        curr->left = new BSTNode<T>(key, data);
        this->__count++;
        return;
      };

      // Assign to right
      if(!isLeft && curr->right == nullptr) {
        curr->right = new BSTNode<T>(key, data);
        this->__count++;
        return;
      };

      // Pass through left
      if(isLeft) {
        this->insertItem(key, data, curr->left);
        return;
      };

      this->insertItem(key, data, curr->right);
    } catch(const exception& e) {
      cout << "Insert Error: ";
      cerr << e.what();
    };
  };

  // deleteItem
  BSTNode<T>* deleteItem(int key, BSTNode<T>* curr = nullptr) {
    if(this->__root == nullptr) return nullptr;
    if(curr == nullptr) curr = this->__root;

    // Search
    if (key < curr->key) {
      if(curr->left == nullptr) return nullptr;
      curr->left = this->deleteItem(key, curr->left);
      return curr;
    } else if(key > curr->key) {
      if(curr->right == nullptr) return nullptr;
      curr->right = this->deleteItem(key, curr->right);
      return curr;
    };

    // Match
    // If Node has one child
    // Left
    if(curr->left == nullptr) {
      BSTNode<T>* temp = curr;
      temp = curr->right;
      delete curr;
      this->__count--;
      return curr;
    }
    // Right
    else if(curr->right == nullptr) {
      BSTNode<T>* temp = curr;
      temp = curr->left;
      delete curr;
      this->__count--;
      return curr;
    }
    // If Node has both
    else {
      // The first choice is always left
      BSTNode<T>* temp = curr->left;
      BSTNode<T>* prev = nullptr;

      // And remains are right.
      while(temp->right != nullptr) {
        prev = temp;
        temp = temp->right;
      };

      if(temp->right == nullptr && temp->left != nullptr) {
        prev->right = temp->left;
        temp->left = prev;
        temp->right = curr->right;

        curr->left = nullptr;
        curr->right = nullptr;
        delete curr;
        this->__count--;

        return temp;
      };

      if(prev == nullptr) {
        temp->right = curr->right;
      } else {
        temp->left = curr->left;
        temp->right = curr->right;
        prev->right = nullptr;
      }

      curr->left = nullptr;
      curr->right = nullptr;
      delete curr;
      this->__count--;
      return temp;
    };
  };

  // searchItem
  T* searchItem(int key, BSTNode<T>* curr = nullptr) {
    if(curr == nullptr) curr = this->__root;
    BSTNode<T>* result = this->__search(key, curr);
    if(result == nullptr) return nullptr;
    return result->data;
  };

  // travel
  void travel() {

  };

  int getDepth() {
    return this->__depth;
  };
};

// Define static method
template<class T>
bool BSTree<T>::isLeaf(BSTNode<T>* curr) {
  return (curr->left == nullptr) && (curr->right == nullptr);
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

int main() {
  // Declare binary search tree
  BSTree<int> tree = BSTree<int>(26, new int(5));

  tree.insertItem(29, new int(3));
  tree.insertItem(20, new int(9));
  tree.insertItem(31, new int(8));
  tree.insertItem(12, new int(10));
  tree.insertItem(3, new int(2));

  int* ptr = tree.searchItem(12);

  cout << "Data: " << *ptr << endl;

  // Delete key 9
  tree.deleteItem(9);

  ptr = tree.searchItem(9);
  cout << "Data: " << (ptr == nullptr ? 0 : *ptr) << endl;

  return 0;
};
