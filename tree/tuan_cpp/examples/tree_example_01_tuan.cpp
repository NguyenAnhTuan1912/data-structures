/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Binary Search Tree

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
using ConstBSTNodeCallBack = function<void(const BSTNode<T>*m, int parentKey, int depth)>;

template<class T>
class BSTree {
private:
  BSTNode<T>* __root = nullptr;
  size_t __count = 0;
  int __depth = 0;

  static BSTNode<T>* __search(int key, BSTNode<T>* curr = nullptr);
  static void __traverseInorder(ConstBSTNodeCallBack<T>& cb, BSTNode<T>* curr, int parentKey, int d);
  static void __traversePreorder(ConstBSTNodeCallBack<T>& cb, BSTNode<T>* curr, int parentKey, int d);
  static void __traversePostorder(ConstBSTNodeCallBack<T>& cb, BSTNode<T>* curr, int parentKey, int d);
  static void __insert(int key, T*& data, BSTNode<T>* curr, int& d, int& c);

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
    this->__insert(key, data, this->__root, d, c);
    this->__count = c;
    if(d > this->__depth) this->__depth = d;
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

  // traverse
  void traverse(ConstBSTNodeCallBack<T>& cb, TraverseType traverseType = Inorder) {
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

  // print
  void print() {
    int D = this->__depth, maxOutputLength = 0;
    vector<string> output((D + 1) * 2 - 1);

    ConstBSTNodeCallBack<T> cb = [&](const BSTNode<T>* node, int parentKey, int depth) {
      int index = depth * 2, M = 0, N = 0;
      string dashes = "", spaces = "", subOutput = "", keyStr = to_string(node->key);
      /*
      cout << "Output: " << (output[index]) << endl;
      cout << "Index: " << index << endl;
      cout << "Key: " << keyStr << endl;
      */
      // Root of subtree
      if(!this->isLeaf(node)) {
        // Generate "-" for left child
        if(node->left != nullptr) {
          if(output[index + 1] != "") {
            N = maxOutputLength - output[index + 1].size() - 1;
            M = 2;
          } else {
            N = output[index + 2].size() - 1;
            M = maxOutputLength - N;
            M = M < 2 ? 2 : M;
          };

          dashes = string(N, ' ');
          dashes += string(M, '-');

          output[index + 1] += dashes;

          maxOutputLength = output[index + 1].size() > maxOutputLength ? output[index + 1].size() : maxOutputLength;
        }

        // Add key string
        N = maxOutputLength - output[index].size() - 1;

        subOutput = string(N, ' ');
        subOutput += keyStr;

        output[index] += subOutput;

        maxOutputLength = output[index].size() > maxOutputLength ? output[index].size() : maxOutputLength;

        // Generate "-" for right child
        N = 0, M = 0;
        if(node->right != nullptr) {
          if(output[index + 1] == "") {
            N = maxOutputLength - 1;
            M = to_string(node->right->key).size() + 1;
          } else {
            N = maxOutputLength - output[index + 1].size() - 1;
            N = N < 0 ? 0 : N;
            M = 2;
          };

          // M = maxOutputLength - output[index + 1].size();
          // M = M < 2 ? 2 : M;

          dashes = string(N, ' ');
          dashes += string(M, '-');

          output[index + 1] += dashes;

          maxOutputLength = output[index + 1].size() > maxOutputLength ? output[index + 1].size() : maxOutputLength;
        }
      }
      // Left
      else if(node->key < parentKey) {
        if(output[index] != "") {
          N = maxOutputLength - output[index].size() - 1;
          N = N == 0 ? 1 : N;
        };

        subOutput = string(N, ' ');
        subOutput += keyStr;

        output[index] += subOutput;

        maxOutputLength = output[index].size() > maxOutputLength ? output[index].size() : maxOutputLength;
      }
      // Right
      else if(node->key > parentKey) {
        N = maxOutputLength - 1;

        if(output[index] != "") {
          N = maxOutputLength - output[index].size() - 1;
          // cout << "Key: " << keyStr << endl;
          // cout << "N: " << N << endl;
        };

        subOutput = string(N, ' ');
        subOutput += keyStr;

        output[index] += subOutput;

        maxOutputLength = output[index].size() > maxOutputLength ? output[index].size() : maxOutputLength;
      };
    };

    this->traverse(cb, Inorder);

    typename vector<string>::iterator itr = output.begin();

    while(itr != output.end()) {
      cout << *itr << endl;
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
void BSTree<T>::__traverseInorder(
  ConstBSTNodeCallBack<T>& cb,
  BSTNode<T>* curr,
  int parentKey,
  int d
) {
  if(curr == nullptr) return;

  if(curr->left != nullptr) {
    __traverseInorder(cb, curr->left, curr->key, d + 1);
  };

  // Execute callback
  cb(curr, parentKey, d);

  if(curr->right != nullptr) {
    __traverseInorder(cb, curr->right, curr->key, d + 1);
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
    __traversePreorder(cb, curr->left, curr->key, d + 1);
  };

  if(curr->right != nullptr) {
    __traversePreorder(cb, curr->right, curr->key, d + 1);
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
    __traversePostorder(cb, curr->left, curr->key, d + 1);
  };

  if(curr->right != nullptr) {
    __traversePostorder(cb, curr->right, curr->key, d + 1);
  };

  // Execute callback
  cb(curr, parentKey, d);
};

template<class T>
void BSTree<T>::__insert(int key, T*& data, BSTNode<T>* curr, int& d, int& c) {
  try {
    if(curr == nullptr) {
      d--;
      return;
    }
    if(curr->key == key) throw runtime_error("Cannot add this Node, because this key is exist before!!!");

    bool isLeft = (key < curr->key);

    // Assign to left
    if(isLeft && curr->left == nullptr) {
      curr->left = new BSTNode<T>(key, data);
      c++;
      d++;
      return;
    };

    // Assign to right
    if(!isLeft && curr->right == nullptr) {
      curr->right = new BSTNode<T>(key, data);
      c++;
      d++;
      return;
    };

    // Pass through left
    if(isLeft && curr->left != nullptr) BSTree<T>::__insert(key, data, curr->left, ++d, c);
    else
      if(!isLeft && curr->right != nullptr) BSTree<T>::__insert(key, data, curr->right, ++d, c);

    return;
  } catch(const exception& e) {
    cout << "Insert Error: ";
    cerr << e.what();
  };
};

int main() {
  // Lambda
  ConstBSTNodeCallBack<int> printValue = [](const BSTNode<int>* node, int parentKey, int depth) {
    cout << *(node->data) << " ";
  };

  // Declare binary search tree
  BSTree<int> tree = BSTree<int>(5, new int(5));

  tree.insertItem(3, new int(3));
  tree.insertItem(9, new int(9));
  tree.insertItem(8, new int(8));
  tree.insertItem(10, new int(10));
  tree.insertItem(2, new int(2));
  tree.insertItem(1, new int(1));

  cout << "Depth of tree: " << tree.getDepth() << endl;

  cout << "Traverse tree (Inorder)\n";
  tree.traverse(printValue);
  cout << endl;
  cout << "Traverse tree (Preorder)\n";
  tree.traverse(printValue, Preorder);
  cout << endl;
  cout << "Traverse tree (Postorder)\n";
  tree.traverse(printValue, Postorder);
  cout << endl;

  // Print
  cout << "Print tree: \n";
  tree.print();
  cout << endl;

  cout << endl;
  int* ptr = tree.searchItem(10);
  cout << "Search 10...\n";
  cout << "Data: " << (ptr == nullptr ? 0 : *ptr) << endl;

  // Delete key 9
  cout << "Delete 9\n";
  tree.deleteItem(9);

  ptr = tree.searchItem(9);
  cout << "Search 9...\n";
  cout << "Data: " << (ptr == nullptr ? 0 : *ptr) << endl;
  cout << endl;

  cout << "Traverse tree (Inorder)\n";
  tree.traverse(printValue);
  cout << endl;
  cout << "Traverse tree (Preorder)\n";
  tree.traverse(printValue, Preorder);
  cout << endl;
  cout << "Traverse tree (Postorder)\n";
  tree.traverse(printValue, Postorder);
  cout << endl;

  // Print
  cout << "Print tree: \n";
  tree.print();
  cout << endl;

  tree = BSTree<int>(8, new int(8));

  tree.insertItem(3, new int(3));
  tree.insertItem(2, new int(2));
  tree.insertItem(4, new int(4));
  tree.insertItem(11, new int(11));
  tree.insertItem(10, new int(10));
  tree.insertItem(12, new int(12));
  tree.insertItem(5, new int(5));
  tree.insertItem(9, new int(9));

  // Print
  cout << "Print tree: \n";
  tree.print();
  cout << endl;

  return 0;
};
