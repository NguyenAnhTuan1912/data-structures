// Box<T> : https://doc.rust-lang.org/book/ch15-01-box.html
// box, stack, heap: https://doc.rust-lang.org/rust-by-example/std/box.html#box-stack-and-heap
//https://doc.rust-lang.org/book/ch04-01-what-is-ownership.html#the-stack-and-the-heap

#[derive(Debug)] // macro cho phep việc in ra console
pub struct LinkedList<T>(Option<(T, Box<LinkedList<T>>)>); // tạo LinkedList: dữ liệu kểu <T> và
                                                           // link node bằng Box<>(cấp bộ nhớ trên heap)

// Box<T> là một smart pointẻr của Rust cho phép llocated trên heap gtri kiểu `T`, còn pointer trỏ
// dến gtri đó nằm trên stack

impl<T> LinkedList<T> {
    pub fn new() -> Self {
        LinkedList(None)
    }

    pub fn push_front(&mut self, data: T) {
        let t = self.0.take();
        self.0 = Some((data, Box::new(LinkedList(t))));
    }

    pub fn push_back(&mut self, data: T) {
        match self.0 {
            Some((_, ref mut child)) => child.push_back(data),
            None => self.push_front(data),
        }
    }
}
fn main() {
    let mut ll = LinkedList::new();
    ll.push_front(3);
    ll.push_back(12);
    ll.push_front(1);
    println!("ll = {:#?}", ll);
}
