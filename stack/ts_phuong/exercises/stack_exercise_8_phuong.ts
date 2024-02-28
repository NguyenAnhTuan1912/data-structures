
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
    if (data !== undefined) {
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

  getTop(): T | undefined {
    if (this.size === 0) {
      console.log("Cann't use method getTop() on empty stack!");
      return undefined;
    } else {
      console.log(`Stack have a top: ${this.head?.data}`);
      return this.head?.data
    }
  }

  print(): string {
    if (this.size === 0) {
      console.log("Cann't use method print() on empty stack!");
      return "";
    }
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
      return text;
    }
  }

  clear(): void {
    if (this.size === 0) console.log("Cann't use method clear() on empty stack!");
    else {
      while (this.size !== 0) this.pop();
    }
  }
}

class UndoRedoStack {
  undoStack: STACK<STACK<number>>;
  redoStack: STACK<STACK<number>>;
  constructor(state: number[]) {
    this.redoStack = new STACK<STACK<number>>([]);
    this.undoStack = new STACK<STACK<number>>([]);
    this.redoStack.push(new STACK<number>(state));
  }

  printUndoStack(): void {
    let currentUndoStackNode = this.undoStack.head;
    let text1 = "";
    while (currentUndoStackNode !== null) {
      if (currentUndoStackNode.next !== null)
      text1 += `(${(currentUndoStackNode.data as STACK<number>).print()}) =>`;
      else
      text1 += `(${(currentUndoStackNode.data as STACK<number>).print()})`;
      currentUndoStackNode = currentUndoStackNode.next;
    }
    console.log("currentUndoStackNode", text1)
  }

  printRedoStack(): void {
    let currentRedoStackNode = this.redoStack.head;
    let text1 = "";
    while (currentRedoStackNode) {
      if (currentRedoStackNode.next !== null)
      text1 += `(${(currentRedoStackNode.data as STACK<number>).print()}) =>`;
      else
      text1 += `(${(currentRedoStackNode.data as STACK<number>).print()})`;
      currentRedoStackNode = currentRedoStackNode.next;
    }
    console.log("currentRedoStackNode", text1)
  }

  currentState(): void {
    console.log((this.redoStack!.head as NODE<STACK<number>>).data.print());
  }

  private createStateWithIndexOperation(index1: number | null = null, index2: number | null = null, data: number | null = null, operation: 'add' | 'delete' | 'swap' | 'pop' | 'push'): void {
    let prevState = this.redoStack.pop(); // Lấy trạng thái tiếp theo mà không loại bỏ nó khỏi redoStack
    if (prevState) {
      let newState = new STACK<number>([]);

      // Lặp qua mỗi phần tử trong prevState từ đỉnh đến đáy và thêm chúng vào newState
      let current = prevState.head;
      const tempStack = new STACK<number>([]);
      while (current) {
          tempStack.push(current.data);
          current = current.next;
      }

      // Lặp qua tempStack từ đỉnh đến đáy và thêm các phần tử vào newState
      current = tempStack.head;
      while (current) {
          newState.push(current.data);
          current = current.next;
      }

      switch (operation) {
        case 'add':
          (data!==null && index1!==null) && newState.add(index1, data);
          break;
        case 'delete':
          (index1 !==null) && newState.delete(index1);
          break;
        case 'swap':
          (index1 !==null && index2!==null) && newState.swap(index1, index2);
          break;
        case 'push':
          console.log('push method', data);
          (data !== null) && newState.push(data);
          break;
        case 'pop':
          newState.pop();
          break;
        default:
          break;
      }

      this.undoStack.push(prevState); // Thêm prevState vào undoStack
      this.redoStack.clear(); // Xóa hết redoStack
      this.redoStack.push(newState); // Đặt lại redoStack với newState

      this.printUndoStack();
      this.printRedoStack();
    }
  }

  push(state: number): void {
    this.createStateWithIndexOperation(null, null, state, 'push');
  }

  pop(): void {
    this.createStateWithIndexOperation(null, null, null, 'pop');
  }

  add(index: number, data: number): void {
      this.createStateWithIndexOperation(index, null, data, 'add');
  }

  delete(index: number): void {
      this.createStateWithIndexOperation(index, null, null, 'delete');
  }

  swap(index1: number, index2: number): void {
      if ((index2 - index1) > 0) {
        this.createStateWithIndexOperation(index1, index2, null, 'swap');
      }
  }

  undo(): void {
    if (this.undoStack.size >= 1) {
      this.redoStack.push(this.undoStack.pop());
      this.currentState();
    }
  }

  redo(): void {
    if (this.redoStack.size >= 2) {
      this.undoStack.push(this.redoStack.pop());
      this.currentState();
    }
  }

  clear(): void {
    if (this.redoStack.size >= 1) {
      let state = this.redoStack.pop();
      this.undoStack.clear();
      this.redoStack.clear();
      this.redoStack.push(state);
    }
  }
}

let stackUndoRedo = new UndoRedoStack([1, 2, 3]);
stackUndoRedo.printUndoStack();
stackUndoRedo.printRedoStack();

console.log("---------");
stackUndoRedo.push(0);
stackUndoRedo.currentState();

console.log("---------");
stackUndoRedo.pop();
stackUndoRedo.currentState();

console.log("---------");
stackUndoRedo.add(1, 100);
stackUndoRedo.currentState();

console.log("---------");
stackUndoRedo.delete(0);
stackUndoRedo.currentState();

console.log("---------");
stackUndoRedo.swap(0,2);
stackUndoRedo.currentState();

console.log("---------");
stackUndoRedo.undo();
stackUndoRedo.printUndoStack();
stackUndoRedo.printRedoStack();

console.log("---------");
stackUndoRedo.redo();
stackUndoRedo.printUndoStack();
stackUndoRedo.printRedoStack();



