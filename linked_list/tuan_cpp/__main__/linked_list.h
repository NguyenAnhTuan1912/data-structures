/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của LinkedList, mọi thay đổi về cấu trúc
  của LinkedList sẽ được thay đổi trong này.
*/

#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED
#pragma once

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

template<class T>
class SinglyLLNode {
public:
  T data;
  SinglyLLNode* next = nullptr;

  SinglyLLNode() = default;
  SinglyLLNode(T d): data{d} {};
  SinglyLLNode(T d, SinglyLLNode* n): data{d}, next{n} {};
};

template<class T>
using CompareFn = std::function<bool(T&, T&)>;

template<class T>
using ConstSinglyLLNodeCallBack = std::function<void(SinglyLLNode<T>*, int index)>;

template<class T>
class LinkedList {
private:
  SinglyLLNode<T>* __head = nullptr;
  SinglyLLNode<T>* __tail = nullptr;
  size_t __size = 0;

public:
  // Khởi tạo một singly linked list mặc định với các thuộc tính
  // được khai báo như ở trong phần khai báo
  // thuộc tính của class LinkedList (ở trên).
  LinkedList() = default;

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
  // 6. Cho next của __head trỏ về __tail. Sau đó tăng itr lên 1 đơn vị.
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
  //   7.1. Tạo một Node mới - new_node; cho next của new_node trỏ về __tail;
  //   7.2. Cho next của ptr trỏ về new_node.
  //   7.3. Cho ptr trỏ về new_node.
  //   7.4. Tăng itr lên một đơn vị để qua phần tử tiếp theo, quay về bước 7.0.
  LinkedList(std::initializer_list<T> lst) {
    typename std::initializer_list<T>::iterator itr = lst.begin();
    typename std::initializer_list<T>::iterator last_item_itr = lst.end();
    this->__size = lst.size();
    last_item_itr--;

    // Setup
    this->__head = new SinglyLLNode<T>(*itr);
    this->__tail = this->__head;

    if(itr == last_item_itr) return;

    this->__tail = new SinglyLLNode<T>(*last_item_itr);
    this->__head->next = this->__tail;

    SinglyLLNode<T>* ptr = this->__head;

    itr++;

    // Assign
    while(itr != last_item_itr) {
      ptr->next = new SinglyLLNode<T>(*itr, this->__tail);
      ptr = ptr->next;
      itr++;
    };
  };

  // TODO: xóa tất cả các Node trong linked list khi linked list
  // "không còn được dùng".
  //
  // Hàm hủy sẽ dùng phương thức clear() để removeFirst()
  // các Nodes có trong linked list.
  ~LinkedList() {
    this->clear();
  };

  // getAt
  // TODO: dùng để lấy ra một con trỏ của Node nào đó ở một vị trí bất kì.
  // và có thể thay đổi được dữ liệu của con trỏ đó.
  //
  // 1. Nếu như linked list rỗng, thì trả về nullptr.
  //
  // 2. Nếu như n <= 0 thì trả về con trỏ của Node đầu.
  //
  // 3. Nếu như n >= __size thì trả về con trỏ của Node đuôi.
  //
  // 4. Tạo ra một con trỏ mà nó trỏ tới __head, khai báo một biến đếm tới n.
  //
  // 5. Bắt đầu vòng lặp
  //   5.0. Nếu như c < n thì dừng vòng lặp.
  //   5.1. Dịch chuyển con trỏ hiện tại về con trỏ sau của nó ptr = ptr->next;
  //   5.2. Tăng c lên 1 đơn vị. Trở lại với bước 5.0.
  //
  // 6. Trả về con trỏ ptr.
  SinglyLLNode<T>* getAt(int n) {
    if(this->__head == nullptr) return nullptr;

    if(n <= 0) return this->__head;
    if(n >= this->__size) return this->__tail;

    SinglyLLNode<T>* ptr = this->__head;
    int c = 0;

    while(c < n) {
      ptr = ptr->next;
      c++;
    };

    return ptr;
  };

  // insertFirst
  // TODO: thêm một Node vào trước Node đầu (Head Node).
  //
  // 1. Nếu như linked list rỗng, thì thêm "lần đầu tiên".
  //
  // 2. Cón không thì tạo một Node mới và next của Node mới trỏ về __head.
  //
  // 3. Cho con trỏ head trỏ về Node mới.
  //
  // 4. Tăng __size lên 1 đơn vị.
  void insertFirst(T data) {
    if(this->__head == nullptr) {
      this->__head = new SinglyLLNode<T>(data);
      this->__tail = this->__head;

      this->__size++;

      return;
    };

    this->__head = new SinglyLLNode<T>(data, this->__head);

    this->__size++;
  };

  // insertLast
  // TODO: thêm một Node vào sau Node đuôi (Tail Node).
  //
  // 1. Nếu như linked list rỗng, thì thêm "lần đầu tiên".
  //
  // 2. Cón không thì, tạo một Node mới, cho next của Node đuôi trỏ về Node mới __tail->next = new_node.
  //
  // 3. Dịch chuyển con trỏ đuôi về Node mới __tail = new_node.
  //
  // 4. Tăng __size lên 1 đơn vị.
  void insertLast(T data) {
    if(this->__head == nullptr) {
      this->__head = new SinglyLLNode<T>(data);
      this->__tail = this->__head;

      this->__size++;

      return;
    };

    SinglyLLNode<T>* new_node = new SinglyLLNode<T>(data);
    this->__tail->next = new_node;
    this->__tail = new_node;

    this->__size++;
  };

  // insertAt
  // TODO: thêm một Node mới vào vị trí của một Node trong
  // linked list.
  //
  // 1. Nếu như linked rỗng hoặc n <= 0 thì thêm Node mới vào đầu với
  // insertFirst();
  //
  // 2. Nếu như n >= __size thì thêm Node mới vào đuôi với insertLast();
  //
  // 3. Còn không thì lấy ra Node trước vị trí cần thêm -  before.
  //
  // 4. Tạo Node mới và cho next của Node mới trỏ về Node tại vị trí cần thêm (before->next).
  //
  // 5. Cho next của before trỏ về Node mới.
  //
  // 6. Tăng __size lên 1 đơn vị.
  void insertAt(T data, int n) {
    if(this->__head == nullptr || n <= 0) {
      this->insertFirst(data);
      return;
    };

    if(n >= this->__size) {
      this->insertLast(data);
      return;
    };

    SinglyLLNode<T>* before = this->getAt(n - 1);
    before->next = new SinglyLLNode<T>(data, before->next);

    this->__size++;
  };

  // insertOrderBy
  // TODO: thêm một node vào trong linked list theo thứ tự được
  // xác định bởi hàm compare.
  //
  // 1. Nếu như linked list rỗng thì thêm "lần đầu" với insertFirst()
  // hoặc insertLast();
  //
  // 2. Tạo 2 con trỏ: 1 trỏ về __head - ptr, 1 trỏ về nullptr - before.
  //
  // 3. Bắt đầu vòng lặp
  //   3.0. Nếu như con trỏ hiện tại bằng nullptr thì dừng vòng lặp.
  //   3.1. Nếu kết quả so sánh của data của con trỏ hiện tại và
  //   data của Node sắp thêm là đúng, thì dừng vòng lặp.
  //   3.2. Cho con trỏ trước trỏ về Node của con trỏ hiện tại.
  //   3.3. Cho con trỏ hiện tại trỏ tới Node tiếp theo.
  //
  // 4. Nếu như ptr bằng nullptr, thì thêm cuối với insertLast().
  //
  // 5. Nếu như ptr bằng với __head, thì thêm đầu với insertFirst().
  //
  // 6. Tạo ra một Node mới, cho next của Node này trỏ về ptr (Node ở vị trí cần thêm).
  //
  // 7. Cho next của before về Node mới.
  //
  // 8. Tăng __size lên 1 đơn vị.
  void insertOrderBy(T data, CompareFn<T> compare) {
    if(this->__head == nullptr) {
      this->insertLast(data);
      return;
    };

    SinglyLLNode<T>* ptr = this->__head;
    SinglyLLNode<T>* before = nullptr;

    while(ptr != nullptr) {
      if(compare(ptr->data, data)) break;

      before = ptr;
      ptr = ptr->next;
    };

    if(ptr == nullptr) {
      this->insertLast(data);
      return;
    } else if(ptr == this->__head) {
      this->insertFirst(data);
      return;
    };

    SinglyLLNode<T>* new_node = new SinglyLLNode<T>(data, ptr);
    before->next = new_node;

    this->__size++;
  };

  // removeFirst
  // TODO: gỡ và xóa Node đầu ra khỏi linked list.
  //
  // 1. Nếu như linked list rỗng thì dừng lại.
  //
  // 2. Còn không thì tạo một con trỏ "xóa Node" - ptr và trỏ về __head.
  //
  // 3. Dịch chuyển __head về Node tiếp theo.
  //
  // 4. Trỏ next của ptr về nullptr
  //
  // 5. Xóa Node với con trỏ ptr.
  //
  // 6. Giảm __size đi 1 đơn vị.
  void removeFirst() {
    if(this->__head == nullptr) return;

    SinglyLLNode<T>* ptr = this->__head;
    this->__head = this->__head->next;
    ptr->next = nullptr;

    delete ptr;

    this->__size--;
  };

  // removeLast
  // TODO: gỡ và xóa đi Node cuối trong linked list.
  //
  // 1. Nếu như linked list rỗng thì dừng lại.
  //
  // 2. Còn không thì tạo ra một con trỏ mà trỏ về trước Node đuôi - before.
  //
  // 3. Khi đó cho next của before về nullptr.
  //
  // 4. Xóa Node duôi.
  //
  // 5. Giảm __size đi 1 đơn vị.
  void removeLast() {
    if(this->__head == nullptr) return;

    SinglyLLNode<T>* before = this->getAt(this->__size - 2);
    before->next = nullptr;

    delete this->__tail;

    this->__tail = before;

    this->__size--;
  };

  // removeAt
  // TODO: gỡ và xóa Node tại một vị trí bất kì trong linked list.
  //
  // 1. Nếu như linked list rỗng thì dừng lại.
  //
  // 2. Nếu như n <=0 thì gỡ và xóa Node đầu với removeFirst();
  //
  // 3. Nếu như n >= __size thì gỡ và xóa Node đuôi với removeLast();
  //
  // 4. Nếu không thì lấy ra con trỏ của Node trước Node cần xóa - before.
  //
  // 5. Lấy ra con trỏ của Node cần xóa - ptr.
  //
  // 6. Cho next của before trỏ về next của ptr.
  //
  // 7. Cho next của ptr trỏ về nullptr.
  //
  // 8. Giảm __size đi 1 đơn vị.
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

    SinglyLLNode<T>* before = this->getAt(n - 1);
    SinglyLLNode<T>* ptr = before->next;

    before->next = ptr->next;
    ptr->next = nullptr;

    delete ptr;

    this->__size--;
  };

  // forEach
  // TODO: duyệt qua linked list và truyền cho ConstSinglyLLNodeCallBack con trỏ tới
  // Node hiện tại đang duyệt và index để thực hiện công việc trong đó mà không làm
  // thay đổi cấu trúc hay dữ liệu của Node đó.
  void forEach(ConstSinglyLLNodeCallBack<T> cb) {
    SinglyLLNode<T>* ptr = this->__head;
    int index = 0;

    while(ptr != nullptr) {
      if(cb != NULL) cb(ptr, index);
      ptr = ptr->next;
      index++;
    };
  };

  // clear
  // TODO: xóa tất cả các Node trong linked list. Lặp khi __head != nullptr (trong linked list còn Node)
  // thì removeFirst() cho đến khi __head == nullptr (hết Node trong linked list) thì dừng lại.
  void clear() {
    while(this->__head != nullptr) this->removeFirst();
  };
};

#endif // LINKED_LIST_H_INCLUDED
