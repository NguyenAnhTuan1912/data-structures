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
  prev: NODE | null = null;

  constructor(data: number) {
    this.data = data;
  }
}

class DOUBLELYLINKEDLIST {
  head: NODE | null = null;
  tail: NODE | null = null;
  size: number =  0;

  constructor(arrayNode: number[]) {
    arrayNode.map((node: number) => this.insertLast(node));
  }
  
  initialize(data: number) {
    this.head = new NODE(data);
    this.tail = this.head;
  }

  insertFirst(data: number) {
    if (this.size === 0) this.initialize(data);
    else {
      let current = this.head;
      let newNode = new NODE(data);
      current!.prev = newNode;
      newNode.next = current;
      this.head = newNode;
    }
    this.size++;
  }
  
  insertLast(data: number) {
    if (this.size === 0) this.initialize(data);
    else {
      let current = this.tail;
      let newNode = new NODE(data);
      current!.next = newNode;
      newNode.prev = current;
      this.tail = newNode; 
    }
    this.size++;
  }
  
  insertAt(index:number, data: number) {
    if (index > this.size - 1) console.log("index is out of bounds");
    else {
      if (index === 0) this.insertFirst(data);
      else if (index === this.size - 1) this.insertLast(data); 
      else {
        let current = this.head;
        let newNode = new NODE(data);
        if (index > this.size/2) {
          let count = this.size - 1 - index;
          while (count !== -1) {
            current = current!.prev;
            count--;
          }
        } else {
          let count = index;
          while (count !== 1) {
            current = current!.next;
            count--;
          }
        }
        current!.next!.prev = newNode;
        newNode.next = current!.next;
        newNode.prev = current;
        current!.next = newNode;
        this.size++;
      }
    }
  }

  insertByOrder(data: number) {
    if (this.size === 0) this.initialize(data);
    else {
      if (this.head!.data > data) this.insertFirst(data);
      else if (this.tail!.data < data) this.insertLast(data);
      else {
        let current = this.head;
        while (current !== this.tail) {
          if (current!.data < data && current!.next!.data > data) {
            console.log("vao");
            let newNode = new NODE(data);
            current!.next!.prev = newNode;
            newNode.next = current!.next;
            newNode.prev = current;
            current!.next = newNode;

            this.size++;
          }
          current = current!.next;
        }
      }
    }
  }
  
  removeLast() {
    if (this.size === 0) console.log("Empty");
    else if (this.size === 1) {
      this.head = null;
      this.tail = null;
    } else {
      this.tail!.prev!.next = null;
      this.tail = this.tail!.prev;
    }
    this.size--;
  }

  removeFirst() {
    if (this.size === 0) console.log("Empty");
    else if (this.size === 1) {
      this.head = null;
      this.tail = null;
    } else {
      this.head = this.head!.next;
      this.head!.prev = null;
    }
    this.size--;
  }

  removeAt(index: number) {
    if (index > this.size - 1) console.log("index is out of bounds");
    else {
      if (index === 0) this.removeFirst();
      else if (index === this.size - 1) this.removeLast(); 
      else {
        let current;
        if (index > this.size/2) {
          current = this.tail;
          let count = this.size - 1 - index;
          while (count !== 0) {
            current = current!.prev;
            count--;
          }
        } else {
          current = this.head;
          let count = index;
          while (count !== 0) {
            current = current!.next;
            count--;
          }
        }
        console.log("current", current.data);
        current!.next!.prev = current!.prev;
        current!.prev!.next = current!.next;
        current = null;
        this.size--;
      }
    }
  }

  getAt(index: number) {
    if (index > this.size - 1) console.log("index is out of bounds");
    else {
     
      let current;
      if (index > this.size/2) {
        current = this.tail;
        let count = this.size - 1 - index;
        while (count !== 0) {
          current = current!.prev;
          count--;
        }
      } else {
        current = this.head;
        let count = index;
        while (count !== 0) {
          current = current!.next;
          count--;
        }
      }
      console.log("GetAt index " + index + "result is :" + current?.data);
    }
  }

  print(): void {
    if (this.size === 0) console.log("Empty");
    else {
      let current = this.head;
      let text = "";
      while (current) {
        if (current === this.tail) {
          text += current.data;
          current = null;
        } else {
          text += current.data + "=>";
          current = current.next;
        }
      }
      console.log(text);
    }
  }
}


let list = new DOUBLELYLINKEDLIST([1, 4, 8, 16, 32])
list.insertFirst(0);
list.insertLast(9);
list.insertAt(1, 10);
list.insertByOrder(7);
list.print();

list.removeLast();
list.removeFirst();
list.print();

list.removeAt(2);
list.print();

list.getAt(7);