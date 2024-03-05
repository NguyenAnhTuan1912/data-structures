#[derive(Debug)]
pub struct Stack {
    head: Vec<i32>,
    size: i32,
    max: u8,
}

impl Stack {
    fn new() -> Self {
        Stack {
            head: Vec::new(),
            size: 0,
            max: 10,
        }
    }
    fn new_arr(mut vec: Vec<i32>) -> Self {
        let mut stack = Stack::new();
        vec.reverse();
        for value in vec.iter() {
            stack.head.push(*value);
            stack.size += 1;
            if stack.size >= stack.max.into() {
                println!("---Stack full memory!---\n");
                break;
            }
        }
        stack
    }
    fn print_display(mut self) {
        println!("Stack: {:?}", self.head);
        println!("Pop stack: {:?}", self.head.pop());
        println!("Pop stack: {:?}", self.head.pop());
        println!("Pop stack: {:?}", self.head.pop());
        println!("Pop stack: {:?}", self.head.pop());
        println!("Pop stack: {:?}", self.head.pop());
        println!("Pop stack: {:?}", self.head.pop());
        println!("Stack Size: {:?}", self.size);
    }
}
pub fn exer_3() {
    let mut st = Stack::new_arr(vec![1, 2, 3, 4, 5]);
    st.print_display()
}
