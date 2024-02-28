/*
  @author Nguyen Anh Tuan
  Quetions 9:
  Create an int (number) linked list class has insertByOrder method.
  Declare a linked list and add numbers of random numbers with insertByOrder.

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


  constructor(ArrayNode: number[]) {
    let index = 0;
    while (ArrayNode.length !== index) {
      this.insertByOrder(ArrayNode[index]);
      index++;
    }
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

  insertByOrder(data: number): void {
    // initialize linkedlist
    if (this.size === 0) this.initializeLinkedList(data);
    else {
      let newNode: NODE | null = new NODE(data);
      if (this.head!.data > newNode.data) this.insertFisrt(data);
      else if (this.tail!.data < newNode.data) this.insertLast(data);
      else {
        let current = this.head;
        while (current!.next) {
          if (current!.data < newNode.data && current!.next!.data > newNode.data) {
            newNode.next = current!.next;
            current!.next = newNode;
            return;
          }
          current = current!.next;
        }
      }
    }
    this.size++;
  }

  initializeLinkedList(data: number): void {
    this.head = new NODE(data);
    this.tail = this.head;
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

let linkedList: LINKEDLIST = new LINKEDLIST([4,8,2,12,10,5]);
linkedList.print();



