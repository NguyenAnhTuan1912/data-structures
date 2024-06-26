/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của Ternary Search Tree, mọi thay đổi về cấu trúc
  của Ternary Search Tree sẽ được thay đổi trong này.
*/

#ifndef TERNARY_SEARCH_TREE_H_INCLUDED
#define TERNARY_SEARCH_TREE_H_INCLUDED

#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include <exception>
#include <string>

enum TreeTraverseType {
  Empty,
  Inorder,
  Preorder,
  Postorder
};

class TSTNode {
public:
  char data;
  bool isEnd = false;
  TSTNode* left = nullptr;
  TSTNode* mid = nullptr;
  TSTNode* right = nullptr;

  TSTNode() = default;
  TSTNode(char data): data{data} {};
  TSTNode(char data, TSTNode* left, TSTNode* mid, TSTNode* right)
  : data{data}, left{std::move(left)}, mid{std::move(mid)}, right{std::move(right)} {};
};

using ConstTSTNodeCallBack = std::function<void(const TSTNode*, int depth)>;

class TSTree {
private:
  TSTNode* __root = nullptr;
  size_t __count = 0;
  int __depth = 0;

  // Static methods
  static void __traverseInorder(ConstTSTNodeCallBack& cb, TSTNode* curr, int d);
  static void __traversePreorder(ConstTSTNodeCallBack& cb, TSTNode* curr, int d);
  static void __traversePostorder(ConstTSTNodeCallBack& cb, TSTNode* curr, int d); 

public:
  TSTree() = default;
  TSTree(std::string data) {
    this->insertItem(data);
  };

  // Static methods
  static bool isLeaf(const TSTNode* node);
  static bool isLeaf(TSTNode* node);
  
  // insertItem
  void insertItem(std::string word) {
    if(word.empty()) return;

    TSTNode *ptr = this->__root, *prev = this->__root;
    int index = 0, N = word.size();

    // Finding
    while(ptr != nullptr) {
      if(word[index] < ptr->data) {
        prev = ptr;
        ptr = ptr->left;
      }
      else if(word[index] > ptr->data) {
        prev = ptr;
        ptr = ptr->right;
      }
      // That means this key is exist.
      else if(word[index] == ptr->data) {
        // If all characters of word are in TST before, stop the insertion.
        if(index == N) return;
        // If last character of word is equal to ptr->data
        if(word[N - 1] == ptr->data) {
          ptr->isEnd = true;
          return;
        };
        // Increase index by 1 to check the next char.
        prev = ptr;
        ptr = ptr->mid;
        index++;
      };
    };

    // If ptr is nullptr and the execution reaches here, that mean the remain
    // characters are new and need to be added.
    // Add remain characters to tree.
    ptr = new TSTNode();

    if(this->__root == nullptr) {
      this->__root = new TSTNode(word[index]);
      ptr = this->__root;
    } else if(word[index] < prev->data) {
      prev->left = ptr;
      ptr->data = word[index];
    } else if(word[index] > prev->data) {
      prev->right = ptr;
      ptr->data = word[index];
    } else if(word[index] == prev->data) {
      prev->mid = ptr;
      ptr->data = word[index];
    };

    index++;

    while(index < N) {
      ptr->mid = new TSTNode(word[index]);
      prev = ptr;
      ptr = ptr->mid;
      index++;
      this->__depth++;
    };

    // Is end
    ptr->isEnd = true;
  };

  // deleteItem
  void deleteItem(std::string word) {
    if(word.empty()) return;

    TSTNode *ptr = this->__root, *prev = this->__root, *firstMatchMid = nullptr;
    int index = 0, N = word.size();

    // Find the first match mid node and last.
    while(ptr != nullptr) {
      if(word[index] < ptr->data) {
        firstMatchMid = nullptr;
        prev = ptr;
        ptr = ptr->left;
      } else if(word[index] > ptr->data) {
        firstMatchMid = nullptr;
        prev = ptr;
        ptr = ptr->right;
      } else if(word[index] == ptr->data) {
        firstMatchMid = ptr;
        
        if(prev->left == ptr) {
          prev->left = nullptr;
        } else if(prev->right == ptr) {
          prev->right = nullptr;
        };
        
        // Iterate to last char
        while(ptr != nullptr && word[index] == ptr->data) {
          ptr = ptr->mid;
          index++;
        };
      };
    };

    if(firstMatchMid == nullptr) return;

    TSTNode* temp;

    while(firstMatchMid != nullptr) {
      temp = firstMatchMid;
      firstMatchMid = firstMatchMid->mid;
      delete(temp);
      this->__depth--;
    };
  };

  // searchItem
  bool searchItem(std::string word) {
    if(word.empty()) return false;

    TSTNode* ptr = this->__root;
    int index = 0, N = word.size();

    while(ptr != nullptr) {
      if(word[index] < ptr->data) {
        ptr = ptr->left;
      } else if(word[index] > ptr->data) {
        ptr = ptr->right;
      } else if(word[index] == ptr->data) {
        if(index == N - 1) return true;
        ptr = ptr->mid;
        index++;
      }; 
    };

    return false;
  };

  // traverse
  void traverse(ConstTSTNodeCallBack& cb, TreeTraverseType TreeTraverseType = Inorder) {
    int d = 0;
    switch(TreeTraverseType) {
      case Preorder: {
        this->__traversePreorder(cb, this->__root, d);
        break;
      };

      case Postorder: {
        this->__traversePostorder(cb, this->__root, d);
        break;
      };

      case Inorder:
      default: {
        this->__traverseInorder(cb, this->__root, d);
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
bool TSTree::isLeaf(const TSTNode* node) {
  return (node->left == nullptr) && (node->right == nullptr) && (node->mid == nullptr);
};

bool TSTree::isLeaf(TSTNode* node) {
  return (node->left == nullptr) && (node->right == nullptr) && (node->mid == nullptr);
};

/*
  Left -> Root -> Mid -> Right
*/
void TSTree::__traverseInorder(
  ConstTSTNodeCallBack& cb,
  TSTNode* curr,
  int d
) {
  if(curr == nullptr) return;

  if(curr->left != nullptr) {
    TSTree::__traverseInorder(cb, curr->left, d + 1);
  };

  // Execute callback
  cb(curr, d);

  if(curr->mid != nullptr) {
    TSTree::__traversePreorder(cb, curr->mid, d + 1);
  };

  if(curr->right != nullptr) {
    TSTree::__traverseInorder(cb, curr->right, d + 1);
  };
};

/*
  Root -> Left -> Mid -> Right
*/
void TSTree::__traversePreorder(
  ConstTSTNodeCallBack& cb,
  TSTNode* curr,
  int d
) {
  if(curr == nullptr) return;

  // Execute callback
  cb(curr, d);

  if(curr->left != nullptr) {
    TSTree::__traversePreorder(cb, curr->left, d + 1);
  };

  if(curr->mid != nullptr) {
    TSTree::__traversePreorder(cb, curr->mid, d + 1);
  };

  if(curr->right != nullptr) {
    TSTree::__traversePreorder(cb, curr->right, d + 1);
  };
};

/*
  Left -> Mid -> Right -> Root
*/
void TSTree::__traversePostorder(
  ConstTSTNodeCallBack& cb,
  TSTNode* curr,
  int d
) {
  if(curr == nullptr) return;

  if(curr->left != nullptr) {
    TSTree::__traversePostorder(cb, curr->left, d + 1);
  };

  if(curr->mid != nullptr) {
    TSTree::__traversePreorder(cb, curr->mid, d + 1);
  };

  if(curr->right != nullptr) {
    TSTree::__traversePostorder(cb, curr->right, d + 1);
  };

  // Execute callback
  cb(curr, d);
};

#endif // TERNARY_SEARCH_TREE_H_INCLUDED
