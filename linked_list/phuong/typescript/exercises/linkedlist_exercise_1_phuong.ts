/*
  @author Nguyen Anh Tuan
  Quetions 1:
  Create a linked list class whose Nodes have a data part is integer type and it has a print method.
  Initialize 5 linked list instances and print their element’s data to console.

  Done.
*/

class NODE{
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
  constructor(NodeArray: number[]) {
    NodeArray.map((node: number) => this.append(node));
  }

  initializeLinkedList(data: number): void {
    this.head = new NODE(data);
    this.tail = this.head;
  }

  append(data: number): void {
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

const linkedLists: LINKEDLIST[] = [
  new LINKEDLIST([1, 2, 6]),
  new LINKEDLIST([3, 6, 8]),
  new LINKEDLIST([9, 4, 3]),
  new LINKEDLIST([4, 2, 6]),
  new LINKEDLIST([1, 2, 0])
];

for (let i = 0; i < linkedLists.length; i++) {
  console.log(`List ${i + 1}:`);
  linkedLists[i].print();
}


