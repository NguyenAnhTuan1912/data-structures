/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của DoublyLinkedList, mọi thay đổi về cấu trúc
  của DoublyLinkedList sẽ được thay đổi trong này.
*/
#ifndef DOUBLY_LINKED_LIST_H_INCLUDED
#define DOUBLY_LINKED_LIST_H_INCLUDED
#pragma once

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

template<class T>
class DoublyLLNode {
public:
  T data;
  DoublyLLNode* next = nullptr;
  DoublyLLNode* prev = nullptr;

  DoublyLLNode() = default;
  DoublyLLNode(T d): data{d} {};
  DoublyLLNode(T d, DoublyLLNode* p, DoublyLLNode* n): data{d}, prev{p}, next{n} {};
};

template<class T>
using CompareFn = std::function<bool(T&, T&)>;

template<class T>
using ConstDoublyLLNodeCallBack = std::function<void(DoublyLLNode<T>*, int index)>;

template<class T>
class DoublyLinkedList {
private:
  DoublyLLNode<T>* __head = nullptr;
  DoublyLLNode<T>* __tail = nullptr;
  size_t __size = 0;

  void __forEachFromHead(ConstDoublyLLNodeCallBack<T> cb = NULL) {
    DoublyLLNode<T>* ptr = this->__head;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->next;
      index++;
    };
  };

  void __forEachFromTail(ConstDoublyLLNodeCallBack<T> cb = NULL) {
    DoublyLLNode<T>* ptr = this->__tail;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->prev;
      index++;
    };
  };

public:
  // Khởi tạo một doubly linked list mặc định với các thuộc tính
  // được khai báo như ở trong phần khai báo
  // thuộc tính của class DoublyLinkedList (ở trên).
  DoublyLinkedList() = default;

  // TODO: khởi tạo một linked list với một danh sách dữ liệu.
  //
  // Nhận vào một std::initializer_list<T> để có thể khởi tạo
  // một queue có dữ liệu.
  // Các bước thực hiện:
  // 1. Lấy ra con trở của phần tử đầu tiên - itr, và phần tử cuối - last_item_itr
  // (bằng cách lùi lst.end() đi 1 đơn vị.
  //
  // 2. Gán __size = lst.size();
  //
  // 3. Tạo Node đầu tiên, và cho __head trỏ về Node đó. Sau đó
  // cho __tail = __head;
  //
  // 4. Nếu như trong lst chỉ có một phần tử, thì dừng việc khởi tạo lại.
  //
  // 5. Còn không thì tạo một con trỏ mới - ptr và trỏ về Node đầu tiên,
  // tạo Node mới cho __tail với dữ liệu là phần tử cuối.
  //
  // 6. Cho next của __head trỏ về __tail; prev của __tail trỏ về __head.
  // Sau đó tăng itr lên 1 đơn vị.
  //
  // TODO: thêm Node mới vào giữa 2 Node, trong đó Node sau
  // sẽ luôn là __tail.
  //
  // Đó là lý do mà mình cần phải tạo một
  // con trỏ - ptr và trỏ về __head, thời điểm ban đầu thì trong queue
  // chỉ có 2 Nodes __head và __tail -> Cứ sau mỗi lần thêm Node thì cho
  // ptr = Node mới => luôn đáp ứng được tiêu chí trên.
  //
  // 7. Bước vào vòng lặp với điều kiện itr != last_item_itr;
  //   7.0. Nếu như con trỏ của phần tử hiện tại bằng với con trỏ của phần tử cuối,
  //   thì dừng vòng lặp.
  //   7.1. Tạo một Node mới - new_node (ptr->next), cho next của new_node trỏ về __tail và
  //   prev của new_node trỏ về ptr.
  //   7.2. Cho next của ptr trỏ về new_node.
  //   7.3. Cho prev của __tail trỏ về new_node.
  //   7.4. Cho ptr trỏ về new_node (ptr = ptr->next).
  //   7.5. Tăng itr lên một đơn vị để qua phần tử tiếp theo, quay về bước 7.0.
  DoublyLinkedList(std::initializer_list<T> lst) {
    typename std::initializer_list<T>::iterator itr = lst.begin();
    typename std::initializer_list<T>::iterator last_item_itr = lst.end();
    this->__size = lst.size();
    last_item_itr--;

    // Setup
    this->__head = new DoublyLLNode<T>(*itr);
    this->__tail = this->__head;

    if(last_item_itr == itr) return;

    this->__tail = new DoublyLLNode<T>(*last_item_itr);
    this->__head->next = this->__tail;
    this->__tail->prev = this->__head;
    DoublyLLNode<T>* ptr = this->__head;

    itr++;

    while(itr != last_item_itr) {
      ptr->next = new DoublyLLNode<T>(*itr, ptr, this->__tail);
      this->__tail->prev = ptr->next;
      ptr = ptr->next;
      itr++;
    };
  };

  // TODO: xóa tất cả các Node trong doubly linked list khi doubly linked list
  // "không còn được dùng".
  //
  // Hàm hủy sẽ dùng phương thức clear() để removeFirst()
  // các Nodes có trong doubly linked list.
  ~DoublyLinkedList() {
    this->clear();
  };

  // getAt
  // TODO: lấy con trỏ của Node tại một vị trí nào đó.
  //
  // 1. Nếu như linked list rỗng thì trả về nullptr.
  //
  // 2. Nếu như n <= 0 thì trả con trỏ của Node đầu tiên.
  //
  // 3. Nếu như n >= __size thì trả về con trỏ của Node đuôi.
  //
  // 4. Còn không thì tạo một con trỏ trỏ tới Node đầu - ptr và
  // một biến để check duyệt từ đầu - canStartFromHead
  //
  // 5. Nếu như n > __size / 2, thì điều đó có nghĩa là Node cần lấy
  // nằm ở nửa cuối của linked list, nên sẽ duyệt từ __tail =>
  // canStartFromHead = false, ngược lại thì Node cần lấy nằm ở nửa đầu
  // của linked list, nên sẽ duyệt từ __head => canStartFromHead = true.
  // Đồng thời mình cho ptr trỏ về __tail và tính lại index của Node cần
  // lấy sao cho phù hợp.
  //
  // 6. Tạo một biến đếm và bắt đầu vòng lặp
  //   6.0. Nếu c >= n thì dừng vòng lặp.
  //   6.1. Nếu canStartFromHead = true thì dịch chuyển ptr về Node tiếp theo,
  //   ngược lại thì dịch chuyển ptr về Node trước đó.
  //   6.2. Tăng c lên 1 đơn vị và tiếp tục vòng lặp.
  //
  // 7. Trả về ptr.
  DoublyLLNode<T>* getAt(int n) {
    if(this->__head == nullptr) return nullptr;
    if(n <= 0) return this->__head;
    if(n >= this->__size) return this->__tail;

    DoublyLLNode<T>* ptr = this->__head;
    bool canStartFromHead = true;

    if(n > (this->__size / 2)) {
      ptr = this->__tail;
      canStartFromHead = false;
      n = this->__size - n - 1;
    };

    int c = 0;

    while(c < n) {
      if(canStartFromHead) ptr = ptr->next;
      else ptr = ptr->prev;
      c++;
    };

    return ptr;
  };

  // insertFirst
  // TODO: thêm một Node mới vào đầu linked list.
  //
  // 1. Nếu như linked list rỗng, thì thêm mới.
  //
  // 2. Còn không thì tạo ra một Node mới - new_node và prev của new_node
  // sẽ trỏ về nullptr còn next của new_node sẽ trỏ về __head.
  //
  // 3. prev của Node đầu sẽ trỏ về new_node.
  //
  // 4. Con trỏ đầu sẽ trỏ về new_node.
  //
  // 5. Tăng __size lên 1 đơn vị.
  void insertFirst(T data) {
    if(this->__head == nullptr) {
      this->__head = new DoublyLLNode<T>(data);
      this->__tail = this->__head;

      this->__size++;

      return;
    };

    DoublyLLNode<T>* new_node = new DoublyLLNode<T>(data, nullptr, this->__head);

    this->__head->prev = new_node;
    this->__head = new_node;

    this->__size++;
  };

  // insertLast
  // TODO: thêm một Node mới vào cuối linked list.
  //
  // 1. Nếu như linked list rỗng thì thêm mới.
  //
  // 2. Còn không thì tạo ra một Node mới - new_node và prev của new_node
  // sẽ trỏ về Node đuôi, còn next của new_node sẽ trỏ về nullptr.
  //
  // 3. next của Node đuôi sẽ trỏ về new_node.
  //
  // 4. Con trỏ đuôi sẽ trỏ về new_node.
  //
  // 5. Tăng __size lên 1 đơn vị.
  void insertLast(T data) {
    if(this->__head == nullptr) {
      this->__head = new DoublyLLNode<T>(data);
      this->__tail = this->__head;

      this->__size++;

      return;
    };

    DoublyLLNode<T>* new_node = new DoublyLLNode<T>(data, this->__tail, nullptr);

    this->__tail->next = new_node;
    this->__tail = new_node;

    this->__size++;
  };

  // insertAt
  // TODO: thêm một Node mới tại một vị trí bất kì.
  //
  // 1. Nếu như n <= 0 hoặc linked list rỗng, thì thêm mới với insertFirst.
  //
  // 2. Nếu như n >= __size, thì thêm vào cuối với insertLast.
  //
  // 3. Còn không thì lấy ra một con trỏ của Node tại vị trí cần thêm - ptr.
  //
  // 4. Tạo một Node mới - new_node; prev của Node mới sẽ trỏ về Node trước của ptr,
  // còn next của new_node sẽ trỏ về ptr.
  //
  // 5. Khi đó next của Node trước ptr sẽ trỏ về new_node.
  //
  // 6. Khi đó prev của ptr sẽ trỏ về new_node.
  //
  // 7. Tăng __size lên 1 đơn vị.
  void insertAt(T data, int n) {
    if(n <= 0 || this->__head == nullptr) {
      this->insertFirst(data);
      return;
    };
    if(n >= this->__size) {
      this->insertLast(data);
      return;
    };

    DoublyLLNode<T>* ptr = this->getAt(n);
    DoublyLLNode<T>* new_node = new DoublyLLNode<T>(data, ptr->prev, ptr);

    ptr->prev->next = new_node;
    ptr->prev = new_node;

    this->__size++;
  };

  // insertOrderBy
  // TODO: thêm một Node mới vào trong linked list theo thứ tự được quyết định
  // bởi hàm compare.
  //
  // 1. Nếu như linked list rỗng, thì thêm mới với insertFirst.
  //
  // 2. Tạo ra một con trỏ và trỏ tới __head - ptr.
  //
  // 3. Bắt đầu vòng lặp
  //   3.0. Nếu như ptr == nullptr thì dừng lại vòng lặp.
  //   3.1. Nếu phép so sánh của ptr->data và data là đúng, thì vòng lặp dừng.
  //   3.2. Còn không thì dịch chuyển ptr với Node tiếp theo.
  //
  // 4. Nếu như ptr == nullptr, thì thêm vào cuối linked list với insertLast.
  //
  // 5. Nếu như ptr == __head, thì thêm vào đầu linked list với insertFirst.
  //
  // 6. Còn không thì tạo ra một Node mới - new_node; prev của new_node trỏ về
  // Node trước đó, còn next của new_node sẽ trỏ về chính Node ở vị trí đó.
  //
  // 7. Khi đó next của Node trước đó sẽ trỏ về new_node.
  //
  // 8. Khi đó prev của ptr (con trỏ của Node cần thay) sẽ trỏ về new_node.
  //
  // 9. Tăng __size lên 1 đơn vị.
  void insertOrderBy(T data, CompareFn<T> compare) {
    if(this->__head == nullptr) {
      this->insertFirst(data);
      return;
    };

    DoublyLLNode<T>* ptr = this->__head;

    while(ptr != nullptr) {
      if(compare(ptr->data, data)) break;

      ptr = ptr->next;
    };

    if(ptr == nullptr) {
      this->insertLast(data);
      return;
    } else if(ptr == this->__head) {
      this->insertFirst(data);
      return;
    };

    DoublyLLNode<T>* new_node = new DoublyLLNode<T>(data, ptr->prev, ptr);

    ptr->prev->next = new_node;
    ptr->prev = new_node;

    this->__size++;
  };

  // removeFirst
  // TODO: gỡ và xóa Node đầu ra khỏi linked list.
  //
  // 1. Nếu như linked list rỗng thì dừng.
  //
  // 2. Còn không thì tạo ra một con trỏ của Node đầu.
  //
  // 3. ptr trỏ về Node sau của Node đầu.
  //
  // 4. prev của ptr trỏ về nullptr.
  //
  // 5. next của Node đầu tiên sẽ trỏ về nullptr (Node đầu mới).
  //
  // 6. Xóa Node đầu cũ với __head.
  //
  // 7. __head trỏ về Node đầu thông qua ptr.
  //
  // 8. Giảm __size 1 đơn vị.
  void removeFirst() {
    if(this->__head == nullptr) return;

    DoublyLLNode<T>* ptr = this->__head;

    ptr = this->__head->next;
    ptr->prev = nullptr;
    this->__head->next = nullptr;

    delete this->__head;

    this->__head = ptr;

    this->__size--;
  };

  // removeLast
  // TODO: gỡ và xóa Node đuôi của linked list.
  //
  // 1. Nếu như linked rỗng thì dừng lại.
  //
  // 2. Còn không thì tạo ra một con trỏ và trỏ về Node đuôi.
  //
  // 3. ptr sẽ trỏ về Node trước của Node đuôi.
  //
  // 4. prev Node trước của Node đuôi sẽ trỏ về nullptr.
  //
  // 5. next của ptr sẽ trỏ về nullptr (Node đuôi mới).
  //
  // 6. Xóa Node đuôi cũ với __tail.
  //
  // 7. __tail trỏ về Node đuôi mới.
  //
  // 8. Giảm __size 1 đơn vị.
  void removeLast() {
    if(this->__tail == nullptr) return;

    DoublyLLNode<T>* ptr = this->__tail;

    ptr = this->__tail->prev;
    this->__tail->prev = nullptr;
    ptr->next = nullptr;

    delete this->__tail;

    this->__tail = ptr;

    this->__size--;
  };

  // removeAt
  // TODO: gỡ và xóa một Node tại một vị trí bất kì trong linked list.
  //
  // 1. Nếu như linked list rỗng thì dừng.
  //
  // 2. Nếu như n <= 0 thì gỡ và xóa Node đầu với removeFirst.
  //
  // 3. Nếu như n >= __size thì gỡ và xóa Node đuôi với removeLast.
  //
  // 4. Còn không thì lấy ra con trỏ của Node cần xóa.
  //
  // 5. next của Node trước của Node cần xóa trỏ về Node sau của Node cần xóa.
  //
  // 6. prev của Node sau của Node cần xóa trỏ về Node trước của Node cần xóa.
  //
  // 7. Xóa Node với ptr.
  //
  // 8. Giảm __size 1 đơn vị.
  void removeAt(int n) {
    if(this->__head == nullptr) return;
    if(n <= 0) {
      this->removeFirst();
      return;
    };
    if(n >= this->__size) {
      this->removeLast();
      return;
    };

    DoublyLLNode<T>* ptr = this->getAt(n);

    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;

    delete ptr;

    this->__size--;
  };

  // forEach
  // TODO: duyệt qua doubly linked list và truyền cho ConstDoublyLLNodeCallBack con trỏ tới
  // Node hiện tại đang duyệt và index để thực hiện công việc trong đó mà không làm
  // thay đổi cấu trúc hay dữ liệu của Node đó. Và có thể duyệt từ đầu hoặc cuối doubly linked list
  // với tham số isStartFromHead.
  void forEach(ConstDoublyLLNodeCallBack<T> cb, bool isStartFromHead = true) {
    if(isStartFromHead) {
      this->__forEachFromHead(cb);
      return;
    };

    this->__forEachFromTail(cb);
  };

  // clear
  // TODO: xóa tất cả các Node trong linked list.
  //
  // 1. Tạo một con trỏ để xóa, trỏ về Node đầu tiên.
  //
  // 2. Bắt đầu vòng lặp
  //   2.0. Nếu như ptr == nullptr thì dừng vòng lặp.
  //   2.1. Con trỏ đầu trỏ tới Node tiếp theo của Node đầu.
  //   2.2. Xóa Node đầu cũ.
  //   2.3. ptr trỏ về Node đầu mới.
  //
  // 3. Gán __size = 0.
  void clear() {
    DoublyLLNode<T>* ptr = this->__head;

    while(ptr != nullptr) {
      this->__head = this->__head->next;
      delete ptr;
      ptr = this->__head;
    };

    this->__size = 0;
  };
};

#endif // DOUBLY_LINKED_LIST_H_INCLUDED
