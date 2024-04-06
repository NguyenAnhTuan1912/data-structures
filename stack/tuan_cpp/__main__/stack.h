/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của Stack, mọi thay đổi về cấu trúc
  của Stack sẽ được thay đổi trong này.
*/

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>
#include <exception>

template<class T>
class StackNode {
public:
  T data;
  StackNode* bottom = nullptr;

  StackNode() = default;
  StackNode(T d): data{d} {};
  StackNode(T d, StackNode* sn): data{d}, bottom{sn} {};
};

template<class T>
using ConstStackNodeCallBack = std::function<void(const StackNode<T>* sn)>;

template<class T>
class Stack {
private:
  StackNode<T>* __top = nullptr;
  size_t __size = 0;
  size_t __max = 100;

public:
  // Khởi tạo một stack mặc định với các thuộc tính
  // được khai báo như ở trong phần khai báo
  // thuộc tính của class Stack (ở trên).
  Stack(size_t max_size = 100): __max{max_size} {};

  // TODO: khởi tạo một Queue với một danh sách dữ liệu.
  //
  // Nhận vào một std::initializer_list<T> để có thể khởi tạo
  // một queue có dữ liệu.
  // Các bước thực hiện:
  // 1. Lấy ra con trở của phần tử đầu tiên - itr, và SAU phần tử cuối - last_item_itr.
  //
  // 2. Gán __max = max_size;
  //
  // TODO: thêm Node mới vào đầu stack.
  //
  // 3. Bước vào vòng lặp với điều kiện itr != last_item_itr;
  //   3.0. Nếu như con trỏ của phần tử hiện tại bằng với con trỏ của SAU phần tử cuối,
  //   thì dừng vòng lặp.
  //   3.1. Nếu như số lượng phần tử hiện tại bằng với số lượng phần tử tối đa thì dừng
  //   vòng lặp __size >= __max;
  //   3.2. Tạo một Node mới và next của Node mới trỏ về __top.
  //   3.3. Dịch chuyển __top "lên" Node mới.
  //   3.4. Tăng __size và itr lên 1 đơn vị và quay lại bước 3.0.
  Stack(std::initializer_list<T> lst, size_t max_size = 100) {
    typename std::initializer_list<T>::iterator itr = lst.begin();
    typename std::initializer_list<T>::iterator itr_end = lst.end();
    this->__max = max_size;

    while(itr != itr_end) {
      if(this->__size >= this->__max) break;
      StackNode<T>* new_node = new StackNode<T>(*itr, this->__top);
      this->__top = new_node;

      this->__size++;
      itr++;
    };
  };
  // TODO: xóa tất cả các Node trong stack khi stack
  // "không còn được dùng".
  //
  // Hàm hủy sẽ dùng phương thức clear() để pop()
  // các Nodes có trong stack.
  ~Stack() {
    this->clear();
  };

  // pop
  // TODO: gỡ và xóa Node "trên cùng" ra khỏi stack.
  //
  // 1. Khởi tạo một con trỏ "xóa node" - ptr và trỏ nó về Node trên cùng.
  //
  // 2. Sau đó là cho con trỏ trên cùng trỏ về Node ở dưới.
  //
  // 3. Cuối cùng là xóa Node trên cùng và giảm __size đi 1 đơn vị.
  void pop() {
    if(this->__top == nullptr) return;

    StackNode<T>* ptr = this->__top;
    this->__top = this->__top->bottom;

    delete ptr;

    this->__size--;
  };

  // push
  // TODO: thêm một Node mới ở "trên cùng" của stack.
  //
  // 1. Nếu như số lượng Node bằng hoặc vượt quá số lượng Node cho phép,
  // thì "ném" ra lỗi.
  //
  // 2. Còn không thì tạo ra một Node mới, next của Node mới này sẽ trỏ về Node trên cùng.
  //
  // 3. Con trỏ trên cùng sẽ trỏ về Node mới.
  //
  // 4. Cuối cùng là tăng __size lên 1 đơn vị.
  void push(T data) {
    if(this->__size >= this->__max) throw std::runtime_error("Maximum size of stack is reached.");

    StackNode<T>* new_node = new StackNode<T>(data, this->__top);
    this->__top = new_node;

    this->__size++;
  };

  // getSize
  // TODO: trả về số lượng Node hiện tại trong stack.
  size_t getSize() { return this->__size; };

  // forEach
  // TODO: duyệt qua stack và truyền cho ConstStackNodeCallBack con trỏ tới
  // Node hiện tại đang duyệt để thực hiện công việc trong đó mà không làm
  // thay đổi cấu trúc hay dữ liệu của Node đó.
  void forEach(ConstStackNodeCallBack<T> cb) {
    StackNode<T>* ptr = this->__top;
    while(ptr != nullptr) {
      cb(ptr);
      ptr = ptr->bottom;
    };
  };

  // clear
  // TODO: xóa tất cả các Node trong stack. Lặp khi __top != nullptr (trong stack còn Node)
  // thì pop() cho đến khi __top == nullptr (hết Node trong stack) thì dừng lại.
  void clear() {
    while(this->__top != nullptr) this->pop();
  };
};

#endif // STACK_H_INCLUDED
