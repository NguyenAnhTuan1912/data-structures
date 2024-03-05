/*!
author: phapdev
Stack simple
*/

/// Stack đơn giản, Chỉ lưu 1 `Vec<T>` có cùng 1 kiểu dữ liệu.
#[derive(Debug, Clone)]
pub struct Stack<T> {
    pub stack: Vec<T>,
}
/// Implemention code cho Stack
impl<T> Stack<T> {
    /// contructor
    pub fn new() -> Self {
        Stack { stack: Vec::new() }
    }
    /// `Pop` trả về giá trị trong stack -> có kiểu `Option<T>`,
    /// Nếu có giá trị trả về Some(item) nếu trống trả về None
    pub fn pop(&mut self) -> Option<T> {
        self.stack.pop()
    }
    pub fn push(&mut self, item: T) {
        self.stack.push(item)
    }

    pub fn is_empty(&self) -> bool {
        self.stack.is_empty()
    }
    /// Trả về số phần tử có trong stack
    pub fn lenght(&self) -> usize {
        self.stack.len()
    }

    /// Trả về item cuối cùng của stack( xem cuối )
    pub fn peek(&self) -> Option<&T> {
        self.stack.last()
    }
}
