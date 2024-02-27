/*
  @author Nguyen Anh Tuan
  Quetions 8:
  Create an int (number) linked list class has getAt method.
  Initialize a linked list and perform getAt method.

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

  initializeLinkedList(data: number): void {
    this.head = new NODE(data);
    this.tail = this.head;
  }

  getAt(index: number){
    if (this.size - 1 < index) console.log("Go over index")
    else if (this.size === 0) console.log("Empty list!");
    else {
      let current = this.head;
      let count = 0;
      while (count !== index) {
        current = current!.next;
        count++;
      }
      console.log("getAt " + index + " is: " + current?.data)
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
linkedList.print();
linkedList.getAt(0);



