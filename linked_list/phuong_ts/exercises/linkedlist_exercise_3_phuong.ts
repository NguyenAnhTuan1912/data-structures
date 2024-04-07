/*
  @author Nguyen Anh Tuan
  Quetions 3:
  Create a linked list class whose Nodes have a data part is integer type and it has print,
  insertLast, insertFirst methods. Declare a linked list instance, then add numbers of random
  int numbers and print its element’s data to console.

  Done.
*/

class NODE {
  data: number;
  next: NODE | null = null;
  constructor(data: number) {
    this.data = data;
  }
}

class LINKEDLIST {
  head: NODE | null = null;
  tail: NODE | null = null;
  size: number = 0;

  initializeLinkedList(data: number): void {
    this.head = new NODE(data);
    this.tail = this.head;
  }

  insertLast(data: number): void {
    // initialize linkedlist
    if (this.size === 0) this.initializeLinkedList(data);
    else {
      let current: NODE | null = new NODE(data);
      if (this.tail !== null && this.tail.next === null) {
        this.tail.next = current;
        this.tail = current;
      }
    }
    this.size++;
  }

  insertFisrt(data: number): void {
    if (this.size === 0) this.initializeLinkedList(data);
    else {
      let current: NODE | null = new NODE(data);
      current.next = this.head;
      this.head = current;
    }
    this.size++;
  }

  print(): void {
    if (this.size === 0) {
      console.log("Empty!")
    } else {
      let current: NODE | null = this.head;
      let text: string = "";
      while (current !== null) {
        if (current !== this.tail) {
          text += current.data + "=>";
          current = current.next
        } else {
          text += current.data;
          current = null;
        }
      }
      console.log(text);
    }
  }
}

let linkedList: LINKEDLIST = new LINKEDLIST();

for (let index = 0; index < 10; index++) {
  linkedList.insertLast(Math.floor(Math.random() * 101));
}

linkedList.print();

