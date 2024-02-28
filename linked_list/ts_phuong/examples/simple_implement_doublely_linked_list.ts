class NODE<T> {
  data: T;
  next: NODE<T> | null = null;
  prev: NODE<T> | null = null;

  constructor(data: T) {
    this.data = data;
  }
}

class DOUBLELYLINKEDLIST<T> {
  head: NODE<T> | null = null; 
  tail: NODE<T> | null = null; 
  
  size: number = 0;

  constructor(ArrayNode: T[]) {
    ArrayNode.forEach((item: T) => this.append(item));
  }

  getSize() : number {
    return this.size;
  }

  append(data: T): void {
    if (this.head === null && this.tail === null) {
      this.head = new NODE<T>(data);
      this.tail = this.head;
    } else {
      let current = new NODE<T>(data);
      if (this.tail && this.tail.next === null) {
        this.tail.next = current;
        current.prev = this.tail
        this.tail = current;
      }
    }
    this.size++;
  }

  preappend(data: T): void {
    if (this.head === null && this.tail === null) {
      this.head = new NODE<T>(data);
      this.tail = this.head;
    } else {
      let current = new NODE<T>(data);
      if (this.head && this.head.prev === null) {
        this.head.prev = current;
        current.next = this.head;
        this.head = current;
      }
    }
    this.size++;
  }

  delete(data: T): void {
    if (!this.head && !this.tail) {
      console.log("Linked List is empty");
      return;
    }

    if (this.head!.data === data) {
      // remove the first node
      this.head = this.head!.next;
      this.head!.prev = null;
      this.size--;
      return;
    }

    let current = this.head!.next;
    while (current) {
      if (current.data === data) {
        if (current.next === null) {
          this.tail = current.prev;
          this.tail!.next = null;
        } else {
          current.prev!.next = current.next;
          current.next!.prev = current.prev;
        }
        this.size--;
        return;
      }
      current = current.next;
    }
  }
  
  search(data: T): void {
    if (!this.head && !this.tail) {
      console.log("Linked List is empty");
      return;
    }

    if (this.head!.data === data) {
      console.log(this.head);
      return;
    }

    let current = this.head!.next;
    while (current) {
      if (current.data === data) {
        console.log(current);
        return;
      }
      current = current.next;
    }
  }

  printIndex(index: number): void {
    if (index > this.size -1 || this.size === 0) {
      console.log('Go over bound of memory or empty!');
      return;
    }

    if (index > this.size/2) {
      let count = (this.size - 1) - index;
      let current = this.tail;
      while (count > 0) {
        current = current!.prev;
        count--;
      }
      console.log("KQ tai vi tri index bang cach chia nua cuoi: " + index + "la " + current?.data);
    } else {
      let current = this.head;
      let count = index;
      while (count > 0) {
        current = current!.next;
        count--;
      }
      console.log("KQ tai vi tri index bang cach chia nua dau: " + index + "la " + current?.data);
    }
  }

  addAfter(index: number, data: T): void {

    // overflow size
    if (index > this.size -1) {
      console.log('The Index go over bound of memory!');
      return;
    }

    // no any node
    if (this.size === 0) {
      this.head = new NODE<T>(data);
      this.tail = this.head;
      return
    } 

    // index is last node 
    if (this.size -1 === index) {
      this.append(data)
      return;
    }


    let current: NODE<T> | null;
    let newNode = new NODE<T>(data)
    if (index > this.size/2) {
      let count = (this.size - 1) - index;
      current = this.tail;
      while (count > 1) {
        current = current!.prev;
        count--;
      }
    } else {
      current = this.head;
      let count = index;
      while (count > -1) {
        current = current!.next;
        count--;
      }
    }

    newNode.prev = current!.prev;
    newNode.next = current;
    current!.prev!.next = newNode;
    current!.prev = newNode
  }

  traverse(): void {
    let current = this.head;
    if (!this.head && !this.tail) {
      console.log("Traverse empty!");
      return;
    }
    let text = "";
    while (current) {
      if (current.next === null) {
        text += current.data;
        current = null;
      } else {
        text += current.data + "=>";
        current = current.next;
      }
    }
    console.log(text);
  }

  traverseReverse(): void {
    let current = this.tail;
    let text = "";
    if (!this.head && !this.tail) {
      console.log("Linked list is empty!");
      return;
    }
    while (current) {
      if (!current.prev) {
        text += current.data;
        current = null;
      } else {
        text += current.data + "=>";
        current = current.prev;
      }
    }
    console.log(text);
  }
}

const list = new DOUBLELYLINKEDLIST<number>([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
console.log("Size:",list.getSize());

list.delete(10);
console.log("Size:",list.getSize());

list.delete(3);
console.log("Size:",list.getSize());

list.delete(6);
console.log("Size:",list.getSize());

list.traverse();
list.traverseReverse();
list.preappend(890);

list.traverse();
list.addAfter(0, 200);
list.traverse();
list.traverseReverse();

console.log("Size:",list.getSize());
list.printIndex(3)
// list.search(3)
