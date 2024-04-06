/*
  @author Nguyen Anh Tuan
  Trong bài này mình sẽ cài đặt code của Hash Table với giải pháp đụng độ index
  Open Addressing với value có kiểu dữ liệu là int. Với các phương thức:
  - insert
  - remove
  - get

  Hashtable này chỉ nhận vào key là int.

  Ấn build để nó hiện ra từng message của lỗi.
  Để thực thi và xem các ví dụ thì comment những chỗ code lỗi lại.
*/

#include <iostream>
#include <vector>
#include <functional>

/*
  Hiện tại thì việc resize lại Hash Table vẫn chưa được tốt cho lắm cho nên là
  sẽ gặp vấn đề về Hash.

  Comment include hashtable không dùng tới. Có thể dùng 2 kiểu khác nhau
  để so sánh kết quả.
*/

// Open Addressing
// #include "hash_table_open_addressing.h"

// Seperate Chaining
#include "hash_table_separate_chaining.h"

using namespace std;

int main() {
  // Print value
  ConstBucketCallBack<string> printSentence = [](string k, string* v) {
    string value = (v == nullptr) ? "" : *v;
    cout << "(K: " << k << ", V: " << value << ")\n";
  };

  // Declare a hash table
  HashTable<string> sentence_ht;

  cout << "INITIAL SIZE: \n";
  cout << "Size: " << sentence_ht.getSize() << endl;
  cout << endl;

  // Add items
  cout << "Add some items...\n";
  sentence_ht.insert("0", "Hello");
  sentence_ht.insert("1", "Day la bai tap ve");
  sentence_ht.insert("2", "HashTable");
  sentence_ht.insert("1", "Key nay bi trung roi");
  sentence_ht.insert("34", "cannot read");
  sentence_ht.insert("3", "Co cac phuong thuc nhu la: ");
  sentence_ht.insert("2", "Key ney bi trung tiep");
  sentence_ht.insert("40", "cannot readdf");
  sentence_ht.insert("4", "insert, delete, get");
  sentence_ht.insert("5", "HashTable nay nhan key-value la int-string");
  sentence_ht.insert("asdfh", "Don't know");
  sentence_ht.insert("ash", "I'm virus");
  sentence_ht.insert("asdad", "Delete me if you can");
  sentence_ht.insert("87fjhs", "You can't see me");
  sentence_ht.insert("lkj4", "DELETEEEEEE");
  cout << endl;

  // print
  cout << "Print sentence: \n";
  cout << "Size: " << sentence_ht.getSize() << endl;
  sentence_ht.forEach(printSentence);
  cout << endl;

  // Remove items
  cout << "Remove some items...\n";
  sentence_ht.remove("34");
  sentence_ht.remove("40");
  sentence_ht.remove("asdfh");
  sentence_ht.remove("ash");
  sentence_ht.remove("asdad");
  sentence_ht.remove("87fjhs");
  sentence_ht.remove("lkj4");
  cout << endl;

  // print
  cout << "Print sentence: \n";
  cout << "Size: " << sentence_ht.getSize() << endl;
  sentence_ht.forEach(printSentence);
  cout << endl;

  // Get with key
  string* s_get_01 = sentence_ht.get("0");
  string* s_get_02 = sentence_ht.get("2");


  cout << "Get data in sentence_ht with key \"0\": ";
  if(s_get_01 == nullptr) cout << "Empty\n";
  else cout << *s_get_01 << endl;

  cout << "Get data in sentence_ht with key \"2\": ";
  if(s_get_01 == nullptr) cout << "Empty\n";
  else cout << *s_get_02 << endl;
  cout << endl;

  // Add more
  cout << "Add more sentences...\n";
  sentence_ht.insert("6", "There are extra sentences!!");
  sentence_ht.insert("74fg", "\"Data structures concept\"");
  sentence_ht.insert("0", "Cannot add");
  sentence_ht.insert("8d45", "is things that every devs must know.");
  sentence_ht.insert("4", "Cannot add too :))");
  cout << endl;

  // print
  cout << "Print sentence: \n";
  cout << "Size: " << sentence_ht.getSize() << endl;
  sentence_ht.forEach(printSentence);
  cout << endl;

  // Get with key
  string* s_get_03 = sentence_ht.get("74fg");
  string* s_get_04 = sentence_ht.get("8d45");


  cout << "Get data in sentence_ht with key \"74fg\": ";
  if(s_get_03 == nullptr) cout << "Empty\n";
  else cout << *s_get_03 << endl;

  cout << "Get data in sentence_ht with key \"8d45\": ";
  if(s_get_04 == nullptr) cout << "Empty\n";
  else cout << *s_get_04 << endl;

  return 0;
};
