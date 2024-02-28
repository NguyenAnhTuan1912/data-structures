struct ListNodeValue<T> {
    item: T,
    next: Box<ListNode<T>>,
}

impl<T> ListNodeValue<T> {
    fn new(item: T, next: Box<ListNode<T>>) -> Self {
        Self { item, next }
    }
}

enum ListNode<T> {
    Empty,
    NonEmpty(ListNodeValue<T>),
}

impl<T> ListNode<T> {
    fn new(item: T, next: Box<ListNode<T>>) -> Self {
        ListNode::NonEmpty(ListNodeValue::new(item, next))
    }

    fn take(&mut self) -> Self {
        let mut cur = Self::Empty;
        std::mem::swap(&mut cur, self);
        cur
    }
}

pub struct SinglyLinkedList<T> {
    head: Box<ListNode<T>>,
    size: usize,
}

impl<T> SinglyLinkedList<T> {
    pub fn new() -> Self {
        Self {
            head: Box::new(ListNode::Empty),
            size: 0,
        }
    }

    pub fn len(&self) -> usize {
        self.size
    }

    pub fn push(&mut self, item: T) {
        let cur_head = self.head.take();
        let new_node = Box::new(ListNode::new(item, Box::new(cur_head)));

        self.head = new_node;
        self.size += 1;
    }

    pub fn pop(&mut self) -> Option<T> {
        let node = self.head.take();

        if let ListNode::NonEmpty(node) = node {
            self.head = node.next;
            self.size -= 1;
            Some(node.item)
        } else {
            None
        }
    }
}

fn main() {
    unimplemented!();
}

#[cfg(test)]
mod tests {
    use super::SinglyLinkedList;

    #[test]
    fn it_works() {
        let mut linked_list: SinglyLinkedList<usize> = SinglyLinkedList::new();
        for i in 1..=10 {
            linked_list.push(i);
        }

        for i in (1..=10).rev() {
            let cur = linked_list.pop();
            assert_eq!(Some(i), cur);
        }

        assert_eq!(None, linked_list.pop());
    }

    #[test]
    fn test_series_of_pops_and_inserts() {
        let mut list: SinglyLinkedList<usize> = SinglyLinkedList::new();
        assert_eq!(list.pop(), None);

        list.push(3);
        list.push(42);
        assert_eq!(list.pop(), Some(42));
        assert_eq!(list.len(), 1);

        list.push(93);
        assert_eq!(list.len(), 2);
        assert_eq!(list.pop(), Some(93));
        assert_eq!(list.pop(), Some(3));
        assert_eq!(list.pop(), None);
        assert_eq!(list.len(), 0);

        list.push(20);
        assert_eq!(list.pop(), Some(20));
        assert_eq!(list.pop(), None);
    }
}
