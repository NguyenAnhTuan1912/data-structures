class NODE {
  constructor(data) {
    this.next = null;
    this.data = data;
  }
}

class STACK {
  constructor(arrayNode) {
    this.head = null;
    this.size = 0;
    this.max = 10;
    arrayNode.reverse().map((node) => this.push(node));
  }
  intialize(data) {
    this.head = new NODE(data);
    this.size++;
  }
  push(data) {
    if (data !== undefined) {
      if (this.size === 0) this.intialize(data);
      else if (this.size === this.max)
        console.log("Cann't use push() method on full of stack!");
      else {
        let newNode = new NODE(data);
        newNode.next = this.head;
        this.head = newNode;
        this.size++;
      }
    }
  }
  pop() {
    if (this.size === 0) {
      console.log("Cann't use method pop() on empty stack!");
      return undefined;
    } else if (this.size === 1) {
      const value = this.head.data;
      this.head = null;
      this.size = 0;
      return value;
    } else {
      let current = this.head;
      let value = this.head.data;
      this.head = current.next;
      current = null;
      this.size--;
      return value;
    }
  }
  empty() {
    let current = this.head;
    while (current) {
      this.pop();
      current = current.next;
    }
    this.size = 0;
  }
  print() {
    if (this.size === 0) {
      console.log("Cann't use method print() on empty stack!");
      return "";
    } else {
      let current = this.head;
      let text = "";
      while (current !== null) {
        if (current.next === null) text += current.data;
        else text += current.data + " => ";
        current = current.next;
      }
      return text;
    }
  }
  getTop() {
    if (this.size === 0) {
      console.log("Cann't use method getTop() on empty stack!");
      return undefined;
    } else {
      return this.head.data;
    }
  }
}

class UNDOREDOSTACK {
  constructor(state) {
    this.redoStack = new STACK([]);
    this.undoStack = new STACK([]);
    this.redoStack.push(state);
  }
  printUndoStack() {
    let currentUndoStackNode = this.undoStack.head;
    let text1 = "";
    while (currentUndoStackNode !== null) {
      if (currentUndoStackNode.next !== null)
        text1 += `(${JSON.stringify(currentUndoStackNode.data)}) =>`;
      else text1 += `(${JSON.stringify(currentUndoStackNode.data)})`;
      currentUndoStackNode = currentUndoStackNode.next;
    }
    console.log("currentUndoStackNode", text1);
  }
  printRedoStack() {
    let currentRedoStackNode = this.redoStack.head;
    let text1 = "";
    while (currentRedoStackNode) {
      if (currentRedoStackNode.next !== null)
        text1 += `(${JSON.stringify(currentRedoStackNode.data)}) =>`;
      else text1 += `(${JSON.stringify(currentRedoStackNode.data)})`;
      currentRedoStackNode = currentRedoStackNode.next;
    }
    console.log("currentRedoStackNode", text1);
  }
  currentState() {
    console.log("currentState", JSON.stringify(this.redoStack.head.data));
  }

  insert(state) {
    this.undoStack.push(this.redoStack.pop());
    this.redoStack.empty();
    this.redoStack.push(state);
  }
  undo() {
    if (this.undoStack.size >= 1) {
      this.redoStack.push(this.undoStack.pop());
      return this.redoStack.getTop();
    }
  }
  redo() {
    if (this.redoStack.size >= 2) {
      this.undoStack.push(this.redoStack.pop());
      return this.redoStack.getTop();
    }
  }
  clear() {
    if (this.redoStack.size >= 1) {
      let state = this.redoStack.pop();
      this.undoStack.empty();
      this.redoStack.empty();
      this.redoStack.push(state);
    }
  }
}

document.addEventListener("DOMContentLoaded", function () {
  const $ = document.querySelector.bind(document);

  const _previewText = $("#text-preview");

  const _form = $("#form-control");

  const _title = $("#text-title");
  const _color = $("#text-color");
  const _size = $("#text-size");

  // btn footer
  const _undoBtn = $("#undo-btn");
  const _redoBtn = $("#redo-btn");
  const _clearBtn = $("#clear-btn");

  const dataDefault = {
    title:
      "Lorem ipsum is placeholder text commonly used in the graphic, print, and publishing industries for previewing layouts and visual mockups.",
    color: "#454545",
    size: "45"
  };

  const stateStack = new UNDOREDOSTACK(dataDefault);
  applyState(dataDefault);

  function applyState(data) {
    console.log("data", data);
    _title.value = data.title;
    _color.value = data.color;
    _size.value = data.size;
    applyPreview(data.title, data.color, data.size);
  }

  function applyPreview(text, color, size) {
    _previewText.textContent = text;
    _previewText.style.color = color;
    _previewText.style.fontSize = size + "px";
  }

  _form.addEventListener("submit", function (event) {
    event.preventDefault();
    applyPreview(_title.value, _color.value, _size.value);

    stateStack.insert({
      title: _title.value,
      color: _color.value,
      size: _size.value
    });
  });

  _undoBtn.addEventListener("click", function (event) {
    event.preventDefault();
    const currentState = stateStack.undo();
    if (currentState) {
      applyState(currentState);
    } else {
      console.log("currentState: null");
    }
  });

  _redoBtn.addEventListener("click", function (event) {
    event.preventDefault();
    const currentState = stateStack.redo();
    console.log("currentState redo", currentState);
    if (currentState) {
      applyState(currentState);
    } else {
      console.log("currentState: null");
    }
  });

  _clearBtn.addEventListener("click", function (event) {
    event.preventDefault();
    stateStack.clear();
  });
});
