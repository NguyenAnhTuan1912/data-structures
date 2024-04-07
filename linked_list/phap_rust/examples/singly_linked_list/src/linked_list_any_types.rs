/// use enum làm Linkedlist
enum Node {
    Nil,
    Node {
        value: Box<dyn std::any::Any>, // trong Any: lưu bất kì kiểu data- và có hàm downcast_ref
        // để lấy các case xem type đc lưu ở Node là gì.
        next: Box<Node>, // luu vùng nhớ Node tiếp theo
    },
}

impl std::fmt::Debug for Node {
    // imp Debug cho Node
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> Result<(), std::fmt::Error> {
        // match trường hợp kiểu types
        match self {
            Node::Nil => write!(f, "Nil"),
            Node::Node { value, next } => {
                if let Some(value) = value.downcast_ref::<f64>() {
                    // case type la float
                    write!(f, "Node({value}) -> {next:?}")
                } else if let Some(value) = value.downcast_ref::<i32>() {
                    // case type la int
                    write!(f, "Node({value}) -> {next:?}")
                } else if let Some(value) = value.downcast_ref::<&str>() {
                    // case là str
                    write!(f, "Node({value:?}) -> {next:?}")
                } else {
                    // case Unknown
                    write!(f, "Node(<unknown type>) -> {next:?}")
                }
            }
        }
    }
}

fn main() {
    let list = Node::Node {
        value: Box::new(56.7),
        next: Box::new(Node::Node {
            value: Box::new("hello"),
            next: Box::new(Node::Node {
                value: Box::new(77),
                next: Box::new(Node::Nil),
            }),
        }),
    };
    dbg!(list);
    let list_1 = Node::Nil; // node trong
    dbg!(list_1);
}
