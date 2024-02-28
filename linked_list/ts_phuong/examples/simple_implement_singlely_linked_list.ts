class NODE<T> {
  data: T;
  // when NODE is declared is next property is null
  next: NODE<T> | null = null; 

  constructor(data: T) {
    this.data = data;
  }
}

class SINGLELYLINKEDLIST<T> {
  head: NODE<T> | null = null;
  tail: NODE<T> | null = null;
  
  constructor(ArrayNode: T[]) {
    let index = 0;
    while (ArrayNode.length !== index) {
      this.append(ArrayNode[index]);
      index++;
    }
  }

  comparator(a: T, b: T): boolean {
    return a === b;
  }
  //--OR--
  // comparator = (a: T, b: T): boolean => a === b;
  
  append(data: T) : void {
    if (this.head === null && this.tail === null) {
      this.head = new NODE(data);
      this.tail = this.head;
    } else {
      let current = new NODE(data);
      if (this.tail?.next === null) {
        this.tail.next = current;
        this.tail = current;
      }
    }
  }

  preappend(data: T): void {
    if (this.head === null && this.tail === null) {
      this.head = new NODE(data);
      this.tail = this.head;
    } else {
      let current = new NODE(data);
      current.next = this.head;
      this.head = current;
    }
  }

  delete(data: T): void {
    if (!this.head) return;
    // Check if the head node is the node to be removed
    if (this.comparator(this.head.data, data)) {
      this.head = this.head.next;
      return;
    }

    let current = this.head.next;
    let previous = this.head;

    while (current) {
      if (this.comparator(current.data, data)) {
        previous.next = current.next;
        if (!current.next) {
          // If the deleted node was the last node, update tail
          this.tail = previous;
        }
        return;
      } else {
        previous = current;
        current = current.next;
      }
    }
  }

  search(data: T): void {
    let current = this.head;
    while (current) {
      if (current.data === data) {
        console.log("Node can tim:", current);
        break;
      }
      current = current?.next ?? null;
      if (current === null) {
        console.log("Kh tim thay node");
      }
    }
  }

  traverse() : void {
    if (!this.head) {
      console.log("Traverse empty");
      return;
    }
    let current = this.head;
    let text = "";
    while (current?.next !== null) {
      text += current?.data + "=>"
      current = current!.next;
    }
    text += current.data
    console.log(text);
  } 
}

const list = new SINGLELYLINKEDLIST<number>([1,2,3,4,5,6,7,8,9]);
list.delete(9)
list.traverse();



