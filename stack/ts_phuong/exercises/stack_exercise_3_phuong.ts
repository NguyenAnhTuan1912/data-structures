

class NODE {
  data: number;
  next: NODE | null = null;

  constructor(data: number) {
    this.data = data;
  }
}

class STACK {
  head: NODE | null = null;
  size: number = 0;
  max: number = 10;

  constructor(arrayNode: number[]) {
    arrayNode.reverse().map((node: number) => this.push(node));
  } 

  intialize(data: number): void {
    this.head = new NODE(data);
  }

  push(data: number): void {
    if (this.size === 0) this.intialize(data);
    else if (this.size === this.max) console.log("Cann't use push() method on full of stack!")
    else {
      let newNode: NODE | null = new NODE(data);
      newNode.next = this.head;
      this.head = newNode;
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
    else console.log(`Stack have a top: ${this.head?.data}`);
  }

  print(): void {
    if (this.size === 0) console.log("Cann't use method print() on empty stack!");
    else {
      let current = this.head;
      let text = "";
      while (current !== null) {
        if (current.next === null)
          text += current.data;
        else 
          text += current.data + " => ";
        current = current.next;
      }
      console.log(text);
    }
  }
}


let stack = new STACK([1,2,3,4,5])
stack.print();