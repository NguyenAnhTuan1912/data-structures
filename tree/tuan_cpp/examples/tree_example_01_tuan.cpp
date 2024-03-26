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
using ConstBSTNodeCallBack = function<void(const BSTNode<T>*,  BSTNode<T>*, int depth)>;

template<class T>
class BSTree {
private:
  BSTNode<T>* __root = nullptr;
  size_t __count = 0;
  int __depth = 0;
  size_t __leftCount = 0;
  size_t __rightCount = 0;

  // Static methods
  static void __traverseInorder(ConstBSTNodeCallBack<T>& cb, BSTNode<T>* curr, BSTNode<T>* parentNode, int d);
  static void __traversePreorder(ConstBSTNodeCallBack<T>& cb, BSTNode<T>* curr, BSTNode<T>* parentNode, int d);
  static void __traversePostorder(ConstBSTNodeCallBack<T>& cb, BSTNode<T>* curr, BSTNode<T>* parentNode, int d);
  static BSTNode<T>* __insert(int key, T*& data, BSTNode<T>* curr, int& d, int& c);
  static bool __isChildrenCountBalance(BSTree<T>* tree);
  static bool __isFullOfChildren(BSTNode<T>* node);
  static int __getNumberOfDirectChildrenOfNode(BSTNode<T>* node);

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
  static bool isLeaf(const BSTNode<T>* node);
  static bool isLeaf(BSTNode<T>* node);

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
  void traverse(ConstBSTNodeCallBack<T>& cb, TreeTraverseType TreeTraverseType = Inorder) {
    int d = 0;
    switch(TreeTraverseType) {
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
    vector<string> output((D + 1) * 2 - 1);
    
    ConstBSTNodeCallBack<T> cb = [&](const BSTNode<T>* node,  BSTNode<T>* parent, int depth) {
      int index = depth * 2, M = 0, N = 0;
      string dashes = "", spaces = "", subOutput = "", keyStr = to_string(node->key);
      
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
            N = maxOutputLength - output[index + 1].size() - (keyStr.size());
            N = N < 0 ? 0 : N;
            M = keyStr.size() + 1;
          };

          dashes = string(N, ' ');
          dashes += string(M, '-');

          output[index + 1] += dashes;

          maxOutputLength = output[index + 1].size() > maxOutputLength ? output[index + 1].size() : maxOutputLength;
        }
      }
      // Left
      else if(node == parent->left) {
        N = maxOutputLength - output[index].size() - 1;
        
        if(output[index] == "") N = N < 0 ? 0 : N;
        else N = N < 0 ? 1 : N;

        subOutput = string(N, ' ');
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

        subOutput = string(N, ' ');
        subOutput += keyStr;

        output[index] += subOutput;

        maxOutputLength = output[index].size() > maxOutputLength ? output[index].size() : maxOutputLength;
      };
    };

    this->traverse(cb, Inorder);

    // Last update dashes for right child of root
    string rightKey = to_string(this->__root->right->key);

    int M = output[2].size() - output[1].size() - (rightKey.size() - 1);

    if(M > 0) {
      output[1] += string(M, '-');
      // Add more space
      output[0] = string(M / 2, ' ') + output[0];
    }

    typename vector<string>::iterator itr = output.begin();

    while(itr != output.end()) {
      cout << *itr << endl;
      itr++;
    };
  };
};

// Define static method
template<class T>
bool BSTree<T>::isLeaf(const BSTNode<T>* node) {
  return (node->left == nullptr) && (node->right == nullptr);
};

template<class T>
bool BSTree<T>::isLeaf(BSTNode<T>* node) {
  return (node->left == nullptr) && (node->right == nullptr);
};

template<class T>
bool BSTree<T>::__isChildrenCountBalance(BSTree<T>* tree) {
  return (tree->__leftCount == tree->__rightCount);
};

template<class T>
int BSTree<T>::__getNumberOfDirectChildrenOfNode(BSTNode<T>* node) {
  int c = node->left != nullptr ? 1 : 0;
  c += (node->right != nullptr ? 1 : 0);
  return c;
};

template<class T>
bool BSTree<T>::__isFullOfChildren(BSTNode<T>* node) {
  return (node->left != nullptr) && (node->right != nullptr);
};

template<class T>
void BSTree<T>::__traverseInorder(
  ConstBSTNodeCallBack<T>& cb,
  BSTNode<T>* curr,
  BSTNode<T>* parentNode,
  int d
) {
  if(curr == nullptr) return;

  if(curr->left != nullptr) {
    __traverseInorder(cb, curr->left, curr, d + 1);
  };

  // Execute callback
  cb(curr, parentNode, d);

  if(curr->right != nullptr) {
    __traverseInorder(cb, curr->right, curr, d + 1);
  };
};

template<class T>
void BSTree<T>::__traversePreorder(
  ConstBSTNodeCallBack<T>& cb,
  BSTNode<T>* curr,
  BSTNode<T>* parentNode,
  int d
) {
  if(curr == nullptr) return;

  // Execute callback
  cb(curr, parentNode, d);

  if(curr->left != nullptr) {
    __traversePreorder(cb, curr->left, curr, d + 1);
  };

  if(curr->right != nullptr) {
    __traversePreorder(cb, curr->right, curr, d + 1);
  };
};

template<class T>
void BSTree<T>::__traversePostorder(
  ConstBSTNodeCallBack<T>& cb,
  BSTNode<T>* curr,
  BSTNode<T>* parentNode,
  int d
) {
  if(curr == nullptr) return;

  if(curr->left != nullptr) {
    __traversePostorder(cb, curr->left, curr, d + 1);
  };

  if(curr->right != nullptr) {
    __traversePostorder(cb, curr->right, curr, d + 1);
  };

  // Execute callback
  cb(curr, parentNode, d);
};

template<class T>
BSTNode<T>* BSTree<T>::__insert(int key, T*& data, BSTNode<T>* curr, int& d, int& c) {
  try {
    if(curr == nullptr) {
      c++;
      return new BSTNode<T>(key, data);
    };
    if(curr->key == key) throw runtime_error("Cannot add this Node, because this key is exist before!!!");

    // Add to left
    if(curr->left == nullptr) {
      curr->left = BSTree<T>::__insert(key, data, curr->left, ++d, c);
      return curr;
    } 
    // Add to right
    else if(curr->right == nullptr) {
      curr->right = BSTree<T>::__insert(key, data, curr->right, ++d, c);
      return curr;
    };

    // Traverse
    if(BSTree<T>::__isFullOfChildren(curr)) {
      curr->left = BSTree<T>::__insert(key, data, curr->left, ++d, c);
    } else {
      curr->right = BSTree<T>::__insert(key, data, curr->right, ++d, c);
    };

    return curr;
  } catch(const exception& e) {
    cout << "Insert Error: ";
    cerr << e.what();
    return nullptr;
  };
};

int main() {
  // Lambda
  ConstBSTNodeCallBack<int> printValue = [](const BSTNode<int>* node, BSTNode<int>* parent, int depth) {
    cout << *(node->data) << " ";
  };

  // Declare binary search tree
  BSTree<int> tree;

  tree.insertItem(5, new int(5));
  tree.insertItem(3, new int(3));
  tree.insertItem(9, new int(9));
  tree.insertItem(8, new int(8));
  tree.insertItem(10, new int(10));
  tree.insertItem(2, new int(2));
  tree.insertItem(7, new int(7));

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
  tree.insertItem(100, new int(100));
  tree.insertItem(10, new int(10));
  tree.insertItem(102, new int(102));
  tree.insertItem(5, new int(5));
  tree.insertItem(9, new int(9));

  // Print
  cout << "Print tree: \n";
  tree.print();
  cout << endl;

  return 0;
};
