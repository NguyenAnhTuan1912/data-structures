/// author:  Luong Van Phap
// Create a linked list class whose Nodes have a data part is integer type and it has a print method. Initialize 5 linked list instances and print their element’s data to console
#[derive(Debug)]
pub struct ListNode {
    // Node
    data: i32, // data đc luuw là int
    next: Option<Box<ListNode>>, // Option - Trả Some() thì là có node ở sau- Box dùng để lưu vị
               // trí ô nhớ chứ ListNode kế tiếp
}

impl ListNode {
    // Implemention cho linkedlist
    // hàm khởi tạo Node đầu tiên
    fn new(data: i32) -> ListNode {
        ListNode { data, next: None } // next là None
    }
}
// convert từ vector( array) sang linkedlist
fn to_list(vector: Vec<i32>) -> Option<Box<ListNode>> {
    let mut cur = None; // Dùng Option nên biến này dùng để trả về kiểu Some or Node.
    for &data in vector.iter() {
        let mut new_node = ListNode::new(data);
        new_node.next = cur; // node tạo đầu tiên sẽ có next là Node
        cur = Some(Box::new(new_node)); // cập nhật lại cur ( đại diện cho list). tới đây nghĩa là
                                        // List đã có node
    }
    cur // trả về Some(bên trong này là List các Node  )
}

fn main() {
    let vector1 = vec![100, 20, 22, -10, -02, 35, 55];
    let vector2 = vec![0];
    let vector3 = vec![1, 2, 3];
    let vector4 = vec![-1, -2, 2, 3];
    let vector5 = vec![0, 1, 2, 3];
    println!("{:#?}", to_list(vector1));
    println!("{:#?}", to_list(vector2));
    println!("{:#?}", to_list(vector3));
    println!("{:#?}", to_list(vector4));
    println!("{:#?}", to_list(vector5));
}
