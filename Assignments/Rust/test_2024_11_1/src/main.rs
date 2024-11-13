use std::collections::LinkedList;
use std::collections::VecDeque;

fn main() {
    // 创建一个链表
    let mut list = LinkedList::new();

    // 在链表中添加一些元素
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    println!("链表内容: {:?}", list);

    // 创建一个栈(使用VecDeque作为栈)
    let mut stack = VecDeque::new();

    // 压入一些元素
    stack.push_back(10);
    stack.push_back(20);
    stack.push_back(30);

    println!("栈内容: {:?}", stack);

    // 弹出并打印栈顶元素
    if let Some(top) = stack.pop_back() {
        println!("弹出栈顶元素: {}", top);
    }

    println!("弹出后的栈内容: {:?}", stack);
}
