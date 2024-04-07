# Stack

## Concept
__[INSERT IMAGE HERE]__
Imagine a stack is like a stack of dishes in a restaurant. When a dish is washed, it will be "stacked" to the top of dishes stack, then more and more dishes will be "stacked", this action is called "__push__". But you can't take the first dish out of the dishes stack, right? So you need to take the last dish first, the top dish, repeat and repeat this action you will take the first dish out, this action is called "__pop__".

And yes, the stack operates similar with things that I memtioned above. When a data has `T` type is __pushed__ to a stack, actually, it will be allocated to heap memory, a stack item will point to this memory and then it will be __pushed__ to stack. Now we have a stack with one item and this item points to a data `T` in heap memory.

Stack is LIFO (Last In First Out) or FILO (First In Last Out) scheme, allow us to schedule taskes to do later.

## Examples
### With CPP
1. Example of Stack
   - By __Nguyen Anh Tuan__, [view more](/stack/tuan_cpp/examples/stack_example_01_tuan.cpp)

### With TS
1. Example of Stack
   - By __Tu Nhat Phuong__, [view more](/stack/phuong_ts/examples/stack_example_01_phuong.ts)

## Exercises
\*Note: Stack always has a clear (a method is used to clear all nodes), default constructor, arguments constructor and destructor (if the language support).

Create some classes:
- Person has name and age.
- Animal has name, age and breed.
- Vehicle has name, color and speed.

Questions:
1. Create a generic Stack has pop, push, getSize, isEmpty and getTop. Initializer 3 stack of People, Animals and Vehicle (each stack has arbitrary numbers of items). Perform all methods of Stack.
2. Create a Stack to control the loop operation in program, recursion; prevent infinite loop.
