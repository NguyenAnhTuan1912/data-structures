# Queue

## Concept
__[INSERT IMAGE HERE]__
Imagine in a cinema, there are many queue of people are waiting for buying ticket. Only person in front of queue is able to buy ticket (he/she can buy pop-corn, drinks, ...), he/she will move out the queue to locate his/her seat, this action is called "__dequeue__". But the queue is full, other people must be way the front move out the queue, then they can move to queue, this action is called "__enqueue__". You  can see, the front person will be served first, different with __stack__.

Queue operates like this, of course, it is more functions when we implement in our program. When a data has `T` type is __enqueued__, it must be allocated in heap memory, then a queue item will be initialized and points to that memory. The item will be __enqueued__ to queue. Now we have a queue that contains one item, this item points to a data `T` in heap memory.

Different with stack, queue is FIFO (First In First Out) or LILO (Last In Last Out) scheme, allow allow us to schedule taskes to do later.

## Examples
1. Example of Queue
   - By __Nguyen Anh Tuan__, [view more](/queue/tuan_cpp/examples/queue_example_01_tuan.cpp)

## Exercises
\*Note: Queue always has a clear (a method is used to clear all nodes), default constructor, arguments constructor and destructor (if the language supports).
Create some classes:
- Drink and Food have name, price. Drink has private property is type = “drink” and type = “food” for Food.

Questions:
1. Create a generic Queue has dequeue, enqueue, getSize, isEmpty. Initializer 2 queue of Drinks and Foods (each queue has arbitrary numbers of items). Perform all methods of Stack.
2. Create a generic Queue to control the sequence of processes (callbacks, instances of class are recommended). Add perform method to perform the first Node’s task, then dequeue.
