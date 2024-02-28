/*
  @author Nguyen Anh Tuan
  Quetions 2:
  Create a linked list class whose Nodes have a data part is Point
  (Point is a class that has 2 private properties indicating for coordinate)
  and it has a print method. Initialize a linked list instance and print its element’s data to console.

  Done.
*/
class POINT {
  private x: number;
  private y: number;

  constructor(x: number, y: number) {
    this.x = x;
    this.y = y;
  }
  
  public getX() : number {
    return this.x;
  }
  
  public getY() : number {
    return this.y;
  }
}

class NODE {
  data: POINT;
  next: NODE | null = null;
  constructor(x: number, y: number) {
    this.data = new POINT(x, y);
  }
}

class LINKEDLIST {
  head: NODE | null = null;
  tail: NODE | null = null;
  size: number = 0;
  constructor(NodeArray: POINT[]) {
    NodeArray.map((node: POINT) => this.append(node.getX(), node.getY()));
  }

  initializeLinkedList(x: number, y: number): void {
    this.head = new NODE(x, y);
    this.tail = this.head;
  }

  append(x: number, y: number): void {
    // initialize linkedlist
    if (this.size === 0) this.initializeLinkedList(x, y);
    else {
      let current: NODE | null = new NODE(x, y);
      if (this.tail !== null && this.tail.next === null) {
        this.tail.next = current;
        this.tail = current;
      }
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

const linkedList = new LINKEDLIST([new POINT(1, 2), new POINT(3, 4), new POINT(5,6)]);

linkedList.print();


