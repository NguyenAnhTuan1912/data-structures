/*
  @author Nguyen Anh Tuan
  Quetions 6:
  Create an int (number) linked list class has print, insertLast,
  insertFirst, insertAt. Initialize a linked list instance to perform all of its methods.

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
      this.insertLast(ArrayNode[index]);
      index++;
    }
  }

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


  insertAt(index: number, data: number) {
    // ex: 1 -> 2 -> 3
    // insertAt(2, 4) => 1 -> 2 -> 4 -> 3 (4 at index 2)
    if (this.size - 1 < index) console.log("Go over index")
    else if (this.size === 0) this.initializeLinkedList(data);
    else {
      if (index === 0) this.insertFisrt(data);
      else if (index === this.size -1) this.insertLast(data);
      else {
        let newNode: NODE | null = new NODE(data);
        let current: NODE | null = this.head;
        let count = 0;
        while (count < index - 1) {
          current = current!.next;
          count++;
        }
        console.log("current", current?.data);
        newNode.next = current!.next;
        current!.next = newNode;
      }
    }

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
linkedList.insertLast(100);
linkedList.insertFisrt(0);
linkedList.insertAt(6, 99);
linkedList.print();



