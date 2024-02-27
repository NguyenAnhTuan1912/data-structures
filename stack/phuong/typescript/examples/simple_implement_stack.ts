class NODE<T> {
  data: T;
  next: NODE<T> | null = null;

  constructor(data: T) {
    this.data = data;
  }
}

class STACK<T> {
  head: NODE<T> | null = null;
  size: number = 0;
  max: number = 10;

  constructor() {
    
  }

  intialize(data: T): void {
    this.head = new NODE<T>(data);
  }

  push(data: T): void {
    if (this.size === 0) this.intialize(data);
    else if (this.size === this.max) console.log("Cann't use push() method on full of stack!")
    else {
      let newNode: NODE<T> | null = new NODE<T>(data);
      newNode.next = this.head;
      newNode = this.head;
    }
    this.size++;
  }

  pop(): void {
    if (this.size === 0) console.log("Cann't use method pop() on empty stack!");
    else if (this.size === 1) this.head = null;
    else {
      let current = this.head;
      this.head = current!.next;
      current = null;
    }
    this.size--;
  }

  getSize(): void {
    console.log(`Stack have a size: ${this.size}`);
  }

  isEmpty(): void {
    let current = this.head;
    while (current) {
      this.pop();
      current = current.next;
    }
    this.size = 0;
  }

  getTop(): void {
    if (this.size === 0) console.log("Cann't use method getTop() on empty stack!");
    else console.log(`Stack have a top: ${this.head!.data}`);
  }

  print(): void {
    if (this.size === 0) console.log("Cann't use method print() on empty stack!");
    else {
      let current = this.head;
      let text = "";
      while (current) {
        if (current.next === null)
          text += current.data;
        else 
          text += current.data + "=>";
        current = current.next;
      }
    }
  }
}

