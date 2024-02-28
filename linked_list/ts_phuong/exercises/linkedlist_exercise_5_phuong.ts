/*
  @author Nguyen Anh Tuan
  Quetions 5:
  Create a generic linked list class has print, insertLast, insertFirst methods.
  Initialize a number type linked list instance and add numbers of random Points
  to a declared Point type linked list instance that are generated from generic
  linked list class and print their element’s data to console.

  Done.
*/


class POINT {
  private x: number;
  private y: number;
  constructor(x: number, y: number) {
    this.x = x;
    this.y = y;
  }

  public getX() {
    return this.x;
  }

  public getY() {
    return this.y; 
  }
}

class NODE {
  data: POINT;
  next: NODE | null = null;
  constructor(point: POINT) {
    this.data = point;
  }
}

class LINKEDLIST {
  head: NODE | null = null;
  tail: NODE | null = null;
  size: number = 0;
  // constructor(NodeArray: number[]) {
  //   NodeArray.map((node: number) => this.insertLast(node));
  // }

  initializeLinkedList(point: POINT): void {
    this.head = new NODE(point);
    this.tail = this.head;
  }

  insertLast(x: number, y: number): void {
    // initialize linkedlist
    if (this.size === 0) this.initializeLinkedList(new POINT(x, y));
    else {
      let current: NODE | null = new NODE(new POINT(x, y));
      if (this.tail !== null && this.tail.next === null) {
        this.tail.next = current;
        this.tail = current;
      }
    }
    this.size++;
  }

  insertFisrt(x: number, y: number): void {
    if (this.size === 0) this.initializeLinkedList(new POINT(x, y));
    else {
      let current: NODE | null = new NODE(new POINT(x, y));
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
          text += `(x:${current.data.getX()},y:${current.data.getY()}) => `;
          current = current.next
        } else {
          text += `(x:${current.data.getX()},y:${current.data.getY()})`;
          current = null;
        }
      }
      console.log(text);
    }
  }
}

let linkedList: LINKEDLIST = new LINKEDLIST();

for (let index = 0; index < 5; index++) {
  linkedList.insertFisrt(Math.floor(Math.random() * 101), Math.floor(Math.random() * 101));
  linkedList.insertLast(Math.floor(Math.random() * 101), Math.floor(Math.random() * 101));
}

linkedList.print();

