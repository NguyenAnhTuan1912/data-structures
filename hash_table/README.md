# Hash Table

## Concept
__[INSERT IMAGE HERE]__
Hash Table is a basic structure of __Map__, __Dictionary__, ... It uses indexing technique to locate and store data. A Hash Table contains numerous __Bucket__, this item contains __key__ and __value__. Hash Table will use an Array or Vector (Dynamic Array) to store buckets. Hash Table has a function named "hash", this will hash the key to and index (hashed index) and locate to this index in array or vector, than create and Bucket to store the key and points to data in heap memory.

The most important concept of Hash Table is hash function, it brings multiple problem we have to solve. If we want to hash a key, we need to know the total of spaces that array or vector allow to store. As I memtioned above, Array or vector inside must be resize itself, see? The size changes, the value of key is different than before (with same key or new key), that thing make hash function isn't pure anymore (very bad). The solution is we need to resize the array or vector reach the nearest prime number with the size of array or vector or something else.

How about hashed index of 2 different keys is equal? There are 2 approaches:
- Open Addressing: jump to next index when slot in this index has data.
- Separate Chaining: array or vector store a list of buckets instead of bucket. If hashed index of a key existed before, add new bucket to list at this position (Recommend this approach).

## Examples
### With CPP
1. Example of Open Addressing
   - By __Nguyen Anh Tuan__, [view more](/hash_table/tuan_cpp/examples/hash_table_example_01_tuan.cpp)
2. Example of Separate Chaining
   - By __Nguyen Anh Tuan__, [view more](/hash_table/tuan_cpp/examples/hash_table_example_02_tuan.cpp)
3. Example of Open Addressing (with string key)
   - By __Nguyen Anh Tuan__, [view more](/hash_table/tuan_cpp/examples/hash_table_example_03_tuan.cpp)

## Exercises
\*Note: HashTable always has a clear (a method is used to clear all nodes), default constructor, arguments constructor and destructor (if the language supports). And key of Bucket in HashTable must be a string.

Create some classes:

- Device has name, company, price.

Questions:
1. Create a generic HashTable to store the data of devices with Open Address Resolution.
2. Create a generic HashTable to store the data of devices with Separate Chaining Resolution.
