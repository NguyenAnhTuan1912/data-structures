
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

  constructor(arrayNode: T[]) {
    arrayNode.reverse().map((node: T) => this.push(node));
  } 

  intialize(data: T): void {
    this.head = new NODE<T>(data);
    this.size++;
  }

  push(data: T | undefined): void {
    if (data === undefined) return;
    else {
      if (this.size === 0) this.intialize(data);
      else if (this.size === this.max) console.log("Cann't use push() method on full of stack!")
      else {
        let newNode: NODE<T> | null = new NODE<T>(data);
        newNode.next = this.head;
        this.head = newNode;
        this.size++;
      }
    }
  }

  pop(): T | undefined {
    if (this.size === 0) {
      console.log("Cann't use method pop() on empty stack!");
      return undefined;
    }
    else if (this.size === 1) {
      const value = this.head!.data as T;
      this.head = null;
      this.size = 0;
      return value;
    }
    else {
      let current = this.head;
      let value = this.head!.data as T;
      this.head = current!.next;
      current = null;
      this.size--;
      return value;
    }
  }

  add(index: number, data: T): void {
    if (index > this.size) console.log("Cann't use method add() when index go over bounds!");
    else if (index === 0) this.push(data);
    else {
      let tempStack = new STACK<T>([]);
      let count = 0;
      while (count !== index) {
        tempStack.push(this.pop());
        count ++;
      }

      this.push(data);

      while (tempStack.size !== 0) {
        this.push(tempStack.pop())
      }
    }
  }

  delete(index: number): void {
    if (index > this.size -1) console.log("Cann't use method add() when index go over bounds!");
    else if (index === 0) this.pop();
    else {
      let tempStack = new STACK<T>([]);
      let count = 0;
      while (count !== index+1) {
        tempStack.push(this.pop());
        count ++;
      }
      
      tempStack.pop(); // remove the node which needs to be deleted

      while (tempStack.size !== 0) {
        this.push(tempStack.pop());
      }
    }
  }

  swap(index1: number, index2: number): void {
    if (index1 > this.size || index2 > this.size) console.log("Cann't use method add() when index go over bounds!");
    // else if (index === 0) this.push(data);
    else {
      let tempStack = new STACK<T>([]);
      let count = 0;
      let dataIndex1, dataIndex2;
      while (count !== index2 + 1) {
        if (count === index1) dataIndex1 = this.pop();
        else if (count === index2) dataIndex2 = this.pop();
        else tempStack.push(this.pop());
        count ++;
      }

      this.push(dataIndex1);
      
      let count1 = 0;
      while (count1 !== (index2 - index1 - 1)) {
        this.push(tempStack.pop())
        count1++;
      }

      this.push(dataIndex2);
      while (tempStack.size !== 0) {
        this.push(tempStack.pop())
      }
    }
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

let stack = new STACK<number>([7, 6, 5, 8, 6, 7, 3, 2])
stack.add(4, 99);
stack.print();
stack.getSize();


stack.delete(4);
stack.print();

stack.getSize();

stack.swap(2, 3);
stack.print();