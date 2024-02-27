#[derive(Debug)]
enum DynamicType {
    /// cac types do minh xác định sẽ được thêm vào list
    /// bool, enum, .... nhiều type khác nữa
    Float(f64),
    Int(i32),
    Str(&'static str),
}

enum Node {
    Nil,
    Node { value: DynamicType, next: Box<Node> },
}

impl std::fmt::Debug for Node {
    // create print method equal implemention Debug for Node
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> Result<(), std::fmt::Error> {
        match self {
            Node::Nil => write!(f, "Nil"),
            Node::Node { value, next } => write!(f, "Node({value:?}) -> {next:?}"),
        }
    }
}

fn main() {
    use DynamicType::*; // su dung enum DynamicType
    let list = Node::Node {
        value: Float(56.7),
        next: Box::new(Node::Node {
            value: Str("demo"),
            next: Box::new(Node::Node {
                value: Int(99),
                next: Box::new(Node::Nil),
            }),
        }),
    };
    dbg!(list);
}
