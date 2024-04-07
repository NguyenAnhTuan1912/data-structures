# Linked List

## Concept
__[INSERT IMAGE HERE]__
Linked List similars with Array, but different with Array, Linked List is more flexible. It's a chain contains numerous Node that links to another Node (or other Nodes). Node contains 2 parts: __Data__ and __Link__, __Data__ points or refers to memory that contains data; __Link__ points or refers to Node(s).

There 3 types of Linked List (I implement 2 of them), difference between them is in __Link__ part -> the implementation between is distinct:
- Singly Linked List: its node only link to one node (called "next node"), contains a __head__ and __tail__ node and 2 vars points or refers to them.
- Doubly Linked List: its node has 2 links, previous link points or refers to previous node and next link points or refers to next node.
- Multiply Linked List: its node has multiple links (maybe an array, set, ...). In my opinion, this type of linked list is a type of __graph__.

Linked List is more flexible than Array, because of "Add-Remove-Delete" operations. For example, if an array add an item, it can add to
- First and Last: the array just add to first or last of array.
- Arbitrary Index: the array must be re-size itself to add the new item.

And when an array deletes an item, it resizes and delete the memory of item. 

With same operations, Linked List is easier. Add new item to random position, it will locate node at this position, then it performs re-point to new Node, faster, right? As well as delete operation, locate node at this position, re-point and delete data in memory. For more information, please see all of the example below.

## Examples
### With CPP
1. Example with Singly Linked List
   - By __Nguyen Anh Tuan__, [view more](/linked_list/tuan_cpp/examples/linkedlist_example_01_tuan.cpp)
2. Example with Doubly Linked List
   - By __Nguyen Anh Tuan__, [view more](/linked_list/tuan_cpp/examples/linkedlist_example_02_tuan.cpp)
3. Example with Circular Linked List
   - By __Nguyen Anh Tuan__, [view more](/linked_list/tuan_cpp/examples/linkedlist_example_03_tuan.cpp)

### With TS
1. Example with Singly Linked List
   - By __Tu Nhat Phuong__, [view more](/linked_list/phuong_ts/examples/linkedlist_example_01_phuong.ts)
2. Example with Doubly Linked List
   - By __Tu Nhat Phuong__, [view more](/linked_list/phuong_ts/examples/linkedlist_example_02_phuong.ts)

### With RS
1. Example with Singly Linked List
   - By __Luong Van Phap__, [view more](/linked_list/phap_rust/examples/singly_linked_list)

## Exercises
*Note: LinkedList always has default constructor and arguments constructor.
1. Create a linked list class whose Nodes have a data part is integer type and it has a print method. Initialize 5 linked list instances and print their element’s data to console.
2. Create a linked list class whose Nodes have a data part is Point (Point is a class that has 2 private properties indicating for coordinate) and it has a print method. Initialize a linked list instance and print its element’s data to console.
3. Create a linked list class whose Nodes have a data part is integer type and it has print, insertLast, insertFirst methods. Declare a linked list instance, then add numbers of random int numbers and print its element’s data to console.
4. Create a linked list class similar to question 3, but Its Nodes’ data part is Point type. Initialize a linked list instance, then add numbers of random Points and print its element’s data to console.
5. Create a generic linked list class has print, insertLast, insertFirst methods. Initialize a number type linked list instance and add numbers of random Points to a declared Point type linked list instance that are generated from generic linked list class and print their element’s data to console.
6. Create an int (number) linked list class has print, insertLast, insertFirst, insertAt. Initialize a linked list instance to perform all of its methods.

Note: *print, insertLast, insertFirst and insertAt methods are required in LinkedList now.*

7. Create an int (number) linked list class has required methods, removeLast, removeFirst and removeAt. Declare a linked list instance and add numbers of random numbers and perform all of its methods.
8. Create an int (number) linked list class has getAt method. Initialize a linked list and perform getAt method.
9. Create an int (number) linked list class has insertByOrder method. Declare a linked list and add numbers of random numbers with insertByOrder.
10. Create an int (number) linked list class has all methods that are mentioned in every previous question. Declare a doubly linked list and perform all of its methods.

Note: *removeLast, removeFirst, removeAt, getAt and insertByOrder methods are required in LinkedList now too.*

11. Create a generic linked list class, a Point class with x and y properties and a Person class with name, age properties. Use generic linked list class to declare 2 linked lists 
    - Point Linked List: add 2 points with insertFirst, 2 points with insertLast, 2 points with insertAt and 2 points with insertByOrder. Get arbitrary 4 points with getAt. Then remove tail, remove head, remove a random point.
    - Person Linked List: add 2 people with insertFirst, 2 people with insertLast, 2 people with insertAt and 2 people with insertByOrder. Get arbitrary 4 people with getAt. Then remove tail, remove head, remove 2 random people.
12. Create a generic doubly linked list class has the same methods as the generic singly linked list class in Question 11 and 2 two classes Point and Person. Use generic doubly linked list class to declare 2 doubly linked lists and do tasks like Question 11.