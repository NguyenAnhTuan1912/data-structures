/*
  @author Nguyen Anh Tuan
  Quetions 7:
  Create an int (number) linked list class has required methods, removeLast,
  removeFirst and removeAt. Declare a linked list instance and add numbers of
  random numbers and perform all of its methods.

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

  removeLast(): void {
    if (this.size === 0) console.log("Empty list!");
    else {
      let current = this.head; 
      while (current!.next !== this.tail) current = current!.next;
      current!.next = null; 
      this.tail = current;
      this.size--;
    }
  }

  removeFisrt(): void {
    if (this.size === 0) console.log("Empty list!");
    else {
      let current = this.head!.next;
      this.head = current
      this.size--;
    }
  }


  removeAt(index: number) {
    // ex: 1 -> 2 -> 3 -> 4
    // insertAt(1) => 1 -> 3 -> 4 (2 at index 1 deleted)
    if (this.size - 1 < index) console.log("Go over index")
    else if (this.size === 0) console.log("Empty list!");
    else {
      if (index === 0) this.removeFisrt();
      else if (index === this.size -1) this.removeLast();
      else {
        let current: NODE | null = this.head;
        let count =0;
        while (count !== index -1) {
          current = current!.next;
          count++;
        }
        current!.next = current!.next!.next;
      }
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
linkedList.removeLast();
linkedList.removeFisrt();
linkedList.print();

linkedList.removeAt(2);
linkedList.print();



