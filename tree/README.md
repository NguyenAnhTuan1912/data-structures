# Tree

## Concept
__[INSERT IMAGE HERE]__
Like a real tree, but tree in computer science context is flipped down. The highest node links to numerous nodes, then chilren of this node links to other nodes. Node in tree has many names, depend on its position in tree:
- __Root Node__: is a highest node in tree, it locate at `depth = 0` and has no parent.
- __Parent/Inner/Internal/Branch Node__: is a node that locate inside a tree, has parent and children.
- __Leaf/Outer/External/Terminal Node__: is a node that locate in top of tree (from bottom to top), has parent and no children.

There are many types of tree, each tree has specific implementation and meaning:
- __Binary Tree__: its Node only has 1-2 children. No rules when a Node is added and doen't have search operation. Delete operation is very expensive when compare with Binary Search Tree.
- __Binary Search Tree__: its Node only has 2 children. There are 2 rules when add a Node to tree: If key of this Node is __greater than__ current Node, then move to __right__; If key of this Node is __less than__ current node, then move to __left__. Because of rules of addition operation, we can implement search operation and delete operation easier.
- Ternary Tree__: like Binary Tree, but its Node only has 1-3 chilren.
- __Ternary Search Tree__: like BST, but its Node only has 1-3 chilren.
- __N-nary__ and __N-nary Search Tree__: you can understand now. In my opinion, it like a type of __graph__.

Balance a Binary Search Tree (Binary Tree balances itself) is important task, for better performance, we need to balance BST. So there are some type of Binary Search Tree:
- __AVL Tree__: it has 2 vars to trace the depth of left side and right side, if depth of one side is greater than the other (different between is more than 1), balance the tree.
- __Red-black Tree__: its Node has an extra property to store bits that indicate Node is red or black.
- And so on.

## Examples
### With CPP
1. Example with Binary Tree
   - By __Nguyen Anh Tuan__, [view more](/tree/tuan_cpp/examples/tree_example_01_tuan.cpp)
2. Example with Binary Search Tree
   - By __Nguyen Anh Tuan__, [view more](/tree/tuan_cpp/examples/tree_example_02_tuan.cpp)
3. Example with Ternary Tree
   - By __Nguyen Anh Tuan__, [view more](/tree/tuan_cpp/examples/tree_example_03_tuan.cpp)
- 3. Example with Ternary Search Tree
   - By __Nguyen Anh Tuan__, [view more](/tree/tuan_cpp/examples/tree_example_04_tuan.cpp)

## Exercises
Questions:
1. Build “autocomplete words” feature with Ternary Search Tree.