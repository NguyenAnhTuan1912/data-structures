/*
  @author Nguyen Anh Tuan
  Quetions 4:
  Create a linked list class similar to question 3, but Its Nodes’ data part is Point type.
  Initialize a linked list instance, then add numbers of random Points and print its element’s data to console.

  Done.
*/

class POINT<T> {
  private x: T;
  private y: T;
  constructor(x: T, y: T) {
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

class NODE<T> {
  data: POINT<T>;
  next: NODE<T> | null = null;
  constructor(point: POINT<T>) {
    this.data = point;
  }
}

class LINKEDLIST<T> {
  head: NODE<T> | null = null;
  tail: NODE<T> | null = null;
  size: number = 0;
  // constructor(NodeArray: T[]) {
  //   NodeArray.map((node: T) => this.insertLast(node));
  // }

  initializeLinkedList(point: POINT<T>): void {
    this.head = new NODE<T>(point);
    this.tail = this.head;
  }

  insertLast(x: T, y: T): void {
    // initialize linkedlist
    if (this.size === 0) this.initializeLinkedList(new POINT<T>(x, y));
    else {
      let current: NODE<T> | null = new NODE(new POINT<T>(x, y));
      if (this.tail !== null && this.tail.next === null) {
        this.tail.next = current;
        this.tail = current;
      }
    }
    this.size++;
  }

  insertFisrt(x: T, y: T): void {
    if (this.size === 0) this.initializeLinkedList(new POINT<T>(x, y));
    else {
      let current: NODE<T> | null = new NODE(new POINT<T>(x, y));
      current.next = this.head;
      this.head = current;
    }
    this.size++;
  }

  print(): void {
    if (this.size === 0) {
      console.log("Empty!")
    } else {
      let current: NODE<T> | null = this.head;
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

let linkedList: LINKEDLIST<number> = new LINKEDLIST<number>();

for (let index = 0; index < 5; index++) {
  linkedList.insertFisrt(Math.floor(Math.random() * 101), Math.floor(Math.random() * 101));
  linkedList.insertLast(Math.floor(Math.random() * 101), Math.floor(Math.random() * 101));
}

linkedList.print();

