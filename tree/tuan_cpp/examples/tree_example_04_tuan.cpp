/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Ternary Search Tree

  Note:
  Có một điều khá thú vị là cách là implement Ternary Search Tree sẽ khác hoàn toàn so với
  Binary Tree, Binary Search Tree và Ternary Tree.

  Thay vì một Node cần key-value (data) thì giờ mình chỉ cần có data (char) là được.
  Bởi vì một từ khi được thêm vào trong cây thì các ký tự của từ sẽ được phân tách ra và
  lưu lại thành từng Node.

  Có vẻ như là Ternary Search Tree "chỉ" có thể dùng với string.

  Ấn build để nó hiện ra từng message của lỗi.
  Để thực thi và xem các ví dụ thì comment những chỗ code lỗi lại.
*/

#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include <exception>
#include <string>

using namespace std;

enum TraverseType {
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
  : data{data}, left{move(left)}, mid{move(mid)}, right{move(right)} {};
};

using ConstTSTNodeCallBack = function<void(const TSTNode*, int depth)>;

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
  TSTree(string data) {
    this->insertItem(data);
  };
  
  // Static methods
  static bool isLeaf(const TSTNode* node);
  static bool isLeaf(TSTNode* node);

  // insertItem
  void insertItem(string word) {
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
  void deleteItem(string word) {
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
  bool searchItem(string word) {
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
  void traverse(ConstTSTNodeCallBack& cb, TraverseType traverseType = Inorder) {
    int d = 0;
    switch(traverseType) {
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
    __traverseInorder(cb, curr->left, d + 1);
  };

  // Execute callback
  cb(curr, d);

  if(curr->mid != nullptr) {
    __traversePreorder(cb, curr->mid, d + 1);
  };

  if(curr->right != nullptr) {
    __traverseInorder(cb, curr->right, d + 1);
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
    __traversePreorder(cb, curr->left, d + 1);
  };

  if(curr->mid != nullptr) {
    __traversePreorder(cb, curr->mid, d + 1);
  };

  if(curr->right != nullptr) {
    __traversePreorder(cb, curr->right, d + 1);
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
    __traversePostorder(cb, curr->left, d + 1);
  };

  if(curr->mid != nullptr) {
    __traversePreorder(cb, curr->mid, d + 1);
  };

  if(curr->right != nullptr) {
    __traversePostorder(cb, curr->right, d + 1);
  };

  // Execute callback
  cb(curr, d);
};

void printSearchResult(TSTree& tree, string query) {
  cout << "Query: " << query << endl;
  if(tree.searchItem(query)) 
    cout << "Found\n";
  else cout << "Not found\n";
};

int main() {
  // Lambda
  ConstTSTNodeCallBack printNodeData = [](const TSTNode* node, int depth) {
    cout << node->data << " ";
  };

  // Declare Ternary Tree
  TSTree tree;
  tree.insertItem("apple");
  tree.insertItem("at");
  tree.insertItem("ananas");
  tree.insertItem("be");

   // Traverse
  cout << "Traverse tree (Inorder)\n";
  tree.traverse(printNodeData);
  cout << endl;
  cout << "Traverse tree (Preorder)\n";
  tree.traverse(printNodeData, Preorder);
  cout << endl;
  cout << "Traverse tree (Postorder)\n";
  tree.traverse(printNodeData, Postorder);
  cout << endl; 

  // Get depth
  cout << "Depth of tree: " << tree.getDepth() << endl;

  printSearchResult(tree, "apple");
  printSearchResult(tree, "be");
  printSearchResult(tree, "ananas"); 
  printSearchResult(tree, "");

  // Delete "ananas"
  cout << "Delete \"ananas\": " << endl;
  tree.deleteItem("ananas");

  printSearchResult(tree, "ananas");

  return 0;
};
