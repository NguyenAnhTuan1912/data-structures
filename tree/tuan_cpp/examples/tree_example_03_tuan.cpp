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
  void traverse(ConstTTNodeCallBack<T>& cb, TraverseType traverseType = Inorder) {
    int d = 0;
    cout << "Number of Nodes: " << this->__count << endl;
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
TTNode<T>* TTree<T>::__insert(int key, T*& data, TTNode<T>* curr, int& d, int& c) {
  try {
    if(curr == nullptr) {
      c++;
      return new TTNode<T>(key, data);
    };
    if(curr->key == key) throw runtime_error("Cannot add this Node, because this key is exist before!!!");
    
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
      return curr;
    }
    // To mid
    else if(nChildrenOfLeftChild > nChildrenOfMidChild) {
      curr->mid = TTree<T>::__insert(key, data, curr->mid, ++d, c);
      return curr;
    }
    // To right
    else {
      curr->right = TTree<T>::__insert(key, data, curr->right, ++d, c);
      return curr;
    };

    return nullptr;
  } catch(const exception& e) {
    cout << "Insert Error: ";
    cerr << e.what();
    return nullptr;
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
  TTree<int> tree02;

  // Insert
  tree.insertItem(30, new string("Hello"));
  tree.insertItem(10, new string("Day"));
  tree.insertItem(15, new string("La"));
  tree.insertItem(20, new string("Cay Tam Phan"));

  tree02.insertItem(1, new int(1));
  tree02.insertItem(2, new int(2));
  tree02.insertItem(3, new int(3));
  tree02.insertItem(4, new int(4));
  
  tree02.insertItem(5, new int(5));
  tree02.insertItem(6, new int(6));
  tree02.insertItem(7, new int(7));
  tree02.insertItem(8, new int(8));
  tree02.insertItem(9, new int(9));
  tree02.insertItem(10, new int(10));
  tree02.insertItem(11, new int(11)); 
  tree02.insertItem(12, new int(12));
  tree02.insertItem(13, new int(13));
  tree02.insertItem(14, new int(14));
  
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
