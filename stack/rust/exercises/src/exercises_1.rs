/*!
author: phapdev
Create a generic Stack has pop, push, getSize, isEmpty and getTop. Initializer 3 stack of People, Animals and Vehicle (each stack has arbitrary numbers of items). Perform all methods of Stack.
*/

use crate::Stack;
/// Lưu dữ liệu cho động vật, nguoi va xe co
#[derive(Debug)]
enum Class {
    /// Luu du lieu cho dong vat
    Animal { name: String, age: u32 },
    /// Luu du lieu cho nguoi`
    People {
        height: u8,
        weight: u8,
        name: String,
    },
    /// Luu du lieu cho xe co
    Vehicle { name_vehicle: String, price: u32 },
}
/// Run Exercises 1
pub fn exer_1() {
    let mut stack_vehicle: Stack<Class> = Stack::new();
    stack_vehicle.push(Class::Vehicle {
        name_vehicle: "BMW".into(),
        price: 100_000_000,
    });

    stack_vehicle.push(Class::Vehicle {
        name_vehicle: "Mecsedec".into(),
        price: 300_000_000,
    });
    println!("-----Vehicle-----\n");
    println!("Stack: {:?}\n", stack_vehicle);
    println!("Pop: {:?}\n", stack_vehicle.pop().unwrap());
    println!("getSize: {:?}\n", stack_vehicle.lenght());
    println!("Is Empty: {:?}\n", stack_vehicle.is_empty());

    let mut stack_people: Stack<Class> = Stack::new();
    stack_people.push(Class::People {
        height: 150,
        weight: 45,
        name: "Phương".into(),
    });
    stack_people.push(Class::People {
        height: 170,
        weight: 55,
        name: "Tuấn".into(),
    });
    println!("-----People-----\n");
    println!("Stack: {:?}\n", stack_people);
    println!("Pop: {:?}\n", stack_people.pop().unwrap());
    println!("getSize: {:?}\n", stack_people.lenght());
    println!("Is Empty: {:?}\n", stack_people.is_empty());

    let mut stack_animals: Stack<Class> = Stack::new();
    stack_animals.push(Class::Animal {
        name: "Dog".into(),
        age: 5,
    });
    stack_animals.push(Class::Animal {
        name: "Cat".into(),
        age: 1,
    });

    println!("-----Animals-----\n");
    println!("Stack: {:?}\n", stack_animals);
    println!("Pop: {:?}\n", stack_animals.pop().unwrap());
    println!("getSize: {:?}\n", stack_animals.lenght());
    println!("Is Empty: {:?}\n", stack_animals.is_empty());
}
