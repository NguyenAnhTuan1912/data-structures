interface IPrintMethod {
  printDetails(): string;
}

class Person implements IPrintMethod {
  name: string = "";
  age: number = 0;

  constructor(name: string, age: number) {
    this.name = name;
    this.age = age;
  }

  printDetails(): string {
    return(`(Name: ${this.name}, Age: ${this.age})`);
  }
}

class Animal implements IPrintMethod {
  name: string = "";
  age: number = 0;
  breed: string = "";

  constructor(name: string, age: number, breed: string) {
    this.name = name;
    this.age = age;
    this.breed = breed;
  }

  printDetails(): string {
    return(`(Name: ${this.name}, Age: ${this.age}, Breed: ${this.breed})`);
  }
}

class Vehicle implements IPrintMethod {
  name: string = "";
  color: string = "";
  speed: number = 0;
  constructor(name:string, color:string, speed:number) {
    this.name = name;
    this.color = color;
    this.speed = speed;
  }

  printDetails(): string {
    return(`(Name: ${this.name}, Color: ${this.color}, Speed: ${this.speed})`);
  }
}

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
    arrayNode.map((node: T) => this.push(node));
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
    else console.log(`Stack have a top: ${(this.head?.data as IPrintMethod).printDetails()}`);
  }

  print(): void {
    if (this.size === 0) console.log("Cann't use method print() on empty stack!");
    else {
      let current = this.head;
      let text = "";
      while (current !== null) {
        if (current.next === null)
          text += (current.data as IPrintMethod).printDetails();
        else 
          text += (current.data as IPrintMethod).printDetails() + " => ";
        current = current.next;
      }
      console.log(text);
    }
  }
}

let peoples = new STACK<Person>([new Person("Phuong", 21), new Person("Nga", 50)]);
peoples.push(new Person("Tam", 30));
peoples.print();
peoples.pop();
peoples.print();
peoples.getTop();
peoples.getSize();
peoples.isEmpty();
peoples.print()


let animals = new STACK<Animal>([new Animal("Kiki", 1, "Golden"), new Animal("Cat", 3, "Long tail")]);
animals.push(new Animal("Aprical", 5, "Africa"));
animals.print();
animals.pop();
animals.print();
animals.getTop();
animals.getSize();
animals.isEmpty();
animals.print()


let vehicles = new STACK<Vehicle>([new Vehicle("KIA Morning", "white", 40), new Vehicle("Mecedes", "Red", 300)]);
vehicles.push(new Vehicle("Vinfast", "black", 180));
vehicles.print();
vehicles.pop();
vehicles.print();
vehicles.getTop();
vehicles.getSize();
vehicles.isEmpty();
vehicles.print()


