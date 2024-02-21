/*
  @author Nguyen Anh Tuan
  Đây là file code chính thức của Queue, mọi thay đổi về cấu trúc
  của Queue sẽ được thay đổi trong này.
*/
#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>

template<class T>
class QueueNode {
public:
  T data;
  QueueNode* next = nullptr;

  QueueNode() = default;
  QueueNode(T d): data{d} {};
  QueueNode(T d, QueueNode* sn): data{d}, next{sn} {};
};

template<class T>
using ConstQueueNodeCallBack = std::function<void(const QueueNode<T>* sn)>;

template<class T>
class Queue {
private:
  QueueNode<T>* __head = nullptr;
  QueueNode<T>* __tail = nullptr;
  size_t __size = 0;

public:
  // Khởi tạo một queue mặc định với các thuộc tính
  // được khai báo như ở trong phần khai báo
  // thuộc tính của class Queue (ở trên).
  Queue() = default;

  // TODO: khởi tạo một queue với một danh sách dữ liệu.
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
  Queue(std::initializer_list<T> lst) {
    typename std::initializer_list<T>::iterator itr = lst.begin();
    typename std::initializer_list<T>::iterator last_item_itr = lst.end();
    this->__size = lst.size();
    last_item_itr--;

    this->__head = new QueueNode<T>(*itr);
    this->__tail = this->__head;

    if(itr == last_item_itr) return;

    QueueNode<T>* ptr = this->__head;
    this->__tail = new QueueNode<T>(*last_item_itr);
    this->__head->next = this->__tail;

    itr++;

    while(itr != last_item_itr) {
      QueueNode<T>* new_node = new QueueNode<T>(*itr, this->__tail);
      ptr->next = new_node;
      ptr = new_node;
      itr++;
    };
  };

  // TODO: xóa tất cả các Node trong queue khi queue
  // "không còn được dùng".
  //
  // Hàm hủy sẽ dùng phương thức clear() để dequeue()
  // các Nodes có trong queue.
  ~Queue() {
    this->clear();
  };

  // dequeue
  // TODO: gỡ và xóa Node đầu tiên ra khỏi queue.
  //
  // 1. Tạo một con trỏ "xóa node" - ptr và trỏ về __head, khi đó
  // __head sẽ được chuyển dịch tới next của chính nó.
  //
  // 2. Dùng ptr để xóa Node đầu tiên.
  //
  // 3. Giảm __size đi 1 đơn vị.
  void dequeue() {
    if(this->__head == nullptr) return;

    QueueNode<T>* ptr = this->__head;
    this->__head = this->__head->next;

    delete ptr;

    this->__size--;
  };

  // enqueue
  //
  // TODO: thêm Node mới vào đằng sau queue.
  //
  // 1. Nếu như queue rỗng, thì thêm Node mới như khởi tạo lần đầu tiên.
  //
  // 2. Ngược lại nếu như queue không rỗng thì tạo một Node mới - new_node.
  //
  // 3. Cho next của __tail trỏ về new_node.
  //
  // 4. Cho __tail = new_node;
  void enqueue(T data) {
    if(this->__head == nullptr) {
      this->__head = new QueueNode<T>(data);
      this->__tail = this->__head;
    } else {
      QueueNode<T>* new_node = new QueueNode<T>(data);
      this->__tail->next = new_node;
      this->__tail = new_node;
    };

    this->__size++;
  };

  // get
  // __NOTE__: không nên dùng, bởi vì nó sẽ trả về một pointer mà trỏ
  // về một instance được tạo trong Heap, nên khi dung thì phải xóa bộ nhớ
  // cẩn thận!!! Vì thế smart_pointer được khuyến nghị.
  //
  // TODO: gỡ Node đầu tiên ra khỏi queue và trả về con trỏ của Node đó.
  //
  // 1. Giống với gỡ và xóa, thì mình cũng phải tạo ra con trỏ của Node bị gỡ - ptr.
  //
  // 2. Sau đó là dịch chuyển __head sang next của chính nó.
  //
  // 3. Giảm __size đi 1 đơn vị và trả về ptr.
  QueueNode<T>* get() {
    if(this->__head == nullptr) return nullptr;

    QueueNode<T>* ptr = this->__head;
    this->__head = this->__head->next;

    this->__size--;

    return ptr;
  };

  // getSize
  // TODO: trả về só phần tử hiện có trong queue.
  size_t getSize() { return this->__size; };

  // forEach
  // TODO: duyệt qua queue và truyền cho ConstQueueNodeCallBack con trỏ tới
  // Node hiện tại đang duyệt để thực hiện công việc trong đó mà không làm
  // thay đổi cấu trúc hay dữ liệu của Node đó.
  void forEach(ConstQueueNodeCallBack<T> cb) {
    QueueNode<T>* ptr = this->__head;
    while(ptr != nullptr) {
      cb(ptr);
      ptr = ptr->next;
    };
  };

  // clear
  // TODO: xóa tất cả các Node trong queue. Lặp khi __head != nullptr (trong queue còn Node)
  // thì dequeue() cho đến khi __head == nullptr (hết Node trong queue) thì dừng lại.
  void clear() {
    while(this->__head != nullptr) this->dequeue();
  };
};

#endif // QUEUE_H_INCLUDED
